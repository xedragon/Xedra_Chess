using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class script_ChessBoard : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        //if (Input.GetMouseButton(0))
        //{
        //    Ray ray = Camera.main.ScreenPointToRay(Input.mousePosition);  //camare2D.ScreenPointToRay (Input.mousePosition);
        //    RaycastHit hit;
        //    if (Physics.Raycast(ray, out hit))
        //    {
        //        if (gameObject.Equals(hit.collider.gameObject))
        //        {
        //            Debug.Log("点击了棋盘");
        //        }
        //    }
        //}
    }

    void OnMouseDown()
    {
        print("点击棋盘");
    }

}
