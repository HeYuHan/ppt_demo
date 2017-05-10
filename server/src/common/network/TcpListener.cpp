#include "TcpListener.h"
TcpListener::TcpListener()
{
}

TcpListener::~TcpListener()
{
}
bool TcpListener::Initialize()
{
	m_Socket = socket(AF_INET, SOCK_STREAM, 0);
	evutil_make_socket_nonblocking(m_Socket);

	int reuseadd_on = 1;
	setsockopt(m_Socket, SOL_SOCKET, SO_REUSEADDR, (char*)&reuseadd_on, sizeof(reuseadd_on));

	if (bind(m_Socket, (struct sockaddr*)&addr, sizeof(addr)) < 0)
	{
		perror("bind error");
		return false;
	}
	if (listen(m_Socket, 20))
	{
		perror("listen");
		return false;
	}
	m_SocketEvent=Event::AddSocket(m_Socket, EV_READ, this);
	return m_SocketEvent != NULL;
}
void TcpListener::OnRead()
{
	struct sockaddr_in ss;
	socklen_t slen = sizeof(ss);
	int fd = accept(m_Socket, (struct sockaddr*)&ss, &slen);
	if (fd < 0)
	{
		perror("do_accept error");
	}
	else if (fd > FD_SETSIZE)
	{
		char msg[128] = { 0 };
		sprintf(msg, "fd size error:%d", fd);
		evutil_closesocket(fd);
		perror(msg);
	}
	else
	{
		OnClientConnected(fd, ss);
	}
}
void TcpListener::OnClose()
{
	Event::RemoveSocket(m_SocketEvent);
	evutil_closesocket(m_Socket);
}
void TcpListener::OnWrite()
{

}