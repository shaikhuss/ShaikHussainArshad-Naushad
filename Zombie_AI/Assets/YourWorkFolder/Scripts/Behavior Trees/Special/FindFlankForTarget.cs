using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FindFlankForTarget : Task
{
    public override TASK_RETURN_STATUS Run(Survivor_AI sAI)
    {
        TASK_RETURN_STATUS output = TASK_RETURN_STATUS.SUCCESS;

        Blackboard_Player blackboard = sAI.GetBlackboard();
        Enemy target = blackboard.chosenTarget;

        if(target != null)
        {
            if(IsTargetVisible(sAI, target))
            {
                // Current position is fine
                

            }
            else
            {
                // Find a new position
                PathNode node = PathFinder.FindClosetNodeToTarget(target.transform.position);

                Vector3 directionToNode = node.transform.position - sAI.transform.position;
                directionToNode.Normalize();

                sAI.GetBlackboard().moveDirection += directionToNode;
            }
        }



        return output;
    }


    bool IsTargetVisible(Survivor_AI sAI, Enemy target)
    {
        bool output = false;

        if (target != null)
        {

            Vector3 heightOffset = new Vector3(0, 0.5f, 0);

            Vector3 origin = sAI.transform.position + heightOffset;
            Vector3 direction = target.transform.position - sAI.transform.position;
            direction.Normalize();

            RaycastHit hitInfo;

            bool hit = Physics.Raycast(origin, direction, out hitInfo, 200);

            if (hit == true)
            {
                GameObject objHit = hitInfo.collider.gameObject;

                Enemy enemy = objHit.GetComponent<Enemy>();

                if (enemy != null)
                {
                    if (enemy.GetInstanceID() == target.GetInstanceID())
                    {
                        output = true;
                    }
                }
            }
        }
        return output;
    }
}
