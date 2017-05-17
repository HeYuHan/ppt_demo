#include "NetworkStream.h"
#include <string>
NetworkStream::NetworkStream():
	write_buff(nullptr)
	,read_buff(nullptr)
	,write_position(nullptr)
	,write_end(nullptr)
	,read_buff_end(nullptr)
	,write_buff_end(nullptr)
	,read_position(nullptr)
	,read_end(nullptr)
	,send_position(nullptr)
	,send_end(nullptr)
	,write_buff_len(0)
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
	read_end = &buffer[data_size];
	read_buff_len = buffer_len;
	read_buff_end = &buffer[buffer_len - 1];
	memset(buffer, 0, read_end - read_position);
}
void NetworkStream::SetWriteBuffer(char* buffer, int data_size,int buffer_len)
{
	
	write_buff = buffer;
	write_position = buffer;
	write_end = &buffer[data_size];
	write_buff_len = buffer_len;
	send_position = nullptr;
	send_end = nullptr;
	write_buff_end = &buffer[buffer_len - 1];
	memset(buffer, 0, write_end - write_position);
}
//////////////////////////////////////////////////////////////
//write data
void NetworkStream::BeginWrite()
{
	write_position = write_end;
	write_end += 4;
}
void NetworkStream::EndWrite()
{
	int totole_len = write_end - write_position;
	int int_len = sizeof(int);
	if (totole_len > int_len)
	{
		int data_len = totole_len - int_len;
		char* write_end_backup = write_end;
		write_end = write_position;
		WriteInt(data_len);
		write_end = write_end_backup;
		char* start = send_position ? send_position : write_position;
		int wait_send_len = write_end - start;
		memmove(write_buff, start, wait_send_len);
		send_position = write_buff;
		send_end = send_position + wait_send_len;
		write_position = write_end = send_end;
	}
	else
	{
		write_end = write_position;
	}
}
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
	int empty_size = (write_buff + write_buff_len) - (write_end + count);
	if (write_buff == nullptr || count < 0 || empty_size <= 0)
	{
		OnStreamError(WRITEERROR);
		return;
	}
	if (count > 0)
	{
		memcpy(write_end, data, count);
		write_end += count;
	}

}
bool NetworkStream::WriteProto(ProtoMessage &proto)
{
	int size = proto.ByteSize();
	if (size > 0 && ((write_buff_end - write_position) - (size + sizeof(int)))>0)
	{
		WriteInt(size);
		proto.SerializeToArray(write_end, size);
		write_end += size;
		return true;
	}
	return false;
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
	if (read_buff == nullptr || count < 0 || read_end - read_position<count)
	{
		OnStreamError(READERROR);
		return;
	}
	if (count > 0)
	{
		memcpy(data, read_position, count);
		read_position += count;
	}
}
bool NetworkStream::ReadProto(ProtoMessage &proto)
{
	int size = 0;
	ReadInt(size);
	int unread = read_end - read_position;
	if (size > 0&& unread>=size)
	{
		proto.ParseFromArray(read_position, size);
		read_position += size;
		return true;
	}
	else
	{
		OnStreamError(READERROR);
	}
	return false;
}