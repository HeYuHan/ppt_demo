#include "event.h"
Event::Event()
{
	
}

Event::~Event()
{
}
bool Event::Init()
{
#ifdef MSBUILD
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 0);
	int ret = WSAStartup(version, &wsaData);
	if (ret != 0)return false;
#endif
	return true;
}