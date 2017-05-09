#include "BaseServer.h"
#include "network/TcpConnection.h"
BaseServer gServer;
BaseServer::BaseServer():
	m_Socket(INVALID_SOCKET)
{
}

BaseServer::~BaseServer()
{
}
TimerEvent* m_UpdateEvent = nullptr;
void ServerUpdate(evutil_socket_t t, short s, void *arg)
{
	gServer.Update();
	Event::AddTimer(m_UpdateEvent, 0);
}
void BaseServer::Update()
{
	for (TcpConnection* c : all_clients)
	{
		c->Update();
	}
}
bool BaseServer::Initialize()
{
	Event::Initialize();
	m_UpdateEvent=Event::AddTimer(ServerUpdate, nullptr, 0);
	return true;
}
TcpConnection* BaseServer::GetEmptyConnection()
{
	for (TcpConnection* c : all_clients)
	{
		if (c->m_State != TcpState::S_Connected)
		{
			return c;
		}
	}
	TcpConnection* tcp = TcpConnection::Create();
	if (tcp)
	{
		all_clients.push_back(tcp);
		return tcp;
	}
	return nullptr;
}
int BaseServer::Run()
{
	return Event::Dispatch();
}
void BaseServer::OnAccept(SOCKET client)
{
	printf("current client count:%d\n", all_clients.size());
	auto c = GetEmptyConnection();
	c->SetSocketEvent(client);
}
void BaseServer::OnClose()
{

}
void BaseServer::OnError(short e)
{

}
bool BaseServer::Listen(int port /* = 0 */)
{
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0;
	sin.sin_port = htons(9595);
	m_Socket = socket(AF_INET, SOCK_STREAM, 0);
	evutil_make_socket_nonblocking(m_Socket);
#ifdef WIN32
	int reuseadd_on = 1;
	setsockopt(m_Socket, SOL_SOCKET, SO_REUSEADDR, (char*)&reuseadd_on, sizeof(reuseadd_on));
#endif
	if (bind(m_Socket, (struct sockaddr*)&sin, sizeof(sin)) < 0)
	{
		perror("bind error");
		return false;
	}
	if (listen(m_Socket, 20))
	{
		perror("listen");
		return false;
	}
	Event::AccpetSocket(m_Socket, this);
	return true;
}