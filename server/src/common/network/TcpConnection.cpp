#include "TcpConnection.h"
#include "../common.h"
TcpConnection::TcpConnection():
	m_State(S_Idle),m_BufferEvent(nullptr)
{
}

TcpConnection::~TcpConnection()
{

}
NetworkStream* TcpConnection::GetStream()
{
	return this;
}
void TcpConnection::OnRead()
{
	int totle_len = read_end - read_position;
	if (totle_len > 4)
	{
		int data_len = 0;
		memcpy(&data_len, read_position, sizeof(int));
		if (totle_len - data_len >= 4)
		{
			char* backup_position = read_position + 4;
			read_position = backup_position;
			OnMessage();
			read_position = backup_position + data_len;
			int unread_len = read_end - read_position;
			if (unread_len > 0)
			{
				memcpy(read_buff, read_position, unread_len);
			}
			read_position = read_buff;
			read_end = read_buff + unread_len;
		}
	}
}
void TcpConnection::OnWrite()
{
	if (m_BufferEvent&&send_position&&send_end)
	{
		int data_len = send_end - send_position;
		if (data_len > 0)
		{
			struct evbuffer *output = bufferevent_get_output(m_BufferEvent);
			if (evbuffer_add(output, send_position, data_len) == 0)
			{
				send_position += data_len;
			}
		}

	}
}
void TcpConnection::OnClose()
{
	Reset();
}
void TcpConnection::OnError(short error)
{
	if (error & BEV_EVENT_EOF) {
		/* connection has been closed, do any clean up here */
		/* ... */
		//perror("BEV_EVENT_EOF");
		OnClose();
	}
	else if (error & BEV_EVENT_ERROR) {
		/* check errno to see what error occurred */
		/* ... */
		//perror("BEV_EVENT_ERROR");
		OnClose();
	}
	else if (error & BEV_EVENT_TIMEOUT) {
		/* must be a timeout event handle, handle it */
		/* ... */
		perror("BEV_EVENT_TIMEOUT");
	}
	FreeBufferEvent();
	
}
void TcpConnection::Reset()
{
	
	SetReadBuffer(read_buffer, 0, STREAM_BUFF_SIZE);
	SetWriteBuffer(write_buffer, 0, STREAM_BUFF_SIZE);
	m_State = S_Idle;
	m_Socket = INVALID_SOCKET;
}
void TcpConnection::FreeBufferEvent()
{
	if (m_BufferEvent)
	{
		bufferevent_disable(m_BufferEvent, EV_READ | EV_WRITE);
		bufferevent_free(m_BufferEvent);
		m_BufferEvent = nullptr;
	}

}
void TcpConnection::OnMessage()
{
	char msg[128] = { 0 };
	ReadString(msg,128);
	BeginWrite();
	WriteString("hello client");
	EndWrite();
}
void TcpConnection::Update()
{
	if (m_State == S_Connected)
	{
		OnRead();
		OnWrite();
	}

}
void TcpConnection::OnConnected()
{
	
	m_State = S_Connected;
	
}
void TcpConnection::Close()
{
}
void TcpConnection::Disconnect()
{
	FreeBufferEvent();
	evutil_closesocket(m_Socket);
	Reset();
}
void TcpConnection::SetSocketEvent(SOCKET socket)
{
	Reset();
	FreeBufferEvent();
	m_Socket = socket;
	m_BufferEvent = Event::ListenSocket(m_Socket,this);
	OnConnected();
}
bool TcpConnection::Initialize()
{
	Reset();
	return true;
}
TcpConnection* TcpConnection::Create()
{
	TcpConnection* tcp = new (std::nothrow) TcpConnection();
	if (tcp&&tcp->Initialize())
	{
		return tcp;
	}
	free(tcp);
	return nullptr;
}