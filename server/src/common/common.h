#pragma once
#ifndef __COMMON_H__
#define __COMMON_H__
#include "define.h"
#include "event_ext.h"

#ifdef WIN32
#include <windows.h>
#include <WinSock2.h>
#pragma comment( lib, "ws2_32.lib")
#else
#include <unistd.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/time.h>
#endif
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <new>
#endif
