#pragma once
#include <vector>
#include "objectpool.h"
#include "network/TcpListener.h"
#include <map>
class TcpConnection;
class TcpListener;
class BaseServer:public TcpListener
{
public:
	BaseServer();
	~BaseServer();
protected:
	virtual void OnClientConnected(int socket, sockaddr_in addr);
public:
	void OnClose();
	void OnError(short e);
	virtual int Run();
	virtual bool Initialize();
	static void Update(evutil_socket_t, short, void *);
	void RemoveClient(TcpConnection* client);
	void UpdateClients();
protected:
	ObjectPool<TcpConnection> client_pool;
	std::map<uint,TcpConnection*> all_clients;
};
extern BaseServer gServer;

