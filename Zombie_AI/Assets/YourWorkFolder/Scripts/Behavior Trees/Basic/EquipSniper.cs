using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EquipSniper : Task
{
    public override TASK_RETURN_STATUS Run(Survivor_AI sAI)
    {
        TASK_RETURN_STATUS output = TASK_RETURN_STATUS.FAILURE;

        int sniperAmmo = GameManager.GetAmmo(WEAPON_TYPE.SNIPER);

        if (sniperAmmo > 0)
        {
            output = TASK_RETURN_STATUS.SUCCESS;
            sAI.SwitchWeapon(WEAPON_TYPE.SNIPER);
        }

        return output;
    }
}