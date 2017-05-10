#include "event_ext.h"
#include "network/NetworkStream.h"
Event::Event()
{
	
}

Event::~Event()
{
}
struct event_base *base;
bool Event::Initialize()
{
#ifdef WIN32
	WSADATA wsaData;
	WORD version = MAKEWORD(2, 0);
	int ret = WSAStartup(version, &wsaData);
	if (ret != 0)return false;
#endif
	base = event_base_new();
	return true;
}
int Event::Dispatch()
{
	return event_base_dispatch(base);
}
void Event::Terminate()
{
	event_base_free(base);
	base = nullptr;
}
int Event::AddTimer(event_callback_fn cb, void *arg, long sec, long mic /* = 0 */)
{
	
	struct event timer_ev;
	evtimer_set(&timer_ev, cb, arg);
	timeval tv;
	tv.tv_sec = sec;
	tv.tv_usec = mic;
	return evtimer_add(&timer_ev, &tv);
}

void Event::OnSocketEvent(evutil_socket_t listener, short event, void* arg)
{
	ISocketEvent* handle = static_cast<ISocketEvent*>(arg);
	if (handle)
	{
		if (event&&EV_READ)handle->OnRead();
		if (event&&EV_WRITE)handle->OnWrite();
	}
}
void Event::OnBufferEvent(struct bufferevent *bev, short event,void *arg)
{
	ISocketEvent* handle = static_cast<ISocketEvent*>(arg);
	if (handle)
	{
		if (event & BEV_EVENT_EOF) {
			handle->OnClose();
		}
		else if (event & BEV_EVENT_ERROR) {
			handle->OnError(BEV_EVENT_ERROR);
		}
		else if (event & BEV_EVENT_TIMEOUT) {
			handle->OnError(BEV_EVENT_TIMEOUT);
		}
	}
}
void Event::OnBufferRead(struct bufferevent *bev, void *arg)
{
	ISocketEvent* handle = static_cast<ISocketEvent*>(arg);
	if (handle)
	{
		handle->OnRead();
	}
}
void Event::OnBufferWrite(struct bufferevent *bev, void *arg)
{
	ISocketEvent* handle = static_cast<ISocketEvent*>(arg);
	if (handle)
	{
		handle->OnWrite();
	}
}
struct event* Event::AddSocket(SOCKET listener, short event, ISocketEvent *handle)
{
	struct event *listen_ev = event_new(base, listener, EV_READ | EV_PERSIST, OnSocketEvent, handle);
	if (event_add(listen_ev, nullptr) == 0)
	{
		return listen_ev;
	}
	
	return nullptr;
}
struct bufferevent* Event::AddBuffer(SOCKET socket, short event, ISocketEvent *handle)
{
	struct bufferevent *bev;
	evutil_make_socket_nonblocking(socket);
	bev = bufferevent_socket_new(base, socket, BEV_OPT_CLOSE_ON_FREE);
	bufferevent_setcb(bev, OnBufferRead, OnBufferWrite, OnBufferEvent, handle);
	if (bufferevent_enable(bev, event) == 0)
	{
		return bev;
	}
	bufferevent_free(bev);
	return nullptr;
}
int Event::RemoveSocket(struct event* e)
{
	int i = event_del(e);
	event_free(e);
	return i;
}
int Event::RemoveBuffer(BufferEvent* e)
{
	int i = bufferevent_disable(e, EV_READ | EV_WRITE);
	bufferevent_free(e);
	return i;
}