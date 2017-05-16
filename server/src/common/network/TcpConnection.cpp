#include "TcpConnection.h"
#include "../common.h"
#include "../BaseServer.h"
TcpConnection::TcpConnection():
	m_State(S_Idle),m_BufferEvent(nullptr)
{
}

TcpConnection::~TcpConnection()
{

}
void TcpConnection::WriteMessage()
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
void TcpConnection::ReadMessage()
{
	//parse data
	while (true)
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
				continue;
			}
		}
		break;
	}

	//move data
	int unread_len = read_end - read_position;
	if (unread_len > 0)
	{
		memcpy(read_buff, read_position, unread_len);
	}
	read_position = read_buff;
	read_end = read_buff + unread_len;
}
void TcpConnection::OnRead()
{
	//revc data
	struct evbuffer *input = bufferevent_get_input(m_BufferEvent);
	char* start = read_end;
	char* end = read_buff + read_buff_len;
	int data_len = 0;
	while ((data_len = evbuffer_get_length(input)) && (end - start) > data_len)
	{
		start += evbuffer_remove(input, start, end - start);
		read_end = start;
	}
}
void TcpConnection::OnWrite()
{
	
}
void TcpConnection::OnClose()
{
	Disconnect();
}
void TcpConnection::OnStreamError(int error)
{
	Disconnect();
}
void TcpConnection::OnError(short error)
{
	if (error & BEV_EVENT_ERROR) {
		/* check errno to see what error occurred */
		/* ... */
		perror("BEV_EVENT_ERROR");
		
	}
	else if (error & BEV_EVENT_TIMEOUT) {
		/* must be a timeout event handle, handle it */
		/* ... */
		perror("BEV_EVENT_TIMEOUT");
	}
	OnClose();
	
}
void TcpConnection::ResetStream()
{
	
	SetReadBuffer(read_buffer, 0, STREAM_BUFF_SIZE);
	SetWriteBuffer(write_buffer, 0, STREAM_BUFF_SIZE);
}
void TcpConnection::FreeBufferEvent()
{
	if (m_BufferEvent)
	{
		bufferevent_free(m_BufferEvent);
		m_BufferEvent = nullptr;
	}

}
void TcpConnection::Update()
{
	if (m_State == S_Connected)
	{
		ReadMessage();
		WriteMessage();
	}

}
void TcpConnection::Disconnect()
{
	if (m_Socket != INVALID_SOCKET)
	{
		printf("client close fd:%d\n", m_Socket);
		FreeBufferEvent();
		evutil_closesocket(m_Socket);
		m_State = S_Disconnected;
		OnDisconnect();
	}
	
}
void TcpConnection::SetSocketEvent(SOCKET socket, sockaddr_in addr)
{
	ResetStream();
	FreeBufferEvent();
	m_Socket = socket;
	m_Addr = addr;
	m_BufferEvent = Event::AddBuffer(m_Socket,EV_READ|EV_WRITE,this);
	m_State = S_Connected;
	OnConnected();
}
bool TcpConnection::Initialize()
{
	ResetStream();
	return true;
}
void TcpConnection::OnConnected()
{

}
void TcpConnection::OnDisconnect()
{

}
void TcpConnection::OnMessage()
{
}
TcpConnection* TcpConnection::Create()
{
	TcpConnection* tcp = new (std::nothrow) TcpConnection();
	if (tcp&&tcp->Initialize())
	{
		return tcp;
	}
	delete tcp;
	tcp = nullptr;
	return nullptr;
}