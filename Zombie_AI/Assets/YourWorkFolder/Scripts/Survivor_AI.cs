using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Survivor_AI : MonoBehaviour
{
    Survivor survivor;

    public LayerMask enemyMask;
    public LayerMask visibiltyMask;

    public float fleeDistance;
    public float fleeSpeed;

    public float overrunDistance;
    public int overrunCount;
    PathNode[] graph;

    Blackboard_Player blackboard;

    Task BT_FireMode;
    Task BT_MoveMode;
    Task BT_ItemMode;

    // Start is called before the first frame update
    void Start()
    {
        survivor = GetComponent<Survivor>();
        graph = GameObject.FindObjectsOfType<PathNode>();

        blackboard = new Blackboard_Player(survivor, graph);

    }

    // Update is called once per frame
    void Update()
    {
        if (BT_FireMode != null)
        {
            BT_FireMode.Run(this);
        }
        if (BT_MoveMode != null)
        {
            BT_MoveMode.Run(this);
        }
        if (BT_ItemMode != null)
        {
            BT_ItemMode.Run(this);
        }
    }

    public void SetFireMode(Task newTree)
    {
        BT_FireMode = newTree;
    }

    public void SetMoveMode(Task newTree)
    {
        BT_MoveMode = newTree;
    }

    public void SetItemMode(Task newTree)
    {
        BT_ItemMode = newTree;
    }

    public void MoveTo(Vector3 target)
    {
        survivor.MoveTo(target);
    }

    public void Fire(Vector3 target)
    {
        survivor.Fire(target);
    }

    public Weapon GetCurrentWeapon()
    {
        return survivor.GetCurrentWeapon();
    }

    public void SwitchWeapon(WEAPON_TYPE newWeapon)
    {
        if (survivor.GetCurrentWeapon().type != newWeapon)
        {
            survivor.SwitchWeapons(newWeapon);
        }
    }

    public bool isAlive()
    {
        return (survivor.GetSurvivorState() == SURVIVORSTATE.NORMAL);
    }
    public Blackboard_Player GetBlackboard()
    {
        return blackboard;
    }


}
