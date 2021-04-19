using System.Collections;
using System.Collections.Generic;
using tabtool;
using ProtoBuf;
using UnityEngine;
using MsgPB;
using System;
using UnityEngine.SceneManagement;

public class gobang_GameManager : MonoBehaviour, IObserver<IExtensible>
{
    public GameObject chessboard;//棋盘
    public GameObject startbutton;//开始按钮
    public GameObject overbutton;//结束按钮
    private script_GobangPieces choosed_piecs;//已捻起的棋子
    public MsgPB.COLOR m_Color;//本玩家的棋子颜色
    public static gobang_GameManager t_gobangGameManager;

    Unsubscriber<IExtensible> iDispose;


    // Start is called before the first frame update
    void Start()
    {
        //Instance
        if (t_gobangGameManager == null)
        {
            t_gobangGameManager = this;
        }

        //Init config
        TableConfig.Instance.LoadTableConfig();

        //register
        iDispose = (Unsubscriber<IExtensible>)MsgMgr.getInstance().Subscribe(this);

        //scene
        overbutton.SetActive(false);
        startbutton.SetActive(true);
    }

    // Update is called once per frame
    void Update()
    {
        //MsgMgr
        MsgMgr.getInstance().update();
        //捻起的棋子跟随鼠标移动
        if (choosed_piecs != null)
        {
            var screeonpos = Camera.main.WorldToScreenPoint(choosed_piecs.transform.position);
            Vector3 mousepos = Input.mousePosition;
            mousepos.z = screeonpos.z;

            var tposition = Camera.main.ScreenToWorldPoint(mousepos);
            tposition.y = -0.3f;

            choosed_piecs.transform.position = tposition;
        }
    }

    private void OnMouseDown()
    {
        print("点击棋盘");
    }

    static public gobang_GameManager getInstance()
    {
        if (t_gobangGameManager == null)
        {
            print("GobangManager UnInitialized");
        }
        return t_gobangGameManager;
    }

    public void PickUpPiece(script_GobangPieces piece)
    {
        choosed_piecs = piece;
    }

    public void LayDownPiece(script_GobangPieces piece)
    {
        if (choosed_piecs == piece)
        {
            //放置棋子
            int x;
            int y;
            if (chessboard.GetComponent<script_GobangBoard>().LayDownPiece(choosed_piecs, out x, out y))
            {
                //发送消息
                Msg_Gobang_Action_C2S msg = new Msg_Gobang_Action_C2S();
                msg.x = x;
                msg.y = y;
                msg.Role = piece.m_Color;
                MsgMgr.getInstance().SendMsg(msg);

                Destroy(choosed_piecs.gameObject);
            }
        }
    }

    public void OnStartGameButton()
    {
        Msg_Gobang_Match_C2S msg = new Msg_Gobang_Match_C2S();
        MsgMgr.getInstance().SendMsg(msg);
    }

    public void OnOverGameButton()
    {
        iDispose.Dispose();
        SceneManager.LoadScene("Lobby");
    }

    public void TurnStart()
    {
        PickUpPiece(script_GobangBoard.CretePiece(m_Color));
    }

    private void onMsg_Gobang_Action_C2S(Msg_Gobang_Action_C2S msg)
    {
        //销毁捻起的棋子
        if (choosed_piecs != null)
        {
            Destroy(choosed_piecs.gameObject);
        }

        //上回合下出的棋子
        {
            chessboard.GetComponent<script_GobangBoard>().AddPiece(msg.Role, msg.x, msg.y);
        }

        //开始本回合
        m_Color = (COLOR)(3 - (int)m_Color);
        //if (msg.Role == m_Color)
        {
            TurnStart();
        }
    }

    private void onMsg_Gobang_Start_S2C(Msg_Gobang_Start_S2C msg)
    {
        startbutton.SetActive(false);
        m_Color = msg.Role;
        if (msg.Role == COLOR.White)
        {
            TurnStart();
        }
    }
    private void onMsg_Gobang_Over_S2C(Msg_Gobang_Over_S2C msg)
    {
        if (m_Color == msg.Winner)
        {
            overbutton.SetActive(true);
        }
    }

    private void onMsg_Gobang_Giveup_S2C(Msg_Gobang_Giveup_S2C msg)
    {
        overbutton.SetActive(true);
    }

    private void onMsg_Gobang_Regret_S2C(Msg_Gobang_Regret_S2C msg)
    {
    }

    private void onMsg_Gobang_Pause_S2C(Msg_Gobang_Pause_S2C msg)
    {
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
        switch (MsgMgr.GetMsgId(value))
        {
            case (ushort)MsgType.Gobang_Start_S2C:
                {
                    onMsg_Gobang_Start_S2C((Msg_Gobang_Start_S2C)value);
                }
                break;
            case (ushort)MsgType.Gobang_Action_C2S:
                {
                    onMsg_Gobang_Action_C2S((Msg_Gobang_Action_C2S)value);
                }
                break;
            case (ushort)MsgType.Gobang_Over_S2C:
                {
                    onMsg_Gobang_Over_S2C((Msg_Gobang_Over_S2C)value);
                }
                break;
            case (ushort)MsgType.Gobang_Giveup_S2C:
                {
                    onMsg_Gobang_Giveup_S2C((Msg_Gobang_Giveup_S2C)value);
                }
                break;
            case (ushort)MsgType.Gobang_Regret_S2C:
                {
                    onMsg_Gobang_Regret_S2C((Msg_Gobang_Regret_S2C)value);
                }
                break;
            case (ushort)MsgType.Gobang_Pause_S2C:
                {
                    onMsg_Gobang_Pause_S2C((Msg_Gobang_Pause_S2C)value);
                }
                break;

            default: break;
        }
    }
}
