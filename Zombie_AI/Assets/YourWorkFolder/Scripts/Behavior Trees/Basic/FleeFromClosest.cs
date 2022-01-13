using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FleeFromClosest : Task
{
    public override TASK_RETURN_STATUS Run(Survivor_AI sAI)
    {
        TASK_RETURN_STATUS output = TASK_RETURN_STATUS.SUCCESS;

        Vector3 fleeTarget = sAI.GetBlackboard().fleeTarget;

        Vector3 survivorPosition = sAI.gameObject.transform.position;


        float distanceAway = Vector3.Distance(fleeTarget, survivorPosition);

        if (distanceAway < sAI.fleeDistance)
        {
            // RUN!!!!!
            Vector3 fleeDirection = survivorPosition - fleeTarget;
            fleeDirection.Normalize();

            fleeDirection *= sAI.fleeSpeed;

            //sAI.MoveTo(survivorPosition + fleeDirection);

            sAI.GetBlackboard().moveDirection += fleeDirection;

           
        }

        sAI.GetBlackboard().fleeTarget = Vector3.zero;

        return output;
    }
}
