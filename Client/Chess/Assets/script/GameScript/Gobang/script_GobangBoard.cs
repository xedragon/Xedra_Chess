﻿using MsgPB;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class script_GobangBoard : MonoBehaviour
{
    void Start()
    {
        sizeX = GetComponent<Collider>().bounds.size.x;
        sizeZ = GetComponent<Collider>().bounds.size.z;
        m_AllPieces = new Dictionary<int, script_GobangPieces>();
    }

    void Update()
    {
    }

    public int num_gridx = 18;
    public int num_gridz = 18;
    private float sizeX;
    private float sizeZ;

    public bool LayDownPiece(script_GobangPieces piece, out int x, out int y)
    {
        var pos = piece.transform.position;
        x = Mathf.RoundToInt((pos.x) / (sizeX / num_gridx));
        y = Mathf.RoundToInt((pos.z) / (sizeZ / num_gridz));

        if (m_AllPieces.ContainsKey(19 * x + y) && m_AllPieces[19 * x + y].m_Color != COLOR.Null)
        {
            //该位置已有棋子
            return false;
        }
        else
        {
            return true;
        }
    }

    public static script_GobangPieces CretePiece(COLOR color)
    {
        GameObject obj = null;
        switch (color)
        {
            case COLOR.Null:
                break;
            case COLOR.White:
                {
                    GameObject WhitePiece = (GameObject)Resources.Load("Perfabs/Gobang/WhitePiece");
                    obj = Instantiate(WhitePiece);
                }
                break;
            case COLOR.Black:
                {
                    GameObject BlackPiece = (GameObject)Resources.Load("Perfabs/Gobang/BlackPiece");
                    obj = Instantiate(BlackPiece);
                }
                break;
            default:
                break;
        }

        return obj.GetComponent<script_GobangPieces>();
    }

    Dictionary<int, script_GobangPieces> m_AllPieces;
    public void AddPiece(COLOR color, int x, int y)
    {
        if (color == COLOR.Null) return;

        var piece = CretePiece(color);
        piece.coord_x = x;
        piece.coord_y = y;
        piece.transform.position = calPos(x, y);

        m_AllPieces[piece.CoorId()] = piece;
    }

    public void DelPiece(int x, int y)
    {
        int coordid = x * 19 + y;
        if (m_AllPieces.ContainsKey(coordid))
        {
            var piece = m_AllPieces[coordid];
            Destroy(piece.gameObject);
            m_AllPieces.Remove(coordid);
        }
    }

    public Vector3 calPos(int gridx, int gridz)
    {
        float x = (gridx) * (sizeX / num_gridx);
        float z = (gridz) * (sizeZ / num_gridz);
        float y = -0.3f;
        return new Vector3(x, y, z);
    }

}
