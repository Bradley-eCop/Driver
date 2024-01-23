/* Comm16.h : Excerpt aus 16-Bit WINDOWS.H */

#ifndef _COMM_H_
#define _COMM_H_

#ifdef WIN32

#define HCOMM HANDLE

/* Diese Funktionen fehlen in Win32-API */

HCOMM WINAPI OpenComm(LPCSTR port, UINT cbInQueue, UINT cbOutQueue);
int WINAPI CloseComm ( HCOMM hComm );

int WINAPI ReadComm ( HCOMM hComm, void FAR *data, int nBytes );
int WINAPI WriteComm ( HCOMM hComm, void FAR *data, int nBytes );
/* UngetCommChar is not supported */
int WINAPI FlushComm ( HCOMM hComm, int fnQueue );

int WINAPI GetCommError ( HCOMM hComm, COMSTAT FAR *stat );

#else /* ! WIN32 */

/* 16-Bit-Seite */
#define HCOMM                     int
#define SetCommState(comm,state)  SetCommState(state)
#define UngetCommChar             Bitte_Kein_UngetCommChar_Benutzen

#endif /* WIN32 */

#endif /* _COMM_H_ */
