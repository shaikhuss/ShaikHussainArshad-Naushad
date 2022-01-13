using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class NeedAmmo : Task
{

    public override TASK_RETURN_STATUS Run(Survivor_AI sAI)
    {
        TASK_RETURN_STATUS output = TASK_RETURN_STATUS.FAILURE;

        Loot[] ammoList = GameObject.FindObjectsOfType<Loot>();
        WEAPON_TYPE weaponType;
        Blackboard_Player blackboard = sAI.GetBlackboard();
        //int gold = GameManager.GetCurrentGold();
        float dist;
        float closestDist = Mathf.Infinity;

        foreach (Loot ammo in ammoList)
        {

            weaponType = GetWeaponForAmmo(ammo.GetLootType());

            dist = (ammo.transform.position - sAI.transform.position).magnitude;

            if (ammo.GetLootType() != LOOT_TYPE.NULL) //&& ammo.getAmmoType() != AMMOTYPE.GRENADE)
            {

                closestDist = dist;
                blackboard.nearestItem = ammo;
                output = TASK_RETURN_STATUS.SUCCESS;

            }

        }

        return output;
    }

    public WEAPON_TYPE GetWeaponForAmmo(LOOT_TYPE ammo)
    {
        WEAPON_TYPE weapon = WEAPON_TYPE.NULL;

        switch (ammo)
        {
            case LOOT_TYPE.ASSAULT:
                weapon = WEAPON_TYPE.ASSAULT;
                break;
            case LOOT_TYPE.SHOTGUN:
                weapon = WEAPON_TYPE.SHOTGUN;
                break;
            case LOOT_TYPE.SNIPER:
                weapon = WEAPON_TYPE.SNIPER;
                break;
        }

        return weapon;
    }
}
