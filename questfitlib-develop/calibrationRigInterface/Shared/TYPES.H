
/* ======================================================================== */
/* Program    :  DASYLab                                                    */
/* Module     :  TYPES.H                                                    */
/* ------------------------------------------------------------------------ */
/* Function   :  all visible types for DLL Toolkit                          */
/* Author     :  Rottmann / Magolei ab 02.04.92                             */
/* ======================================================================== */

// Some Changes for Dasylab 2016 : MX_SG Oct 2015

/* ------------------------------------------------------------------------ */
/* Global Constants                                                         */
/* ------------------------------------------------------------------------ */

#define  MAX_MODULES                   256 /* max. number of modules */
#define  MAX_MODULE_CLASSES            300 /* max. number of module classes */
#define  MAX_COPY                      16  /* max. number of user for one FIFO */
#define  MAX_CHANNEL                   16  /* max. number of outputs */
#define  MAX_CHANNEL                   16  /* max. number of inputs */
#define  MAX_CHANNEL                   16  /* max. number of channels */
#define  MAX_SYNC_ACTIONS              16  /* max. number of synchronous actions for each module */
#define  MAX_PANEL_CONNECTIONS         32  /* max. number of panel connections for each module */
#define  ANZ_ABZWEIGE                  2   /* */
#define  CHANNEL_NAME_LENGTH           20  /* max. number of characters for channel name */
#define  MAX_UNIT_LEN                  64  /* max. number of characters for units */
#define  MODULE_NAME_LENGTH            12  /* max. number of characters for module name */
#define  MODULE_STATUS_LENGTH          40  /* max. number of characters for status string */
#define  MODULE_DESCRIPTION_LENGTH     40  /* max. number of characters for module description */
#define  MAX_DLL                       40  /* max. number of DLLs to load */

#define  NO_MODULE                     0xffff
#define  RUNTT_X                       345
#define  RUNTT_Y                       125
#define  MAX_X                         (unsigned) 250
#define  MAX_Y                         (unsigned) 250
#define  MAXLISTENELEMENTE             1000
#define  MAXFONT                       30
#define  MAXSIZE                       20

#define M_E                            2.71828182845904523536
#define M_LOG2E                        1.44269504088896340736
#define M_LOG10E                       0.434294481903251827651
#define M_LN2                          0.693147180559945309417
#define M_LN10                         2.30258509299404568402
#define M_PI                           3.14159265358979323846
#define M_PI_2                         1.57079632679489661923
#define M_PI_4                         0.785398163397448309616
#define M_1_PI                         0.318309886183790671538
#define M_2_PI                         0.636619772367581343076
#define M_1_SQRTPI                     0.564189583547756286948
#define M_2_SQRTPI                     1.12837916709551257390
#define M_SQRT2                        1.41421356237309504880
#define M_SQRT_2                       0.707106781186547524401
#define M_ZWEI_PI                      (2.0 * M_PI)
#define M_1K5_PI                       (3.0 * M_PI_2)



/* ------------------------------------------------------------------------ */
/* Channel Types                                                            */
/* Changes forbidden                                                        */
/* ------------------------------------------------------------------------ */

#define  KT_NORMAL    0         /* Standard data channel */
#define  KT_BINARY    1         /* TTL-coded binary data */
#define  KT_SPEC      10        /* Spectral data, full length */
#define  KT_SPEC2     11        /* Spectral data, half length */
#define  KT_SPEC3     12        /* Spectral data, half length + 1 */
#define  KT_SPEC4     13        /* Spectral data, symmetric X-axis */
#define  KT_TERZ      14        /* Spectral data, Third analysis */
#define  KT_OCT       15        /* Spectral data, Octave analysis */
#define  KT_CLASS     20        /* Histogram data without time information */
#define  KT_CLASS2    21        /* Histogram data with time information and new class setup */
#define  KT_DIG_WORD  30        /* Digital-WORD from 0.0 through 65535.0 */



/* ------------------------------------------------------------------------ */
/* Channel Flags                                                            */
/* Changes forbidden                                                        */
/* ------------------------------------------------------------------------ */

#define  KF_NORMAL     0x0000   /* Default */
#define  KF_HOLES      0x0001   /* Gaps in the data can occur */
#define  KF_SHORT_BLK  0x0002   /* Short blocks can occur */
#define  KF_ASYNC      0x0004   /* For future use: asyncronous data */
#define  KF_COPY_PART  0x0FFF   /* Part which is sent to structure test */
#define  KF_READY      0x1000   /* Part which is not sent to structure test */
#define  KF_DELAY      0x2000   /* Part which is not sent to structure test */

/* ------------------------------------------------------------------------ */
/* Channel Relations                                                        */
/* Changes forbidden                                                        */
/* ------------------------------------------------------------------------ */

#define  KZ_NORMAL     0
#define  KZ_2_1        1
#define  KZ_1_2        2
#define  KZ_2_2        3
#define  KZ_1_ALL      4
#define  KZ_ALL_1      5
#define  KZ_1_LESS     6
#define  KZ_DELAY      7
#define  KZ_BBOX       8
#define  KZ_BBOXIO     9
#define  KZ_BBOXSAT   10
#define  KZ_2_1_FIRST 11
#define  KZ_NONE      12
#define  KZ_ALL_ALL   13



/* ------------------------------------------------------------------------ */
/* DASYLab Data Type                                                        */
/* Changes forbidden                                                        */
/* Since Dasylab 14, this is double.                                        */
/* ------------------------------------------------------------------------ */

typedef double DLAB_FLOAT;
#define  DLAB_FLOAT_MAX      DBL_MAX                // Groesste Zahl
#define  DLAB_FLOAT_MIN      DBL_MIN                // Kleinste positive Zahl
#define  DLAB_FLOAT_EPSILON  DBL_EPSILON            // 1 - ( Kleinste Zahl > 1 )
#define  ALMOST_ZERO  1E-200                        // Kleiner als kleinste darstellbare Zahl

typedef DLAB_FLOAT* lpDLAB_FLOAT;

// Dasylab file formats still uses float
typedef float DLAB_DATAFILE_FLOAT;

/* ------------------------------------------------------------------------ */
/* Type: DATA_BLOCK_HEADER                                                  */
/* ------------------------------------------------------------------------ */

typedef struct
{
   HANDLE r1;              /* Reserved for internal use */
   WORD r2;                /* Reserved for internal use */
   WORD r3;                /* Reserved for internal use starting at DASYLab 14 */
   double fStartTime;      /* Start time of a block in secondes since start   */
                           /* of experiment. Value has to be passed for all   */
                           /* connected modules!                              */
   double fSampleDistance; /* Time in seconds between single data values   */
                           /* of a data block. This value is changed by e.g.  */
                           /* average module, standard module like CHAN + CHAN*/
                           /* pass this value                                 */
   UINT uiBlockSize;       /* Number of samples in a block. Value has to be   */  // changed from WORD to UINT !!
                           /* passed or changed of the module.                */
   DLAB_FLOAT Data[1];     /* Easy Data access to block. Start adress of the  */
                           /* block which should be processed.                */
} DATA_BLOCK_HEADER;


/* ------------------------------------------------------------------------ */
/* Type Definitions for static and dynamic Extra Memory (new in DASYLab 15) */
/* ------------------------------------------------------------------------ */

typedef struct
{
   BYTE b[4];
} EMEM_HANDLE;


typedef union
{
   BYTE a[4];
   BYTE b[4];
} EMEM_START;


typedef struct
{
   BYTE b[24];
} EMEM_ORGA;


/* ------------------------------------------------------------------------ */
/* Type: FIFO_HEADER                                                        */
/* ------------------------------------------------------------------------ */

typedef struct
{
   /* DASYLab Memory Management */
   UINT     uiMaxBlockSize;      /* Max. block size  : name has changed, tyme was already ok*/
   double   fSampleDistance;     /* Sample distance */
   WORD     ChannelType;         /* Data Types in Fifo. See type description above  */
                                 /* KT_NORMAL, KT_BINARY, KT_SPECx, KT_CLASS, ...   */
   WORD     ChannelFlags;        /* Channel Flags in Fifo                           */
                                 /* OR-Combination of the flags, see description above */
                                 /* KF_HOLES, KF_SHORT_BLK, ...                     */

   /* Reserved for internal use only ! never ever change something in this region */
   UINT r1;
   UINT r2;
   BOOL _bComputing;
   void* r4;
   void* r5;
   void* r6;
   HANDLE r7;
   UINT wAnzUser;
   DATA_BLOCK_HEADER FAR *r9[MAX_COPY];
   WORD r10;
   BOOL bAusgDirekt[MAX_COPY][ANZ_ABZWEIGE];
   HANDLE r12[MAX_COPY];
   HBITMAP r13[MAX_COPY];
   UINT r14[MAX_COPY];
   UINT r15[MAX_COPY];
   UINT r16[MAX_COPY];
   UINT wAusgModulNr[MAX_COPY][ANZ_ABZWEIGE];
   UINT wAusgKanalNr[MAX_COPY][ANZ_ABZWEIGE];
   POINT r19;
   RECT r20;
   UINT r21[MAX_COPY];
   UINT r22[MAX_COPY][ANZ_ABZWEIGE];
   /* End internal use */

#define FIFO_HIDDEN (sizeof(double)+sizeof(double)+sizeof(HWND)+sizeof(UINT)+sizeof(long)+3*sizeof(double)+sizeof(UINT)+sizeof(char)*MAX_UNIT_LEN+sizeof(DWORD)+(sizeof(char)*13)+(sizeof(UINT))+(sizeof(BOOL))+2*sizeof(EMEM_ORGA)+2*sizeof(void*))
   double X_Min;        /* Histogram and FFT: 1. Time Value in data block */
   double X_Max;        /* Histogram and FFT: Last time value in a block */
   HWND hwndModule;     /* Handle to the module's window */

   /* Variables used for Fifo-Info-Window */
   WORD     wRealBlockSize;
   long     lCntBlocks;
   double   fStartTimeLastBlock;
   double   fStartTimePreLastBlock;
   double   fAktValue;
   UINT     wPossibleFifoBlocks;

   char     Unit[MAX_UNIT_LEN];   /* Unit */
   DWORD    dwTimeNullBlocks;     /* Number of Nulls when requesting an output block */
   char     ModuleName[13];       /* Module name */

   UINT nCurrentCountBlocks;  // Aktuelle Anzahl der Blöcke im Fifo

   BOOL bBlockingWarningDone; // TRUE, wenn für diesen Fifo bereits einmal eine Warnung ausgegeben wurde, dass ein Modul den Datenstrom blockiert.

   // Verwaltung für dynamisches und statisches Extra Memory - 
   EMEM_ORGA EmemFifo;
   void* EmemCopyFifo;

   EMEM_ORGA EmemBlock;
   void* EmemCopyBlock;
} FIFO_HEADER;

// MHa 04.01.2011 - Profiler Erweiterungen
#define MAX_PROFILER_HISTOGRAM_CLASS                                      10+2

typedef struct
{
   // DCM_SETUP_FIFO
   LARGE_INTEGER tSetupFifoTime;

   // DMM_PREPARE_START_MODULE
   LARGE_INTEGER tPrepareStartTime;
   LARGE_INTEGER tDelayToPrepareStartTime;
   __int64 i64DelayToPrepareStartTimePos;

   // DMM_START_MODULE
   LARGE_INTEGER tStartTime;
   LARGE_INTEGER tDelayToStartTime;
   __int64 i64DelayToStartTimePos;

   // DMM_GO_MODULE
   LARGE_INTEGER tGoModuleTime;
   LARGE_INTEGER tGoDelayToStartTime;
   __int64 i64GoDelayToStartTimePos;

   // DMM_PREPARE_STOP
   LARGE_INTEGER tPrepareStopTime;
   LARGE_INTEGER tDelayToPrepareStopTime;
   __int64 i64DelayToPrepareStopTimePos;

   // DMM_STOP_MODULE
   LARGE_INTEGER tStopTime;
   LARGE_INTEGER tDelayToStopTime;
   __int64 i64DelayToStopTimePos;

   // DMM_MODULE_ACTION
   __int64 i64ActionCount;

   // DMM_EXPLAIN_USER_ACTION
   LARGE_INTEGER tExplainActionTimeAvg;
   __int64 i64ExplainActionCount;

   // DMM_LOAD_MODULE
   LARGE_INTEGER tLoadTime;

   // DMM_SAVE_MODULE
   LARGE_INTEGER tSaveTime;

   // ProcessData
   LARGE_INTEGER tProcessDataTimeAvg;
   LARGE_INTEGER tProcessDataTimeMin;
   __int64 i64ProcessDataTimeMinPos;
   LARGE_INTEGER tProcessDataTimeMax;
   __int64 i64ProcessDataTimeMaxPos;
   __int64 i64ProcessDataCount;
   __int64 i64ProcessDataHaveWorkedCount;
   BOOL bProcessDataReturnFeatureUsed;
   __int64 i64ProcessDataReturnWithCalcCount;
   LARGE_INTEGER tProcessDataDelayToStartTime;
   __int64 i64ProcessDataDelayToStartTimePos;

   // DrawNewData
   LARGE_INTEGER tDrawNewDataTimeMin;
   __int64 i64DrawNewDataTimeMinPos;
   LARGE_INTEGER tDrawNewDataTimeMax;
   __int64 i64DrawNewDataTimeMaxPos;
   LARGE_INTEGER tDrawNewDataTimeAvg;
   __int64 i64DrawNewDataCount;

   // Zyklus-Zeit Hilfsvariablen
   DWORD dwTimeFirstCall;
   DWORD dwTimeLastCall;
   UINT uiSignalFlowPos;
   // MHa 04.01.2011 - Profiler Erweiterungen - Start
   DWORD dwMinTimeLastCall;
   DWORD dwMaxTimeLastCall;
   __int64 i64MinTimeLastCall;
   __int64 i64MaxTimeLastCall;
   __int64 i64Histogram[MAX_PROFILER_HISTOGRAM_CLASS];
   UINT uiHistogramNumKlass;
   double dHistogramMini;
   double dHistogramMaxi;
   double dHistogramDiff;
   __int64 i64ProcessDataTimeHistogram[MAX_PROFILER_HISTOGRAM_CLASS];
   UINT uiProcessDataTimeHistogramNumKlass;
   LARGE_INTEGER tProcessDataTimeHistogramMini;
   LARGE_INTEGER tProcessDataTimeHistogramMaxi;
   LARGE_INTEGER tProcessDataTimeHistogramDiff;
   // MHa 04.01.2011 - Profiler Erweiterungen - Stop

   // HyperTrace-Ersatz
   BOOL bSendTraceToConsole;
   char chTraceToConsoleText[100];

   // MHa 19.12.2007 - Bugfix zur CAR 4G3929GS
   // Threads
   unsigned long ulThreadTimeAvg;
} PROFILER;

extern LARGE_INTEGER tProfilerStartTime;
extern __int64 i64ProfilerPrepareStartTimeCount;
extern __int64 i64ProfilerStartTimeCount;
extern __int64 i64ProfilerGoTimeCount;
extern __int64 i64ProfilerProcessDataTimeCount;
extern LARGE_INTEGER tProfilerStopTime;
extern __int64 i64ProfilerStopTimeCount;
extern __int64 i64ProfilerPrepareStopTimeCount;


/* ------------------------------------------------------------------------ */
/* Type: MODULE                                                             */
/* ------------------------------------------------------------------------ */

typedef struct
{
   /* Global Part */
   HWND     hwndModule;          /* Window handle of block symbol in flowchart. */
   HWND     hwndWindow;          /* All modules which create an additional display window */
                                 /* should use this handle. */
   UINT     wModuleNum;          /* ID of the module */
   int      iGlobalModuleClass;  /* ID of the class of the module */
   BOOL     bModuleIsConnected;  /* Is module output channel connected to input */
   HBITMAP _hBlockBmp;           /* unused */
   UINT     wBmpWidth;
   UINT     wBmpHeight;
   UINT     wXpos;
   UINT     wYpos;
   char     ModuleName[13];         /* Name of module in flowchart symbol */
   char     ModuleDescription[41];  /* Description of the module */

   /* Reserved for internal use only ! */
   double r1;
   double r2;
   BOOL r3;
   BOOL r4;
   /* End internal use */

   /* Input Part */
   UINT wNumInpChan;    /* Number of defined input channels                         */

   /* Reserved for internal use only ! */
   UINT r5[MAX_CHANNEL];
   UINT r6[MAX_CHANNEL];
   UINT r7[MAX_CHANNEL];
   DATA_BLOCK_HEADER FAR *r8[MAX_CHANNEL];
   HBITMAP r9[MAX_CHANNEL];
   POINT r10[MAX_CHANNEL];
   RECT r11[MAX_CHANNEL];
   /* End internal use */

   /* Output Part */
   UINT wNumOutChan;      /* Number of defined output channels                        */
   WORD ChannelRelation;  /* Relation of inputs to outputs of a single module         */
                          /* Use: KZ_NORMAL, KZ_2_1, KZ_1_2, KZ_2_2, KZ_ALL_1         */
                          /*      KZ_1_ALL, KZ_1_LESS                                 */

   UINT r12[MAX_CHANNEL];               /* Reserved for internal use only !                       */
   FIFO_HEADER FAR *Fifo[MAX_CHANNEL];  /* Array of wNumOutChan module channels which send data to  */
                                        /* their output FIFOs.                                      */

   /* Privat Data */
   void FAR *ModuleParameters;               /* Memory area for module relevant data, the data    */
                                             /* are stored in a flowchart, so do not use variables for   */
                                             /* proccessing and help functions!  Store here variables    */
                                             /* can be set up in the dialog boxes!                       */
   void FAR *TempModuleData;                 /* Memory for data which are NOT stored in the flowchart */
                                             /* Like: Window handles, pointer, memory handles, font handles */
   void FAR *TempChannelData[MAX_CHANNEL];   /* Memory area for proccessing work. Data NOT stroed in flow chart */
   BOOL bModuleIsSelected;

   char cModuleDocu[256];                   /* Full module documentation                                */
   PROFILER r13;                            // internal profiler data : do not touch

   // Release or Debug version of the module (DMM_IS_DEBUG)
   BOOL bIsDebugDLL;
} MODULE;



typedef struct
{
   BOOL bReplaceItself;
   BOOL bChannelNamesUsed;
   BOOL bUnitsUsed;
   BOOL bCopyChannelNamesUsed;
   char szChannelName[MAX_CHANNEL][24];
   BOOL bCopyChannelName[MAX_CHANNEL];
   char szUnit[MAX_CHANNEL][MAX_UNIT_LEN];
} MODULE_DATA_TEMPLATE;

#define MAXDATSAVE 20
#define MAXDATLOAD 20
#define MAX_PASS_WORT 11

typedef struct
{
   BOOL bMitRaster;        /* soll Raster gezeigt werden                     */
   BOOL bPunkte;           /* Raster als Punktlinie oder durchgezogene Linie */
   UINT wAbstand;          /* Abstand der Rasterlinien                       */
   BOOL bIconLeiste;       /* Iconleiste zeigen/verbergen                    */
   BOOL bFunktionsLeiste;  /* Funktionsleiste zeigen/verbergen               */
   BOOL bAutoRouter;       /* Autorouter an/aus                              */
   UINT wxClient;          /* hor. Groesse der Arbeitsflaeche                */
   UINT wyClient;          /* ver. Groesse der Arbeitsflaeche                */
   UINT wVscrollPos;       /* hor. Scrollposition des Hauptfensters          */
   UINT wHscrollPos;       /* ver. Scrollposition des Hauptfensters          */
   UINT wxScreen;          /* hor. Groesse des Hauptfensters                 */
   UINT wyScreen;          /* ver. Groesse des Hauptfensters                 */
   BOOL bDebugInfo;        /* Debugfenster anzeigen/verbergen                */
   BOOL bOverview;         /* Übersichtsfenster                              */
   RECT reSpeicher;        /* Koordinaten des Prozentbalkens                 */
   BOOL bProtectedDsb;
   RECT __reTasten;
   RECT __reTastenFeld[10];
   UINT __uiTastenTyp[10];
   HBITMAP __hTastenBmp[10];
   BOOL __bButtonDown;
   UINT __uiTaste;
   BOOL bWasZoomed;
   UINT __wMaxTaste;

   UINT wDatSave;
   char cDatSaveName[MAXDATSAVE][20];
   UINT iDatSaveMenu[MAXDATSAVE];
   BOOL bDatSaveUsed[MAXDATSAVE];

   UINT wDatLoad;
   char cDatLoadName[MAXDATSAVE][20];
   UINT iDatLoadMenu[MAXDATSAVE];
   BOOL bDatLoadUsed[MAXDATSAVE];

   BOOL bPassWort;
   char chPassWort[MAX_PASS_WORT];
   BOOL bCopyright;
   BOOL bLoadModuleBar;

   HFONT hFifoInfoFont;     /* Fifo Dialogbox */
   LOGFONT lfFifo;
   MODULE * FifoModule;     /* Dieses Modul betrachten wir */
   FIFO_HEADER *AktFifo;
   UINT wOutpChan;
   UINT wFifoModuleNr;
   BOOL bHideWindows;
   BOOL bMinWindows;
   BOOL bPalette;          /* Layouter Palette zeigen/verbergen */
   BOOL bStatusZeile;      /* Statuszeile zeigen/verbergen */
   UINT IconLeisteSpalten;

   BOOL bDlgNewModule;
   BOOL bDlgNewLayoutPage;
   BOOL bDlgNewLayoutObject;
   BOOL bInvisibleModuleWindows;
   BOOL bInputGlobalStringVars;
   BOOL bCopyChannelNamesAtStart;
   BOOL bLoadWithFileInfo;
   BOOL bWarnIfJammed;
   BOOL bControlDataflow;
   BOOL bControlDataflowRemainMemIgnore;         // if true, we don't care about available memory for fifos at all.
   int  nControlDataflowRemainVirtMemPerc;       // How much of the max. virtual memory do we want to use for fifos?
   ULONGLONG nControlDataflowDlabFifoMemLimit;   // in Bytes
   ULONGLONG nControlDataflowUsedFifoMem;        // Used memory by fifo blocks in bytes.
   BOOL bNoESC;

   BOOL bTreeShowBitmap;
   COLORREF clrTreeBk;
   char cTreeBmp[BUFSIZE_MAX_PATH_LENGTH_FOR_DLAB];
   int wTreeBmpMode;

   BOOL bToTreeAtStart;
   BOOL bToChartAtStop;
   int  wTreeSortMode;
   BOOL bHideLoadProgress;

   BOOL bScrollDesk;
   POINT ptScroll;
   POINT ptOldScroll;

   BOOL bDragDropMode;
   BOOL bDragDrop;
   UINT DropId;

   BOOL bReleaseCpu;
   BOOL bWarnFileChange;

   DLAB_FLOAT *FifoData;
   BOOL bNewFifoData;
   BOOL bNewFifoDataForNewGraph;

   BOOL bToLayoutAtStart;

   BOOL bUserDefinedColorsDSB;
   BOOL bModuleTooltips;
   BOOL bLoadDDLVerbose;
   BOOL bProfiler;
   BOOL bExplDrag;
   DWORD imlExplDrag;
   char szDragFileName[512];

   // DebugInfo und DebugGrapf Fenster:
   BOOL bDebugListActive;
   BOOL bDebugGraphActive;

   // MHa 07.01.2008 - ProcessData nach Thread verlagern
   BOOL bProcessDataIntoThread;
} FENSTERPARAMETER;


#define MAXDATSAVE 20
#define MAXDATLOAD 20
#define MAX_PASS_WORT 11
#define MAX_MODUL_ICONS   40

/* ------------------------------------------------------------------------ */
/* Type: ICON                                                               */
/* Reserved for internal use only !                                         */
/* ------------------------------------------------------------------------ */

typedef struct
{
   int     iClassNr[MAX_MODUL_ICONS];
   WORD    wIconTyp[MAX_MODUL_ICONS];
   UINT    wAnzIcon;
   UINT    wIconNr;
   HANDLE  hIconFont;
   UINT    wYoffset;
   UINT    uiMaxVisible;
   UINT    BBoxId;
   UINT    wVscrollPos;
   int     xPos;
   int     yPos;
   int     xSize;
   int     ySize;
} ICONS;

extern ICONS  *icons;

/* BBox-Types, where can module be used? */
#define  BB_UNIVERSAL    0
#define  BB_DAP          1
#define  BB_HYDRA        2



/* ------------------------------------------------------------------------ */
/* Global Constants                                                         */
/* ------------------------------------------------------------------------ */

typedef unsigned long (*PERFORM_ACTION_PROC) (MODULE FAR *ThisModule, int wMsg, int wParam, long lParam);
typedef int (*PROCESS_DATA_PROC) (MODULE FAR *ThisModule);
typedef void (*INIT_FKT) (void);
typedef BOOL (*CREATE_FKT) (UINT ModulNr);
typedef void (*SAVE_FKT) (UINT ModulNr);
typedef BOOL (*LOAD_FKT) (UINT ModulNr);
typedef void (*PARAM_FKT) (MODULE FAR *ThisModule);
typedef BOOL (*START_FKT) (UINT ModulNr);
typedef BOOL (*FIFO_FKT) (UINT ModulNr, UINT FifoNr);
typedef void (*HANDLE_FKT) (UINT ModulNr);
typedef BOOL (*STOP_FKT) (UINT ModulNr);
typedef void (*DELETE_FKT) (UINT ModulNr);
typedef void (*EXIT_FKT) (void);



/* ------------------------------------------------------------------------ */
/* Type: MODULKLASSE                                                        */
/* ------------------------------------------------------------------------ */

typedef struct
{
   HINSTANCE hInst;               /* Instance of DLL where module can be found          */
   char Name[16];                 /* Name of Module (max. 15 chars)                     */
   UINT DataSize;                 /* Size of module data                                */
   UINT VarSize;                  /* Size of var data                                   */
   UINT KanalSize;                /* Size of channel data                               */
   UINT MenuId;                   /* Menu identifier                                    */
   const char FAR *IdString;      /* Default module name                                */
   const char FAR *StatusString;  /* Status string                                      */
   UINT HelpId;                   /* Default help ID                                    */
   const char FAR *HelpFileName;  /* Name of help file or NULL                          */
   UINT BBoxId;                   /* In which BBox can module be placed                 */
   HBITMAP ModIcon;               /* Icon in module bar                                 */
   HBITMAP BlkIcon;               /* Icon in flowchart                                  */
   CREATE_FKT Create;             /* Create function: Add new module                    */
   SAVE_FKT   Save;               /* Prepare save of module data                        */
   LOAD_FKT   Load;               /* Prepare after load of module data. E.g. version check */
   PARAM_FKT  Param;              /* Activate dialogbox                                 */
   START_FKT  Start;              /* One time called for a single module at start of experiment */
   FIFO_FKT   SetupFifo;          /* One time called for a single output channel at start of experiment */
   HANDLE_FKT Handler;            /*  */
   STOP_FKT   Stop;               /* Called at stop of experiment for a single module   */
   DELETE_FKT Delete;             /* Called at module deleting                          */
   EXIT_FKT   Terminate;          /* Called at end of program                           */

   PERFORM_ACTION_PROC PerformAction;  /* Process actions                           */
   PROCESS_DATA_PROC ProcessData;      /* Process data function                     */
} MODULKLASSE;



/* TOOLKIT-Functions defined as CALLBACK functions !!! */
#define TOOLAPI CALLBACK



#define MAX_ARRANGE_WND 9
#define MINIMIZE_FLAG 1
#define HIDE_FLAG     2

/* ------------------------------------------------------------------------ */
/* Type: MODULE_WND_POS                                                     */
/* Used for storing of window arrangments                                   */
/* ------------------------------------------------------------------------ */

typedef struct
{
   BOOL bUsed;
   RECT reWnd;
   int  nWndFlags;    /* Bit 0: SW_MINIMIZED=1, BIT 1: SW_HIDE=1, SW_SHOW=0 */
   BOOL bMaximized;
} MODULE_WND_POS;

#define MINIMIZE_FLAG 1
#define HIDE_FLAG     2



/* ------------------------------------------------------------------------ */
/* Type: ACTION_DESCRIPTION                                                 */
/* Used for description of DASYLab actions                                  */
/* ------------------------------------------------------------------------ */

#define ACTION_0_PARAMS                   0
#define ACTION_1_PARAMS                   1
#define ACTION_2_PARAMS                   2
#define ACTION_3_PARAMS                   3
#define ACTION_4_PARAMS                   4
#define ACTION_STRING_PARAMS              5
#define ACTION_DOUBLE_STRING_PARAMS       6
#define ACTION_2DOUBLE_STRING_PARAMS      7
#define ACTION_2STRING_PARAMS             8
#define ACTION_PARAM_TYPE_INT    0
#define ACTION_PARAM_TYPE_DOUBLE 1
#define ACTION_PARAM_TYPE_VAR_NO          2
#define ACTION_PARAM_TYPE_STR_NO          3

typedef struct
{
   HINSTANCE hInst;      /* Instance used for loading strings out of correct RC     */
   UINT Number;
   char InternalName[20];
                         /* Used Action parameter for dialog box                    */
   UINT Params;          /* 0:   None                                               */
                         /* 1-4: Double;                                            */
                         /* 5:   String                                             */
                         /* 6:   1 Double; 1 String                                 */
                         /* 7:   2 Double; 1 String                                 */
                         /* 8:   2 String a 128 characters                          */
   UINT IdName;          /* Resource ID for action name                             */
   UINT IdParams[4];     /* Resource ID for header                                  */
   UINT ParamType[4];    /* 0: Integer; 1: Double */
} ACTION_DESCRIPTION;



/* ------------------------------------------------------------------------ */
/* Type: ONE_ACTION                                                         */
/* ------------------------------------------------------------------------ */

typedef struct
{
   UINT   Number;          /* Nummer (ID) of action                                 */
   UINT   ReceiveID;       /* ID set up with Synchronous actions                    */
   double fParam[4];       /* Parameter int oder double                             */
   char   szParam[256];    /* Text Parameter                                        */
   double fStartTime;      /* Start time of data block, when action was prepared    */
   MODULE *Receiver;       /* Pointer to receiver module                            */
   MODULE *Source;         /* Pointer to sender module                              */
} ONE_ACTION;



/* ------------------------------------------------------------------------ */
/* Type: WORDRECT                                                           */
/* ------------------------------------------------------------------------ */

typedef struct WORDRECT
{
   WORD left, right, top, bottom;
} WRECT;



/* ------------------------------------------------------------------------ */
/* Type: ALDUSMFHEADER                                                      */
/* placeable metafile header                                                */
/* ------------------------------------------------------------------------ */

typedef struct
{
   DWORD   key;
   WORD    hmf;
   WRECT    bbox;
   WORD    inch;
   DWORD   reserved;
   WORD    checksum;
} ALDUSMFHEADER;



/* ------------------------------------------------------------------------ */
/* Type: DAP_SETUP                                                          */
/* Used to have a view at the momentary DAP setup                           */
/* ------------------------------------------------------------------------ */

typedef struct
{
   BOOL bIsUsed;
   double fSampleDistance;
   UINT   wBlockSize;
   int FreeMem;
}  DAP_SETUP;



/* ------------------------------------------------------------------------ */
/* Type: PARAMETER_INFO                                                     */
/* Used to save module paramters as ASCII-text                              */
/* ------------------------------------------------------------------------ */

typedef struct
{
   char     *szDescription;
   char     *szType;
   size_t   nOffset;
   size_t   nStructOffset;
} PARAMETER_INFO;



/* ------------------------------------------------------------------------ */
/* Type: MOUSE_PARAM                                                        */
/* Used to send mouse messages from the panel to the module                 */
/* ------------------------------------------------------------------------ */

typedef struct
{
   POINT NormalPoint;
   POINT Corner;
   HWND hWnd;
} MOUSE_PARAM;


/* ======================================================================== */
/* TIME BASE FUNCTIONS                                                      */
/* ======================================================================== */

/* ------------------------------------------------------------------------ */
/* Time Base Constants                                                      */
/* ------------------------------------------------------------------------ */

#define ID_TIMEBASE_DASYLAB   1
#define ID_TIMEBASE_DRIVER    2
#define ID_TIMEBASE_INSTRUNET 7
#define ID_TIMEBASE_NICAN     8
#define ID_TIMEBASE_NIDAQ1    10
#define ID_TIMEBASE_NIDAQN    99

#define ID_TIMEBASE_COCAIN    101
#define ID_TIMEBASE_DAPDLL    102
#define ID_TIMEBASE_IBR       103
#define ID_TIMEBASE_NUDAM     104
#define ID_TIMEBASE_OMEGADRX  105
#define ID_TIMEBASE_SOLARTRON 106

#define ID_TIMEBASE_GBM_1     107
#define ID_TIMEBASE_GBM_2     108
#define ID_TIMEBASE_GBM_3     109
#define ID_TIMEBASE_GBM_4     110
#define ID_TIMEBASE_GBM_5     111
#define ID_TIMEBASE_GBM_6     112
#define ID_TIMEBASE_GBM_7     113
#define ID_TIMEBASE_GBM_8     114

#define ID_TIMEBASE_CONDOR    115

#define ID_TIMEBASE_IXXATCAN  116
#define ID_TIMEBASE_KVASERCAN 117
#define ID_TIMEBASE_ICPDASCAN 118
#define ID_TIMEBASE_DEWESOFT  119      // Treiber für Dewesoft, vergeben an Measx am 08.09.2010
                                       // Nachtrag: Sourcen werden von Measx verwaltet.
#define ID_TIMEBASE_DELPHIN   120      // Treiber für Delphin Technology, vergeben an Measx am 08.09.2010
                                       // Nachtrag: Sourcen werden von Measx verwaltet.
#define ID_TIMEBASE_DEWETRON  121      // Treiber für Dewetron, zur Weitergabe an Measx versendet am 08.10.2013
                                       // Angefragt von Herrn Peter Gutmann 
#define ID_TIMEBASE_IOTECH    130
#define ID_TIMEBASE_IOTECH_PD 131      // Personal DAQ, vergeben am 10.09.2007, auf Anfrage von CJ

#define ID_TIMEBASE_GOLDAMMER_1 150    // Goldammer Treiber, vergeben am 13.08.2008, auf Anfrage
#define ID_TIMEBASE_GOLDAMMER_2 151    // von Herrn Torsten Schinkel von Goldammer.
#define ID_TIMEBASE_GOLDAMMER_3 152
#define ID_TIMEBASE_GOLDAMMER_4 153

#define ID_TIMEBASE_SIMATIC   160      // Simatic Treiber, vergeben am 30.08.2010, auf Anfrage
                                       // von Herrn Treydte (ServiceLab).
#define ID_TIMEBASE_SIMATIC_2 161      // Simatic Treiber, zweite ID, vergeben am 07.05.2012, auf Anfrage
                                       // von Herrn Treydte (ServiceLab).

#define ID_TIMEBASE_IMTRON    170      // Imtron Messtechnik GmbH, Herr Werner Heinrich
                                       // vergeben am 26.03.2013

#define ID_TIMEBASE_GANTNER   171            // Gantner Instruments Test & Measurement GmbH, 64297 Darmstadt
                                             // Ansprechpartner: Hr. Wunderle
                                             // vergeben am 14.09.2015 von HWMX (wegen ID-Kollision mit IXXAT-CAN 116)

#define ID_TIMEBASE_NEHRING_NECC    172      // Zeitbasis für Herrn Nehring, vergeben am 06.09.2017 MXSG
#define ID_TIMEBASE_NEHRING_MGCPLUS 173      // Zeitbasis für Herrn Nehring, vergeben am 06.09.2017 MXSG
#define ID_TIMEBASE_NEHRING_LTT     174      // Zeitbasis für Herrn Nehring, vergeben am 06.09.2017 MXSG

#define ID_TIMEBASE_DEWETRON_TRION  175      // Zeitbasis für Dewetron Trion Treiber, vergeben am 7.9.2017 von MXSG

#define ID_TIMEBASE_M_DRV_1   200
#define ID_TIMEBASE_M_DRV_N   299

#define ID_TIMEBASE_DEWE_1    300
#define ID_TIMEBASE_DEWE_N    399

#define ID_TIMEBASE_NIDAQMX_1 400

#define ID_TIMEBASE_MCC_1     500
#define ID_TIMEBASE_MCC_N     599

#define ID_TIMEBASE_OMEGA_1   600
#define ID_TIMEBASE_OMEGA_N   699

#define ID_TIMEBASE_CYBERRESEARCH_1   700
#define ID_TIMEBASE_CYBERRESEARCH_N   799

#define ID_TIMEBASE_DT_1            800  // MX_SG : Zeitbasen IDs für DataTranslation  vergeben am 24.05.2017
#define ID_TIMEBASE_DT_N            820  // Ansprechpartner DT : Michael Buergin,            
												     // Measurement Computing GmbH, Im Weilerlen 10, 74321 Bietigheim-Bissingen, Germany, Tel: +49 (0) 7142-9531-30	

#define ID_TIMEBASE_MAX       999

#define ID_TIMEBASE_MHZ       0
#define ID_TIMEBASE_KHZ       1
#define ID_TIMEBASE_HZ        2
#define ID_TIMEBASE_MS        3
#define ID_TIMEBASE_SEK       4
#define ID_TIMEBASE_MIN       5

//#define MAX_BLOCKSIZE         32768
#define DLAB13_MAX_BLOCKSIZE  32768
#define MAX_BLOCKSIZE         1048576  // = (1024L*1024L)  new big blocks since Dasylab 14 (2016)



/* ------------------------------------------------------------------------ */
/* Time Base Data Structures                                                */
/* ------------------------------------------------------------------------ */

typedef struct
{
   UINT uiID;
   BOOL bAutoBlockSize;
   UINT uiBlockSize;
   int  nFreqFormat;
   double fSampleDistance;
   short wVarBlockSize;
   short wVarSampleRate;
} EXT_TIMEBASE;


/* ------------------------------------------------------------------------ */
/* Variables Overview Data Structures                                       */
/* ------------------------------------------------------------------------ */

typedef struct
{
   UINT wSize;
   UINT uiVersion;
   LPARAM pHandle;
   UINT wVarType;
   UINT wVarNumber;
   UINT wAccess;
   UINT wVarUsage;
   int  iChannelNumber;
   BOOL bAction;              // Nur im Aktionsmodul TRUE!!
   UINT wActionNumber;
   char szDescription[GLVO_USAGEDESCRIPTION_MAXLEN + 1];
} GLVO_MODULE_NOTIFY_PARAM;

/* ------------------------------------------------------------------------ */
/* Menu Items setting from TKDlls Structures                                */
/* ------------------------------------------------------------------------ */
typedef struct
{
   UINT  uiSize;
   UINT  uiVersion;
   char  szMainMenuEntry[MAIN_MENU_ENTRY_MAXLEN];
   char  szSubMenusEntry[SUB_MENUS_ENTRY_MAXLEN];
   char  szNewMenuEntries[SUB_MENUS_ENTRY_MAXLEN];
   char  szMenuGroupEntries[MAIN_MENU_ENTRY_MAXLEN];
   UINT  uiNewMenuID;
   char  cMenuAccessKey;
} DASYLAB_INSERT_MENU;

#define EXTEND_DLL_FOR_PYTHON                                           ".dly"

/* -eof- */
