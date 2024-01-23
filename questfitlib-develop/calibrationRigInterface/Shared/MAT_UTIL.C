
/* ======================================================================== */
/* Programm   :  MAT_UTIL.C                                                 */
/* Funktionen :  Diverse mathematische Unterprogramme zur allgemeinen       */
/*               Benutzung: FFT, RFFT, ...                                  */
/* ======================================================================== */



/* ------------------------------------------------------------------------ */
/* Einbinden der Windows Headerdatei und der C Headerdateien                */
/* ------------------------------------------------------------------------ */

#include "PRE_WIN.H"
#include <WINDOWS.H>
#include "POST_WIN.H"
#include <WINDOWSX.H>
#include <FLOAT.H>
#include <MATH.H>
#include <STRING.H>
#include <LIMITS.H>


/* ------------------------------------------------------------------------ */
/* Einbinden der Headerdateien des EVA Projekts                             */
/* ------------------------------------------------------------------------ */

#include "DLAB.H"


/* ------------------------------------------------------------------------ */
/* Funktionsname     : Expo                                                 */
/* Beschreibung      : Berechnet Exponent einer Float Zahl                  */
/* Aufrufparameter   : ex - Operant                                         */
/* Rückgabewert      : lExp - Exponent                                      */
/* Globale Variablen : -                                                    */
/* ------------------------------------------------------------------------ */

long Expo (double ex)
{
   long lExp;

   ex = fabs (ex);
   lExp = 0;
   if (ex == 0)
      return 0;

   /* bei ENUM machen wirs auch korrekt */
   // MX_Ro 15.05.2015 : FLOAT Konstanten durch DLAB_FLOAT Konstanten ersetzt (und DBL)
   if (ex > DLAB_FLOAT_MAX || ex < -DLAB_FLOAT_MAX)
      return DBL_MAX_10_EXP;

   if (ex >= 1.0)
   {
      while (ex >= 1.0)
      {
         ex /= 10.0;
         lExp++;
      }
      lExp--;
   }
   else
   {
      while (ex <= 1.0)
      {
         ex *= 10.0;
         lExp--;
      }
   }
   return lExp;
}



/* ------------------------------------------------------------------------ */
/* Funktionsname     : Exp10                                                */
/* Beschreibung      : Berechnung der Funktion 10 hoch x                    */
/* Globale Variablen : -                                                    */
/* ------------------------------------------------------------------------ */

double Exp10 (double e)
{
   return (exp (e*log (10)));
}



/* ------------------------------------------------------------------------ */
/* Funktionsname     : Roundf                                               */
/* Beschreibung      : Runden von double Werten                              */
/* Rückgabewert      : gerundeter long-Wert                                 */
/* Globale Variablen : -                                                    */
/* ------------------------------------------------------------------------ */

long Roundf (double f)
{
   if (f < 0)
      return (long)(f - 0.5);

   return (long)(f + 0.5);
}



short Float2Short (double f)
{
   if (f > 32767.0)  // SHRT_MAX
      return 32767;
   if (f < -32768.0)
      return -32768;

   if (f < 0)
      return (short)(f - 0.5);

   return (short)(f + 0.5);
}



WORD Float2Word (double f)
{
   if (f > 65535.0)    // USHRT_MAX
      return 65535;
   if (f < 0.0)
      return 0;

   return (WORD)(f + 0.5);
}



int Float2Int (double f)
{
   if (f > 2147483647.0)
      return 2147483647;
   if (f < -2147483648.0)
      return 2147483648;

   if (f < 0)
      return (int)(f - 0.5);

   return (int)(f + 0.5);
}


UINT Float2Uint (double f)
{
   if (f > (UINT)0xffffffff)
      return (UINT)0xffffffff;
   if (f < 0.0)
      return 0;

   return (UINT)(f + 0.5);
}


UINT AnzahlAktiveBits (DWORD CorpusDelicti)
{
   UINT Result = 0;
   DWORD Maske = 1L;
   int i;

   for (i = 0; i < 32; i++)
   {
      if ((Maske & CorpusDelicti) != 0)
         Result++;
      Maske <<= 1;
   }
   return Result;
}




/* ------------------------------------------------------------------------ */
/* Funktionsname     : Horner                                               */
/* Beschreibung      : Diese Funktion wird intern von Modulen Polynom oder  */
/*                   : Skalierung->Thermoelemntlinearisierung benutzt.      */
/*                   : Die Funktion berechnet eine Polynom an einer Stelle. */
/* Aufrufparameter   : Auszuwertende Stelle, Grad des Polynoms, Array mit   */
/*                   : den Koeffizienten (double) beginnend mit a0.         */
/*                   : ACHTUNG: Keine Überprüfung auf Länge des Arrays !!!  */
/* Globale Variablen : keine benutzt                                        */
/* ------------------------------------------------------------------------ */

double Horner (double x, int Grad, double *a)
{
   double Erg = 0.0;
   int i;

   for (i = Grad; i >= 0; i--)
      Erg = Erg * x + a[i];

   return Erg;
}


/* ------------------------------------------------------------------------ */
/* Funktionsname     : IsNearlyEqual                                        */
/* Beschreibung      : Vergleich von Floating-Point-Zahlen                  */
/* Aufrufparameter   : Zwei Floating-Point-Zahlen                           */
/*                   : Toleranz. z.B.: 0.01 == ca. 1% Abweichung erlaubt    */
/* Rückgabewert      : TRUE = Zahlen sind 'fast gleich'                     */
/*                   : FALSE sonst                                          */
/* Globale Variablen : -                                                    */
/* ------------------------------------------------------------------------ */

BOOL IsNearlyEqual (double a, double b, double tol)
{
   if (fabs (a - b) <= tol * (fabs (a) + fabs (b)) / 2.0)
      return TRUE;

   return FALSE;
}

/* -eof- */
