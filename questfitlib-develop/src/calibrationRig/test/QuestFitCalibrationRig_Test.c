#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "QuestFitCalibrationRig.h"
#include "eLog.h"
#ifdef _MSC_VER
#include <windows.h>
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

#define NUM_SAMPLES 2000

int main(void)
{
    QuestFitCalibrationRig_Init();

#ifdef _MSC_VER
    Sleep(9000);
#else
    sleep(1);
#endif
    QuestFitCalibrationRig_StartCapture(1700.0);
    int counter = 0;
    size_t data_retrieved = 0;
    QuestFitCalibrationSampleInterface_t samples[NUM_SAMPLES];
    while (1)
    {
#ifdef _MSC_VER
        Sleep(1000);
#else
        sleep(1);
#endif
        elogInfo("Trying to get sample");
        QuestFitCalibrationRig_GetSamples(NUM_SAMPLES, samples, &data_retrieved);
        if (data_retrieved >= 1)
        {
            elogInfo("Retrieved %d samples after %d seconds", data_retrieved, counter);
            break;
        }
        counter++;
    }
    Sleep(4000);
    QuestFitCalibrationRig_GetSamples(NUM_SAMPLES, samples, &data_retrieved);
    QuestFitCalibrationRig_GetSamples(NUM_SAMPLES, samples, &data_retrieved);
    counter = 0;
    FILE *fptr;
    fptr = fopen("data.csv", "w");
    if (fptr == NULL)
    {
        elogInfo("Couldn't open file");
    }
    fprintf(fptr, "Fx1, Fy1, Fz1, Fx2, Fy2, Fz2, Fx3, Fy3, Fz3, Fx4, Fy4, Fz4, Fx, Fy, Fz, Mx, My, Mz\n");
    size_t totalSamples = 0;

    struct timespec time1, time2;
    gettime(&time1);
    while (counter < 4)
    {
#ifdef _MSC_VER
        Sleep(200);
#else
        sleep(1);
#endif
        elogInfo("Trying to get sample");
        QuestFitCalibrationRigError_e res = QuestFitCalibrationRig_GetSamples(NUM_SAMPLES, samples, &data_retrieved);
        if (res == QFCR_OK && data_retrieved >= 1)
        {
            totalSamples += data_retrieved;
            elogInfo("Retrieved %d samples after %d seconds", data_retrieved, counter);
            for (int j = 0; j < data_retrieved; j++)
            {
                fprintf(fptr, "%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f\n",
                        samples[j].Fx12,
                        samples[j].Fx34,
                        samples[j].Fy14,
                        samples[j].Fy23,
                        samples[j].Fz1,
                        samples[j].Fz2,
                        samples[j].Fz3,
                        samples[j].Fz4,
                        samples[j].Fx,
                        samples[j].Fy,
                        samples[j].Fz,
                        samples[j].Mx,
                        samples[j].My,
                        samples[j].Mz);
            }
            counter++;
        }
    }
    fclose(fptr);
    gettime(&time2);
    struct timespec elapsed = diff(time1, time2);
    double rate = (((double)totalSamples) / (((double)elapsed.tv_sec) * 1E9 + (double)elapsed.tv_nsec)) * 1E6;
    printf("\n\nGot %d samples in %ld:%ld, rate %.2lf KHz\n", totalSamples, elapsed.tv_sec, elapsed.tv_nsec, rate);
    while (TRUE)
    {
#ifdef _MSC_VER
        Sleep(2000);
#else
        sleep(1);
#endif
    }

    QuestFitCalibrationRig_StopCapture();
    QuestFitCalibrationRig_Destroy();

    return 0;
}