using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using ProtoBuf;
using System.IO;
unsafe public class NetworkStream {

    protected byte[] write_buffer = null;
    protected byte[] read_buffer = null;
    protected int write_position = 0;
    protected int write_end = 0;
    protected int read_position = 0;
    protected int read_end = 0;
    protected int send_position = 0;
    protected int send_end = 0;

    public NetworkStream(int buff_size = 0)
    {
        if (buff_size > 0)
        {
            write_buffer = new byte[buff_size];
            read_buffer = new byte[buff_size];
        }
    }
    public void SetReadBuffer(byte[] buffer, int data_size)
    {
        read_buffer = buffer;
        read_position = 0;
        read_end = data_size;
    }
    public void SetWriteBuffer(byte[] buffer, int data_size)
    {
        write_buffer = buffer;
        write_position = 0;
        write_end = data_size;
        send_position = 0;
        send_end = 0;
    }
    public static void CopyArray(byte* src, byte* dst, int count)
    {
        if (null == src || null == dst || count<=0)
        {
            return;
        }
        if(count>=4)
        {
            for (int n = 0; n < count / 4; n++)
            {
                *((int*)dst) = *((int*)src);
                dst += 4;
                src += 4;
            }
        }
        for (int n = 0; n < count % 4; n++)
        {
            *dst = *src;
            dst++;
            src++;
        }
    }
    //////////////////////////////////////////////////////////////
    //read data
    public byte ReadByte()
    {
        byte reslut = 0;
        ReadData(&reslut, sizeof(byte));
        return reslut;
    }
    public short ReadShort()
    {
        short reslut = 0;
        ReadData(&reslut, sizeof(short));
        return reslut;
    }
    public int ReadInt()
    {
        int reslut = 0;
        ReadData(&reslut, sizeof(int));
        return reslut;
    }
    public float ReadFloat()
    {
        float reslut = 0;
        ReadData(&reslut, sizeof(float));
        return reslut;
    }
    public long ReadLong()
    {
        long reslut = 0;
        ReadData(&reslut, sizeof(long));
        return reslut;
    }

    public ushort ReadUShort()
    {
        ushort reslut = 0;
        ReadData(&reslut, sizeof(ushort));
        return reslut;
    }
    public uint ReadUInt()
    {
        uint reslut = 0;
        ReadData(&reslut, sizeof(uint));
        return reslut;
    }
    public ulong ReadULong()
    {
        ulong reslut = 0;
        ReadData(&reslut, sizeof(ulong));
        return reslut;
    }
    public string ReadString()
    {
        int len = ReadInt();
        if(len>0)
        {
            fixed(byte* data= &read_buffer[read_position])
            {
                read_position += len;
                return new string((char*)data,0,len/2);
            }
            
        }
        return string.Empty;
    }
    public T ReadProtoBuf<T>()where T: new()
    {
        int len = ReadInt();
        if (len > 0 && len <= (read_end - read_position))
        {
            using (MemoryStream ms = new MemoryStream(read_buffer, read_position, len, false))
            {
                T instance = Serializer.Deserialize<T>(ms);
                read_position += len;
                return instance;
            }
        }
        return default(T);
    }
    public void ReadData(byte[] data,int count)
    {
        fixed (byte* b_data = data)
        {
            ReadData(b_data, count);
        }
    }
    public void ReadData(void* data,int count)
    {
        if(read_buffer==null)
        {
            throw new Exception("read_buff==null");
        }
        if(read_position + count > read_end)
        {
            throw new Exception("read_position+count>read_end");
        }
        
        fixed (byte* pSrc = &read_buffer[read_position])
        {
            CopyArray(pSrc, (byte*)data, count);
        }
        read_position += count;
    }

    //////////////////////////////////////////////////////////////
    //write data
    public void BeginWrite()
    {
        write_position = write_end;
        write_end = write_position + 4;

    }
    public void EndWrite()
    {
        int totole_len = write_end - write_position;
        int int_len = 4;
        if (totole_len > int_len)
        {
            int data_len = totole_len - int_len;
            int write_end_backup = write_end;
            write_end = write_position;
            WriteInt(data_len);
            write_end = write_end_backup;
            int start = (send_position < write_position) ? send_position : write_position;
            int wait_send_len = write_end - start;
            fixed(byte* data_start= &write_buffer[start],origin = write_buffer)
            {
                CopyArray(data_start, origin, wait_send_len);
            }
            send_position = 0;
            send_end = wait_send_len;
            write_position = write_end = send_end;
        }
        else
        {
            write_end = write_position;
        }
    }
    public void WriteByte(byte data)
    {
        WriteData(&data, sizeof(byte));
    }
    public void WriteShort(short data)
    {
        WriteData(&data, sizeof(short));
    }
    public void WriteInt(int data)
    {
        WriteData(&data, sizeof(int));
    }
    public void WriteFloat(float data)
    {
        WriteData(&data, sizeof(float));
    }
    public void WriteLong(long data)
    {
        WriteData(&data, sizeof(long));
    }

    public void WriteUShort(ushort data)
    {
        WriteData(&data, sizeof(ushort));
    }
    public void WriteUInt(uint data)
    {
        WriteData(&data, sizeof(uint));
    }
    public void WriteULong(ulong data)
    {
        WriteData(&data, sizeof(ulong));
    }
    public void WriteString(string data)
    {
        if(data.Length>0)
        {
            WriteInt(data.Length*2);
            fixed(char* str=data)
            {
                WriteData((byte*)str, data.Length*2);
            }
            
        }
    }
    public void WriteProtoBuf<T>(T instance)
    {
        using (MemoryStream ms = new MemoryStream(write_buffer, write_end+4, write_buffer.Length - write_end-4, true))
        {
            Serializer.Serialize(ms, instance);
            int serialize = (int)ms.Position;
            WriteInt(serialize);
            write_end += serialize;
        }
            
    }
    public void WriteData(byte[] data,int count)
    {
        fixed(byte* b_data=data)
        {
            WriteData(b_data, count);
        }
       
    }
  
    void WriteData(void* data,int count)
    {
        if(write_buffer==null)
        {
            throw new System.Exception("send_buff==null");
        }
        if(write_end + count > write_buffer.Length)
        {
            throw new System.Exception("send_end+count>send_buff.Length");
        }
        if(count<=0)
        {
            throw new System.Exception("count<=0");
        }
        fixed (byte* pDst = &write_buffer[write_end])
        {
            CopyArray((byte*)data, pDst, count);
        }
        write_end += count;
    }
    
}
