#include "test_server.h"
using namespace std;
TestServer gTestServer;
void TestServerListener::OnClientConnected(int socket, sockaddr_in addr)
{
	gTestServer.OnClientConnected(socket, addr);
}
TestServer::TestServer()
{

}
TestServer::~TestServer()
{

}
bool TestServer::Initialize()
{
	if (!BaseServer::Initialize())return false;
	if (!client_pool.Initialize(2048))return false;
	listenner.addr.sin_family = AF_INET;
	listenner.addr.sin_addr.s_addr = 0;
	listenner.addr.sin_port = htons(9595);
	if (!listenner.Initialize())return false;
	return true;
}
void TestServer::OnClientConnected(int socket, sockaddr_in addr)
{
	TestClient *client = client_pool.Allocate();
	client->SetSocketEvent(socket, addr);
	online_clients.insert(TestClientPair(client->uid,client));
	printf("current count:%d\n", client_pool.Count());
}
void TestServer::Update()
{
	auto begin = online_clients.begin();
	auto end = online_clients.end();
	while (begin!=end)
	{
		if (begin->second->IsConnected())
		{
			begin->second->Update();
			begin++;
		}
		else
		{
			client_pool.Free(begin->first);
			begin = online_clients.erase(begin);
		}
	}
}
void TestServer::BroadClientMessage(char* msg, int size)
{
	auto begin = online_clients.begin();
	auto end = online_clients.end();
	while (begin != end)
	{
		auto client = begin->second;
		client->BeginWrite();
		client->WriteData(msg, size);
		client->EndWrite();
		begin++;
	}
}
