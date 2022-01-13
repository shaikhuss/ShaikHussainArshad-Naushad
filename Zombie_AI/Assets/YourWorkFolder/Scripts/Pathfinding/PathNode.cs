using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PathNode : MonoBehaviour
{
    public List<PathNode> neighbors;

    public float maxDistanceToNeighbor;
    public LayerMask neighborMask;

    public LayerMask enemyMask;
    public float enemyDetectionRadius;

    public float defensiveValue;

    public PathNode parent;
    public float FScore;

    // Start is called before the first frame update
    void Start()
    {
        neighbors = new List<PathNode>();

        FindMyNeighbors();
    }

    // Update is called once per frame
    void Update()
    {
        FindNearbyEnemies();

        Debug_DrawNeighbors();
    }

    void FindMyNeighbors()
    {
        PathNode[] allNodes = GameObject.FindObjectsOfType<PathNode>();

        for(int i = 0; i < allNodes.Length; i++)
        {
            PathNode node = allNodes[i];

            if (node.GetInstanceID() != this.GetInstanceID())
            {
                RaycastHit hitInfo;

                Vector3 origin = transform.position;
                Vector3 direction = node.transform.position - gameObject.transform.position;
                float distance = direction.magnitude;

                if (distance <= maxDistanceToNeighbor)
                {
                    direction.Normalize();

                    bool hit = Physics.Raycast(origin, direction, out hitInfo, distance, neighborMask);

                    if (hit)
                    {
                        // Do Nothing
                    }
                    else
                    {
                        neighbors.Add(node);
                    }
                }
            }
        }

    }

    void Debug_DrawNeighbors()
    {
        for(int i = 0; i < neighbors.Count; i++)
        {
            Vector3 neighborPos = neighbors[i].transform.position;

            Debug.DrawLine(neighborPos, transform.position, Color.blue);
        }
    }

    void FindNearbyEnemies()
    {
        Collider[] hits = Physics.OverlapSphere(transform.position, enemyDetectionRadius,
            enemyMask);

        for(int i = 0; i < hits.Length; i++)
        {
            GameObject enemy = hits[i].gameObject;

            Debug.Log(enemy.name);

        }
    }



}
