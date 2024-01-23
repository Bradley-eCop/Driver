/* ======================================================================== */
/* Programm   :  DLAB -  Messwerterfassung und Verarbeitung unter Windows   */
/* Datei      :  TOOLKIT.H                                                  */
/* ------------------------------------------------------------------------ */
/* Funktionen :  Allgemeine Include-Datei für das DLL-Toolkit               */
/* Letzte Änd.:  12.11.2015 SG                                              */
/* ======================================================================== */

#ifndef _USE_TOOLKIT_
#define _USE_TOOLKIT_
#endif

#ifndef _TOOLKIT_
#define _TOOLKIT_

#ifndef RC_INVOKED
#pragma pack(1)
#endif  /* RC_INVOKED */

// Falls mit einem C++ Compiler übersetzt wird, dafür sorgen, das die Funktionen in C-Syntax gesucht werden.
#ifdef __cplusplus
extern "C" {
#endif


   /* Nur diese zwei Funktionen müssen vom Anwender bereitgestellt werden */
   BOOL Init_DLL (void);
   BOOL Exit_DLL (void);


   /* EXTERN soll vom Anwender niemals definiert werden */
#ifndef EXTERN
# define  EXTERN  extern
#endif

#ifndef CLOCKS_PER_SEC
#  include <time.h>
#endif

   // Noch einige benötigte Funktionen von der 16->32 Bit umstellung
# include "NT32.H"

   /* Erlauben von '//'-Kommentaren */
#pragma warning(disable:4001)             /* Single line comment */

   /* Unbenutzte lokale Variablen bitte entfernen ! */
#pragma warning( error :4101)             /* Unreferenced local variable */

   /* Nameless structs/unions sind Ok */
#pragma warning(disable:4201)             /* Nonstandard extension used : nameless struct/union */

   /* Unbenutzte Parameter müssen mit UNUSED() markiert werden ! */
#ifdef NDEBUG   /* Release-Optionen */
#  pragma warning(disable:4100)           /* Unreferenced formal parameter */
#  define UNUSED(p)
#else           /* Debug-Optionen */
#  pragma warning( error :4100)           /* Unreferenced formal parameter */
#  define UNUSED(p) p=p
#endif


#include "CONST.H"
#include "HELP.H"
#include "TYPES.H"
#include "MODCLASS.H"
#include "TOOLUTIL.H"
#include "MAT_UTIL.H"
#include "STR_UTIL.H"
#include "COMMCTRL.H"


   /* Toolkit-Lib */
   void InitChannelBar (HWND);
   void HandleLessMoreButton (HWND, UINT);
   void HandleChannelClick (HWND, UINT);
   BOOL ModalChooseColor (void *colptr, BOOL bEnableAllWindows, HWND hwndOwner);
   BOOL ModalChooseFont (void *fntptr, BOOL bEnableAllWindows, HWND hwndOwner);

   __declspec(deprecated("CenterDialog is deprecated and has no function. Please delete.")) void CenterDialog (HWND hwnd, HWND hwndOwner);
   void TKCenterDialogColorDlg (HWND hwnd, HWND hwndOwner);
   void TKEnableThemeDialogTexture (HWND hwnd);

   void SetupInputBitmap (MODULE *ThisModule, UINT wChannel, UINT wIndexNr);
   void SetupOutputBitmap (MODULE *ThisModule, UINT wChannel, UINT wIndexNr);
#define MAX_BMP_INDEX 255

   // Globale Variablen aus DASYLab 
   EXTERN HINSTANCE hInst;                 /* DLL's Instanz-Handle ! */
   EXTERN HINSTANCE hInstDlab;             /* DASYLab's Instanz-Handle ! */
   EXTERN BOOL FAR *lpbPauseIsDisabled;
#define bPauseIsDisabled lpbPauseIsDisabled[0]

   EXTERN ICONS  *icons;

   EXTERN BOOL FAR *lpbDisplayWithoutWnd;
#define bDisplayWithoutWnd lpbDisplayWithoutWnd[0]

   EXTERN HPEN hBlackPen;
   EXTERN HPEN hWhitePen;
   EXTERN HPEN hDkGrayPen;
   EXTERN HPEN hPipePenRed;
   EXTERN HPEN hPipePenGreen;
   EXTERN HPEN hPipePenYellow;

   EXTERN HBRUSH hLightRedBrush;
   EXTERN HBRUSH hGreenBrush;
   EXTERN HBRUSH hDkGrayBrush;

   EXTERN UINT wDialCurChan;
   EXTERN UINT wDialNumChan;
   EXTERN UINT wDialMaxChan;
   EXTERN UINT wDialLastFocus;

   EXTERN char ShortTempString[400];
   EXTERN char LongTempString[1024];

   EXTERN void FAR *SingleInfo;

   EXTERN DWORD ofnExplorerFlag;            /* == OFN_EXPLORER oder 0 */

   EXTERN double fGlobalMilliSecondsPerSample;
   EXTERN DWORD dwExperimentStartTimeTicks;
   EXTERN UINT uiGlobalBlockSize;

   EXTERN UINT FAR *lpCurrentModule;
   //08// define CurrentModule lpCurrentModule[0]
   EXTERN MODULE FAR * FAR *lpCurrentModulePtr;
#define CurrentModulePtr lpCurrentModulePtr[0]

   EXTERN BOOL bAnimation;
   EXTERN BOOL bExperimentIsRunning;
   EXTERN BOOL bExperimentIsPaused;

   EXTERN time_t FAR *lpExperimentStartTime;
#define ExperimentStartTime lpExperimentStartTime[0]
   EXTERN long FAR *lpStartingTimeTicks;
#define StartingTimeTicks lpStartingTimeTicks[0]

   EXTERN HWND hwndMain;
   EXTERN HWND FAR *lphwndDesk;
#define hwndDesk lphwndDesk[0]

   EXTERN MODULE FAR * FAR * FAR *lpModule;
   //08// define Module lpModule[0]

   EXTERN MODULE FAR * FAR * FAR *lpViewModule;
   //08// define ViewModule lpViewModule[0]

   EXTERN UINT FAR *lpwNumberOfModules;
#define wNumberOfModules lpwNumberOfModules[0]
   EXTERN UINT FAR *lpuiHighModuleNumber;
#define uiHighModuleNumber lpuiHighModuleNumber[0]

   EXTERN MODULKLASSE FAR *GlobalModuleClass;
   EXTERN MODULKLASSE FAR TempModuleClass;

   EXTERN char FAR *NameOfFlowChart;
   EXTERN char FAR *FullNameOfFlowChart;

   EXTERN char FAR *InitialStartupDir;
   EXTERN char FAR *ExeFileDir;

   EXTERN char FAR *ProgSaveDlabName;

   EXTERN char FAR *ProgFileNameIni;

   EXTERN DWORD FAR *lpDdeInstance;
#define DdeInstance lpDdeInstance[0]

   EXTERN COLORREF *clrUserDefinedColors;
   EXTERN COLORREF *clrUserDefinedColorsDSB;
   EXTERN COLORREF clrControlKanalBk;
   EXTERN FENSTERPARAMETER far *wndpar;

   /* Zwischenergebnisse der Tooltip Routinen, Ro 04/05/95 */
   typedef struct
   {
      HFONT hFont;            /* Font für ToolTip-Text */
      char szText[512];        /* Nächster zu schreibender Text */
      int TextLen;            /* Textlänge des auszugebenden Textes */
      int xText, yText;       /* Position zum Schreiben des Textes */
      int Width, Height;      /* Umschließendes Rechteck */
      int xMargin, yMargin;   /* Zusätzlicher Rand um den Text */
      POINT ptMouse;          /* Letzte gemerkte Maus Position ? */
      BOOL IsVisible;         /* Wird gerade ein Tooltip Fenster angezeigt */
      HWND hWnd;              /* Handle des erzeugten ToolTip Fensters */
      BOOL bTimerIsSet;       /* Timer wurde eingeschaltet */
      BOOL bQuickRedraw;      /* Es wurde schon mal ein ToolTip gezeichnet und die */
      /* Maus hat die Funktionsleiste noch nicht verlassen */
      RECT reActive;          /* Button-Fläche des Buttons, für den ein */
      /* ToolTip aktuell ist */
   } ToolTipTyp;

   EXTERN ToolTipTyp FAR *lpToolTip;
#define ToolTip lpToolTip[0]

   typedef void (TOOLAPI *PROTO_CreateAndShowToolTipWindow) (HWND hwndParent, HMENU hMenu, int MenuId);
   EXTERN PROTO_CreateAndShowToolTipWindow CreateAndShowToolTipWindow;

   EXTERN int FAR *lpnWindowOrder;
#define nWindowOrder lpnWindowOrder[0] /* Merker für Fenster Z-Achsen Anornung */

   /*----- Standard Verzeichnisse --------------*/

   EXTERN char FAR *DefFlowchartDir;
   EXTERN char FAR *DefStreamingDir;
   EXTERN char FAR *DefDataDir;
   EXTERN char FAR *DefDeviceDir;
   EXTERN char FAR *DefUtilityDir;
   EXTERN char FAR *chDefSharedUserDir;


   // Achtung: Neues Interface für Seriennummer
#define NAME_LAENGE 52
#define SERNO_LAENGE 36
#define ADRESS_LAENGE 100

   typedef struct
   {
      char FAR szSerNo[SERNO_LAENGE + 2];
      char FAR szName[NAME_LAENGE + 2];
      char FAR szFirma[NAME_LAENGE + 2];

      char FAR szDistr[ADRESS_LAENGE + 2];
      char FAR szDistrStr[ADRESS_LAENGE + 2];
      char FAR szDistrOrt[ADRESS_LAENGE + 2];
      char FAR szDistrTel[ADRESS_LAENGE + 2];

      UINT SysInfo_VersionsNr;
      DWORD SysInfo_Treiber[2];       /* 64 Bit für Treiber */
      char FAR szVersionsTyp[64];
      UINT uiDistributorTyp;
      UINT uiVersionsTyp;
      BOOL bLayouterSupported;

      char FAR szHersteller[50];
      char SerNo[40];
      unsigned short Hersteller;
      unsigned short Version;
      unsigned short Kunde;
      unsigned short Sprache;
      unsigned short Programm;
      unsigned short Treiber1;
      unsigned short Treiber2;
      unsigned short Release;
      unsigned short MonthYear;
      unsigned short Laufzeit;
      unsigned short Dongle;
      long Optionen;
      long Nummer;

      BOOL bDongelFrei;
      BOOL bInstrunet;
      BOOL bSollWertGen;
      BOOL bDapDll;
      BOOL b10Netz;
      BOOL b20Netz;
      BOOL bDlabNetz;
      BOOL bS5S7;
      BOOL bAddOn1;
      BOOL bRainflow;
      BOOL bIbus;
      BOOL bSoftingCan;
      BOOL bNICan;
      BOOL bDeprecated;
      BOOL bOpc;
      BOOL bSolartron;

      BOOL bNuDAM;   // bReserve1
      BOOL bOmega;   // bReserve2
      BOOL bAdam;    // bReserve3
      BOOL bReserve4;
      BOOL bReserve5;
      BOOL bReserve6;
      BOOL bReserve7;
      BOOL bReserve8;
      BOOL bReserve9;
      BOOL bReserve10;
      BOOL bReserve11;
      BOOL bReserve12;
      BOOL bReserve13;
      BOOL bReserve14;
      BOOL bReserve15;
      BOOL bReserve16;

   } SERIAL_OPT;

   EXTERN SERIAL_OPT *lpSerialOpt;
#define SerialOpt lpSerialOpt[0]

   typedef struct
   {
      BOOL AO_Async;
      BOOL DO_Async;
      BOOL AO_FillOnce;
      BOOL DO_FillOnce;
      UINT AO_FreqFaktor;
      UINT DO_FreqFaktor;
      UINT AO_StartDelay;
      UINT DO_StartDelay;
   } LAYER_OUTPUT_PARAM;

   EXTERN LAYER_OUTPUT_PARAM *lpLAYER_OutputParam;
#define LAYER_OutputParam lpLAYER_OutputParam[0]

   typedef struct
   {
      BOOL bStreamOn;
      char StreamingFile[300];           /* Aktuelle Datei für Disk Streaming */
      BOOL bWarning;
      BOOL bWriteProtect;
      BOOL bRing;
      long lRingSamples;
      BOOL bTwoFiles;
      BOOL bAnyChannelsConnected;
      int iReserved[20];                 /* 40 Bytes für späteren Gebrauch */
   } STREAMOPTIONEN;

   EXTERN STREAMOPTIONEN *lpStreamOptionen;
#define StreamOptionen lpStreamOptionen[0]

   EXTERN STREAMOPTIONEN * *lpTempStreamOptionen;
#define TempStreamOptionen lpTempStreamOptionen[0]

   /* Cold-Junction-Compensation for Thermo Element measurement */
   EXTERN double *lpCJ_Temp;    /* Compensation Temperature in Centigrade */
#define CJ_Temp lpCJ_Temp[0]
   EXTERN UINT *lpCJ_Refs;     /* number of modules that need the CJ_Temp */
#define CJ_Refs lpCJ_Refs[0]

   /*----- Datums und Zeitformat ---------------*/
   EXTERN BOOL bDateDayLeadingZero;
   EXTERN BOOL bDateMonthLeadingZero;
   EXTERN BOOL bDateYearLong;
   EXTERN UINT wDateFormat;
   EXTERN BOOL bTime24h;
   EXTERN BOOL bTimeLeadingZero;
   EXTERN char FAR *TimeTrenn;
   EXTERN char FAR *DezTrenn;
   EXTERN BOOL bDecLeadingZero;
   EXTERN char FAR *DateTrenn;

#define iBmpKanalX 18

   /*-------------------------------------------*/

   EXTERN struct
   {
      char FAR *Author;
      char FAR *Company;
      char FAR *Department;
      char FAR *Title;
      char FAR *Info;
   } GlobalFlowChartInfo;

   EXTERN UINT wxScreen, wyScreen;

#if 0
   EXTERN struct {
      UINT wxScreen;
      UINT wyScreen;
   } FAR *wndpar;
#endif


   EXTERN HMENU MainMenu;

   /* EXTERN UINT uiSelectedModule;             / * FIXME !!! */
   EXTERN MODULE FAR *BBoxModul;     /* FIXME !!! */

   typedef void (TOOLAPI *PROTO_DefineModuleClassEx) (MODULKLASSE FAR *Class, UINT ClassSize);
   EXTERN PROTO_DefineModuleClassEx DefineModuleClassEx;

   typedef BOOL (TOOLAPI *PROTO_DefineDllModule) (void);
   typedef BOOL (TOOLAPI *PROTO_DefineDllVariable) (char FAR *VarName,
                                                    void FAR *VarAddress,
                                                    UINT VarSize);

   /* Importe aus DASYLab */
   EXTERN PROTO_DefineDllModule DefineDllModule;
   EXTERN PROTO_DefineDllVariable DefineDllVariable;

   typedef void (TOOLAPI *PROTO_BBox_FullEnter) (MODULE FAR *ThisModule, BOOL bRedraw);
   typedef void (TOOLAPI *PROTO_BBox_FullLeave) (MODULE FAR *ThisModule, BOOL bRedraw);

   EXTERN PROTO_BBox_FullEnter    BBox_FullEnter;
   EXTERN PROTO_BBox_FullLeave BBox_FullLeave;

   typedef void (TOOLAPI *PROTO_BBox_LightEnter) (MODULE FAR *ThisModule);
   typedef void (TOOLAPI *PROTO_BBox_LightLeave) (MODULE FAR *ThisModule);

   EXTERN PROTO_BBox_LightEnter    BBox_LightEnter;
   EXTERN PROTO_BBox_LightLeave    BBox_LightLeave;

   typedef BOOL (TOOLAPI *PROTO_CreateSatellite) (MODULE FAR *IoModule, char FAR *SatClassName);
   typedef BOOL (TOOLAPI *PROTO_UpdateSatellite) (MODULE FAR *SatModule);
   typedef void (TOOLAPI *PROTO_RemoveUselessSatellites) (void);
   EXTERN PROTO_CreateSatellite            CreateSatellite;
   EXTERN PROTO_UpdateSatellite            UpdateSatellite;
   EXTERN PROTO_RemoveUselessSatellites    RemoveUselessSatellites;

   typedef BOOL (TOOLAPI *PROTO_RegisterModuleClass) (MODCLASS FAR *modclass);
   typedef unsigned long (TOOLAPI *PROTO_PerformDefaultAction) (MODULE FAR *ThisModule, int wMsg, int wParam, long lParam);

   EXTERN PROTO_RegisterModuleClass    RegisterModuleClass;
   EXTERN PROTO_PerformDefaultAction   PerformDefaultAction;

   typedef unsigned long (TOOLAPI *PROTO_SendModuleMessage) (MODULE *ThisModule, int wMsg, int wParam, long lParam);
   EXTERN PROTO_SendModuleMessage      SendModuleMessage;

   typedef unsigned long (TOOLAPI *PROTO_SendModChanMessage) (MODULE *ThisModule, int wMsg, int wParam, long lParam);
   EXTERN PROTO_SendModChanMessage      SendModChanMessage;

   typedef BOOL (TOOLAPI *PROTO_ChangeModuleName) (MODULE *ThisModule, LPSTR szNewName);
   EXTERN PROTO_ChangeModuleName     ChangeModuleName;

   typedef BOOL (TOOLAPI *PROTO_ChangeNameInString) (LPSTR szString, UINT uiStringLength, LPSTR szFrom, LPSTR szTo);
   EXTERN PROTO_ChangeNameInString   ChangeNameInString;

   typedef char * (TOOLAPI *PROTO_ScanStringForGlobals) (char *Source, UINT *pType, short *pIndex);
   EXTERN PROTO_ScanStringForGlobals ScanStringForGlobals;

   typedef void (TOOLAPI *PROTO_CopyChannelName) (FIFO_HEADER * Fifo, LPSTR *chBezeichnung);
   EXTERN PROTO_CopyChannelName      CopyChannelName;

   typedef void (TOOLAPI *PROTO_FillUnitList) (HWND hDlg, UINT nListId, LPSTR SetString);
   EXTERN PROTO_FillUnitList      FillUnitList;

   typedef void (TOOLAPI *PROTO_ExpandUnit) (MODULE *ThisModule, UINT wFifoNr, UINT wStartChannel);
   EXTERN PROTO_ExpandUnit      ExpandUnit;


   /* DRUCKEN */
   typedef struct
   {
      HDC dc;
      int LogPixelsX;
      int LogPixelsY;
      RECT reHeader;
      RECT reData;
      RECT reInfo;
      RECT reFooter;
   } DruckInfo;

   typedef BOOL (TOOLAPI *PROTO_InitPrinter) (DruckInfo FAR *di, BOOL ErstFragen);
   typedef BOOL (TOOLAPI *PROTO_ExitPrinter) (DruckInfo FAR *di);
   typedef BOOL (TOOLAPI *PROTO_PrintHeader) (DruckInfo FAR *di, char FAR *Bezeichnung);
   typedef BOOL (TOOLAPI *PROTO_PrintFooter) (DruckInfo FAR *di);
   typedef BOOL (TOOLAPI *PROTO_NextPage) (DruckInfo FAR *di);
   EXTERN PROTO_InitPrinter    InitPrinter;
   EXTERN PROTO_ExitPrinter    ExitPrinter;
   EXTERN PROTO_PrintHeader    PrintHeader;
   EXTERN PROTO_PrintFooter    PrintFooter;
   EXTERN PROTO_NextPage       NextPage;

   typedef HFILE (TOOLAPI *PROTO_CheckedCreateFile) (void FAR *name, int attrib, MODULE * ThisModule);
   EXTERN PROTO_CheckedCreateFile CheckedCreateFile;
   typedef HFILE (TOOLAPI *PROTO_CheckedOpenFile) (void FAR * name, OFSTRUCT far * x, int mode, MODULE * ThisModule);
   EXTERN PROTO_CheckedOpenFile CheckedOpenFile;


   typedef BOOL (TOOLAPI *PROTO_LoadInterpolationTable) (void FAR *Tabelle, char FAR *DateiName,
                                                         int FAR *ErrorCode, char FAR *TabellenText);
   EXTERN PROTO_LoadInterpolationTable    LoadInterpolationTable;

   typedef BOOL (TOOLAPI *PROTO_LoadTableFromFile) (void FAR *Tabelle, char FAR *DateiName,
                                                    char FAR *FirstLine, int NumColumns,
                                                    int FAR *ErrorCode, char FAR *TabellenText);
   EXTERN PROTO_LoadTableFromFile    LoadTableFromFile;
   typedef BOOL (TOOLAPI *PROTO_SearchForFileToLoad) (char* szFileName, char* szDefDir,
                                                      char* szWorksheetDir, char* szModuleName, BOOL bShowMsgBox);
   EXTERN PROTO_SearchForFileToLoad SearchForFileToLoad;

   typedef BOOL (TOOLAPI *PROTO_AskForFilenameChange) (char* szFilenameOld,
                                                       char* szFilenameNew, BOOL bMoreFiles);
   EXTERN PROTO_AskForFilenameChange AskForFilenameChange;

   typedef BOOL (TOOLAPI *PROTO_CheckCreateDir) (const char *szFileAndPath, const BOOL bCheckGlobalFlag);
   EXTERN PROTO_CheckCreateDir CheckCreateDir;

   typedef BOOL (TOOLAPI *PROTO_DoesFileExistAndMsg) (char* szFile, char* szModuleName, BOOL bShowMsg);
   EXTERN PROTO_DoesFileExistAndMsg DoesFileExistAndMsg;

   typedef unsigned long (TOOLAPI *PROTO_SendPanelMessage) (HPANEL hPanel, int wMsg, int wParam, long lParam);
   EXTERN PROTO_SendPanelMessage    SendPanelMessage;


   /* GDI-Stack */
   typedef HPEN (TOOLAPI *PROTO_CreateStackedPen) (int fPenStyle, int nWidth, COLORREF clrref);
   EXTERN PROTO_CreateStackedPen    CreateStackedPen;

   typedef HPEN (TOOLAPI *PROTO_CreateStackedPenIndirect) (LPLOGPEN plpen);
   EXTERN PROTO_CreateStackedPenIndirect    CreateStackedPenIndirect;

   typedef HFONT (TOOLAPI *PROTO_CreateStackedFontIndirect) (LPLOGFONT lplf);
   EXTERN PROTO_CreateStackedFontIndirect    CreateStackedFontIndirect;

   typedef HBRUSH (TOOLAPI *PROTO_CreateStackedSolidBrush) (COLORREF col);
   EXTERN PROTO_CreateStackedSolidBrush    CreateStackedSolidBrush;

   typedef HBRUSH (TOOLAPI *PROTO_CreateStackedBrushIndirect) (LPLOGBRUSH lpbr);
   EXTERN PROTO_CreateStackedBrushIndirect    CreateStackedBrushIndirect;

   typedef BOOL (TOOLAPI *PROTO_DeleteStackedObject) (HANDLE h);
   EXTERN PROTO_DeleteStackedObject    DeleteStackedObject;

   typedef BOOL (TOOLAPI *PROTO_ExpandString) (char *Source, int MaxSourceSize,
                                               char *Destination, int MaxDestSize);
   EXTERN PROTO_ExpandString    ExpandString;
   typedef BOOL (TOOLAPI *PROTO_ExpandStringNumber) (char *Source, int MaxSourceSize,
                                                     short *Number);
   EXTERN PROTO_ExpandStringNumber ExpandStringNumber;
   typedef BOOL (TOOLAPI *PROTO_ExpandVarNumber) (char *Source, int MaxSourceSize,
                                                  short *Number);
   EXTERN PROTO_ExpandVarNumber    ExpandVarNumber;

   typedef BOOL (TOOLAPI *PROTO_GlStr_Set) (short Number, char *GlText, int MaxSize);
   EXTERN PROTO_GlStr_Set    GlStr_Set;
   typedef BOOL (TOOLAPI *PROTO_GlStr_Get) (short Number, char *GlText, int MaxSize);
   EXTERN PROTO_GlStr_Get    GlStr_Get;
   typedef BOOL (TOOLAPI *PROTO_GlStr_PrefixGet) (short Number, char *GlText, int MaxSize);
   EXTERN PROTO_GlStr_PrefixGet  GlStr_PrefixGet;
   typedef BOOL (TOOLAPI *PROTO_GlVar_Set) (short Number, double GlValue);
   EXTERN PROTO_GlVar_Set    GlVar_Set;
   typedef BOOL (TOOLAPI *PROTO_GlVar_Get) (short Number, double *GlValue);
   EXTERN PROTO_GlVar_Get GlVar_Get;
   typedef BOOL (TOOLAPI *PROTO_GlVar_PrefixGet) (short Number, char *GlText, int MaxSize);
   EXTERN PROTO_GlVar_PrefixGet  GlVar_PrefixGet;
   typedef BOOL (TOOLAPI *PROTO_GlVar_VarStringGet) (short Number, char *GlText);
   EXTERN PROTO_GlVar_VarStringGet  GlVar_VarStringGet;
   typedef BOOL (TOOLAPI *PROTO_GlStr_SetSyntax) (char *szDest, short nNumber);
   EXTERN PROTO_GlStr_SetSyntax GlStr_SetSyntax;
   typedef BOOL (TOOLAPI *PROTO_GlVar_SetSyntax) (char *szDest, short nNumber);
   EXTERN PROTO_GlStr_SetSyntax GlVar_SetSyntax;
   typedef void (TOOLAPI *PROTO_SetMenuForGlobalStrings) (HWND hDlg, UINT wID);
   EXTERN PROTO_SetMenuForGlobalStrings SetMenuForGlobalStrings;
   typedef void (TOOLAPI *PROTO_SetMenuForGlobalVars) (HWND hDlg, UINT wID);
   EXTERN PROTO_SetMenuForGlobalVars SetMenuForGlobalVars;
   typedef void (TOOLAPI *PROTO_DeleteMenuForGlobalStrings) (HWND hDlg, UINT wID);
   EXTERN PROTO_DeleteMenuForGlobalStrings DeleteMenuForGlobalStrings;
   typedef void (TOOLAPI *PROTO_DeleteMenuForGlobalVars) (HWND hDlg, UINT wID);
   EXTERN PROTO_DeleteMenuForGlobalVars DeleteMenuForGlobalVars;
   typedef void (TOOLAPI *PROTO_ShowVarsAndSelect) (HWND hwndParent, BOOL bReplaceAll);
   EXTERN PROTO_ShowVarsAndSelect ShowVarsAndSelect;

   typedef BOOL (TOOLAPI *PROTO_GlStr_RegisterByNumber) (short Number, void *ObjectPtr,
                                                         unsigned long (*UpdateFunction) (void *ObjectPtr,
                                                         int wMsg, int wParam, long lParam));
   EXTERN PROTO_GlStr_RegisterByNumber  GlStr_RegisterByNumber;

   typedef BOOL (TOOLAPI *PROTO_GlStr_RegisterByText) (char *theText, void *ObjectPtr,
                                                       unsigned long (*UpdateFunction) (void *ObjectPtr,
                                                       int wMsg, int wParam, long lParam));
   EXTERN PROTO_GlStr_RegisterByText  GlStr_RegisterByText;

   typedef BOOL (TOOLAPI *PROTO_GlStr_UnregisterByNumber) (short Number, void *ObjectPtr,
                                                           unsigned long (*UpdateFunction) (void *ObjectPtr,
                                                           int wMsg, int wParam, long lParam));
   EXTERN PROTO_GlStr_UnregisterByNumber  GlStr_UnregisterByNumber;

   typedef BOOL (TOOLAPI *PROTO_GlStr_UnregisterByText) (char *theText, void *ObjectPtr,
                                                         unsigned long (*UpdateFunction) (void *ObjectPtr,
                                                         int wMsg, int wParam, long lParam));
   EXTERN PROTO_GlStr_UnregisterByText  GlStr_UnregisterByText;

   typedef BOOL (TOOLAPI *PROTO_GlVar_RegisterByNumber) (short Number, void *ObjectPtr,
                                                         unsigned long (*UpdateFunction) (void *ObjectPtr,
                                                         int wMsg, int wParam, long lParam));
   EXTERN PROTO_GlVar_RegisterByNumber  GlVar_RegisterByNumber;

   typedef BOOL (TOOLAPI *PROTO_GlVar_UnregisterByNumber) (short Number, void *ObjectPtr,
                                                           unsigned long (*UpdateFunction) (void *ObjectPtr,
                                                           int wMsg, int wParam, long lParam));
   EXTERN PROTO_GlVar_UnregisterByNumber  GlVar_UnregisterByNumber;

   typedef void (TOOLAPI *PROTO_DsbHasChanged) (void);
   EXTERN PROTO_DsbHasChanged      DsbHasChanged;

   typedef void (TOOLAPI *PROTO_RegisterMenuEntry) (UINT MenuId, void (*CallFunction) (void));
   EXTERN PROTO_RegisterMenuEntry  RegisterMenuEntry;

   typedef void (TOOLAPI *PROTO_ExpandUnitString) (char *Destination, char *UnitFormula,
                                                   MODULE *ThisModule, UINT wStartChannel);
   EXTERN PROTO_ExpandUnitString  ExpandUnitString;

   typedef void (TOOLAPI *PROTO_DispatchQueuedMessages) (void);
   EXTERN PROTO_DispatchQueuedMessages  DispatchQueuedMessages;

   EXTERN DAP_SETUP FAR * DapSetup;

   typedef MODULE FAR * (TOOLAPI *PROTO_FindModuleByName) (LPSTR ModuleName);
   EXTERN PROTO_FindModuleByName  FindModuleByName;

   typedef BOOL (TOOLAPI *PROTO_RegisterExtraMemory) (char *Kennung, void *pExtMem, long groesse, PARAMETER_INFO *ExtraMemParms, int NumStructures);
   EXTERN PROTO_RegisterExtraMemory  RegisterExtraMemory;

   typedef BOOL (TOOLAPI *PROTO_AddExtMemInstance) (char *Kennung);
   EXTERN PROTO_AddExtMemInstance  AddExtMemInstance;

   typedef BOOL (TOOLAPI *PROTO_RemoveExtMemInstance) (char *Kennung);
   EXTERN PROTO_RemoveExtMemInstance  RemoveExtMemInstance;

   typedef BOOL (TOOLAPI *PROTO_RegisterNewWorksheetNotification) (void (CALLBACK* NewWorksheetNotification)(void));
   EXTERN PROTO_RegisterNewWorksheetNotification  RegisterNewWorksheetNotification;


   /* ------------------- */
   /* Time Base Functions */
   /* ------------------- */

   typedef void (TOOLAPI *PROTO_RegisterTimeBase) (LPSTR szName, UINT uiID, LPSTR szDescription, void (CALLBACK *SetDriver) (EXT_TIMEBASE *pExtBase), BOOL bTemporary);
   EXTERN PROTO_RegisterTimeBase RegisterTimeBase;

   typedef void (TOOLAPI *PROTO_UnregisterTimeBase) (UINT uiID);
   EXTERN PROTO_UnregisterTimeBase UnregisterTimeBase;

   typedef BOOL (TOOLAPI *PROTO_SetTimeBase) (EXT_TIMEBASE *pExtBase);
   EXTERN PROTO_SetTimeBase SetTimeBase;

   typedef void (TOOLAPI *PROTO_SetTimeBaseTime) (UINT uiID, double fTime);
   EXTERN PROTO_SetTimeBaseTime SetTimeBaseTime;

   typedef void (TOOLAPI *PROTO_IncTimeBaseTime) (UINT uiID, double fAddTime);
   EXTERN PROTO_IncTimeBaseTime IncTimeBaseTime;

   typedef UINT (TOOLAPI *PROTO_GetTimeBaseBlockSize) (UINT uiID);
   EXTERN PROTO_GetTimeBaseBlockSize GetTimeBaseBlockSize;

   typedef double (TOOLAPI *PROTO_GetTimeBaseSampleDistance) (UINT uiID);
   EXTERN PROTO_GetTimeBaseSampleDistance GetTimeBaseSampleDistance;

   typedef double (TOOLAPI *PROTO_GetTimeBaseTime) (UINT uiID);
   EXTERN PROTO_GetTimeBaseTime GetTimeBaseTime;

   typedef void (TOOLAPI *PROTO_FillTimeBaseCombo) (HWND hDlg, UINT uiIdCombo, UINT uiIDSel);
   EXTERN PROTO_FillTimeBaseCombo FillTimeBaseCombo;

   typedef UINT (TOOLAPI *PROTO_GetTimeBaseComboID) (UINT uiSel);
   EXTERN PROTO_GetTimeBaseComboID GetTimeBaseComboID;

   typedef BOOL (TOOLAPI *PROTO_TimeBaseDialog) (HWND hwndParent, UINT uiID);
   EXTERN PROTO_TimeBaseDialog TimeBaseDialog;

   typedef int (TOOLAPI *PROTO_GlvoModuleNotifyGlobalVar) (GLVO_MODULE_NOTIFY_PARAM* pParam);
   EXTERN PROTO_GlvoModuleNotifyGlobalVar GlvoModuleNotifyGlobalVar;

   typedef BOOL (TOOLAPI *PROTO_DASYLabInsertMenu) (char* pszDlabMenuStruct);
   EXTERN PROTO_DASYLabInsertMenu DASYLabInsertMenu;

#if 1
   typedef HWND (TOOLAPI *PROTO_CreateDispWindow) (LPCTSTR lpClassName,  // registered class name
                                                   LPCTSTR lpWindowName, // window name
                                                   DWORD dwStyle,        // window style
                                                   int x,                // horizontal position of window
                                                   int y,                // vertical position of window
                                                   int nWidth,           // window width
                                                   int nHeight,          // window height
                                                   HWND hWndParent,      // handle to parent or owner window
                                                   HMENU hMenu,          // menu handle or child identifier
                                                   HINSTANCE hInstance,  // handle to application instance
                                                   LPVOID lpParam);
   EXTERN PROTO_CreateDispWindow CreateDispWindow;
#endif

   typedef HWND (TOOLAPI *PROTO_CreateAToolBarDisplayEx) (HWND hWndParent, int iNumImages, TBBUTTON * tbButtonsCreate, int iAnztbButtonsCreate, HBITMAP hbmNormal, HBITMAP hbmGrey);
   EXTERN PROTO_CreateAToolBarDisplayEx CreateAToolBarDisplayEx;

   typedef void (TOOLAPI *PROTO_DeleteAToolBarDisplayEx) (HWND hToolbar);
   EXTERN PROTO_DeleteAToolBarDisplayEx DeleteAToolBarDisplayEx;

   typedef void (TOOLAPI *PROTO_CheckWindowPosition) (HWND hwnd, MODULE *ThisModule);
   EXTERN PROTO_CheckWindowPosition CheckWindowPosition;

#ifndef __cplusplus
#define  CreatePen           Use_CreateStackedPen_Instead
#define  CreatePenIndirect   Use_CreateStackedPenIndirect_Instead
#ifndef WIN32
#define  CreateFontIndirect  Use_CreateStackedFontIndirect_Instead
#endif
#define  DeleteObject        Use_DeleteStackedObject_Instead
#endif

#ifdef __cplusplus
}
#endif

#ifndef RC_INVOKED
#pragma pack()
#endif  /* RC_INVOKED */


#endif /* ndef _TOOLKIT_ */

/* -eof- */

