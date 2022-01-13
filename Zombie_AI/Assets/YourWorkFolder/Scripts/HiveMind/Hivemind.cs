using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Hivemind : MonoBehaviour
{
    Survivor_AI[] survivors;
    Survivor[] s;

    Task BT_DefaultFire;
    Task BT_DefaultFind;
    Task BT_DefaultMove;

    Task BT_SpecialFire;
    Task BT_SpecialMove;

    Task BT_SpecialFind;

    Task bearHuntBehavior;
    //PathNode[] graph;
    Task BT_MoveToTargetPoint;
    Task BT_MoveToDefendPoint;

    public DefendPoint[] defendLocations;

    public PathNode[] visibilityLocations;
    PathNode[] allNodes = GameObject.FindObjectsOfType<PathNode>();
    int k = 0;

    // FOR DEMO
    public List<PathNode> samplePath;
    Task followPathBehaviorDemo;

    // Start is called before the first frame update
    void Start()
    {

        CreateDefaultBehaviors();
        MoveToItem();
        CreateHuntBearBehavior();
        CreateMoveToTargetPoint();

        survivors = GameObject.FindObjectsOfType<Survivor_AI>();

        s = GameObject.FindObjectsOfType<Survivor>();

        allNodes = survivors[0].GetBlackboard().graph;

        for (int i = 0; i < survivors.Length; i++)
        {
            survivors[i].SetFireMode(BT_DefaultFire);
            survivors[i].SetMoveMode(BT_DefaultMove);
            //survivors[i].SetItemMode(BT_DefaultFind);
        }

        //MoveSurvivorsToDefensivePoint();

        // 
    }

    // Update is called once per frame
    void Update()
    {
        CheckForBears();
        PurchaseStuffFromStore();
        // MoveSurvivorsToDefensivePoint();
    }



    // Goal Driven Behavior
    public void GoalCompleted(Survivor_AI aI, string goalName)
    {
        Debug.Log("Goal Complete");

        if (goalName == "MoveToDefendPoint")
        {
            aI.SetMoveMode(BT_DefaultMove);
        }

        if (goalName == "MoveToItem")
        {
            aI.SetItemMode(BT_MoveToDefendPoint);
            //MoveSurvivorsToDefensivePoint();
        }

        if (goalName == "MoveToUpperPoint")
        {
            aI.SetItemMode(BT_DefaultFind);
            if (aI.GetBlackboard().k > 7)
            {
                aI.GetBlackboard().k = 0;
            }
            aI.GetBlackboard().k++;
        }

        else if (goalName == "KillBear")
        {
            aI.SetFireMode(BT_DefaultFire);
        }
    }

    public void GoalFailed(Survivor_AI aI, string goalName)
    {
        if (goalName == "KillBear")
        {
            aI.SetMoveMode(BT_DefaultFire);
        }
    }

    void MoveSurvivorsToDefensivePoint()
    {
        for (int i = 0; i < survivors.Length; i++)
        {
            survivors[i].GetBlackboard().moveTarget = defendLocations[0].defendPts[i].transform.position;
            survivors[i].GetBlackboard().currentGoal = "MoveToDefendPoint";
            survivors[i].SetMoveMode(BT_MoveToDefendPoint);
        }
    }


    void CheckForBears()
    {
        List<Enemy> zomHell = GameManager.getHellephantList();

        if (zomHell.Count > 0)
        {
            for (int i = 0; i < survivors.Length; i++)
            {
                survivors[i].SetFireMode(BT_SpecialFire);
                survivors[i].SetMoveMode(BT_DefaultMove);
                survivors[i].SetItemMode(BT_DefaultFind);
            }

        }
    }
    Survivor_AI FindClosestSurvivorToTarget(Vector3 target)
    {
        Survivor_AI output = null;

        float closestDistSoFar = Mathf.Infinity;
        Survivor_AI closestSoFar = null;

        for (int i = 0; i < survivors.Length; i++)
        {
            if (survivors[i].isAlive() == true)
            {
                float dist = Vector3.Distance(target, survivors[i].transform.position);

                if (dist < closestDistSoFar)
                {
                    closestDistSoFar = dist;
                    closestSoFar = survivors[i];
                }
            }
        }

        output = closestSoFar;


        return output;
    }

    void CreateMoveToTargetPoint()
    {
        Task root = new Sequence();

        root.AddTask(new SetMoveDefend());
        root.AddTask(new MoveDefend());
        root.AddTask(new ReachedDefend());
        root.AddTask(new CompletedGoal());

        BT_MoveToDefendPoint = root;
    }

    //void FollowPathDemo()
    //{
    //    survivors[0].SetMoveMode(BT_MoveToTargetPoint);
    //
    //    survivors[0].GetBlackboard().currentPath = PathFinder.GetPathToPoint(samplePath[0].transform.position, survivors[0].transform.position);
    //   
    //}


    void CreateDefaultBehaviors()
    {
        // MOVE Behavior
        BT_DefaultMove = new RunAll();

        ///Selector Goal = new Selector();
        Sequence moveBehavior = new Sequence();
        moveBehavior.AddTask(new FindClosestFleeTarget());
        moveBehavior.AddTask(new FleeFromClosest());
        moveBehavior.AddTask(new MovePlayer());
        BT_DefaultMove.AddTask(moveBehavior);
        //Seq pickupSelector = new Selector();

        Task root = new Sequence();

        BT_SpecialFind = new RunAll();
        Selector choosePickup = new Selector();
        NeedHealth needHealthNode = new NeedHealth();
        NeedAmmo needAmmoNode = new NeedAmmo();
        choosePickup.AddTask(needHealthNode);
        choosePickup.AddTask(needAmmoNode);

        FindItemPath findPathToItem = new FindItemPath();

        Sequence pickupprocess = new Sequence();
        pickupprocess.AddTask(choosePickup);
        pickupprocess.AddTask(findPathToItem);

        Sequence pickupSequence = new Sequence();
        PickItem pickupItemNode = new PickItem();
        // pickupSelector.AddTask(moveToItemNode);
        pickupSequence.AddTask(pickupprocess);
        pickupSequence.AddTask(pickupItemNode);


        root.AddTask(pickupSequence);
        root.AddTask(new CompletedGoal());

        BT_SpecialFind = root;
        //////////////////


        // Fire Behavior
        BT_DefaultFire = new RunAll();


        //Sequence sequence1 = new Sequence();
        //
        //sequence1.AddTask(new EquipPistol());
        //sequence1.AddTask(new SurvivorOverrun());
        //sequence1.AddTask(new EquipShotgun());


        BT_DefaultFire.AddTask(new ChooseWeapon());
        BT_DefaultFire.AddTask(new FindClosestTarget());
        //BT_DefaultFire.AddTask(new CheckTargetVisible());
        BT_DefaultFire.AddTask(new FireAtTarget());

    }

    void CreateHuntBearBehavior()
    {
        BT_SpecialMove = new RunAll();



        Sequence moveBehavior = new Sequence();
        moveBehavior.AddTask(new FindClosestFleeTarget());
        moveBehavior.AddTask(new FleeFromClosest());
        moveBehavior.AddTask(new MovePlayer());
        BT_SpecialMove.AddTask(moveBehavior);
        //Seq pickupSelector = new Selector();

        Task root = new Sequence();

        root.AddTask(new SetMoveTarget());
        root.AddTask(new MovePlayer());
        root.AddTask(new ReachedTarget());
        root.AddTask(new CompletedGoal());

        BT_DefaultFind = root;
        //BT_SpecialFind = new RunAll();
        //Selector choosePickup = new Selector();
        //NeedHealth needHealthNode = new NeedHealth();
        //NeedAmmo needAmmoNode = new NeedAmmo();
        //choosePickup.AddTask(needHealthNode);
        //choosePickup.AddTask(needAmmoNode);
        //
        //FindItemPath findPathToItem = new FindItemPath();
        //
        //Sequence pickupprocess = new Sequence();
        //pickupprocess.AddTask(choosePickup);
        //pickupprocess.AddTask(findPathToItem);
        //
        //Sequence pickupSequence = new Sequence();
        //PickItem pickupItemNode = new PickItem();
        //// pickupSelector.AddTask(moveToItemNode);
        //pickupSequence.AddTask(pickupprocess);
        //pickupSequence.AddTask(pickupItemNode);
        //
        //
        //BT_SpecialFind.AddTask(pickupSequence);

        //////////////////


        // Fire Behavior
        BT_SpecialFire = new RunAll();

        //Selector selector1 = new Selector();
        //selector1.AddTask(new CheckTargetVisible());
        //selector1.AddTask(new FailedGoal());

        //Sequence sequence1 = new Sequence();
        //sequence1.AddTask(new EquipSniper());
        //sequence1.AddTask(new SurvivorOverrun());
        //sequence1.AddTask(new EquipShotgun());


        // BT_SpecialFire.AddTask(sequence1);

        BT_SpecialFire.AddTask(new FindClosest());
        BT_SpecialFire.AddTask(new ChooseWeapon());
        //BT_SpecialFire.AddTask(new MoveToBear());
        BT_SpecialFire.AddTask(new FireAtTarget());

    }

    // void CreateKillTargetWithSniperBehavior()
    // {
    //     Sequence fireSequence = new Sequence();
    //
    //     Selector selector1 = new Selector();
    //     selector1.AddTask(new CheckTargetVisible());
    //     selector1.AddTask(new FailedGoal());
    //
    //     fireSequence.AddTask(new EquipSniper());
    //     fireSequence.AddTask(new FireAtTarget());
    //     fireSequence.AddTask(new CompletedGoal());
    //
    //     BT_KillTargetWithSniper = fireSequence;
    //
    // }

    //void CreateMoveToTargetPoint()
    //{
    //    Task root = new Sequence();
    //
    //    root.AddTask(new SetMoveTarget());
    //    root.AddTask(new MovePlayer());
    //    root.AddTask(new ReachedTarget());
    //    root.AddTask(new CompletedGoal());
    //
    //    BT_DefaultFind = root;
    //}


    void CreateFollowPathDemo()
    {
        Task root = new RunAll();

        Task pathTree = new Sequence();

        pathTree.AddTask(new FollowPath());
        pathTree.AddTask(new CompletedGoal());


        root.AddTask(pathTree);
        root.AddTask(new FindClosestFleeTarget());
        root.AddTask(new FleeFromClosest());
        root.AddTask(new MovePlayer());


        followPathBehaviorDemo = root;
    }
    void MoveToItem()
    {

    }

    public void BreakEvent()
    {
        Debug.Log("Break mode active");
        //FollowPathDemo();
        //for (int i = 0; i < 4; i++)
        //{
        survivors[1].GetBlackboard().currentGoal = "MoveToItem";
        survivors[1].SetItemMode(BT_SpecialFind);


    }

    public void SubWaveComplete()
    {
        //MoveSurvivorsToDefensivePoint();
    }

    public void WaveCompleted()
    {
        MoveSurvivorsToDefensivePoint();
    }


    void PurchaseStuffFromStore()
    {
        if (GameManager.isBreakInProgress() == true)
        {
            int gold = GameManager.GetCurrentGold();
            int gold1 = gold / 3;
            int gold2 = gold1;
            int gold3 = gold2;

            while (gold1 > GameManager.GetShotgunAmmoCost())
            {
                GameManager.PurchaseAmmo(WEAPON_TYPE.SHOTGUN);
                gold1 = GameManager.GetCurrentGold() - gold2 - gold3;
            }
            while (gold2 > GameManager.GetSniperAmmoCost())
            {
                GameManager.PurchaseAmmo(WEAPON_TYPE.SNIPER);
                gold2 = GameManager.GetCurrentGold() - gold1 - gold3;
            }
            while (gold3 > GameManager.GetAssaultAmmoCost())
            {
                GameManager.PurchaseAmmo(WEAPON_TYPE.ASSAULT);
                gold3 = GameManager.GetCurrentGold() - gold1 - gold2;
            }
            while (gold > 49)
            {
                for (int i = 0; i < survivors.Length; i++)
                {
                    GameManager.PurchaseHealth(s[i]);
                    gold = GameManager.GetCurrentGold();
                }
            }
            MoveSurvivorsToDefensivePoint();
            GameManager.PurchaseAmmo(WEAPON_TYPE.SHOTGUN);
        }
        else
        {
            Invoke("PurchaseStuffFromStore", 1.0f);
        }
    }


}
