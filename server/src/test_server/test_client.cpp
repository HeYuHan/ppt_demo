#include "test_server.h"
void TestClient::OnDisconnect()
{

}
void TestClient::OnMessage()
{
	char msg[128] = { 0 };
	ReadString(msg, 128);
	printf("client msg:%s\n", msg);
	BeginWrite();
	WriteString("hello client");
	EndWrite();
	//gTestServer.BroadClientMessage(msg, strlen(msg));
}