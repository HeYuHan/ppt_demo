#pragma once
#ifndef __TEST_SERVER_H__
#include "../common/common.h"
#include "test_client.h"
#include <unordered_map>
typedef std::unordered_map<uint, TestClient*>::value_type TestClientPair;
class TestServerListener :public TcpListener
{
protected:
	virtual void OnClientConnected(int socket, sockaddr_in addr);
};
class TestServer:public BaseServer
{
public:
	TestServer();
	~TestServer();

public:
	virtual bool Initialize();
	virtual void Update();
	void OnClientConnected(int socket, sockaddr_in addr);
	void BroadClientMessage(char* msg, int size);
protected:
	TestServerListener listenner;
	ObjectPool<TestClient> client_pool;
	std::unordered_map<uint, TestClient*> online_clients;
	
};
extern TestServer gTestServer;
#define __TEST_SERVER_H__
#endif
