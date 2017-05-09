#pragma once
#include "common.h"
#include <vector>
class TcpConnection;
class BaseServer:public IServerSocket
{
public:
	BaseServer();
	~BaseServer();
public:
	bool Listen(int port = 0);
	void OnAccept(SOCKET client);
	void OnClose();
	void OnError(short e);
	virtual int Run();
	virtual bool Initialize();
	void Update();
private:
	TcpConnection* GetEmptyConnection();
public:
	SOCKET m_Socket;
	std::vector<TcpConnection*> all_clients;
};
extern BaseServer gServer;

