using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ReachedDefend : Task
{
    public override TASK_RETURN_STATUS Run(Survivor_AI sAI)
    {
        TASK_RETURN_STATUS output = TASK_RETURN_STATUS.FAILURE;

        Vector3 targetPoint = sAI.GetBlackboard().moveTarget;

        float distanceToTarget = Vector3.Distance(targetPoint, sAI.transform.position);

        if (distanceToTarget < 2)
        {
            output = TASK_RETURN_STATUS.SUCCESS;
        }

        return output;
    }
}
