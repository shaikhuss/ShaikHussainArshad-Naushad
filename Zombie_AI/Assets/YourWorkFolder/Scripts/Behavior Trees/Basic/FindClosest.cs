using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FindClosest : Task
{
    public override TASK_RETURN_STATUS Run(Survivor_AI sAI)
    {
        // Fix this later
        TASK_RETURN_STATUS output = TASK_RETURN_STATUS.FAILURE;

        List<Enemy> bunnyList = GameManager.getZomBunnyList();
        List<Enemy> bearList = GameManager.getZomBearList();
        List<Enemy> HellList = GameManager.getHellephantList();
        //List<Enemy> ClownList = GameManager.get();

        float closestDistanceSoFar = Mathf.Infinity;
        Enemy chosenTarget = null;
        for (int i = 0; i < bunnyList.Count; i++)
        {
            Enemy e = bunnyList[i];
            Vector3 enemyPosition = e.gameObject.transform.position;
            Vector3 survivorPosition = sAI.gameObject.transform.position;

            float distanceToTarget = Vector3.Distance(enemyPosition, survivorPosition);
            if (IsTargetVisible(sAI, e))
            {
                if (distanceToTarget < closestDistanceSoFar)
                {
                    closestDistanceSoFar = distanceToTarget;
                    chosenTarget = e;

                }
            }
        }
        if (chosenTarget != null)
        {
            sAI.GetBlackboard().chosenTarget = chosenTarget;
            return output = TASK_RETURN_STATUS.SUCCESS;
        }
        for (int i = 0; i < HellList.Count; i++)
        {
            Enemy e = HellList[i];
            Vector3 enemyPosition = e.gameObject.transform.position;
            Vector3 survivorPosition = sAI.gameObject.transform.position;

            float distanceToTarget = Vector3.Distance(enemyPosition, survivorPosition);
            if (IsTargetVisible(sAI, e))
            {
                if (distanceToTarget < closestDistanceSoFar)
                {
                    closestDistanceSoFar = distanceToTarget;
                    chosenTarget = e;

                }
            }
        }
        if (chosenTarget != null)
        {
            sAI.GetBlackboard().chosenTarget = chosenTarget;
            return output = TASK_RETURN_STATUS.SUCCESS;
        }
        for (int i = 0; i < bearList.Count; i++)
        {
            Enemy e = bearList[i];
            Vector3 enemyPosition = e.gameObject.transform.position;
            Vector3 survivorPosition = sAI.gameObject.transform.position;

            float distanceToTarget = Vector3.Distance(enemyPosition, survivorPosition);
            if (IsTargetVisible(sAI, e))
            {
                if (distanceToTarget < closestDistanceSoFar)
                {
                    closestDistanceSoFar = distanceToTarget;
                    chosenTarget = e;

                }
            }
        }
        if (chosenTarget != null)
        {
            sAI.GetBlackboard().chosenTarget = chosenTarget;
            return output = TASK_RETURN_STATUS.SUCCESS;
        }

        return output;
    }
    bool isTargetVisible(Enemy e, Vector3 rayOrigin)
    {
        bool output = false;

        RaycastHit hit;
        Vector3 dir = e.transform.position - rayOrigin;
        dir.Normalize();

        if (Physics.Raycast(rayOrigin, dir, out hit, 1000.0f))
        {
            if (hit.collider.gameObject.layer == LayerMask.NameToLayer("Enemy"))
            {

                if (hit.collider.gameObject.GetInstanceID() == e.gameObject.GetInstanceID())
                {
                    output = true;
                }
            }
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
