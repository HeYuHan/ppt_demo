#pragma once
#ifndef __EVENT_H__
#define __EVENT_H__
#include <event.h>
#include "define.h"

typedef bufferevent BufferEvent;
typedef event TimerEvent, SocketEvent;
class NetworkStream;
struct ISocketEvent
{
	virtual void OnClose() = 0;
	virtual void OnRead() = 0;
	virtual void OnWrite() = 0;
	virtual void OnError(short e) = 0;
};
class Event
{
private:
	Event();
	~Event();
private:
	static void OnSocketEvent(evutil_socket_t listener, short event, void* arg);
	static void OnBufferEvent(struct bufferevent *bev, short event, void *arg);
	static void OnBufferRead(struct bufferevent *bev, void *arg);
	static void OnBufferWrite(struct bufferevent *bev, void *arg);
	
public:
	static bool Initialize();
	static int Dispatch();
	static void Terminate();
	static int AddTimer(struct event &timer_ev,event_callback_fn cb,void *arg,long mic);
	static SocketEvent* AddSocket(SOCKET listener, short event,ISocketEvent *handle);
	static BufferEvent* AddBuffer(SOCKET socket, short event, ISocketEvent *handle);
	static int RemoveSocket(struct event* e);
	static int RemoveBuffer(BufferEvent* e);
};


#endif
