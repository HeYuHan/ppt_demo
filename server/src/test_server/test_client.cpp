#include "test_server.h"
void TestClient::OnDisconnect()
{

}
void TestClient::OnMessage()
{
	char msg[128] = { 0 };
	ReadString(msg, 128);
	printf("client msg:%s\n", msg);
	gTestServer.BroadClientMessage(msg, strlen(msg));
}