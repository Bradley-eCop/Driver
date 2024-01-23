/* ======================================================================== */
/* Programm   :  DLAB -  Messwerterfassung und Verarbeitung unter Windows   */
/* Modul      :  TOOLMAIN.H                                                 */
/* ------------------------------------------------------------------------ */
/* Funktionen :  Rahmen-Hauptprogramm für DLL-Toolkit                       */
/* Erstellt   :  C. Strunk ab 12.05.93                                      */
/* Erweitert  :  ---  (Hier ggf. andere Programmierer eintragen)            */
/* Letzte Änd.:  12.05.93 CS                                                */
/* ======================================================================== */


#pragma region Changelog

// - MX_SG 05.07.2016
//   Bei der Umstellung auf DASYLab 2016 wurden die Funktionen "SetInputBitmap" und "SetOutputBitmap" versehentlich entfernt.
//  

#pragma endregion


#include "PRE_WIN.H"
#include <WINDOWS.H>
#include "POST_WIN.H"
#include <WINDOWSX.H>
#include <STDIO.H>
#include <FLOAT.H>
#include <COMMDLG.H>
#include <STRING.H>
#include <DIRECT.H>

HBITMAP *hBitChannel;         // Bitmaps für benutzerdefiniertes Controls in den Dasylab Dialogen
HBITMAP *hBitLessMore;

int iTKVersionsNummer = 2;    // MX_RO 13.07.2015 - Versionsnummer von 1 auf 2 gesetzt - bedeutet: Toolkit DASYLab 2016

#ifndef _USE_TOOLKIT_
#define _USE_TOOLKIT_
#endif

#define EXTERN                      /* Externe Variablen hier instantiieren */
//#include "KERNEL.H"
#include "DLAB.H"
#include "EDITOR.H"

#ifndef BBM_SETBITS
#  define BBM_SETBITS       ( BM_SETSTYLE + 10)         /* Aus BWCC.H */
#endif

/* Kommunikation mit DASYLab */
#define ImportVar(type,name)  if ( (name= type SendMessage ( hwndMain, WM_GET_DASYLAB_VARIABLE, TOOLKIT_VERSION , (LPARAM)(LPSTR)#name )) == type NULL ) return 0
#define ImportBool(type,name) name= type SendMessage ( hwndMain, WM_GET_DASYLAB_VARIABLE, TOOLKIT_VERSION , (LPARAM)(LPSTR)#name )
#define ImportAdr(type,name)  if ( (lp##name= type SendMessage ( hwndMain, WM_GET_DASYLAB_VARIABLE, TOOLKIT_VERSION , (LPARAM)(LPSTR)"&" #name )) == NULL ) return 0
#define ImportProc(name)      if ( (name= (PROTO_##name) SendMessage ( hwndMain, WM_GET_DASYLAB_FUNCTION, TOOLKIT_VERSION , (LPARAM)(LPSTR)#name )) == NULL ) return 0
#define ExportVar(v)          if ( DefineDllVariable((LPSTR)#v,&v,sizeof(v)) == FALSE ) return 0;
#define ExportProc(p)         if ( DefineDllVariable((LPSTR)#p,(void *)(long)&p,sizeof(void *)) == FALSE ) return 0;

LRESULT CALLBACK ControlKanalProc (HWND hwnd, UINT wMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ControlLessMoreProc (HWND hwnd, UINT wMsg, WPARAM wParam, LPARAM lParam);

// MX_RO 29.09.2015 - Removed SetFontSmallProc since deprecated since Windows 16 Bit

#pragma code_seg ( "_INIT_TEXT" )

#ifndef _AFXDLL

// Entry Point for DLLs

//*************************************************************************************************
// DllMain
// Main Entry Point of the DLL.
//
//*************************************************************************************************
BOOL WINAPI DllMain (HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
   switch (dwReason)
   {
      case DLL_PROCESS_ATTACH:
         hInst = hInstance;
         break;

      // Not used by DASYLab
      case DLL_PROCESS_DETACH:
      case DLL_THREAD_ATTACH:
      case DLL_THREAD_DETACH:
         break;

      default:
         break;
   }

   UNUSED (lpReserved);

   return TRUE;
}

#endif

//*************************************************************************************************
// SetupDlabDLL
// This function creates the connection to DASYlab, imports all needed functions and variables and
// prepares some global Variables.
//
//*************************************************************************************************
int WINAPI SetupDlabDLL (HWND hwnd)
{
   WNDCLASS wndclass;

   // Fenster-Handle des DASYLab-Hauptfensters sichern
   hwndMain = hwnd;

   // Toolkit-Versionsnummer in DASYLab bekanntmachen.
   SendMessage (hwndMain, WM_SET_DASYLAB_VARIABLE, (WPARAM) (int) iTKVersionsNummer, 0);

   // Pointer- und Handle-Variablen von DASYLab erfragen (incl. NULL-Check)

   // hInstDlab - The instance handle of the DASYLab program. You will normally not need this
   ImportVar ( (HINSTANCE) (UINT), hInstDlab);

   // MainMenu - Handle of DASYLab 's main menu bar.
   ImportVar ( (HMENU) (UINT), MainMenu);

   // GlobalModuleClass - ???
   ImportVar ( (MODULKLASSE *), GlobalModuleClass);

   // icons - ???
   ImportVar ( (ICONS *), icons);

   // hwndDesk - Window handle of the DASYLab desk window; this is the area where the flow chart gets displayed.
   ImportAdr ( (HWND *), hwndDesk);

   // Pointer to main Module structure
   ImportAdr ( (MODULE * * *), Module);

   // ViewModule - ???
   ImportAdr ( (MODULE * * *), ViewModule);

   // wNumberOfModules - Number of modules in the currently active black box.
   ImportAdr ( (UINT *), wNumberOfModules);

   // uiHighModuleNumber - Last module number in use for the currently active black box plus one.
   ImportAdr ( (UINT *), uiHighModuleNumber);
   // CurrentModule - ???
   ImportAdr ( (UINT *), CurrentModule);

   // CurrentModule - Dialog box handling: Pointer to the actual module.
   ImportAdr ( (MODULE * *), CurrentModulePtr);

   // bDateDayLeadingZero - Date day format with leading zero
   ImportBool ( (BOOL), bDateDayLeadingZero);

   // bDateMonthLeadingZero - Month day format with leading zero
   ImportBool ( (BOOL), bDateMonthLeadingZero);

   // bDateYearLong - Date year format is long (1999)
   ImportBool ( (BOOL), bDateYearLong);

   // wDateFormat - Date format
   ImportBool ( (UINT), wDateFormat);

   // bTime24h - Time format counts from 0 to 24 hours
   ImportBool ( (BOOL), bTime24h);

   // bTimeLeadingZero - Time format has a leading zero
   ImportBool ( (BOOL), bTimeLeadingZero);

   // TimeTrenn - Time separator
   ImportVar ( (char *), TimeTrenn);

   // DezTrenn - Decimal separator
   ImportVar ( (char *), DezTrenn);

   // bDecLeadingZero - Decimal format has a leading zero
   ImportBool ( (BOOL), bDecLeadingZero);

   // DateTrenn - Time separator
   ImportVar ( (char *), DateTrenn);

   // bDisplayWithoutWnd - ???
   ImportAdr ( (BOOL *), bDisplayWithoutWnd);

   ImportAdr ( (BOOL *), bPauseIsDisabled);

   // LAYER_OutputParam - ???
   ImportAdr ( (LAYER_OUTPUT_PARAM *), LAYER_OutputParam);

   // StreamOptionen - ???
   ImportAdr ( (STREAMOPTIONEN *), StreamOptionen);

   // TempStreamOptionen - ???
   ImportAdr ( (STREAMOPTIONEN * *), TempStreamOptionen);

   // CJ_Refs - ???
   ImportAdr ( (UINT *), CJ_Refs);

   // CJ_Temp - ???
   ImportAdr ( (double *), CJ_Temp);

   // hBitChannel - ???
   ImportVar ( (HBITMAP *), hBitChannel);

   // hBitLessMore - ???
   ImportVar ( (HBITMAP *), hBitLessMore);

   // hDkGrayPen - A dark gray pen for general use.
   ImportVar ( (HPEN) (UINT), hDkGrayPen);

   // hPipePenRed - A red pen for general use.
   ImportVar ( (HPEN) (UINT), hPipePenRed);

   // hPipePenGreen - A green pen for general use.
   ImportVar ( (HPEN) (UINT), hPipePenGreen);

   // hLightRedBrush - A light red brush for general use.
   ImportVar ( (HBRUSH) (UINT), hLightRedBrush);

   // hGreenBrush - A green brush for general use.
   ImportVar ( (HBRUSH) (UINT), hGreenBrush);

   // InitialStartupDir - The DASYLab directory.
   ImportVar ( (char *), InitialStartupDir);

   // ExeFileDir
   ImportVar ( (char *), ExeFileDir);
   ImportVar ( (char *), NameOfFlowChart);

   // FullNameOfFlowChart - Full name (including path) of the flow chart currently loaded.
   ImportVar ( (char *), FullNameOfFlowChart);

   // ProgFileNameIni
   ImportVar ( (char *), ProgFileNameIni);

   // DefStreamingDir - The default directory for storing streaming files.
   ImportVar ( (char *), DefStreamingDir);

   // DefFlowchartDir - The default directory for storing flow charts.
   ImportVar ( (char *), DefFlowchartDir);

   // DefDataDir - The default directory for storing data values.
   ImportVar ( (char *), DefDataDir);

   // DefDeviceDir - The default directory for storing device data.
   ImportVar ( (char *), DefDeviceDir);

   // DefUtilityDir - The default directory for storing util and tool data.
   ImportVar ( (char *), DefUtilityDir);

   // chDefSharedUserDir - Dasylab Directory in "shared Documents". This is the root of all shared data directory for dasylab
   ImportVar ( (char *), chDefSharedUserDir);

   // GlobalFlowChartInfo.Author - ???
   ImportVar ( (char *), GlobalFlowChartInfo.Author);

   // GlobalFlowChartInfo.Company - ???
   ImportVar ( (char *), GlobalFlowChartInfo.Company);

   // GlobalFlowChartInfo.Department - ???
   ImportVar ( (char *), GlobalFlowChartInfo.Department);

   // GlobalFlowChartInfo.Title - ???
   ImportVar ( (char *), GlobalFlowChartInfo.Title);

   // GlobalFlowChartInfo.Info - ???
   ImportVar ( (char *), GlobalFlowChartInfo.Info);

   ImportVar ( (DAP_SETUP *), DapSetup);

   // clrUserDefinedColors - ???
   ImportVar ( (COLORREF *), clrUserDefinedColors);

   // clrUserDefinedColorsDSB - ???
   ImportVar ( (COLORREF *), clrUserDefinedColorsDSB);

   // clrControlKanalBk - ???
   ImportBool ( (COLORREF), clrControlKanalBk);

   // wndpar - ???
   ImportVar ( (FENSTERPARAMETER far *), wndpar);

   // ExperimentStartTime - Date and time when the experiment was started. The time is given in seconds since Jan 1, 1970, UTC.
   ImportAdr ( (time_t *), ExperimentStartTime);

   // StartingTimeTicks - ???
   ImportAdr ( (long *), StartingTimeTicks);

   // SerialOpt : Options from the serial Number
   ImportAdr ( (SERIAL_OPT *), SerialOpt);

   // DdeInstance - ???
   ImportAdr ( (DWORD *), DdeInstance);

   // ToolTip - ???
   ImportAdr ( (ToolTipTyp *), ToolTip);

   // nWindowOrder - ???
   ImportAdr ( (int *), nWindowOrder);

   // Funktions-Pointer von DASYLab erfragen
   // NewMemAlloc
   ImportProc (NewMemAlloc);

   // NewMemReAlloc - ???
   ImportProc (NewMemReAlloc);

   // NewDoMemFree - ???
   ImportProc (NewDoMemFree);

   // DefineDllModule - ???
   ImportProc (DefineDllModule);

   // DefineDllVariable - ???
   ImportProc (DefineDllVariable);

   // RegisterModuleClass - Register a module class with DASYLab.
   ImportProc (RegisterModuleClass);

   // PerformDefaultAction - Default module message handler.
   ImportProc (PerformDefaultAction);

   // NewReleaseOutputBlock - ???
   ImportProc (NewReleaseOutputBlock);

   // GetCurrentOutputBlock - Retrieves a pointer to a data block to store new data.
   ImportProc (GetCurrentOutputBlock);

   // GetInputFifo - Retrieves a pointer to the FIFO connected to a module's input side at a specific channel.
   ImportProc (GetInputFifo);

   // GetInputBlock - Retrieves a pointer to an input block for the selected channel.
   ImportProc (GetInputBlock);

   // NewReleaseInputBlock - ???
   ImportProc (NewReleaseInputBlock);

   // ChangeModuleSize - Change the number of input and output channels for a module.
   ImportProc (ChangeModuleSize);

   // ChangeModuleName - Change the name of a module and make the name change known to all
   // instances within DASYLab that might use it (Action modules, Layout objects).
   ImportProc (ChangeModuleName);

   // ChangeNameInString - This function is used to exchange placeholders for global strings
   // or variables in strings after a name change.
   ImportProc (ChangeNameInString);

   // ScanStringForGlobals - ???
   ImportProc (ScanStringForGlobals);

   // SendModuleMessage - ???
   ImportProc (SendModuleMessage);

   // SendModChanMessage - ???
   ImportProc (SendModChanMessage);

   // CopyChannelName - Copy the channel name to the connected module(s).
   ImportProc (CopyChannelName);

   // FillUnitList - Fill a combo box with the default units.
   ImportProc (FillUnitList);

   // MODUL_InitAll - ???
   ImportProc (MODUL_InitAll);

   // MODUL_DestroyAll - ???
   ImportProc (MODUL_DestroyAll);

   // InitMatrixNew - ???
   ImportProc (InitMatrixNew);

   // MX_RO 10.12.2015 API for static (Fifo) and dynamic (Block) Extra Memory
   // This API is subject to change - tentiavly usable with VERSION_CODE >= 1500   
   ImportProc (EmemFifo_SETUP_MsgBuildInit);    
   ImportProc (EmemFifp_SETUP_MsgDataExchange);
   ImportProc (EmemFifo_SETUP_MsgAdd);
   ImportProc (EmemFifo_SETUP_MsgDelete);
   ImportProc (EmemFifo_SETUP_MsgBuildFinalize);
   ImportProc (EmemFifo_SETUP_MsgGetCnt);
   ImportProc (EmemFifo_SETUP_MsgExplain);
   ImportProc (EmemFifo_SETUP_MsgRead);
   ImportProc (EmemFifo_SETUP_MsgCopyPlain);
   ImportProc (EmemFifo_SETUP_MsgCopyModify);

   ImportProc (EmemBlock_SETUP_MsgBuildInit);
   ImportProc (EmemBlock_SETUP_MsgDataExchange);
   ImportProc (EmemBlock_SETUP_MsgAdd);
   ImportProc (EmemBlock_SETUP_MsgDelete);
   ImportProc (EmemBlock_SETUP_MsgBuildFinalize);
   ImportProc (EmemBlock_START_MsgGetCnt);
   ImportProc (EmemBlock_START_MsgExplain);
   ImportProc (EmemBlock_PROCESS_MsgRead);
   ImportProc (EmemBlock_PROCESS_MsgCopyPlain);    // Suggested to include from DASYLab 14 DLLs to ensure compatibility with later versions
   ImportProc (EmemBlock_PROCESS_MsgCopyModify);   

   // ShowWarning - Show a dialog box. Mainly used for warning messages.
   ImportProc (ShowWarning);

   // Same as ShowWarning but only for console.
   ImportProc (ConsoleOutWarning);

   // Prints a formatted text on the console.
   ImportProc (ConsoleOutRaw);

   // Prints a simple formatted text on the console.
   ImportProc (ConsoleOutf);

   // EnableAllWindows - Enable/Disable all module windows.
   ImportProc (EnableAllWindows);

   // ShowInternalError - ???
   ImportProc (ShowInternalError);

   // StopExperiment - Stop the experiment.
   ImportProc (StopExperiment);

   // PauseExperiment - Pause the experiment; can then be resumed later on.
   ImportProc (PauseExperiment);

   // CurrentExperimentTime - ???
   ImportProc (CurrentExperimentTime);

   // DispatchQueuedMessages - ???
   ImportProc (DispatchQueuedMessages);

   // BlackBox
   // BBox_FullEnter - ???
   ImportProc (BBox_FullEnter);

   // BBox_FullLeave - ???
   ImportProc (BBox_FullLeave);

   // BBox_LightEnter - ???
   ImportProc (BBox_LightEnter);

   // BBox_LightLeave - ???
   ImportProc (BBox_LightLeave);

   // CreateSatellite - ???
   ImportProc (CreateSatellite);

   // UpdateSatellite - ???
   ImportProc (UpdateSatellite);

   // RemoveUselessSatellites - ???
   ImportProc (RemoveUselessSatellites);

   // SetupModuleBarBitmaps - ???
   //ImportProc (SetupModuleBarBitmaps);

   // GDI Stack
   // CreateStackedPen - Call this function to receive a pen handle by the DASYLab GDI stack management.
   ImportProc (CreateStackedPen);

   // CreateStackedPenIndirect - Call this function to receive a pen handle by the DASYLab GDI stack management.
   // As parameter the LPLOGPEN structure is used.
   ImportProc (CreateStackedPenIndirect);

   // CreateStackedFontIndirect - Call this function to receive a font handle by the DASYLab GDI stack management.
   // As parameter the LPLOGFONT structure is used.
   ImportProc (CreateStackedFontIndirect);

   // CreateStackedSolidBrush - Call this function to receive a solid brush handle by the DASYLab GDI stack management.
   // As parameter the COLORREF structure is used.
   ImportProc (CreateStackedSolidBrush);

   // CreateStackedBrushIndirect - Call this function to receive any brush handle by the DASYLab GDI stack management.
   // As parameter the LPLOGBRUSH structure is used.
   ImportProc (CreateStackedBrushIndirect);

   // DeleteStackedObject - After using an device handle it has to be unregistered by the DASYLab GDI stack.
   // So call this function before requesting i.e. a changed pen color or at the DELETE_ function, when the module is destroyed.
   ImportProc (DeleteStackedObject);

   // This and That ...
   // do_fft - Basic FFT calculation (internal processing)
   ImportProc (do_fft);

   // do_fftex - FFT calculation with NI math Library
   ImportProc (do_fftex);

   // EditText - ???
   ImportProc (EditText);

   // LoadInterpolationTable - Load DASYLab Interpolation Table
   ImportProc (LoadInterpolationTable);

   // LoadTableFromFile - Load DASYLab Interpolation Table
   ImportProc (LoadTableFromFile);

   // SearchForFileToLoad - ???
   ImportProc (SearchForFileToLoad);

   // DoesFileExistAndMsg - ???
   ImportProc (DoesFileExistAndMsg);

   // AskForFilenameChange - ???
   ImportProc (AskForFilenameChange);

   // CheckCreateDir - ???
   ImportProc (CheckCreateDir);

   // InitPrinter - ???
   ImportProc (InitPrinter);

   // PrintHeader - ???
   ImportProc (PrintHeader);

   // ExitPrinter - ???
   ImportProc (ExitPrinter);

   // PrintFooter - ???
   ImportProc (PrintFooter);

   // NextPage - ???
   ImportProc (NextPage);

   ImportProc (CheckedCreateFile);

   // CheckedOpenFile - ???
   ImportProc (CheckedOpenFile);

   // CreateAndShowToolTipWindow - ???
   ImportProc (CreateAndShowToolTipWindow);

   // SendPanelMessage - ???
   ImportProc (SendPanelMessage);

   // GlStr_RegisterByText - Register the update function which has
   // to be called if the global string indicated by the placeholder
   ImportProc (GlStr_RegisterByText);

   // GlStr_UnregisterByText - Unregister the update function which
   // has to be called if the global string indicated by the
   // placeholder theText has changed.
   ImportProc (GlStr_UnregisterByText);

   // ExpandString - Before the output of a string which could
   // contain a global string, it is necessary to exchange the
   // global string with the stored string. Use the ExpandString
   // function for easily changing the global string holder.
   ImportProc (ExpandString);

   // ExpandStringNumber - ???
   ImportProc (ExpandStringNumber);

   // ExpandVarNumber - The function ExpandVarNumber checks the
   // dialog box item string. If there was added a global variable
   // the return value is larger than 0. In VarNumber the referring
   // variable number from 1 to 999 is stored.
   ImportProc (ExpandVarNumber);

   // ExpandUnitString - Simplify a unit given in UnitFormula.
   ImportProc (ExpandUnitString);

   // ExpandUnit - ???
   ImportProc (ExpandUnit);

   // GlStr_RegisterByNumber - Register the update function which has
   // to be called if the global string indicated by Number has changed.
   ImportProc (GlStr_RegisterByNumber);

   // GlStr_UnregisterByNumber - Unregister the update function which
   // has to be called if the global string indicated by Number has
   // changed.
   ImportProc (GlStr_UnregisterByNumber);

   // GlStr_Set - Assign a string to the global string indicated by Number.
   ImportProc (GlStr_Set);

   // GlStr_Get - Recieve the string of the global string indicated by Number.
   ImportProc (GlStr_Get);

   // GlStr_PrefixGet - Recieve the prefix string of the global string indicated by Number.
   ImportProc (GlStr_PrefixGet);

   // GlVar_RegisterByNumber - Call this function to register the used
   // variable number (1-999). Each time this variable is changed from
   // outside, a message DMM_GLOBAL_VAR_CHANGED is sent to the
   ImportProc (GlVar_RegisterByNumber);

   // GlVar_UnregisterByNumber - Call this function to unregister the
   // used variable number. The number of calls for register and
   // unregister have to be equal. So pay attention in a module dialog
   // box. Unregister the variables before the ChangeModuleSize
   // function is called and register the variables again before
   // leaving the dialog box in the IDOK statement. It is also useful
   // to register all variables at the START_ function again.
   ImportProc (GlVar_UnregisterByNumber);

   // GlVar_Set - Here is a short description of additional functions
   // which can be called. GlVar_Set and GlVar_Get set or retrieve the
   // value of a particular variable. GlVar_PrefixGet gets the prefix
   // string of a special variable number. GlVar_VarStringGet gets a
   // variable number out of a string (dialog box string ... ).
   ImportProc (GlVar_Set);

   // GlVar_Get - Here is a short description of additional functions
   // which can be called. GlVar_Set and GlVar_Get set or retrieve the
   // value of a particular variable. GlVar_PrefixGet gets the prefix
   // string of a special variable number. GlVar_VarStringGet gets a
   // variable number out of a string (dialog box string ... ).
   ImportProc (GlVar_Get);

   // GlVar_PrefixGet - Here is a short description of additional functions
   // which can be called. GlVar_Set and GlVar_Get set or retrieve the
   // value of a particular variable. GlVar_PrefixGet gets the prefix
   // string of a special variable number. GlVar_VarStringGet gets a
   // variable number out of a string (dialog box string ... ).
   ImportProc (GlVar_PrefixGet);

   // GlVar_VarStringGet - Here is a short description of additional
   // functions which can be called. GlVar_Set and GlVar_Get set or
   // retrieve the value of a particular variable. GlVar_PrefixGet
   // gets the prefix string of a special variable number.
   // GlVar_VarStringGet gets a variable number out of a string
   // (dialog box string ... ).
   ImportProc (GlVar_VarStringGet);

   // GlVar_SetSyntax - This function is used for setting the correct
   // text in a dialog box if a global variable or a system variable
   // is used (see example above).
   ImportProc (GlVar_SetSyntax);

   // GlStr_SetSyntax - This function is used for setting the correct
   // text in a dialog box if a global string or a system string is
   // used (see example above).
   ImportProc (GlStr_SetSyntax);

   // SetMenuForGlobalStrings - The popup menu of those edit fields
   // in a dialog box where global strings can be entered can be
   // extended by using this function. A menu to select global strings
   // or system strings is added. This function has to be called with
   // the initialization of the dialog box WM_INITDIALOG.
   ImportProc (SetMenuForGlobalStrings);

   // SetMenuForGlobalVars - Use this function to expand the popup
   // menu of edit fields in dialog boxes. The appended menu item
   // allows to select global variables via dialog.

   ImportProc (SetMenuForGlobalVars);

   // DeleteMenuForGlobalStrings - ???
   ImportProc (DeleteMenuForGlobalStrings);

   // DeleteMenuForGlobalVars - ???
   ImportProc (DeleteMenuForGlobalVars);

   // ShowVarsAndSelect - ???
   ImportProc (ShowVarsAndSelect);

   // DsbHasChanged - Tell DASYLab that a flowchart has changed. Use
   // this call i.e. at the IDOK of a dialog box so that the user is
   // asked to save the flowchart before leaving the DASYLab session.
   ImportProc (DsbHasChanged);

   // RegisterMenuEntry - ???
   ImportProc (RegisterMenuEntry);

   // RegisterExtraMemory - The function RegisterExtraMemory registers
   // exactly one additional memory range. After that it is necessary
   // to call AddExtMemInstance if one wants to save the registered
   // memory in a flow chart (in dsb- or ASCII-format) and loading
   // the flow chart reads this memory later.
   ImportProc (RegisterExtraMemory);

   // FindModuleByName - ???
   ImportProc (FindModuleByName);

   // AddExtMemInstance - The function RegisterExtraMemory registers
   // exactly one additional memory range. After that it is necessary
   // to call AddExtMemInstance if one wants to save the registered
   // memory in a flow chart (in dsb- or ASCII-format) and loading
   // the flow chart reads this memory later.
   ImportProc (AddExtMemInstance);

   // RemoveExtMemInstance - This function call decrements the instance
   // counter for the named identifier by one, if there is at least one
   // instance of the identifier. Otherwise the counter of instance is
   // set to zero.
   ImportProc (RemoveExtMemInstance);

   // RegisterNewWorksheetNotification - ???
   ImportProc (RegisterNewWorksheetNotification);

   // RegisterTimeBase - The function registers a time base structure
   // for use within DASYLab.
   ImportProc (RegisterTimeBase);
   ImportProc (UnregisterTimeBase);

   // SetTimeBase - The function updates the time base settings
   // within DASYLab.
   ImportProc (SetTimeBase);

   // SetTimeBaseTime - The function updates the time of the time base.
   ImportProc (SetTimeBaseTime);

   // IncTimeBaseTime - The function increments the time of the
   // time base.
   ImportProc (IncTimeBaseTime);

   // GetTimeBaseBlockSize - The function retrieves the actual block
   // size of the time base.
   ImportProc (GetTimeBaseBlockSize);

   // GetTimeBaseSampleDistance - The function retrieves the actual
   // sample distance of the time base.
   ImportProc (GetTimeBaseSampleDistance);

   // GetTimeBaseTime - The function retrieves the actual time of the
   // time base.
   ImportProc (GetTimeBaseTime);

   // FillTimeBaseCombo - The function sets up a ComboBox in a dialog
   // for selection of a time base.
   ImportProc (FillTimeBaseCombo);

   // GetTimeBaseComboID - The function returns the time base ID of the
   // selected entry of a ComboBox created with the previous function.
   ImportProc (GetTimeBaseComboID);

   // TimeBaseDialog - The function opens the DASYLab time base dialog.
   ImportProc (TimeBaseDialog);

   // GlvoModuleNotifyGlobalVar - The call of the function
   // GlvoModuleNotifyGlobalVar with the properly filled struct variable
   // Param notifies the Variable Overview if and in which way variables
   // are used inside this module.
   ImportProc (GlvoModuleNotifyGlobalVar);

   // DASYLabInsertMenu - ???
   ImportProc (DASYLabInsertMenu);

   // CreateDispWindow - ???
   ImportProc (CreateDispWindow);

   // CreateAToolBarDisplayEx - ???
   ImportProc (CreateAToolBarDisplayEx);

   // DeleteAToolBarDisplayEx - ???
   ImportProc (DeleteAToolBarDisplayEx);

   // CheckWindowPosition - ???
   ImportProc (CheckWindowPosition);

   wxScreen = (GetSystemMetrics (SM_CXVIRTUALSCREEN) );
   wyScreen = (GetSystemMetrics (SM_CYVIRTUALSCREEN) );

   // Set ofnExplorerFlag
   ofnExplorerFlag = OFN_EXPLORER | OFN_ENABLESIZING;

   // Anmelden der DLL bei DASYLab
   if (!DefineDllModule () )
   {
      return 0;
   }

   // fGlobalMilliSecondsPerSample - Sample distance in milliseconds, as
   // specified in the global experiment setup dialog box. Modules like
   // the Generator or Timer use this rate to produce their data.
   ExportVar (fGlobalMilliSecondsPerSample);

   // uiGlobalBlockSize - Data block size, as specified in the global
   // experiment setup dialog box. Modules like the Generator or Timer
   // use this block size to produce their data.
   ExportVar (uiGlobalBlockSize);

   // bAnimation - TRUE, if the user activated the animation.
   ExportVar (bAnimation);

   // bExperimentIsRunning - TRUE, while the experiment is running.
   ExportVar (bExperimentIsRunning);

   // bExperimentIsPaused - TRUE, while the experiment is paused.
   ExportVar (bExperimentIsPaused);

   // dwExperimentStartTimeTicks - This is the value of GetTickCount()
   // that windows reported when the experiment was started. Modules
   // like the Generator or Timer use this as a time base for real time
   // release of the data blocks.
   ExportVar (dwExperimentStartTimeTicks);

   ExportVar (BBoxModul);

   // Pens laden
   hBlackPen = (HPEN) GetStockObject (BLACK_PEN);
   hWhitePen = GetStockObject (WHITE_PEN);
   hDkGrayBrush = GetStockObject (DKGRAY_BRUSH);

   // Initialisierung der hier definierten Modulklassen
   if (!Init_DLL () )
   {
      return 0;
   }

   // Fensterklasse für benutzerdefiniertes CONTROL Element initialisieren
   wndclass.lpszClassName = "EVA:CONTROLKANAL";
   wndclass.hInstance = hInst;
   wndclass.lpfnWndProc = ControlKanalProc;
   wndclass.hCursor = LoadCursor (NULL, IDC_ARROW);
   wndclass.hIcon = NULL;
   wndclass.lpszMenuName = NULL;
   wndclass.hbrBackground = GetStockObject (DKGRAY_BRUSH);
   wndclass.style = CS_DBLCLKS;
   wndclass.cbClsExtra = 0;
   wndclass.cbWndExtra = 2;

   RegisterClass (&wndclass);

   // Fensterklasse für benutzerdefiniertes CONTROL Element initialisieren
   wndclass.lpszClassName = "EVA:CONTROLLESSMORE";
   wndclass.hInstance = hInst;
   wndclass.lpfnWndProc = ControlLessMoreProc;
   wndclass.hCursor = LoadCursor (NULL, IDC_ARROW);
   wndclass.hIcon = NULL;
   wndclass.lpszMenuName = NULL;
   wndclass.hbrBackground = GetStockObject (DKGRAY_BRUSH);
   wndclass.style = CS_DBLCLKS;
   wndclass.cbClsExtra = 0;
   wndclass.cbWndExtra = 2;

   RegisterClass (&wndclass);

   return TRUE;
}

#pragma code_seg ( "_EXIT_TEXT" )

//*************************************************************************************************
//
//
//
//*************************************************************************************************
int WINAPI WEP (int nParam)
{
   UNUSED (nParam);

   return 1;
}

//*************************************************************************************************
//
//
//
//*************************************************************************************************
int WINAPI FinishDlabDLL (HWND hwnd)
{
   UnregisterClass ("EVA:CONTROLKANAL", hInst);
   UnregisterClass ("EVA:CONTROLLESSMORE", hInst);

   UNUSED (hwnd);
   return Exit_DLL ();
}

#pragma code_seg()   /* Reset to default */

/* Hilfsprozeduren für Dialogboxen */

//*************************************************************************************************
//
//
//
//*************************************************************************************************
void InitChannelBar (HWND hDlg)
{
   UINT i;
   HANDLE hButton;

   for (i = 0; i < wDialMaxChan; i++)
   {
      hButton = GetDlgItem (hDlg, IDD_KAN00 + i);

      if (i < wDialNumChan)
      {
         if (i == wDialCurChan)
         {
            SendMessage (hButton, BBM_SETBITS, 1, (LONG) 0);
         }
         else
         {
            SendMessage (hButton, BBM_SETBITS, 2, (LONG) 0);
         }
      }
      else
      {
         SendMessage (hButton, BBM_SETBITS, 3, (LONG) 0);
      }
   }

   /* Ändern der Anzahl der Ausgänge verhindern, wenn Messung läuft */
   if (bExperimentIsRunning == TRUE)
   {
      hButton = GetDlgItem (hDlg, IDD_LESS);
      SendMessage (hButton, BBM_SETBITS, 0, (LONG) 0);
      hButton = GetDlgItem (hDlg, IDD_MORE);
      SendMessage (hButton, BBM_SETBITS, 3, (LONG) 0);
   }
   else
   {
      hButton = GetDlgItem (hDlg, IDD_LESS);

      if (wDialNumChan < 2)
      {
         SendMessage (hButton, BBM_SETBITS, 0, (LONG) 0);
      }
      else
      {
         SendMessage (hButton, BBM_SETBITS, 1, (LONG) 0);
      }

      hButton = GetDlgItem (hDlg, IDD_MORE);

      if (wDialNumChan > wDialMaxChan - 1)
      {
         SendMessage (hButton, BBM_SETBITS, 3, (LONG) 0);
      }
      else
      {
         SendMessage (hButton, BBM_SETBITS, 4, (LONG) 0);
      }
   }

   return;
}

//*************************************************************************************************
//
//
//
//*************************************************************************************************
void HandleLessMoreButton (HWND hDlg, UINT wTypID)
{
   HWND hButton;

   if (SerialOpt.uiVersionsTyp == ID_VERSION_RUNTIME)
   {
      return;
   }

   switch (wTypID)
   {
      case IDD_LESS:
      {
         if (wDialNumChan == wDialMaxChan)
         {
            /* More Button war Disabled; nach Less Enablen */
            hButton = GetDlgItem (hDlg, IDD_MORE);
            SendMessage (hButton, BBM_SETBITS, 4, (LONG) 0);
         }

         wDialNumChan--;

         if (wDialNumChan < 2)
         {
            /* Less Button Enablen, da min. Anzahl erreicht */
            hButton = GetDlgItem (hDlg, IDD_LESS);
            SendMessage (hButton, BBM_SETBITS, 0, (LONG) 0);
         }

         /* "Angeklemmten" Kanal abklemmen */
         hButton = GetDlgItem (hDlg, IDD_KAN00 + wDialNumChan);
         SendMessage (hButton, BBM_SETBITS, 3, (LONG) 0);

         /* Ein Auge auf den aktuellen Kanal werfen */
         if (wDialCurChan >= wDialNumChan)
         {
            wDialCurChan = wDialNumChan - 1;
            hButton = GetDlgItem (hDlg, IDD_KAN00 + wDialCurChan);
            SendMessage (hButton, BBM_SETBITS, 1, (LONG) 0);
         }
      }
      break;

      case IDD_MORE:
      {
         if (wDialNumChan == 1)
         {
            /* Less Button war Disabled; nach More Enablen */
            hButton = GetDlgItem (hDlg, IDD_LESS);
            SendMessage (hButton, BBM_SETBITS, 1, (LONG) 0);
         }

         wDialNumChan++;

         if (wDialNumChan > wDialMaxChan - 1)
         {
            /* More Button Enablen, da max. Anzahl erreicht */
            hButton = GetDlgItem (hDlg, IDD_MORE);
            SendMessage (hButton, BBM_SETBITS, 3, (LONG) 0);
         }

         /* "Abgeklemmten" Kanal anklemmen */
         hButton = GetDlgItem (hDlg, IDD_KAN00 + wDialNumChan - 1);
         SendMessage (hButton, BBM_SETBITS, 2, (LONG) 0);
      }
      break;
   }

   return;
}

//*************************************************************************************************
//
//
//
//*************************************************************************************************
void HandleChannelClick (HWND hDlg, UINT wParam)
{
   HWND hButton;

   hButton = GetDlgItem (hDlg, IDD_KAN00 + wDialCurChan);
   SendMessage (hButton, WM_AUSSCHALTEN, 0, (LONG) 0);
   wDialCurChan = GetDlgCtrlID ( (HWND) wParam) - IDD_KAN00;
   SendMessage ( (HWND) wParam, BBM_SETBITS, 1, (LONG) 0);
}

/* ------------------------------------------------------------------------ */
/* Rückgabewert      : -                                                    */
/* Globale Variablen :                                                      */
/* Historie          : 07.05.1992 Mago (Erstellung)                         */
/*                     07.07.1992 Mago (Letzte Änderung)                    */
/* ------------------------------------------------------------------------ */

//*************************************************************************************************
//
//
//
//*************************************************************************************************
BOOL ModalChooseColor (void *colptr, BOOL bEnableAllWindows, HWND hwndOwner)
/* Diese Funktion entfällt in Zukunft ! */
{
   int iCountUserDefinedColors;
   CHOOSECOLOR *cc = (CHOOSECOLOR *) colptr;
   BOOL rc;
   COLORREF temporaerUserDefinedColors[16];

   cc->Flags &= ~CC_SHOWHELP;

   //Kopieren von aus dem temporären Feld für Schaltbilddatei.
   if (wndpar->bUserDefinedColorsDSB == TRUE)
   {
      for (iCountUserDefinedColors = 0; iCountUserDefinedColors < 16; iCountUserDefinedColors++)
      {
         clrUserDefinedColors[iCountUserDefinedColors] = clrUserDefinedColorsDSB[iCountUserDefinedColors];
      }
   }

   for (iCountUserDefinedColors = 0; iCountUserDefinedColors < 16; iCountUserDefinedColors++)
   {
      temporaerUserDefinedColors[iCountUserDefinedColors] = clrUserDefinedColors[iCountUserDefinedColors];
   }

   //Zuerst einmal mit den bisherigen benutzerdefinierten Farben initialisieren.
   cc->lpCustColors = clrUserDefinedColors;

   if (bEnableAllWindows)
   {
      EnableAllWindows (FALSE);
   }
   else if (hwndOwner != NULL)
   {
      EnableWindow (hwndOwner, FALSE);
   }

   rc = ChooseColor ( (CHOOSECOLOR *) cc);

   //Nur wenn nicht Abbrechen oder kein Fehler aufgetreten ist, die neuen benutzerdefinierten
   //Farbwerte in die Variablen übernehmen.
   if (rc != 0)
   {
      //Nach der Auswahl der benutzerdefinierten Farbe, diese speichern.
      for (iCountUserDefinedColors = 0; iCountUserDefinedColors < 16; iCountUserDefinedColors++)
      {
         clrUserDefinedColors[iCountUserDefinedColors] = (cc->lpCustColors) [iCountUserDefinedColors];
      }

      //IMMER auch die globalen benutzerdefinierten Farben auch im Schaltbild
      //(zusätzlich zur DASYLab.ini) speichern.
      //d.h. nicht: if(wndpar->bUserDefinedColorsDSB == TRUE)
      //Kopieren in das temporären Feld für Schaltbilddatei.
      for (iCountUserDefinedColors = 0; iCountUserDefinedColors < 16; iCountUserDefinedColors++)
      {
         clrUserDefinedColorsDSB[iCountUserDefinedColors] = clrUserDefinedColors[iCountUserDefinedColors];
      }
   }
   else
   {
      //Im Fehlerfall oder bei Abbrechen wird das 16-elementige Feld 'benutzerdefinierte Farben'
      //manuell mit den Werten besetzt, die es VOR dem Aufruf des Dialogs "ChooseColor" hatte.
      //Dies ist erforderlich, da ChooseColor diese Änderungen in dem 'benutzerdefinierten
      //Farbfeld' SOFORT übernimmt; bei Abbrechen werden diese übernommenen Werte
      //NICHT von ChooseColor verworfen.
      //Restaurierung der benutzerdefinierten Farbwerte.
      for (iCountUserDefinedColors = 0; iCountUserDefinedColors < 16; iCountUserDefinedColors++)
      {
         clrUserDefinedColors[iCountUserDefinedColors] = temporaerUserDefinedColors[iCountUserDefinedColors];
      }
   }

   if (bEnableAllWindows)
   {
      EnableAllWindows (TRUE);
   }
   else if (hwndOwner != NULL)
   {
      EnableWindow (hwndOwner, TRUE);
   }

   return rc;
}

/* ------------------------------------------------------------------------ */
/* Funktionsname     : ModalChooseFont                                        */
/* Beschreibung      : Ersatz für WINDOWS ChooseFont                        */
/* Aufrufparameter   : wie ChooseColor aus COMMDLG                          */
/* Rückgabewert      : wie ChooseColor aus COMMDLG                          */
/* Globale Variablen : --                                                   */
/* Historie          : 09.11.1992 CS (Erstellung)                           */
/*                   : 09.11.1992 CS (Letzte Änderung)                      */
/* ------------------------------------------------------------------------ */

BOOL ModalChooseFont (void *fntptr, BOOL bEnableAllWindows, HWND hwndOwner)
{
   CHOOSEFONT *cf = (CHOOSEFONT *) fntptr;
   BOOL rc;

   /* Erlaube nur TrueType und keine Symbol-Fonts */
   if (SerialOpt.Sprache != ID_SPRACHE_JAPAN)
   {
      cf->Flags |= CF_ANSIONLY | CF_TTONLY;
   }
   else
   {
      cf->Flags |= CF_TTONLY;
   }

   if (bEnableAllWindows)
   {
      EnableAllWindows (FALSE);
   }
   else if (hwndOwner != NULL)
   {
      EnableWindow (hwndOwner, FALSE);
   }

   rc = ChooseFont (cf);

   if (bEnableAllWindows)
   {
      EnableAllWindows (TRUE);
   }
   else if (hwndOwner != NULL)
   {
      EnableWindow (hwndOwner, TRUE);
   }

   return rc;
}

/* ------------------------------------------------------------------------ */
/* Funktionsname     : ClToScr                                              */
/* Beschreibung      : Konvertierung Clientkoordinaten in Screenkoo.        */
/* Aufrufparameter   : hwndClient - Fensterhandle des Clientfensters        */
/*                     re         - Rectvariable des Bereiches der Konv.wird*/
/* Rückgabewert      : konvertierte RECT-Koordinaten                        */
/* Globale Variablen :                                                      */
/* Historie          : 16.03.1992 Ma (Erstellung)                           */
/*                     16.03.1992 Ma (Letzte Änderung)                      */
/* ------------------------------------------------------------------------ */

RECT ClToScr (HWND hwndClient, HWND hwndBezug, RECT re)
{
   POINT ph[2];
   ph[0] = * (PPOINT) &re.left;
   ClientToScreen (hwndClient, &ph[0]);
   ScreenToClient (hwndBezug, &ph[0]);
   ph[1] = * (PPOINT) &re.right;
   ClientToScreen (hwndClient, &ph[1]);
   ScreenToClient (hwndBezug, &ph[1]);
   re = * (PRECT) ph;
   return (re);
}

/* ------------------------------------------------------------------------ */
/* Funktionsname     : ScrToCl                                              */
/* Beschreibung      : Konvertierung Screenkoordinaten in Clientkoo.       */
/* Aufrufparameter   : hwndClient - Fensterhandle des Clientfensters        */
/*                     re         - Rectvariable des Bereiches der Konv.wird*/
/* Rückgabewert      : konvertierte RECT-Koordinaten                        */
/* Globale Variablen :                                                      */
/* Historie          : 16.03.1992 Ma (Erstellung)                           */
/*                     16.03.1992 Ma (Letzte Änderung)                      */
/* ------------------------------------------------------------------------ */

RECT ScrToCl (HWND hwndClient, RECT re)
{
   POINT ph[2];
   ph[0] = * (PPOINT) &re.left;
   ScreenToClient (hwndClient, &ph[0]);
   ph[1] = * (PPOINT) &re.right;
   ScreenToClient (hwndClient, &ph[1]);
   re = * (PRECT) ph;
   return (re);
}

//*************************************************************************************************
//
//
//
//*************************************************************************************************
void CenterDialogOriginal (HWND hwnd, HWND hwndOwner)
{
   POINT pt;
   RECT swp;
   RECT rParent;
   int iwidth, iheight;
   int max_x, max_y;
   int too_big_x, too_big_y;

   /* Größe der Fenster bestimmen */
   GetWindowRect (hwnd, &swp);

   if (hwndOwner != NULL)
   {
      GetClientRect (hwndOwner, &rParent);
   }
   else
   {
      GetWindowRect (GetDesktopWindow (), &rParent);
   }

   /* Breite und Höhe des zu zentrierenden Fensters berechenen */
   iwidth = swp.right - swp.left;
   iheight = swp.bottom - swp.top;

   /* Mitte finden und nach Screen Koordinaten konvertieren */
   pt.x = (rParent.right - rParent.left) / 2;
   pt.y = (rParent.bottom - rParent.top) / 2;

   if (hwndOwner != NULL)
   {
      ClientToScreen (hwndOwner, &pt);
   }

   /* Startpunkt des zu zentrierenden Fensters bestimmen */
   pt.x = pt.x - (iwidth / 2);
   pt.y = pt.y - (iheight / 2);

   /* Paßt die Dialogbox denn auch auf den Schirm ? */
   max_x = GetSystemMetrics (SM_CXVIRTUALSCREEN);
   max_y = GetSystemMetrics (SM_CYVIRTUALSCREEN);

   /* Nicht zuweit rechts unten plazieren */
   too_big_x = pt.x + iwidth - max_x;

   if (too_big_x > 0)
   {
      pt.x -= too_big_x;
   }

   too_big_y = pt.y + iheight - max_y;

   if (too_big_y > 0)
   {
      pt.y -= too_big_y;
   }

   /* Aber auch nicht zuweit links oben plazieren */
   if (pt.x < 0)
   {
      pt.x = 0;
   }

   if (pt.y < 0)
   {
      pt.y = 0;
   }

   /* Schlußendlich Fenster an die neue Position verschieben */
   MoveWindow (hwnd, pt.x, pt.y, iwidth, iheight, FALSE);

   if (SerialOpt.Sprache == ID_SPRACHE_JAPAN)
   {
      return;
   }
}

//*************************************************************************************************
//
//
//
//*************************************************************************************************
void CenterDialog (HWND hwnd, HWND hwndOwner)
{
   UNUSED (hwnd);
   UNUSED (hwndOwner);
}

typedef HRESULT (WINAPI * ENABLETHEMEDIALOGTEXTURE) (HWND, DWORD);

// entnommen aus uxtheme.h
#define ETDT_DISABLE                                                0x00000001
#define ETDT_ENABLE                                                 0x00000002
#define ETDT_USETABTEXTURE                                          0x00000004
#define ETDT_ENABLETAB                     (ETDT_ENABLE  | ETDT_USETABTEXTURE)

//*************************************************************************************************
//
//
//
//*************************************************************************************************
void TKCenterDialogColorDlg (HWND hwnd, HWND hwndOwner)
{
   POINT pt;
   RECT swp;
   RECT rParent;
   int iwidth = 0;
   int iheight = 0;
   int max_x = 0;
   int max_y = 0;
   int too_big_x = 0;
   int too_big_y = 0;

   HRESULT hr;
   HINSTANCE hDll;
   ENABLETHEMEDIALOGTEXTURE pfnETDT;

   // MHa 06.11.2009 - Behandlung der Farbprobleme bei Nutzung von Tab
   // Controls und CreateDialog. Mit der Funktion EnableThemeDialogTexture
   // verhindern wir die grauen Flächen innerhalb der Registerkarten.

   // Maps a WIN32 error value into an HRESULT. Note that this assumes WIN32
   // errors fall in the range of -32k to 32k.
   // ERROR_CALL_NOT_IMPLEMENTED = This function is not supported on this
   // system.
   hr = HRESULT_FROM_WIN32 (ERROR_CALL_NOT_IMPLEMENTED);

   if (NULL != (hDll = LoadLibrary (TEXT ("uxtheme.dll") ) ) )
   {
      if (NULL != (pfnETDT = (ENABLETHEMEDIALOGTEXTURE) GetProcAddress (hDll, "EnableThemeDialogTexture") ) )
      {
         hr = pfnETDT (hwnd, ETDT_ENABLETAB);
      }

      FreeLibrary (hDll);
   }

   // Größe der Fenster bestimmen
   GetWindowRect (hwnd, &swp);

   if (hwndOwner != NULL)
   {
      GetClientRect (hwndOwner, &rParent);
   }
   else
   {
      GetWindowRect (GetDesktopWindow (), &rParent);
   }

   // Breite und Höhe des zu zentrierenden Fensters berechenen
   iwidth = swp.right - swp.left;
   iheight = swp.bottom - swp.top;

   // Mitte finden und nach Screen Koordinaten konvertieren
   pt.x = (rParent.right - rParent.left) / 2;
   pt.y = (rParent.bottom - rParent.top) / 2;

   if (hwndOwner != NULL)
   {
      ClientToScreen (hwndOwner, &pt);
   }

   // Startpunkt des zu zentrierenden Fensters bestimmen
   pt.x = pt.x - (iwidth / 2);
   pt.y = pt.y - (iheight / 2);

   // Paßt die Dialogbox denn auch auf den Schirm?
   max_x = GetSystemMetrics (SM_CXVIRTUALSCREEN);
   max_y = GetSystemMetrics (SM_CYVIRTUALSCREEN);

   // Nicht zuweit rechts unten plazieren
   too_big_x = pt.x + iwidth - max_x;

   if (too_big_x > 0)
   {
      pt.x -= too_big_x;
   }

   too_big_y = pt.y + iheight - max_y;

   if (too_big_y > 0)
   {
      pt.y -= too_big_y;
   }

   // Aber auch nicht zuweit links oben plazieren
   if (pt.x < 0)
   {
      pt.x = 0;
   }

   if (pt.y < 0)
   {
      pt.y = 0;
   }

   // Schlußendlich Fenster an die neue Position verschieben
   MoveWindow (hwnd, pt.x, pt.y, iwidth, iheight, FALSE);

   // MX_RO 29.09.2015 - SetFontSmallProc entfernt da schmale Fonts in Dialogboxen seit WIN32 Standard sind
}

//*************************************************************************************************
//
//
//
//*************************************************************************************************
void TKEnableThemeDialogTexture (HWND hwnd)
{
   HRESULT hr;
   HINSTANCE hDll;
   ENABLETHEMEDIALOGTEXTURE pfnETDT;

   hr = HRESULT_FROM_WIN32 (ERROR_CALL_NOT_IMPLEMENTED);

   if (NULL != (hDll = LoadLibrary (TEXT ("uxtheme.dll") ) ) )
   {
      if (NULL != (pfnETDT = (ENABLETHEMEDIALOGTEXTURE) GetProcAddress (hDll, "EnableThemeDialogTexture") ) )
      {
         hr = pfnETDT (hwnd, ETDT_ENABLETAB);
      }

      FreeLibrary (hDll);
   }
}

//*************************************************************************************************
//
//
//
//*************************************************************************************************
void HandleLessMoreCountButtons (HWND hDlg, UINT wTypID, UINT wCount)
{
   HWND hMoreButton, hLessButton;
   UINT wButtonLessOrMore;

   int i, Repeat = 0;

   if (SerialOpt.uiVersionsTyp == ID_VERSION_RUNTIME)
   {
      return;
   }

   //Überprüfen, ob LESS/MORE-Buttons im Dlg vorhanden sind.
   wButtonLessOrMore = IDD_MORE;
   hMoreButton = GetDlgItem (hDlg, IDD_MORE);
   hLessButton = GetDlgItem (hDlg, IDD_LESS);

   if ( (hMoreButton == NULL) || (hLessButton == NULL) )
   {
      return;
   }

   switch (wTypID)
   {
      case IDD_LESS:
         if (wDialNumChan < 2)
         {
            return;
         }

         wButtonLessOrMore = IDD_LESS;

         if (GetAsyncKeyState (VK_CONTROL) & 0x8000)
         {
            Repeat = wDialNumChan - wCount;
         }
         else
         {
            Repeat = 1;
         }

         break;

      case IDD_MORE:
         if (wDialNumChan > (wDialMaxChan - 1) )
         {
            return;
         }

         wButtonLessOrMore = IDD_MORE;

         if (GetAsyncKeyState (VK_CONTROL) & 0x8000)
         {
            Repeat = wCount - wDialNumChan + 1;
         }
         else
         {
            Repeat = 1;
         }

         break;
   }

   for (i = 0; i < Repeat; i++)
   {
      SendMessage (hDlg, WM_COMMAND, wButtonLessOrMore, 0);
   }

   return;
}

//Bisherige Funktionalität (nichtTransparentes Malen der Bitmaps).
void DrawNoneTransparentBitmap (HDC hdc, HBITMAP hBitmap, int xStartScr, int yStartScr, int xStartDest, int yStartDest)
{
   BITMAP bm;
   HDC hMemDC;
   POINT  pt;

   hMemDC = CreateCompatibleDC (hdc);
   SelectObject (hMemDC, hBitmap);
   SetMapMode (hMemDC, GetMapMode (hdc) );
   GetObject (hBitmap, sizeof (BITMAP), (LPSTR) &bm);
   pt.x = bm.bmWidth;
   pt.y = bm.bmHeight;
   DPtoLP (hdc, &pt, 1);
   BitBlt (hdc, xStartDest, yStartDest, pt.x, pt.y, hMemDC, xStartScr, yStartScr, SRCCOPY);
   DeleteDC (hMemDC);
}

// Statt TransparentBlt(), für die die Msimg32.lib erforderlich ist, wird mittels DrawTransparentBitmap() die Fkt
// TransparentBlt() nachgebildet, so dass sie auch unter Win98 läuft.
// Außerdem kann die Transparenzfarbe geändert werden, indem einfach vor Malen des TransparentBitmaps ein Viereck
// in Bitmapgrösse mit der neuen gewünschten Hintergrundfarbe gemalt wird.
// FIXME SG : Wir brauche keine Rücksicht mehr auf Windows 98 zu nehmen. Ab Dasylab 2016 haben wir doch immer mindestens Windows 7
//            Da könnte man doch auch wieder die original Funktion verwenden TransparentBlt verwenden 
void DrawTransparentBitmap (HDC hdc,
                            HBITMAP hBitmap,
                            int xStartScr,
                            int yStartScr,
                            COLORREF cTransparentColor,
                            int xStartDest,
                            int yStartDest,
                            COLORREF cTransparentReplaceColor)
{
   BITMAP bm;
   COLORREF cColor;
   HBITMAP bmAndBack, bmAndObject, bmAndMem, bmSave;
   HBITMAP bmBackOld, bmObjectOld, bmMemOld, bmSaveOld;
   HDC hdcMem, hdcBack, hdcObject, hdcTemp, hdcSave;
   POINT ptSize;
   RECT rect;

   // MHa 21.04.2005 - Bugfix BoundsChecker Resource leak
   HBRUSH brush = NULL;

   HBRUSH OldBrush;
   hdcTemp = CreateCompatibleDC (hdc);
   SelectObject (hdcTemp, hBitmap);  // Select the bitmap

   GetObject (hBitmap, sizeof (BITMAP), (LPSTR) &bm);
   ptSize.x = bm.bmWidth;            // Get width of bitmap
   ptSize.y = bm.bmHeight;           // Get height of bitmap
   DPtoLP (hdcTemp, &ptSize, 1);     // Convert from device

   // to logical points
   if (cTransparentColor != cTransparentReplaceColor)
   {
      //Transparenzfarbe durch neue Hintergrundfarbe ersetzen.
      brush = CreateSolidBrush (cTransparentReplaceColor);

      // MHa 21.04.2005 - Bugfix BoundsChecker Invalid argument
      OldBrush = (HBRUSH) SelectObject (hdc, brush);

      rect.left = xStartDest;
      rect.right = rect.left + ptSize.x;
      rect.top = yStartDest;
      rect.bottom = rect.top + ptSize.y;
      FillRect (hdc, &rect, brush);

      // MHa 21.04.2005 - Bugfix BoundsChecker Invalid argument
      brush = SelectObject (hdc, OldBrush);
      DeleteStackedObject (brush);
   }

   // Create some DCs to hold temporary data.
   hdcBack = CreateCompatibleDC (hdc);
   hdcObject = CreateCompatibleDC (hdc);
   hdcMem = CreateCompatibleDC (hdc);
   hdcSave = CreateCompatibleDC (hdc);

   // Create a bitmap for each DC. DCs are required for a number of
   // GDI functions.

   // Monochrome DC
   bmAndBack = CreateBitmap (ptSize.x, ptSize.y, 1, 1, NULL);

   // Monochrome DC
   bmAndObject = CreateBitmap (ptSize.x, ptSize.y, 1, 1, NULL);

   bmAndMem = CreateCompatibleBitmap (hdc, ptSize.x, ptSize.y);
   bmSave = CreateCompatibleBitmap (hdc, ptSize.x, ptSize.y);

   // Each DC must select a bitmap object to store pixel data.
   bmBackOld = (HBITMAP) SelectObject (hdcBack, bmAndBack);
   bmObjectOld = (HBITMAP) SelectObject (hdcObject, bmAndObject);
   bmMemOld = (HBITMAP) SelectObject (hdcMem, bmAndMem);
   bmSaveOld = (HBITMAP) SelectObject (hdcSave, bmSave);

   // Set proper mapping mode.
   SetMapMode (hdcTemp, GetMapMode (hdc) );

   // Save the bitmap sent here, because it will be overwritten.
   BitBlt (hdcSave, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

   // Set the background color of the source DC to the color.
   // contained in the parts of the bitmap that should be transparent
   cColor = SetBkColor (hdcTemp, cTransparentColor);

   // Create the object mask for the bitmap by performing a BitBlt
   // from the source bitmap to a monochrome bitmap.
   BitBlt (hdcObject, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

   // Set the background color of the source DC back to the original
   // color.
   SetBkColor (hdcTemp, cColor);

   // Create the inverse of the object mask.
   BitBlt (hdcBack, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, NOTSRCCOPY);

   // Copy the background of the main DC to the destination.
   BitBlt (hdcMem, 0, 0, ptSize.x, ptSize.y, hdc, xStartDest, yStartDest, SRCCOPY);

   // Mask out the places where the bitmap will be placed.
   BitBlt (hdcMem, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, SRCAND);

   // Mask out the transparent colored pixels on the bitmap.
   BitBlt (hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcBack, 0, 0, SRCAND);

   // XOR the bitmap with the background on the destination DC.
   BitBlt (hdcMem, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCPAINT);

   // Copy the destination to the screen.
   BitBlt (hdc, xStartDest, yStartDest, ptSize.x, ptSize.y, hdcMem, xStartScr, yStartScr, SRCCOPY);

   // Place the original bitmap back into the bitmap sent here.
   BitBlt (hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcSave, 0, 0, SRCCOPY);

   // Bitmap-Resourcen zurücktauschen und entfernen
   bmAndBack = (HBITMAP) SelectObject (hdcBack, bmBackOld);
   bmAndObject = (HBITMAP) SelectObject (hdcObject, bmObjectOld);
   bmAndMem = (HBITMAP) SelectObject (hdcMem, bmMemOld);
   bmSave = (HBITMAP) SelectObject (hdcSave, bmSaveOld);

   DeleteStackedObject (bmAndBack);
   DeleteStackedObject (bmAndObject);
   DeleteStackedObject (bmAndMem);
   DeleteStackedObject (bmSave);

   // Delete the memory DCs.
   DeleteDC (hdcMem);
   DeleteDC (hdcBack);
   DeleteDC (hdcObject);
   DeleteDC (hdcSave);
   DeleteDC (hdcTemp);
}

//*************************************************************************************************
//
//
//
//*************************************************************************************************
void DrawBitmap (HDC     hdc,
                 HBITMAP hBitmap,
                 int     xStartScr,
                 int     yStartScr,
                 long    cTransparentColor,
                 BOOL    bIncludeBackColor,
                 int     xStartDest,
                 int     yStartDest,
                 long    cTransparentReplaceColor)
{
   if (bIncludeBackColor == FALSE)
   {
      // Transparent das Bitmap malen.
      DrawTransparentBitmap (hdc, hBitmap, xStartScr, yStartScr, cTransparentColor, xStartDest, yStartDest, cTransparentColor);
   }
   else
   {
      // Hintergrund der Bitmaps werden auch bearbeitet
      if (cTransparentColor == cTransparentReplaceColor)
      {
         // Normale Behandlung mit EINMALIGEM Aufruf von BitBlt().
         DrawNoneTransparentBitmap (hdc, hBitmap, xStartScr, yStartScr, xStartDest, yStartDest);
      }
      else
      {
         // Die Transparenz-Hintergrundfarbe durch eine neue Hintergrundfarbe ersetzt.
         DrawTransparentBitmap (hdc, hBitmap, xStartScr, yStartScr, cTransparentColor, xStartDest, yStartDest, cTransparentReplaceColor);
      }
   }
}

//*************************************************************************************************
//
//
//
//*************************************************************************************************
LRESULT CALLBACK ControlKanalProc (HWND hwnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
   switch (wMsg)
   {
      case WM_CREATE:
      {
         CREATESTRUCT *Daten = (CREATESTRUCT *) lParam;
         MoveWindow (hwnd, Daten->x, Daten->y, 22, 30, TRUE);
      }
      break;

      case BBM_SETBITS:
         SetWindowWord (hwnd, 0, (WORD) wParam);
         InvalidateRect (hwnd, NULL, FALSE);
         break;

      case WM_AUSSCHALTEN:
         if (GetWindowWord (hwnd, 0) == 1)
         {
            SetWindowWord (hwnd, 0, 2);
            InvalidateRect (hwnd, NULL, FALSE);
         }

         break;

      case WM_LBUTTONDBLCLK:
         if (!bExperimentIsRunning)
         {
            if ( (GetAsyncKeyState (VK_CONTROL) & 0x8000) )
            {
               UINT iActualPositionInChannelList;
               iActualPositionInChannelList = GetDlgCtrlID (hwnd) - IDD_KAN00;
               HandleLessMoreCountButtons (GetParent (hwnd), IDD_MORE, iActualPositionInChannelList);
            }

            //Einen Kanal wahlfrei an einer Position innerhalb der bestehenden Kanalliste hinzufügen.
            //wird im z.B. Action.c selbst verarbeitet (Msg: WM_DCLICK_L).
            SendMessage (GetParent (hwnd), WM_DCLICK_L, (WPARAM) hwnd, (LPARAM) GetWindowWord (hwnd, 0) );
         }

         break;

      case WM_RBUTTONDBLCLK:
         if (!bExperimentIsRunning)
         {
            //Mehrere Kanäle in der Kanalliste löschen.
            if ( (GetAsyncKeyState (VK_CONTROL) & 0x8000) )
            {
               UINT iActualPositionInChannelList;
               iActualPositionInChannelList = GetDlgCtrlID (hwnd) - IDD_KAN00;

               if (iActualPositionInChannelList > 0)
               {
                  HandleLessMoreCountButtons (GetParent (hwnd), IDD_LESS, iActualPositionInChannelList);
               }
               else
                  //Kanalnummer 0 darf nicht gelöscht werden, daher bis inklusiv Kanalnummer 1 löschen.
               {
                  HandleLessMoreCountButtons (GetParent (hwnd), IDD_LESS, 1);
               }
            }

            SendMessage (GetParent (hwnd), WM_DCLICK_R, (WPARAM) hwnd, (LPARAM) GetWindowWord (hwnd, 0) );
         }

         break;

      case WM_LBUTTONDOWN:
         SendMessage (GetParent (hwnd), WM_CLICK_LDOWN, (WPARAM) hwnd, (LPARAM) GetWindowWord (hwnd, 0) );
         break;

      case WM_LBUTTONUP:
         SendMessage (GetParent (hwnd), WM_CLICK_LUP, (WPARAM) hwnd, (LPARAM) GetWindowWord (hwnd, 0) );
         break;

      case WM_PAINT:
      {
         PAINTSTRUCT ps;
         HDC hdc;
         COLORREF clrBmpBkColor, clrBmpTransparentColor;

         /* Male das Bitmap hBitChannel mit Nummer wParam */
         //Falls clrControlKanalBk == RGB(0,0,0), dann wurde kein Eintrag in der DASYLab.ini für die Kanalleiste-Hintergrundfarbe gefunden.
         if (clrControlKanalBk != RGB (0, 0, 0) )
         {
            //Hintergrund-Farbe für die Kanalleiste aus DASYLab.ini verwenden, falls vorhanden.
            clrBmpBkColor = clrControlKanalBk;
         }
         else
         {
            //Ansonsten als Default-Hintergrundfarbe SystemColors abfragen.
            clrBmpBkColor = GetSysColor (COLOR_3DFACE);
         }

         //Bei neuerer Dll ist Transparenzfarbe weiss (RGB(255,255,255)); bei älteren Dlls grau (RGB(192,192,192)).
         if (iTKVersionsNummer > 0)
         {
            clrBmpTransparentColor = RGB (255, 255, 255);
         }
         else
         {
            clrBmpTransparentColor = RGB (192, 192, 192);
         }

         hdc = BeginPaint (hwnd, &ps);
         DrawBitmap (hdc, hBitChannel[GetWindowWord (hwnd, 0)], 0, 0, clrBmpTransparentColor, TRUE, 0, 0, clrBmpBkColor);
         EndPaint (hwnd, &ps);
      }
      break;

      default:
         return DefWindowProc (hwnd, wMsg, wParam, lParam);
   }

   return (0L);
}

//*************************************************************************************************
//
//
//
//*************************************************************************************************
LRESULT CALLBACK ControlLessMoreProc (HWND hwnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
   switch (wMsg)
   {
      case WM_CREATE:
      {
         CREATESTRUCT *Daten = (CREATESTRUCT *) lParam;
         MoveWindow (hwnd, Daten->x, Daten->y, 24, 32, TRUE);
      }
      break;

      case BBM_SETBITS:
         SetWindowWord (hwnd, 0, (WORD) wParam);
         InvalidateRect (hwnd, NULL, FALSE);
         break;

      case WM_RBUTTONDBLCLK:
         if (!bExperimentIsRunning && (GetAsyncKeyState (VK_CONTROL) & 0x8000) && (GetDlgCtrlID (hwnd) == IDD_LESS) )
         {
            HandleLessMoreCountButtons (GetParent (hwnd), IDD_LESS, wDialNumChan - 1);
         }

         break;

      case WM_LBUTTONDBLCLK:
      {
         // WICHTIG: WM_LBUTTONDBLCLK unmittelbar vor WM_LBUTTONDOWN wegen 'Fallthru'
         if (!bExperimentIsRunning)
         {
            if ( (GetAsyncKeyState (VK_CONTROL) & 0x8000) )
            {
               if (GetDlgCtrlID (hwnd) == IDD_MORE)
               {
                  // HandleLessMoreCountButtons (GetParent (hwnd), IDD_MORE, wDialMaxChan);
                  // 1x weniger, da bereits ein Kanal durch WM_LBUTTONUP in ControlLessMoreProc erzeugt wurde.
                  HandleLessMoreCountButtons (GetParent (hwnd), IDD_MORE, wDialMaxChan - 1);
               }
               else
               {
                  HandleLessMoreCountButtons (GetParent (hwnd), IDD_LESS, 1);
               }

               break;
            }
         }
      }

      // Fallthru - Hier KEIN break; !!!
      case WM_LBUTTONDOWN:
      {
         WORD wDummy = GetWindowWord (hwnd, 0);

         if ( (wDummy != 0) && (wDummy != 3) )
         {
            if (wDummy < 3)
            {
               /* IDD_LESS */
               SetWindowWord (hwnd, 0, 2);
               InvalidateRect (hwnd, NULL, FALSE);
               UpdateWindow (hwnd);
            }
            else
            {
               /* IDD_MORE */
               SetWindowWord (hwnd, 0, 5);
               InvalidateRect (hwnd, NULL, FALSE);
               UpdateWindow (hwnd);
            }

            SetCapture (hwnd);
         }
      }
      break;

      case WM_LBUTTONUP:
      {
         WORD wDummy;

         if (hwnd != GetCapture () )
         {
            break;
         }

         wDummy = GetWindowWord (hwnd, 0);

         if ( (wDummy != 0) && (wDummy != 3) )
         {
            ReleaseCapture ();

            if (wDummy < 3)
            {
               /* IDD_LESS */
               SetWindowWord (hwnd, 0, 1);
               InvalidateRect (hwnd, NULL, FALSE);
               UpdateWindow (hwnd);
               SendMessage (GetParent (hwnd), WM_COMMAND, IDD_LESS, 0);
            }
            else
            {
               /* IDD_MORE */
               SetWindowWord (hwnd, 0, 4);
               InvalidateRect (hwnd, NULL, FALSE);
               UpdateWindow (hwnd);
               SendMessage (GetParent (hwnd), WM_COMMAND, IDD_MORE, 0);
            }
         }
      }
      break;

      case WM_PAINT:
      {
         // Male das Bitmap hBitChannel mit Nummer wParam - 'wParam' entspricht wohl 'GetWindowWord (hwnd, 0)'.
         PAINTSTRUCT ps;
         HDC hdc;
         COLORREF clrBmpBkColor;

         // Falls clrControlKanalBk == RGB(0,0,0), dann wurde kein Eintrag in der DASYLab.ini für die Kanalleiste-Hintergrundfarbe gefunden.
         if (clrControlKanalBk != RGB (0, 0, 0) )
         {
            // Hintergrund-Farbe für die Kanalleiste aus DASYLab.ini verwenden, falls vorhanden.
            clrBmpBkColor = clrControlKanalBk;
         }
         else
         {
            // Ansonsten als Default-Hintergrundfarbe SystemColors abfragen.
            clrBmpBkColor = GetSysColor (COLOR_3DFACE);
         }

         /* Male das Bitmap hBitChannel mit Nummer wParam */
         hdc = BeginPaint (hwnd, &ps);
         DrawBitmap (hdc, hBitLessMore[GetWindowWord (hwnd, 0)], 0, 0, RGB (255, 255, 255), TRUE, 0, 0, clrBmpBkColor);
         EndPaint (hwnd, &ps);
      }
      break;

      default:
         return DefWindowProc (hwnd, wMsg, wParam, lParam);
   }

   return (0L);
}


void SetupInputBitmap (MODULE *ThisModule, UINT wChannel, UINT wIndexNr)
{
   /* Nur sinnvolle Kanalnummern bitte */
   if (wChannel < MAX_CHANNEL)
      ThisModule->r9[wChannel] = (HBITMAP)wIndexNr;
}



void SetupOutputBitmap (MODULE *ThisModule, UINT wChannel, UINT wIndexNr)
{
   /* Nur sinnvolle Kanalnummern bitte */
   if (wChannel < MAX_CHANNEL)
      ThisModule->r12[wChannel] = wIndexNr;
}

//*************************************************************************************************
//
//
//
//*************************************************************************************************

/* -eof- */