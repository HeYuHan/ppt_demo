#include "test_server.h"
#include "addressbook.pb.h"
using namespace tutorial;
void TestClient::OnDisconnect()
{

}
void TestClient::OnMessage()
{
	AddressBook ab;
	ReadProto(ab);
	printf("client proto:%s\n", ab.SerializeAsString().c_str());
	//gTestServer.BroadClientMessage(msg, strlen(msg));
}
void TestClient::OnConnected()
{
	AddressBook ab;
	auto p = ab.add_person();
	p->set_name("ffffff");
	p->set_id(12345);
	p->set_email("12345qwer@qq.com");
	auto n = p->add_phone();
	n->set_type(Person_PhoneType::Person_PhoneType_HOME);
	n->set_number("123456789");
	BeginWrite();
	WriteProto(ab);
	EndWrite();
}