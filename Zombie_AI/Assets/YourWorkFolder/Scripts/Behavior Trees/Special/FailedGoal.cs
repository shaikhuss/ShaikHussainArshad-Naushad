using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FailedGoal : Task
{
    public override TASK_RETURN_STATUS Run(Survivor_AI sAI)
    {
        TASK_RETURN_STATUS output = TASK_RETURN_STATUS.FAILURE;

        GameObject hiveMindObj = GameObject.FindGameObjectWithTag("HiveMind");

        Hivemind hivemind = hiveMindObj.GetComponent<Hivemind>();
        hivemind.GoalCompleted(sAI, sAI.GetBlackboard().currentGoal);

        return output;
    }
}
