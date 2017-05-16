#pragma once
#ifndef __TCP_CONN_H__
#define __TCP_CONN_H__
#include "../event_ext.h"
#include "../define.h"
#include "NetworkStream.h"
#define STREAM_BUFF_SIZE 1024
enum TcpState
{
	S_Idle=0,S_Connected,S_Disconnected
};

class TcpConnection:public ISocketEvent,public NetworkStream
{
public:
	TcpConnection();
	virtual ~TcpConnection();

private:
	char read_buffer[STREAM_BUFF_SIZE];
	char write_buffer[STREAM_BUFF_SIZE];
	TcpState m_State;
public:
	BufferEvent* m_BufferEvent;
	SOCKET m_Socket;
	sockaddr_in m_Addr;
private:
	void ReadMessage();
	void WriteMessage();
	void OnRead();
	void OnWrite();
	void OnClose();
	void OnError(short e);
	void Disconnect();
protected:
	virtual void OnMessage();
	virtual void OnConnected();
	virtual void OnDisconnect();
	virtual void OnStreamError(int error);
	
public: 
	const bool IsConnected() { return m_State == S_Connected; };
	void SetSocketEvent(SOCKET socket, sockaddr_in addr);
	bool Initialize();
	void FreeBufferEvent();
	void ResetStream();
	void Update();
	static TcpConnection* Create();
};



#endif