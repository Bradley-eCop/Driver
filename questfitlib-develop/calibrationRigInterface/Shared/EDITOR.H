
/* ======================================================================== */
/* Programm   :  DLAB  -  Messwerterfassung und Verarbeitung unter Windows  */
/* Datei      :  EDITOR.C                                                   */
/* ------------------------------------------------------------------------ */
/* Funktionen :  Ein kleiner Editor in einem Fenster.                       */
/*               Abgeleitet aus POPPAD2 von Petzold.                        */
/* Letzte Änd.:  21.07.93 CS                                                */
/* ======================================================================== */

#ifndef __EDITOR_H
#define __EDITOR_H

/* We specify a definite packing for the following data structures */
#ifndef RC_INVOKED

/* Vorsicht ! Diese Struktur darf (wg. Toolkit) nir geändert, sondern immer nur */
/* am Ende erweitert werden.                                                    */

typedef struct
{
   UINT size;
   HWND hwndEdit;
   LPSTR Title;
   LPSTR buf;
   UINT EditMode;
   int MaxSize;
   UINT *lpModFlag;
   UINT ModFlagVal;
} EDTEXTDEF;


#ifdef _TOOLKIT_
typedef void (TOOLAPI *PROTO_EditText) (EDTEXTDEF *lpEtd);
EXTERN PROTO_EditText  EditText;
#else
void TOOLAPI EditText ( EDTEXTDEF *lpEtd );
#endif


LRESULT CALLBACK EditorWndProc (HWND, UINT, WPARAM, LPARAM);

#endif  /* ndef RC_INVOKED */


/*--------------------------
   Include-Datei für POPPAD2
   --------------------------*/

#define IDM_NEW      1
#define IDM_OPEN     2
#define IDM_SAVE     3
#define IDM_SAVEAS   4
#define IDM_PRINT    5
#define IDM_EXIT     6

#define IDM_UNDO    10
#define IDM_CUT     11
#define IDM_COPY    12
#define IDM_PASTE   13
#define IDM_DEL     14
#define IDM_SELALL  15

#define IDM_HELP    IDHELP
#define IDM_ABOUT   22

#define STR_EDIT_DELETE_CHANGES    23930
#define STR_EDIT_PROTECT_CHANGES   23931
#define STR_EDIT_EDITOR_NAME       23932

#endif /* __EDITOR_H */

/* -eof- */
