#include "NetwrokStream.h"
NetworkStream::NetworkStream():
	send_buff(nullptr)
	,read_buff(nullptr)
	,send_position(nullptr)
	,send_end(nullptr)
	,read_position(nullptr)
	,read_end(nullptr)
	,send_buff_len(0)
	,read_buff_len(0)
{
}

NetworkStream::~NetworkStream()
{
}
void NetworkStream::SetReadBuffer(char* buffer, int data_size,int buffer_len)
{
	read_buff = buffer;
	read_position = buffer;
	read_end = &buffer[buffer_len];
	read_buff_len = buffer_len;
}
void NetworkStream::SetSendBuffer(char* buffer, int data_size,int buffer_len)
{
	send_buff = buffer;
	send_position = buffer;
	send_end = &buffer[buffer_len];
	send_buff_len = buffer_len;
}

//////////////////////////////////////////////////////////////
//write data
void NetworkStream::WirteByte(byte data)
{
	WriteData(&data, sizeof(byte));
}
void NetworkStream::WirteByte(char data) 
{
	WriteData(&data, sizeof(char));
}
void NetworkStream::WriteShort(short data) 
{
	WriteData(&data, sizeof(short));
}
void NetworkStream::WriteUShort(ushort data) 
{
	WriteData(&data, sizeof(ushort));
}
void NetworkStream::WriteInt(int data) 
{
	WriteData(&data, sizeof(int));
}
void NetworkStream::WriteUInt(uint data)
{
	WriteData(&data, sizeof(uint));
}
void NetworkStream::WriteFloat(float data) 
{
	WriteData(&data, sizeof(float));
}
void NetworkStream::WriteLong(long data) 
{
	WriteData(&data, sizeof(long));
}
void NetworkStream::WriteULong(ulong data) 
{
	WriteData(&data, sizeof(ulong));
}
void NetworkStream::WriteString(const char* str) 
{
	int len = strlen(str);
	WriteInt(len);
	WriteData(str, len);
}
void NetworkStream::WriteData(const void* data, int count) 
{
	if (send_buff == nullptr || count < 0 || send_end + count > send_buff + send_buff_len)
	{
		throw WRITEERROR;
	}
	if (count > 0)
	{
		memcpy(send_end, data, count);
	}

}
//////////////////////////////////////////////////////////////
//read data
void NetworkStream::ReadByte(byte &data)
{
	ReadData(&data, sizeof(byte));
}
void NetworkStream::ReadByte(char &data)
{
	ReadData(&data, sizeof(char));
}
void NetworkStream::ReadShort(short &data)
{
	ReadData(&data, sizeof(short));
}
void NetworkStream::ReadUShort(ushort &data)
{
	ReadData(&data, sizeof(ushort));
}
void NetworkStream::ReadInt(int &data)
{
	ReadData(&data, sizeof(int));
}
void NetworkStream::ReadUInt(uint &data)
{
	ReadData(&data, sizeof(uint));
}
void NetworkStream::ReadFloat(float &data)
{
	ReadData(&data, sizeof(float));
}
void NetworkStream::ReadLong(long &data)
{
	ReadData(&data, sizeof(long));
}
void NetworkStream::ReadULong(ulong &data)
{
	ReadData(&data, sizeof(ulong));
}
int NetworkStream::ReadString(char* str,int size)
{
	int len = 0;
	ReadInt(len);
	if (len < 0||size<len)
	{
		throw READERROR;
		
	}
	str[len] = 0;
	ReadData(str, len);
	return len;
}
void NetworkStream::ReadData(void* data, int count)
{
	if (read_buff == nullptr || count < 0 || read_end - read_position>count)
	{
		throw READERROR;
	}
	if (count > 0)
	{
		memcpy(data, read_position, count);
	}
}