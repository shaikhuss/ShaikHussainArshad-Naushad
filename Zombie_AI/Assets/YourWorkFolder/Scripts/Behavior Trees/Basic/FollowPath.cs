using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FollowPath : Task
{

    public override TASK_RETURN_STATUS Run(Survivor_AI sAI)
    {
        TASK_RETURN_STATUS output = TASK_RETURN_STATUS.FAILURE;

        Blackboard_Player blackBoard = sAI.GetBlackboard();

        PathNode currentNode = blackBoard.currentPath[0];

        if (currentNode != null)
        { 
            // Test to see if you have arrived at node
            float distanceToCurrentNode = Vector3.Distance(currentNode.transform.position,
                sAI.transform.position);

            if (distanceToCurrentNode < 5.0f)
            {
                blackBoard.currentPath.RemoveAt(0);

                if (blackBoard.currentPath.Count > 0)
                {
                    currentNode = blackBoard.currentPath[0];
                }
                else
                {
                    // We have arrived at the last node
                    output = TASK_RETURN_STATUS.SUCCESS;
                }

            }
        }

        if (currentNode != null)
        {
            Vector3 direction = currentNode.transform.position
                - sAI.transform.position;

            direction.Normalize();

            blackBoard.moveDirection += direction;
        }

        return output;
    }


}
