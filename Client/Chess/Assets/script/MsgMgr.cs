using ProtoBuf;
using protocols.Msg;
using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Linq;
using System.Collections.Generic;

public class MsgMgr : IObservable<IExtensible>
{
    private static MsgMgr g_MsgMgr = null;
    private Socket _socket;

    public static MsgMgr getInstance()
    {
        if (g_MsgMgr == null)
        {
            g_MsgMgr = new MsgMgr();
        }
        return g_MsgMgr;
    }

    void GenProtoMsgFromStream(byte[] bytes, ushort msgType, ushort msgSize)
    {
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
        }
        if (msg != null)
            NotifyMsg(msgType, msg);
    }

    private List<byte> m_RecvBufflist = new List<byte>();
    public void RecvMsg()
    {
        if (null == _socket) return;

        byte[] m_RecvBuff = new byte[255];
        int ReceivedLen = _socket.Receive(m_RecvBuff);
        Console.WriteLine("ReceivedLen: " + ReceivedLen);
        for (int i = 0; i < ReceivedLen; i++)
        {
            m_RecvBufflist.Add(m_RecvBuff[i]);
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

                //Array.Clear(Bytes, 0, 4 + size);
                //Array.Clear(m_RecvBuff, 0, 4 + size);
                m_RecvBufflist.RemoveRange(0, 4 + size);
            }
            else
            {
                break;
            }
        }
    }

    public ushort GetMsgId(IExtensible msg)
    {
        var type = msg.GetType();
        if (type.Equals(typeof(Msg_Login_C2S))) return 0;

        return 0;
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
        stream.Write(BitConverter.GetBytes(size),0,2);
        stream.Write(BitConverter.GetBytes(type),0,2);
        stream.Write(msg,0,size);

        int SendLen = _socket.Send(stream.ToArray());
    }

    public void Init()
    {
        _socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        _socket.Connect(new IPEndPoint(IPAddress.Parse("127.0.0.1"), 235));

        //Msg_Login_C2S msg = new Msg_Login_C2S();
        //msg.conMethod = 1;
        //msg.szName = "xedra";
        //msg.szPassWord = "wocao";
        //SendMsg(msg);
    }

    /// <summary>
    /// 使用观察者模式派发消息
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
