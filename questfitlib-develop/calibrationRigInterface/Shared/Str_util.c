/* ======================================================================== */
/* Programm   :  STR_UTIL.C                                                 */
/* Funktionen :  Diverse Nutzroutinen zur laufenden Verwendung für          */
/*               String-Konversionen, ...                                   */
/* Letzte Änd.:  14.12.2015 MX_RO                                           */
/* ======================================================================== */

/* ------------------------------------------------------------------------ */
/* Einbinden der Windows Headerdatei und der C Headerdateien                */
/* ------------------------------------------------------------------------ */

#include "PRE_WIN.H"
#include <WINDOWS.H>
#include "POST_WIN.H"
#include <WINDOWSX.H>
#include <MATH.H>
#include <STDLIB.H>
#include <STDIO.H>
#include <STRING.H>
#include <FLOAT.H>
#include <CTYPE.H>
#include <direct.h>

/* ------------------------------------------------------------------------ */
/* Einbinden der Headerdateien des EVA Projekts                             */
/* ------------------------------------------------------------------------ */

//#include "KERNEL.H"
#include "DLAB.H"

//#include "HTMLHELP.H"

#define NEW 1

void sprintf_red (char *str, double wert, int nks);


// MX_RO 20.05.2015 - Min und Max auf double geändert
void chg_float_formatted (char *str, double wert, int Zeichen, int Nks, double Max, double Min)
{
   if (Zeichen > 25)
      Zeichen = 25;

   if (Nks > 16)
      Nks = 16;

   if (Nks > Zeichen - 2)
      Nks = max (0, (int)Zeichen - 2);

   if ((wert < Max && wert > Min) || (wert > -1.0 * Max && wert < -1.0 * Min) || (wert == 0.0))
      chg_float (str, wert, Nks);
   else
   {
      if (Nks > Zeichen - 9)
      {
         Nks = Zeichen - 9;
      }

      float2str (Zeichen, Nks, wert, ID_KONV_ING, str);
   }
}

/* ************************************************************************ */
/*                                                                          */
/* Procedure : chg_float                                                    */
/*                                                                          */
/* Zweck     : Konvertierung  Gleitkommazahl <--> Zeichenkette              */
/*             incl. Formatspezifikation                                    */
/*                                                                          */
/* Includedateien:                                                          */
/*                   - string.h                                             */
/*                   - math.h                                               */
/*                                                                          */
/* ************************************************************************ */

void chg_float (char *str, double wert, int nks)
{
   double dWert;
   char cFormatStr[20], cHelp[20];

   if (nks > 16)
      nks = 16;

   dWert = wert;
   strcpy (cFormatStr, "%.");
   itoa (abs (nks), cHelp, 10);
   strcat (cFormatStr, cHelp);

   if (fabs (wert) > 1e6 ||
       (nks < 0 && wert != 0.0 && fabs (wert) < 0.1))
   {
      strcat (cFormatStr, "e");
      sprintf (str, cFormatStr, wert);
      /* Wir entfernen hier das Plus und die erste Null nach dem e */
      ;
   }
   else
   {
      strcat (cFormatStr, "f");
      sprintf (str, cFormatStr, wert);
   }

   CheckLeadingZero (str);
   CheckStringDec (str);

   return;
}

// MX_Ro 20.05.2015 - Min und Max auf double geändert
void chg_float_red (char *str, double wert, int Zeichen, int Nks, double Max, double Min)
{
   if (Zeichen > 25)
      Zeichen = 25;

   if (Nks > 16)
      Nks = 16;

   if (Nks > Zeichen - 2)
      Nks = max (0, (int)Zeichen - 2);

   if ((wert < Max && wert > Min) || (wert > -1.0 * Max && wert < -1.0 * Min) || (wert == 0.0))
      sprintf_red (str, wert, Nks);
   else
   {
      if (Nks > Zeichen - 9)
      {
         Nks = Zeichen - 9;
      }

      float2str (Zeichen, Nks, wert, ID_KONV_ING, str);
   }
}

int CheckCntNks (double f)
{
   int nks = 0;

   char *str, *str2;
   char cBuf[50];
   BOOL bFlag;

   sprintf (cBuf, "%.10f", f);
   /* OLD: chg_f (cBuf, f, 6); */
   strcat (cBuf, "0");
   str = strrchr (cBuf, '0');

   if (str == NULL)
   {
      strcat (cBuf, "0");
      str = strrchr (cBuf, '0');
   }

   str2 = strrchr (cBuf, '.');

   if (str2 == NULL)
   {
      str2 = strrchr (cBuf, DezTrenn[0]);
   }

   while (strlen (cBuf) > 20)
   {
      *str = '\0';
      str--;
   }

   bFlag = FALSE;

   while (str != str2)
   {
      str--;

      if (*str != '0')
      {
         bFlag = TRUE;
      }

      if ((bFlag) && (str != str2))
      {
         nks++;
      }
   }

   return nks;
}

void sprintf_red (char *str, double wert, int nks)
{
   double dWert;
   char cFormatStr[20], cHelp[20];

   if (nks > 16)
      nks = 16;

   dWert = wert;
   strcpy (cFormatStr, "%.");
   itoa (abs (nks), cHelp, 10);
   strcat (cFormatStr, cHelp);

   if (fabs (wert) > 1e5 ||
       (nks < 0 && wert != 0.0 && fabs (wert) < 0.1))
   {
      strcat (cFormatStr, "e");
      sprintf (str, cFormatStr, wert);
      /* Wir entfernen hier das Plus und die erste Null nach dem e */
      ;
   }
   else
   {
      int wertnks;

      wertnks = CheckCntNks (wert);

      if (wertnks > 6)
         wertnks = 6;

      strcpy (cFormatStr, "%.");
      itoa (abs (wertnks), cHelp, 10);
      strcat (cFormatStr, cHelp);

      strcat (cFormatStr, "f");
      sprintf (str, cFormatStr, wert);
   }

   CheckLeadingZero (str);
   CheckStringDec (str);

   return;
}

/* ************************************************************************ */
/*                                                                          */
/* Procedure : chg_int                                                      */
/*                                                                          */
/* Zweck     : Konvertierung  Integer <--> Zeichenkette                     */
/*             incl. Formatspezifikation                                    */
/*                                                                          */
/* Includedateien:                                                          */
/*                   - string.h                                             */
/*                   - math.h                                               */
/*                                                                          */
/* ************************************************************************ */

void chg_int (char *str, int wert)
{
   char  *c;
   int   dec, sign, k;
   int   ndig = 20;

   double x, y;
   int nks;

   nks = 0;
   x = fabs (wert);
   y = x;
   x -= y;

   c = ecvt ((double)wert, ndig, &dec, &sign);

   if (sign == 1)
      *str++ = '-';

   if (dec < 0)
   {
      *str++ = '0';
      *str++ = '.';

      for (k = nks; k > nks + dec; k--)
         *str++ = '0';

      for (k = nks + dec; k > 0; k--)
         *str++ = *c++;
   }
   else
   {
      for (k = 1; k <= dec; k++)
         *str++ = *c++;

      if (dec == 0)
         *str++ = '0';
   }

   *str = '\0';
}

#pragma optimize ("", off)

/* ------------------------------------------------------------------------ */
/* Funktionsname     : float2str                                            */
/* Beschreibung      : Konvertierung eines Double-Wertes in String          */
/* Aufrufparameter   : uiStellen    - gesamte Stellenanzahl                 */
/*                   : uiNks        - Anzahl Nachkommastellen               */
/*                   : dWert        - Wert der konvertiert wird             */
/*                   : uiAusgabeTyp - Formatierungsart,IDs siehe STR_UTIL.H */
/*                   : szString     - konvertierter String                  */
/* Rückgabewert      : -                                                    */
/* Globale Variablen : keine benutzt                                        */
/* Historie          : 03.03.1993  Mago (Erstellung)                        */
/*                   : 03.03.1993  Mago (Letzte Änderung)                   */
/* ------------------------------------------------------------------------ */

#pragma warning (disable: 4748)
void float2str (UINT uiStellen, UINT uiNks, double dWert, UINT uiAusgabeTyp, LPSTR szString)
{
   char cBuf[MAX_KONV_STR], cExp[64];
   char TempString[500] = "";                  // MX_SG 28.09.2015  Muss größer sein wegen double: 
   char cFormatStr[20] = "", cHelp[20] = "";
   int nExp;
   double dMant;

   if (uiStellen > 25)
      uiStellen = 25;

   if (uiNks > 16)
      uiNks = 16;

   if (uiNks > uiStellen - 2)
      uiNks = max (0, (int)uiStellen - 2);

   /* Range-Check zuerst */
   if (dWert >= DLAB_FLOAT_MAX)
   {
      LoadString (hInstDlab, STR_ERR_RANGE_MAX, szString, MAX_KONV_STR);
      return;
   }

   if (dWert <= -DLAB_FLOAT_MAX)
   {
      LoadString (hInstDlab, STR_ERR_RANGE_MIN, szString, MAX_KONV_STR);
      return;
   }

   if (!(dWert <= 0.0 || dWert >= 0.0))
   {
      LoadString (hInstDlab, STR_ERR_KONV, szString, MAX_KONV_STR);
      return;
   }

   switch (uiAusgabeTyp)
   {
      case ID_KONV_NRM:
      {
         /* erst mal schaun ob es ganz simple geht */
         strcpy (cFormatStr, "%.");
         itoa (uiNks, cHelp, 10);
         strcat (cFormatStr, cHelp);
         strcat (cFormatStr, "f");

         // MX_SG 28.09.2015 
         // Falls beim Versuch , die Variable in TempString zu schreiben, über die maximale Stringlänge
         // hinausgeschrieben wird, dann gibt es hier jetzt eine Exeption. Beim Testen mit einem Kundenschaltbild passierte 
         // genau das, weil aus irgend einem Grund in in der Variable 1.0 E 300 stand: dies wird länger als die ursprunglich
         // möglichen 100 Zeichen...
         sprintf_s (TempString, _countof (TempString), cFormatStr, dWert);

         if (dWert == 0.0)
            nExp = 0;
         else
         {
            if (dWert < 0)
               nExp = (int)log10 (-1 * dWert);
            else
               nExp = (int)log10 (dWert);
         }

         if (strlen (TempString) > uiStellen)
         {
            /* So einfach ging es nicht, jetzt müssen wir Exp. darstellen */
            dMant = dWert / Exp10 ((double)nExp);

            if (dMant >= 1.0)
            {
               dMant /= 10;

               if (nExp > 0)
                  nExp++;
               else
                  nExp--;
            }

            sprintf (cBuf, cFormatStr, dMant);
            sprintf (cExp, "E%02d", nExp);
            strcat (cBuf, cExp);
            strcpy (szString, (LPSTR)cBuf);

            if (strlen (szString) > uiStellen)
               LoadString (hInstDlab, STR_ERR_KONV, szString, MAX_KONV_STR);
         }
         else
         {
            strcpy (szString, TempString);
         }
      }
      break;

      case ID_KONV_ING:
      {
         double l, vorz;

         strcpy (cFormatStr, "%.");
         itoa (uiNks, cHelp, 10);
         strcat (cFormatStr, cHelp);
         strcat (cFormatStr, "f");

         if (dWert < 0)
            vorz = -1.0;
         else
            vorz = 1.0;

         dWert = fabs (dWert);

         if (dWert != 0)
            l = log10 (dWert);
         else
            l = 0;

         l /= 3.0;
         l = floor (l);
         l *= 3;

         dMant = vorz * dWert / Exp10 (l);

         if (fabs (dMant) >= 1000.0)
         {
            if (l < 0)
               l -= 3;
            else
               l += 3;

            dMant /= 1000.0;
         }

         sprintf (cBuf, cFormatStr, dMant);

         sprintf (cExp, "E%02d", (int)l);
         strcat (cBuf, cExp);
         strcpy (szString, (LPSTR)cBuf);

         if (strlen (szString) > uiStellen)
            LoadString (hInstDlab, STR_ERR_KONV, szString, MAX_KONV_STR);
      }
      break;

      case ID_KONV_EXP:
      {
         strcpy (cFormatStr, "%.");
         itoa (uiNks, cHelp, 10);
         strcat (cFormatStr, cHelp);
         strcat (cFormatStr, "f");
         sprintf (TempString, cFormatStr, dWert);
         strcpy (szString, TempString);

         if (dWert == 0.0)
            nExp = 0;
         else
         {
            if (dWert < 0)
               nExp = (int)log10 (-1 * dWert);
            else
               nExp = (int)log10 (dWert);
         }

         /* So einfach ging es nicht, jetzt müssen wir Exp. darstellen */
         dMant = dWert / Exp10 ((double)nExp);

         if (dMant > 1.0)
         {
            dMant /= 10;

            if (nExp >= 0)
               nExp++;
            else
               nExp--;
         }

         sprintf (cBuf, cFormatStr, dMant);
         sprintf (cExp, "E%02d", nExp);
         strcat (cBuf, cExp);
         strcpy (szString, (LPSTR)cBuf);

         if (strlen (szString) > uiStellen)
            LoadString (hInstDlab, STR_ERR_KONV, szString, MAX_KONV_STR);
      }
      break;

      default:
         LoadString (hInstDlab, STR_ERR_KONV, szString, MAX_KONV_STR);
   }

   CheckLeadingZero (szString);
   CheckStringDec (szString);
}
#pragma warning (default: 4748)

#pragma optimize ("", on)



/* ------------------------------------------------------------------------ */
/* Funktionsname     : int2hex                                              */
/* Beschreibung      : Konvertierung eines Hex-Wertes (Integer) in String   */
/* Aufrufparameter   : wStellen     - Anzahl Stellen                        */
/*                   : nZahl        - Wert der konvertiert wird             */
/*                   : cString      - konvertierter String                  */
/* Rückgabewert      : -                                                    */
/* Globale Variablen : keine benutzt                                        */
/* Historie          : 11.01.2000  CS  (Erstellung)                         */
/* ------------------------------------------------------------------------ */

void int2hex (UINT wStellen, int nZahl, LPSTR cString)
{
#pragma warning (disable: 4295)
   char szHexDigit[17] = "0123456789ABCDEF";
#pragma warning (default: 4295)
   UINT n = 8;
   UINT i;

   if (wStellen < 8)
      n = wStellen;

   for (i = 0; i < n; i++)
      cString[i] = szHexDigit[(nZahl >> (4 * (n - i - 1))) & 0xF];

   cString[i] = '\0';
}



/* ------------------------------------------------------------------------ */
/* Funktionsname     : int2oct                                              */
/* Beschreibung      : Konvertierung eines Oktal-Wertes (Integer) in String */
/* Aufrufparameter   : wStellen     - Anzahl Stellen                        */
/*                   : nZahl        - Wert der konvertiert wird             */
/*                   : cString      - konvertierter String                  */
/* Rückgabewert      : -                                                    */
/* Globale Variablen : keine benutzt                                        */
/* Historie          : 11.01.2000  CS  (Erstellung)                         */
/* ------------------------------------------------------------------------ */

void int2oct (UINT wStellen, int nZahl, LPSTR cString)
{
   UINT n = 11;
   UINT i;

   if (wStellen < 11)
      n = wStellen;

   for (i = 0; i < n; i++)
      cString[i] = (char)(((nZahl >> (3 * (n - i - 1))) & 07) + '0');

   cString[i] = '\0';
}



/* ------------------------------------------------------------------------ */
/* Funktionsname     : int2bin                                              */
/* Beschreibung      : Konvertierung eines Binär-Wertes (Integer) in String */
/* Aufrufparameter   : wStellen     - Anzahl Stellen                        */
/*                   : nZahl        - Wert der konvertiert wird             */
/*                   : cString      - konvertierter String                  */
/* Rückgabewert      : -                                                    */
/* Globale Variablen : keine benutzt                                        */
/* Historie          : 11.01.2000  CS  (Erstellung)                         */
/* ------------------------------------------------------------------------ */

void int2bin (UINT wStellen, int nZahl, LPSTR cString)
{
   UINT n = 32;
   UINT i;

   if (wStellen < 32)
      n = wStellen;

   for (i = 0; i < n; i++)
      cString[i] = (char)(((nZahl >> (n - i - 1)) & 1) + '0');

   cString[i] = '\0';
}



/* ------------------------------------------------------------------------ */
/* Funktionsname     : time2str                                             */
/* Beschreibung      : Konvertierung eines Zeit-Wertes (Sekunden) in String */
/* Aufrufparameter   : NKS          - Anzahl Nachkommastellen               */
/*                   : fZahl        - Wert der konvertiert wird             */
/*                   : cZahlString  - konvertierter String                  */
/*                   : NKS          - Anzahl Nachkommastellen               */
/* Rückgabewert      : -                                                    */
/* Globale Variablen : keine benutzt                                        */
/* Historie          : 03.03.1993  CS  (Erstellung)                         */
/*                   : 03.03.1993  CS  (Letzte Änderung)                    */
/*                   : 10.01.1994 Mago (Letzte Änderung - Format 0:00:00)   */
/* ------------------------------------------------------------------------ */

static char *ito2c (long i)
{
   static char buf[10];

   if (i < 10)
   {
      *buf = '0';
      ltoa (i, buf + 1, 10);
   }
   else
   {
      ltoa (i, buf, 10);
   }

   return buf;
}



void time2str (double fZahl, char *cZahlString, int NKS)
{
   long std, min, sec, nkst, i;

   if (NKS > 9)
   {
      NKS = 9;
   }

   if (fZahl < 0.0)
   {
      strcpy (cZahlString, "-");
      fZahl *= -1.0;
   }
   else
   {
      /* String aufbauen */
      cZahlString[0] = '\0';
   }

   /* Vorher runden, nicht mitten im Ablauf */
   for (i = 0; i < NKS; i++)
   {
      fZahl *= 10.0;
   }

   fZahl = floor (fZahl + 0.5);

   for (i = 0; i < NKS; i++)
   {
      fZahl /= 10.0;
   }

   /* std, min, sek berechnen */
   std = (long)(fZahl / 3600.0);
   fZahl -= std * 3600.0;
   min = (long)(fZahl / 60.0);
   fZahl -= min * 60.0;
   sec = (long)fZahl;
   fZahl -= sec;

   for (i = 0; i < NKS; i++)
   {
      fZahl *= 10.0;
   }

   nkst = (long)Roundf (fZahl);

   /* Zur Sicherheit: Rundung prüfen */
   if (sec >= 60)
   {
      sec -= 60;
      min += 1;
   }

   if (min >= 60)
   {
      min -= 60;
      std += 1;
   }

   strcat (cZahlString, ito2c (std));
   strcat (cZahlString, ":");

   strcat (cZahlString, ito2c (min));
   strcat (cZahlString, ":");

   strcat (cZahlString, ito2c (sec));

   if (NKS != 0)
   {
      char buf[10];

      ltoa (nkst, buf, 10);
      strcat (cZahlString, DezTrenn);

      for (i = strlen (buf); i < NKS; i++)
      {
         strcat (cZahlString, "0");
      }

      strcat (cZahlString, buf);
   }
}

void min2str (double fZahl, char *cZahlString, int NKS)
{
   long min, sec, nkst, i;

   if (NKS > 9)
   {
      NKS = 9;
   }

   if (fZahl < 0.0)
   {
      strcpy (cZahlString, "-");
      fZahl *= -1.0;
   }
   else
   {
      /* String aufbauen */
      cZahlString[0] = '\0';
   }

   /* Vorher runden, nicht mitten im Ablauf */
   for (i = 0; i < NKS; i++)
   {
      fZahl *= 10.0;
   }

   fZahl = floor (fZahl + 0.5);

   for (i = 0; i < NKS; i++)
   {
      fZahl /= 10.0;
   }

   min = (long)(fZahl / 60.0);
   fZahl -= min * 60.0;
   sec = (long)fZahl;
   fZahl -= sec;

   for (i = 0; i < NKS; i++)
   {
      fZahl *= 10.0;
   }

   nkst = (long)Roundf (fZahl);

   /* Zur Sicherheit: Rundung prüfen */
   if (sec >= 60)
   {
      sec -= 60;
      min += 1;
   }

   strcat (cZahlString, ito2c (min));
   strcat (cZahlString, ":");

   strcat (cZahlString, ito2c (sec));

   if (NKS != 0)
   {
      char buf[10];

      ltoa (nkst, buf, 10);
      strcat (cZahlString, DezTrenn);

      for (i = strlen (buf); i < NKS; i++)
      {
         strcat (cZahlString, "0");
      }

      strcat (cZahlString, buf);
   }
}

/* ------------------------------------------------------------------------ */
/* Funktionsname     : str2float                                            */
/* Beschreibung      : Ersatz für 'atof'. Erlaubt auch ',' statt '.'        */
/* Historie          : 03.03.1993  CS  (Erstellung)                         */
/*                   : 03.03.1993  CS  (Letzte Änderung)                    */
/* ------------------------------------------------------------------------ */

#undef atof

double str2float (char *s)
{
   char *p = s;

   while (p != NULL)
   {
      p = strchr (p, ',');

      if (p != NULL)
      {
         *p = '.';
      }
      else
      {
         if (DezTrenn[0] != '.' && DezTrenn[0] != ',' && DezTrenn[0] != '\0')
         {
            p = strchr (s, DezTrenn[0]);

            if (p != NULL)
            {
               *p = '.';
            }
         }
      }
   }
   // MX_SG : s könnte Null sein...
   if (s == NULL)
      return 0.0;
   else
      return atof (s);
}

#define atof str2float


/* ------------------------------------------------------------------------ */
/* Funktionsname     : StrToESC                                             */
/* Beschreibung      : Umwandlung von \... in ESC Zeichen                   */
/* Historie          : 02.04.1993  rb  (Erstellung)                         */
/*                   : 02.04.1993  rb  (Letzte Änderung)                    */
/* ------------------------------------------------------------------------ */

void StrToESC (char *dest, char *source)
{
   char  szHilf[16];
   char *stopstring;

   while (*source != '\0')
   {
      if (*source == 0x5C)
      {
         source++;

         switch (*source)
         {
            case 'x':
            case 'X':
               source++;
               szHilf[0] = *source;
               source++;
               szHilf[1] = *source;
               szHilf[2] = '\0';
               *dest = (char)strtoul (szHilf, &stopstring, 16);
               break;

            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
               szHilf[0] = *source;
               source++;
               szHilf[1] = *source;
               source++;
               szHilf[2] = *source;
               szHilf[3] = '\0';
               *dest = (char)strtoul (szHilf, &stopstring, 8);
               break;

            case 'a':
               *dest = 0x07;
               break;

            case 'b':
               *dest = 0x08;
               break;

            case 'f':
               *dest = 0x0C;
               break;

            case 'n':
               *dest = 0x0A;
               break;

            case 'r':
               *dest = 0x0D;
               break;

            case 't':
               *dest = 0x09;
               break;

            case 'v':
               *dest = 0x0B;
               break;

            case 0x5C:                  /* \ */
               *dest = 0x5C;
               break;

            case '?':
               *dest = 0x3F;
               break;

            case 0x2C:                  /* ' */
               *dest = 0x2C;
               break;

            case '"':
               *dest = 0x22;
               break;

            default:
               *dest = 0x5C;             /* \ */
               dest++;
               *dest = *source;
         }
      }
      else
      {
         *dest = *source;
      }

      dest++;
      source++;
   }

   *dest = '\0';
}

/* Fügt den String src vor dest ein */

char *strins (char *dest, char *src)
{
   UINT n = strlen (src);

   if (n > 0)
   {
      memmove (dest + n, dest, strlen (dest) + 1);
      memmove (dest, src, n);
   }

   return dest;
}


void CheckStringDec (LPSTR cBuf)
{
   char *p = cBuf;

   if (DezTrenn[0] == '.')
      return;

   if (p != NULL)
   {
      p = strchr (p, '.');

      if (p != NULL)
         *p = DezTrenn[0];
   }

}


void CheckLeadingZero (LPSTR str)
{
   if (bDecLeadingZero == FALSE)
   {
      if (strlen (str) > 2)
      {
         if ((str[0] == '0' && (str[1] == '.' || str[1] == DezTrenn[0])) ||
             (str[0] == '-' && str[1] == '0' && (str[2] == '.' || str[1] == DezTrenn[0])))
         {
            if (str[0] == '0')
               str[0] = ' ';
            else if (str[1] == '0')
               str[1] = ' ';
         }
      }
   }
}


void NoMinusNull (char * c)
{
   int i;

   if (c[0] != '-')
      return;

   for (i = 1; i < (int)strlen (c); i++)
   {
      if (isdigit (c[i]) && c[i] != '0')
         return;
   }

   if (i == 1)
      return;

   c[0] = ' ';
}


void TextOutDec (HDC dc, int x, int y, LPSTR cBuf, int sLen)
{
   NoMinusNull (cBuf);
   CheckLeadingZero (cBuf);
   CheckStringDec (cBuf);
   TextOut (dc, x, y, cBuf, sLen);
}


void sprintf_year (LPSTR cYear, int year, int mon, int day)
{
   char cFormatDay[10], cFormatMon[10], cFormatYear[10];

   if (bDateDayLeadingZero)
      sprintf (cFormatDay, "%02d", day);
   else
      sprintf (cFormatDay, "%d", day);

   if (bDateMonthLeadingZero)
      sprintf (cFormatMon, "%02d", mon);
   else
      sprintf (cFormatMon, "%d", mon);

   if (bDateYearLong)
      sprintf (cFormatYear, "%04d", 1900 + year);
   else
   {
      if (year > 99)
         year -= 100;

      sprintf (cFormatYear, "%02d", year);
   }

   switch (wDateFormat)
   {
      case 0:
         sprintf (cYear, "%s%s%s%s%s", cFormatMon, DateTrenn, cFormatDay, DateTrenn, cFormatYear);
         break;

      case 1:
         sprintf (cYear, "%s%s%s%s%s", cFormatDay, DateTrenn, cFormatMon, DateTrenn, cFormatYear);
         break;

      default:
         sprintf (cYear, "%s%s%s%s%s", cFormatYear, DateTrenn, cFormatMon, DateTrenn, cFormatDay);
   }
}


int sprintf_clock (LPSTR cTime, int hour, int min, int sec)
{
   char *szAmPm = " AM";

   if (!bTime24h && hour > 11)
      szAmPm = " PM";

   if (!bTime24h && hour > 12)
      hour -= 12;

   if (bTimeLeadingZero)
      wsprintf (cTime, "%02d%s%02d%s%02d", hour, (LPSTR)TimeTrenn, min, (LPSTR)TimeTrenn, sec);
   else
      wsprintf (cTime, "%2d%s%02d%s%02d", hour, (LPSTR)TimeTrenn, min, (LPSTR)TimeTrenn, sec);

   if (!bTime24h)
      strcat (cTime, szAmPm);

   return strlen (cTime);
}


void sscanf_year (LPSTR cYear, int *year, int *mon, int *day)
{
   char cFormat[32];

   wsprintf (cFormat, "%%d%s%%d%s%%d", DateTrenn, DateTrenn);

   switch (wDateFormat)
   {
      case 0:
         sscanf (cYear, cFormat, mon, day, year);
         break;

      case 1:
         sscanf (cYear, cFormat, day, mon, year);
         break;

      default:
         sscanf (cYear, cFormat, year, mon, day);
   }
}


void sscanf_clock (LPSTR cTime, int *hour, int *min, int *sec)
{
   char cFormat[32], cUpperTime[128];

   wsprintf (cFormat, "%%d%s%%d%s%%d", TimeTrenn, TimeTrenn);

   sscanf (cTime, cFormat, hour, min, sec);

   if (!bTime24h)
   {
      strcpy (cUpperTime, cTime);
      strupr (cUpperTime);

      if (strstr (cUpperTime, "PM") != NULL)
      {
         if (*hour < 12)
            *hour += 12;
      }
      else
      {
         if (*hour == 12)
            *hour = 0;
      }
   }
}


/* Berechnung eines proportionalen Fonts */
HFONT CreatePropFont (LOGFONT *lf)
{
   int FontHeight, FontWidth;
   SIZE TextSize;
   int MaxHeight;
   int MaxWidth;
   HFONT hf, hOldFont;
   HDC hdc;

   if (lf == NULL)
      return NULL;

   MaxHeight = abs (lf->lfHeight);
   MaxWidth = abs (lf->lfWidth);

   if (MaxHeight <= 5 || MaxWidth <= 3)
   {
      if (MaxHeight == 0 && MaxWidth == 0)
         return NULL;

      if (MaxHeight <= 5 || MaxWidth <= 3)
         return NULL;

      if (MaxHeight == 0)
         MaxHeight = 100;

      if (MaxWidth == 0)
         MaxWidth = 50;
   }

   hdc = GetDC (hwndMain);

   /* Schritt 1: Natürliche Aspect Ratio bestimmen */
   lf->lfHeight = 50;
   lf->lfWidth = 0;

#undef  DeleteObject

   hf = CreateFontIndirect (lf);
   hOldFont = SelectObject (hdc, hf);

   GetTextExtentPoint (hdc, "0000g", 5, &TextSize);
   FontHeight = TextSize.cy;
   FontWidth = (TextSize.cx + 4) / 5;

   SelectObject (hdc, hOldFont);
   DeleteObject (hf);
   hf = hOldFont = NULL;

   if (MaxHeight <= 0 || MaxWidth <= 0)
   {
      MaxHeight = FontHeight / 8;
      MaxWidth = FontWidth / 8;
   }

   /* Schritt 2: Fontgröße bestimmen und Font anlegen */

   /* Volle Höhe möglich, oder ist das Feld dann zu breit ? */
   if (MaxHeight * (long)FontWidth > MaxWidth * (long)FontHeight)
   {
      /* Bei voller Höhe wäre der Font zu breit ! */
      MaxHeight = (int)((MaxWidth * (long)FontHeight) / FontWidth);
   }

   lf->lfHeight = -MaxHeight;
   lf->lfWidth = 0;

   if (MaxHeight > 6)
      hf = CreateStackedFontIndirect (lf);
   else
      hf = NULL;

   ReleaseDC (hwndMain, hdc);

   return hf;
}


void AddLastBackSlash (char * ch)
{
   /* Immer Backslash am Ende erzwingen */
   if (strlen (ch) > 1 && ch[strlen (ch) - 1] != '\\')
   {
      strcat (ch, "\\");
   }
}


void RemoveLastBackSlash (char * ch)
{
   /* Immer Backslash löschen */
   if (strlen (ch) > 1 && ch[strlen (ch) - 1] == '\\')
   {
      ch[strlen (ch) - 1] = '\0';
   }
}


// MHa 28.08.2008 - Projekt LONG_MULTIBYTE_FILENAMES
// Hinweise:
// - TKOpenFile realisiert die Ersatzfunktion CreateFile für OpenFile
//   bzw. _lopen
// - TKCloseFile realisiert die Ersatzfunktion CloseHandle für _lclose
// - künftig könnte man in vorheriger Vorgehensweise Ersatzfunktionen
//   für (_lcreat?,) _lread, _llseek, _lwrite erstellen, also z.B. eine
//   Funktion TKFileRead für _lread, welche als Ersatzfunktion ReadFile
//   verwendet

/* ------------------------------------------------------------------------ */
/* Funktionsname     : TKGetFileName                                        */
/* Hinweis           : Funktion zur erweiterten GetOpenFileName Behandlung  */
/*                     zum Projekt LONG_MULTIBYTE_FILENAMES                 */
/* Historie          : 15.01.2008 MHa (Erstellung)                          */
/* ------------------------------------------------------------------------ */

BOOL TKGetFileName (char* chFilter, char* chTitle, char* chFileExt, DWORD dwFlags, char* chTempTransferFileName, HANDLE hOwner)
{
   // für _splitpath
   char szString[BUFSIZE_MAX_PATH_LENGTH_FOR_DLAB];
   char szDriveStr[BUFSIZE_MAX_DRIVE];
   char szDirStr[BUFSIZE_MAX_PATH_LENGTH_FOR_DLAB];
   char szFileName[BUFSIZE_MAX_PATH_LENGTH_FOR_DLAB];
   char szFileExt[BUFSIZE_MAX_PATH_LENGTH_FOR_DLAB];
   // für OPENFILENAME
   OPENFILENAME ofn;
   char szFile[BUFSIZE_MAX_PATH_LENGTH_FOR_DLAB];
   char szPath[BUFSIZE_MAX_PATH_LENGTH_FOR_DLAB];
   char chReplace;
   UINT cbString = 0;
   UINT i = 0;
   // für _getcwd, _chdir
   char cOldDir[BUFSIZE_MAX_PATH_LENGTH_FOR_DLAB];
   char cNewDir[BUFSIZE_MAX_PATH_LENGTH_FOR_DLAB];
   // sonstig
   BOOL bRet = FALSE;
   DWORD dwRet = 0;

   szFile[0] = '\0';

   cbString = strlen (chFilter);

   chReplace = chFilter[cbString - 1];

   for (i = 0; chFilter[i] != '\0'; i++)
   {
      if (chFilter[i] == chReplace)
         chFilter[i] = '\0';
   }

   strcpy (szString, chTempTransferFileName);

   // Break a path name into components.
   _splitpath (szString, szDriveStr, szDirStr, szFileName, szFileExt);

   strcpy (szFile, szFileName);
   strcat (szFile, szFileExt);
   strcpy (szPath, szDriveStr);
   strcat (szPath, szDirStr);

   if (strlen (szPath) == 0)
      strcpy (szPath, DefUtilityDir);

   ZeroMemory (&ofn, sizeof (OPENFILENAME));

   // Specifies the length, in bytes, of the structure.
   ofn.lStructSize = sizeof (OPENFILENAME);

   ofn.hwndOwner = hOwner;
   ofn.hInstance = hInst;
   ofn.lpstrFilter = chFilter;
   ofn.nFilterIndex = 1;
   ofn.lpstrFile = szFile;
   ofn.nMaxFile = sizeof (szFile);
   ofn.lpstrFileTitle = NULL;
   ofn.lpstrInitialDir = szPath;
   ofn.lpstrTitle = chTitle;
   ofn.Flags = dwFlags;
   ofn.lpstrDefExt = chFileExt;
   ofn.FlagsEx = 0;

   // Get the current working directory.
   _getcwd (cOldDir, BUFSIZE_MAX_PATH_LENGTH_FOR_DLAB);

   strcpy (cNewDir, szPath);
   if (strlen (cNewDir) > 1 && cNewDir[strlen (cNewDir) - 1] == '\\')
      cNewDir[strlen (cNewDir) - 1] = (char)0;

   // Change the current working directory.
   _chdir (cNewDir);

   bRet = GetOpenFileName (&ofn);
   switch (bRet)
   {
      case TRUE:
         strcpy (chTempTransferFileName, ofn.lpstrFile);
         break;

      default:
         dwRet = CommDlgExtendedError ();  // FIXME_RO - Warum aufrufen, wenn nicht brauchen ???
         break;
   }

   if (strlen (cOldDir) > 1 && cOldDir[strlen (cOldDir) - 1] == '\\ ')
      cOldDir[strlen (cOldDir) - 1] = 0;

   // Change the current working directory.
   _chdir (cOldDir);

   return bRet;
}


/* ------------------------------------------------------------------------ */
/* Funktionsname     : TKCallOnlineHelp                                     */
/* Hinweis           : angepasste Funktion für Aufruf der Online-Hilfen     */
/*                     zum Projekt LONG_MULTIBYTE_FILENAMES                 */
/* Historie          : 14.03.2008 MHa (Erstellung)                          */
/* ------------------------------------------------------------------------ */

BOOL TKCallOnlineHelp (UINT uiHelpPathInfo, UINT uHelpCommand, UINT uiLastFocus, char* chHelpFileName, DWORD_PTR dwHelpIndex)
{
   BOOL bRet = FALSE;
   DWORD_PTR dwHelpID = 0;
   char chTemp[BUFSIZE_MAX_PATH_LENGTH_FOR_DLAB];
   char sMainHelp[MAX_PATH];

   // Convert a string to lowercase.

   _strlwr (chHelpFileName);

   switch (uiHelpPathInfo)
   {
      case HELP_PATH_IS_ALREADY_COMPLETE_DESIGNED:
         strcpy (chTemp, chHelpFileName);
         break;

      case HELP_PATH_INCLUDE_ONLY_THE_FILE_NAME:
         strcpy (chTemp, ExeFileDir);
         strcat (chTemp, chHelpFileName);
         break;

      default:
         break;
   }

   switch (uiLastFocus)
   {
      case IDD_MODUL_NAME:
         dwHelpID = MODULNAME;
         break;

      case IDD_MODUL_BEZEICHNUNG:
         dwHelpID = MODULBESCHREIB;
         break;

      case IDD_KANAL_NAME:
         dwHelpID = KBEZEICHNUNG;
         break;

      case IDD_KAN00:
         dwHelpID = GL_KANALANZ;
         break;

      case ID_LIST_UNIT:
         dwHelpID = KEINHEIT;
         break;

      default:
         dwHelpID = dwHelpIndex;
         break;
   }

   //MessageBox(NULL, "Mainhelp", "Helptest", MB_OK);
   strcpy (sMainHelp, ExeFileDir);
   strcat (sMainHelp, "mainhelp.chm");
   /*HtmlHelp (
      NULL,
      sMainHelp,
      HH_HELP_CONTEXT,
      INDEX);
      */
   //MessageBox(NULL, "Eigentlicher Aufruf", "Helptest", MB_OK);
   /*HtmlHelp (
      NULL,
      chTemp,
      uHelpCommand,
      dwHelpID);
      */
   UNUSED (uiHelpPathInfo);
   UNUSED (chHelpFileName);
   UNUSED (uiLastFocus);
   UNUSED (uHelpCommand);
   UNUSED (dwHelpIndex);

   return bRet;
}


/* ------------------------------------------------------------------------ */
/* Funktionsname     : helpfuncCreateFile                                   */
/* Hinweis           : Hilfsfunktion für TKOpenFile                         */
/* Historie          : 28.08.2008 MHa (Erstellung)                          */
/* ------------------------------------------------------------------------ */

static HANDLE helpfuncCreateFile (
   LPCSTR path,
   INT mode)
{
   DWORD access = 0;
   DWORD sharing = 0;
   DWORD creation = 0;
   DWORD dwRet = 0;
   HANDLE hCFile;
   /*
   LPVOID lpMsgBuf;
   int iLen=0;
   */

   // MHa 16.12.2009 - Bugfix zur CAR 198863
   if (mode & OF_CREATE)
   {
      CheckCreateDir (
         path,
         TRUE);
   }

   if (mode & OF_CREATE)
   {
      creation = CREATE_ALWAYS;
      access = GENERIC_READ | GENERIC_WRITE;
   }
   else
   {
      creation = OPEN_EXISTING;

      switch (mode & 0x03)
      {
         case OF_READ:
            access = GENERIC_READ;
            break;

         case OF_WRITE:
            access = GENERIC_WRITE;
            break;

         case OF_READWRITE:
            access = GENERIC_READ | GENERIC_WRITE;
            break;

         default:
            access = 0;
            break;
      }
   }

   switch (mode & 0x70)
   {
      case OF_SHARE_EXCLUSIVE:
         sharing = 0;
         break;

      case OF_SHARE_DENY_WRITE:
         sharing = FILE_SHARE_READ;
         break;

      case OF_SHARE_DENY_READ:
         sharing = FILE_SHARE_WRITE;
         break;

      case OF_SHARE_DENY_NONE:
      case OF_SHARE_COMPAT:
      default:
         sharing = FILE_SHARE_READ | FILE_SHARE_WRITE;
         break;
   }

   // The CreateFile function creates or opens the following objects and
   // returns a handle that can be used to access the object:
   hCFile = CreateFile (path,
                        access,
                        sharing,
                        NULL,
                        creation,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL);

   // Return Values
   // If the function succeeds, the return value is an open handle to the
   // specified file.

   if (hCFile == INVALID_HANDLE_VALUE)
   {
      dwRet = GetLastError ();
      /*
      FormatMessage (
      FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
      NULL,
      dwRet,
      MAKELANGID ( LANG_NEUTRAL, SUBLANG_DEFAULT ),
      (LPTSTR) &lpMsgBuf,
      0,
      NULL);

      strcpy ( LongTempString, "\\c0000FF;" );
      iLen = strlen ( LongTempString );
      iLen += strlen ( lpMsgBuf );

      if ( iLen < sizeof ( LongTempString ) )
      {
      strcat ( LongTempString, lpMsgBuf );
      TKKillAll ( LongTempString, "\r" ); // Entferne \r = Carriage Return
      TKKillAll ( LongTempString, "\n" ); // Entferne \n = Zeilenvorschub
      ConsoleOutf ( LongTempString );
      }
      */
   }

   UNUSED (path);
   UNUSED (mode);

   return hCFile;
}


/* ------------------------------------------------------------------------ */
/* Funktionsname     : TKOpenFile                                           */
/* Hinweis           : Die Funktion öffnet mit den empfohlenen Funktionen   */
/*                     eine Datei und konvertiert das Rückgabe HANDLE auf   */
/*                     das übliche 16-Bit HFILE zurück. Dies ermöglicht     */
/*                     die nachfolgende Verwendung von 16-Bit File-IO       */
/*                     Funktionen zum Lesen / Schreiben.                    */
/*                     (Projekt LONG_MULTIBYTE_FILENAMES)                   */
/* Historie          : 28.08.2008 MHa (Erstellung)                          */
/* ------------------------------------------------------------------------ */

HFILE TKOpenFile (LPCSTR path, INT mode)
{
   HANDLE hfile;

   hfile = helpfuncCreateFile (path, mode);

   UNUSED (path);
   UNUSED (mode);

   return HandleToLong (hfile); // Funktion aus basetsd.h
}


/* ------------------------------------------------------------------------ */
/* Funktionsname     : TKCloseFile                                          */
/* Hinweis           : Die Funktion meldet das mit TKOpenFile offene HANDLE */
/*                     (verwaltet als HFILE) wieder ab.                     */
/*                     (Projekt LONG_MULTIBYTE_FILENAMES)                   */
/* Historie          : 28.08.2008 MHa (Erstellung)                          */
/* ------------------------------------------------------------------------ */

HFILE TKCloseFile (HFILE hFile)
{
   return CloseHandle (LongToHandle (hFile)) ? 0 : HFILE_ERROR;
}



/* ------------------------------------------------------------------------ */
/* Funktionsname     : TKStringLineFeed                                     */
/* Hinweis           : Die Funktion erzeugt innerhalb eines Strings jeweils */
/*                     immer nach uiUmbruchNachZeichen Zeichen einen        */
/*                     Zeilenvorschub                                       */
/* Historie          : 30.10.2009 MHa (Erstellung)                          */
/* ------------------------------------------------------------------------ */

void TKStringLineFeed (UINT uiUmbruchNachZeichen, CHAR * csString)
{
   UINT i = 0;
   UINT j = 0;
   int iLen = strlen (csString);

   for (i = 0; i < (UINT)iLen; i++)
   {
      if (csString[i] == ' ')
      {
         if (j >= uiUmbruchNachZeichen)
         {
            csString[i] = '\n';
            j = 0;
         }
      }

      j++;
   }

   UNUSED (csString);
}


/* ------------------------------------------------------------------------ */
/* Funktionsname     : TKPathExists                                         */
/* Hinweis           : Die Funktion prüft das Vorhandensein eines Pfades    */
/*                     Return = TRUE -> Pfad existiert                      */
/*                     Return = FALSE -> Pfad nicht vorhanden               */
/* Historie          : 22.06.2010 MHa (Erstellung)                          */
/* ------------------------------------------------------------------------ */

BOOL TKPathExists (LPSTR cNewDir)
{
   char cOldDir[BUFSIZE_MAX_DIR];
   BOOL bError = FALSE;

   // Altes Verzeichnis merken
   _getcwd (cOldDir, BUFSIZE_MAX_DIR);

   RemoveLastBackSlash ((LPSTR)cNewDir);

   // Changes the current working directory.

   if (_chdir (cNewDir) == 0)
   {
      bError = TRUE;
   }
   else
   {
      bError = FALSE;
   }

   // in altes Verzeichnis wechseln
   RemoveLastBackSlash ((LPSTR)cOldDir);
   _chdir (cOldDir);

   return bError;
}


// MHa 14.12.2012 - Bugfix zur CAR 383382 - Start
/* ------------------------------------------------------------------------ */
/* Funktionsname     : TKTrimSpaces                                         */
/* Hinweis           : Die Funktion entfernt führende und abschließende     */
/*                     white-space character (0x09 – 0x0D or 0x20).         */
/*                     Beispiele:                                           */
/*                     "nothing to trim"                                    */
/*                     "    trim the front"                                 */
/*                     "trim the back     "                                 */
/*                     " trim one char front and back "                     */
/*                     " trim one char front"                               */
/*                     "trim one char back "                                */
/*                     "                   "                                */
/*                     " "                                                  */
/*                     "a"                                                  */
/*                     ""                                                   */
/* Historie          : 14.12.2012 MHa (Erstellung)                          */
/* ------------------------------------------------------------------------ */

char *TKTrimSpaces (char *str)
{
   size_t len = 0;
   char *frontp = str - 1;
   char *endp = NULL;

   if (str == NULL)
   {
      return NULL;
   }

   if (str[0] == '\0')
   {
      return str;
   }

   len = strlen (str);
   endp = str + len;

   // Move the front and back pointers to address the first
   // non-whitespace characters from each end.
   while (isspace (*(++frontp)));

   while (isspace (*(--endp)) && endp != frontp);

   if (str + len - 1 != endp)
   {
      *(endp + 1) = '\0';
   }
   else if (frontp != str &&  endp == frontp)
   {
      *str = '\0';
   }

   // Shift the string so that it starts at str so that if it's
   // dynamically allocated, we can still free it on the
   // returned pointer. Note the reuse of endp to mean the front
   // of the string buffer now.
   endp = str;

   if (frontp != str)
   {
      while (*frontp)
      {
         *endp++ = *frontp++;
      }

      *endp = '\0';
   }

   return str;
}


enum strtrim_mode_t
{
   STRLIB_MODE_ALL = 0,
   STRLIB_MODE_RIGHT = 0x01,
   STRLIB_MODE_LEFT = 0x02,
   STRLIB_MODE_BOTH = 0x03
};


/* ------------------------------------------------------------------------ */
/* Funktionsname     : TKstrcpyTrimBase                                     */
/* Hinweis           :                                                      */
/* Historie          : 14.12.2012 MHa (Erstellung)                          */
/* ------------------------------------------------------------------------ */

char *TKstrcpyTrimBase (
   char *d, // destination
   char *s, // source
   int mode,
   char *delim)
{
   char *o = d; // save orig
   char *e = 0; // end space ptr.
   char dtab[256] = { 0 };

   if (!s || !d)
   {
      return 0;
   }

   while (*delim)
   {
      dtab[*delim++] = 1;
   }

   while ((*d = *s++) != 0)
   {
      if (!dtab[*d])
      {
         // Not a match char
         e = 0; // Reset end pointer
      }
      else
      {
         if (!e)
         {
            e = d;   // Found first match.
         }

         if (mode == STRLIB_MODE_ALL || ((mode != STRLIB_MODE_RIGHT) && (d == o)))
         {
            continue;
         }
      }

      d++;
   }

   if (mode != STRLIB_MODE_LEFT && e)
   {
      // for everything but trim_left, delete trailing matches.
      *e = 0;
   }

   return o;
}


char *TKTrimLeft (char *s, char *d)
{
   return TKstrcpyTrimBase (s, s, STRLIB_MODE_LEFT, d);
}


char *TKTrimRight (char *s, char *d)
{
   return TKstrcpyTrimBase (s, s, STRLIB_MODE_RIGHT, d);
}


char *TKTrimLeftAndRight (char *s, char *d)
{
   return TKstrcpyTrimBase (s, s, STRLIB_MODE_BOTH, d);
}


char *TKKillAll (char *s, char *d)
{
   return TKstrcpyTrimBase (s, s, STRLIB_MODE_ALL, d);
}


/* ------------------------------------------------------------------------ */
/* Ende der Datei                                                           */
/* ------------------------------------------------------------------------ */