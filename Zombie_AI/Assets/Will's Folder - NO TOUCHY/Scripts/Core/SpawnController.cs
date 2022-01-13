using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SpawnController : MonoBehaviour
{ 
    //public Transform[] spawnAreas;

    public GameObject zomBunnyPrefab;
    public GameObject zombBearPrefab;
    public GameObject hellephantPrefab;
    public GameObject clownPrefab;
    public GameObject sheepPrefab;

    public EnemyWaveData[] Waves;
    private EnemyWaveData currentWave;
    private int waveCounter;

    //public float difficultyHealthMultiplier = 1.0f;

    public float breakTimeLength;
    private float breakTimeCounter;

    private bool waveInProgress;
    private bool inBreakBetweenWave;
    private int subWaveCounter;
    private int maxSubWave;

    bool allWavesComplete;

    private GameManager gameMan;
    // Start is called before the first frame update
    void Start()
    {
        if (Waves.Length > 0)
        {
            currentWave = Waves[0];
        }

        gameMan = gameObject.GetComponentInParent<GameManager>();
    }

    // Update is called once per frame
    void Update()
    {
        if(inBreakBetweenWave)
        {
            breakTimeCounter -= Time.deltaTime;

            if(breakTimeCounter < 0)
            {
                inBreakBetweenWave = false;
                StartNewWave();
            }
        }

        if(Input.GetKeyDown(KeyCode.H))
        {
            CompletedAllWaves();
        }

    }

    public void StartNewWave()
    {
        if (allWavesComplete == false)
        {
            waveInProgress = true;
            waveCounter += 1;

            subWaveCounter = 0;

            if (currentWave != null)
            {
                maxSubWave = currentWave.subWaves.Length;

                if (subWaveCounter < maxSubWave)
                {
                    SpawnWave(currentWave.subWaves[subWaveCounter]);
                    subWaveCounter += 1;
                    Invoke("SpawnNextSubWave", currentWave.timeBetweenSubWaves);
                }
            }
            else
            {
                WaveComplete();
            }
        }
    }

    void SpawnNextSubWave()
    {
        gameMan.SubWaveCompleted.Invoke();

        if (subWaveCounter < maxSubWave)
        {
            subWaveCounter += 1;
            SpawnWave(currentWave.subWaves[subWaveCounter-1]);
            Invoke("SpawnNextSubWave", currentWave.timeBetweenSubWaves);
        }
        else
        {
            gameMan.WaveCompleted.Invoke();
            WaveComplete();
        }
    }

    void WaveComplete()
    {
        waveInProgress = false;

        if(waveCounter < Waves.Length)
        {
            currentWave = Waves[waveCounter];
            inBreakBetweenWave = true;
            breakTimeCounter = breakTimeLength;
            
        }
        else
        {
            gameMan.AllWavesCompleted.Invoke();
            CompletedAllWaves();

        }

        gameMan.BreakEvent.Invoke();
    }

    void CompletedAllWaves()
    {
        allWavesComplete = true;
        GameManager.AllWavesComplete(this);
    }

    public bool AreAllWavesComplete()
    {
        return allWavesComplete;
    }

    void SpawnWave(EnemySubWaveData data)
    {
        for (int j = 0; j < data.spawnPoints.Length; j++)
        {
            for (int i = 0; i < data.ZomBunniesPerPoint; i++)
            {
                SpawnZombie(data.spawnPoints[j], zomBunnyPrefab);
            }
            for (int i = 0; i < data.ZomBearsPerPoint; i++)
            {
                SpawnZombie(data.spawnPoints[j], zombBearPrefab);
            }
            for (int i = 0; i < data.HellephantPerPoint; i++)
            {
                SpawnZombie(data.spawnPoints[j], hellephantPrefab);
            }
            for (int i = 0; i < data.ClownPerPoint; i++)
            {
                SpawnZombie(data.spawnPoints[j], clownPrefab);
            }
            for (int i = 0; i < data.SheepPerPoint; i++)
            {
                SpawnZombie(data.spawnPoints[j], sheepPrefab);
            }
        }
    }

    void SpawnZombie(Transform spawnPoint, GameObject enemyPrefab)
    {
        Vector3 pos = spawnPoint.position;

        // Spawn Bunnies
        GameObject obj = Instantiate(enemyPrefab, pos, Quaternion.identity);
        Enemy e = obj.GetComponent<Enemy>();
        GameManager.AddEnemy(e);
    }

    public bool isBreakInProgress()
    {
        return inBreakBetweenWave;
    }

    public float GetTimeLeftInBreak()
    {
        return breakTimeCounter;
    }

    public bool isWaveInProgress()
    {
        return waveInProgress;
    }
   
    public int GetWaveCount()
    {
        return waveCounter;
    }
}
