#pragma once
#ifndef __NETWORK_STREAM_H__
#define __NETWORK_STREAM_H__
#include "../define.h"
#include <google/protobuf/message.h>
typedef enum
{
	READERROR=0,WRITEERROR=1
}STREAMERROR;
class NetworkStream
{

public:
	NetworkStream();
	~NetworkStream();
protected:
	char* write_buff;
	char* read_buff;
	char* write_buff_end;
	char* read_buff_end;
	char* write_position;
	char* write_end;
	char* read_position;
	char* read_end;
	char* send_position;
	char* send_end;
	int write_buff_len;
	int read_buff_len;
public:
	void SetReadBuffer(char* buffer, int data_size, int buffer_len);
	void SetWriteBuffer(char* buffer, int data_size, int buffer_len);
protected:
	virtual void OnStreamError(int error,const char* msg=nullptr)=0;
//////////////////////////////////////////////////////////////
//write data
public:
	void WirteByte(byte data);
	void WirteByte(char data);
	void WriteShort(short data);
	void WriteUShort(ushort data);
	void WriteInt(int data);
	void WriteUInt(uint data);
	void WriteFloat(float data);
	void WriteLong(long data);
	void WriteULong(ulong data);
	void WriteString(const char* str);
	void WriteData(const void* data, int count);
	void BeginWrite();
	void EndWrite();
	bool WriteProto(ProtoMessage &proto);
	//////////////////////////////////////////////////////////////
	//read data
public:
	void ReadByte(byte &data);
	void ReadByte(char &data);
	void ReadShort(short &data);
	void ReadUShort(ushort &data);
	void ReadInt(int &data);
	void ReadUInt(uint &data);
	void ReadFloat(float &data);
	void ReadLong(long &data);
	void ReadULong(ulong &data);
	int ReadString(char* str,int size);
	void ReadData(void* data, int count);
	bool ReadProto(ProtoMessage &proto);

};
#endif