using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SetMoveTarget : Task
{
    public override TASK_RETURN_STATUS Run(Survivor_AI sAI)
    {
        TASK_RETURN_STATUS output = TASK_RETURN_STATUS.SUCCESS;
        int i = sAI.GetBlackboard().k;

        sAI.GetBlackboard().moveTarget = sAI.GetBlackboard().graph[i].transform.position;
        sAI.GetBlackboard().currentGoal = "MoveToUpperPoint";
        //sAI.SetMoveMode(BT_DefaultFind);

        Vector3 direction = sAI.GetBlackboard().moveTarget - sAI.transform.position;
        sAI.GetBlackboard().moveDirection = direction;

        return output;
    }
}
