using System;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using ProtoBuf;
using protocols.Msg;

public class MsgMgr
{
    private static MsgMgr g_MsgMgr = null;

    ArraySegment<byte> m_ExistRecvBuff = new ArraySegment<byte>();
    private MemoryStream _MemoryStream = new MemoryStream();
    private Socket _socket;

    public static MsgMgr getInstance()
    {
        if (g_MsgMgr == null)
        {
            g_MsgMgr = new MsgMgr();
        }
        return g_MsgMgr;
    }
    void DisPatchMsg(IExtensible msg)
    {

    }

    void GenProtoMsgFromStream(MemoryStream stream, ushort msgType, ushort msgSize)
    {
        IExtensible msg;
        switch (msgType)
        {
            case 1:
                {
                    msg = Serializer.Deserialize<Msg_Login_C2S>(stream);
                    DisPatchMsg(msg);
                }
                break;

        }
        stream.SetLength(0);
        stream.Position = 0;
    }

    int ParseMsg(byte[] RecvBuff)
    {
        int offset = 0;
        int end = RecvBuff.Length;
        while (RecvBuff.Length > 4)
        {
            var msg_type = BitConverter.ToUInt16(RecvBuff, offset);
            var msg_size = BitConverter.ToUInt16(RecvBuff, offset + 2);
            if (RecvBuff.Length >= offset + msg_size)
            {
                _MemoryStream.Write(RecvBuff, offset, msg_size);
                GenProtoMsgFromStream(_MemoryStream, msg_type, msg_size);
                offset += msg_size + 4;
            }
            else
            {
                break;
            }
        }

        return offset;
    }


    public void RecvMsg()
    {
        if (null == _socket) return;

        //socket.recv
        byte[] RecvBuff = new byte[1024];
        int ReceivedLen = _socket.Receive(RecvBuff);
        //remained bytes
        int existLen = m_ExistRecvBuff.Array.Length;
        Buffer.BlockCopy(m_ExistRecvBuff.Array, existLen, RecvBuff, 0, RecvBuff.Length);
        ReceivedLen += existLen;

        if (ReceivedLen > 0)
        {
            int solvedLen = ParseMsg(m_ExistRecvBuff.Array);
            m_ExistRecvBuff = new ArraySegment<byte>(m_ExistRecvBuff.Array, solvedLen, ReceivedLen - solvedLen);
        }
    }

    public void Init()
    {
        _socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
        _socket.Connect(new IPEndPoint(IPAddress.Parse("127.0.0.1"), 235));

        Thread thread = new Thread(new ThreadStart(RecvMsg));
    }
}
