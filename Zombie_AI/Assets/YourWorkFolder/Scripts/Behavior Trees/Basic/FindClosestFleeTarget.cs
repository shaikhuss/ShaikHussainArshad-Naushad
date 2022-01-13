using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FindClosestFleeTarget : Task
{
    public override TASK_RETURN_STATUS Run(Survivor_AI sAI)
    {
        // Fix this later
        TASK_RETURN_STATUS output = TASK_RETURN_STATUS.FAILURE;

        List<Enemy> enemyList = GameManager.getAllEnemies();

        float closestDistanceSoFar = Mathf.Infinity;
        Enemy closestEnemy = null;

        for (int i = 0; i < enemyList.Count; i++)
        {
            Enemy e = enemyList[i];
            Vector3 enemyPosition = e.gameObject.transform.position;
            Vector3 survivorPosition = sAI.gameObject.transform.position;

            float distanceToTarget = Vector3.Distance(enemyPosition, survivorPosition);

            if (distanceToTarget < closestDistanceSoFar)
            {
                closestDistanceSoFar = distanceToTarget;
                closestEnemy = e;

            }
        }

        if (closestEnemy != null)
        {
            output = TASK_RETURN_STATUS.SUCCESS;

            sAI.GetBlackboard().fleeTarget = closestEnemy.transform.position;
        }


        return output;
    }
}
