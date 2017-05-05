﻿using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

unsafe public class NetworkStream {

    byte[] send_buff = null;
    byte[] read_buff = null;
    int send_position = 0;
    int send_end = 0;
    int read_position = 0;
    int read_end = 0;
    public int ReadPosition
    {
        get { return read_position; }
    }
    public int ReadEnd
    {
        get { return read_end; }
    }
    public int SendPosition
    {
        get { return send_position; }
    }
    public int SendEnd
    {
        get { return send_end; }
    }
    public NetworkStream(int buff_size = 0)
    {
        if (buff_size > 0)
        {
            send_buff = new byte[buff_size];
            read_buff = new byte[buff_size];
        }
    }
    public void SetReadBuffer(byte[] buffer, int data_size)
    {
        read_buff = buffer;
        read_position = 0;
        read_end = data_size;
    }
    public void SetSendBuffer(byte[] buffer, int data_size)
    {
        send_buff = buffer;
        send_position = 0;
        send_end = data_size;
    }
    static void CopyArray(byte* src, byte* dst, int count)
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
            fixed(byte* data= &read_buff[read_position])
            {
                read_position += len;
                return new string((char*)data,0,len/2);
            }
            
        }
        return string.Empty;
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
        if(read_buff==null)
        {
            throw new Exception("read_buff==null");
        }
        if(read_position + count > read_end)
        {
            throw new Exception("read_position+count>read_end");
        }
        
        fixed (byte* pSrc = &read_buff[read_position])
        {
            CopyArray(pSrc, (byte*)data, count);
        }
        read_position += count;
    }

    //////////////////////////////////////////////////////////////
    //write data
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
    public void WriteData(byte[] data,int count)
    {
        fixed(byte* b_data=data)
        {
            WriteData(b_data, count);
        }
       
    }
  
    void WriteData(void* data,int count)
    {
        if(send_buff==null)
        {
            throw new System.Exception("send_buff==null");
        }
        if(send_end + count > send_buff.Length)
        {
            throw new System.Exception("send_end+count>send_buff.Length");
        }
        if(count<=0)
        {
            throw new System.Exception("count<=0");
        }
        fixed (byte* pDst = &send_buff[send_end])
        {
            CopyArray((byte*)data, pDst, count);
        }
        send_end += count;
    }
    
}
