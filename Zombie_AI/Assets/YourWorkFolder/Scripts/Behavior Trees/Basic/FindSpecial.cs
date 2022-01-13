using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FindSpecial : Task
{
    public override TASK_RETURN_STATUS Run(Survivor_AI sAI)
    {
        TASK_RETURN_STATUS output = TASK_RETURN_STATUS.FAILURE;

        Enemy zomBear = FindClosestSpecialByType(EnemyType.ZOMBEAR, sAI);

        if (zomBear != null)
        {
            //sAI.GetBlackboard().closestBear = zomBear;
            output = TASK_RETURN_STATUS.SUCCESS;
        }
        
        return output;
    }



    Enemy FindClosestSpecialByType(EnemyType eType, Survivor_AI sAI)
    {
        Enemy output = null;

        switch(eType)
        {
            case EnemyType.ZOMBEAR:
                output = FindClosestFromList(GameManager.getZomBearList(), sAI);
                break;

            default:
                break;
        }

        return output;
    }


    // Note: Not Checking if target is in range of gun
    Enemy FindClosestFromList(List<Enemy> enemyList, Survivor_AI sAI)
    {
        Enemy output = null;

        float closestDistanceSoFar = Mathf.Infinity;

        for (int i = 0; i < enemyList.Count; i++)
        {
            Enemy e = enemyList[i];
            Vector3 enemyPosition = e.gameObject.transform.position;
            Vector3 survivorPosition = sAI.gameObject.transform.position;

            float distanceToTarget = Vector3.Distance(enemyPosition, survivorPosition);

            if (distanceToTarget < closestDistanceSoFar)
            {
                closestDistanceSoFar = distanceToTarget;
                output = e;

            }
        }

        return output;
    }

}
