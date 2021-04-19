using System.Collections;
using System.Collections.Generic;
using tabtool;
using ProtoBuf;
using UnityEngine;
using MsgPB;
using System;
using UnityEngine.SceneManagement;

public class chess_GameManager : MonoBehaviour, IObserver<IExtensible>
{
    //Ui Constols
    public GameObject chessboard;//棋盘
    public GameObject startbutton;//开始按钮
    public GameObject overbutton;//结束按钮

    private int m_TurnId;//当前回合
    private script_ChessPieces choosed_piecs;//已捻起的棋子
    public MsgPB.COLOR m_Color;//本玩家的棋子颜色
    public static chess_GameManager t_chessGameManager;
    private bool bInMyTurn = false;
    Unsubscriber<IExtensible> iDispose;

    // Start is called before the first frame update
    void Start()
    {
        //Instance
        if (t_chessGameManager == null)
        {
            t_chessGameManager = this;
        }

        //Init config
        TableConfig.Instance.LoadTableConfig();

        //register
        iDispose = (Unsubscriber<IExtensible>)MsgMgr.getInstance().Subscribe(this);
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
            tposition.y = 1.3f;
            choosed_piecs.transform.position = tposition;
        }

        if (Input.GetMouseButtonDown(1))
        {
            if (choosed_piecs != null)
            {
                //放回原位
                chessboard.GetComponent<script_ChessBoard>().setPiece(choosed_piecs.m_id, choosed_piecs.m_coord_x, choosed_piecs.m_coord_y);
                choosed_piecs = null;
            }
        }
    }

    private void OnMouseDown()
    {
        var screeonpos = Camera.main.WorldToScreenPoint(transform.position);
        Vector3 mousepos = Input.mousePosition;
        mousepos.z = screeonpos.z;

        var tposition = Camera.main.ScreenToWorldPoint(mousepos);
    }

    static public chess_GameManager getInstance()
    {
        if (t_chessGameManager == null)
        {
            print("ChessManager UnInitialized");
        }
        return t_chessGameManager;
    }

    public void LayDownPiece(script_ChessPieces piece)
    {
        if (!bInMyTurn) return;//非本方回合
        if (piece.m_Color != m_Color) return;//点选了非本方棋子

        //点击选择棋子
        if (choosed_piecs == null)
        {
            choosed_piecs = piece;
        }
        //再次点击选择放置棋子
        else if (choosed_piecs == piece)
        {
            //放置
            int x;
            int y;
            if(chessboard.GetComponent<script_ChessBoard>().calCoord(choosed_piecs.transform.position, out x, out y))
            {
                //发送消息
                Msg_Chess_Action_C2S msg = new Msg_Chess_Action_C2S();

                Msg_Chess_Piece temp = new Msg_Chess_Piece();
                temp.id = choosed_piecs.m_id;
                temp.des_posx = x;
                temp.des_posy = y;

                msg.Pieces.Add(temp);
                MsgMgr.getInstance().SendMsg(msg);

                //放回原位
                chessboard.GetComponent<script_ChessBoard>().setPiece(choosed_piecs.m_id, choosed_piecs.m_coord_x, choosed_piecs.m_coord_y);
                choosed_piecs = null;
            }
        }
    }

    public void OnStartGameButton()
    {
        Msg_Chess_Match_C2S msg = new Msg_Chess_Match_C2S();
        MsgMgr.getInstance().SendMsg(msg);

        chessboard.SetActive(true);

        startbutton.SetActive(false);
    }

    public void OnOverGameButton()
    {
        iDispose.Dispose();
        chessboard.GetComponent<script_ChessBoard>().ClearBoard();
        SceneManager.LoadScene("Lobby");
    }

    public void OnRegretGameButton()
    {
        Msg_Chess_Regret_C2S msg = new Msg_Chess_Regret_C2S();
        MsgMgr.getInstance().SendMsg(msg);
    }

    public void OnGiveupGameButton()
    {
        Msg_Chess_Giveup_C2S msg = new Msg_Chess_Giveup_C2S();
        MsgMgr.getInstance().SendMsg(msg);
    }

    public void TurnStart()
    {
        //if (((int)m_Color + m_TurnId) % 2 == 0)
        //{
        //    bInMyTurn = true;
        //}
        //else 
        //{
        //    bInMyTurn = false;
        //}
        bInMyTurn = true;
    }

    private void onMsg_Chess_Start_S2C(Msg_Chess_Start_S2C msg)
    {
        //数据初始化
        //m_Color = COLOR.White;
        m_Color = msg.Role;
        m_TurnId = 1;
        //加载场景
        chessboard.GetComponent<script_ChessBoard>().InitBoard(m_Color);
        //回合开始
        TurnStart();
    }

    private void onMsg_Chess_Action_S2C(Msg_Chess_Action_S2C msg)
    {
        //上回合的变动
        foreach (var p in msg.Pieces)
        {
            chessboard.GetComponent<script_ChessBoard>().setPiece(p.id, p.des_posx, p.des_posy);
        }

        //棋权变更
        m_TurnId = msg.turnId+1;
        TurnStart();
    }
    private void onMsg_Chess_Regret_S2C(Msg_Chess_Regret_S2C msg)
    {
        //上回合的变动
        foreach (var p in msg.Pieces)
        {
            chessboard.GetComponent<script_ChessBoard>().setPiece(p.id, p.ori_posx, p.ori_posy);
        }

        //棋权变更
        m_TurnId = msg.turnId + 1;
        TurnStart();
    }

    private void onMsg_Chess_Giveup_S2C(Msg_Chess_Giveup_S2C msg)
    {
        overbutton.SetActive(true);
    }


    private void onMsg_Chess_Pause_S2C(Msg_Chess_Pause_S2C msg)
    {
    }

    private void onMsg_Chess_Over_S2C(Msg_Chess_Over_S2C msg)
    {
        //if (msg.Winner == m_Color)
        {
            overbutton.SetActive(true);
        }
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
            case (ushort)MsgType.Chess_Start_S2C:
                {
                    onMsg_Chess_Start_S2C((Msg_Chess_Start_S2C)value);
                }
                break;
            case (ushort)MsgType.Chess_Action_S2C:
                {
                    onMsg_Chess_Action_S2C((Msg_Chess_Action_S2C)value);
                }
                break;
            case (ushort)MsgType.Chess_Over_S2C:
                {
                    onMsg_Chess_Over_S2C((Msg_Chess_Over_S2C)value);
                }
                break;
            case (ushort)MsgType.Chess_Giveup_S2C:
                {
                    onMsg_Chess_Giveup_S2C((Msg_Chess_Giveup_S2C)value);
                }
                break;
            case (ushort)MsgType.Chess_Regret_S2C:
                {
                    onMsg_Chess_Regret_S2C((Msg_Chess_Regret_S2C)value);
                }
                break;
            case (ushort)MsgType.Chess_Pause_S2C:
                {
                    onMsg_Chess_Pause_S2C((Msg_Chess_Pause_S2C)value);
                }
                break;

            default: break;
        }
    }
}
