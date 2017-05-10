#include "BaseServer.h"
#include "network/TcpConnection.h"
BaseServer gServer;
BaseServer::BaseServer()
{
}

BaseServer::~BaseServer()
{
}
void BaseServer::Update(evutil_socket_t t, short e, void *arg)
{
	gServer.UpdateClients();
	Event::AddTimer(Update, arg, 1);
}
void BaseServer::OnClientConnected(int socket, sockaddr_in addr)
{
	
	auto c = client_pool.Allocate();
	if (c)
		c->SetSocketEvent(socket, addr);
	all_clients.insert(std::map<uint, TcpConnection*>::value_type(c->uid, c));
	printf("current client:%d\n", client_pool.Count());
}
bool BaseServer::Initialize()
{
	if (!Event::Initialize())return false;
	if (!client_pool.Initialize(1024 * 10))return false;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = 0;
	addr.sin_port = htons(9595);
	if (!TcpListener::Initialize())return false;
	BaseServer::Update(-1,0,NULL);
	return true;
}
int BaseServer::Run()
{
	return Event::Dispatch();
}
void BaseServer::OnClose()
{

}
void BaseServer::OnError(short e)
{

}
void BaseServer::RemoveClient(TcpConnection* client)
{
	client_pool.Free(client->uid);
	all_clients.erase(client->uid);
}
void BaseServer::UpdateClients()
{
	for (auto iter : all_clients)
	{
		iter.second->Update();
	}
}