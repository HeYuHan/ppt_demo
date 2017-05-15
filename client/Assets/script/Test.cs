using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using ProtoBuf;
using tutorial;
using System.IO;

public class Test : MonoBehaviour {

	// Use this for initialization
	void Start () {
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
        

        byte[] data = new byte[1024];
        NetworkStream s = new NetworkStream();
        s.SetSendBuffer(data,0);
        s.WriteByte(4);
        s.WriteShort(232);
        s.WriteInt(1000);
        s.WriteFloat(100.12345f);
        s.WriteString("12345qwer哈哈哈123");
        s.WriteUInt(12345);
        s.WriteLong(long.MaxValue - 10);
        s.WriteProtoBuf(abook);
        
        Debug.Log("send length=" + s.SendEnd);
        NetworkStream s2 = new NetworkStream();
        s2.SetReadBuffer(data, s.SendEnd);
        Debug.Log(s2.ReadByte());
        Debug.Log(s2.ReadShort());
        Debug.Log(s2.ReadInt());
        Debug.Log(s2.ReadFloat());
        Debug.Log(s2.ReadString());
        Debug.Log(s2.ReadUInt());
        Debug.Log(s2.ReadLong());
        AddressBook ab2=s2.ReadProtoBuf<AddressBook>();
        return;
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
