using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChooseTarget : Task
{
    public override TASK_RETURN_STATUS Run(Survivor_AI sAI)
    {

        TASK_RETURN_STATUS output = TASK_RETURN_STATUS.FAILURE;
        /*
        Blackboard_Player blackboard = sAI.GetBlackboard();

        Enemy closestBunny = blackboard.closestZombunny;
        Enemy closestBear = blackboard.closestBear;

        if(IsTargetVisible(sAI, closestBear))
        {
            blackboard.chosenTarget = closestBear;
            output = TASK_RETURN_STATUS.SUCCESS;
        }
        else if(IsTargetVisible(sAI, closestBunny))
        {
            blackboard.chosenTarget = closestBunny;
            output = TASK_RETURN_STATUS.SUCCESS;
        }

        */

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
