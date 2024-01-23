/* ======================================================================== */
/* Programm   :  DLAB -  Messwerterfassung und Verarbeitung unter Windows   */
/* Datei      :  DLABUTIL.C                                                 */
/* ------------------------------------------------------------------------ */
/* Funktionen :  Hilfsfunktionen für DasyLab                                */
/* Erstellt   :  C. Strunk ab 13.02.93                                      */
/* Erweitert  :  ---  (Hier ggf. andere Programmierer eintragen)            */
/* Letzte Änd.:  13.02.93 CS                                                */
/* ======================================================================== */




/* ------------------------------------------------------------------------ */
/* Funktionsname     : ReleaseInputBlock                                    */
/* Beschreibung      : Sperrbit eines Eingangs-Blocks freigeben. Der Block  */
/*                   : wird dadurch als 'schon bearbeitet' markiert.        */
/* Aufrufparameter   : Modul und Eingangskanal-Nummer                       */
/* Rückgabewert      : --                                                   */
/* Globale Variablen : keine benutzt                                        */
/* Historie          : 13.02.1993  C. Strunk  (Erstellung)                  */
/*                   : 13.02.1993  CS (Letzte Änderung)                     */
/* ------------------------------------------------------------------------ */


/* Typdefinitionen für Importe aus DASYLab */
typedef void FAR * (TOOLAPI *PROTO_NewMemAlloc) ( DWORD nbytes, const char FAR *TheFile, int TheLine );
typedef void FAR * (TOOLAPI *PROTO_NewMemReAlloc) ( void FAR *ptr, DWORD nbytes, const char FAR *TheFile, int TheLine );
typedef void (TOOLAPI *PROTO_NewDoMemFree) ( void FAR *ptr, const char FAR *TheFile, int TheLine );

EXTERN PROTO_NewMemAlloc NewMemAlloc;
EXTERN PROTO_NewMemReAlloc NewMemReAlloc;
EXTERN PROTO_NewDoMemFree NewDoMemFree;

#define MemAlloc(n)        NewMemAlloc(n,__FILE__,__LINE__)
#define MemReAlloc(ptr,n)  NewMemReAlloc(ptr,n,__FILE__,__LINE__)
#define MemFree(ptr)       ( NewDoMemFree(ptr,__FILE__,__LINE__), ptr = NULL )

/* Die folgenden Funktionen sin in Modul.c definiert */
typedef BOOL (TOOLAPI  *PROTO_NewReleaseOutputBlock) (FIFO_HEADER FAR *Fifo, const char FAR *TheFile, int TheLine);
typedef DATA_BLOCK_HEADER FAR * (TOOLAPI  *PROTO_GetCurrentOutputBlock) (FIFO_HEADER FAR *);
typedef FIFO_HEADER FAR * (TOOLAPI *PROTO_GetInputFifo) ( MODULE FAR *ThisModule, UINT wKanalNr );
typedef DATA_BLOCK_HEADER FAR * (TOOLAPI *PROTO_GetInputBlock) ( MODULE FAR *ThisModule, UINT wKanalNr );
typedef void (TOOLAPI *PROTO_NewReleaseInputBlock) ( MODULE FAR *, UINT, const char FAR *TheFile, int TheLine );

/* Importe aus DASYLab */
EXTERN PROTO_NewReleaseOutputBlock NewReleaseOutputBlock;
#define ReleaseOutputBlock(f)    NewReleaseOutputBlock(f,__FILE__,__LINE__)
EXTERN PROTO_GetCurrentOutputBlock GetCurrentOutputBlock;
EXTERN PROTO_GetInputFifo GetInputFifo;
EXTERN PROTO_GetInputBlock GetInputBlock;
EXTERN PROTO_NewReleaseInputBlock NewReleaseInputBlock;
#define ReleaseInputBlock(mod,n)    NewReleaseInputBlock(mod,n,__FILE__,__LINE__)

typedef BOOL (TOOLAPI *PROTO_ChangeModuleSize) (MODULE FAR *, UINT, UINT);
EXTERN PROTO_ChangeModuleSize ChangeModuleSize;

typedef BOOL (TOOLAPI *PROTO_MODUL_InitAll) (void);
typedef BOOL (TOOLAPI *PROTO_MODUL_DestroyAll) (void);
typedef BOOL (TOOLAPI *PROTO_InitMatrixNew) (void);
EXTERN PROTO_MODUL_InitAll MODUL_InitAll;
EXTERN PROTO_MODUL_DestroyAll MODUL_DestroyAll;
EXTERN PROTO_InitMatrixNew InitMatrixNew;

// MX_RO 10.12.2015 Das API für das statische (Fifo) und dynamische (Block) Extra Memory
typedef BOOL (TOOLAPI *PROTO_EmemFifo_SETUP_MsgBuildInit) (FIFO_HEADER* OutFifo, UINT16 NumberOfChanges);
typedef BOOL (TOOLAPI *PROTO_EmemFifp_SETUP_MsgDataExchange) (FIFO_HEADER* OutFifo, UINT16 FifoMsgNo, UINT16 FifoMsgSize);
typedef BOOL (TOOLAPI *PROTO_EmemFifo_SETUP_MsgAdd) (FIFO_HEADER* OutFifo, UINT16 FifoMsgNo, UINT16 FifoMsgSize);
typedef BOOL (TOOLAPI *PROTO_EmemFifo_SETUP_MsgDelete) (FIFO_HEADER* OutFifo, UINT16 FifoMsgNo, UINT16 FifoMsgSize);
typedef BOOL (TOOLAPI *PROTO_EmemFifo_SETUP_MsgBuildFinalize) (FIFO_HEADER* OutFifo, UINT16 NumberOfChanges);
typedef BOOL (TOOLAPI *PROTO_EmemFifo_SETUP_MsgGetCnt) (FIFO_HEADER* InFifo, WORD* FifoMsgCnt);
typedef BOOL (TOOLAPI *PROTO_EmemFifo_SETUP_MsgExplain) (FIFO_HEADER* InFifo, UINT16 FifoMsgNo, UINT16* FifoMsgHandle);
typedef BOOL (TOOLAPI *PROTO_EmemFifo_SETUP_MsgRead) (FIFO_HEADER* InFifo, EMEM_HANDLE FifoMsgHandle, void* pMsg, UINT16 FifoMsgSize);
typedef BOOL (TOOLAPI *PROTO_EmemFifo_SETUP_MsgCopyPlain) (FIFO_HEADER* OutFifo, FIFO_HEADER* InFifo);
typedef BOOL (TOOLAPI *PROTO_EmemFifo_SETUP_MsgCopyModify) (FIFO_HEADER* OutFifo, FIFO_HEADER* InFifo, void* FifoMsgDataCluster, UINT16 TotalSize);

typedef BOOL (TOOLAPI *PROTO_EmemBlock_SETUP_MsgBuildInit) (FIFO_HEADER* OutFifo, UINT16 NumberOfChanges);
typedef BOOL (TOOLAPI *PROTO_EmemBlock_SETUP_MsgDataExchange) (FIFO_HEADER* OutFifo, UINT16 BlockMsgNo, UINT16 BlockMsgSize);
typedef BOOL (TOOLAPI *PROTO_EmemBlock_SETUP_MsgAdd) (FIFO_HEADER* OutFifo, UINT16 BlockMsgNo, UINT16 BlockMsgSize);
typedef BOOL (TOOLAPI *PROTO_EmemBlock_SETUP_MsgDelete) (FIFO_HEADER* OutFifo, UINT16 BlockMsgNo, UINT16 BlockMsgSize);
typedef BOOL (TOOLAPI *PROTO_EmemBlock_SETUP_MsgBuildFinalize) (FIFO_HEADER* OutFifo, UINT16 NumberOfChanges);
typedef BOOL (TOOLAPI *PROTO_EmemBlock_START_MsgGetCnt) (FIFO_HEADER* InFifo, WORD* BlockMsgCnt);
typedef BOOL (TOOLAPI *PROTO_EmemBlock_START_MsgExplain) (FIFO_HEADER* InFifo, UINT16 BlockMsgNo, UINT16* BlockMsgHandle);
typedef BOOL (TOOLAPI *PROTO_EmemBlock_PROCESS_MsgRead) (FIFO_HEADER* InFifo, DATA_BLOCK_HEADER* InBlock, EMEM_HANDLE BlockMsgHandle, void* pMsg, UINT16 BlockMsgSize);
typedef BOOL (TOOLAPI *PROTO_EmemBlock_PROCESS_MsgCopyPlain) (FIFO_HEADER* OutFifo, DATA_BLOCK_HEADER* OutBlock, FIFO_HEADER* InFifo, DATA_BLOCK_HEADER* InBlock);
typedef BOOL (TOOLAPI *PROTO_EmemBlock_PROCESS_MsgCopyModify) (FIFO_HEADER* OutFifo, DATA_BLOCK_HEADER* OutBlock, FIFO_HEADER* InFifo, DATA_BLOCK_HEADER* InBlock, void* BlockMsgDataCluster, UINT16 TotalSize);

EXTERN PROTO_EmemFifo_SETUP_MsgBuildInit EmemFifo_SETUP_MsgBuildInit;
EXTERN PROTO_EmemFifp_SETUP_MsgDataExchange EmemFifp_SETUP_MsgDataExchange;
EXTERN PROTO_EmemFifo_SETUP_MsgAdd EmemFifo_SETUP_MsgAdd;
EXTERN PROTO_EmemFifo_SETUP_MsgDelete EmemFifo_SETUP_MsgDelete;
EXTERN PROTO_EmemFifo_SETUP_MsgBuildFinalize EmemFifo_SETUP_MsgBuildFinalize;
EXTERN PROTO_EmemFifo_SETUP_MsgGetCnt EmemFifo_SETUP_MsgGetCnt;
EXTERN PROTO_EmemFifo_SETUP_MsgExplain EmemFifo_SETUP_MsgExplain;
EXTERN PROTO_EmemFifo_SETUP_MsgRead EmemFifo_SETUP_MsgRead;
EXTERN PROTO_EmemFifo_SETUP_MsgCopyPlain EmemFifo_SETUP_MsgCopyPlain;
EXTERN PROTO_EmemFifo_SETUP_MsgCopyModify EmemFifo_SETUP_MsgCopyModify;

EXTERN PROTO_EmemBlock_SETUP_MsgBuildInit EmemBlock_SETUP_MsgBuildInit;
EXTERN PROTO_EmemBlock_SETUP_MsgDataExchange EmemBlock_SETUP_MsgDataExchange;
EXTERN PROTO_EmemBlock_SETUP_MsgAdd EmemBlock_SETUP_MsgAdd;
EXTERN PROTO_EmemBlock_SETUP_MsgDelete EmemBlock_SETUP_MsgDelete;
EXTERN PROTO_EmemBlock_SETUP_MsgBuildFinalize EmemBlock_SETUP_MsgBuildFinalize;
EXTERN PROTO_EmemBlock_START_MsgGetCnt EmemBlock_START_MsgGetCnt;
EXTERN PROTO_EmemBlock_START_MsgExplain EmemBlock_START_MsgExplain;
EXTERN PROTO_EmemBlock_PROCESS_MsgRead EmemBlock_PROCESS_MsgRead;
EXTERN PROTO_EmemBlock_PROCESS_MsgCopyPlain EmemBlock_PROCESS_MsgCopyPlain;
EXTERN PROTO_EmemBlock_PROCESS_MsgCopyModify EmemBlock_PROCESS_MsgCopyModify;


/* Überläufer aus WIN_UTIL.H */
typedef void (TOOLAPI *PROTO_ShowWarning) (char FAR *, char FAR *);
typedef void (TOOLAPI *PROTO_ConsoleOutWarning) (LPCTSTR szTitle, LPCTSTR szMsg);
typedef void (TOOLAPI *PROTO_ConsoleOutRaw) (LPCTSTR szText, BOOL bBold, BOOL bItalic, int nRed, int nGreen, int nBlue);
typedef void (TOOLAPI *PROTO_ConsoleOutf) (char *szText);
typedef void (TOOLAPI *PROTO_EnableAllWindows) (BOOL);
typedef void (TOOLAPI *PROTO_ShowInternalError) (const char FAR *, const char FAR *, int);
typedef void (TOOLAPI *PROTO_StopExperiment) ( void );
typedef double (TOOLAPI *PROTO_CurrentExperimentTime) ( int bSynchronize );

EXTERN PROTO_ShowWarning ShowWarning;
EXTERN PROTO_ConsoleOutWarning ConsoleOutWarning;
EXTERN PROTO_ConsoleOutRaw ConsoleOutRaw;
EXTERN PROTO_ConsoleOutf ConsoleOutf;
EXTERN PROTO_EnableAllWindows EnableAllWindows;
EXTERN PROTO_ShowInternalError ShowInternalError;
EXTERN PROTO_StopExperiment StopExperiment;
EXTERN PROTO_CurrentExperimentTime CurrentExperimentTime;

#define InternalError(msg) ShowInternalError (msg, "DLL:" __FILE__, __LINE__ )
#define ImpossibleCase() InternalError("Impossible case")
#define ImpossibleCaseNum(n) ( sprintf(LongTempString,"Impossible case %ld",(long)(n)), InternalError(LongTempString) )

/* Überläufer aus MAIN.H */
typedef void (TOOLAPI *PROTO_PauseExperiment) ( void );

/* Überläufer aus BLOCK.H */
RECT ClToScr (HWND, HWND, RECT);

/* Überläufer aus MODUL.H */
#define ModulBenutzt(mod) ( mod->bModuleIsConnected || mod->wNumInpChan == 0 )

EXTERN PROTO_PauseExperiment PauseExperiment;

// Überläufer aus MAT_UTIL.H
typedef void (TOOLAPI *PROTO_do_fft) (
   DLAB_FLOAT FAR *datar, // Realteil
   DLAB_FLOAT FAR *datai, // Imaginärteil
   int nn,                // Größe des Feldes (Zweierpotenz)
   int Richtung);        // 1 = FFT, -1 = inverse FFT
typedef void (TOOLAPI *PROTO_do_fftex) (
   DLAB_FLOAT *datar,     // Realteil
   DLAB_FLOAT *datai,     // Imaginärteil
   double *dArrayXReal,   // Hilfsfeld zur Bestimmung Realteil
   double *dArrayXImg,    // Hilfsfeld zur Bestimmung Imaginärteil
   int nn,                // Blockgröße muss keiner Zweierpotenz entsprechen
   int Richtung,          // 1 = FFT, -1 = inverse FFT
   UINT uiFFTVerfahren); // 0 = ReFFT und ReInvFFT, 1 = FFTEx und InvFFTEx

EXTERN PROTO_do_fft do_fft;
EXTERN PROTO_do_fftex do_fftex;

/* ------------------------------------------------------------------------ */
/* Ende der Datei                                                           */
/* ------------------------------------------------------------------------ */
