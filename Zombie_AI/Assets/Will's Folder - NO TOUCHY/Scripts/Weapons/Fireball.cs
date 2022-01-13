using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Fireball : Projectile {

    [SerializeField]
    GameObject explosionPrefab;
    [SerializeField]
    LayerMask targetMask;
    [SerializeField]
    float explosionRadius;

	// Use this for initialization
	void Start () {
		
	}

    public float GetExplosionRadius()
    {
        return explosionRadius;
    }


    private void OnCollisionEnter(Collision collision)
    {
        Instantiate(explosionPrefab, transform.position, Quaternion.identity);

        Explode();

        Destroy(gameObject);
    }

    void Explode()
    {
        Collider[] cols = Physics.OverlapSphere(transform.position, explosionRadius, targetMask);

        foreach(Collider c in cols)
        {
            Entity e = c.GetComponent<Entity>();
            if(e != null)
            {
                e.OnHit(this);
            }

        }

    }



}
