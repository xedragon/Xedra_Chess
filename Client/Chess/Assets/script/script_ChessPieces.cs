using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum PIECES_TYPE
{
    BING,
    CHE,
    MA,
    PAO,
    JIANG,
    SHI,
    XIANG,
};


public class script_ChessPieces : MonoBehaviour
{
    public int coord_x;
    public int coord_y;
    public PIECES_TYPE type;

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
        script_GameManager.getInstance().ChoosePiece(this);
    }

    /// <summary>
    /// Self Defined Methods Below
    /// </summary>


}
