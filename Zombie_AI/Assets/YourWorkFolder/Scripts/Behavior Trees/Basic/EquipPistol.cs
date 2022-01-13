using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EquipPistol : Task
{
    public override TASK_RETURN_STATUS Run(Survivor_AI sAI)
    {
        TASK_RETURN_STATUS output = TASK_RETURN_STATUS.SUCCESS;

        sAI.SwitchWeapon(WEAPON_TYPE.PISTOL);

        return output;
    }
}
