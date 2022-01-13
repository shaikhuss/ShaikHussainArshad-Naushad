using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Loot : MonoBehaviour
{
    [SerializeField]
    protected LOOT_TYPE lootType;

    protected int amount;

    public void Start()
    {
        GameManager.AddLootToList(this);
    }

    public LOOT_TYPE GetLootType()
    {
        return lootType;
    }

    public void SetAmount(int value, LootSpawner spawner)
    {
        amount = value;
    }

    public int GetAmount()
    {
        return amount;
    }

    public void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.layer == LayerMask.NameToLayer("Player"))
        {
            Survivor s = other.GetComponent<Survivor>();
            GameManager.PickupLoot(this, s);

            Destroy(gameObject);
        }
    }
}
