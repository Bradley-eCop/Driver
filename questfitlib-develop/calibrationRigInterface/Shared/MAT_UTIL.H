
/* ======================================================================== */
/* Programm   :  EVATOOLS.H  -  Headerdatei                                 */
/* Funktionen :  Globale Variablen und Funktionsprototypen, die in der zu-  */
/*               gehörigen C Datei EV_TOOLS.C definiert sind.               */
/* Letzte Änd.:  08.01.93 CS                                                */
/* ======================================================================== */




/* ------------------------------------------------------------------------ */
/* Funktionsprototypen */
/* ------------------------------------------------------------------------ */

long Expo (double);    /* Berechnet den Exponent eines Double 01.12.92 Mago */
long Roundf (double);  /* Rundet Double in Long               01.12.92 Mago */
double Exp10 (double); /* 10 hoch Double                      01.12.92 Mago */

short Float2Short (double f);
WORD Float2Word (double f);
int Float2Int (double f);
UINT Float2Uint (double f);

#define Float2Sample Float2Short
#define Float2UnsignedSample Float2Word

UINT AnzahlAktiveBits (DWORD); /* Bits in DWORD, die 1 sind; Ro 20.01.93 */
double Horner (double x, int Grad, double a[]); /* Polynom nach Horner */
BOOL IsNearlyEqual (double a, double b, double tol);

/* -eof- */
