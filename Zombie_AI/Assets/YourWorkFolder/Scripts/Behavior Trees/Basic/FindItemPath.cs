using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FindItemPath : Task
{


    public FindItemPath() : base()
    {
    }

    public override TASK_RETURN_STATUS Run(Survivor_AI sAI)
    {
        TASK_RETURN_STATUS output = TASK_RETURN_STATUS.FAILURE;
        Blackboard_Player blackboard = sAI.GetBlackboard();
        //PathNode start = NearestNodeStart(blackboard.survivor, blackboard.graph);
        //PathNode end = NearestNodeEnd(blackboard.nearestItem, blackboard.graph);

        Vector3 target = blackboard.survivor.transform.position;
        Vector3 end = blackboard.nearestItem.transform.position;

        //PathNode node = PathFinder.FindClosetNodeToTarget(target.transform.position);
        // PathNode node = PathFinder.FindClosetNodeToTarget(target);
        blackboard.pickPath = PathFinder.GetPathToPoint(target, end);
        // PathFinder path = new PathFinder(sAI);
        //bool status = path.GetPath(ref blackboard.pickPath, start, end);

        //if (status == false)
        //{
        //    // Failed
        //    Debug.Log("FindItemPath - output: " + output);
        //    return output;
        //}
        output = TASK_RETURN_STATUS.SUCCESS;
        Debug.Log("FindItemPath - output: " + output);

        return output;
    }

    private PathNode NearestNodeStart(Survivor start, PathNode[] graph)
    {
        float dist;
        float closestDist = float.MaxValue;
        PathNode nearestNode = null;

        foreach (PathNode node in graph)
        {
            dist = (node.transform.position - start.transform.position).magnitude;
            if (dist <= closestDist)
            {
                closestDist = dist;
                nearestNode = node;
            }
        }

        return nearestNode;
    }

    private PathNode NearestNodeEnd(Loot end, PathNode[] graph)
    {
        Vector3 dir;
        float dist;
        float closestDist = float.MaxValue;
        PathNode nearestNode = null;

        foreach (PathNode node in graph)
        {

            dir = node.transform.position - end.transform.position;
            dist = dir.magnitude;
            if (dist <= closestDist)
            {
                closestDist = dist;
                nearestNode = node;
            }
        }

        return nearestNode;
    }
}
