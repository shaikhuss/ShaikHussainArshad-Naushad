using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FireAtClosest : Task
{
    public override TASK_RETURN_STATUS Run(Survivor_AI sAI)
    {
        TASK_RETURN_STATUS output = TASK_RETURN_STATUS.FAILURE;

        Enemy closestTarget = sAI.GetBlackboard().chosenTarget;

        if (closestTarget != null)
        {
            // Check Gun Range
            float gunRange = sAI.GetCurrentWeapon().getRange();
            //float distanceToTarget = (chosenTarget.transform.position - gameObject.transform.position).magnitude;
            float distanceToTarget = Vector3.Distance(closestTarget.transform.position, 
                sAI.gameObject.transform.position);

            if (distanceToTarget <= gunRange)
            {
                Vector3 heightOffset = new Vector3(0, 0.5f, 0);

                sAI.Fire(closestTarget.transform.position + heightOffset);

                output = TASK_RETURN_STATUS.SUCCESS;
            }
        }

        return output;
    }
}
