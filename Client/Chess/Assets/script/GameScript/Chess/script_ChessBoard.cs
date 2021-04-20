using MsgPB;
using System.Collections;
using System.Collections.Generic;
using tabtool;
using UnityEngine;

public class script_ChessBoard : MonoBehaviour
{
    void Start()
    {
        sizeX = GetComponent<Collider>().bounds.size.x;
        sizeZ = GetComponent<Collider>().bounds.size.z;
    }

    public void InitBoard(COLOR color)
    {
        //由服务器分配阵营为黑、白
        m_Color = color;
        //加载配置表，生成棋子
        for (int i = 1; i <= 32; i++)
        {
            var item = SingletonTable<cfgChessTypeTable>.Instance.GetTableItem(i);
            //添加一枚棋子，参数为颜色、类型、初始位置、唯一id
            AddPiece((COLOR)item.color, (CHESSTYPE)item.type, item.posx, item.posy, item.id);
        }
        //AddPiece(COLOR.White, CHESSTYPE.King, 5, 1, 1);

        //黑色方的棋盘视角进行180度反转
        if (color == COLOR.Black)
        {
            transform.Rotate(new Vector3(0, 180, 0));
        }
    }

    void Update()
    {
    }

    public int num_gridx = 8;
    public int num_gridz = 8;
    private float sizeX;
    private float sizeZ;
    public COLOR m_Color;

    public static script_ChessPieces CretePiece(COLOR color, CHESSTYPE type, int id)
    {
        string strPath = "";
        switch (color)
        {
            case COLOR.Null:
                break;
            case COLOR.White:
                {
                    switch (type)
                    {
                        case CHESSTYPE.King:
                            strPath = "Perfabs/Chess/WhiteStoneKing";
                            break;
                        case CHESSTYPE.Queen:
                            strPath = "Perfabs/Chess/WhiteStoneQueen";
                            break;
                        case CHESSTYPE.Car:
                            strPath = "Perfabs/Chess/WhiteStoneRook";
                            break;
                        case CHESSTYPE.Elephant:
                            strPath = "Perfabs/Chess/WhiteStoneBishop";
                            break;
                        case CHESSTYPE.Horse:
                            strPath = "Perfabs/Chess/WhiteStoneHorse";
                            break;
                        case CHESSTYPE.Solider:
                            strPath = "Perfabs/Chess/WhiteStonePawn";
                            break;
                        default:
                            break;
                    }
                }
                break;
            case COLOR.Black:
                {
                    switch (type)
                    {
                        case CHESSTYPE.King:
                            strPath = "Perfabs/Chess/BlackStoneKing";
                            break;
                        case CHESSTYPE.Queen:
                            strPath = "Perfabs/Chess/BlackStoneQueen";
                            break;
                        case CHESSTYPE.Car:
                            strPath = "Perfabs/Chess/BlackStoneRook";
                            break;
                        case CHESSTYPE.Elephant:
                            strPath = "Perfabs/Chess/BlackStoneBishop";
                            break;
                        case CHESSTYPE.Horse:
                            strPath = "Perfabs/Chess/BlackStoneHorse";
                            break;
                        case CHESSTYPE.Solider:
                            strPath = "Perfabs/Chess/BlackStonePawn";
                            break;
                        default:
                            break;
                    }
                }
                break;
            default:
                break;
        }

        GameObject obj = Instantiate((GameObject)Resources.Load(strPath));

        var scipt = obj.AddComponent<script_ChessPieces>();
        scipt.m_Color = color;
        scipt.m_Type = type;
        scipt.m_id = id;
        return obj.GetComponent<script_ChessPieces>();
    }

    private void setPiece(script_ChessPieces piece, int x, int y)
    {
        piece.m_coord_x = x;
        piece.m_coord_y = y;

        piece.transform.SetParent(this.transform);
        piece.transform.localPosition =  calPos(x, y);
    }

    public void setPiece(int id, int x, int y)
    {
        if (allPieces.ContainsKey(id))
        {
            var piece = allPieces[id];
            if (x == 0 && y == 0)
            {
                piece.gameObject.SetActive(false);
            }
            else
            {
                piece.gameObject.SetActive(true);
                setPiece(piece, x, y);
            }
        }
    }

    Dictionary<int, script_ChessPieces> allPieces = new Dictionary<int, script_ChessPieces>();
    public void AddPiece(COLOR color, CHESSTYPE type, int x, int y, int id)
    {
        //if (color == COLOR.Null) return;

        var piece = CretePiece(color, type, id);
        setPiece(piece, x, y);

        allPieces[id] = piece;
    }

    public void ClearBoard()
    {
        foreach (var pair in allPieces)
        {
            Destroy(pair.Value.gameObject);
        }
        allPieces.Clear();
    }

    public Vector3 calPos(int gridx, int gridz)
    {
        var centerx = /*transform.position.x*/ -9f;
        var centery = /*transform.position.z*/ -9f;

        float x = centerx/*原点*/ + (gridx)/*格子编号*/ * (sizeX / num_gridx)/*格子宽度*/;
        float z = centery + (gridz) * (sizeZ / num_gridz);
        float y = 1.3f;
        return new Vector3(x, y, z);
    }

    public bool calCoord(Vector3 pos, out int x, out int y)
    {
        var centerx = transform.position.x - 9f;
        var centery = transform.position.z - 9f;

        x = Mathf.RoundToInt((pos.x - centerx) / (sizeX / num_gridx));
        y = Mathf.RoundToInt((pos.z - centery) / (sizeZ / num_gridz));
        return LeagelPos(x, y);
    }

    public bool LeagelPos(int x, int y)
    {
        if (x < 1 || x > 8) return false;
        if (y < 1 || y > 8) return false;
        return true;
    }
}
