using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Lobby_GameManager : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void onGobangClicked()
    {
        SceneManager.LoadScene("Gobang");
    }

    public void onChessClicked()
    {
        SceneManager.LoadScene("Chess");
    }
}
