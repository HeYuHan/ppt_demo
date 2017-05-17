#pragma once
#include "../common/common.h"
class TestClient :public TcpConnection
{
public:
	uint uid;
protected:
	virtual void OnDisconnect();
	virtual void OnMessage();
	virtual void OnConnected();
};