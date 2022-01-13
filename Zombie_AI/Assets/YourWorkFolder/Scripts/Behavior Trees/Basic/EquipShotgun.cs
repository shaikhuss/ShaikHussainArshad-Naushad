using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EquipShotgun : Task
{
    public override TASK_RETURN_STATUS Run(Survivor_AI sAI)
    {
        TASK_RETURN_STATUS output = TASK_RETURN_STATUS.FAILURE;

        int shottyAmmo = GameManager.GetAmmo(WEAPON_TYPE.SHOTGUN);

        if (shottyAmmo > 0)
        {
            output = TASK_RETURN_STATUS.SUCCESS;
            sAI.SwitchWeapon(WEAPON_TYPE.SHOTGUN);
        }

        return output;
    }
}
