using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class script_ChessPieces : MonoBehaviour
{
    public int m_id;
    public int m_coord_x;
    public int m_coord_y;
    public MsgPB.COLOR m_Color;
    public MsgPB.CHESSTYPE m_Type;

    /// <summary>
    /// Unity Methods Below
    /// </summary>

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {

    }

    void OnMouseDown()
    {
        chess_GameManager.getInstance().LayDownPiece(this);
    }
}
