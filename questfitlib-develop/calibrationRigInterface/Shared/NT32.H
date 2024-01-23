/* ======================================================================== */
/* Programm   :  DLAB -  Messwerterfassung und Verarbeitung unter Windows   */
/* Modul      :  NT16.H                                                     */
/* ------------------------------------------------------------------------ */
/* Funktionen :  Anpassung für Windows 3.1 zwecks Kompatibilität mit NT     */
/* Erstellt   :  C. Strunk ab 03.03.93                                      */
/* Erweitert  :  ---  (Hier ggf. andere Programmierer eintragen)            */
/* Letzte Änd.:  03.03.93 CS                                                */
/* ======================================================================== */

/* MX Ro 21.07.2015 - Zur Zeit übrig gebliebene Reste von der Umstellung von 16 Bit auf 32 Bit */

#define  SetWindowBackground(h,bg)     SetClassLong(h,GCL_HBRBACKGROUND,(long)(bg))
#define  SetWindowCursor(h,cur)        SetClassLong(h,GCL_HCURSOR,(long)(cur))

#define ClientToScreen(hwnd,rect) ( ClientToScreen(hwnd,rect), (rect)->x &= 0xFFFF, (rect)->y &= 0xFFFF )

/* NT: Immer 100% frei */

/* -eof- */
