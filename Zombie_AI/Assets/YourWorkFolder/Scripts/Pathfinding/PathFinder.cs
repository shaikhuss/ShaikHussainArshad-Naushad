using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PathFinder : MonoBehaviour
{
    PathNode[] pathNodes;

    private static PathFinder instance;


    void Awake()
    {
        if (instance == null)
        {
            instance = this;
        }
        else
        {
            DestroyImmediate(gameObject);
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        pathNodes = GameObject.FindObjectsOfType<PathNode>();


    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public static PathNode FindClosetNodeToTarget(Vector3 point)
    {
        PathNode output = null;

        float closestDistance = Mathf.Infinity;
        PathNode closestSoFar = null;

        for(int i = 0; i < instance.pathNodes.Length; i++)
        {
            PathNode node = instance.pathNodes[i];

            float distance = Vector3.Distance(point, node.transform.position);

            if(distance < closestDistance)
            {
                closestDistance = distance;
                closestSoFar = node;
            }
        }

        if(closestSoFar != null)
        {
            output = closestSoFar;
        }

        return output;
    }


    public static List<PathNode> GetPathToPoint(Vector3 dest, Vector3 survivorPos)
    {
        List<PathNode> path = new List<PathNode>();

        if(instance.pathNodes != null)
        {
            PathNode startNode = FindClosetNodeToTarget(survivorPos);

            List<PathNode> open = new List<PathNode>();
            List<PathNode> closed = new List<PathNode>();

            instance.ClearParents();
            instance.ClearFScore();

            if(startNode != null)
            {
                startNode.FScore = instance.CalculateFScore(startNode, startNode.transform.position, dest);
                //startNode.parent = startNode;
                instance.AddNodeByFScore(ref open, startNode, startNode.transform.position, dest);
                

                PathNode currentNode = open[0];

                while(open.Count > 0)
                {
                    currentNode = open[0];
                    open.RemoveAt(0);

                    closed.Add(currentNode);

                    if(instance.isTargetNode(currentNode, dest))
                    {
                        break;
                    }

                    List<PathNode> neighbors = currentNode.neighbors;

                    for(int i = 0; i < neighbors.Count; i++)
                    {
                        PathNode temp = neighbors[i];

                        if(closed.Contains(temp) == false)
                        {
                            if(open.Contains(temp) == true)
                            {
                                float newFScore = instance.CalculateFScore(temp, startNode.transform.position, dest);
                                if(newFScore < temp.FScore)
                                {
                                    temp.parent = currentNode;
                                    temp.FScore = newFScore;
                                }
                            }
                            else
                            {
                                temp.parent = currentNode;
                                instance.AddNodeByFScore(ref open, temp, startNode.transform.position, dest);
                            }
                        }
                    }
                }

                PathNode t = currentNode;

                while (t != null)
                {
                    path.Insert(0, t);
                    t = t.parent;
                }
            }
        }


        return path;
    }


    void ClearParents()
    {
        for (int i = 0; i < instance.pathNodes.Length; i++)
        {
            instance.pathNodes[i].parent = null;
        }
    }

    void ClearFScore()
    {
        for (int i = 0; i < instance.pathNodes.Length; i++)
        {
            instance.pathNodes[i].FScore = Mathf.Infinity;
        }
    }

    bool isTargetNode(PathNode n, Vector3 dest)
    {
        bool output = false;

        float d = Vector3.Distance(n.transform.position, dest);
        if (d < 1.0f)
        {
            output = true;
        }


        return output;
    }

    void AddNodeByFScore(ref List<PathNode> openList, PathNode p, Vector3 startPos, Vector3 targetPos)
    {
        p.FScore = CalculateFScore(p, startPos, targetPos);

        if(openList.Count > 0)
        {
            bool added = false;
            for(int i = 0; i < openList.Count; i++)
            {
                if(p.FScore < openList[i].FScore)
                {
                    openList.Insert(i, p);
                    added = true;
                    break;
                }
            }
            if(added == false)
            {
                openList.Insert(openList.Count - 1, p);
            }
        }
        else
        {
            openList.Add(p);
        }
    }

    float CalculateFScore(PathNode p, Vector3 startPos, Vector3 targetPos)
    {
        float G = (startPos - p.transform.position).magnitude;
        float H = (targetPos - p.transform.position).magnitude;

        return G + H;
    }
}
