using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SurvivorOverrun : Task
{
    public override TASK_RETURN_STATUS Run(Survivor_AI sAI)
    {
        TASK_RETURN_STATUS output = TASK_RETURN_STATUS.FAILURE;

        Collider[] hits = Physics.OverlapSphere(sAI.transform.position, sAI.overrunDistance, sAI.enemyMask);

        if(hits.Length >= sAI.overrunCount)
        {
            output = TASK_RETURN_STATUS.SUCCESS;
        }
        
        return output;
    }
}
