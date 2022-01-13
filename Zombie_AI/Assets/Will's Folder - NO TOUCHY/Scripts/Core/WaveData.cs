using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum WAVE_TYPE
{
    ZOMBUNNY,
    ZOMBEAR
}

[System.Serializable]
public class EnemyWaveData
{
    public EnemySubWaveData[] subWaves;
    public float timeBetweenSubWaves;
}

[System.Serializable]
public class EnemySubWaveData
{
    public Transform[] spawnPoints;
    public int ZomBunniesPerPoint;
    public int ZomBearsPerPoint;
    public int HellephantPerPoint;
    public int ClownPerPoint;
    public int SheepPerPoint;
}
