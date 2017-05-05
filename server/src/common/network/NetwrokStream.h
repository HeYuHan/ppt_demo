#pragma once
#ifndef __NETWORK_STREAM_H__
#define __NETWORK_STREAM_H__
#include "../common.h"
typedef enum
{
	READERROR=0,WRITEERROR=1
}NETERR;
class NetworkStream
{

public:
	NetworkStream();
	~NetworkStream();
private:
	char* send_buff;
	char* read_buff;
	char* send_position;
	char* send_end;
	char* read_position;
	char* read_end;
	int send_buff_len;
	int read_buff_len;
public:
	const char* GetReadPosition() { return read_position; }
	const char* GetReadEnd() { return read_end; }
	const char* GetSendPosition() { return send_position; }
	const char* GetSendEnd() { return send_end; }
	void SetReadBuffer(char* buffer, int data_size, int buffer_len);
	void SetSendBuffer(char* buffer, int data_size, int buffer_len);
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

};
#endif