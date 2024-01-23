
/* ======================================================================== */
/* Programm   :  DLAB  -  Messwerterfassung und Verarbeitung unter Windows  */
/* Datei      :  MODCLASS.H                                                 */
/* ------------------------------------------------------------------------ */
/* Funktionen :  Verwaltung der message-orientierten Modulklassen           */
/* Erstellt   :  C. Strunk ab 15.11.93                                      */
/* Erweitert  :  ---  (Hier ggf. andere Programmierer eintragen)            */
/* Letzte Änd.:  15.11.93 CS                                                */
/* ======================================================================== */

typedef struct {
   /* ACHTUNG: Nach Veröffentlichung des DLL-Toolkits darf diese Struktur   */
   /*          nicht mehr verändert werden. Erweiterungen sind dann nur     */
   /*          noch über neue Messages realisierbar.                        */
   HINSTANCE hInst;               /* Instanz der DLL, die das Modul enthält */
   const char FAR *Name;               /* Name des Moduls (max. 15 Zeichen) */
   UINT DataSize;                                  /* Größe der Modul-Daten */
   UINT VarSize;              /* Größe der Laufzeitvariablen (Handles etc.) */
   UINT ChannelSize;                       /* Größe der Kanal-Daten pro Kanal */
   UINT MenuId;                        /* Identifizierung in der Menüleiste */
   const char FAR *IdString;                          /* Default-Block-Name */
   const char FAR *StatusString;                   /* For use in Status Bar */
   UINT HelpId;                              /* Einsprungpunkt in der Hilfe */
   const char FAR *HelpFileName;          /* Name der Hilfe-Datei oder NULL */
   UINT BBoxId;                    /* In welcher BBox ist das Modul erlaubt */
   HBITMAP ModIcon;                                 /* Icon in Modul-Leiste */
   HBITMAP BlkIcon;                                      /* Icon des Blocks */
   PERFORM_ACTION_PROC PerformAction;           /* Behandlung der Meldungen */
   PROCESS_DATA_PROC ProcessData;         /* Laufzeit-Behandlung der Blöcke */
   UINT reserved[30];                            /* reserved for future use */
} MODCLASS;

/* (There is no default PROCESS_DATA_PROC procedure.) */

#ifndef _TOOLKIT_
/* Register a new Module Class */
BOOL TOOLAPI RegisterModuleClass ( MODCLASS FAR *modclass );

/* Default Message Handler for PERFORM_ACTION_PROC */
unsigned long TOOLAPI PerformDefaultAction ( MODULE FAR *ThisModule, int wMsg, int wParam, long lParam );

/* Send messages to Class/Module/Channel */
unsigned long TOOLAPI SendModClassMessage ( int wClassNr, int wMsg, int wParam, long lParam );
unsigned long TOOLAPI SendModuleMessage  ( MODULE FAR *ThisModule, int wMsg, int wParam, long lParam );
unsigned long TOOLAPI SendModChanMessage ( MODULE FAR *ThisModule, int wMsg, int wParam, long lParam );

/* Send messages to all modules */
BOOL TOOLAPI BroadcastModuleMessage  ( int wMsg, int wParam, long lParam );
#endif

/* DASYLab Class Messages (called with ThisModule == NULL) */
#define  DQM_UNREGISTER_CLASS             1
#define  DQM_CHECK_REPLACE                2

/* DASYLab Module Messages */
#define  DMM_CREATE_MODULE               101
#define  DMM_DELETE_MODULE               102
#define  DMM_PARAM_MODULE                103
#define  DMM_SAVE_MODULE                 104
#define  DMM_LOAD_MODULE                 105
#define  DMM_START_MODULE                106
#define  DMM_STOP_MODULE                 107
#define  DMM_PAUSE_MODULE                108
#define  DMM_RESUME_MODULE               109
#define  DMM_BBOX_CLOSE                  110
#define  DMM_BBOX_STRUCTURE              111
#define  DMM_BBOX_SWITCH                 112
#define  DMM_SAVE_WINDOW_POS             113
#define  DMM_DEL_WINDOW_POS              114
#define  DMM_DEL_ALL_WINDOW_POS          115
#define  DMM_SHOW_WINDOW_POS             116
#define  DMM_QUERY_MODULE_ACTION         117
#define  DMM_MODULE_ACTION               118
#define  DMM_QUERY_SYNC_MODULE_ACTION    119
#define  DMM_INIT_SYNC_MODULE_ACTION     120
#define  DMM_SYNC_MODULE_ACTION          121
#define  DMM_SYNC_MODULE_NO_ACTION       122
#define  DMM_CLEAR_SYNC_MODULE_ACTIONS   123
#define  DMM_EXPLAIN_USER_ACTION         124
#define  DMM_DDE_RECEIVE_ADVISE_DATA     125
#define  DMM_DDE_RECEIVE_POKE_DATA       126
#define  DMM_DDE_DISCONNECT              127
#define  DMM_GO_MODULE                   128

#define DMM_QUERY_PANEL                                                    129 // In/out: Maske der Verbindungstypen
#define DMM_PANEL_CONNECT                                                  130 // In: Handle + Typ; Out: BOOL
#define  DMM_PANEL_SET_SIZE              131
#define  DMM_PANEL_REQUEST_STRING        132
#define  DMM_PANEL_REQUEST_METAFILE      133
#define  DMM_PANEL_PERFORM_DRAW          134
#define  DMM_PANEL_DISCONNECT            135
#define  DMM_PANEL_DISCONNECT_ALL        136
#define  DMM_PANEL_DRAW_NEW_DATA         137
#define  DMM_PANEL_WM_LBUTTONDOWN        138
#define  DMM_PANEL_WM_LBUTTONUP          139
#define  DMM_PANEL_WM_MOUSEMOVE          140
#define  DMM_PANEL_WM_LBUTTONDBLCLK      141
#define  DMM_PANEL_WM_RBUTTONDOWN        142
#define  DMM_PANEL_SET_WINDOW            143

#define  DMM_DDE_SEND_ADVISE_START       144
#define  DMM_DDE_SEND_ADVISE_STOP        145
#define  DMM_DDE_SEND_ADVISE_REQUEST     146
#define  DMM_DDE_SEND_REQUEST            147

#define  DMM_GLOBAL_VAR_CHANGED          148
#define  DMM_GLOBAL_STRING_CHANGED       149

#define  DMM_DDE_SEND_LINK_TYPE          150

#define  DMM_COPY_CHANNEL_NAME           151
#define  DMM_GET_CHANNEL_NAME            152
#define  DMM_SET_CHANNEL_NAME_COPY_OPTION 153
#define  DMM_GET_PARAMETERS_INFO         154

#define  DMM_PREPARE_START_MODULE        155

#define  DMM_GET_EXTRA_PARAM_SIZE        156
#define  DMM_GET_EXTRA_PARAMS            157
#define  DMM_SET_EXTRA_PARAMS            158

#define  DMM_ACTIVATE_WORKSHEET          159
#define  DMM_ACTIVATE_LAYOUT             160
#define  DMM_ACTIVATE_DISPLAY_WND        161
#define  DMM_COPY_DEFAULT_FONT           162

#define  DMM_REGISTER_MENU               163

#define  DMM_CHANGE_VAR_NAME             164
#define  DMM_CHANGE_MODULE_NAME          165
#define  DMM_DELETE_LAYOUT               166

#define  DMM_CREATE_REPLACE              167
#define  DMM_REPLACE_MODULE              168
#define  DMM_GET_MODULE_TYPE             169

#define  DMM_REQUEST_GLOB_VARS           170
#define  DMM_REQUEST_GLOB_ACTION_VARS    171

#define  DMM_REQ_MODULE_DEFAULT          172

#define DMM_REQUEST_EDIT_NEW_STATE                                         173
#define DMM_SET_EDIT_NEW_STATE                                             174

#define DMM_FILE_NEW                                                       175 // MHa 20.03.2007 - Botschaft für Datei >> Neu
#define DMM_PREPARE_STOP                                                   176 // MHa 19.12.2007 - Bugfix zur CAR 4G3929GS
#define DMM_THREAD_TIME                                                    177 // MHa 19.12.2007 - Bugfix zur CAR 4G3929GS
#define DMM_IS_DEBUG                                                       178 // MHa 08.01.2008 - Meldung von DLL ob Release oder Debug
#define DMM_NORMALIZE_ALL_WINDOWS                                          179 // MHa 14.01.2008 - Botschaft für MN_ANSICHT_NORMAL_ALL_WND
#define DMM_HIDE_ALL_WINDOWS                                               180 // MHa 14.01.2008 - Botschaft für MN_ANSICHT_HIDE_ALL_WND
#define DMM_SHOW_ALL_WINDOWS                                               181 // MHa 14.01.2008 - Botschaft für MN_ANSICHT_SHOW_ALL_WND
#define DMM_MINIMIZE_ALL_WINDOWS                                           182 // MHa 14.01.2008 - Botschaft für MN_ANSICHT_MINI_ALL_WND
#define DMM_HAS_MODULE_CHANGED                                             183 // MHa 01.12.2008 - Bugfix zur CAR 104235
#define DMM_RESET_MODULE_CHANGE_FLAG                                       184 // MHa 01.12.2008 - Bugfix zur CAR 104235
#define DMM_PREPARE_DSB_START                                              185 // MHa 04.07.2009 - Bugfix zur CAR 177432

#define DMM_GET_TIMEBASE_ID                                                186 // MX_RO 07.07.2016 - Allows DASYLab to store only the used timebases in the flowchart


// DASYLab Channel Messages (wParam == channel == 0 .. 15)
#define  DCM_SETUP_FIFO                  201
#define  DCM_GET_UNIT                    202

typedef struct _MESSAGE_DATA_
{
   int wMsg;
   int wParam;
   long lParam;
} MESSAGE_DATA;


/* ======================================================================================= */
/* ======================================================================================= */
/* ======================================================================================= */

/* Meldungen _von_ den Modulen _an_ die Panel */

#define  PT_TEXT          0x01
#define  PT_METAFILE      0x02
#define  PT_PAINT         0x04
#define  PT_PAINT_SCALED  0x08
#define  PT_WINDOW        0x10

/* Parameter für DMM_PANEL_SET_SIZE Meldungen */
typedef struct
{
   SIZE absolute;       /* Absolute Objektgröße in Zehntelmillimetern */
   SIZE scaled;         /* Derzeitige skalierte Objektgröße z.B. in Pixel */
} TWO_SIZES;

/* Panel Handle */
typedef unsigned int HPANEL;

#ifndef _TOOLKIT_
/* Send messages to a Panel */
unsigned long TOOLAPI SendPanelMessage ( HPANEL hPanel, int wMsg, int wParam, long lParam );
#endif

/* Panel Messages */
#define  DPM_PANEL_DISCONNECT                501
#define  DPM_PANEL_GOT_NEW_DATA              502
#define  DPM_PANEL_QUERY_MODULE_MUST_WAIT    503   /* Wird von Modulen gefragt   */
#define  DPM_PANEL_QUERY_PANEL_MUST_WAIT     504   /* Wird vom Layouter gefragt  */
#define  DPM_PANEL_SET_EVENT_TIME            505   /* Wird vom Layouter gesendet */
#define  DPM_PANEL_RECONNECT                 506
#define  DPM_PANEL_GET_HWND                  507   /* non documented; subject to change without notice */
#define  DPM_PANEL_GET_CORNER_X              508   /* non documented; subject to change without notice */
#define  DPM_PANEL_GET_CORNER_Y              509   /* non documented; subject to change without notice */
#define  DPM_PANEL_GET_BK_COL                510   /* non documented; subject to change without notice */


/* ======================================================================================= */
/* ======================================================================================= */
/* ======================================================================================= */

/* Prototypen aus C++ File Main_Wnd.CPP */

#define  DLM_LAYOUT_UPDATE                600
#define  DLM_LAYOUT_PRINT                 601
#define  DLM_LAYOUT_TO_CLIPBOARD_METAFILE 602
#define  DLM_LAYOUT_SETFULLSCREEN         603
#define  DLM_LAYOUT_ACTIVATE              604
#define  DLM_LAYOUT_LOCK                  605
#define  DLM_LAYOUT_UNLOCK                606
#define  DLM_LAYOUT_NORMALIZE             607
#define  DLM_LAYOUT_NOTTOPMOST            608
#define  DLM_LAYOUT_TOPMOST               609
#define  DLM_LAYOUT_ACTIVATE_WORKSHEET    610
#define  DLM_LAYOUT_RESCALE               611
#define  DLM_LAYOUT_START                 612
#define  DLM_LAYOUT_STOP                  613
#define  DLM_LAYOUT_TO_WMF                614
#define  DLM_LAYOUT_TO_BMP                615
#define  DLM_LAYOUT_TO_JPEG               616
#define  DLM_LAYOUT_TO_CLIPBOARD_BITMAP   617
#define  DLM_LAYOUT_TO_PNG                618

typedef unsigned int HLAYOUT;

void UnregisterLayout ( HLAYOUT hLayout );
unsigned long TOOLAPI SendLayouterMessage ( HLAYOUT hLayout, int wMsg, int wParam, long lParam );
unsigned long TOOLAPI SendLayouterMessageNext (int wMsg, int wParam, long lParam);
unsigned long TOOLAPI BroadcastLayouterMessage ( int wMsg, int wParam, long lParam );
unsigned long TOOLAPI BroadcastLayouterMessageExceptThis ( HLAYOUT hLayout, int wMsg, int wParam, long lParam );

BOOL IsDASYLabWindow (HWND hwnd);

/* -eof- */
