/* ======================================================================== */
/* Programm   :  CONST.H  -  Headerdatei                                    */
/* Funktionen :  Defines für Programmkonstanten, IDs für Menüeinträge,      */
/*               IDs für Stringtabelle, IDs für Dialogboxen, ...            */
/* Letzte Änd.:  14.12.2015 MX_RO                                           */
/* ======================================================================== */


#ifndef IDHELP
#  define   IDHELP          9
#endif

#ifndef BBM_SETBITS
#  define   BBM_SETBITS     ( BM_SETSTYLE + 10 )
#endif

#ifndef APSTUDIO_INVOKED
#  ifdef SS_ETCHEDFRAME
#    undef SS_BLACKFRAME
#    define SS_BLACKFRAME SS_ETCHEDFRAME
#  endif
#endif  /* APSTUDIO_INVOKED */

#define  VERSION_CODE     1400

#define  MAIN_RELEASE     14
#define  MAJOR_VERSION    -1
#define  MINOR_VERSION    0


#define BUFSIZE_MAX_PATH_LENGTH_FOR_DLAB                               4*260+4
#define BUFSIZE_MAX_PATH                      BUFSIZE_MAX_PATH_LENGTH_FOR_DLAB
#define BUFSIZE_MAX_DRIVE                     BUFSIZE_MAX_PATH_LENGTH_FOR_DLAB /*12*/
#define BUFSIZE_MAX_DIR                       BUFSIZE_MAX_PATH_LENGTH_FOR_DLAB
#define BUFSIZE_MAX_FNAME                     BUFSIZE_MAX_PATH_LENGTH_FOR_DLAB
#define BUFSIZE_MAX_EXT                       BUFSIZE_MAX_PATH_LENGTH_FOR_DLAB

#define SIZE_MAX_PATH_LENGTH_FOR_DLAB                                      260
#define SIZE_MAX_PATH                                                      260
#define SIZE_MAX_DRIVE                                                       3
#define SIZE_MAX_DIR                                                       256
#define SIZE_MAX_FNAME                                                     256
#define SIZE_MAX_EXT                                                       256
/* ------------------------------------------------------------------------ */

#define MAX_PATHCOMPACTPATHEX                                               75
#define DSB_HOME                                                       "HOME:"

#define MAX_CHANNEL_NAME_LENGTH                          CHANNEL_NAME_LENGTH+4

// Neue Konstante für Info-Strings:
// Sollte nicht in zu speichernden Strukturen verwendet werden, da sich  die Größe ändern kann.
#define MAX_INFO_STR 160

/* ------------------------------------------------------------------------ */
/* IDs für Menüeinträge  Hauptmenü (100-999)                                */
/* ------------------------------------------------------------------------ */

#define IDS_SYSTEM_MENU             10
#define IDS_SYSTEM_RESTORE          11
#define IDS_SYSTEM_MOVE             12
#define IDS_SYSTEM_SIZE             13
#define IDS_SYSTEM_MINIMIZE         14
#define IDS_SYSTEM_MAXIMIZE         15
#define IDS_SYSTEM_CLOSE            16
#define IDS_SYSTEM_SWITCH           17

#define MN_DATEI                    100
#define MN_DATEI_NEU                101
#define MN_DATEI_OEFFNEN            102
#define MN_DATEI_SPEICHERN          103
#define MN_DATEI_SPEICHERN_UNTER    104
#define MN_DATEI_INFO               105
#define MN_DATEI_LAYOUT             106
#define MN_DATEI_DRUCKEN            107
#define MN_DATEI_INSTALLATION       108
#define MN_DATEI_BEENDEN            109
#define MN_DATEI_SEITEN_FMT         110
#define MN_DATEI_WINDOWS_BEENDEN    111
#define MN_DATEI_WINDOWS_NEUSTART   112
#define MN_DATEI_EXPORT             113

// MHa 03.01.2012 - Start
#define MN_DATEI_WINDOWS_LOGOFF     114
// MHa 03.01.2012 - Stop

#define MN_BEARBEITEN               200
#define MN_BEARB_SCHALTBILD         201
#define MN_BEARB_BITMAP             202
#define MN_BEARB_MODUL_NEU          203
#define MN_BEARB_MODUL_LADEN        204
#define MN_BEARB_MODUL_SAVE         205
#define MN_BEARB_MODUL_SAVEAS       206
#define MN_BEARB_MODUL_DEFAULT      207
#define MN_BEARB_CUT                208
#define MN_BEARB_COPY               209
#define MN_BEARB_PASTE              210
#define MN_BEARB_UNDO               211
#define MN_BEARB_DEL                212

#define MN_BEARB_MODUL_ADVANCED     213
#define MN_BEARB_MODUL_PROFI        214
#define MN_ESCAPE                   215


/* Die Menu-Id jedes Moduls muß im folgenden Bereich liegen: */
#define MN_ERSTES_MODUL             301
#define MN_LETZTES_MODUL            399

/* Bislang sind die folgenden Menu-Id's vergeben: */
#define MN_MODUL                    300
#define MN_MODUL_ADBLOCK            301
#define MN_MODUL_GENERATOR          302
#define MN_MODUL_YTGRAPH            303
#define MN_MODUL_ARITHMETIK         304
#define MN_MODUL_TRIGONOMETRIE      305
#define MN_MODUL_MITTELUNG          306
#define MN_MODUL_FFT                307
#define MN_MODUL_LAMPE              308
#define MN_MODUL_WINDOW             309
#define MN_MODUL_BARGRAPH           310
#define MN_MODUL_ZEIGER             311
#define MN_MODUL_DDE_IN             312
#define MN_MODUL_DDE_OUT            313
#define MN_MODUL_DIGITAL            314
#define MN_MODUL_DATEILADEN         315
#define MN_MODUL_DATEISPEICHERN     316
#define MN_MODUL_DA_OUT             317
#define MN_MODUL_BLOCKMITTELUNG     318
#define MN_MODUL_RELAIS             319
#define MN_MODUL_CT_IN              320
#define MN_MODUL_DELAY              321
#define MN_MODUL_ADAPT              322
#define MN_MODUL_UMSCHALTER         323
#define MN_MODUL_ACTION             324
#define MN_MODUL_MESSAGE            325
#define MN_MODUL_UHRZEIT            326
#define MN_MODUL_NETZ_IN            327
#define MN_MODUL_NETZ_OUT           328
#define MN_MODUL_EXTENDED_TRIGGER   329

#define MN_MODUL_BLOCKPRG           330
#define MN_MODUL_FLEXPRO_WRITE      331
#define MN_MODUL_RS232_OUT          332
#define MN_MODUL_MIN_MAX            333
#define MN_MODUL_CT_OUT             334
#define MN_MODUL_TRANSFER           335
#define MN_MODUL_FALTUNG            336
#define MN_MODUL_WEIGHT             337
#define MN_MODUL_TECHFIL            338
#define MN_MODUL_MSG_NET_IN         339
#define MN_MODUL_MSG_NET_OUT        340
#define MN_MODUL_FFT_FILTER         341
#define MN_MODUL_ZPREGELN           342
#define MN_MODUL_TRANSFER_NEU       343
#define MN_MODUL_ZAEHLVERFAHREN     344
#define MN_MODUL_IEEE_OUT           345
#define MN_MODUL_SAVE_UFF           346
#define MN_MODUL_FFT_MAX            347

#define MN_MODUL_EMAIL              348
#define MN_MODUL_PHONE              349
#define MN_MODUL_PWM_ANALYSE        350
#define MN_MODUL_RBUF               351
#define MN_MODUL_GRAY               352

#define MN_MODUL_FLIPFLOP           353

#define MN_MODULE_FORMEL            354
#define MN_MODUL_CHECK_SK           355
#define MN_MODUL_SOLLKURVE          356
#define MN_MODUL_BEGRENZ            357
#define MN_MODUL_POLAR              358
#define MN_MODUL_NUMERISCH          359
#define MN_MODUL_ZEITGEBER          360
#define MN_MODUL_STOP               361
#define MN_MODUL_KORRELATION        362
#define MN_MODUL_DIGIN              363
#define MN_MODUL_DIGOUT             364
#define MN_MODUL_RS232              365
#define MN_MODUL_VORNACH_TRIGGER    366
#define MN_MODUL_STARTSTOP_TRIGGER  367
#define MN_MODUL_SAMPLE_TRIGGER     368
#define MN_MODUL_DEMAND_TRIG        369
#define MN_MODUL_SKALIERUNG         371
#define MN_MODUL_ABLEITUNG          372
#define MN_MODUL_KLASSIFIZIERUNG    373
#define MN_MODUL_REGRESSION         374
#define MN_MODUL_EXTREMA            375
#define MN_MODUL_ZAEHLEN            376
#define MN_MODUL_FILTER             378
#define MN_MODUL_SCHALTER           379
#define MN_MODUL_HANDREGLER         380
#define MN_MODUL_PID                381
#define MN_MODUL_LOGIK              382
#define MN_MODUL_XYGRAPH            383
#define MN_MODUL_LINIENSCHREIBER    384
#define MN_MODUL_SEPARIEREN         386
#define MN_MODUL_ZEITSCHEIBE        387
#define MN_MODUL_IEEE               388
#define MN_MODUL_BBOX               389
#define MN_MODUL_BBOXIO             390
#define MN_MODUL_DIGITAL2           391
#define MN_MODUL_BITLOGIK           392

#define MN_MODUL_BACKUP             393
#define MN_MODUL_CUT_OUT            394
#define MN_MODUL_MIX                395
#define MN_MODUL_POS_SIGNAL         396
#define MN_MODUL_LATCH              397

#define MN_MODULE_SETPT             398
#define MN_MODULE_MULTISWITCH       399

#define MN_MODUL_ODBC               2700
#define MN_MODUL_ODBC_OUT           2701
#define MN_MODUL_ODBC_IN            2702
#define MN_MODUL_VDZ_MWZ            2703
#define MN_MODUL_DISTORTION         2704
#define MN_MODUL_CHAN_SORT          2705
#define MN_MODUL_VAR_READ           2706
#define MN_MODUL_VAR_WRITE          2707
#define MN_MODUL_NMAX               2708
#define MN_MODUL_UFILT              2709
#define MN_MODUL_CASE               2710
#define MN_MODUL_IVI_CONFIG         2711
#define MN_MODUL_IVI_DMM            2712
#define MN_MODUL_IVI_FGEN           2713
#define MN_MODUL_IVI_SCOPE          2714
#define MN_MODUL_IVI_SWITCH         2715
#define MN_MODUL_IVI_POWER          2716
#define MN_MODUL_IVI_EXT1           2717
#define MN_MODUL_IVI_EXT2           2718
#define MN_MODUL_IVI_EXT3           2719
#define MN_MODUL_IVI_EXT4           2720
#define MN_MODUL_IVI_EXT5           2721

#define MN_MODUL_ELEC               2722
#define MN_MODUL_HARMONISCH         2723
#define MN_MODUL_PERIODE            2724
#define MN_MODUL_MULTIDRIVER        2725
#define MN_MODUL_ICOM               2726
#define MN_MODUL_ICOMOUT            2727
#define MN_MODUL_COMP               2728
#define MN_MODUL_BLOCKTIME          2729
#define MN_MODUL_SHIFTREG           2730
#define MN_MODUL_MODBUS_AI          2731
#define MN_MODUL_MODBUS_AO          2732
#define MN_MODUL_MODBUS_DI          2733
#define MN_MODUL_MODBUS_DO          2734
#define MN_MODUL_MODBUS_RES1        2735
#define MN_MODUL_MODBUS_RES2        2736
#define MN_MODUL_MODBUS_RES3        2737
#define MN_MODUL_MODBUS_RES4        2738
#define MN_MODUL_MULTIDRIVER_AO     2739
#define MN_MODUL_MULTIDRIVER_DI     2740
#define MN_MODUL_MULTIDRIVER_DO     2741
#define MN_MODUL_POLAR_GRAPH        2742
#define MN_MODUL_DIAGRAM            2743
#define MN_MODUL_PSCRIPT            2744
#define MN_MODUL_ORDERANALYSIS      2745

#define MN_MESSEN                   410
#define MN_MESSEN_START             411
#define MN_MESSEN_STOP              412
#define MN_MESSEN_PAUSE             413
#define MN_MESSEN_HARDSETUP         414
#define MN_MESSEN_KANAL             415
#define MN_MESSEN_ZEIT              416
#define MN_MESSEN_TREIBER           417
#define MN_MESSEN_AUTOSTART         418
#define MN_MESSEN_AUSGABE           419
#define MN_MESSEN_REMOTE            420
#define MN_MESSEN_TIMEBASE          421
#define MN_MESSEN_PASSWORT          422

#define MN_ANSICHT                  500
#define MN_ANSICHT_VERKLEINERT      502
#define MN_ANSICHT_ANIMATION        503
#define MN_ANSICHT_FKTLEISTE        504
#define MN_ANSICHT_ICONLEISTE       505
#define MN_ANSICHT_FIFO_STATUS      506
#define MN_ANSICHT_PALETTE          522
#define MN_ANSICHT_STATUSZEILE      523
#define MN_ANSICHT_PANE_EXPLORER    507
#define MN_ANSICHT_PANE_INFO        508
#define MN_ANSICHT_PANE_CONSOLE     509
#define MN_ANSICHT_PANE_DEBUGLIST   517
#define MN_ANSICHT_PANE_DEBUGGRAPH  518
#define MN_ANSICHT_PANE_CONS_CLEAR  519

#define MN_ANSICHT_TREE             524
#define MN_ANSICHT_CHART            525
#define MN_ANSICHT_LAYOUT           526
#define MN_ANSICHT_SEQ              527

#define MN_ANSICHT_1_COLUMN         530
#define MN_ANSICHT_2_COLUMN         531
#define MN_ANSICHT_4_COLUMN         532
#define MN_ANSICHT_5_COLUMN         533
#define MN_ANSICHT_8_COLUMN         534
#define MN_ANSICHT_10_COLUMN        535
#define MN_ANSICHT_20_COLUMN        536
#define MN_ANSICHT_40_COLUMN        537

#define MN_ANSICHT_SET_BUTTON       540
#define MN_SET_USER_TBBUTTON        541
#define MN_SET_NONE_TBBUTTON        542

#define MN_DEBUGINFO                506
#define MN_ANSICHT_HIDE_ONE_WND     570
#define MN_ANSICHT_SHOW_ONE_WND     571
#define MN_ANSICHT_HIDE_ALL_WND     572
#define MN_ANSICHT_SHOW_ALL_WND     573

#define MN_ANSICHT_MINI_ONE_WND     574
#define MN_ANSICHT_NORMAL_ONE_WND   575
#define MN_ANSICHT_MINI_ALL_WND     576
#define MN_ANSICHT_NORMAL_ALL_WND   577

#define MN_ANSICHT_SAVE_WND_POS     510
#define MN_ANSICHT_DEL_WND_POS      511
#define MN_ANSICHT_SELECT_WND_POS   512
#define MN_ANSICHT_DEL_ALL_WND_POS  513
#define MN_ANSICHT_WND_POS_TEXT     514
#define ID_ANSICHT_COMBO            515
#define ID_WINDOW_DISPLAY_WND       516

#define MN_BBOX_LEAVE               550
#define MN_BBOX_SAVE_AS             551
#define MN_BBOX_LOAD                552
#define MN_BBOX_INFO                553
#define MN_BBOX_CODE                554
#define MN_BBOX_HARDWAREDEF         555
#define MN_BBOX_OUTPUTDEF           556
#define MN_BBOX_MEASDEF             557
#define MN_BBOX_LEAVEDLL            558

#define MN_OPTIONEN                 600
#define MN_OPTIONEN_FENSTER         601
#define MN_OPTIONEN_COLOUR          602
#define MN_OPTIONEN_LINE_INS        603
#define MN_OPTIONEN_LINE_OUT        604
#define MN_OPTIONEN_AUTOROUTER      605
#define MN_OPTIONEN_DESK_GRID       606
#define MN_OPTIONEN_PASS            607
#define MN_OPTIONEN_PASSWORT        608
#define MN_OPTIONEN_CHECK_FLOWCHART 609
#define MN_OPTIONEN_DIRECTORY       610
#define MN_OPTIONEN_KEY_EVENT       611
#define MN_OPTIONEN_GLOBAL_STRING   612
#define MN_OPTIONEN_SCREEN_LOCKING  613
#define MN_OPTIONEN_GLOBAL_VAR      614
#define MN_OPTIONEN_COPY_CHANNEL_NAMES 615
#define MN_OPTIONEN_ACTION_LIST     616
#define MN_OPTIONEN_DEFAULT_FONT    617
#define MN_OPTIONEN_TREE            618
#define MN_OPTIONEN_RUNTIME         619

#define MN_LOADOLDDSB               620                        
#define MN_LOADOLDDSB2              621                        
#define MN_LOADOLDDSB3              622                        
#define MN_LOADOLDDSB4              623                        
#define MN_LOADOLDDSB5              624                        
#define MN_LOADOLDDSB6              625                        

#define MN_OPTIONEN_ACTION_LIST_OVERVIEW  626
#define MN_OPTIONEN_SERIAL_DEVICE_CONFIG  627
#define MN_OPTIONEN_EXPORT_VAR      628
#define MN_OPTIONEN_IMPORT_VAR      629
#define MN_OPTIONEN_SORTSTART_VAR   630
#define MN_OPTIONEN_PROFILER        631
#define MN_OPTIONEN_WKS_PARAMETERS  632 
#define MN_OPTIONEN_VAR_STRING_OVERVIEW 633
#define MN_OPTIONEN_HOTKEYS         634
#define MN_OPTIONEN_WARNINGS        635


/* Layouter */
#define MN_TOOL_SELECT              650
#define MN_TOOL_RAHMEN              651
#define MN_TOOL_LINIE               652
#define MN_TOOL_TEXT                653
#define MN_TOOL_MODULE_TEXT         654
#define MN_TOOL_MODULE_GRAPH        655
#define MN_TOOL_FILLED_RECT         656
#define MN_TOOL_FILLED_ELLIPSE      657
#define MN_TOOL_ELLIPSE             658
#define MN_TOOL_MULTILINE           659
#define MN_TOOL_DIB                 660
#define MN_TOOL_GRID                661
#define MN_TOOL_GROUP               662
#define MN_TOOL_OBJ_PROPERTIES      663
#define MN_TOOL_PAGEPROP            664
#define MN_TOOL_PROPERTIES          665

#define MN_OPTIONEN_ZOOM1               1000
#define MN_OPTIONEN_ZOOM2               1001
#define MN_OPTIONEN_ZOOM025             1002
#define MN_OPTIONEN_ZOOM05              1003
#define MN_OPTIONEN_ZOOM5               1004
#define MN_OPTIONEN_ZOOMAUTO            1005
#define MN_OPTIONEN_ZOOMDOIT            1006
#define MN_ANSICHT_VOLLBILD             1007
#define MN_OBJEKT_UNDO                  1008
#define MN_OBJEKT_NACHVORNE             1009
#define MN_OBJEKT_NACHHINTEN            1010
#define MN_OBJEKT_GANZVORNE             1011
#define MN_OBJEKT_GANZHINTEN            1012
#define MN_LAY_CLIPBOARD_METAFILE       1013
#define MN_LAY_IMPORT                   1014
#define MN_LAY_SPEICHERN                1015
#define MN_LAYOUT_DELETE                1016
#define MN_ANSICHT_DOCU                 1017
#define MN_ANSICHT_DOCU_CHANGE          1018
#define MN_ANSICHT_DOCU_DEL             1024
#define MN_ANSICHT_DOCU_PROPERTY        1025
#define MN_LAY_CLIPBOARD_BITMAP         1026

#define MN_OPTIONEN_SEQ_DEBUG           1028

/* Hier liegen die ladbaren BlackBox-Module */
#define MN_BBOX_USER                700

/* Ab hier kommen die Runtime-Datsave/load Module */
#define MN_DATSAVE_RT               800
#define MN_DATLOAD_RT               850

#define MN_TOOL_1                   870
#define MN_TOOL_2                   871
#define MN_TOOL_3                   872
#define MN_TOOL_4                   873
#define MN_TOOL_5                   874
#define MN_TOOL_6                   875
#define MN_TOOL_7                   876
#define MN_TOOL_8                   877
#define MN_TOOL_9                   878
#define MN_TOOL_10                  879
#define MN_TOOL_11                  880
#define MN_TOOL_12                  881
#define MN_TOOL_13                  882
#define MN_TOOL_14                  883
#define MN_TOOL_15                  884
#define MN_TOOL_16                  885

#define MN_HILFE                    900
#define MN_HILFE_INDEX              IDHELP
#define MN_HILFE_HARDWARE           902
#define MN_HILFE_VERWENDEN          903
#define MN_HILFE_SYSTEM             904
#define MN_HILFE_UEBER              905
#define MN_HILFE_GLOSSAR            906
#define MN_REPORT                   907
#define MN_GETTING_STARTED          908
#define MN_PATENTS                  909

#define MN_CONTEXT_INS_AKT_POS      940
#define MN_CONTEXT_DEL_AKT_POS      941
#define MN_CONTEXT_INS_MULT_POS     942
#define MN_CONTEXT_DEL_MULT_POS     943


/* Sequencer Menu Defines */

#define MN_SEQ_NEW_STATE            950
#define MN_SEQ_DEL_STATE            951
#define MN_SEQ_NEW_ACTION           952
#define MN_SEQ_DEL_ACTION           953
#define MN_SEQ_MOVE_STATE           954
#define MN_SEQ_MOVE_ACTION          955
#define MN_SEQ_EDIT_ACTION          956
#define MN_SEQ_LOAD_FLOWCHART       957
#define MN_SEQ_EDIT_STATE           958
#define MN_SEQ_SET_START_STATE      959
#define MN_SEQ_VIEW_SEQ             960
#define MN_SEQ_VIEW_TREE            961
#define MN_SEQ_VIEW_CHART           962
#define MN_SEQ_VIEW_LAYOUT          963


#define ID_KEIN_ICON               1000
#define ID_ABGRIFF                 1001

#define MAX_TOOL_EXTENSION          16

#define ID_MODULEING_0            1000
#define ID_MODULEING_1            1001
#define ID_MODULEING_2            1002
#define ID_MODULEING_3            1003
#define ID_MODULEING_4            1004
#define ID_MODULEING_5            1005
#define ID_MODULEING_6            1006
#define ID_MODULEING_7            1007
#define ID_MODULEING_8            1008
#define ID_MODULEING_9            1009
#define ID_MODULEING_10           1010
#define ID_MODULEING_11           1011
#define ID_MODULEING_12           1012
#define ID_MODULEING_13           1013
#define ID_MODULEING_14           1014
#define ID_MODULEING_15           1015
#define ID_MODULEING_16           1016

#define ID_MODULAUSG_0            1100
#define ID_MODULAUSG_1            1101
#define ID_MODULAUSG_2            1102
#define ID_MODULAUSG_3            1103
#define ID_MODULAUSG_4            1104
#define ID_MODULAUSG_5            1105
#define ID_MODULAUSG_6            1106
#define ID_MODULAUSG_7            1107
#define ID_MODULAUSG_8            1108
#define ID_MODULAUSG_9            1109
#define ID_MODULAUSG_10           1110
#define ID_MODULAUSG_11           1111
#define ID_MODULAUSG_12           1112
#define ID_MODULAUSG_13           1113
#define ID_MODULAUSG_14           1114
#define ID_MODULAUSG_15           1115
#define ID_MODULAUSG_16           1116

#define MN_STATUS                 1300
#define MN_STATUS_ADBLOCK         1301
#define MN_STATUS_GENERATOR       1302
#define MN_STATUS_YTGRAPH         1303
#define MN_STATUS_ARITHMETIK      1304
#define MN_STATUS_TRIGONOMETRIE   1305
#define MN_STATUS_MITTELUNG       1306
#define MN_STATUS_FFT             1307
#define MN_STATUS_LAMPE           1308
#define MN_STATUS_WINDOW          1309
#define MN_STATUS_BARGRAPH        1310
#define MN_STATUS_ZEIGER          1311
#define MN_STATUS_DDE_IN          1312
#define MN_STATUS_DDE_OUT         1313
#define MN_STATUS_DIGITAL         1314
#define MN_STATUS_DATEILADEN      1315
#define MN_STATUS_DATEISPEICHERN  1316
#define MN_STATUS_DA_OUT          1317
#define MN_STATUS_BLOCKMITTELUNG  1318
#define MN_STATUS_RELAIS          1319
#define MN_STATUS_CT_IN           1320
#define MN_STATUS_DELAY           1321
#define MN_STATUS_ADAPT           1322
#define MN_STATUS_ACTION          1324
#define MN_STATUS_MESSAGE         1325
#define MN_STATUS_UHRZEIT         1326
#define MN_STATUS_NETZ_IN         1327
#define MN_STATUS_NETZ_OUT        1328
#define MN_STATUS_EXTENDED_TRIGGER  1329

#define MN_STATUS_BLOCKPRG        1330
#define MN_STATUS_FLEXPRO_WRITE   1331
#define MN_STATUS_RS232_OUT       1332
#define MN_STATUS_MIN_MAX         1333
#define MN_STATUS_CT_OUT          1334
#define MN_STATUS_TRANSFER        1335
#define MN_STATUS_FALTUNG         1336
#define MN_STATUS_WEIGHT          1337
#define MN_STATUS_TECHFIL         1338
#define MN_STATUS_MSG_NET_IN      1339
#define MN_STATUS_MSG_NET_OUT     1340
#define MN_STATUS_FFT_FILTER      1341
#define MN_STATUS_ZPREGELN        1342
#define MN_STATUS_TRANSFER_NEU    1343
#define MN_STATUS_ZAEHLVERFAHREN  1344
#define MN_STATUS_IEEE_OUT        1345
#define MN_STATUS_SAVE_UFF        1346
#define MN_STATUS_FFT_MAX         1347
#define MN_STATUS_EMAIL           1348
#define MN_STATUS_PHONE           1349
#define MN_STATUS_PWM_ANALYSE     1350
#define MN_STATUS_RBUF            1351
#define MN_STATUS_GRAY            1352
#define MN_STATUS_FLIPFLOP        1353
#define MN_STATUS_FORMEL          1354
#define MN_STATUS_CHECK_SK        1355
#define MN_STATUS_SOLLKURVE       1356
#define MN_STATUS_BEGRENZ         1357
#define MN_STATUS_POLAR           1358
#define MN_STATUS_NUMERISCH       1359
#define MN_STATUS_ZEITGEBER       1360
#define MN_STATUS_STOP            1361
#define MN_STATUS_KORRELATION     1362
#define MN_STATUS_DIGIN           1363
#define MN_STATUS_DIGOUT          1364
#define MN_STATUS_RS232           1365
#define MN_STATUS_VORNACH_TRIGGER 1366
#define MN_STATUS_STARTSTOP_TRIGGER 1367
#define MN_STATUS_SAMPLE_TRIGGER  1368
#define MN_STATUS_DEMAND_TRIG     1369
#define MN_STATUS_SKALIERUNG      1371
#define MN_STATUS_ABLEITUNG       1372
#define MN_STATUS_KLASSIFIZIERUNG 1373
#define MN_STATUS_REGRESSION      1374
#define MN_STATUS_EXTREMA         1375
#define MN_STATUS_ZAEHLEN         1376
#define MN_STATUS_FILTER          1378
#define MN_STATUS_SCHALTER        1379
#define MN_STATUS_HANDREGLER      1380
#define MN_STATUS_PID             1381
#define MN_STATUS_LOGIK           1382
#define MN_STATUS_XYGRAPH         1383
#define MN_STATUS_LINIENSCHREIBER 1384
#define MN_STATUS_ONLINEDRUCKER   1385
#define MN_STATUS_SEPARIEREN      1386
#define MN_STATUS_ZEITSCHEIBE     1387
#define MN_STATUS_IEEE            1388
#define MN_STATUS_BBOX            1389
#define MN_STATUS_BBOXIO          1390
#define MN_STATUS_DIGITAL2        1391
#define MN_STATUS_BITLOGIK        1392

#define MN_STATUS_BACKUP          1393
#define MN_STATUS_CUT_OUT         1394
#define MN_STATUS_MIX             1395
#define MN_STATUS_POS_SIGNAL      1396
#define MN_STATUS_LATCH           1397
#define MN_STATUS_SETPT           1398
#define MN_STATUS_MULTISWITCH     1399

#define MN_STATUS_ODBC            3700
#define MN_STATUS_ODBC_OUT        3701
#define MN_STATUS_ODBC_IN         3702
#define MN_STATUS_VDZ_MWZ         3703
#define MN_STATUS_DISTORTION      3704
#define MN_STATUS_CHAN_SORT       3705
#define MN_STATUS_VAR_READ        3706
#define MN_STATUS_VAR_WRITE       3707
#define MN_STATUS_NMAX            3708
#define MN_STATUS_UFILT           3709
#define MN_STATUS_CASE            3710

// IVI
#define MN_STATUS_IVI_CONFIG      3711
#define MN_STATUS_IVI_DMM         3712
#define MN_STATUS_IVI_FGEN        3713
#define MN_STATUS_IVI_SCOPE       3714
#define MN_STATUS_IVI_SWITCH      3715
#define MN_STATUS_IVI_POWER       3716
#define MN_STATUS_IVI_EXT1        3717
#define MN_STATUS_IVI_EXT2        3718
#define MN_STATUS_IVI_EXT3        3719
#define MN_STATUS_IVI_EXT4        3720
#define MN_STATUS_IVI_EXT5        3721

#define MN_STATUS_ELEC            3722
#define MN_STATUS_HARMONISCH      3723
#define MN_STATUS_PERIODE         3724
#define MN_STATUS_MULTIDRIVER     3725
#define MN_STATUS_ICOM            3726
#define MN_STATUS_ICOMOUT         3727
#define MN_STATUS_COMP            3728
#define MN_STATUS_BLOCKTIME       3729
#define MN_STATUS_SHIFTREG        3730
#define MN_STATUS_MODBUS_AI       3731
#define MN_STATUS_MODBUS_AO       3732
#define MN_STATUS_MODBUS_DI       3733
#define MN_STATUS_MODBUS_DO       3734
#define MN_STATUS_MODBUS_RES1     3735
#define MN_STATUS_MODBUS_RES2     3736
#define MN_STATUS_MODBUS_RES3     3737
#define MN_STATUS_MODBUS_RES4     3738
#define MN_STATUS_MULTIDRIVER_AO  3739
#define MN_STATUS_MULTIDRIVER_DI  3740
#define MN_STATUS_MULTIDRIVER_DO  3741
#define MN_STATUS_POLAR_GRAPH     3742
#define MN_STATUS_DIAGRAM         3743
#define MN_STATUS_PSCRIPT         3744

#define MN_GLVO_CTXT_EXPAND       3760
#define MN_GLVO_CTXT_COLLAPSE     3761
#define MN_GLVO_CTXT_COLLAPSE_ALL 3762
#define MN_GLVO_CTXT_SORT_NAMES   3763
#define MN_GLVO_CTXT_SORT_NUMBERS 3764
#define MN_GLVO_CTXT_SEARCH       3765
#define MN_GLVO_CTXT_GOTO         3766
#define MN_GLVO_CTXT_DLG_OPEN     3767
#define MN_GLVO_CTXT_CONT_SEARCH  3768
#define MN_GLVO_CTXT_LEVEL0       3769
#define MN_GLVO_CTXT_LEVEL1       3770
#define MN_GLVO_CTXT_LEVEL2       3771
#define MN_GLVO_CTXT_LEVEL3       3772
#define MN_GLVO_CTXT_LEVEL4       3773
#define MN_GLVO_CTXT_LEVEL5       3774
#define MN_GLVO_CTXT_LEVEL6       3775
#define MN_GLVO_INIT              3776
#define MN_GLVO_REBUILD           3777
#define MN_GLVO_CLOSE_AND_RETURN_VAR 3778

#define MN_GLVO_MAIN_DETAIL       3800
#define MN_GLVO_MAIN_LISTE        3801

#define ausg                      1116

#define ID_KEY_ALT_0              1500
#define ID_KEY_ALT_1              1501
#define ID_KEY_ALT_2              1502
#define ID_KEY_ALT_3              1503
#define ID_KEY_ALT_4              1504
#define ID_KEY_ALT_5              1505
#define ID_KEY_ALT_6              1506
#define ID_KEY_ALT_7              1507
#define ID_KEY_ALT_8              1508
#define ID_KEY_ALT_9              1509
#define ID_KEY_ALT_S              1510

#define ID_KEY_ALT_CTRL_0         1520
#define ID_KEY_ALT_CTRL_1         1521
#define ID_KEY_ALT_CTRL_2         1522
#define ID_KEY_ALT_CTRL_3         1523
#define ID_KEY_ALT_CTRL_4         1524
#define ID_KEY_ALT_CTRL_5         1525
#define ID_KEY_ALT_CTRL_6         1526
#define ID_KEY_ALT_CTRL_7         1527
#define ID_KEY_ALT_CTRL_8         1528
#define ID_KEY_ALT_CTRL_9         1529

#define ID_KEY_ALT_SHIFT_0        1530
#define ID_KEY_ALT_SHIFT_1        1531
#define ID_KEY_ALT_SHIFT_2        1532
#define ID_KEY_ALT_SHIFT_3        1533
#define ID_KEY_ALT_SHIFT_4        1534
#define ID_KEY_ALT_SHIFT_5        1535
#define ID_KEY_ALT_SHIFT_6        1536
#define ID_KEY_ALT_SHIFT_7        1537
#define ID_KEY_ALT_SHIFT_8        1538
#define ID_KEY_ALT_SHIFT_9        1539

/* Die Menu-Id jedes Moduls muß liegen im Bereich: */
#define MN_ZWEITES_MODUL           2001
#define MN_VORLETZTES_MODUL        2999

/*  ===>  Reserviert für DAP: Bereich 2000-2099 (siehe DAPBOX.H)  <===  */

/*  OLD!!! ===>  Reserviert für HYDRA: Bereich 2500-2699  <===  */

/*  ===>  Reserviert für UX?: Bereich 2950-2974 <===  */
#define MN_FIRST_EXT_MODULE        2950
#define MN_LAST_EXT_MODULE         2974

/* Diese Konstante darf (wg. Toolkit) *nie* mehr geändert werden. */
#define  MENU_EXPAND_POS  3

/* Die zusätzlichen Menu-Id jeder DLL müssen liegen im Bereich: */
#define MN_FIRST_EXT_MENU_ID       4990
#define MN_LAST_EXT_MENU_ID        4999

/*  ===>  Reserviert für FIP: Bereich 4000-4009  <===  */
/*  ===>  Reserviert für UX1: Bereich 4010-4019  <===  */
/*  ===>  Reserviert für UX2: Bereich 4020-4029  <===  */
/*  ===>  Reserviert für UX3: Bereich 4030-4039  <===  */
/*  ===>  Reserviert für UX4: Bereich 4040-4049  <===  */
/*  ===>  Reserviert für UX5: Bereich 4050-4059  <===  */
/*  ===>  Reserviert für UX6: Bereich 4060-4069  <===  */
/*  ===>  Reserviert für UX7: Bereich 4070-4079  <===  */
/*  ===>  Reserviert für UX8: Bereich 4080-4089  <===  */

/*  ===>  Reserviert für CAN: Bereich 4090-4099  <===  */
/*  ===>  Reserviert für DSO: Bereich 4100-4109  <===  */
/*  ===>  Reserviert für NDDI:Bereich 4110-4119  <===  */
/*  ===>  Reserviert für Mxxx-Treiber:Bereich 4120-4121  <===  */
#define MN_FIRST_MXXX_MENU_ID      4120
#define MN_LAST_MXXX_MENU_ID       4121
/*  ===>  Reserviert für PScript: Bereich 4130-4139  <===  */
#define MN_FIRST_PSCRIPT_MENU_ID      4130
/*  ===>  Reserviert für Später:    Bereich 4140-4179  <===  */

/*  ===>  Reserviert für INTERBUS:  Bereich 4180-4189  <===  */
/*  ===>  Reserviert für HYDRA:     Bereich 4190-4199  <===  */


#define MN_ERSTE_DLL_MENU_ID       4000
#define MN_LETZTE_DLL_MENU_ID      4199



/* ------------------------------------------------------------------------ */
/* IDs für zusätzliche Menüs (100 - 19999) in 500er Abstand                 */
/* ------------------------------------------------------------------------ */


/* ------------------------------------------------------------------------ */
/* IDs für Dialogboxen Borghoff (21000 - 21999)                             */
/* ------------------------------------------------------------------------ */

#define IDD_CHANGE_ALL_FILENAMES    21000      /* jp 18.2.97 */

#define STR_ILL_BLOCKSIZE           21999      /* Wird auch von FFT benutzt */
#define STR_ILL_HARDWARE            21998      /* w.o. für ADBLOCK, DIBLOCK */
#define STR_NOCHANNEL               21997      /* w.o. für ADBLOCK, DIBLOCK */
#define STR_MODULE_BUTTON_NEW       21996
#define STR_BLOCKSIZE_MISMATCH      21995
#define STR_SET_USER_TBBUTTON_NEW   21994

#define STR_SOLLK_FILTER            21950
#define STR_SOLLK_LOAD_TITLE        21951
#define STR_SOLLK_EXT               21952
#define STR_SOLLK_ERR_WRONG_HEADER  21953
#define STR_SOLLK_ERR_ALLOC         21954
#define STR_SOLLK_ERR_NOT_FOUND     21955

#define STR_DATALOG_FORMAT          21642      /* Auch für Diskstreaming */
#define STR_STREAM_TITLE            21643



/* ------------------------------------------------------------------------ */
/* IDs für Dialogboxen Magolei (22000 - 22999)                              */
/* ------------------------------------------------------------------------ */
#define ID_PROG_ICON            22000
#define IDD_PROGVERSION         22001      /* About-Dialog: Programmversion */
#define IDD_PROGSTAND           22002      /* About-Dialog: Programmstand   */
#define IDD_WINDOWTEXT          22003      /* Fenster Text der Listbox      */
#define ID_PROG_ICON_WBW        22004


#define ID_VERSION_KUNDE        22004
#define ID_VERSION_HAENDLER     22005
#define ID_VERSION_HOCHSCHULE   22006
#define ID_VERSION_NODONGLE     22007
#define ID_VERSION_DATALOG      22008      /* Interne DONGLE-freie DATALOG-Version */
#define ID_VERSION_NODO_KUNDE   22009      /* Kunden DONGLE-freie Version          */
#define ID_VERSION_DAMAGED      22010      /* Quersumme stimmt nicht DasyLab beenden */
#define ID_VERSION_LIGHT        22011
#define ID_VERSION_RUNTIME      22012
#define ID_VERSION_FULL         22013
#define ID_VERSION_BASIC        22014
#define ID_VERSION_30_DAYS      22015
#define ID_VERSION_DEWE_RUNTIME 22016
#define ID_VERSION_SAMPLER      22017
#define ID_VERSION_SCHOOL       22018

#define STR_DAT_LOAD_MENU       21776
#define STR_DAT_LOAD_POP        21777
// MHa 14.01.2013 - Bugfix zur CAR 336416
#define STR_ANALYZE_DRIVE       21804

#define STR_DAT_SAVE_MENU       21656
#define STR_DAT_SAVE_POP        21657

#define ID_DISTRIB_DASYLAB      22020
#define ID_DISTRIB_SIGNALYS     22021
#define ID_DISTRIB_STRAWBERRY   22022
#define ID_DISTRIB_FLEXPRO      22023
#define ID_DISTRIB_OXY          22024
#define ID_DISTRIB_SIEMENS      22025

#define STR_INFO_ABOUT          22035

#define STR_CONSOLE_INFO_TEXT_1  22036
#define STR_CONSOLE_INFO_TEXT_2  22037

#define ID_HERSTELLER_DATALOG    0
#define ID_HERSTELLER_DASYTEC    1
#define ID_HERSTELLER_OMEGA      2
#define ID_HERSTELLER_IOTECH     3
#define ID_HERSTELLER_QUATECH    4

#define ID_VERSION_DASYLAB      0
#define ID_VERSION_STRAWBERRY   1
#define ID_VERSION_FLEXPRO      2
#define ID_VERSION_OXY          3
#define ID_VERSION_SIGNALYS     4
#define ID_VERSION_SIEMENS      5
#define ID_VERSION_VI_LAB       6
#define ID_VERSION_PHOENIX      7

#define ID_TYP_DEMO             0
#define ID_TYP_FULL             1
#define ID_TYP_BASIC            2
#define ID_TYP_RUNTIME          3
#define ID_TYP_LITE             4
#define ID_TYP_MINI             5
#define ID_TYP_MINI_IOTECH      6
#define ID_TYP_30_DAYS          7
#define ID_TYP_DEWE_RUNTIME     8
#define ID_TYP_CHART            9

#define ID_LIEFERUNG_KUNDE      1
#define ID_LIEFERUNG_HOCHSCHULE 2
#define ID_LIEFERUNG_HAENDLER   3

#define ID_SPRACHE_DEUTSCH      1
#define ID_SPRACHE_ENGL         2
#define ID_SPRACHE_JAPAN        3
#define ID_SPRACHE_SONST        4

#define STR_DEF_FLOWCHART_NAME  22030
#define STR_DEF_MODULBAR_NAME   22031
#define STR_DEF_BBOX_NAME       22032

#define STR_ABOUT_VERSION_FULL         22040
#define STR_ABOUT_VERSION_BASIC        22041
#define STR_ABOUT_VERSION_RUNTIME      22042
#define STR_ABOUT_VERSION_LITE         22043
#define STR_ABOUT_LIEFERUNG_ENDKUNDE   22044
#define STR_ABOUT_LIEFERUNG_HOCHSCHULE 22045
#define STR_ABOUT_LIEFERUNG_HAENDLER   22046
#define STR_ABOUT_SPRACHE_DEUTSCH      22047
#define STR_ABOUT_SPRACHE_ENGL         22048
#define STR_ABOUT_SPRACHE_SONST        22049
#define STR_ABOUT_SPRACHE_EXE          22061

#define IDD_XANZ                22060
#define IDD_MAXY                22070
#define IDD_BLOECKE             22080
#define IDD_ACHSEN              22090
#define IDD_RASTER              22100
#define IDD_YTKANAELE           22110
#define IDD_YTKANPLUS           22120
#define IDD_YTKANMINUS          22130
#define IDD_SHOWGRAFIK          22140
#define ID_DRVBUF               22150
#define STR_INP_NOT_CONNECTED   22330
#define STR_OUTP_NOT_CONNECTED  22331
#define ID_FKT_LIST             22340
#define ID_FKT_ICON             22341
#define ID_MENU_LIST            22343
#define ID_MENU_TREE            22344
#define ID_MENU_CHOICE          22345
#define ID_MENU_PATH            22346
#define IDD_TAKEOVER_TBSETTINGS 22347
#define IDC_TAKEOVER_SEQUENCER  22348
#define IDC_TAKEOVER_DISPLAY    22349
#define IDC_TAKEOVER_WORKSHEET  22350
#define IDC_TAKEOVER_LAYOUT     22351

#define ID_HOTKEY_CHOICE_OLD    22352
#define ID_HOTKEY_CHOICE        22353
#define IDD_CNTRL               22354
#define IDD_ALT                 22355
#define IDD_SHIFT               22356
#define IDD_HOTKEYS_UNSORT      22357
#define ID_ADD_HOTKEY           22358
#define ID_DEL_HOTKEY           22359
#define IDD_RESET_HOTKEYS       22361
#define IDD_MENUITEM_SORT       22362
#define IDD_NEWHOTKEY_CHOICE    22363
#define ID_CHANGE_HOTKEY        22364
#define IDD_LB_HOTKEYS_UNSORT   22365
#define IDD_FREIE_HOTKEYS       22366
#define IDD_LB_HOTKEYS_FREE     22367
#define IDD_GOTO_FREE_HKEY      22368

#define ID_LIST_WINDOWS         22380

#define STR_OUT_OF_SCREEN       22342
#define STR_DDE_NO_CONNECTION   22503
#define STR_DDE_NOT_INIT        22504
#define STR_DDE_INPUT           22505
#define STR_ONE_MODULE          22506

#define ID_VERSION_DEMO         22507
#define ID_VERSION_MINI         22508
#define ID_VERSION_MINI_IOTECH  22509
#define ID_VERSION_CHART        22510

#define STR_USERINFO                    23000
#define STR_NO_CHANGE_WHILE_MEASURE     23001
#define ID_NETZHILFE                    23002
#define ID_HARDHILFE                    ID_NETZHILFE
#define ID_EVAHILFE                     23003
#define STR_NO_CONNECTION               23004
#define STR_DELETE_CONNECTION           23005
#define STR_DELETE_MODUL                23006
#define STR_DELETE_OUTPUT_CONNECTION    23007
#define STR_CAPTION_ATTENTION           23008
#define STR_CAPTION_MISTAKE             23009
#define STR_FIRST_DELETE_CONNECTION     23010
#define STR_DDE_NO_SERVER               23011
#define STR_LOW_RESOURCE                23012
#define STR_TOO_FAST                    23013
#define STR_STRUKTUR_FEHLER             23014
#define STR_STRUKTUR_PROBLEME           23015
#define STR_NOT_IN_DEMO                 23016     /* ... in DEMO-Vers. gesperrt */
#define STR_OUT_OF_MEM                  23017

#define STR_ERR_KONV                    23018
#define STR_ERR_RANGE_MAX               23019
#define STR_ERR_RANGE_MIN               23020

#define STR_OVERVIEW                    23021     /* Titel Übersichtsfenster */
#define STR_MAX_ABGR_15                 23022
#define STR_NO_MOVE                     23023

#define STR_ERR_ONE_MODULE              23024
#define STR_ERR_ONE_CHANNEL             23025
#define STR_ERR_STREAM_BLOCKING         23026

// MHa 15.10.2009 - Bugfix zur CAR 121289
#define STR_STRUCTUR_PROBLEM_LOOPBACK   23027

#define STR_BBOX_USER                   23030

#define STR_SYSINFO_MISSING             23031
#define STR_SYSINFO_NO_FUNCTION         23032
#define STR_SYSINFO_DONGLE_INCOMPATIBEL 23033

#define STR_DELTE_SEL_MODULES           23034
#define STR_DELTE_SEL_MODULES_SHORT     23035
#define STR_DELTE_SEL_MODULES_QUIT      23036
#define STR_DELTE_SEL_MODULES_SHORT_QUIT 23037
#define STR_NO_COPY_WITH_BBOX           23038
#define STR_PASTE_FAILED                23039

#define STR_NOT_IN_LITE                 23040     /* ... in LIGHT-Vers. gesperrt */
#define STR_NOT_IN_STARTER              23041
#define STR_NOT_IN_VERSION_UNSPECIFIED  23042

#define STR_GETTING_STARTED_HEADLINE    23100
#define STR_GETTING_STARTED_MSGTEXT     23101
#define STR_GETTING_STARTED_DISPLAY     23102

#define STR_HOTKEY_CONTEXT_MENU         23860
#define STR_HOTKEY_ERR_WIN              23861
#define STR_HOTKEY_ERR_FILE             23862
#define STR_HOTKEY_ERR_FILE_SAV         23863
#define STR_HOTKEY_ERR_MAX              23864
#define STR_HOTKEY_ERR_HEADMAX          23865
#define STR_HOTKEY_HINT_USED            23866
#define STR_HOTKEY_HINT_DELETE          23867
#define STR_HOTKEY_ACC_EXIST            23868
#define STR_HOTKEY_ERR_ACC_DEL          23869
#define STR_HOTKEY_ALL_DEL              23870
#define STR_HOTKEY_ALL_HEADDEL          23871
#define STR_HOTKEY_ERR_HEAD             23872
#define STR_HOTKEY_HINT_HEAD            23873
#define STR_COPY_F7                     23874
#define STR_COPY_F8                     23875
#define STR_HOTKEY_EXIST_HEAD           23876
#define STR_HOTKEY_WIN_RESERVE          23877
#define STR_HOTKEY_DLAB_RESERVE         23878
#define STR_HOTKEY_ACC_EXIST_OTHERVIEW  23879

#define STR_WARN_MENU_NOT_ALLOWED_HEAD  23890
#define STR_WARN_MENU_NOT_ALLOWED       23891
#define STR_HINT_EXE_ALREADY_RUNNING    23892
#define STR_HINT_USER_IS_GUEST          23893

#define STR_KLEIN_FENST_NAME            23901
#define MODUL_UNSELECT                  23902
#define MODUL_DIALOG                    23903
#define ID_DEL_COMP                     23904
#define ID_DEL_INP                      23905
#define ID_DEL_OUTP                     23906
#define STR_INFO_FIRMA                  23907
#define STR_INFO_ABTL                   23908
#define STR_INFO_NAME                   23909
#define STR_INFO_SERIENNR               23910
#define STR_BACK_TO_MAIN_CHART          23911
#define STR_BACK_TO_NEXT_BBOX           23912
#define STR_NO_PLACE_NO_MODULE          23913
#define ID_DEL_REPL                     23914

#define IDD_ERR_MESSAGE                 23920
#define IDD_ERR_FILE                    23921
#define IDD_ERR_LINE                    23922
#define STR_OVERWR_ARRANGE              23923
#define STR_WINDOW_ARRANGE              23924
#define STR_DEL_WINDOW_ARRANGE          23925
#define STR_DEL_ALL_WINDOW_ARRANGE      23926
#define STR_DEL_WINDOW_ARRANGE2         23927
#define STR_WINDOW_APPEND               23928

#define MN_EIGENSCHAFTEN_MESSUNG        23929

#define ID_COPY_CHANNEL_NAME            23930
#define ID_LIST_UNIT                    23931
#define MAX_DEFAULT_UNITS               12

#define MN_TREE_UPDATE                  23932
#define IDD_ERR_GENERAL                 23933
#define IDD_ERR_GENERAL_I               23934

#define STR_DEFAULT_UNIT_1              23940
#define STR_DEFAULT_UNIT_2              23941
#define STR_DEFAULT_UNIT_3              23942
#define STR_DEFAULT_UNIT_4              23943
#define STR_DEFAULT_UNIT_5              23944
#define STR_DEFAULT_UNIT_6              23945
#define STR_DEFAULT_UNIT_7              23946
#define STR_DEFAULT_UNIT_8              23947
#define STR_DEFAULT_UNIT_9              23948
#define STR_DEFAULT_UNIT_10             23949
#define STR_DEFAULT_UNIT_11             23950
#define STR_DEFAULT_UNIT_12             23951
#define STR_DEFAULT_UNIT_13             23952
#define STR_DEFAULT_UNIT_14             23953
#define STR_DEFAULT_UNIT_15             23954
#define STR_DEFAULT_UNIT_16             23955

/* ------------------------------------------------------------------------ */
/* IDs für Dialogboxen Rottmann (23000 - 23999)                             */
/* ------------------------------------------------------------------------ */

#define IDD_LESS                23000
#define IDD_MORE                23001
#define IDD_KAN00               23002
#define IDD_KAN01               23003
#define IDD_KAN02               23004
#define IDD_KAN03               23005
#define IDD_KAN04               23006
#define IDD_KAN05               23007
#define IDD_KAN06               23008
#define IDD_KAN07               23009
#define IDD_KAN08               23010
#define IDD_KAN09               23011
#define IDD_KAN10               23012
#define IDD_KAN11               23013
#define IDD_KAN12               23014
#define IDD_KAN13               23015
#define IDD_KAN14               23016
#define IDD_KAN15               23017
#define IDD_MODUL_NAME          23018
#define IDD_MODUL_BEZEICHNUNG   23019
#define IDD_KANAL_NR            23020
#define IDD_KANAL_NAME          23021

#define IDD_NUM00               21500
#define IDD_NUM01               21501
#define IDD_NUM02               21502
#define IDD_NUM03               21503
#define IDD_NUM04               21504
#define IDD_NUM05               21505
#define IDD_NUM06               21506
#define IDD_NUM07               21507
#define IDD_NUM08               21508
#define IDD_NUM09               21509
#define IDD_NUM10               21510
#define IDD_NUM11               21511
#define IDD_NUM12               21512
#define IDD_NUM13               21513
#define IDD_NUM14               21514
#define IDD_NUM15               21515

#define STR_SERVER_NOT_POSSIBLE 23500
#define STR_SERVER              23501
#define STR_BBOX_KENNUNG        23502

#define STR_OLD_FILE_SAVE       23503
#define STR_NO_DSB_NAME         23504
#define STR_ILL_BLOCKTIME       23505
#define STR_TIMECHANGE          23506

#define STR_TABLE_FILTER        23507
#define STR_TABLE_EXT           23508
#define STR_TABLE_LOAD          23509

#define STR_FLOWCHART_FILTER_NAME 23510

#define STR_FLOWCHART_LOAD      23512
#define STR_FLOWCHART_SAVE      23513
#define STR_MODULBAR_FILTER     23514
#define STR_MODULBAR_EXT        23515
#define STR_MODULBAR_LOAD       23516
#define STR_MODULBAR_SAVE       23517
#define STR_BBOX_FILTER         23518
#define STR_BBOX_EXT            23519
#define STR_BBOX_SAVE           23520
#define STR_BBOX_LOAD           23521

#define STR_DONGLE_UEBERSCHRIFT  23522
#define STR_DONGLE_UNKNOWN       23523
#define STR_DONGLE_INIT          23524
#define STR_DONGLE_LAUFZEIT      23525
#define STR_DONGLE_MISSING_DLL   23539

#define STR_STREAMING_FILTER     23526
#define STR_STREAMING_EXT        23527
#define STR_STREAMING_SAVE       23528
#define STR_DONGLE_TOO_MANY_USERS 23529

#define STR_NAME_EXIST           23530

#define STR_ILL_ACTION_TIME       23531

#define STR_STOP_REQUEST         23532

#define STR_SWITCH_RUNTIME       23533

#define STR_VAREXPORT_FILTER     23534
#define STR_VAREXPORT_EXT        23535
#define STR_VAREXPORT            23536
#define STR_VARIMPORT            23537
#define STR_VARIMPORT_ERROR      23538

#define STR_TEXTFILE_FILTER      23540
#define STR_TEXTFILE_EXT         23541
#define STR_DOCUMENTATION_FILTER 23542
#define STR_DOCUMENTATION_EXT    23543
#define STR_MATRIX_EXT           23544

#define STR_HTML_FILTER          61226
#define STR_HTML_EXT             61227

// ML, 09.07.2010 - UNIFIED_FILE_ACCESS
#define STR_INI_FILTER           61228
#define STR_INI_EXT              61229
#define STR_INI_LOAD             63106

#define STR_GLOBVAR_UNREGISTER                                           63107
#define STR_GLOBSTR_UNREGISTER                                           63108
#define STR_GLOBSTR_VAR_NOT_YET_UNREGISTER                               63109
#define STR_GLOBSTR_STR_NOT_YET_UNREGISTER                               63110
#define STR_GLOBSTR_SYSVAR_NOT_YET_UNREGISTER                            63111
#define STR_GLOBSTR_SYSSTR_NOT_YET_UNREGISTER                            63112

#define STR_GLOBSTR_USED_FROM_CHANNEL                                    63113


/* ------------------------------------------------------------------------ */
/* IDs für Dialogboxen Strunk (27000 - 27999)                               */
/* ------------------------------------------------------------------------ */

#define STR_ILL_INPUT           27901
#define STR_INP_FREQ_TOO_HIGH   27902
#define STR_DRUCKEN             27903
#define STR_START_DRUCK         27904
#define STR_PLEASE_SETUP        27905
#define STR_KEIN_STANDARD_DRUCKER 27906
#define STR_ILL_MULTIPLEX_INPUT 27907

#define  STR_DSB_CORRUPT        27011     /* DSB-Datei ist defekt */

#define  STR_MHZ                27020
#define  STR_KHZ                27021
#define  STR_HZ                 27022
#define  STR_MS                 27023
#define  STR_SEK                27024
#define  STR_MIN                27025

#define  STR_MESS_CONT          27026
#define  STR_MESS_RUNNING       27027
#define  STR_MESS_ISOLATED      27028
#define  STR_MESS_ONE_SHOT      27029

#define  STR_CO_RATE            27030
#define  STR_CO_PULSE           27031
#define  STR_CO_PWM             27032
#define  STR_CO_RESERVED1       27033
#define  STR_CO_RESERVED2       27034
#define  STR_CO_RESERVED3       27035
#define  STR_CO_RESERVED4       27036
#define  STR_CO_RESERVED5       27037
#define  STR_CO_RESERVED6       27038
#define  STR_CO_RESERVED7       27039

#define  STR_REMAINING_TIME     27060
#define  STR_ERR_30_STARTUP     27061
#define  STR_ERR_30_DSA         27062
#define  STR_ERR_30_DSB         27063
#define  STR_30_DAYS_STRING     27064
#define  STR_ERR_DEWE_DSB       27065
#define  STR_SCHOOL_VERSION_STRING 27066
#define  STR_ERR_X_DAYS_DSB     27067
#define  STR_ERR_X_DAYS_DSA     27068
#define  STR_ERR_X_DAYS_STARTUP 27069
#define  STR_ERR_SCHOOL_DSB     27083 
#define  STR_ERR_SCHOOL_DSA     27084 
// MHa 18.05.2011 - Bugfix zur CAR 299576 - Start
#define  STR_ERR_X_DAYS_STARTUP_SHORT_INFO 27085
// MHa 18.05.2011 - Bugfix zur CAR 299576 - Stop
#define  STR_30_DAYS_RUN_LIMIT  27090

/* Resource IDs for Module Replacement */
#define  STR_REPLACE_NOT_SUPPORTED  27601
#define  STR_REPLACE_NO_MOD_FOUND   27602
#define  STR_REPLACE_CREATE_ERROR   27603


/* Switch für Ausgabe-Umlenkung */

#define  OUT_SCREEN   0                       /* Ausgabe auf den Bildschirm */
#define  OUT_PRINTER  1                       /* Ausgabe auf den Drucker */
#define  OUT_META     2                       /* Ausgabe in ein Meta-File */
#define  OUT_PLOTTER  3                       /* Ausgabe auf den Plotter */

/* Default-Abmessungen des MetaFiles bei MM_ANISOTROPIC */


/* ------------------------------------------------------------------------ */
/* Globale Defines Magolei 42000-42999                                      */
/* ------------------------------------------------------------------------ */

#define MAX_BBOX_USER 20

#define STR_PASTE_ERR1                  42500
#define STR_PASTE_ERR2                  42501
#define STR_PASTE_ERR3                  42502
#define STR_PASTE_ERR4                  42503
#define STR_PASTE_ERR5                  42504
#define STR_PASTE_ERR6                  42505
#define STR_PASTE_ERR7                  42506
#define STR_PASTE_ERR8                  42507 
#define STR_PASTE_ERR9                  42508

/* ------------------------------------------------------------------------ */
/* Globale Defines Rottmann 43000-43999                                     */
/* ------------------------------------------------------------------------ */

#define REOPEN_NORMAL               (UINT) 43000
#define REOPEN_ZOOM                 (UINT) 43001
#define REOPEN_ICONIC               (UINT) 43002

#define STATUS_NORMAL               (UINT) 43003
#define STATUS_HILFE                (UINT) 43004

#define ID_TIMER_STATUS             (UINT) 43005
#define ID_TIMER_50                 (UINT) 43006
#define ID_TIMER_2000               (UINT) 43009
#define ID_TIMER_MAIN               (UINT) 43010

#define STATUS_NORMAL_1             (UINT) 43007
#define STATUS_NORMAL_2             (UINT) 43008

#define WM_CLICK_LDOWN              (UINT) (WM_USER+1)
#define WM_CLICK_LUP                (UINT) (WM_USER+2)
#define WM_DCLICK_L                 (UINT) (WM_USER+3)
#define WM_DCLICK_R                 (UINT) (WM_USER+4)
#define WM_AUSSCHALTEN              (UINT) (WM_USER+5)
#define WM_PAINTBLOCK               (UINT) (WM_USER+6)
#define WM_COPYFOCUS                (UINT) (WM_USER+7)
#define WM_COPYALL                  (UINT) (WM_USER+8)

#define MODE_LAY_DONT_CHANGE        0
#define MODE_LAY_MINIMIZE           1
#define MODE_LAY_HIDE               2

#define WM_TCPIP_EVENT              (UINT) (WM_USER+9)

#define WM_SEND_PANEL_MESSAGE       (UINT) (WM_USER+10)
#define WM_BROADCAST_PANEL_MESSAGE  (UINT) (WM_USER+11)

#define WM_SEND_MODULE_MESSAGE      (UINT) (WM_USER+12)

#define WM_INPUT_GLOBAL_STRINGS     (UINT) (WM_USER+13)
#define WM_INPUT_GLOBAL_VARS        (UINT) (WM_USER+14)
#define WM_SHOW_NEXT_MDI            (UINT) (WM_USER+15)
#define WM_INPUT_FILE_NAME          (UINT) (WM_USER+16)

#define WM_ACKNOWLEDGE_MSG          (UINT) (WM_USER+17)

#define WM_NEXTCOL                  (UINT) (WM_USER+18)
#define WM_NEXTROW                  (UINT) (WM_USER+19)

#define WM_STOP_EXPERIMENT          (UINT) (WM_USER+20)
#define WM_STOP_AND_TERMINATE       (UINT) (WM_USER+21)

#define WM_STOP_AND_TERMINATE_REQUEST         (UINT) (WM_USER+22)

#define WM_CLICK_RDOWN              (UINT) (WM_USER+23)
#define WM_CLICK_RUP                (UINT) (WM_USER+24)

#define WM_GET_MAIN_DISPL_WND       (UINT) (WM_USER+25)
#define WM_SAVE_PANEL_OBJ           (UINT) (WM_USER+26)

/* ------------------------------------------------------------------------ */
/* Globale Defines Fehlermeldungen 64000-64999                              */
/* ------------------------------------------------------------------------ */

#define DATEN_NICHT_GESICHERT       (UINT) 64010
#define PROFILDATEI_FEHLER          (UINT) 64011
#define TREIBER_NICHT_ENTFERNT      (UINT) 64012
#define SPEICHER_NICHT_OK           (UINT) 64013



/* ------------------------------------------------------------------------ */
/* Globale Default-Skalierung                                               */
/* ------------------------------------------------------------------------ */

#define  ONE_VOLT  1.0           /* Interne Darstellung für ein Volt */
#define  DEF_UNIT  "Volt"        /* Default für Einheit */

/* TTL-Norm: Über 2 Volt ist High, unter 0.8 Volt ist Low, sonst undefiniert. */
/* Wir (Bi,CS) legen hier im undefinierten Bereich die Grenze auf 1.5 Volt */

#define  IS_TRUE_TTL_HIGH(a) ((a)>=2.0*ONE_VOLT)
#define  IS_TRUE_TTL_LOW(a) ((a)<=0.8*ONE_VOLT)

#define  IS_TTL_HIGH(a) ((a)>1.5*ONE_VOLT)
#define  IS_TTL_LOW(a) ((a)<=1.5*ONE_VOLT)


/* ------------------------------------------------------------------------ */
/* Gelbe Lampe anzeigen ?                                                   */
/* ------------------------------------------------------------------------ */

#define  WARN_LOST_DATA  TRUE


/* ------------------------------------------------------------------------ */
/* Sequencer Event Conditions                                               */
/* ------------------------------------------------------------------------ */

#define  SEQCOND_RISING_EDGE        0
#define  SEQCOND_FALLING_EDGE       1
#define  SEQCOND_EXCEED_VAL         2
#define  SEQCOND_FALL_BELOW_VAL     3
#define  SEQCOND_TTL_HIGH           4
#define  SEQCOND_TTL_LOW            5
#define  SEQCOND_ABOVE_LIMIT        6
#define  SEQCOND_BELOW_LIMIT        7
#define  SEQCOND_ALWAYS             8
#define  SEQCOND_NEVER              9
#define  SEQCOND_START             10
#define  SEQCOND_STOP              11
#define  SEQCOND_STRING_CHANGED    12
#define  SEQCOND_VAR_CHANGED       13
#define  SEQCOND_VAL_REACHED       14

#define  STR_SEQCONDITION           28900
#define  STR_SEQCOND_RISING_EDGE    (STR_SEQCONDITION + SEQCOND_RISING_EDGE)
#define  STR_SEQCOND_FALLING_EDGE   (STR_SEQCONDITION + SEQCOND_FALLING_EDGE)
#define  STR_SEQCOND_EXCEED_VAL     (STR_SEQCONDITION + SEQCOND_EXCEED_VAL)
#define  STR_SEQCOND_FALL_BELOW_VAL (STR_SEQCONDITION + SEQCOND_FALL_BELOW_VAL)
#define  STR_SEQCOND_TTL_HIGH       (STR_SEQCONDITION + SEQCOND_TTL_HIGH)
#define  STR_SEQCOND_TTL_LOW        (STR_SEQCONDITION + SEQCOND_TTL_LOW)
#define  STR_SEQCOND_ABOVE_LIMIT    (STR_SEQCONDITION + SEQCOND_ABOVE_LIMIT)
#define  STR_SEQCOND_BELOW_LIMIT    (STR_SEQCONDITION + SEQCOND_BELOW_LIMIT)
#define  STR_SEQCOND_ALWAYS         (STR_SEQCONDITION + SEQCOND_ALWAYS)
#define  STR_SEQCOND_NEVER          (STR_SEQCONDITION + SEQCOND_NEVER)
#define  STR_SEQCOND_START          (STR_SEQCONDITION + SEQCOND_START)
#define  STR_SEQCOND_STOP           (STR_SEQCONDITION + SEQCOND_STOP)
#define  STR_SEQCOND_STRING_CHANGED (STR_SEQCONDITION + SEQCOND_STRING_CHANGED)
#define  STR_SEQCOND_VAR_CHANGED    (STR_SEQCONDITION + SEQCOND_VAR_CHANGED)
#define  STR_SEQCOND_VAL_REACHED    (STR_SEQCONDITION + SEQCOND_VAL_REACHED)



/* ------------------------------------------------------------------------ */
/* Ereignisse, die von DASYLab an die Module versendet werden               */
/* ------------------------------------------------------------------------ */

#define  COND_RISING_EDGE        0
#define  COND_FALLING_EDGE       1
#define  COND_EXCEED_VAL         2
#define  COND_FALL_BELOW_VAL     3
#define  COND_TTL_HIGH           4
#define  COND_TTL_LOW            5
#define  COND_ABOVE_LIMIT        6
#define  COND_BELOW_LIMIT        7
#define  COND_ALWAYS             8
#define  COND_NEVER              9
#define  COND_START             10
#define  COND_STOP              11
#define  COND_STRING_CHANGED    12
#define  COND_VAR_CHANGED       13
#define  COND_INPUT_CHANGED     14
#define  COND_INPUT_REACHED     15
#define  COND_INPUT_EQUAL       16

/* #define  COND_INPUT_XXX      17  das ist die nächste Kondition die benutzt werden darf */
#define  COND_LAST              COND_INPUT_EQUAL /* Hier muss immer die letzte Kondition eingetragen werden!!! */

#define  STR_NO_ACTION_RESPONSE   27999

#define  STR_CONDITION           28000
#define  STR_COND_RISING_EDGE    (STR_CONDITION + COND_RISING_EDGE)
#define  STR_COND_FALLING_EDGE   (STR_CONDITION + COND_FALLING_EDGE)
#define  STR_COND_EXCEED_VAL     (STR_CONDITION + COND_EXCEED_VAL)
#define  STR_COND_FALL_BELOW_VAL (STR_CONDITION + COND_FALL_BELOW_VAL)
#define  STR_COND_TTL_HIGH       (STR_CONDITION + COND_TTL_HIGH)
#define  STR_COND_TTL_LOW        (STR_CONDITION + COND_TTL_LOW)
#define  STR_COND_ABOVE_LIMIT    (STR_CONDITION + COND_ABOVE_LIMIT)
#define  STR_COND_BELOW_LIMIT    (STR_CONDITION + COND_BELOW_LIMIT)
#define  STR_COND_ALWAYS         (STR_CONDITION + COND_ALWAYS)
#define  STR_COND_NEVER          (STR_CONDITION + COND_NEVER)
#define  STR_COND_START          (STR_CONDITION + COND_START)
#define  STR_COND_STOP           (STR_CONDITION + COND_STOP)
#define  STR_COND_STRING_CHANGED (STR_CONDITION + COND_STRING_CHANGED)
#define  STR_COND_VAR_CHANGED    (STR_CONDITION + COND_VAR_CHANGED)
#define  STR_COND_INPUT_CHANGED  (STR_CONDITION + COND_INPUT_CHANGED)
#define  STR_COND_INPUT_REACHED  (STR_CONDITION + COND_INPUT_REACHED)
#define  STR_COND_INPUT_EQUAL    (STR_CONDITION + COND_INPUT_EQUAL)


#define  ACTION_NULL                         0
#define  ACTION_PRINT                        1
#define  ACTION_RESET                        2
#define  ACTION_SET                          3
#define  ACTION_FADE_IN                      4
#define  ACTION_FADE_OUT                     5
#define  ACTION_NEXT                         6
#define  ACTION_TO_CLIPBPOARD                7
#define  ACTION_ONE_WINDOW                   8
#define  ACTION_MULTI_WINDOW                 9
#define  ACTION_SET_CAPTION                  10
#define  ACTION_WARN_MESSAGE                 11
#define  ACTION_SEL_WIN_SETUP                12

#define  ACTION_USER_0                       13
#define  ACTION_USER_1                       14
#define  ACTION_USER_2                       15
#define  ACTION_USER_3                       16
#define  ACTION_USER_4                       17
#define  ACTION_USER_5                       18
#define  ACTION_USER_6                       19
#define  ACTION_USER_7                       20
#define  ACTION_USER_8                       21
#define  ACTION_USER_9                       22
#define  ACTION_USER_10                      23
#define  ACTION_USER_11                      24
#define  ACTION_USER_12                      25
#define  ACTION_USER_13                      26
#define  ACTION_USER_14                      27
#define  ACTION_USER_15                      28
#define  ACTION_USER_16                      29
#define  ACTION_USER_17                      30
#define  ACTION_USER_18                      31
#define  ACTION_USER_19                      32
#define  ACTION_USER_20                      33
#define  ACTION_USER_21                      34
#define  ACTION_USER_22                      35
#define  ACTION_USER_23                      36
#define  ACTION_USER_24                      37

#define  MAX_ACTION_USER_OLD                 ACTION_USER_24

#define  ACTION_LOAD_DSB                     38
#define  ACTION_LOAD_GO_DSB                  39
#define  ACTION_BACKUP                       40
#define  ACTION_PRINT_LAYOUT                 41
#define  ACTION_FULLSCREEN_LAYOUT            42
#define  ACTION_ACTIVATE_LAYOUT              43

#define  ACTION_SET_VAR                      44
#define  ACTION_SET_STRING                   45
#define  ACTION_SAVE_VAR                     46
#define  ACTION_SAVE_STRING                  47
#define  ACTION_LOAD_VAR                     48
#define  ACTION_LOAD_STRING                  49
#define  ACTION_ADD_VAR                      50
#define  ACTION_MULT_VAR                     51
#define  ACTION_NORMALIZE_LAYOUT             52
#define  ACTION_SHOW_WORKSHEET               53
#define  ACTION_UPDATE_LAYOUTER_OBJECTS      54
#define  ACTION_INPUT_GLOBAL_STRINGS         55
#define  ACTION_INPUT_GLOBAL_VARS            56
#define  ACTION_START_EXTERNAL_PROGRAM       57
#define  ACTION_EXIT_DASYLAB                 58
#define  ACTION_EXIT_WINDOWS                 59
#define  ACTION_EXIT_RESTART_WINDOWS         60
#define  ACTION_MESSAGE_BEEP                 61
#define  ACTION_STOP_DSB                     62
#define  ACTION_STOP_RESTART_DSB             63
#define  ACTION_SAVE_VAR_TO_FILE             64
#define  ACTION_SAVE_STRING_TO_FILE          65
#define  ACTION_LOAD_VAR_FROM_FILE           66
#define  ACTION_LOAD_STRING_FROM_FILE        67
#define  ACTION_CREATE_DIR                   68
#define  ACTION_COPY_VAR                     69
#define  ACTION_COPY_STRING                  70
#define  ACTION_SHOW_TREEVIEW                71
#define  ACTION_MULTISAVE_VAR                72
#define  ACTION_MULTISAVE_STRING             73
#define  ACTION_MULTILOAD_VAR                74
#define  ACTION_MULTILOAD_STRING             75
#define  ACTION_MULTISAVE_VAR_TO_FILE        76
#define  ACTION_MULTISAVE_STRING_TO_FILE     77
#define  ACTION_MULTILOAD_VAR_FROM_FILE      78
#define  ACTION_MULTILOAD_STRING_FROM_FILE   79
#define  ACTION_INPUT_FILE_NAME              80
#define  ACTION_SCREEN_LOCK                  81
#define  ACTION_SCREEN_UNLOCK                82
#define  ACTION_LAYOUT_TO_CLIPBOARD_METAFILE 83
#define  ACTION_LAYOUT_TO_WMF                84
#define  ACTION_LAYOUT_TO_BMP                85
#define  ACTION_LAYOUT_TO_JPEG               86
#define  ACTION_MULTISET_VAR                 87
#define  ACTION_MULTISET_STRING              88
#define  ACTION_PAUSE_EXPERIMENT             89
#define  ACTION_STOP_AND_TERMINATE_REQUEST   90

#define  ACTION_USER_25                      91
#define  ACTION_USER_26                      92
#define  ACTION_USER_27                      93
#define  ACTION_USER_28                      94
#define  ACTION_USER_29                      95
#define  ACTION_USER_30                      96
#define  ACTION_USER_31                      97
#define  ACTION_USER_32                      98
#define  ACTION_USER_33                      99
#define  ACTION_USER_34                      100
#define  ACTION_USER_35                      101
#define  ACTION_USER_36                      102
#define  ACTION_USER_37                      103
#define  ACTION_USER_38                      104
#define  ACTION_USER_39                      105
#define  ACTION_USER_40                      106
#define  ACTION_USER_41                      107
#define  ACTION_USER_42                      108
#define  ACTION_USER_43                      109
#define  ACTION_USER_44                      110
#define  ACTION_USER_45                      111
#define  ACTION_USER_46                      112
#define  ACTION_USER_47                      113
#define  ACTION_USER_48                      114
#define  ACTION_USER_49                      115

/* ACTION_USER actions können bis Id.Nr. 199 noch vorgesetzt werden! */
/* das sollte reichen */

#define  MAX_ACTION_USER_NEWSTART            ACTION_USER_25
#define  MAX_ACTION_USER                     199

/* Nächste allgemeine DASYLab Aktion beginnt dann bei 200 */
#define  ACTION_LAYOUT_TO_CLIPBOARD_BITMAP   200
#define  ACTION_NEXT_LAYOUT                  201
#define  ACTION_NEXT_FULLSCREEN_LAYOUT       202
#define  ACTION_SELECT_LAYOUT                203
#define  ACTION_MULTICOPY_VAR				      204
#define  ACTION_MULTICOPY_STRING				   205
#define  ACTION_LAYOUT_TO_PNG                206
#define  ACTION_EXIT_LOGOFF_WINDOWS          207

#define  STR_ACTION_NULL                28100
#define  STR_ACTION_PRINT               28101
#define  STR_ACTION_RESET               28102
#define  STR_ACTION_SET                 28103
#define  STR_ACTION_SET_WERT            28104
#define  STR_ACTION_FADE_IN             28105
#define  STR_ACTION_FADE_OUT            28106
#define  STR_ACTION_NEXT                28107
#define  STR_ACTION_LOAD_DSB            28108
#define  STR_ACTION_LOAD_GO_DSB         28109
#define  STR_ACTION_LOAD_DSB_TEXT       28110
#define  STR_ACTION_TO_CLIPBPOARD       28112
#define  STR_ACTION_ONE_WINDOW          28113
#define  STR_ACTION_MULTI_WINDOW        28114
#define  STR_ACTION_SET_CAPTION         28115
#define  STR_ACTION_SET_CAPTION_TEXT    28116
#define  STR_ACTION_WARN_MESSAGE        28117
#define  STR_ACTION_WARN_MESSAGE_TEXT   28118
#define  STR_ACTION_SEL_WIN_SETUP       28119
#define  STR_ACTION_SEL_WIN_SETUP_NUM   28120
#define  STR_ACTION_BACKUP              28121
#define  STR_ACTION_BACKUP_DIR          28122

#define  STR_ACTION_PRINT_LAYOUT        28123
#define  STR_ACTION_FULLSCREEN_LAYOUT   28124
#define  STR_ACTION_ACTIVATE_LAYOUT     28125
#define  STR_ACTION_LAYOUT              28126
#define  STR_ACTION_NORMALIZE_LAYOUT    28127        
#define  STR_ACTION_SHOW_WORKSHEET      28128

#define  STR_ACTION_SET_VAR             28129
#define  STR_ACTION_SET_STRING          28130
#define  STR_ACTION_SAVE_VAR            28131
#define  STR_ACTION_SAVE_STRING         28132
#define  STR_ACTION_LOAD_VAR            28133
#define  STR_ACTION_LOAD_STRING         28134
#define  STR_ACTION_NUMBER              28135
#define  STR_ACTION_VALUE               28136
#define  STR_ACTION_STRING              28137
#define  STR_ACTION_ADD_VAR             28138
#define  STR_ACTION_MULT_VAR            28139

#define  STR_ACTION_UPDATE_LAYOUTER_OBJECTS  28141
#define  STR_ACTION_INPUT_GLOBAL_STRINGS     28142
#define  STR_ACTION_INPUT_GLOBAL_VARS        28143
#define  STR_ACTION_GLSTR                    28144
#define  STR_ACTION_GLVAR                    28145
#define  STR_ACTION_TITLE                    28146

#define  STR_ACTION_START_EXTERNAL_PROGRAM   28147
#define  STR_INPUT_CMD_LINE                  28148

#define  STR_ACTION_EXIT_DASYLAB             28150
#define  STR_ACTION_EXIT_WINDOWS             28151
#define  STR_ACTION_EXIT_RESTART_WINDOWS     28152
#define  STR_ACTION_MESSAGE_BEEP             28153
#define  STR_ACTION_STOP_DSB                 28154
#define  STR_ACTION_STOP_RESTART_DSB         28155

#define  STR_ACTION_SAVE_VAR_TO_FILE         28156
#define  STR_ACTION_SAVE_STRING_TO_FILE      28158
#define  STR_ACTION_LOAD_VAR_FROM_FILE       28159
#define  STR_ACTION_LOAD_STRING_FROM_FILE    28160
#define  STR_ACTION_FILE                     28161

#define  STR_ACTION_CREATE_DIR               28162
#define  STR_ACTION_CREATE_DIR_TEXT          28163
#define  STR_ACTION_COPY_VAR                 28164
#define  STR_ACTION_COPY_STRING              28165
#define  STR_ACTION_COPY_FROM                28166
#define  STR_ACTION_COPY_TO                  28167
#define  STR_ACTION_SHOW_TREEVIEW            28168

#define  STR_ACTION_MULTISAVE_VAR            28169
#define  STR_ACTION_MULTISAVE_STRING         28170
#define  STR_ACTION_MULTILOAD_VAR            28171
#define  STR_ACTION_MULTILOAD_STRING         28172
#define  STR_ACTION_MULTISAVE_VAR_TO_FILE    28173
#define  STR_ACTION_MULTISAVE_STRING_TO_FILE 28174
#define  STR_ACTION_MULTILOAD_VAR_FROM_FILE  28175
#define  STR_ACTION_MULTILOAD_STRING_FROM_FILE 28176

#define  STR_ACTION_COPY_COUNT               28178

#define  STR_ACTION_FROM                     28180
#define  STR_ACTION_TO                       28181
#define  STR_ACTION_INPUT_FILE_NAME          28182

#define  STR_ACTION_SCREEN_LOCK              28183
#define  STR_ACTION_SCREEN_UNLOCK            28184
#define  STR_ACTION_LAYOUT_TO_CLIPBOARD      28185
#define  STR_ACTION_LAYOUT_TO_WMF            28186
#define  STR_ACTION_LAYOUT_TO_BMP            28187
#define  STR_ACTION_LAYOUT_TO_JPEG           28188

#define  STR_ACTION_MULTISET_VAR             28189
#define  STR_ACTION_MULTISET_STRING          28190

#define  STR_ACTION_PAUSE_EXPERIMENT         28191

#define  STR_ACTION_STOP_AND_TERMINATE_REQUEST 28192
#define  STR_ACTION_LAYOUT_TO_CLIPBOARD_BITMAP 28193
#define  STR_ACTION_NEXT_LAYOUT              28194
#define  STR_ACTION_NEXT_FULLSCREEN_LAYOUT   28195
#define  STR_ACTION_SELECT_LAYOUT            28196
#define  STR_ACTION_MULTICOPY_VAR            28197
#define  STR_ACTION_MULTICOPY_STRING         28198
#define  STR_ACTION_LAYOUT_TO_PNG            28199

#define  STR_MF_CHANNEL                      28200
#define  STR_MF_NUMBER                       28201
#define  STR_MF_MISSING_FILENAME             28202

#define  STR_ACTION_EXIT_LOGOFF_WINDOWS      28203

#define  STR_GLSTR_LOAD_WITHFILENAME         28204

#define  STR_ACTION_SCALE_OR_DPI             28205




/* ------------------------------------------------------------------------ */
/* Variablenübersicht                                                       */
/* ------------------------------------------------------------------------ */

// Variablenübersicht Version
#define GLVO_VERSION       1

// Variablen-Zugriff 
#define GLVO_ACCESS_NONE                     0
#define GLVO_ACCESS_READ                     1
#define GLVO_ACCESS_WRITE                    2
#define GLVO_ACCESS_RW                       3

// Verwendung von globalen Variablen/Strings in Modulen
#define GLVO_VARUSAGE_NEVER                  0
#define GLVO_VARUSAGE_NOT_YET                1
#define GLVO_VARUSAGE_USED                   2
#define GLVO_VARUSAGE_USED_AS_INDEX          3

// Variablentype Nummer oder String
#define GLVO_VARTYPE_NONE                    0
#define GLVO_VARTYPE_NUMBER                  1
#define GLVO_VARTYPE_STRING                  2
#define GLVO_VARTYPE_NUMSTR                  3
#define GLVO_VARTYPE_SYSTEM                  4

// Layout Objekt-Typen
#define GLVO_LAYOBJ_MULTILINE                0
#define GLVO_LAYOBJ_MODULELINK               1
#define GLVO_LAYOBJ_TEXT                     2
#define GLVO_LAYOBJ_GRID                     3

// Fehlercodes
#define GLVOERR_NOERR                        0     // Kein Fehler
#define GLVOERR_VARINUSE_CHECK_FAILED        1     // Fehler der Funktion isVariableInUse
#define GLVOERR_INVALID_VARTYPE              2     // Ungültiger Variablentype kann nur GLVO_VARTYPE_NUMBER oder GLVO_VARTYPE_STRING sein.
#define GLVOERR_INCOMP_VERSION               3     // Glvo Versionsnummern von Dasylab und dem Modul stimmen nicht überein
#define GLVOERR_INVALID_CHANNEL              4     // Ungültige Kanalnummer 


// Fehler in der Listenverwaltung:
#define GLVOERR_LIST_NOERR                   10    // kein Fehler
#define GLVOERR_LIST_NOMEM                   11    // Es konnte kein Speicher angefordert werden
#define GLVOERR_LIST_BAD_PARM                12    // Ungültige Paramter (z.B. nicht erwarteter Nullzeiger usw.)
#define GLVOERR_LIST_INCONSISTENCE           13    // Interne Datenstruktur ist inkonsistent
#define GLVOERR_LIST_NO_ITEM                 14    // Es ist kein weiteres Item vorhanden.
#define GLVOERR_LIST_SIZE_MISMATCH           15    // Die angeforderte Größe der Daten stimmt nicht mit der gespeicherten Größe in der Liste überein.
#define GLVO_USAGEDESCRIPTION_MAXLEN         128

#define STR_GLVO_FILENAME                    32005
#define STR_GLVO_ACT_FILENAME                32006
#define STR_GLVO_FLEX4_DESCR                 32007

#define STR_GLVO_DDECNT_START1               32050
#define STR_GLVO_DDECNT_INC1                 32051
#define STR_GLVO_DDECNT_INCCOND1             32052
#define STR_GLVO_DDECNT_RESTARTAT1           32053
#define STR_GLVO_DDECNT_RESTART1             32054
#define STR_GLVO_DDECNT_START2               32055
#define STR_GLVO_DDECNT_INC2                 32056
#define STR_GLVO_DDECNT_INCCOND2             32057
#define STR_GLVO_DDECNT_RESTARTAT2           32058
#define STR_GLVO_DDECNT_RESTART2             32059

#define STR_GLVO_LAYOUT_GRID_ROW             32060
#define STR_GLVO_LAYOUT_GRID_COLUMN          32061

#define IDD_GLVO_SEARCHSTRING                21000
#define IDD_GLVO_CASE_SENSITIVE              21001



/* ------------------------------------------------------------------------ */
/* DASYLab Explorer                                                         */
/* ------------------------------------------------------------------------ */

#define ID_EXPL_START                        32100

// Context Menu
#define STR_EXPL_MENU_COLLAPSE_BRANCH           (ID_EXPL_START +    0)
#define STR_EXPL_MENU_COLLAPSE_ALL              (ID_EXPL_START +    1)
#define STR_EXPL_MENU_SHOW_ALL                  (ID_EXPL_START +    2)
#define STR_EXPL_MENU_EXPAND                    (ID_EXPL_START +    3)
#define STR_EXPL_MENU_SEARCH                    (ID_EXPL_START +    4)
#define STR_EXPL_MENU_SEARCH_CONTINUE           (ID_EXPL_START +    5)
#define STR_EXPL_MENU_INSERT_CURRENT_BLACKBOX   (ID_EXPL_START +    6)
#define STR_EXPL_MENU_INSERT_DIRNODE            (ID_EXPL_START +    7)
#define STR_EXPL_MENU_REMOVE_ITEM               (ID_EXPL_START +    8)
#define STR_EXPL_MENU_GOTO                      (ID_EXPL_START +    9)
#define STR_EXPL_MENU_OPEN_MODULE_DLG           (ID_EXPL_START +   10)

// Tabs
#define STR_EXPL_TAB_MODULE                     (ID_EXPL_START +   11)
#define STR_EXPL_TAB_FAVORITES                  (ID_EXPL_START +   12)
#define STR_EXPL_TAB_BLACK_BOX                  (ID_EXPL_START +   13)
#define STR_EXPL_TAB_NAVIGATOR                  (ID_EXPL_START +   14)

// Tab Reiter
#define EXPLTAB_MODULES                         0
#define EXPLTAB_BBOX                            1
#define EXPLTAB_NAVIGATOR                       2

// Fifo Debug List
#define FIFOLIST_FIFO_PARAM                     (ID_EXPL_START +   15)
#define FIFOLIST_FIFO_VALUE                     (ID_EXPL_START +   16)
#define FIFOLIST_BLOCKSIZE                      (ID_EXPL_START +   17)
#define FIFOLIST_REAL_BLOCKSIZE                 (ID_EXPL_START +   18)
#define FIFOLIST_COUNT_BLOCKS                   (ID_EXPL_START +   19)
#define FIFOLIST_SAMPLE_RATE                    (ID_EXPL_START +   20)
#define FIFOLIST_FIFO_BLOCKS                    (ID_EXPL_START +   21)
#define FIFOLIST_FIFO_LOCKED_BLOCKS             (ID_EXPL_START +   22)
#define FIFOLIST_START_TIME_REL                 (ID_EXPL_START +   23)
#define FIFOLIST_START_TIME_ABS                 (ID_EXPL_START +   24)
#define FIFOLIST_DIFF_TIME                      (ID_EXPL_START +   25)
#define FIFOLIST_CURRENT_VALUE                  (ID_EXPL_START +   26)
#define FIFOLIST_CHANNEL_TYPE                   (ID_EXPL_START +   27)
#define FIFOLIST_CHANNEL_FLAGS                  (ID_EXPL_START +   28)
#define FIFOLIST_OUTPUT                         (ID_EXPL_START +   29)
#define FIFOLIST_INPUT                          (ID_EXPL_START +   30)

// Black Box Explorer
#define BBEXP_DEL_DIR_FAILED                    (ID_EXPL_START +   31)
#define BBEXP_DEL_BOX_FAILED                    (ID_EXPL_START +   32)
#define BBEXP_NAME                              (ID_EXPL_START +   33)




/* ------------------------------------------------------------------------ */
/* Globale Strings und Variablen                                            */
/* Änderungen nur unter Rücksprache mit H.Rottmann oder R.Magolei!!!!!!!!!  */
/* ------------------------------------------------------------------------ */

#define  GLSTR_MAX_NUMBER           1001
#define  GLVAR_MAX_NUMBER           1001

#define GLSTR_MAX_NAME_LEN            20

/* ------------------------------------------------------------------------ */
/* MHa 15.01.2008 - Bugfix zur CAR 4CD9J3GS "allgemein >> Korrektur der     */
/* Handhabung von Pfadangaben erforderlich"                                 */
/* Projektname = LONG_MULTIBYTE_FILENAMES                                   */
/* ------------------------------------------------------------------------ */
#define GLSTR_MAX_STR_LEN_V5                                               256
#define GLSTR_MAX_STR_LEN_V6                                               256
#define GLSTR_MAX_EXP_LEN_V6                                               256
#define GLSTR_MAX_STR_LEN_V7                                               256
#define GLSTR_MAX_EXP_LEN_V7                                               256
#define GLSTR_MAX_STR_LEN_V10                                              256
#define GLSTR_MAX_EXP_LEN_V10                                              256
#define GLVAR_MAX_EXP_LEN_V10                                              256

#define GLSTR_MAX_STR_LEN                     BUFSIZE_MAX_PATH_LENGTH_FOR_DLAB
#define GLSTR_MAX_EXP_LEN                     BUFSIZE_MAX_PATH_LENGTH_FOR_DLAB
#define GLVAR_MAX_EXP_LEN                     BUFSIZE_MAX_PATH_LENGTH_FOR_DLAB

#define GLSYSVAR_MAX_NUMBER           50
#define GLSYSSTR_MAX_NUMBER           50
#define GLSYSVAR_OFFSET             1000
#define GLSYSSTR_OFFSET             1000

/* ------------------------------------------------------------------------ */
/* Kommunikation zwischen DASYLab und dem DLL-Toolkit                       */
/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Menu Items setting from TKDlls Structures                                */
/* ------------------------------------------------------------------------ */
#define DASYLAB_INSERT_MENU_VERSION    1
#define MAIN_MENU_ENTRY_MAXLEN       256
#define SUB_MENUS_ENTRY_MAXLEN      1024
// MHa 04.06.2012 - Projekt "xnet_driver" - Start
#define MENU_MENUACCESSKEY_MAXLEN                                            2
// MHa 04.06.2012 - Projekt "xnet_driver" - Stop


#define  TOOLKIT_VERSION            2  

#define  WM_GET_DASYLAB_VARIABLE    30000
#define  WM_GET_DASYLAB_FUNCTION    30001
#define  WM_LOAD_WORKSHEET          30002

#define  WM_SET_DASYLAB_VARIABLE    30010

#define STR_MISSING_WORKSHEET_PATH 22004
#define STR_MISSING_STREAMING_PATH 22005
#define STR_MISSING_DATA_PATH      22006
#define STR_MISSING_DEVISE_PATH    22007
#define STR_MISSING_BLACK_BOX_PATH 22008
#define STR_MISSING_DIV_PATH       22009
#define STR_FILE_ERR_CREATEFILE    22010
#define STR_FILE_ERR_READFILE      22011


/* ------------------------------------------------------------------------ */
/* Ml 02.06.2010 - DASYLab 12.0 Feature - CONFIGURATOR                      */
/* ------------------------------------------------------------------------ */

#define STR_LINK_DSB_TYPENAME   63000
#define STR_LINK_DSA_TYPENAME   63001
#define STR_LINK_DMX_TYPENAME   63002
#define STR_LINK_DSQ_TYPENAME   63003
#define STR_LINK_DSK_TYPENAME   63004
#define STR_LINK_DLP_TYPENAME   63005
#define STR_LINK_DSB_INFOTIP    63100
#define STR_LINK_DSA_INFOTIP    63101
#define STR_LINK_DMX_INFOTIP    63102
#define STR_LINK_DSQ_INFOTIP    63103
#define STR_LINK_DSK_INFOTIP    63104
#define STR_LINK_DLP_INFOTIP    63105


/* -eof- */
