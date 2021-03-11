using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class script_ChessPieces : MonoBehaviour
{
    public int coord_x;
    public int coord_y;
    public MsgPB.COLOR m_Color;

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
        gobang_GameManager.getInstance().LayDownPiece(this);
    }

    public int CoorId()
    {
        return 19 * coord_x + coord_y;
    }

    /// <summary>
    /// Self Defined Methods Below
    /// </summary>

}
