#include <stdio.h>
#include <iostream>
#include "common/common.h"
using namespace std;
int main(int argc, char** argv)
{
	Event::Init();
	struct event_base *base = event_base_new();
	sockaddr_in listen_addr;
	int listen_fd;
	int reuseadd_on = 1;
	struct event listen_ev;

	return 0;
}