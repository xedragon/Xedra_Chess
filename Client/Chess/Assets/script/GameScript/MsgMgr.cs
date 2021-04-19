using ProtoBuf;
using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Linq;
using System.Collections.Generic;
using MsgPB;
using UnityEngine;

public class MsgMgr : IObservable<IExtensible>
{
    private bool _bInit = false;
    private Socket _socket;//
    private List<byte> m_RecvBufflist = new List<byte>();//消息缓冲

    //void Start()
    //{
    //    Init();
    //}

    //void Update()
    //{
    //    RecvMsg();
    //}

    public void Init()
    {
        if (!_bInit)
        {
            _socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            _socket.Connect(new IPEndPoint(IPAddress.Parse("127.0.0.1"), 235));

            _socket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ReceiveTimeout, 100);
            _bInit = true;
        }
    }

    public void update()
    {
        RecvMsg();
    }

    public void RecvMsg()
    {
        if (null == _socket) return;

        byte[] m_RecvBuff = new byte[255];
        try
        {
            int ReceivedLen = _socket.Receive(m_RecvBuff);
            //Debug.Log("ReceivedLen: " + ReceivedLen);
            for (int i = 0; i < ReceivedLen; i++)
            {
                m_RecvBufflist.Add(m_RecvBuff[i]);
            }
        }
        catch (SocketException e)
        {
            if (e.ErrorCode == 10060)
            {

            }
        }

        while (m_RecvBufflist.Count >= 4)
        {
            var Bytes = m_RecvBufflist.ToArray();
            //截取消息包
            var size = BitConverter.ToUInt16(Bytes, 0);
            var type = BitConverter.ToUInt16(Bytes, 2);
            if (Bytes.Length >= 4 + size)
            {
                byte[] temp = Bytes.Skip(4).Take(size).ToArray();
                GenProtoMsgFromStream(temp, type, size);

                m_RecvBufflist.RemoveRange(0, 4 + size);
            }
            else
            {
                break;
            }
        }
    }

    public void SendMsg(IExtensible msg)
    {
        MemoryStream stream = new MemoryStream();
        Serializer.Serialize(stream, msg);

        byte[] bytes = stream.ToArray();
        SendMsg(bytes, (ushort)bytes.Length, GetMsgId(msg));
    }

    public void SendMsg(byte[] msg, ushort size, ushort type)
    {
        MemoryStream stream = new MemoryStream();
        stream.Write(BitConverter.GetBytes(size), 0, 2);
        stream.Write(BitConverter.GetBytes(type), 0, 2);
        stream.Write(msg, 0, size);

        int SendLen = _socket.Send(stream.ToArray());
    }

    //单例模式
    private static MsgMgr g_MsgMgr = null;
    public static MsgMgr getInstance()
    {
        if (g_MsgMgr == null)
        {
            g_MsgMgr = new MsgMgr();
            g_MsgMgr.Init();
        }
        return g_MsgMgr;
    }

    void GenProtoMsgFromStream(byte[] bytes, ushort msgType, ushort msgSize)
    {
        Debug.Log("MsgLen" + msgSize);
        MemoryStream stream = new MemoryStream();
        stream.Write(bytes, 0, msgSize);
        stream.Position = 0;

        IExtensible msg = null;
        switch (msgType)
        {
            case (ushort)MsgType.Connect_S2C:
                {
                    msg = Serializer.Deserialize<Msg_Connect_S2C>(stream);
                }
                break;

            case (ushort)MsgType.LOGIN_S2C:
                {
                    msg = Serializer.Deserialize<Msg_Login_S2C>(stream);
                }
                break;
                ///Gobang
            case (ushort)MsgType.Gobang_Start_S2C:
                {
                    msg = Serializer.Deserialize<Msg_Gobang_Start_S2C>(stream);
                }
                break;

            case (ushort)MsgType.Gobang_Action_C2S:
                {
                    msg = Serializer.Deserialize<Msg_Gobang_Action_C2S>(stream);
                }
                break;

            case (ushort)MsgType.Gobang_Over_S2C:
                {
                    msg = Serializer.Deserialize<Msg_Gobang_Over_S2C>(stream);
                }
                break;
            case (ushort)MsgType.Gobang_Giveup_S2C:
                {
                    msg = Serializer.Deserialize<Msg_Gobang_Giveup_S2C>(stream);
                }
                break;
            case (ushort)MsgType.Gobang_Regret_S2C:
                {
                    msg = Serializer.Deserialize<Msg_Gobang_Regret_S2C>(stream);
                }
                break;
            case (ushort)MsgType.Gobang_Pause_S2C:
                {
                    msg = Serializer.Deserialize<Msg_Gobang_Pause_S2C>(stream);
                }
                break;
                ///Chess
            case (ushort)MsgType.Chess_Start_S2C:
                {
                    msg = Serializer.Deserialize<Msg_Chess_Start_S2C>(stream);
                }
                break;

            case (ushort)MsgType.Chess_Action_S2C:
                {
                    msg = Serializer.Deserialize<Msg_Chess_Action_S2C>(stream);
                }
                break;

            case (ushort)MsgType.Chess_Over_S2C:
                {
                    msg = Serializer.Deserialize<Msg_Chess_Over_S2C>(stream);
                }
                break;
            case (ushort)MsgType.Chess_Giveup_S2C:
                {
                    msg = Serializer.Deserialize<Msg_Chess_Giveup_S2C>(stream);
                }
                break;
            case (ushort)MsgType.Chess_Regret_S2C:
                {
                    msg = Serializer.Deserialize<Msg_Chess_Regret_S2C>(stream);
                }
                break;
            case (ushort)MsgType.Chess_Pause_S2C:
                {
                    msg = Serializer.Deserialize<Msg_Chess_Pause_S2C>(stream);
                }
                break;
        }
        if (msg != null)
            NotifyMsg(msgType, msg);
    }

    public static ushort GetMsgId(IExtensible msg)
    {
        var type = msg.GetType();
        if (type.Equals(typeof(Msg_Login_C2S))) return 0;
        if (type.Equals(typeof(Msg_Login_S2C))) return 1;
        if (type.Equals(typeof(Msg_Connect_S2C))) return 2;
        if (type.Equals(typeof(Msg_Login_C2S))) return 3;

        if (type.Equals(typeof(Msg_Gobang_Match_C2S))) return 101;
        if (type.Equals(typeof(Msg_Gobang_Start_S2C))) return 102;
        if (type.Equals(typeof(Msg_Gobang_Action_C2S))) return 103;
        if (type.Equals(typeof(Msg_Gobang_Action_S2C))) return 104;
        if (type.Equals(typeof(Msg_Gobang_Over_S2C))) return 105;
        if (type.Equals(typeof(Msg_Gobang_Giveup_C2S))) return 106;
        if (type.Equals(typeof(Msg_Gobang_Giveup_S2C))) return 107;
        if (type.Equals(typeof(Msg_Gobang_Regret_C2S))) return 108;
        if (type.Equals(typeof(Msg_Gobang_Regret_S2C))) return 109;
        if (type.Equals(typeof(Msg_Gobang_Pause_C2S))) return 110;
        if (type.Equals(typeof(Msg_Gobang_Pause_S2C))) return 111;

        if (type.Equals(typeof(Msg_Chess_Match_C2S))) return 201;
        if (type.Equals(typeof(Msg_Chess_Start_S2C))) return 202;
        if (type.Equals(typeof(Msg_Chess_Action_C2S))) return 203;
        if (type.Equals(typeof(Msg_Chess_Action_S2C))) return 204;
        if (type.Equals(typeof(Msg_Chess_Over_S2C))) return 205;
        if (type.Equals(typeof(Msg_Chess_Giveup_C2S))) return 206;
        if (type.Equals(typeof(Msg_Chess_Giveup_S2C))) return 207;
        if (type.Equals(typeof(Msg_Chess_Regret_C2S))) return 208;
        if (type.Equals(typeof(Msg_Chess_Regret_S2C))) return 209;
        if (type.Equals(typeof(Msg_Chess_Pause_C2S))) return 210;
        if (type.Equals(typeof(Msg_Chess_Pause_S2C))) return 211;

        return 9999;
    }

    /// <summary>
    /// 观察者模式
    /// </summary>
    private List<IObserver<IExtensible>> m_Observers = new List<IObserver<IExtensible>>();
    public IDisposable Subscribe(IObserver<IExtensible> observer)
    {
        if (!m_Observers.Contains(observer))
        {
            m_Observers.Add(observer);
        }
        return new Unsubscriber<IExtensible>(m_Observers, observer);
    }

    void NotifyMsg(ushort msgid, IExtensible msg)
    {
        foreach (var observer in m_Observers)
        {
            if (msg == null)
            {
                observer.OnError(new Exception());
            }
            else
            {
                observer.OnNext(msg);
            }
        }
    }
}

public class Unsubscriber<T> : IDisposable
{
    private List<IObserver<T>> _observers;
    private IObserver<T> _observer;

    public Unsubscriber(List<IObserver<T>> observers, IObserver<T> observer)
    {
        this._observers = observers;
        this._observer = observer;
    }

    public void Dispose()
    {
        if (_observer != null && _observers.Contains(_observer))
            _observers.Remove(_observer);
    }
}


