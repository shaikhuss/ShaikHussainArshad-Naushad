using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FireAtTarget : Task
{
    public override TASK_RETURN_STATUS Run(Survivor_AI sAI)
    {
        TASK_RETURN_STATUS output = TASK_RETURN_STATUS.FAILURE;

        Enemy chosenTarget = sAI.GetBlackboard().chosenTarget;

        if (chosenTarget != null)
        {
            //if (IsTargetVisible(sAI, chosenTarget))
           // {
                // Check Gun Range
                float gunRange = sAI.GetCurrentWeapon().getRange();
                //float distanceToTarget = (chosenTarget.transform.position - gameObject.transform.position).magnitude;
                float distanceToTarget = Vector3.Distance(chosenTarget.transform.position,
                    sAI.gameObject.transform.position);

                if (distanceToTarget <= gunRange)
                {
                    Vector3 heightOffset = new Vector3(0, 0.5f, 0);

                    sAI.Fire(chosenTarget.transform.position + heightOffset);

                    output = TASK_RETURN_STATUS.SUCCESS;
                }
           // }
        }

        return output;
    }

    bool IsTargetVisible(Survivor_AI sAI, Enemy target)
    {
        bool output = false;

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

            if(enemy != null)
            {
                if(enemy.GetInstanceID() == target.GetInstanceID())
                {
                    output = true;
                }
            }
        }
        return output;
    }
}
