/*
/////////////////////////////////////////////////////////////////////
//
// Enable inclusion of WINDOWS.H without warnings
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

#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0601   // MX Ro 4.08.2015 - Windows 7

#define _CRT_SECURE_NO_DEPRECATE 1

// In Visual C++ 2005, _ftime_s is equivalent to _ftime64_s and _timeb
// contains a 64-bit time. This is true unless _USE_32BIT_TIME_T is
// defined, in which case the old behavior is in effect; _ftime_s
// uses a 32-bit time and _timeb contains a 32-bit time.
#define _USE_32BIT_TIME_T 1

// MX_RO 19.09.2015 - die Windows Header Dateien lassen sich ohne Warnungen compilieren
// Kein Ausschalten von den Warnungen 4115, 4201, 4214, 4515 mehr

/* -eof- */
