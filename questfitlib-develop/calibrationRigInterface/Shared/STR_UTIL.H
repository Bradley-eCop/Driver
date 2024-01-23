
/* ======================================================================== */
/* Programm   :  STR_UTIL.H  -  Headerdatei                                 */
/* Funktionen :  Globale Variablen und Funktionsprototypen, die in der zu-  */
/*               gehörigen C Datei STR_UTIL.C definiert sind.               */
/* ======================================================================== */

/* ------------------------------------------------------------------------ */
#define ID_KONV_NRM 0x0001   /* Normale Darstellung                         */
#define ID_KONV_EXP 0x0002   /* Exponential Darstellung                     */
#define ID_KONV_ING 0x0004   /* Ingeneur Darstellung E03, E06...            */

#define MAX_KONV_STR    64   /* max. Länge eines zu konv. Strings           */
/* ------------------------------------------------------------------------ */

/* ------------------------------------------------------------------------ */
/* Funktionsprototypen */
/* ------------------------------------------------------------------------ */

void chg_int (char *, int);
void chg_float (char *, double, int);
void float2str (UINT uiStellen, UINT uiNks, double dWert, UINT uiAusgabeTyp, LPSTR szString);
void int2hex (UINT wStellen, int nZahl, LPSTR cString);
void int2oct (UINT wStellen, int nZahl, LPSTR cString);
void int2bin (UINT wStellen, int nZahl, LPSTR cString);
void time2str (double fZahl, char FAR *cZahlString, int NKS);
void min2str (double fZahl, char FAR *cZahlString, int NKS);

/* atof erlaubt nur Punkt als Komma. Wir wollen aber auch Komma erlauben! */
double str2float (char *s);
#define atof str2float

void StrToESC (char FAR *dest, char FAR *source);
int CheckCntNks (double f);

void SetVersionsString (UINT uiVerId);

/* Fügt den String src vor dest ein */
char *strins (char *dest, char *src);
void chg_float_formatted (char *str, double wert, int Zeichen, int Nks, double Max, double Min);  // MX_Ro 20.05.2015 - Min und Max auf double geändert
void chg_float_red (char *str, double wert, int Zeichen, int Nks, double Max, double Min);        // MX_Ro 20.05.2015 - Min und Max auf double geändert

/* Länderkonvertierung */
void CheckStringDec (LPSTR);       /* Komma Konvertierung */
void CheckLeadingZero (LPSTR str);  /* Führende Null rausschmeissen */
void TextOutDec (HDC dc, int x, int y, LPSTR cBuf, int sLen);
void sprintf_year (LPSTR cYear, int year, int mon, int day);
int sprintf_clock (LPSTR cTime, int hour, int min, int sec);
void sscanf_year (LPSTR cYear, int *year, int *mon, int *day);
void sscanf_clock (LPSTR cTime, int *hour, int *min, int *sec);

/* Fontbestimmung */
HFONT CreatePropFont (LOGFONT *lf);

void AddLastBackSlash (char * ch);
void RemoveLastBackSlash (char * ch);
void NoMinusNull (char * c);

BOOL TKGetFileName (char* chFilter, char* chTitle, char* chFileExt, DWORD dwFlags, char* chTempTransferFileName, HANDLE hOwner);

#define HELP_PATH_IS_ALREADY_COMPLETE_DESIGNED                               0
#define HELP_PATH_INCLUDE_ONLY_THE_FILE_NAME                                 1
#define HELP_DO_NOT_CHECK_LASTFOCUS                                          0

BOOL TKCallOnlineHelp (UINT uiHelpPathInfo, UINT uHelpCommand, UINT uiLastFocus, char* chHelpFileName, DWORD_PTR dwHelpIndex);
HFILE TKOpenFile (LPCSTR path, INT mode);
HFILE TKCloseFile (HFILE hFile);

BOOL dlStrToken (int* pnPos, char* szSource, char cDelimiter, char* szToken, int nTokenMax);
BOOL IsOldEvalVersion (char* szFirstStart, int nMaxLen);
BOOL AppendVersionNumber (char* szStr, int nMaxLen);

void TKStringLineFeed (UINT uiUmbruchNachZeichen, CHAR * csString);

BOOL TKPathExists (LPSTR cNewDir);

char *TKTrimSpaces (char *str);
char *TKstrcpyTrimBase (char *d, char *s, int mode, char *delim);
char *TKTrimLeft (char *s, char *d);
char *TKTrimRight (char *s, char *d);
char *TKTrimLeftAndRight (char *s, char *d);
char *TKKillAll (char *s, char *d);

/* ------------------------------------------------------------------------ */
/* Ende der Datei                                                           */
/* ------------------------------------------------------------------------ */