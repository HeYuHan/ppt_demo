#pragma once
#ifndef __TCP_CONN_H__
#define __TCP_CONN_H__
#include "../common.h"
#ifndef SOCKET
#define SOCKET int
#endif // !SOCKET
#ifndef SOCKET_ERROR
#define SOCKET_ERROR -1
#endif
#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif // !INVALID_SOCKET
class TcpConnection
{
public:
	TcpConnection();
	~TcpConnection();

private:

};



#endif