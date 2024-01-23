/* ======================================================================== */
/* Program    :  DASYLab                                                    */
/* Module     :  GENERAT.C                                                  */
/* ------------------------------------------------------------------------ */
/* Functions  :  All necessary Functions for this Module                    */
/* Created    :  J. Pfannkuch                                               */
/* ======================================================================== */

/*
   Contents:
   0. General functions
   1. Module functions:    Creating, Loading, Saving, Deleting, Data processing
   2. Dialog box handling
   3. Action handling:     Executing event driven actions
   4. DASYLab message handling
   5. Module class initializing
   */

/* ------------------------------------------------------------------------ */
/* Include the necessary Windows and C Header Files                         */
/* ------------------------------------------------------------------------ */

#include "PRE_WIN.H"
#include <WINDOWS.H>
#include "POST_WIN.H"
#include <WINDOWSX.H>
#include <STDLIB.H>
#include <STRING.H>
#include <MATH.H>
#include <FLOAT.H>
#include <STDDEF.H>
//#include "HtmlHelp.h"

/* ------------------------------------------------------------------------ */
/* Include DASYLab�s Header Files                                           */
/* ------------------------------------------------------------------------ */

#include "DLAB.H"
#include "DlabExtTkExample.H"
#include "GENERAT.H"

/*
*  Include the QuestFitSDK header file
*/
#include "QuestFitCalibrationRig.h"
#define QF_TIMEBASE_ID 555
#define QF_TIMEBASE_BLOCKSIZE 100
/* ------------------------------------------------------------------------ */
/* Data structures                                                          */
/* ------------------------------------------------------------------------ */

// MODULE_GENERATOR is a private data structure for the module, which contains
// data to be stored with the flow chart on disk. (I.e. all values set in the
// dialog box.)

typedef struct
{
   char szChannelName[MAX_CHANNEL][24];    // Channel name
   char szUnit[MAX_CHANNEL][MAX_UNIT_LEN]; // Unit
   double fFrequency[MAX_CHANNEL];         // Frequency
   double fAmplitude[MAX_CHANNEL];         // Amplitude
   short nVarFrequency[MAX_CHANNEL];       // Global variable number for frequency
   short nVarAmplitude[MAX_CHANNEL];       // Global variable number for amplitude
   WORD wFunction[MAX_CHANNEL];            // Function type: Sine, sawtooth...
   BOOL bRealTime[MAX_CHANNEL];            // Realtime output
   UINT uiTimeBase;                        // Time Base Identifier
   /*
      Add new parameters here.
      Don't forget to add them in the PARAMETER_INFO also.
      */
} MODULE_GENERATOR;

static PARAMETER_INFO ParameterGenerator[] =
    {
        {"Channel_Name[0..15]", "string[24]", offsetof(MODULE_GENERATOR, szChannelName[0][0]), 0},
        {"Unit[0..15]", "string[64]", offsetof(MODULE_GENERATOR, szUnit[0][0]), 0},
        {"Frequency[0..15]", "double", offsetof(MODULE_GENERATOR, fFrequency[0]), 0},
        {"Amplitude[0..15]", "double", offsetof(MODULE_GENERATOR, fAmplitude[0]), 0},
        {"Frequency_Variable[0..15]", "short", offsetof(MODULE_GENERATOR, nVarFrequency[0]), 0},
        {"Frequency_Variable[0..15]", "short", offsetof(MODULE_GENERATOR, nVarAmplitude[0]), 0},
        {"Function[0..15]", "WORD:0=SINE,1=SQUARE,2=PULSE,3=TRIANGULAR,4=SAWTOOTH",
         offsetof(MODULE_GENERATOR, wFunction[0]), 0},
        {"Real_Time_Output[0..15]", "BOOL", offsetof(MODULE_GENERATOR, bRealTime[0]), 0},
        {"Time_Base_ID", "UINT", offsetof(MODULE_GENERATOR, uiTimeBase), 0},
        {NULL, NULL, 0, 0}};

// VAR_GENERATOR is a private data structure for
// the module, which contains data for temporary use only.

typedef struct
{
   UINT uiBlockSize;
   double fSampleDistance;
} VAR_GENERATOR;

// CHANNEL_GENERATOR is a private data structure for each channel of
// the module, which contains data for temporary use only.

typedef struct
{
   DWORD dwSample;      // Actual sample
   BOOL bPeakDone;      // For pulse output
   double fPtDistance;  // Distance between two x values in [rad]
   double fActPoint;    // New x value in [rad]
   BOOL bComputing;     // Still computing ?
   double fReleaseTime; // Release time of the actual output-block
} CHANNEL_GENERATOR;

/* ------------------------------------------------------------------------ */
/* Global variables                                                         */
/* ------------------------------------------------------------------------ */

static char IdString_GENERATOR[MODULE_NAME_LENGTH + 2];
static char StatusString_GENERATOR[MODULE_STATUS_LENGTH + 2];

unsigned long PerformAction_GENERATOR(MODULE *ThisModule, int wMsg, int wParam, long lParam);

/* ************************************************************************ */
/* 0. General functions                                                     */
/* ************************************************************************ */

/* ------------------------------------------------------------------------ */
/* Function Name     : Compute_GENERATOR                                    */
/* Description       : Calculate distance between two x-values in [rad]     */
/* Parameter         : Pointer to Module Structure                          */
/* ------------------------------------------------------------------------ */

static void Compute_GENERATOR(MODULE *ThisModule)
{
   MODULE_GENERATOR *ModuleInfo = ThisModule->ModuleParameters;
   CHANNEL_GENERATOR *KanalInfo;
   UINT wFifoNr = 0;

   for (wFifoNr = 0; wFifoNr < ThisModule->wNumOutChan; wFifoNr++)
   {
      KanalInfo = ThisModule->TempChannelData[wFifoNr];

      // Distance between two values in [rad]
      KanalInfo->fPtDistance = M_ZWEI_PI *
                               ModuleInfo->fFrequency[wFifoNr] *
                               GetTimeBaseSampleDistance(ModuleInfo->uiTimeBase);
   }
}

/* ------------------------------------------------------------------------ */
/* Function Name     : RegisterStrVarGenerator                              */
/* Description       : Register used global string/vars                     */
/* Parameter         : Pointer to Module Structure                          */
/* ------------------------------------------------------------------------ */

static void RegisterStrVarGenerator(MODULE *ThisModule)
{
   MODULE_GENERATOR *ModuleInfo = ThisModule->ModuleParameters;
   UINT i = 0;

   for (i = 0; i < ThisModule->wNumOutChan; i++)
   {
      GlStr_RegisterByText(ModuleInfo->szChannelName[i], ThisModule, PerformAction_GENERATOR);

      if (ModuleInfo->nVarFrequency[i] > 0)
         GlVar_RegisterByNumber(ModuleInfo->nVarFrequency[i], ThisModule, PerformAction_GENERATOR);

      if (ModuleInfo->nVarAmplitude[i] > 0)
         GlVar_RegisterByNumber(ModuleInfo->nVarAmplitude[i], ThisModule, PerformAction_GENERATOR);
   }
}

/* ------------------------------------------------------------------------ */
/* Function Name     : UnregisterStrVarGenerator                            */
/* Description       : Unregister used global string/vars                   */
/* Parameter         : Pointer to Module Structure                          */
/* ------------------------------------------------------------------------ */

static void UnregisterStrVarGenerator(MODULE *ThisModule)
{
   MODULE_GENERATOR *ModuleInfo = ThisModule->ModuleParameters;
   UINT i = 0;

   for (i = 0; i < ThisModule->wNumOutChan; i++)
   {
      GlStr_UnregisterByText(ModuleInfo->szChannelName[i], ThisModule, PerformAction_GENERATOR);

      if (ModuleInfo->nVarFrequency[i] > 0)
         GlVar_UnregisterByNumber(ModuleInfo->nVarFrequency[i], ThisModule, PerformAction_GENERATOR);

      if (ModuleInfo->nVarAmplitude[i] > 0)
         GlVar_UnregisterByNumber(ModuleInfo->nVarAmplitude[i], ThisModule, PerformAction_GENERATOR);
   }
}

/* ------------------------------------------------------------------------ */
/* Function Name     : CheckVars                                            */
/* Description       : Set actual values of global vars to used variables   */
/* Parameter         : Pointer to Module Structure                          */
/* ------------------------------------------------------------------------ */

static void CheckVars(MODULE *ThisModule)
{
   MODULE_GENERATOR *ModuleInfo = ThisModule->ModuleParameters;
   UINT i = 0;

   for (i = 0; i < ThisModule->wNumOutChan; i++)
   {
      if (ModuleInfo->nVarFrequency[i] != 0)
         GlVar_Get(ModuleInfo->nVarFrequency[i], &ModuleInfo->fFrequency[i]);

      if (ModuleInfo->nVarAmplitude[i] != 0)
         GlVar_Get(ModuleInfo->nVarAmplitude[i], &ModuleInfo->fAmplitude[i]);
   }
}
static void __stdcall Timebase_Callback(EXT_TIMEBASE* timebase)
{

}

/* ************************************************************************ */
/* 1. Module functions                                                      */
/* ************************************************************************ */

/* ------------------------------------------------------------------------ */
/* Function Name     : Create_GENERATOR                                     */
/* Description       : Initializes private data structures of the module    */
/* Parameter         : Pointer to module structure                          */
/* ------------------------------------------------------------------------ */

static BOOL Create_GENERATOR(MODULE *ThisModule)
{
   MODULE_GENERATOR *ModuleInfo = ThisModule->ModuleParameters;
   CHANNEL_GENERATOR *KanalInfo;
   UINT i = 0;

   if (ThisModule->wNumInpChan == 0 && ThisModule->wNumOutChan == 0)
      ThisModule->wNumOutChan = 14;

   // Create and register a new timebase
   RegisterTimeBase("QuestFit", QF_TIMEBASE_ID, "QuestFit instrument timebase", &Timebase_Callback, TRUE);
   EXT_TIMEBASE qfTimebase ={
      .uiID = QF_TIMEBASE_ID,
      .bAutoBlockSize = FALSE,
      .uiBlockSize = QF_TIMEBASE_BLOCKSIZE,
      .nFreqFormat = ID_TIMEBASE_KHZ,
      .fSampleDistance = (1.0/2000.0),
      .wVarBlockSize = 0,
      .wVarSampleRate = 0,
   };
   SetTimeBase(&qfTimebase);
   SetTimeBaseTime(QF_TIMEBASE_ID, 0.0);
   ModuleInfo->uiTimeBase = QF_TIMEBASE_ID;

   for (i = 0; i < MAX_CHANNEL; i++)
   {
      strcpy(ModuleInfo->szUnit[i], "V");

      ModuleInfo->bRealTime[i] = TRUE;
      ModuleInfo->fFrequency[i] = (1 + i / 4) * 10.0;
      ModuleInfo->fAmplitude[i] = 4.0 * ONE_VOLT;
      // Copy Channel Name
      strcpy(ModuleInfo->szChannelName[i], IdString_GENERATOR);
      strcat(ModuleInfo->szChannelName[i], " ");
      switch (i)
      {
                  case 0:
                     strcat(ModuleInfo->szChannelName[i], "Fx12");
                     break;
                  case 1:
                     strcat(ModuleInfo->szChannelName[i], "Fx34");
                     break;
                  case 2:
                     strcat(ModuleInfo->szChannelName[i], "Fy14");
                     break;
                  case 3:
                     strcat(ModuleInfo->szChannelName[i], "Fy23");
                     break;
                  case 4:
                     strcat(ModuleInfo->szChannelName[i], "Fz1");
                     break;
                  case 5:
                     strcat(ModuleInfo->szChannelName[i], "Fz2");
                     break;
                  case 6:
                     strcat(ModuleInfo->szChannelName[i], "Fz3");
                     break;
                  case 7:
                     strcat(ModuleInfo->szChannelName[i], "Fz4");
                     break;
                  case 8:
                     strcat(ModuleInfo->szChannelName[i], "Fx");
                     break;
                  case 9:
                     strcat(ModuleInfo->szChannelName[i], "Fy");
                     break;
                  case 10:
                     strcat(ModuleInfo->szChannelName[i], "Fz");
                     break;
                  case 11:
                     strcat(ModuleInfo->szChannelName[i], "Mx");
                     break;
                  case 12:
                     strcat(ModuleInfo->szChannelName[i], "My");
                     break;
                  case 13:
                     strcat(ModuleInfo->szChannelName[i], "Mz");
                     break;
      }

      ModuleInfo->nVarFrequency[i] = 0;
      ModuleInfo->nVarAmplitude[i] = 0;

      KanalInfo = ThisModule->TempChannelData[i];
      KanalInfo->fPtDistance = 0.0;
      KanalInfo->fActPoint = 0.0;
      KanalInfo->bPeakDone = TRUE;
      KanalInfo->dwSample = 0;
   }

   return TRUE;
}

/* ------------------------------------------------------------------------ */
/* Function Name     : Load_GENERATOR                                       */
/* Description       : This function is called while loading a flowchart    */
/* Parameter         : Pointer to module structure                          */
/* ------------------------------------------------------------------------ */

static BOOL Load_GENERATOR(MODULE *ThisModule)
{
   RegisterStrVarGenerator(ThisModule);
   CheckVars(ThisModule);

   return TRUE;
}

/* ------------------------------------------------------------------------ */
/* Function Name     : Delete_GENERATOR                                     */
/* Description       : This function is called, if the flowchart is         */
/*                     deleted; it should release memory and GDI objects,   */
/*                     that are created in the Create_... function          */
/* Parameter         : Pointer to module structure                          */
/* ------------------------------------------------------------------------ */

static void Delete_GENERATOR(MODULE *ThisModule)
{
   UnregisterStrVarGenerator(ThisModule);
}

/* ------------------------------------------------------------------------ */
/* Function Name     : Save_GENERATOR                                       */
/* Description       : This function is called while saving a flowchart.    */
/* Parameter         : Pointer to module structure                          */
/* ------------------------------------------------------------------------ */

static void Save_GENERATOR(MODULE *ThisModule)
{
   UNUSED(ThisModule);
}

/* ------------------------------------------------------------------------ */
/* Function Name     : CreateReplace_GENERATOR                              */
/* Description       : This Function is called, once the User has selected  */
/*                     this module to be replaced by another one. Module    */
/*                     parameters will be copied to a Replace Template.     */
/* Parameter         : Pointer to the Module, Pointer to Replace Template   */
/* ------------------------------------------------------------------------ */

static BOOL CreateReplace_GENERATOR(MODULE *ThisModule, MODULE *ReplaceTemplate)
{
   MODULE_GENERATOR *ModuleInfo = ThisModule->ModuleParameters;
   MODULE_DATA_TEMPLATE *TemplateInfo = ReplaceTemplate->ModuleParameters;
   UINT i = 0;

   // Copy parameters to Replace Template
   for (i = 0; i < MAX_CHANNEL; i++)
   {
      strncpy(TemplateInfo->szChannelName[i], ModuleInfo->szChannelName[i], 24);
      strncpy(TemplateInfo->szUnit[i], ModuleInfo->szUnit[i], MAX_UNIT_LEN);
   }

   // Set validity indicators in Replace Template
   TemplateInfo->bChannelNamesUsed = TRUE;
   TemplateInfo->bUnitsUsed = TRUE;

   return TRUE;
}

/* ------------------------------------------------------------------------ */
/* Function Name     : CheckReplace_GENERATOR                               */
/* Description       : This Function is called, once the User has selected  */
/*                     this module to be replaced by another one. Module    */
/*                     parameters will be copied to a Replace Template.     */
/* Parameter         : Pointer to Replace Template                          */
/* ------------------------------------------------------------------------ */

static BOOL CheckReplace_GENERATOR(MODULE *ReplaceTemplate)
{
   // No chance if inputs or no outputs
   if (ReplaceTemplate->wNumInpChan > 0 || ReplaceTemplate->wNumOutChan == 0)
      return FALSE;

   // Otherwise we're fine
   return TRUE;
}

/* ------------------------------------------------------------------------ */
/* Function Name     : Replace_GENERATOR                                    */
/* Description       : This Function is called, once the User has selected  */
/*                     this module to replace another one. Parameters will  */
/*                     be taken from the Replace Template.                  */
/* Parameter         : Pointer to the Module, Pointer to Replace Template   */
/* ------------------------------------------------------------------------ */

static BOOL Replace_GENERATOR(MODULE *ThisModule, MODULE *ReplaceTemplate)
{
   MODULE_GENERATOR *ModuleInfo = ThisModule->ModuleParameters;
   MODULE_DATA_TEMPLATE *TemplateInfo = ReplaceTemplate->ModuleParameters;
   UINT i = 0;

   // First setup default data for the new module
   Create_GENERATOR(ThisModule);

   // Set correct channel relation (source module might be different)
   ThisModule->ChannelRelation = KZ_NORMAL;

   // Copy valid data from Replace Template
   if (TemplateInfo->bChannelNamesUsed)
   {
      for (i = 0; i < MAX_CHANNEL; i++)
         strncpy(ModuleInfo->szChannelName[i], TemplateInfo->szChannelName[i], 24);
   }

   if (TemplateInfo->bUnitsUsed)
   {
      for (i = 0; i < MAX_CHANNEL; i++)
         strncpy(ModuleInfo->szUnit[i], TemplateInfo->szUnit[i], MAX_UNIT_LEN);
   }

   return TRUE;
}

/* ------------------------------------------------------------------------ */
/* Function Name     : RequestGlobalVars_GENERATOR                          */
/* Description       : The Variable-Overview asks for the used              */
/*                     variables in this module. Here we have               */
/*                     to answer.                                           */
/* Parameter         : Pointer to the Module,                                */
/*                     handle of Global Variables Overview                  */
/* ------------------------------------------------------------------------ */

BOOL RequestGlobalVars_GENERATOR(MODULE *ThisModule, LPARAM pHandle)
{
   GLVO_MODULE_NOTIFY_PARAM Param;
   MODULE_GENERATOR *ModuleInfo = ThisModule->ModuleParameters;
   UINT i = 0;

   Param.wSize = sizeof(GLVO_MODULE_NOTIFY_PARAM);
   Param.uiVersion = GLVO_VERSION;
   Param.pHandle = pHandle;

   Param.wVarType = GLVO_VARTYPE_NUMBER;
   Param.wAccess = GLVO_ACCESS_READ;
   Param.bAction = FALSE;
   Param.wActionNumber = 0;

   for (i = 0; i < ThisModule->wNumOutChan; i++)
   {
      // Frequency
      LoadString(hInst, STR_FREQUENZ, Param.szDescription, sizeof(Param.szDescription));

      if (ModuleInfo->nVarFrequency[i] == 0)
      {
         // Set proper parameters in order to show that we do not
         // use a variable here
         Param.wVarUsage = GLVO_VARUSAGE_NOT_YET;
         Param.wVarNumber = 0;
         Param.iChannelNumber = -1;
         strcpy(Param.szDescription, "---");
      }
      else
      {
         Param.wVarUsage = GLVO_VARUSAGE_USED;
         Param.wVarNumber = (short)ModuleInfo->nVarFrequency[i];
         Param.iChannelNumber = i;
      }

      GlvoModuleNotifyGlobalVar(&Param);

      // Amplitude
      LoadString(hInst, STR_AMPLITUDE, Param.szDescription, sizeof(Param.szDescription));

      if (ModuleInfo->nVarAmplitude[i] == 0)
      {
         // Set proper parameters in order to show that we do not
         // use a variable here
         Param.wVarUsage = GLVO_VARUSAGE_NOT_YET;
         Param.wVarNumber = 0;
         Param.iChannelNumber = -1;
         strcpy(Param.szDescription, "---");
      }
      else
      {
         Param.wVarUsage = GLVO_VARUSAGE_USED;
         Param.wVarNumber = (short)ModuleInfo->nVarAmplitude[i];
         Param.iChannelNumber = i;
      }

      GlvoModuleNotifyGlobalVar(&Param);
   }

   // return true in order to show that we processed the
   // message DMM_REQUEST_GLOB_VARS
   return TRUE;
}

/* ------------------------------------------------------------------------ */
/* Function Name     : Start_GENERATOR                                      */
/* Description       : This function is called, if the user has started the */
/*                     experiment; you can perform some "First Time"        */
/*                     routines                                             */
/* Parameter         : Pointer to module structure                          */
/* ------------------------------------------------------------------------ */

static BOOL Start_GENERATOR(MODULE *ThisModule)
{
   CHANNEL_GENERATOR *KanalInfo;
   MODULE_GENERATOR *ModuleInfo = ThisModule->ModuleParameters;
   UINT wFifoNr = 0;
   BOOL bRateOK = FALSE;
   // Send the mV/V data to the FPE

   for (wFifoNr = 0; wFifoNr < ThisModule->wNumOutChan; wFifoNr++)
   {
      KanalInfo = ThisModule->TempChannelData[wFifoNr];
      KanalInfo->fPtDistance = 0.0;
      KanalInfo->fActPoint = 0.0;
      KanalInfo->bPeakDone = TRUE;
      KanalInfo->dwSample = 0;
      KanalInfo->bComputing = FALSE;
   }
   double sampleDistance = GetTimeBaseSampleDistance(ModuleInfo->uiTimeBase);

   QuestFitCalibrationRig_StartCapture(1.0/sampleDistance);
   UnregisterStrVarGenerator(ThisModule);
   RegisterStrVarGenerator(ThisModule);
   CheckVars(ThisModule);

   Compute_GENERATOR(ThisModule);

   bRateOK = TRUE;

   for (wFifoNr = 0; wFifoNr < ThisModule->wNumOutChan; wFifoNr++)
   {
      KanalInfo = ThisModule->TempChannelData[wFifoNr];

      if (KanalInfo->fPtDistance > 0.9 * M_PI)
         bRateOK = FALSE;
   }

   if (bRateOK == FALSE)
   {
      LoadString(hInst, STR_GENU_FAST, LongTempString, sizeof(LongTempString));
      ShowWarning(ThisModule->ModuleName, LongTempString);
   }

   return TRUE;
}

/* ------------------------------------------------------------------------ */
/* Function Name     : SetupFifo_GENERATOR                                  */
/* Description       : This function is called for each output of a module  */
/*                     to perform the structure test of DASYLab; this has   */
/*                     to be done very carefully                            */
/* Parameter         : Pointer to Module, Number of the FIFO                */
/* ------------------------------------------------------------------------ */

static BOOL SetupFifo_GENERATOR(MODULE *ThisModule, UINT wFifoNr)
{
   MODULE_GENERATOR *ModuleInfo = ThisModule->ModuleParameters;
   VAR_GENERATOR *PrivatVars = ThisModule->TempModuleData;
   FIFO_HEADER *ThisFifo = ThisModule->Fifo[wFifoNr];

   ThisFifo->uiMaxBlockSize = PrivatVars->uiBlockSize = GetTimeBaseBlockSize(ModuleInfo->uiTimeBase);
   ThisFifo->fSampleDistance = PrivatVars->fSampleDistance = GetTimeBaseSampleDistance(ModuleInfo->uiTimeBase);

   return TRUE;
}

/* ------------------------------------------------------------------------ */
/* Function Name     : ProcessData_GENERATOR                                */
/* Description       : Data processing                                      */
/* Parameter         : Pointer to module                                    */
/* ------------------------------------------------------------------------ */

static int ProcessData_GENERATOR(MODULE *ThisModule)
{
   MODULE_GENERATOR *ModuleInfo = ThisModule->ModuleParameters;
   VAR_GENERATOR *PrivatVars = ThisModule->TempModuleData;
   CHANNEL_GENERATOR *KanalInfo;
   DATA_BLOCK_HEADER *OutputBlock;
   FIFO_HEADER *OutFifo;
   UINT i = 0;
   UINT wFifoNr = 0;
   UINT madeUpSampleCount = 0;

   // If there's no module to use our data we don't have to process it
   if (!ThisModule->bModuleIsConnected)
      return FALSE;

   // Get a block's worth of data from the QuestFit SDK
   size_t samplesRetrieved = 0;
   QuestFitCalibrationSampleInterface_t *inputSamples = malloc((100+PrivatVars->uiBlockSize) * sizeof(QuestFitCalibrationSampleInterface_t));
   if (QuestFitCalibrationRig_GetSamples(PrivatVars->uiBlockSize, inputSamples, &samplesRetrieved) != QFCR_OK)
   {
      free(inputSamples);
      return FALSE;
   }
   if (samplesRetrieved == 0)
   {
      free(inputSamples);
      return FALSE;
   }
   // One FIFO after the other
   for (wFifoNr = 0; wFifoNr < ThisModule->wNumOutChan; wFifoNr++)
   {
      OutFifo = ThisModule->Fifo[wFifoNr];
      KanalInfo = ThisModule->TempChannelData[wFifoNr];

      // Are we still processing ?
      if (KanalInfo->bComputing != TRUE)
      {
         if ((OutputBlock = GetCurrentOutputBlock(OutFifo)) != NULL)
         {
            // Set time information
            OutputBlock->fStartTime = KanalInfo->dwSample * PrivatVars->fSampleDistance;
            OutputBlock->fSampleDistance = PrivatVars->fSampleDistance;
            OutputBlock->uiBlockSize = PrivatVars->uiBlockSize;

            // Release time for this block
            KanalInfo->fReleaseTime = OutputBlock->fStartTime + OutputBlock->uiBlockSize * OutputBlock->fSampleDistance;

            for (i = 0; i < OutputBlock->uiBlockSize; i++)
            {
               float currentSampleComponent;
               if (i >= samplesRetrieved)
               {
                  currentSampleComponent = 0; // Fill with zeros if we don't have enough data
                  madeUpSampleCount++;
               }
               else
               {

                  switch (wFifoNr)
                  {
                  case 0:
                     currentSampleComponent = inputSamples[i].Fx12;
                     break;
                  case 1:
                     currentSampleComponent = inputSamples[i].Fx34;
                     break;
                  case 2:
                     currentSampleComponent = inputSamples[i].Fy14;
                     break;
                  case 3:
                     currentSampleComponent = inputSamples[i].Fy23;
                     break;
                  case 4:
                     currentSampleComponent = inputSamples[i].Fz1;
                     break;
                  case 5:
                     currentSampleComponent = inputSamples[i].Fz2;
                     break;
                  case 6:
                     currentSampleComponent = inputSamples[i].Fz3;
                     break;
                  case 7:
                     currentSampleComponent = inputSamples[i].Fz4;
                     break;
                  case 8:
                     currentSampleComponent = inputSamples[i].Fx;
                     break;
                  case 9:
                     currentSampleComponent = inputSamples[i].Fy;
                     break;
                  case 10:
                     currentSampleComponent = inputSamples[i].Fz;
                     break;
                  case 11:
                     currentSampleComponent = inputSamples[i].Mx;
                     break;
                  case 12:
                     currentSampleComponent = inputSamples[i].My;
                     break;
                  case 13:
                     currentSampleComponent = inputSamples[i].Mz;
                     break;
                  default:
                     currentSampleComponent = 0;
                     break;
                  }
               }
               OutputBlock->Data[i] = currentSampleComponent;
            }
            KanalInfo->bComputing = TRUE;
            KanalInfo->dwSample += OutputBlock->uiBlockSize;
            SetTimeBaseTime(QF_TIMEBASE_ID, KanalInfo->fReleaseTime);
         }
      }

      // If release time greater than actual experiment time or there's no real time output for this FIFO: Release block.
      if ((KanalInfo->bComputing == TRUE) && (bExperimentIsPaused == FALSE) &&
          ((ModuleInfo->bRealTime[wFifoNr] == FALSE) || (GetTimeBaseTime(ModuleInfo->uiTimeBase) >= KanalInfo->fReleaseTime)))
      {
         // TK14 - since we have no input, there is no need to process extra memory - in later versions of the toolkit
         //        we might add some code for adding additional data here.
         ReleaseOutputBlock(OutFifo);
         KanalInfo->bComputing = FALSE;
      }
   }
   free(inputSamples);

   return TRUE;
}

/* ------------------------------------------------------------------------ */
/* Function Name     : Stop_GENERATOR                                       */
/* Description       : This function is called when the user stops the      */
/*                     experiment                                           */
/* Parameter         : Pointer to Module                                    */
/* ------------------------------------------------------------------------ */

static BOOL Stop_GENERATOR(MODULE *ThisModule)
{
   UNUSED(ThisModule);
   QuestFitCalibrationRig_StopCapture();

   return TRUE;
}

/* ************************************************************************ */
/* 2. Dialog box handling                                                   */
/* ************************************************************************ */

/* ------------------------------------------------------------------------ */
/* Function Name     : DisplayChannel                                       */
/* Description       : This function displays the data for one channel in   */
/*                     the dialog box                                       */
/* Parameter         : Handle of dialog box, number of channel to display   */
/* ------------------------------------------------------------------------ */

static void DisplayChannel(HWND hDlg, UINT wNummer)
{
   MODULE_GENERATOR *TempInfo = SingleInfo;

   FillUnitList(hDlg, ID_LIST_UNIT, TempInfo->szUnit[wNummer]);

   SetDlgItemText(hDlg, IDD_KANAL_NAME, TempInfo->szChannelName[wNummer]);

   CheckRadioButton(hDlg, IDD_GEN_SINE, IDD_GEN_SAWTOOTH, IDD_GEN_SINE + TempInfo->wFunction[wNummer]);

   if (TempInfo->nVarFrequency[wNummer] == 0)
      chg_float(ShortTempString, TempInfo->fFrequency[wNummer], -4);
   else
      GlVar_SetSyntax(ShortTempString, TempInfo->nVarFrequency[wNummer]);

   SetDlgItemText(hDlg, IDD_GEN_FREQ, ShortTempString);

   if (TempInfo->nVarAmplitude[wNummer] == 0)
      chg_float(ShortTempString, TempInfo->fAmplitude[wNummer], -4);
   else
      GlVar_SetSyntax(ShortTempString, TempInfo->nVarAmplitude[wNummer]);

   SetDlgItemText(hDlg, IDD_GEN_AMPL, ShortTempString);

   CheckDlgButton(hDlg, IDD_GEN_REALTIME, TempInfo->bRealTime[wNummer]);
}

/* ------------------------------------------------------------------------ */
/* Function Name     : RetrieveChannel                                      */
/* Description       : This function retrieves the data for one channel in  */
/*                     the dialog box                                       */
/* Parameter         : Handle of dialog box, number of channel to display   */
/* ------------------------------------------------------------------------ */

static void RetrieveChannel(HWND hDlg, UINT wNummer)
{
   MODULE_GENERATOR *TempInfo = SingleInfo;
   short VarNummer = 0;

   GetDlgItemText(hDlg, IDD_KANAL_NAME, TempInfo->szChannelName[wNummer], CHANNEL_NAME_LENGTH);

   ComboBox_GetText(GetDlgItem(hDlg, ID_LIST_UNIT), TempInfo->szUnit[wNummer], MAX_UNIT_LEN);

   GetDlgItemText(hDlg, IDD_GEN_FREQ, ShortTempString, 24);

   if (ExpandVarNumber(ShortTempString, 24, &VarNummer))
   {
      TempInfo->nVarFrequency[wNummer] = VarNummer;
   }
   else
   {
      TempInfo->fFrequency[wNummer] = atof(ShortTempString);
      TempInfo->nVarFrequency[wNummer] = 0;
   }

   GetDlgItemText(hDlg, IDD_GEN_AMPL, ShortTempString, 24);

   if (ExpandVarNumber(ShortTempString, 24, &VarNummer))
   {
      TempInfo->nVarAmplitude[wNummer] = VarNummer;
   }
   else
   {
      TempInfo->fAmplitude[wNummer] = atof(ShortTempString);
      TempInfo->nVarAmplitude[wNummer] = 0;
   }
}

/* ------------------------------------------------------------------------ */
/* Function Name     : GeneratorProc                                        */
/* Description       : Dialog box function for this dialog box. This        */
/*                     function has to be exported and should not be static */
/* Parameter         : Standard for dialog functions or Window functions    */
/* ------------------------------------------------------------------------ */

BOOL CALLBACK GeneratorProc(HWND hDlg, UINT Message, WPARAM wParam, LPARAM lParam)
{
   MODULE *ThisModule = CurrentModulePtr;
   MODULE_GENERATOR *TempInfo = SingleInfo;

   switch (Message)
   {
   case WM_INITDIALOG:
   {
      // Allocate memory for temporary data
      SingleInfo = MemAlloc(sizeof(MODULE_GENERATOR));

      if (!SingleInfo)
      {
         EndDialog(hDlg, FALSE);
         return TRUE;
      }

      TempInfo = SingleInfo;

      // Copy module parameters to the temporary structure
      memcpy(TempInfo, ThisModule->ModuleParameters, sizeof(MODULE_GENERATOR));

      // Set number of in-/outputs
      wDialNumChan = ThisModule->wNumOutChan;
      wDialCurChan = 0;
      wDialMaxChan = 16;

      // Set popup menu for global variables
      SetMenuForGlobalStrings(hDlg, IDD_KANAL_NAME);
      SetMenuForGlobalVars(hDlg, IDD_GEN_FREQ);
      SetMenuForGlobalVars(hDlg, IDD_GEN_AMPL);

      InitChannelBar(hDlg);

      // Fill time base combo box
      FillTimeBaseCombo(hDlg, IDD_GEN_TIMEBASE, TempInfo->uiTimeBase);
      EnableWindow(GetDlgItem(hDlg, IDD_GEN_TIMEBASE), !bExperimentIsRunning);

      // Limit some edit boxes
      Edit_LimitText(GetDlgItem(hDlg, IDD_KANAL_NAME), CHANNEL_NAME_LENGTH);
      Edit_LimitText(GetDlgItem(hDlg, IDD_MODUL_NAME), MODULE_NAME_LENGTH);
      Edit_LimitText(GetDlgItem(hDlg, IDD_MODUL_BEZEICHNUNG), MODULE_DESCRIPTION_LENGTH);

      SetDlgItemText(hDlg, IDD_MODUL_NAME, ThisModule->ModuleName);
      SetDlgItemText(hDlg, IDD_MODUL_BEZEICHNUNG, ThisModule->ModuleDescription);

      DisplayChannel(hDlg, wDialCurChan);
      SetFocus(GetDlgItem(hDlg, IDD_MODUL_NAME));
      wDialLastFocus = 0;

      return (FALSE);
   }
   break;

   case WM_CLICK_LDOWN:
   {
      // A new channel was selected
      if (LOWORD(lParam) == 2)
      {
         RetrieveChannel(hDlg, wDialCurChan);
         HandleChannelClick(hDlg, wParam);
         DisplayChannel(hDlg, wDialCurChan);
      }

      wDialLastFocus = IDD_KAN00;
      SetFocus(GetDlgItem(hDlg, IDD_KAN00));
      return TRUE;
   }
   break;

   case WM_COPYFOCUS: // F7 Key
   {
      UINT i = 0;

      // Get actual values
      RetrieveChannel(hDlg, wDialCurChan);
      DisplayChannel(hDlg, wDialCurChan);

      // Check last focus and copy
      for (i = 0; i < wDialNumChan; i++)
      {
         if (i != wDialCurChan)
         {
            switch (wDialLastFocus)
            {
            case IDD_KANAL_NAME:
               strcpy(TempInfo->szChannelName[i], TempInfo->szChannelName[wDialCurChan]);
               break;

            case IDD_GEN_FREQ:
               TempInfo->fFrequency[i] = TempInfo->fFrequency[wDialCurChan];
               break;

            case IDD_GEN_AMPL:
               TempInfo->fAmplitude[i] = TempInfo->fAmplitude[wDialCurChan];
               break;

            case IDD_GEN_SINE:
            case IDD_GEN_RECT:
            case IDD_GEN_PULSE:
            case IDD_GEN_TRIANGULAR:
            case IDD_GEN_SAWTOOTH:
               TempInfo->wFunction[i] = TempInfo->wFunction[wDialCurChan];
               break;

            case IDD_GEN_REALTIME:
               TempInfo->bRealTime[i] = TempInfo->bRealTime[wDialCurChan];
               break;

            case ID_LIST_UNIT:
               strcpy(TempInfo->szUnit[i], TempInfo->szUnit[wDialCurChan]);
               break;
            }
         }
      }
   }
   break;

   case WM_COPYALL: // F8 Key
   {
      UINT i = 0;

      // Get actual values
      RetrieveChannel(hDlg, wDialCurChan);
      DisplayChannel(hDlg, wDialCurChan);

      for (i = 0; i < wDialNumChan; i++)
      {
         if (i != wDialCurChan)
         {
            strcpy(TempInfo->szChannelName[i], TempInfo->szChannelName[wDialCurChan]);
            TempInfo->fFrequency[i] = TempInfo->fFrequency[wDialCurChan];
            TempInfo->fAmplitude[i] = TempInfo->fAmplitude[wDialCurChan];
            TempInfo->wFunction[i] = TempInfo->wFunction[wDialCurChan];
            TempInfo->bRealTime[i] = TempInfo->bRealTime[wDialCurChan];
            strcpy(TempInfo->szUnit[i], TempInfo->szUnit[wDialCurChan]);
         }
      }
   }
   break;

   case WM_COMMAND:
   {
      UINT cmd_id = GET_WM_COMMAND_ID(wParam, lParam);
      UINT cmd_cmd = GET_WM_COMMAND_CMD(wParam, lParam);

      switch (cmd_id)
      {
      case IDD_LESS:
      {
         // One channel less
         RetrieveChannel(hDlg, wDialCurChan);
         HandleLessMoreButton(hDlg, IDD_LESS);
         DisplayChannel(hDlg, wDialCurChan);
         wDialLastFocus = IDD_KAN00;
         SetFocus(GetDlgItem(hDlg, IDD_KAN00));
         return TRUE;
      }
      break;

      case IDD_MORE:
      {
         // One more channel
         RetrieveChannel(hDlg, wDialCurChan);
         HandleLessMoreButton(hDlg, IDD_MORE);
         DisplayChannel(hDlg, wDialCurChan);
         wDialLastFocus = IDD_KAN00;
         SetFocus(GetDlgItem(hDlg, IDD_KAN00));
         return TRUE;
      }
      break;

      case ID_LIST_UNIT:
         if (cmd_cmd == CBN_SETFOCUS)
         {
            wDialLastFocus = cmd_id;
         }

         if (cmd_cmd == CBN_KILLFOCUS)
         {
            RetrieveChannel(hDlg, wDialCurChan);
            DisplayChannel(hDlg, wDialCurChan);
         }

         break;

      case IDD_GEN_SINE:
      case IDD_GEN_RECT:
      case IDD_GEN_PULSE:
      case IDD_GEN_TRIANGULAR:
      case IDD_GEN_SAWTOOTH:
      {
         RetrieveChannel(hDlg, wDialCurChan);
         TempInfo->wFunction[wDialCurChan] = (WORD)(wParam - IDD_GEN_SINE);
         wDialLastFocus = cmd_id;
         DisplayChannel(hDlg, wDialCurChan);
         return TRUE;
      }
      break;

      case IDD_GEN_REALTIME:
      {
         TempInfo->bRealTime[wDialCurChan] = 1 - TempInfo->bRealTime[wDialCurChan];
         wDialLastFocus = IDD_GEN_REALTIME;
         return TRUE;
      }
      break;

      case IDD_GEN_TIMEBASE:
      {
         if (cmd_cmd == CBN_SETFOCUS)
         {
            wDialLastFocus = IDD_GEN_TIMEBASE;
         }

         if (cmd_cmd == CBN_SELCHANGE)
         {
            TempInfo->uiTimeBase = GetTimeBaseComboID(ComboBox_GetCurSel(GetDlgItem(hDlg, IDD_GEN_TIMEBASE)));
         }

         return TRUE;
      }
      break;

      case IDD_KANAL_NAME:
      case IDD_GEN_FREQ:
      case IDD_GEN_AMPL:
      case IDD_MODUL_NAME:
      case IDD_MODUL_BEZEICHNUNG:
      {
         if (cmd_cmd == EN_SETFOCUS)
            wDialLastFocus = cmd_id;
         return FALSE;
      }
      break;

      case IDHELP:
      {
         UINT wHelpID = MODULNAME;

         LoadString(hInstDlab, ID_EVAHILFE, ShortTempString, sizeof(ShortTempString));
         strcpy(LongTempString, ExeFileDir);
         strcat(LongTempString, ShortTempString);

         // Load help file with the parameter of the last focus
         switch (wDialLastFocus)
         {
         case IDD_MODUL_NAME:
            wHelpID = MODULNAME;
            break;

         case IDD_MODUL_BEZEICHNUNG:
            wHelpID = MODULBESCHREIB;
            break;

         case IDD_KAN00:
            wHelpID = GL_KANALANZ;
            break;

         case IDD_KANAL_NAME:
            wHelpID = KBEZEICHNUNG;
            break;

         case ID_LIST_UNIT:
            wHelpID = KEINHEIT;
            break;

         default:
            /*
                     !!!! Here your help file should be used !!!!
                     LoadString ( hInst, ID_YOUR_HELP, ShortTempString, sizeof(ShortTempString) );
                     wHelpID = YOUR_HELP_ID;
                     */
            break;
         }

         /*
               HtmlHelp (NULL, LongTempString, HH_HELP_CONTEXT, wHelpID);
               */

         wDialLastFocus = 0;
         return TRUE;
      }
      break;

      case IDOK:
      {
         SetFocus(GetDlgItem(hDlg, IDOK));

         RetrieveChannel(hDlg, wDialCurChan);

         ThisModule = CurrentModulePtr;

         GetDlgItemText(hDlg, IDD_MODUL_NAME, ShortTempString, MODULE_NAME_LENGTH + 1);
         ChangeModuleName(ThisModule, ShortTempString);

         GetDlgItemText(hDlg, IDD_MODUL_BEZEICHNUNG, ThisModule->ModuleDescription, MODULE_DESCRIPTION_LENGTH + 1);

         UnregisterStrVarGenerator(ThisModule);

         // Copy temporary data to the module parameters
         memcpy(ThisModule->ModuleParameters, TempInfo, sizeof(MODULE_GENERATOR));

         ChangeModuleSize(ThisModule, 0, wDialNumChan);

         RegisterStrVarGenerator(ThisModule);

         // Free memory for temporary data
         MemFree(SingleInfo);
         SingleInfo = NULL;

         EndDialog(hDlg, TRUE);
         return TRUE;
      }
      break;

      case IDCANCEL:
      {
         SetFocus(GetDlgItem(hDlg, IDCANCEL));

         // Free memory for temporary data
         MemFree(SingleInfo);
         SingleInfo = NULL;

         EndDialog(hDlg, FALSE);
         return TRUE;
      }
      break;
      }
   }
   break;
   }

   return FALSE;
}

/* ------------------------------------------------------------------------ */
/* Function Name     : Param_GENERATOR                                      */
/* Description       : Process the dialog box for this module               */
/* Parameter         : Pointer to the module structure                      */
/* ------------------------------------------------------------------------ */

static void Param_GENERATOR(MODULE *ThisModule)
{
   HWND hwnd = ThisModule->hwndModule;
   BOOL bDoit = FALSE;

   bDoit = DialogBox(hInst, "GENERATOR", hwnd, (DLGPROC)GeneratorProc);

   if (bDoit)
      Compute_GENERATOR(ThisModule);
}

/* ************************************************************************ */
/* 3. Action handling                                                       */
/* ************************************************************************ */

/* ------------------------------------------------------------------------ */
/* Function Name     : ActionQuery_GENERATOR                                */
/* Description       : Check if we can process specific events.             */
/* ------------------------------------------------------------------------ */

static BOOL ActionQuery_GENERATOR(MODULE *ThisModule, int wAction, int wChannel, ONE_ACTION *Action)
{
   switch (Action->Number)
   {
   case ACTION_NULL:
   case ACTION_SET_FREQ:
   case ACTION_SET_AMPLITUDE:
      return TRUE;

   default:
      break;
   }

   UNUSED(ThisModule);
   UNUSED(wAction);
   UNUSED(wChannel);

   return FALSE;
}

/* ------------------------------------------------------------------------ */
/* Function Name     : ExplainAction_GENERATOR                              */
/* Description       : Set action parameters                                */
/* ------------------------------------------------------------------------ */

static BOOL ExplainAction_GENERATOR(MODULE *ThisModule, int wAction, int wChannel, ACTION_DESCRIPTION *Acd)
{
   switch (Acd->Number)
   {
   case ACTION_SET_FREQ:
      Acd->hInst = hInst;
      strcpy(Acd->InternalName, "GEN_SET_FREQ");
      Acd->Params = ACTION_1_PARAMS;
      Acd->IdName = STR_ACTION_SET_FREQ;
      Acd->IdParams[0] = STR_FREQUENZ;
      Acd->ParamType[0] = ACTION_PARAM_TYPE_DOUBLE;
      return TRUE;

   case ACTION_SET_AMPLITUDE:
      Acd->hInst = hInst;
      strcpy(Acd->InternalName, "GEN_SET_AMPL");
      Acd->Params = ACTION_1_PARAMS;
      Acd->IdName = STR_ACTION_SET_AMPLITUDE;
      Acd->IdParams[0] = STR_AMPLITUDE;
      Acd->ParamType[0] = ACTION_PARAM_TYPE_DOUBLE;
      return TRUE;

   default:
      break;
   }

   UNUSED(ThisModule);
   UNUSED(wAction);
   UNUSED(wChannel);

   return FALSE;
}

/* ------------------------------------------------------------------------ */
/* Function Name     : Action_GENERATOR                                     */
/* Description       : Here we process incoming events.                     */
/* ------------------------------------------------------------------------ */

static BOOL Action_GENERATOR(MODULE *ThisModule, int wAction, int wChannel, ONE_ACTION *Action)
{
   MODULE_GENERATOR *ModuleInfo = ThisModule->ModuleParameters;
   UINT i = 0;

   switch (wAction)
   {
   // Asynchronous action
   case DMM_MODULE_ACTION:
   {
      // All channels ?
      if (wChannel == 0)
         wChannel = -1;

      for (i = 0; i < ThisModule->wNumOutChan; i++)
      {
         if (wChannel & (1L << i))
         {
            switch (Action->Number)
            {
            case ACTION_SET_FREQ:
            {
               // MX_EK 27.05.2015 ToDo: fester Zahlenwert 1E-300 als Vergleichswert gr��er als Null
               if (Action->fParam[0] > 1E-300)
                  ModuleInfo->fFrequency[i] = Action->fParam[0];
            }
            break;

            case ACTION_SET_AMPLITUDE:
            {
               ModuleInfo->fAmplitude[i] = Action->fParam[0];
            }
            break;

            default:
               return FALSE;
            }
         }
      }

      Compute_GENERATOR(ThisModule);
   }

      return TRUE;

   default:
      break;
   }

   return TRUE;
}

/* ------------------------------------------------------------------------ */
/* Function Name     : Exit_GENERATOR                                       */
/* Description       : Here we destroy things, that we initialized in the   */
/*                     Init_... function; especially WindowClasses. This is */
/*                     only necessary very seldom. This Function is called  */
/*                     when the Program is unloaded                         */
/* Parameter         : ---                                                  */
/* ------------------------------------------------------------------------ */

static void Exit_GENERATOR(void)
{
   QuestFitCalibrationRig_Destroy();
}

/* ************************************************************************ */
/* 4. DASYLab message handling                                              */
/* ************************************************************************ */

/* ------------------------------------------------------------------------ */
/* Function Name     : PerformAction_GENERATOR                              */
/* ------------------------------------------------------------------------ */

unsigned long PerformAction_GENERATOR(MODULE *ThisModule, int wMsg, int wParam, long lParam)
{
   switch (wMsg)
   {
   // DASYLab Class Messages
   case DQM_UNREGISTER_CLASS:
      Exit_GENERATOR();
      return TRUE;

   case DQM_CHECK_REPLACE:
      return CheckReplace_GENERATOR((MODULE *)lParam);

      // DASYLab Module Messages
   case DMM_CREATE_MODULE:
      return Create_GENERATOR(ThisModule);

   case DMM_DELETE_MODULE:
      Delete_GENERATOR(ThisModule);
      return TRUE;

   case DMM_PARAM_MODULE:
      Param_GENERATOR(ThisModule);
      return TRUE;

   case DMM_SAVE_MODULE:
      Save_GENERATOR(ThisModule);
      return TRUE;

   case DMM_LOAD_MODULE:
      return Load_GENERATOR(ThisModule);

   case DMM_START_MODULE:
      return Start_GENERATOR(ThisModule);

   case DMM_STOP_MODULE:
      return Stop_GENERATOR(ThisModule);

   case DMM_QUERY_MODULE_ACTION:
      return ActionQuery_GENERATOR(ThisModule, wMsg, wParam, (ONE_ACTION *)lParam);

   case DMM_MODULE_ACTION:
      return Action_GENERATOR(ThisModule, wMsg, wParam, (ONE_ACTION *)lParam);

   case DMM_EXPLAIN_USER_ACTION:
      return ExplainAction_GENERATOR(ThisModule, wMsg, wParam, (ACTION_DESCRIPTION *)lParam);

   case DMM_GLOBAL_STRING_CHANGED:
   case DMM_GLOBAL_VAR_CHANGED:
   {
      CheckVars(ThisModule);
      Compute_GENERATOR(ThisModule);
   }
   break;

   case DCM_SETUP_FIFO:
      return SetupFifo_GENERATOR(ThisModule, wParam);

   case DMM_COPY_CHANNEL_NAME:
   {
      MODULE_GENERATOR *ModuleInfo = ThisModule->ModuleParameters;
      UINT i = 0;

      for (i = 0; i < ThisModule->wNumOutChan; i++)
      {
         CopyChannelName(ThisModule->Fifo[i], (LPSTR *)ModuleInfo->szChannelName[i]);
      }
   }
   break;

   case DCM_GET_UNIT:
   {
      MODULE_GENERATOR *ModuleInfo = ThisModule->ModuleParameters;

      return (long)ModuleInfo->szUnit[wParam];
   }
   break;

   case DMM_GET_PARAMETERS_INFO:
      return (long)ParameterGenerator;

   case DMM_CREATE_REPLACE:
      return CreateReplace_GENERATOR(ThisModule, (MODULE *)lParam);

   case DMM_REPLACE_MODULE:
      return Replace_GENERATOR(ThisModule, (MODULE *)lParam);

   case DMM_REQUEST_GLOB_VARS:
      return RequestGlobalVars_GENERATOR(ThisModule, lParam);

   case DMM_REQ_MODULE_DEFAULT:
      return TRUE;

   case DMM_IS_DEBUG:
#ifdef _DEBUG
      return 2;
#else
      return TRUE;
#endif

   case DMM_GET_TIMEBASE_ID:
      return ((MODULE_GENERATOR *)ThisModule->ModuleParameters)->uiTimeBase;

   default:
      break;
   }

   return PerformDefaultAction(ThisModule, wMsg, wParam, lParam);
}

/* ------------------------------------------------------------------------ */
/* Function Name     : FillTkDllsMenu_GENERATOR                             */
/* Description       : Insert a MenuItem in the DASYLab main menu           */
/* Remark            : For possible values look at the description for the  */
/*                     Function "ExpandModuleBar ( void )".                 */
/* ------------------------------------------------------------------------ */

BOOL FillTkDllsMenu_GENERATOR(UINT uiMenuId)
{
   DASYLAB_INSERT_MENU DlabMenuStruct;

   strcpy(DlabMenuStruct.szMainMenuEntry, "MOD");
   strcpy(DlabMenuStruct.szSubMenusEntry, "IO");
   strcpy(DlabMenuStruct.szNewMenuEntries, "QuestFit Raw Data");
   strcpy(DlabMenuStruct.szMenuGroupEntries, "GEN");
   DlabMenuStruct.uiNewMenuID = uiMenuId;
   DlabMenuStruct.cMenuAccessKey = 'G';

   // The MenuItem is only inserted in the DASYLabMenu. The Registration take place
   // together with "RegisterModuleClass ( &mc );"
   if (ExpandDASYLabMenu(&DlabMenuStruct) == FALSE)
      MessageBox(NULL, "Error in Function FillTkDllsMenu_GENERATOR()", "Error", MB_OK);

   //Separator.
   //wsprintf(DlabMenuStruct.szNewMenuEntries, "&New !!!");
   //MakeDASYLabMenuSeparator(&DlabMenuStruct);

   return TRUE;
}

/* ************************************************************************ */
/* 5. Module class initializing                                             */
/* ************************************************************************ */

#pragma code_seg("_INIT_TEXT")

void Init_GENERATOR(void)
{
   MODCLASS mc;

   memset(&mc, 0, sizeof(mc));

   LoadString(hInst, MN_MODUL_GENERATOR, IdString_GENERATOR, MODULE_NAME_LENGTH + 1);
   IdString_GENERATOR[MODULE_NAME_LENGTH + 1] = '\0';

   LoadString(hInst, MN_STATUS_GENERATOR, StatusString_GENERATOR, MODULE_STATUS_LENGTH - 1);
   StatusString_GENERATOR[MODULE_STATUS_LENGTH - 1] = '\0';

   mc.hInst = hInst;
   mc.Name = "NEW:GENERATOR";
   mc.DataSize = sizeof(MODULE_GENERATOR);
   mc.VarSize = sizeof(VAR_GENERATOR);
   mc.ChannelSize = sizeof(CHANNEL_GENERATOR);
   mc.MenuId = MN_MODUL_GENERATOR;
   mc.IdString = IdString_GENERATOR;
   mc.StatusString = StatusString_GENERATOR;
   mc.HelpId = 0;
   mc.HelpFileName = NULL;
   mc.BBoxId = BB_UNIVERSAL;
   mc.ModIcon = LoadBitmap(hInst, "GENERATOR_ICO");
   mc.BlkIcon = LoadBitmap(hInst, "EV_GENERATOR");
   mc.PerformAction = PerformAction_GENERATOR;
   mc.ProcessData = ProcessData_GENERATOR;

   // Insert menu item in the DASYLab menu.
   if (mc.MenuId != 0)
      FillTkDllsMenu_GENERATOR(mc.MenuId);

   RegisterModuleClass(&mc);
   QuestFitCalibrationRig_Init();
}

#pragma code_seg()

/* ------------------------------------------------------------------------ */
/* End of file                                                              */
/* ------------------------------------------------------------------------ */
