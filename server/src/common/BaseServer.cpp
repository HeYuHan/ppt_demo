#include "BaseServer.h"
#include "network/TcpConnection.h"
BaseServer gServer;
TimerEvent m_UpdateTimer;
BaseServer::BaseServer()
{
}

BaseServer::~BaseServer()
{
}
void BaseServer::Update(evutil_socket_t t, short e, void *arg)
{
	gServer.UpdateClients();
	Event::AddTimer(m_UpdateTimer,Update, arg, 10);
}
void BaseServer::OnClientConnected(int socket, sockaddr_in addr)
{
	printf("current client:%d\n", client_pool.Count());
	auto c = client_pool.Allocate();
	if (c)
		c->SetSocketEvent(socket, addr);
	all_clients.insert(std::map<uint, TcpConnection*>::value_type(c->uid, c));
	
}
bool BaseServer::Initialize()
{
	if (!Event::Initialize())return false;
	if (!client_pool.Initialize(1024 * 10))return false;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = 0;
	addr.sin_port = htons(9595);
	if (!TcpListener::Initialize())return false;
	Update(-1,0,nullptr);
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