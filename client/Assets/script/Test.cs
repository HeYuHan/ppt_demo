using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using ProtoBuf;
using tutorial;
using System.IO;
public class TestClient:TcpConnection
{

    public TestClient():base("127.0.0.1",9595)
    {

    }
    public override void OnMessage()
    {
        tutorial.AddressBook ab = ReadProtoBuf<tutorial.AddressBook>();
        UnityEngine.Debug.Log("on message......");

        AddressBook abook = new AddressBook();

        Person p = new Person();
        p.email = "asdfasdfsdaf";
        p.id = 1;
        p.name = "xxxxxx";

        Person.PhoneNumber n = new Person.PhoneNumber();
        n.number = "fffffff";
        n.type = Person.PhoneType.HOME;
        p.phone.Add(n);

        abook.person.Add(p);
        BeginWrite();
        WriteProtoBuf<AddressBook>(abook);
        EndWrite();
    }
}

public class Test : MonoBehaviour {
    TestClient t;
	// Use this for initialization
	void Start () {
        

        t = new TestClient();
        t.Connect();
        return;
	}
	
	// Update is called once per frame
	void Update () {
        if (t != null) t.Update();
	}
}
