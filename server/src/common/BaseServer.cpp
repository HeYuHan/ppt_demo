#include "BaseServer.h"
#include "network/TcpConnection.h"
TimerEvent m_UpdateTimer;
BaseServer::BaseServer()
{
}

BaseServer::~BaseServer()
{
}
static void UpdateTimer(evutil_socket_t t, short e, void *arg)
{
	BaseServer* server = static_cast<BaseServer*>(arg);
	if (server)
	{
		server->Update();
	}
	Event::AddTimer(m_UpdateTimer, UpdateTimer, arg, 10);
}
bool BaseServer::Initialize()
{
	if (!Event::Initialize())return false;
	UpdateTimer(-1,0,this);
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
