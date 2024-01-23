/*
/////////////////////////////////////////////////////////////////////
//
// Revert to standard warnings after inclusion of WINDOWS.H
//
/////////////////////////////////////////////////////////////////////
//
// Copyright (c) 1995 - 2001 National Instruments Services GmbH
// All rights reserved
//
/////////////////////////////////////////////////////////////////////
//
// Created: 06-MAY-1997 / CS
//
/////////////////////////////////////////////////////////////////////
*/

#ifndef _NEW_WARNINGS
#define MessageBoxC(hwnd, text1, text2, flags) (ShowWarning ((text2), (text1)))
#define MessageBoxP3(text1, text2, flags) (ShowWarning ((text2), (text1)))
#define MessageBoxP2(text1, text2) (ShowWarning ((text2), (text1)))
#define MessageBoxP1(text1) (ShowWarning (("Error"), (text1)))
#define _NEW_WARNINGS
#endif // _NEW_WARNINGS

// MHa 26.07.2006 - warning C4996
#define ecvt _ecvt
#define itoa _itoa
#define ltoa _ltoa
#define stricmp _stricmp
#define strlwr _strlwr
#define strnicmp _strnicmp
#define strupr _strupr
// eof
