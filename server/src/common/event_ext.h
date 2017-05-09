#pragma once
#ifndef __EVENT_H__
#define __EVENT_H__
#include <event.h>
#include "define.h"

typedef bufferevent BufferEvent;
typedef event TimerEvent, SocketEvent;
class NetworkStream;
struct ISocket
{
	virtual void OnClose() {};
	virtual void OnError(short e) {};
};
struct IServerSocket:public ISocket
{
	virtual void OnAccept(SOCKET client) {};
};
struct IClientSocket:public ISocket
{
	virtual void OnRead() {};
	virtual void OnWrite() {};
	virtual NetworkStream* GetStream() { return nullptr; };
};
class Event
{
private:
	Event();
	~Event();
private:
	static void AcceptCallBack(evutil_socket_t listener, short event, void* arg);
	static void ReadCallBack(struct bufferevent *bev, void *arg);
	static void ErrorCallBack(struct bufferevent *bev, short error, void *arg);
	static void WriteCallBack(struct bufferevent *bev, void *arg);
	
public:
	static bool Initialize();
	static int Dispatch();
	static void Terminate();
	static TimerEvent* AddTimer(event_callback_fn cb,void *arg, long sec, long mic = 0);
	static int AddTimer(TimerEvent* e, long sec, long mic=0);
	static SocketEvent* AccpetSocket(SOCKET listener, IServerSocket *handle);
	static BufferEvent* ListenSocket(SOCKET socket, IClientSocket *handle);
	static int RemoveEvent(struct event* e);
	static int RemoveBufferEvent(BufferEvent* e);
};


#endif
