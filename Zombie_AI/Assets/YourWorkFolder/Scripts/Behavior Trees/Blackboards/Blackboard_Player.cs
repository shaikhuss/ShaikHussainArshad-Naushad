using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Blackboard_Player : Blackboard
{
    // public Enemy closestZombunny;
    //  public Enemy closestBear;
    public Enemy closestZombunny;
    public Enemy closestBear;
    public Enemy closestHellephant;

    public Survivor survivor;
    public List<PathNode> pickPath;
    public Loot nearestItem;

    public Enemy chosenTarget;
    public float fleeDistance;
    public Vector3 moveDirection;

    public PathNode[] graph;
    public List<PathNode> currentPath;
    public List<PathNode> move;
    public PathNode currentNode;
    public PathNode targetNode;
    public Vector3 fleeDirection;

    public Vector3 fleeTarget;

    public string currentGoal;


    public int k;

    // public Vector3 fleeTarget;
    // public Survivor survivor;
    //
    // // This is the enemy I will fire at
    // public Enemy chosenTarget;
    //
    public Vector3 moveTarget;
    // public Vector3 moveDirection;
    // public PathNode[] graph;
    // public LinkedList<PathNode> pickPath;
    //
    // 
    // public Loot nearestItem;
    //
    // public List<PathNode> currentPath;
    // public PathNode targetNode;

    public Blackboard_Player(Survivor s, PathNode[] g)
    {
        this.pickPath = new List<PathNode>();
        this.survivor = s;
        this.graph = g;
        this.k = 0;
    }
}
