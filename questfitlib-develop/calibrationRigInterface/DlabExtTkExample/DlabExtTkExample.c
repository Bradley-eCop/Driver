/* ======================================================================== */
/* Program    :  DASYLab  -  Measure and Analysis in Windows 3.1 and above  */
/* Module     :  DlabExtTkExample.H                                         */
/* ------------------------------------------------------------------------ */
/* Functions  :  All necessary Functions for this Module                    */
/* ======================================================================== */


/* ------------------------------------------------------------------------ */
/* Include the necessary Windows and C Header Files                         */
/* ------------------------------------------------------------------------ */

#include "PRE_WIN.H"
#include <WINDOWS.H>
#include "POST_WIN.H"
#include <WINDOWSX.H>
#include <DLGS.H>
#include <STRING.H>
#include <COMMDLG.H>


/* ------------------------------------------------------------------------ */
/* Include DASYLab´s Header Files                                           */
/* ------------------------------------------------------------------------ */

#include "DLAB.H"
#include "DlabExtTkExample.H"


/* ------------------------------------------------------------------------ */
/* Function prototypes                                                      */
/* ------------------------------------------------------------------------ */

static void ExpandModuleBar (void);


// Init-Functions for each module class

void Init_LAMP (void);
void Init_GENERATOR (void);
void Init_QUESTFIT (void);


#ifdef _DEBUG
#if VERSION_CODE < 1400
#pragma message( __DATE__" "__TIME__ "   *** ERROR - VERSION_CODE is invalid - possible mixup of files of older DASYLab toolkits" )
#endif
#if VERSION_CODE == 1400
#pragma message( __DATE__" "__TIME__ "   *** Extensions Toolkit *** Debug 14.0 (for DASYLab 2016)" )
#endif
#else
#if VERSION_CODE < 1400
#pragma message( __DATE__" "__TIME__ "   *** ERROR - VERSION_CODE is invalid - possible mixup of files of older DASYLab toolkits" )
#endif
#if VERSION_CODE == 1400
#pragma message( __DATE__" "__TIME__ "   *** Extensions Toolkit *** Release 14.0 (for DASYLab 2016)" )
#endif
#endif


/* ------------------------------------------------------------------------ */
/* Function Name     : Init_DLL                                             */
/* Description       : Register all supported modules classes               */
/* ------------------------------------------------------------------------ */

BOOL Init_DLL (void)
{
   // Expand DASYLab's module bar for the new modules
   ExpandModuleBar ();

   // Init all new Modules here
   //Init_QUESTFIT ();
   Init_GENERATOR ();

   return TRUE;
}


/* ------------------------------------------------------------------------ */
/* Function Name     : Exit_DLL                                             */
/* Description       : Unload DLL                                           */
/* ------------------------------------------------------------------------ */

BOOL Exit_DLL (void)
{
   return TRUE;
}


/* ------------------------------------------------------------------------ */
/* Function Name     : SetupProc                                            */
/* Description       : Callback function for setup menu item                */
/* ------------------------------------------------------------------------ */

void SetupProc (void)
{
   MessageBox (NULL, "Do here some setup functions!", "Setup", MB_OK);
}


// ***************************************************************************
// MakeDASYLabInsertMenuString
//
// Description:
//    This function creates a menu insert string using the structure 'DASYLAB_INSERT_MENU'.
//    DASYLab makes the menu change by this string.
//
//
// In:
//    pDlabMenuStruct: Pointer to the structure DASYLAB_INSERT_MENU containing all the needed information
//    for the desired menu item (included the menu path).
// Out:
//    ---.
//
// Return:
//    BOOL: TRUE, if the insertion of the menu item was done, in other cases FALSE.
// ***************************************************************************


BOOL MakeDASYLabInsertMenuString (DASYLAB_INSERT_MENU *pDlabMenuStruct)
{
   char szDlabMenuStructString[SUB_MENUS_ENTRY_MAXLEN];
   BOOL bMenuItemInserted = FALSE;

   wsprintf (szDlabMenuStructString, "%u;%u;%s;%s;", pDlabMenuStruct->uiSize, pDlabMenuStruct->uiVersion,
             pDlabMenuStruct->szMainMenuEntry, pDlabMenuStruct->szSubMenusEntry);
   wsprintf (szDlabMenuStructString, "%s%s;%s;%u;%c;", szDlabMenuStructString, pDlabMenuStruct->szNewMenuEntries,
             pDlabMenuStruct->szMenuGroupEntries, pDlabMenuStruct->uiNewMenuID, pDlabMenuStruct->cMenuAccessKey);

   if (DASYLabInsertMenu (szDlabMenuStructString) == TRUE)
      bMenuItemInserted = TRUE;

   return bMenuItemInserted;
}


/* ------------------------------------------------------------------------ */
/* Function Name     : MakeDASYLabMenuSeparator                             */
/* Description       : Create a MenuSeparator in the DASYLab main menu      */
/* ------------------------------------------------------------------------ */

BOOL MakeDASYLabMenuSeparator (DASYLAB_INSERT_MENU *pDlabMenuStruct)
{
   pDlabMenuStruct->uiNewMenuID = 0;
   pDlabMenuStruct->cMenuAccessKey = '0';

   if (strcmp (pDlabMenuStruct->szNewMenuEntries, "") != 0)
      strcat (pDlabMenuStruct->szNewMenuEntries, "//");

   strcat (pDlabMenuStruct->szNewMenuEntries, "Separator");

   return ExpandDASYLabMenu (pDlabMenuStruct);
}


/* ------------------------------------------------------------------------ */
/* Function Name     : ExpandDASYLabMenu                                    */
/* Description       : Extended the DASYLab main menu                       */
/* ------------------------------------------------------------------------ */

BOOL ExpandDASYLabMenu (DASYLAB_INSERT_MENU *pDlabMenuStruct)
{
   pDlabMenuStruct->uiSize = sizeof (DASYLAB_INSERT_MENU);
   pDlabMenuStruct->uiVersion = DASYLAB_INSERT_MENU_VERSION;

   return MakeDASYLabInsertMenuString (pDlabMenuStruct);
}


/* ------------------------------------------------------------------------ */
/* Function Name     : ExpandModuleBar                                      */
/* Description       : Expand the DASYLab main menu                         */
/* ------------------------------------------------------------------------ */

// ***************************************************************************
//    szMainMenuEntry: SubMenu for insertion menu items. Possible values are "MOD"(=Module-SubMenu),
//                     "ME"(=Measurement: Experiment-SubMenu) and "HLP"(=Help-SubMenu).
//    szSubMenusEntry: SubMenus depends of szMainMenuEntry.
//                     "MOD": "IO"(=Ein/Ausgänge), "TRIG" (=Trigger Functions), "MATH" (=Mathematics), "STAT" (=Statistics),
//                                "SIG" (=Signal Analysis), "CONTR" (=Control), "DISPL" (=Display),
//                                "FILE" (=Files), "REDUCT" (=Data reduction), "NET" (=Netzwork),
//                                "SPEC" (=Special) and "ADDON" (=Add-on Modules) allowed.
//                     "ME": "HS"(=HardwareSetup) and "ES"(=ExperimentSetup) allowed.
//                     "HLP": "HWH"(=HardwareHelp) allowed.
//    szMenuGroupEntry: The szSubMenusEntry-SubMenu is devided in Menu Groups. There already exists following Menu Group
//                      Names:
//                      MODULE
//                      "IO": "DRV" (In/Output for HardwareDriver/DDE/RS232/ICom/IEEE488), "SOFT_INTERFACE" (IVI), "BUS_SYSTEMS" (Modbus).
//                      "TRIG": "TRIGGER" (all trigger) and "RELAIS".
//                      "MATH": "FORMULA", "LOGIC_OPERATION", "SLOPE_LIMIT", "REF_CURVE".
//                      "STAT": "CHARACTERISTICS", "ANALYSIS_STO", "ANALYSIS_DET", "CHECK_REF_CURVE".
//                      "SIG": "SIG_ANALYSIS1" (Filter), "SIG_ANALYSIS2" (Kenngrößen).
//                      "CONTR": "GEN", "CONTR1", "CONTR2" (Timer), "GLOBALS".
//                      "DISPL": "GRAPH", "VALUE".
//                      "FILE": "FILES", "ODBC".
//                      "REDUCT": "AVERAGE", "SEPARATE", "CLIPPING".
//                      "NET": "NETIO", "MSG", "DSOCKETS".
//                      "SPEC": "BBOX" (BlackBox), "MSG", "TIMEBASE", "ADAPTION".
//                      "ADDON"(serial number required): "FUNCTION", "UFFILE".
//                      MESSEN
//                      "HS"(HardwareSetup): "DRV"
//                      "ES"(ExperimentSetup): "DRV"
//                      "TB"(TimeBase): "DRV"
//                      HILFE
//                      "HWH"(HardWareHelp): "HARDWAREHELP"
// ***************************************************************************

static void ExpandModuleBar (void)
{
   DASYLAB_INSERT_MENU DlabMenuStruct;

   // FirstSubMenu.
   strcpy (DlabMenuStruct.szMainMenuEntry, "ME");
   // SecondSubMenu.
   strcpy (DlabMenuStruct.szSubMenusEntry, "ES");
   // MenuGroup.
   strcpy (DlabMenuStruct.szMenuGroupEntries, "GLOBAL");
   // NewMenuID.
   DlabMenuStruct.uiNewMenuID = MN_EXTTK_SETUP;
   // MenuAccessKey.
   DlabMenuStruct.cMenuAccessKey = 'G';
   // NewMenuPathItemName.
   wsprintf (DlabMenuStruct.szNewMenuEntries, "&TK_New !!!//Global Setup");

   if (ExpandDASYLabMenu (&DlabMenuStruct) == TRUE)
   {
      // Register the inserted menu item as it is not a module. (Modules are registered calling: RegisterModulClass(&mc)).
      RegisterMenuEntry (DlabMenuStruct.uiNewMenuID, &SetupProc);
   }

   // For a menu separator.
   // wsprintf(DlabMenuStruct.szNewMenuEntries, "&New !!!");
   // MakeDASYLabMenuSeparator ( &DlabMenuStruct );
}


/* ------------------------------------------------------------------------ */
/* Function Name     : CopyBlock                                            */
/* Description       : Copy an input block to the corresponding output      */
/* ------------------------------------------------------------------------ */

void TOOLAPI CopyBlock (MODULE *ThisModule, UINT wEingang)
{
   FIFO_HEADER *OutFifo = ThisModule->Fifo[wEingang];
   DATA_BLOCK_HEADER *OutputBlock;
   DATA_BLOCK_HEADER *InputBlock;

   OutputBlock = GetCurrentOutputBlock (OutFifo);

   if (OutputBlock == NULL)
   {
      ImpossibleCase ();
      return;
   }

   InputBlock = GetInputBlock (ThisModule, wEingang);

   if (InputBlock == NULL)
   {
      ImpossibleCase ();
      return;
   }

   OutputBlock->fStartTime = InputBlock->fStartTime;
   OutputBlock->fSampleDistance = InputBlock->fSampleDistance;
   OutputBlock->uiBlockSize = InputBlock->uiBlockSize;

   memcpy (OutputBlock->Data, InputBlock->Data, InputBlock->uiBlockSize * sizeof (DLAB_FLOAT)); // TK14: DLAB_FLOAT is now double

   // TK14: For future compatibility: Copy extra memory (per data block) from the "Father" block to the block we filled with data above
   //     : This will have no effect in DASYLab 14 (2016) but your module/dll will support a new feature in DASYLab 15 without recompiling
   //     : The cpu cost for DASYLab 14 is near zero - the call of this funtion is optional for DASYLab 14 and mandatory for DASYLab 15

   // If the InFifo parameter is NULL, the function assumes, that the maximum blocksize of the input fifo is equal to the maximum blocksize
   // of the output fifo (what is "the normal behaviour") . If you are unsure (what you shouldn't be because you wrote/modified the 
   // SetupFifo_xxx routine) or the maximum blocksize of OutFifo and InFifo is not equal, the provide the InFifo as parameter.
   EmemBlock_PROCESS_MsgCopyPlain (OutFifo, OutputBlock, NULL, InputBlock);

   ReleaseOutputBlock (OutFifo);
}


/* ------------------------------------------------------------------------ */
/* Function Name     : SaveHwndPos                                          */
/* Description       : Save current window position                         */
/* ------------------------------------------------------------------------ */

void SaveHwndPos (MODULE_WND_POS *WndPosPtr, HWND hwnd)
{
   if (WndPosPtr != NULL && hwnd != NULL)
   {
      WndPosPtr->bUsed = TRUE;
      GetWindowRect (hwnd, &WndPosPtr->reWnd);
      WndPosPtr->nWndFlags = 0;

      if (IsMinimized (hwnd))
         WndPosPtr->nWndFlags |= MINIMIZE_FLAG;
      else
         WndPosPtr->nWndFlags &= ~MINIMIZE_FLAG;

      if (IsWindowVisible (hwnd))
         WndPosPtr->nWndFlags &= ~HIDE_FLAG;
      else
         WndPosPtr->nWndFlags |= HIDE_FLAG;

      WndPosPtr->bMaximized = IsMaximized (hwnd);
   }
}


/* ------------------------------------------------------------------------ */
/* Function Name     : ShowHwndPos                                          */
/* Description       : Show the window in given position and size           */
/* ------------------------------------------------------------------------ */

void ShowHwndPos (MODULE_WND_POS *WndPosPtr, HWND hwnd)
{
   // Safety Check
   if (!WndPosPtr || !hwnd)
      return;

   // Nichts zu tun
   if (!WndPosPtr->bUsed)
      return;

   // Ausblenden
   if ((WndPosPtr->nWndFlags & HIDE_FLAG) != 0)
   {
      ShowWindow (hwnd, SW_HIDE);
      return;
   }

   if ((WndPosPtr->nWndFlags & MINIMIZE_FLAG) != 0)
      ShowWindow (hwnd, SW_SHOWMINIMIZED);
   else
   {
      if (WndPosPtr->bMaximized)
         ShowWindow (hwnd, SW_SHOWMAXIMIZED);
      else
      {
         ShowWindow (hwnd, SW_SHOWNORMAL);
         MoveWindow (hwnd, WndPosPtr->reWnd.left, WndPosPtr->reWnd.top,
                     WndPosPtr->reWnd.right - WndPosPtr->reWnd.left, WndPosPtr->reWnd.bottom - WndPosPtr->reWnd.top, TRUE);
      }
   }
   UpdateWindow (hwnd);
}


/* ------------------------------------------------------------------------ */
/* Function Name     : AppendLayoutMenu                                     */
/* ------------------------------------------------------------------------ */

void AppendLayoutMenu (MODULE *ThisModule)
{
   HMENU hSysMenu;

   hSysMenu = GetSystemMenu (ThisModule->hwndWindow, FALSE);
   AppendMenu (hSysMenu, MF_SEPARATOR, 0, NULL);
   LoadString (hInst, STR_ACTION_LAYOUT_ACT, ShortTempString, sizeof (ShortTempString) - 1);
   AppendMenu (hSysMenu, MF_STRING, MN_LAYOUT_ACTUAL, ShortTempString);
}


/* ------------------------------------------------------------------------ */
/* Function Name     : CheckMinMax                                          */
/* ------------------------------------------------------------------------ */

void CheckMinMax (UINT *Wert, UINT Min, UINT Max)
{
   if (*Wert < Min)
      *Wert = Min;

   if (*Wert > Max)
      *Wert = Max;
}


/* ------------------------------------------------------------------------ */
/* Function Name     : ModalChooseFontDisableSize                           */
/* ------------------------------------------------------------------------ */

BOOL ModalChooseFontDisableSize (void *fntptr, BOOL bEnableAllWindows, HWND hwndOwner)
{
   CHOOSEFONT *cf = (CHOOSEFONT *)fntptr;
   BOOL rc = FALSE;

   // Check to japanese version
   if (SerialOpt.Sprache != ID_SPRACHE_JAPAN)
      cf->Flags |= CF_SCRIPTSONLY | CF_TTONLY;  // NO hook used !!
   else
      cf->Flags |= CF_TTONLY;

   cf->lpfnHook = NULL;

   if (bEnableAllWindows)
      EnableAllWindows (FALSE);
   else if (hwndOwner != NULL)
      EnableWindow (hwndOwner, FALSE);

   rc = ChooseFont (cf);
   if (bEnableAllWindows)
      EnableAllWindows (TRUE);
   else if (hwndOwner != NULL)
      EnableWindow (hwndOwner, TRUE);

   return rc;
}


/* ------------------------------------------------------------------------ */
/* End of file                                                              */
/* ------------------------------------------------------------------------ */
