using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveToTarget : Task
{



    public override TASK_RETURN_STATUS Run(Survivor_AI sAI)
    {
        Blackboard_Player blackboard = sAI.GetBlackboard();
        TASK_RETURN_STATUS output = TASK_RETURN_STATUS.FAILURE;

        Enemy item = blackboard.chosenTarget;

        // If there is an item to get
        if (item != null)
        {
            Vector3 itemDir = item.transform.position - blackboard.survivor.transform.position;

            // If we don't have a path to follow anymore
            if (blackboard.pickPath.Count <= 0)
            {

                // Get the item
                blackboard.survivor.MoveTo(item.transform.position);

                output = TASK_RETURN_STATUS.SUCCESS;
                //Debug.Log("PickupItem - output: " + output + ", item: " + item);
            }



        }
        return output;
    }
    //public override TASK_RETURN_STATUS Run(Survivor_AI sAI)
    //{
    //    TASK_RETURN_STATUS output = TASK_RETURN_STATUS.FAILURE;
    //    Blackboard_Player blackboard = sAI.GetBlackboard();

    //    if (blackboard.pickPath.Count > 0)
    //    {
    //        Survivor survivor = blackboard.survivor;
    //        PathNode pathnode = blackboard.pickPath.First.Value;

    //        // Move to PathNode
    //        Vector3 direction = Seek(survivor.transform.position, pathnode.transform.position);
    //        survivor.MoveTo(direction + survivor.transform.position);

    //        // If at PathNode
    //        if (IsAtPathNode(pathnode, survivor))
    //        {
    //            blackboard.pickPath.RemoveFirst();
    //        }
    //        output = TASK_RETURN_STATUS.SUCCESS;
    //        // Debug.Log("MoveToItem - output: " + output);
    //    }

    //    return output;
    //}

    //private bool IsAtPathNode(PathNode node, Survivor s)
    //{
    //    Vector2 dir = node.transform.position - s.transform.position;

    //    return (dir.magnitude <= 0.8f);
    //}

    //private Vector3 Seek(Vector3 start, Vector3 end)
    //{
    //    Vector3 dir = end - start;
    //    float dist = dir.magnitude;
    //    dir.Normalize();
    //    dir *= dist;

    //    return dir;
    //}
}
