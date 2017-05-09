#pragma once
#ifndef __DEFINE_H__
#define __DEFINE_H__
typedef unsigned char byte;
typedef byte uint8;
typedef long int64;
typedef unsigned long uint64;

typedef unsigned int uint32;
typedef int int32;
typedef unsigned short uint16;
typedef short int16;


#ifdef FD_SETSIZE
#undef FD_SETSIZE
#define FD_SETSIZE 2048
#else
#define FD_SETSIZE 2048
#endif

#ifndef WIN32
typedef int SOCKET
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1
#endif // !WIN32
#ifdef WIN32
typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
#endif
#endif