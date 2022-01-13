using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovePlayer : Task
{
    public override TASK_RETURN_STATUS Run(Survivor_AI sAI)
    {
        TASK_RETURN_STATUS output = TASK_RETURN_STATUS.SUCCESS;

        Vector3 targetPoint = sAI.transform.position + sAI.GetBlackboard().moveDirection;

        sAI.MoveTo(targetPoint);

        sAI.GetBlackboard().moveDirection = Vector3.zero;

        return output;
    }
}
