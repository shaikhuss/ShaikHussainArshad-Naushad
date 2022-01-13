using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SetMoveDefend : Task
{
    public override TASK_RETURN_STATUS Run(Survivor_AI sAI)
    {
        TASK_RETURN_STATUS output = TASK_RETURN_STATUS.SUCCESS;

        Vector3 direction = sAI.GetBlackboard().moveTarget - sAI.transform.position;
        sAI.GetBlackboard().moveDirection = direction;

        return output;
    }
}
