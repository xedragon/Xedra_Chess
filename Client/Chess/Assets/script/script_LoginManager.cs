using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using MsgPB;
using ProtoBuf;
using System;
using UnityEngine.SceneManagement;

public class script_LoginManager : script_GameManager
{
    // Start is called before the first frame update
    public void Start()
    {
        base.Start();
        RegisterMsg(onMsg_Login_S2C,(int)MsgType.LOGIN_S2C);
    }

    // Update is called once per frame
    void Update()
    {
        base.Update();
        MsgMgr.getInstance().update();
    }

    public void onLoginButtonClicked()
    {
        GameObject Name_obj = GameObject.FindGameObjectWithTag("NameText");
        string strName = Name_obj.GetComponent<InputField>().text;
        GameObject Pass_obj = GameObject.FindGameObjectWithTag("PasswordText");
        string strPassword = Pass_obj.GetComponent<InputField>().text;

        Login(strName, strPassword, Msg_Login_C2S.CONMETHOD.Login);
    }

    public void onRegisterButtonClicked()
    {
        GameObject Name_obj = GameObject.FindGameObjectWithTag("NameText");
        string strName = Name_obj.GetComponent<InputField>().text;
        GameObject Pass_obj = GameObject.FindGameObjectWithTag("PasswordText");
        string strPassword = Pass_obj.GetComponent<InputField>().text;

        Login(strName, strPassword, Msg_Login_C2S.CONMETHOD.Regist);
    }

    public void Login(string name,string password, Msg_Login_C2S.CONMETHOD method)
    {
        Msg_Login_C2S msg = new Msg_Login_C2S();
        msg.szName = name;
        msg.szPassWord = password;
        msg.conMethod = method;
        MsgMgr.getInstance().SendMsg(msg);
    }

    private void onMsg_Login_S2C(IExtensible extensible)
    {
        var msg = (Msg_Login_S2C)extensible;
        if (msg == null) return;

        if (msg._ErrorCode == Msg_Login_S2C.ERRORCODE.LoginSuccess || msg._ErrorCode == Msg_Login_S2C.ERRORCODE.LoginSuccess)
        {
            SceneManager.LoadScene("Lobby");
        }

    }
}
