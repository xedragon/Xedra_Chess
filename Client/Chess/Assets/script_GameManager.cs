using protocols.Msg;
using System.Collections;
using System.Collections.Generic;
using tabtool;
using ProtoBuf;
using UnityEngine;

public class script_GameManager : MonoBehaviour
{
    public GameObject chessboard;
    public GameObject chessPiece;
    public static script_GameManager g_GameManager;

    /// <summary>
    /// Unity Methods Below
    /// </summary>

    // Start is called before the first frame update
    void Start()
    {
        //Init config
        if (TableConfig.Instance.LoadTableConfig())
        {
            tbsChessTypeItem item = cfgChessTypeTable.Instance.GetTableItem(1);
            if (item != null)
            {
                print("load config");
                print(item);
            }
        }
        //Init scene
        g_GameManager = this;
        LoadChessPieces();
        //Test protobuf
        Msg_Login_C2S s=new Msg_Login_C2S();
        s.conMethod = 1;
        s.szName = "sds";
        s.szPassWord = "卧槽";

        print(s.szPassWord);

    }

    // Update is called once per frame
    void Update()
    {
        if (choosed_piecs != null)
        {
            //Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);
            //RaycastHit hit;
            //if (Physics.Raycast(ray, out hit))
            //{
            //    var hitpoint =  hit.point;

            //    choosed_piecs.transform.position = hitpoint;
            //}

            var screeonpos = Camera.main.WorldToScreenPoint(choosed_piecs.transform.position);
            Vector3 mousepos = Input.mousePosition;
            mousepos.z = screeonpos.z;

            var tposition = Camera.main.ScreenToWorldPoint(mousepos);
            tposition.y = 0;

            //new Vector3(Input.mousePosition.x, Input.mousePosition.y,0);
            choosed_piecs.transform.position = tposition;
        }
    }

    /// <summary>
    /// Self Defined Methods Below
    /// </summary>
    static public script_GameManager getInstance()
    {
        if (g_GameManager == null)
        {
            print("未添加GameManager");
            g_GameManager = new script_GameManager();
        }
        return g_GameManager;
    }

    private void LoadChessPieces()
    {
        var sizeX = chessboard.GetComponent<Collider>().bounds.size.x;
        var sizeY = chessboard.GetComponent<Collider>().bounds.size.y;
        var pieceX = sizeX / 9;
        var pieceY = sizeY / 11;
        var boardcenter = chessboard.transform.position;
        for (int i = 1; i < 10; i++)
        {
            var tPiece = GameObject.Instantiate(chessPiece);
            tPiece.transform.position = boardcenter + new Vector3((i - 5) * pieceX, 0, 0);
        }
    }


    private script_ChessPieces choosed_piecs;
    public void ChoosePiece(script_ChessPieces piece)
    {
        if (choosed_piecs == piece)
        {
            choosed_piecs = null;
            return;
        }
        choosed_piecs = piece;
    }

}
