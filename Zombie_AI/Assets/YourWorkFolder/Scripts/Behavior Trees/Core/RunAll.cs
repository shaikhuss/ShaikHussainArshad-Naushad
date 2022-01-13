using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RunAll : Task
{
    public override TASK_RETURN_STATUS Run(Survivor_AI sAI)
    {
        TASK_RETURN_STATUS output = TASK_RETURN_STATUS.SUCCESS;

        for (int i = 0; i < children.Count; i++)
        {
            Task child = children[i];

            child.Run(sAI);
        }

        return output;
    }

}
