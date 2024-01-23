#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "QuestFitCommon.h"
#include "QuestFitCalibrationRig.h"
#include "eLog.h"
#ifdef _MSC_VER
#include <windows.h>
// #define SIM
int gettime(struct timespec *spec) //C-file part
{
    __int64 wintime;
    GetSystemTimeAsFileTime((FILETIME *)&wintime);
    wintime -= 116444736000000000i64;            //1jan1601 to 1jan1970
    spec->tv_sec = wintime / 10000000i64;        //seconds
    spec->tv_nsec = wintime % 10000000i64 * 100; //nano-seconds
    return 0;
}
#else
int gettime(struct timespec *spec) //C-file part
{
    clock_gettime(CLOCK_MONOTONIC, spec);
    return 0;
}
#endif
struct timespec diff(struct timespec start, struct timespec end)
{
    struct timespec temp;
    if ((end.tv_nsec - start.tv_nsec) < 0)
    {
        temp.tv_sec = end.tv_sec - start.tv_sec - 1;
        temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    }
    else
    {
        temp.tv_sec = end.tv_sec - start.tv_sec;
        temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    }
    return temp;
}
BOOL WINAPI consoleHandler(DWORD signal) {

    if (signal == CTRL_C_EVENT)
    {

        printf("Ctrl-C handled\n"); // do cleanup
    QuestFitCalibrationRig_StopCapture();
    Sleep(2000);
    QuestFitCalibrationRig_Destroy();
        exit(0);
    }

    return TRUE;
}

#define NUM_SAMPLES 2000
#define BLOCK_SIZE 100
#define SAMPLE_RATE 1500
#define MAX_SAMPLE_COUNT (SAMPLE_RATE * 10000)

int main(void)
{
    if (!SetConsoleCtrlHandler(consoleHandler, TRUE)) {
        printf("\nERROR: Could not set control handler"); 
        return 1;
    }

    struct timespec time;
    gettime(&time);

    QuestFitCalibrationRig_Init();

#ifdef _MSC_VER
    Sleep(8000);
#else
    sleep(1);
#endif
    QuestFitCalibrationRig_StartCapture(SAMPLE_RATE);
    int counter = 0;
    size_t data_retrieved = 0;
    QuestFitCalibrationSampleInterface_t samples[NUM_SAMPLES];
    uint64_t samples_received = 0;
    uint64_t pe_count = 0;
    int64_t pe_timestamp = 0;
    int64_t pe_last_timestamp = 0;
    int64_t pe_start_timestamp = 0;
    uint64_t pe_seconds = 0;
    uint32_t count = 5;//200;
    uint64_t computer_start_time, computer_time =0;
    while (samples_received < MAX_SAMPLE_COUNT)
    {
#ifdef _MSC_VER
        Sleep(10);
#else
        sleep(1);
#endif
        data_retrieved = 0;
        if (QuestFitCalibrationRig_GetSamples(BLOCK_SIZE, samples, &data_retrieved) != QFE_OK){
            continue;
        }
        if (data_retrieved >= 1)
        {
            samples_received += data_retrieved;
#ifdef SIM
            pe_count = samples[data_retrieved-1].Fx34;
            pe_timestamp = samples[data_retrieved-1].Fy14;
            if(pe_start_timestamp == 0)
            {
                pe_start_timestamp = samples[0].Fy14;
                gettime(&computer_start_time);
                GetSystemTimeAsFileTime((FILETIME *)&computer_start_time);
                computer_start_time -= (data_retrieved * 10000000) / SAMPLE_RATE;
                
            }
            if (pe_timestamp < pe_last_timestamp){
                pe_seconds ++;
            }
            pe_last_timestamp = pe_timestamp;
#endif
            if (samples_received >= MAX_SAMPLE_COUNT)
            {
#ifdef SIM
                // Compute the difference in samples received vs clock edges reported
                int64_t drift = pe_count - (samples_received-1);
                int64_t drift_ms = (drift * 1000) /SAMPLE_RATE;

                // Compute the difference in clock edges reported vs wall clock time as observed by the PE
                int64_t expected_edges = (pe_seconds * SAMPLE_RATE) + (((pe_timestamp - pe_start_timestamp) / 1000000)  * SAMPLE_RATE)/1000;
                int64_t diff_edges = expected_edges - pe_count;

                GetSystemTimeAsFileTime((FILETIME *)&computer_time);
                uint64_t expected_computer_edges = (((computer_time - computer_start_time) / 10000)  * SAMPLE_RATE)/1000;
                int64_t diff_comp_edges = expected_computer_edges - pe_count;


                elogInfo("Current drift %ld samples, %ld ms at %ld seconds experiment time %ld expected %ld rx %ld edges lost, %ld comp diff", drift, drift_ms, samples_received/SAMPLE_RATE, expected_edges, pe_count, diff_edges, diff_comp_edges);
#else
                elogInfo("%ld seconds experiment time  rx %ld",samples_received/SAMPLE_RATE, samples_received);
#endif
                count --;
            }
        }
    }
    QuestFitCalibrationRig_StopCapture();
    Sleep(3000);
    while (QuestFitCalibrationRig_GetSamples(1, samples, &data_retrieved) == QFE_OK){
        pe_count = samples[data_retrieved-1].Fx34;
        samples_received += data_retrieved;
    }
    elogInfo("Total Samples Received: %ld, PE count %ld", samples_received, pe_count);

    Sleep(2000);
    QuestFitCalibrationRig_Destroy();

    return 0;
}