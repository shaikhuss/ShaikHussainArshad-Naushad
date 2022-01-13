using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NeedHealth : Task
{

    public override TASK_RETURN_STATUS Run(Survivor_AI sAI)
    {
        TASK_RETURN_STATUS output = TASK_RETURN_STATUS.FAILURE;
        Blackboard_Player blackboard = sAI.GetBlackboard();
        Loot[] health = GameObject.FindObjectsOfType<Loot>();

        float dist;
        float closestDist = Mathf.Infinity;

        foreach (Loot ammo in health)
        {


            dist = (ammo.transform.position - sAI.transform.position).magnitude;

            if (ammo.GetLootType() == LOOT_TYPE.HEALTH) //&& ammo.getAmmoType() != AMMOTYPE.GRENADE)
            {

                closestDist = dist;
                blackboard.nearestItem = ammo;
                output = TASK_RETURN_STATUS.SUCCESS;

            }

        }

        return output;
    }
}
