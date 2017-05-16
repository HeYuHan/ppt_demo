#include <stdio.h>
#include<iostream>
#include "test_server.h"
using namespace std;
// void write_cb(struct bufferevent *bev, void *ctx)
// {

// }
// void error_cb(struct bufferevent *bev, short error, void *ctx)
// {
// 	if (error & BEV_EVENT_EOF) {
// 		/* connection has been closed, do any clean up here */
// 		/* ... */
// 	}
// 	else if (error & BEV_EVENT_ERROR) {
// 		/* check errno to see what error occurred */
// 		/* ... */
// 	}
// 	else if (error & BEV_EVENT_TIMEOUT) {
// 		/* must be a timeout event handle, handle it */
// 		/* ... */
// 	}
// 	bufferevent_free(bev);
// }
// void read_cb(struct bufferevent *bev, void *ctx)
// {
// 	struct evbuffer *input, *output;
// 	input = bufferevent_get_input(bev);
// 	output = bufferevent_get_output(bev);
// 	char buff[1024] = { 0 };
// 	int n = 0;
// 	while (evbuffer_get_length(input))
// 	{
// 		n += evbuffer_remove(input, &buff[n], 1024 - n);
// 	}
// 	printf(buff);
// 	char buff2[1024] = { 0 };
// 	sprintf(buff2, "server:%s", buff);
// 	evbuffer_add(output, buff2, strlen(buff2));
// }
// void do_accept(evutil_socket_t listener, short event, void* arg)
// {
// 	struct event_base *base = (struct event_base*)arg;
// 	struct sockaddr_in ss;
// 	socklen_t slen = sizeof(ss);
// 	int fd = accept(listener, (struct sockaddr*)&ss, &slen);
// 	if (fd < 0)
// 	{
// 		perror("do_accept error");
// 	}
// 	else if (fd > FD_SETSIZE)
// 	{
// 		evutil_closesocket(fd);
// 		char msg[128] = { 0 };
// 		sprintf(msg, "fd size error:%d", fd);
// 		perror(msg);
// 	}
// 	else
// 	{
// 		cout << "client connected:" << endl;
// 		struct bufferevent *bev;
// 		evutil_make_socket_nonblocking(fd);
// 		bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
// 		bufferevent_setcb(bev, read_cb, write_cb, error_cb, NULL);
// 		bufferevent_enable(bev, EV_READ | EV_WRITE);
// 	}
// }
int main(int argc, char** argv)
{
	printf("server start\n");
	bool ret = gTestServer.Initialize();
	return gTestServer.Run();
}
