using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ChooseWeapon : Task
{
    public override TASK_RETURN_STATUS Run(Survivor_AI sAI)
    {
        TASK_RETURN_STATUS output = TASK_RETURN_STATUS.FAILURE;

        Blackboard_Player blackboard = sAI.GetBlackboard();
        Survivor s = blackboard.survivor;
        Enemy e = blackboard.chosenTarget;

        Collider[] hits = Physics.OverlapSphere(sAI.transform.position, sAI.overrunDistance, sAI.enemyMask);

        // if (hits.Length >= sAI.overrunCount)
        // {
        //float enemyDist = (e.transform.position - s.transform.position).magnitude;

        //Enemy chosenTarget = sAI.GetBlackboard().chosenTarget;

        if (e != null)
        {
            EnemyType eType = e.GetEnemyType();

            if (GameManager.GetAmmo(WEAPON_TYPE.SHOTGUN) > 0 && hits.Length >= sAI.overrunCount) //&& GameManager.GetAmmo(WEAPON_TYPE.ASSAULT) < 1 && GameManager.GetAmmo(WEAPON_TYPE.SNIPER) < 1)
            {
                sAI.SwitchWeapon(WEAPON_TYPE.SHOTGUN);
            }
            else if ((eType == EnemyType.ZOMBEAR && GameManager.GetAmmo(WEAPON_TYPE.SNIPER) > 0) || eType == EnemyType.HELLEPHANT && GameManager.GetAmmo(WEAPON_TYPE.SNIPER) > 0)
            {

                sAI.SwitchWeapon(WEAPON_TYPE.SNIPER);

            }
            else if ((eType == EnemyType.CLOWN && GameManager.GetAmmo(WEAPON_TYPE.ASSAULT) > 0 || eType == EnemyType.ZOMBEAR && GameManager.GetAmmo(WEAPON_TYPE.ASSAULT) > 0) || (eType == EnemyType.HELLEPHANT && GameManager.GetAmmo(WEAPON_TYPE.ASSAULT) > 0))
            {
                sAI.SwitchWeapon(WEAPON_TYPE.ASSAULT);
            }
            else
            {
                sAI.SwitchWeapon(WEAPON_TYPE.PISTOL);
            }

            output = TASK_RETURN_STATUS.SUCCESS;
        }

        return output;
    }


}
