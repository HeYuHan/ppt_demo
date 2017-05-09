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
TimerEvent* Event::AddTimer(event_callback_fn cb, void *arg, long sec, long mic /* = 0 */)
{
	
	struct event *timer_ev = evtimer_new(base, cb, arg);
	AddTimer(timer_ev, sec,mic);
	return timer_ev;
}
int Event::AddTimer(TimerEvent* e, long sec, long mic/* =0 */)
{
	timeval tv;
	tv.tv_sec = sec;
	tv.tv_usec = mic;
	return evtimer_add(e, &tv);
}
void Event::AcceptCallBack(evutil_socket_t listener, short event, void* arg)
{
	
	struct event_base *base = (struct event_base*)arg;
	struct sockaddr_in ss;
	socklen_t slen = sizeof(ss);
	int fd = accept(listener, (struct sockaddr*)&ss, &slen);
	char msg[128] = { 0 };
	sprintf(msg, "fd size error:%d", fd);
	if (fd < 0)
	{
		perror("do_accept error");
	}
	else if (fd > FD_SETSIZE)
	{
		evutil_closesocket(fd);
		perror(msg);
	}
	else
	{
		IServerSocket* handle = static_cast<IServerSocket*>(arg);
		if (handle) 
		{
			handle->OnAccept(fd);
		}
		else
		{
			evutil_closesocket(fd);
		}
	}
}
void Event::ReadCallBack(struct bufferevent *bev, void *arg)
{
	struct evbuffer *input;
	input = bufferevent_get_input(bev);
	IClientSocket* handle = static_cast<IClientSocket*>(arg);
	if (handle)
	{
		NetworkStream* stream = handle->GetStream();
		char* start = stream->read_end;
		char* end = stream->read_buff+stream->read_buff_len;
		int data_len = 0;
		while ((data_len = evbuffer_get_length(input))&&(end-start)>data_len)
		{
			start += evbuffer_remove(input, start, end - start);
			stream->read_end = start;
		}
	}
	
}
void Event::ErrorCallBack(struct bufferevent *bev, short error, void *arg)
{
	
	
	ISocket* handle = static_cast<ISocket*>(arg);
	if (handle)
	{
		handle->OnError(error);
	}
	
}
void Event::WriteCallBack(struct bufferevent *bev, void *arg)
{

}
struct event* Event::AccpetSocket(SOCKET listener,IServerSocket *handle)
{
	struct event *listen_ev = event_new(base, listener, EV_READ | EV_PERSIST, AcceptCallBack, handle);
	if (event_add(listen_ev, nullptr) == 0)
	{
		return listen_ev;
	}
	free(listen_ev);
	return nullptr;
}
struct bufferevent* Event::ListenSocket(SOCKET socket,IClientSocket *handle)
{
	struct bufferevent *bev;
	evutil_make_socket_nonblocking(socket);
	bev = bufferevent_socket_new(base, socket, BEV_OPT_CLOSE_ON_FREE);
	bufferevent_setcb(bev, ReadCallBack, WriteCallBack, ErrorCallBack, handle);
	if (bufferevent_enable(bev, EV_READ | EV_WRITE) == 0)
	{
		return bev;
	}
	free(bev);
	return nullptr;
}
int Event::RemoveEvent(struct event* e)
{
	int i = event_del(e);
	event_free(e);
	return i;
}
int Event::RemoveBufferEvent(BufferEvent* e)
{
	int i = bufferevent_disable(e, EV_READ | EV_WRITE);
	bufferevent_free(e);
	return i;
}