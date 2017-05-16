#pragma once
#include <vector>
#include "objectpool.h"
#include "network/TcpListener.h"
#include <map>

class BaseServer
{
public:
	BaseServer();
	~BaseServer();
protected:
	void OnClose();
	void OnError(short e);
public:
	virtual int Run();
	virtual bool Initialize()=0;
	virtual void Update()=0;
};

