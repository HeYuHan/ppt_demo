#pragma once
#ifndef __TCP_CONN_H__
#define __TCP_CONN_H__
#include "../event_ext.h"
#include "../define.h"
#include "NetworkStream.h"
#define STREAM_BUFF_SIZE 1024
enum TcpState
{
	S_Idle=0,S_Connected,S_Destory
};

class TcpConnection:public ISocketEvent,public NetworkStream
{
public:
	TcpConnection();
	~TcpConnection();

private:
	char read_buffer[STREAM_BUFF_SIZE];
	char write_buffer[STREAM_BUFF_SIZE];
public:
	TcpState m_State;
	BufferEvent* m_BufferEvent;
	SOCKET m_Socket;
	sockaddr_in m_Addr;
	uint uid;
private:
	void ReadMessage();
	void WriteMessage();
public: 
	void OnMessage();
	void OnRead();
	void OnWrite();
	void OnClose();
	void OnError(short e);
	void OnConnected();
	void Disconnect();
	void Close();
	void SetSocketEvent(SOCKET socket, sockaddr_in addr);
	bool Initialize();
	void FreeBufferEvent();
	void Reset();
	void Update();
	static TcpConnection* Create();
};



#endif