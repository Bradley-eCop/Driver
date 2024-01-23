/* ======================================================================== */
/* Program    :  DASYLab  -  Measure and Analysis in Windows 3.1 and above  */
/* Module     :  DlabExtTkExample.H                                         */
/* ======================================================================== */

// new help ID
#ifdef INDEX
   # undef INDEX
   # define INDEX                                                         2000
#endif

// Nearly zero should be:
#define NEAR_ZERO                                                        1e-30

// Undefine used menu IDs from main project
#undef MN_MODUL_LAMP
#undef MN_MODUL_GENERATOR
#undef MN_MODUL_DEMAND_TRIG
#undef MN_MODUL_DERIVATION
#undef MN_STATUS_LAMP
#undef MN_STATUS_GENERATOR
#undef MN_STATUS_DEMAND_TRIG
#undef MN_STATUS_DERIVATION

// Used menu IDs for Toolkit (reserved Area: 2950-2999
#define MN_MODUL_LAMP                                                     2950
#define MN_MODUL_GENERATOR                                                2951
#define MN_MODUL_DEMAND_TRIG                                              2952
#define MN_MODUL_DERIVATION                                               2953
#define MN_MODUL_QUESTFIT                                                 2954

// Used status string IDs for Toolkit (reserved Area: 3950-3999
#define MN_STATUS_LAMP                                                    3950
#define MN_STATUS_GENERATOR                                               3951
#define MN_STATUS_DEMAND_TRIG                                             3952
#define MN_STATUS_DERIVATION                                              3953
#define MN_STATUS_QUESTFIT                                                3954

#define ACTION_LAYOUT_ACT                                        ACTION_USER_0
#define STR_ACTION_LAYOUT_ACT                                            24500
#define MN_LAYOUT_ACTUAL                                                 24501

#define IDD_0                                                             2000

#define MN_EXTTK_SETUP                                                    4990

#ifdef __cplusplus
   extern "C" { // Assume C declarations for C++
#endif // __cplusplus

void TOOLAPI CopyBlock ( MODULE *ThisModule, UINT wEingang );
void SaveHwndPos ( MODULE_WND_POS *WndPosPtr, HWND hwnd );
void ShowHwndPos ( MODULE_WND_POS *WndPosPtr, HWND hwnd );
void AppendLayoutMenu ( MODULE *ThisModule );
//void CheckWindowPosition ( MODULE *ThisModule );
void CheckMinMax ( UINT *Wert, UINT Min, UINT Max );
BOOL ModalChooseFontDisableSize ( void *fntptr, BOOL bEnableAllWindows, HWND hwndOwner );

BOOL ExpandDASYLabMenu ( DASYLAB_INSERT_MENU *pDlabMenuStruct );
BOOL MakeDASYLabMenuSeparator ( DASYLAB_INSERT_MENU *pDlabMenuStruct );

#ifdef __cplusplus
} // End of extern "C" {
#endif // __cplusplus



/* ------------------------------------------------------------------------ */
/* End of file                                                              */
/* ------------------------------------------------------------------------ */
