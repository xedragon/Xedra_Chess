using System.Collections;
using System.Collections.Generic;
using tabtool;
using ProtoBuf;
using UnityEngine;
using MsgPB;
using System;

public class script_GameManager : MonoBehaviour, IObserver<IExtensible>
{
    delegate void MsgCallBack(IExtensible msg);
    Dictionary<int, Action<IExtensible>> m_CallBackMap;

    // Start is called before the first frame update
    public void Start()
    {
        m_CallBackMap = new Dictionary<int, Action<IExtensible>>();

        //Init config
        TableConfig.Instance.LoadTableConfig();

        //register
        MsgMgr.getInstance().Subscribe(this);
    }

    // Update is called once per frame
    public void Update()
    {
        //MsgMgr
        MsgMgr.getInstance().update();
    }

    protected  void RegisterMsg(Action<IExtensible> callback,int msgid)
    {
        m_CallBackMap.Add(msgid, callback);
    }


    public void OnCompleted()
    {
        throw new NotImplementedException();
    }

    public void OnError(Exception error)
    {
        throw new NotImplementedException();
    }
    public void OnNext(IExtensible value)
    {
        int msgid = MsgMgr.GetMsgId(value);
        if (m_CallBackMap.ContainsKey(msgid))
        {
            m_CallBackMap[msgid](value);
        }
    }
}
