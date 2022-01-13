using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PickItem : Task
{

    public override TASK_RETURN_STATUS Run(Survivor_AI sAI)
    {
        Blackboard_Player blackboard = sAI.GetBlackboard();
        TASK_RETURN_STATUS output = TASK_RETURN_STATUS.FAILURE;

        Loot item = blackboard.nearestItem;

        // If there is an item to get
        if (item != null)
        {
            Vector3 itemDir = item.transform.position - blackboard.survivor.transform.position;
            float distanceToTarget = Vector3.Distance(item.transform.position, sAI.transform.position);

            // If we don't have a path to follow anymore
            if (blackboard.pickPath.Count >= 0)
            {

                // Get the item
                blackboard.survivor.MoveTo(item.transform.position);

                if (distanceToTarget < 2)
                {
                    output = TASK_RETURN_STATUS.SUCCESS;
                }

                //Debug.Log("PickupItem - output: " + output + ", item: " + item);
            }



        }
        return output;
    }
}


