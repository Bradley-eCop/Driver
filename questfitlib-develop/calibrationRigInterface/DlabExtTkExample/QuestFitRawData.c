/* ======================================================================== */
/* Program    :  Quest Fit DASYLab Interface                                */
/* Module     :  QUESTFITRAWDATA.C                                                  */
/* ------------------------------------------------------------------------ */
/* Functions  :  All necessary Functions for this Module                    */
/* Created    :  Billy Neuson<billy@twisthink.com>                          */
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
#include "QuestFitRawData.H"

/*
*  Include the QuestFitSDK header file
*/
#include "QuestFitCalibrationRig.h"


/* ------------------------------------------------------------------------ */
/* Data structures                                                          */
/* ------------------------------------------------------------------------ */

// MODULE_QUESTFIT is a private data structure for the module, which contains
// data to be stored with the flow chart on disk. (I.e. all values set in the
// dialog box.)

typedef struct
{
   char szChannelName[MAX_CHANNEL][24];    // Channel name
   BOOL bRealTime[MAX_CHANNEL];            // Realtime output
   UINT uiTimeBase;                        // Time Base Identifier
   /*
      Add new parameters here.
      Don't forget to add them in the PARAMETER_INFO also.
      */
} MODULE_QUESTFIT;


static PARAMETER_INFO ParameterGenerator[] =
{
   { "Channel_Name[0..15]", "string[24]", offsetof (MODULE_QUESTFIT, szChannelName[0][0]), 0 },
   { "Real_Time_Output[0..15]", "BOOL", offsetof (MODULE_QUESTFIT, bRealTime[0]), 0 },
   { "Time_Base_ID", "UINT", offsetof (MODULE_QUESTFIT, uiTimeBase), 0 },
   { NULL, NULL, 0, 0 }
};


// VAR_QUESTFIT is a private data structure for
// the module, which contains data for temporary use only.

typedef struct
{
   UINT uiBlockSize;
   double fSampleDistance;
} VAR_QUESTFIT;


// CHANNEL_QUESTFIT is a private data structure for each channel of
// the module, which contains data for temporary use only.

typedef struct
{
   DWORD dwSample;      // Actual sample
   BOOL bPeakDone;      // For pulse output
   BOOL bComputing;     // Still computing ?
   double fReleaseTime; // Release time of the actual output-block
} CHANNEL_QUESTFIT;


/* ------------------------------------------------------------------------ */
/* Global variables                                                         */
/* ------------------------------------------------------------------------ */

static char IdString_QUESTFIT[MODULE_NAME_LENGTH + 2];
static char StatusString_QUESTFIT[MODULE_STATUS_LENGTH + 2];

unsigned long PerformAction_QUESTFIT (MODULE *ThisModule, int wMsg, int wParam, long lParam);


/* ************************************************************************ */
/* 0. General functions                                                     */
/* ************************************************************************ */


/* ------------------------------------------------------------------------ */
/* Function Name     : RegisterStrVarGenerator                              */
/* Description       : Register used global string/vars                     */
/* Parameter         : Pointer to Module Structure                          */
/* ------------------------------------------------------------------------ */

static void RegisterStrVarQuestFit (MODULE * ThisModule)
{
   MODULE_QUESTFIT *ModuleInfo = ThisModule->ModuleParameters;
   UINT i = 0;

   for (i = 0; i < ThisModule->wNumOutChan; i++)
   {
      GlStr_RegisterByText (ModuleInfo->szChannelName[i], ThisModule, PerformAction_QUESTFIT);

   }
}


/* ------------------------------------------------------------------------ */
/* Function Name     : UnregisterStrVarGenerator                            */
/* Description       : Unregister used global string/vars                   */
/* Parameter         : Pointer to Module Structure                          */
/* ------------------------------------------------------------------------ */

static void UnregisterStrVarGenerator (MODULE * ThisModule)
{
   MODULE_QUESTFIT *ModuleInfo = ThisModule->ModuleParameters;
   UINT i = 0;

   for (i = 0; i < ThisModule->wNumOutChan; i++)
   {
      GlStr_UnregisterByText (ModuleInfo->szChannelName[i], ThisModule, PerformAction_QUESTFIT);

   }
}


/* ************************************************************************ */
/* 1. Module functions                                                      */
/* ************************************************************************ */

/* ------------------------------------------------------------------------ */
/* Function Name     : Create_QUESTFIT                                     */
/* Description       : Initializes private data structures of the module    */
/* Parameter         : Pointer to module structure                          */
/* ------------------------------------------------------------------------ */

static BOOL Create_QUESTFIT (MODULE *ThisModule)
{
   MODULE_QUESTFIT *ModuleInfo = ThisModule->ModuleParameters;
   CHANNEL_QUESTFIT *KanalInfo;
   UINT i = 0;
   char channelNames[18][5] = {
       "Fx1",
       "Fy1",
       "Fz1",
       "Fx2",
       "Fy2",
       "Fz2",
       "Fx3",
       "Fy3",
       "Fz3",
       "Fx4",
       "Fy4",
       "Fz4",
       "Fx",
       "Fy",
       "Fz",
       "Mx",
       "My",
       "Mz",
   };

   ThisModule->wNumInpChan = 0;
   ThisModule->wNumOutChan = 18;

   ModuleInfo->uiTimeBase = ID_TIMEBASE_DRIVER;

   for (i = 0; i < MAX_CHANNEL; i++)
   {

      ModuleInfo->bRealTime[i] = TRUE;
      strcpy (ModuleInfo->szChannelName[i], channelNames[i]);

      KanalInfo = ThisModule->TempChannelData[i];
      KanalInfo->bPeakDone = TRUE;
      KanalInfo->dwSample = 0;
   }

   return TRUE;
}


/* ------------------------------------------------------------------------ */
/* Function Name     : Load_QUESTFIT                                       */
/* Description       : This function is called while loading a flowchart    */
/* Parameter         : Pointer to module structure                          */
/* ------------------------------------------------------------------------ */

static BOOL Load_QUESTFIT (MODULE *ThisModule)
{
   RegisterStrVarQuestFit (ThisModule);

   return TRUE;
}


/* ------------------------------------------------------------------------ */
/* Function Name     : Delete_QUESTFIT                                     */
/* Description       : This function is called, if the flowchart is         */
/*                     deleted; it should release memory and GDI objects,   */
/*                     that are created in the Create_... function          */
/* Parameter         : Pointer to module structure                          */
/* ------------------------------------------------------------------------ */

static void Delete_QUESTFIT (MODULE *ThisModule)
{
   UnregisterStrVarGenerator (ThisModule);
}


/* ------------------------------------------------------------------------ */
/* Function Name     : Save_QUESTFIT                                       */
/* Description       : This function is called while saving a flowchart.    */
/* Parameter         : Pointer to module structure                          */
/* ------------------------------------------------------------------------ */

static void Save_QUESTFIT (MODULE *ThisModule)
{
   UNUSED (ThisModule);
}


/* ------------------------------------------------------------------------ */
/* Function Name     : CreateReplace_QUESTFIT                              */
/* Description       : This Function is called, once the User has selected  */
/*                     this module to be replaced by another one. Module    */
/*                     parameters will be copied to a Replace Template.     */
/* Parameter         : Pointer to the Module, Pointer to Replace Template   */
/* ------------------------------------------------------------------------ */

static BOOL CreateReplace_QUESTFIT (MODULE *ThisModule, MODULE *ReplaceTemplate)
{
   MODULE_QUESTFIT *ModuleInfo = ThisModule->ModuleParameters;
   MODULE_DATA_TEMPLATE *TemplateInfo = ReplaceTemplate->ModuleParameters;
   UINT i = 0;

   // Copy parameters to Replace Template
   for (i = 0; i < MAX_CHANNEL; i++)
   {
      strncpy (TemplateInfo->szChannelName[i], ModuleInfo->szChannelName[i], 24);
   }

   // Set validity indicators in Replace Template
   TemplateInfo->bChannelNamesUsed = TRUE;
   TemplateInfo->bUnitsUsed = TRUE;

   return TRUE;
}


/* ------------------------------------------------------------------------ */
/* Function Name     : CheckReplace_QUESTFIT                               */
/* Description       : This Function is called, once the User has selected  */
/*                     this module to be replaced by another one. Module    */
/*                     parameters will be copied to a Replace Template.     */
/* Parameter         : Pointer to Replace Template                          */
/* ------------------------------------------------------------------------ */

static BOOL CheckReplace_QUESTFIT (MODULE *ReplaceTemplate)
{
   // No chance if inputs or no outputs
   if (ReplaceTemplate->wNumInpChan > 0 || ReplaceTemplate->wNumOutChan == 0)
      return FALSE;

   // Otherwise we're fine
   return TRUE;
}


/* ------------------------------------------------------------------------ */
/* Function Name     : Replace_QUESTFIT                                    */
/* Description       : This Function is called, once the User has selected  */
/*                     this module to replace another one. Parameters will  */
/*                     be taken from the Replace Template.                  */
/* Parameter         : Pointer to the Module, Pointer to Replace Template   */
/* ------------------------------------------------------------------------ */

static BOOL Replace_QUESTFIT (MODULE *ThisModule, MODULE *ReplaceTemplate)
{
   MODULE_QUESTFIT *ModuleInfo = ThisModule->ModuleParameters;
   MODULE_DATA_TEMPLATE *TemplateInfo = ReplaceTemplate->ModuleParameters;
   UINT i = 0;

   // First setup default data for the new module
   Create_QUESTFIT (ThisModule);

   // Set correct channel relation (source module might be different)
   ThisModule->ChannelRelation = KZ_NORMAL;

   // Copy valid data from Replace Template
   if (TemplateInfo->bChannelNamesUsed)
   {
      for (i = 0; i < MAX_CHANNEL; i++)
         strncpy (ModuleInfo->szChannelName[i], TemplateInfo->szChannelName[i], 24);
   }


   return TRUE;
}


/* ------------------------------------------------------------------------ */
/* Function Name     : Start_QUESTFIT                                      */
/* Description       : This function is called, if the user has started the */
/*                     experiment; you can perform some "First Time"        */
/*                     routines                                             */
/* Parameter         : Pointer to module structure                          */
/* ------------------------------------------------------------------------ */

static BOOL Start_QUESTFIT (MODULE *ThisModule)
{
   CHANNEL_QUESTFIT *KanalInfo;
   UINT wFifoNr = 0;
   BOOL bRateOK = FALSE;

   for (wFifoNr = 0; wFifoNr < ThisModule->wNumOutChan; wFifoNr++)
   {
      KanalInfo = ThisModule->TempChannelData[wFifoNr];
      KanalInfo->bPeakDone = TRUE;
      KanalInfo->dwSample = 0;
      KanalInfo->bComputing = FALSE;
   }

   UnregisterStrVarGenerator (ThisModule);
   RegisterStrVarQuestFit (ThisModule);

   bRateOK = TRUE;

   for (wFifoNr = 0; wFifoNr < ThisModule->wNumOutChan; wFifoNr++)
   {
      KanalInfo = ThisModule->TempChannelData[wFifoNr];

   }

   if (bRateOK == FALSE)
   {
      LoadString (hInst, STR_GENU_FAST, LongTempString, sizeof (LongTempString));
      ShowWarning (ThisModule->ModuleName, LongTempString);
   }

   return TRUE;
}


/* ------------------------------------------------------------------------ */
/* Function Name     : SetupFifo_QUESTFIT                                  */
/* Description       : This function is called for each output of a module  */
/*                     to perform the structure test of DASYLab; this has   */
/*                     to be done very carefully                            */
/* Parameter         : Pointer to Module, Number of the FIFO                */
/* ------------------------------------------------------------------------ */

static BOOL SetupFifo_QUESTFIT (MODULE *ThisModule, UINT wFifoNr)
{
   MODULE_QUESTFIT *ModuleInfo = ThisModule->ModuleParameters;
   VAR_QUESTFIT *PrivatVars = ThisModule->TempModuleData;
   FIFO_HEADER *ThisFifo = ThisModule->Fifo[wFifoNr];

   ThisFifo->uiMaxBlockSize = PrivatVars->uiBlockSize = GetTimeBaseBlockSize (ModuleInfo->uiTimeBase);
   ThisFifo->fSampleDistance = PrivatVars->fSampleDistance = GetTimeBaseSampleDistance (ModuleInfo->uiTimeBase);

   return TRUE;
}


/* ------------------------------------------------------------------------ */
/* Function Name     : ProcessData_QUESTFIT                                */
/* Description       : Data processing                                      */
/* Parameter         : Pointer to module                                    */
/* ------------------------------------------------------------------------ */

static int ProcessData_QUESTFIT (MODULE *ThisModule)
{
   MODULE_QUESTFIT *ModuleInfo = ThisModule->ModuleParameters;
   VAR_QUESTFIT *PrivatVars = ThisModule->TempModuleData;
   CHANNEL_QUESTFIT *KanalInfo;
   DATA_BLOCK_HEADER *OutputBlock;
   FIFO_HEADER *OutFifo;
   UINT i = 0;
   UINT wFifoNr = 0;

   // If there's no module to use our data we don't have to process it
   if (!ThisModule->bModuleIsConnected)
      return FALSE;

   // Get a block's worth of data from the QuestFit SDK
   size_t samplesRetrieved = 0;
   QuestFitCalibrationSampleInterface_t* inputSamples = malloc(PrivatVars->uiBlockSize * sizeof(QuestFitCalibrationSampleInterface_t));
   if (QuestFitCalibrationRig_GetSamples(PrivatVars->uiBlockSize, inputSamples, &samplesRetrieved) != QFCR_OK)
   {
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
         if ((OutputBlock = GetCurrentOutputBlock (OutFifo)) != NULL)
         {
            // Set time information
             OutputBlock->fStartTime = KanalInfo->dwSample * (1.0 / 2500);
            OutputBlock->fSampleDistance = (1.0 / 2500); // Inverse of 2500Hz
            OutputBlock->uiBlockSize = samplesRetrieved;

            // Release time for this block
            KanalInfo->fReleaseTime = OutputBlock->fStartTime + OutputBlock->uiBlockSize * OutputBlock->fSampleDistance;

            for (i = 0; i < OutputBlock->uiBlockSize; i++)
            {
                int32_t currentSampleComponent;
                switch (wFifoNr)
                {
                  //   case 0:
                  //       currentSampleComponent = inputSamples[i].Fx1;
                  //       break;
                  //   case 1:
                  //       currentSampleComponent = inputSamples[i].Fy1;
                  //       break;
                  //   case 2:
                  //       currentSampleComponent = inputSamples[i].Fz1;
                  //       break;
                  //   case 3:
                  //       currentSampleComponent = inputSamples[i].Fx2;
                  //       break;
                  //   case 4:
                  //       currentSampleComponent = inputSamples[i].Fy2;
                  //       break;
                  //   case 5:
                  //       currentSampleComponent = inputSamples[i].Fz2;
                  //       break;
                  //   case 6:
                  //       currentSampleComponent = inputSamples[i].Fx3;
                  //       break;
                  //   case 7:
                  //       currentSampleComponent = inputSamples[i].Fy3;
                  //       break;
                  //   case 8:
                  //       currentSampleComponent = inputSamples[i].Fz3;
                  //       break;
                  //   case 9:
                  //       currentSampleComponent = inputSamples[i].Fx4;
                  //       break;
                  //   case 10:
                  //       currentSampleComponent = inputSamples[i].Fy4;
                  //       break;
                  //   case 11:
                  //       currentSampleComponent = inputSamples[i].Fz4;
                  //       break;
                  //   case 12:
                  //       currentSampleComponent = inputSamples[i].Fx;
                  //       break;
                  //   case 13:
                  //       currentSampleComponent = inputSamples[i].Fy;
                  //       break;
                  //   case 14:
                  //       currentSampleComponent = inputSamples[i].Fz;
                  //       break;
                  //   case 15:
                  //       currentSampleComponent = inputSamples[i].Mx;
                  //       break;
                  //   case 16:
                  //       currentSampleComponent = inputSamples[i].My;
                  //       break;
                  //   case 17:
                  //       currentSampleComponent = inputSamples[i].Mz;
                  //       break;
                    default:
                        currentSampleComponent = 0;
                        break;
                }
                OutputBlock->Data[i] = currentSampleComponent;
            }
            // Signal processing

            KanalInfo->bComputing = TRUE;
            KanalInfo->dwSample += PrivatVars->uiBlockSize;
         }
      }

      // If release time greater than actual experiment time or there's no real time output for this FIFO: Release block.
      if ((KanalInfo->bComputing == TRUE) && (bExperimentIsPaused == FALSE) &&
          ((ModuleInfo->bRealTime[wFifoNr] == FALSE) || (GetTimeBaseTime (ModuleInfo->uiTimeBase) >= KanalInfo->fReleaseTime)))
      {
         // TK14 - since we have no input, there is no need to process extra memory - in later versions of the toolkit
         //        we might add some code for adding additional data here. 
         ReleaseOutputBlock (OutFifo);
         KanalInfo->bComputing = FALSE;
      }
   }
   free(inputSamples);

   return TRUE;
}


/* ------------------------------------------------------------------------ */
/* Function Name     : Stop_QUESTFIT                                       */
/* Description       : This function is called when the user stops the      */
/*                     experiment                                           */
/* Parameter         : Pointer to Module                                    */
/* ------------------------------------------------------------------------ */

static BOOL Stop_QUESTFIT (MODULE *ThisModule)
{
   UNUSED (ThisModule);

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

static void DisplayChannel (HWND hDlg, UINT wNummer)
{
   MODULE_QUESTFIT *TempInfo = SingleInfo;


   SetDlgItemText (hDlg, IDD_KANAL_NAME, TempInfo->szChannelName[wNummer]);



   CheckDlgButton (hDlg, IDD_GEN_REALTIME, TempInfo->bRealTime[wNummer]);
}


/* ------------------------------------------------------------------------ */
/* Function Name     : RetrieveChannel                                      */
/* Description       : This function retrieves the data for one channel in  */
/*                     the dialog box                                       */
/* Parameter         : Handle of dialog box, number of channel to display   */
/* ------------------------------------------------------------------------ */

static void RetrieveChannel (HWND hDlg, UINT wNummer)
{
   MODULE_QUESTFIT *TempInfo = SingleInfo;

   GetDlgItemText (hDlg, IDD_KANAL_NAME, TempInfo->szChannelName[wNummer], CHANNEL_NAME_LENGTH);

}


/* ------------------------------------------------------------------------ */
/* Function Name     : QuestFitProc                                        */
/* Description       : Dialog box function for this dialog box. This        */
/*                     function has to be exported and should not be static */
/* Parameter         : Standard for dialog functions or Window functions    */
/* ------------------------------------------------------------------------ */

BOOL CALLBACK QuestFitProc (HWND hDlg, UINT Message, WPARAM wParam, LPARAM lParam)
{
   MODULE *ThisModule = CurrentModulePtr;
   MODULE_QUESTFIT *TempInfo = SingleInfo;

   switch (Message)
   {
      case WM_INITDIALOG:
      {
         // Allocate memory for temporary data
         SingleInfo = MemAlloc (sizeof (MODULE_QUESTFIT));

         if (!SingleInfo)
         {
            EndDialog (hDlg, FALSE);
            return TRUE;
         }

         TempInfo = SingleInfo;

         // Copy module parameters to the temporary structure
         memcpy (TempInfo, ThisModule->ModuleParameters, sizeof (MODULE_QUESTFIT));

         // Set number of in-/outputs
         wDialNumChan = ThisModule->wNumOutChan;
         wDialCurChan = 0;
         wDialMaxChan = 16;

         // Set popup menu for global variables
         SetMenuForGlobalStrings (hDlg, IDD_KANAL_NAME);
         SetMenuForGlobalVars (hDlg, IDD_GEN_FREQ);
         SetMenuForGlobalVars (hDlg, IDD_GEN_AMPL);

         InitChannelBar (hDlg);

         // Fill time base combo box
         FillTimeBaseCombo (hDlg, IDD_GEN_TIMEBASE, TempInfo->uiTimeBase);
         EnableWindow (GetDlgItem (hDlg, IDD_GEN_TIMEBASE), !bExperimentIsRunning);

         // Limit some edit boxes
         Edit_LimitText (GetDlgItem (hDlg, IDD_KANAL_NAME), CHANNEL_NAME_LENGTH);
         Edit_LimitText (GetDlgItem (hDlg, IDD_MODUL_NAME), MODULE_NAME_LENGTH);
         Edit_LimitText (GetDlgItem (hDlg, IDD_MODUL_BEZEICHNUNG), MODULE_DESCRIPTION_LENGTH);

         SetDlgItemText (hDlg, IDD_MODUL_NAME, ThisModule->ModuleName);
         SetDlgItemText (hDlg, IDD_MODUL_BEZEICHNUNG, ThisModule->ModuleDescription);

         DisplayChannel (hDlg, wDialCurChan);
         SetFocus (GetDlgItem (hDlg, IDD_MODUL_NAME));
         wDialLastFocus = 0;

         return (FALSE);
      }
      break;

      case WM_CLICK_LDOWN:
      {
         // A new channel was selected
         if (LOWORD (lParam) == 2)
         {
            RetrieveChannel (hDlg, wDialCurChan);
            HandleChannelClick (hDlg, wParam);
            DisplayChannel (hDlg, wDialCurChan);
         }

         wDialLastFocus = IDD_KAN00;
         SetFocus (GetDlgItem (hDlg, IDD_KAN00));
         return TRUE;
      }
      break;

      case WM_COPYFOCUS:   // F7 Key
      {
         UINT i = 0;

         // Get actual values
         RetrieveChannel (hDlg, wDialCurChan);
         DisplayChannel (hDlg, wDialCurChan);

         // Check last focus and copy
         for (i = 0; i < wDialNumChan; i++)
         {
            if (i != wDialCurChan)
            {
               switch (wDialLastFocus)
               {
                  case IDD_KANAL_NAME:
                     strcpy (TempInfo->szChannelName[i], TempInfo->szChannelName[wDialCurChan]);
                     break;

                  case IDD_GEN_REALTIME:
                     TempInfo->bRealTime[i] = TempInfo->bRealTime[wDialCurChan];
                     break;
               }
            }
         }
      }
      break;

      case WM_COPYALL:  // F8 Key
      {
         UINT i = 0;

         // Get actual values
         RetrieveChannel (hDlg, wDialCurChan);
         DisplayChannel (hDlg, wDialCurChan);

         for (i = 0; i < wDialNumChan; i++)
         {
            if (i != wDialCurChan)
            {
               strcpy (TempInfo->szChannelName[i], TempInfo->szChannelName[wDialCurChan]);
               TempInfo->bRealTime[i] = TempInfo->bRealTime[wDialCurChan];
            }
         }
      }
      break;

      case WM_COMMAND:
      {
         UINT cmd_id = GET_WM_COMMAND_ID (wParam, lParam);
         UINT cmd_cmd = GET_WM_COMMAND_CMD (wParam, lParam);

         switch (cmd_id)
         {
            case IDD_LESS:
            {
               // One channel less
               RetrieveChannel (hDlg, wDialCurChan);
               HandleLessMoreButton (hDlg, IDD_LESS);
               DisplayChannel (hDlg, wDialCurChan);
               wDialLastFocus = IDD_KAN00;
               SetFocus (GetDlgItem (hDlg, IDD_KAN00));
               return TRUE;
            }
            break;

            case IDD_MORE:
            {
               // One more channel
               RetrieveChannel (hDlg, wDialCurChan);
               HandleLessMoreButton (hDlg, IDD_MORE);
               DisplayChannel (hDlg, wDialCurChan);
               wDialLastFocus = IDD_KAN00;
               SetFocus (GetDlgItem (hDlg, IDD_KAN00));
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
                  RetrieveChannel (hDlg, wDialCurChan);
                  DisplayChannel (hDlg, wDialCurChan);
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
                  TempInfo->uiTimeBase = GetTimeBaseComboID (ComboBox_GetCurSel (GetDlgItem (hDlg, IDD_GEN_TIMEBASE)));
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

               LoadString (hInstDlab, ID_EVAHILFE, ShortTempString, sizeof (ShortTempString));
               strcpy (LongTempString, ExeFileDir);
               strcat (LongTempString, ShortTempString);

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
               SetFocus (GetDlgItem (hDlg, IDOK));

               RetrieveChannel (hDlg, wDialCurChan);

               ThisModule = CurrentModulePtr;

               GetDlgItemText (hDlg, IDD_MODUL_NAME, ShortTempString, MODULE_NAME_LENGTH + 1);
               ChangeModuleName (ThisModule, ShortTempString);

               GetDlgItemText (hDlg, IDD_MODUL_BEZEICHNUNG, ThisModule->ModuleDescription, MODULE_DESCRIPTION_LENGTH + 1);

               UnregisterStrVarGenerator (ThisModule);

               // Copy temporary data to the module parameters
               memcpy (ThisModule->ModuleParameters, TempInfo, sizeof (MODULE_QUESTFIT));

               ChangeModuleSize (ThisModule, 0, wDialNumChan);

               RegisterStrVarQuestFit (ThisModule);

               // Free memory for temporary data
               MemFree (SingleInfo);
               SingleInfo = NULL;

               EndDialog (hDlg, TRUE);
               return TRUE;
            }
            break;

            case IDCANCEL:
            {
               SetFocus (GetDlgItem (hDlg, IDCANCEL));

               // Free memory for temporary data
               MemFree (SingleInfo);
               SingleInfo = NULL;

               EndDialog (hDlg, FALSE);
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
/* Function Name     : Param_QUESTFIT                                      */
/* Description       : Process the dialog box for this module               */
/* Parameter         : Pointer to the module structure                      */
/* ------------------------------------------------------------------------ */

static void Param_QUESTFIT (MODULE *ThisModule)
{
   HWND hwnd = ThisModule->hwndModule;
   BOOL bDoit = FALSE;

   bDoit = DialogBox (hInst, "QUESTFIT", hwnd, (DLGPROC)QuestFitProc);

}


/* ************************************************************************ */
/* 3. Action handling                                                       */
/* ************************************************************************ */


/* ------------------------------------------------------------------------ */
/* Function Name     : Exit_QUESTFIT                                       */
/* Description       : Here we destroy things, that we initialized in the   */
/*                     Init_... function; especially WindowClasses. This is */
/*                     only necessary very seldom. This Function is called  */
/*                     when the Program is unloaded                         */
/* Parameter         : ---                                                  */
/* ------------------------------------------------------------------------ */

static void Exit_QUESTFIT (void)
{
}


/* ************************************************************************ */
/* 4. DASYLab message handling                                              */
/* ************************************************************************ */

/* ------------------------------------------------------------------------ */
/* Function Name     : PerformAction_QUESTFIT                              */
/* ------------------------------------------------------------------------ */

unsigned long PerformAction_QUESTFIT (MODULE *ThisModule, int wMsg, int wParam, long lParam)
{
   switch (wMsg)
   {
      // DASYLab Class Messages
      case DQM_UNREGISTER_CLASS:
         Exit_QUESTFIT ();
         return TRUE;

      case DQM_CHECK_REPLACE:
         return CheckReplace_QUESTFIT ((MODULE *)lParam);

         // DASYLab Module Messages
      case DMM_CREATE_MODULE:
         return Create_QUESTFIT (ThisModule);

      case DMM_DELETE_MODULE:
         Delete_QUESTFIT (ThisModule);
         return TRUE;

      case DMM_PARAM_MODULE:
         Param_QUESTFIT (ThisModule);
         return TRUE;

      case DMM_SAVE_MODULE:
         Save_QUESTFIT (ThisModule);
         return TRUE;

      case DMM_LOAD_MODULE:
         return Load_QUESTFIT (ThisModule);

      case DMM_START_MODULE:
         return Start_QUESTFIT (ThisModule);

      case DMM_STOP_MODULE:
         return Stop_QUESTFIT (ThisModule);

      case DMM_QUERY_MODULE_ACTION:
      case DMM_MODULE_ACTION:
      case DMM_EXPLAIN_USER_ACTION:
      case DMM_GLOBAL_STRING_CHANGED:
      case DMM_GLOBAL_VAR_CHANGED:
          return TRUE;

      case DCM_SETUP_FIFO:
         return SetupFifo_QUESTFIT (ThisModule, wParam);

      case DMM_COPY_CHANNEL_NAME:
      {
         MODULE_QUESTFIT *ModuleInfo = ThisModule->ModuleParameters;
         UINT i = 0;

         for (i = 0; i < ThisModule->wNumOutChan; i++)
         {
            CopyChannelName (ThisModule->Fifo[i], (LPSTR *)ModuleInfo->szChannelName[i]);
         }
      }
      break;

      case DCM_GET_UNIT:
      {

         return 0;
      }
      break;

      case DMM_GET_PARAMETERS_INFO:
         return (long)ParameterGenerator;

      case DMM_CREATE_REPLACE:
         return CreateReplace_QUESTFIT (ThisModule, (MODULE *)lParam);

      case DMM_REPLACE_MODULE:
         return Replace_QUESTFIT (ThisModule, (MODULE *)lParam);

      case DMM_REQUEST_GLOB_VARS:
          return TRUE;

      case DMM_REQ_MODULE_DEFAULT:
         return TRUE;

      case DMM_IS_DEBUG:
      # ifdef _DEBUG
         return 2;
      # else
         return TRUE;
      # endif

      case DMM_GET_TIMEBASE_ID:
         return ((MODULE_QUESTFIT *)ThisModule->ModuleParameters)->uiTimeBase;

      default:
         break;
   }

   return PerformDefaultAction (ThisModule, wMsg, wParam, lParam);
}


/* ------------------------------------------------------------------------ */
/* Function Name     : FillTkDllsMenu_QUESTFIT                             */
/* Description       : Insert a MenuItem in the DASYLab main menu           */
/* Remark            : For possible values look at the description for the  */
/*                     Function "ExpandModuleBar ( void )".                 */
/* ------------------------------------------------------------------------ */

BOOL FillTkDllsMenu_QUESTFIT (UINT uiMenuId)
{
   DASYLAB_INSERT_MENU DlabMenuStruct;

   strcpy (DlabMenuStruct.szMainMenuEntry, "MOD");
   strcpy (DlabMenuStruct.szSubMenusEntry, "CONTR");
   strcpy (DlabMenuStruct.szNewMenuEntries, "&New TK !!!//New: Generator");
   strcpy (DlabMenuStruct.szMenuGroupEntries, "GEN2");
   DlabMenuStruct.uiNewMenuID = uiMenuId;
   DlabMenuStruct.cMenuAccessKey = 'G';

   // The MenuItem is only inserted in the DASYLabMenu. The Registration take place
   // together with "RegisterModuleClass ( &mc );"
   if (ExpandDASYLabMenu (&DlabMenuStruct) == FALSE)
      MessageBox (NULL, "Error in Function FillTkDllsMenu_QUESTFIT()", "Error", MB_OK);

   //Separator.
   //wsprintf(DlabMenuStruct.szNewMenuEntries, "&New !!!");
   //MakeDASYLabMenuSeparator(&DlabMenuStruct);

   return TRUE;
}


/* ************************************************************************ */
/* 5. Module class initializing                                             */
/* ************************************************************************ */

#pragma code_seg ( "_INIT_TEXT" )

void Init_QUESTFIT (void)
{
   MODCLASS mc;

   memset (&mc, 0, sizeof (mc));

   LoadString (hInst, MN_MODUL_QUESTFIT, IdString_QUESTFIT, MODULE_NAME_LENGTH + 1);
   IdString_QUESTFIT[MODULE_NAME_LENGTH + 1] = '\0';

   LoadString (hInst, MN_STATUS_QUESTFIT, StatusString_QUESTFIT, MODULE_STATUS_LENGTH - 1);
   StatusString_QUESTFIT[MODULE_STATUS_LENGTH - 1] = '\0';

   mc.hInst = hInst;
   mc.Name = "NEW:QUESTFIT";
   mc.DataSize = sizeof (MODULE_QUESTFIT);
   mc.VarSize = sizeof (VAR_QUESTFIT);
   mc.ChannelSize = sizeof (CHANNEL_QUESTFIT);
   mc.MenuId = MN_MODUL_QUESTFIT;
   mc.IdString = IdString_QUESTFIT;
   mc.StatusString = StatusString_QUESTFIT;
   mc.HelpId = 0;
   mc.HelpFileName = NULL;
   mc.BBoxId = BB_UNIVERSAL;
   mc.ModIcon = LoadBitmap (hInst, "QUESTFIT");
   mc.BlkIcon = LoadBitmap (hInst, "EV_QUESTFIT");
   mc.PerformAction = PerformAction_QUESTFIT;
   mc.ProcessData = ProcessData_QUESTFIT;

   // Insert menu item in the DASYLab menu.
   if (mc.MenuId != 0)
      FillTkDllsMenu_QUESTFIT (mc.MenuId);

   RegisterModuleClass (&mc);
}

#pragma code_seg ()

/* ------------------------------------------------------------------------ */
/* End of file                                                              */
/* ------------------------------------------------------------------------ */
