#pragma once
#include "../event_ext.h"
#include "../define.h"
class TcpListener:ISocketEvent
{
public:
	TcpListener();
	~TcpListener();
protected:
	SOCKET m_Socket;
	sockaddr_in addr;
	SocketEvent* m_SocketEvent;
protected:
	// on client connected
	virtual void OnClientConnected(int socket, sockaddr_in addr) = 0;
public:
	bool Initialize();
private:
	// on read
	virtual void OnRead();
	// on write
	virtual void OnWrite();
	virtual void OnClose();
private:

};

