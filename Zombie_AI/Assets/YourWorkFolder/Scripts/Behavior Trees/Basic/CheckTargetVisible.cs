using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CheckTargetVisible : Task
{
    public override TASK_RETURN_STATUS Run(Survivor_AI sAI)
    {
        TASK_RETURN_STATUS output = TASK_RETURN_STATUS.FAILURE;

        Enemy chosenTarget = sAI.GetBlackboard().chosenTarget;

        if(IsTargetVisible(sAI, chosenTarget))
        {
            output = TASK_RETURN_STATUS.SUCCESS;
        }


        return output;
    }

    bool IsTargetVisible(Survivor_AI sAI, Enemy target)
    {
        bool output = false;

        if (target != null)
        {

            Vector3 heightOffset = new Vector3(0, 0.5f, 0);

            Vector3 origin = sAI.GetCurrentWeapon().transform.position;
            Vector3 direction = target.transform.position - sAI.GetCurrentWeapon().transform.position;
            direction.Normalize();


            RaycastHit[] hitInfos = Physics.RaycastAll(origin, direction, 200, sAI.visibiltyMask);

            if (hitInfos.Length > 0)
            {
                List<RaycastHit> sortedHits = SortHitListByDistance(hitInfos);

                for (int i = 0; i < sortedHits.Count; i++)
                {
                    GameObject objHit = sortedHits[i].collider.gameObject;

                    Enemy enemy = objHit.GetComponent<Enemy>();

                    if (enemy != null)
                    {
                        if (enemy.GetInstanceID() == target.GetInstanceID())
                        {
                            output = true;
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
        return output;
    }

    List<RaycastHit> SortHitListByDistance(RaycastHit[] hits)
    {
        List<RaycastHit> output = new List<RaycastHit>();

        foreach (RaycastHit hit in hits)
        {
            output.Add(hit);
        }

        output.Sort(SortByDistance);

        return output;

    }

    static int SortByDistance(RaycastHit hit1, RaycastHit hit2)
    {
        return hit1.distance.CompareTo(hit2.distance);
    }

}
