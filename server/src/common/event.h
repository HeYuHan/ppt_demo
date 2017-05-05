#pragma once
#ifndef __EVENT_H__
#define __EVENT_H__
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>
class Event
{
public:
	Event();
	~Event();

private:
public:
	static bool Init();

};


#endif
