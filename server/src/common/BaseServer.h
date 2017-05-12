#pragma once
#include <vector>
#include "objectpool.h"
#include "network/TcpListener.h"
#include <map>
class TcpConnection;
class BaseServerListenner :public TcpListener
{
protected:
	virtual void OnClientConnected(int socket, sockaddr_in addr);
};
class BaseServer
{
public:
	BaseServer();
	~BaseServer();

public:
	void OnClose();
	void OnError(short e);
	virtual int Run();
	virtual bool Initialize();
	static void Update(evutil_socket_t, short, void *);
	void RemoveClient(TcpConnection* client);
	void UpdateClients();
public:
	ObjectPool<TcpConnection> client_pool;
	std::map<uint, TcpConnection*> all_clients;
protected:
	
	BaseServerListenner listenner;
};
extern BaseServer gServer;

