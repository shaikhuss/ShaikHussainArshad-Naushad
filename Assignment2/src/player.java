public class player
{
	public
	seLinkList head = null;
	seLinkList tail = null;
	int size = 0;
	PlayerData[] myData;
	player()
	{
		size = numPlayers();
	   initializeList();
	   
	}
	public int numPlayers()
	{
	    PlayerData obj4 = new PlayerData();
	    myData = obj4.getMyData();
	    int num = myData.length;
		return num;
	}
	public void addPlayer()
	{
		seLinkList tmp;
		if(head==null)
		{
			tmp = new seLinkList();
			head = tmp;
			tail = head;
		}
		else {
			tmp = new seLinkList();
			tail.next = tmp;
			tail = tmp;
		}
	}
	public void findMaxWeight()
	{
		int maxWeight = 0;
		seLinkList tmp = head;
		seLinkList max = tmp;
		for(int i =0;i<size;i++)
		{
		int k = tmp.a+tmp.b+tmp.c;
		if(k>maxWeight)
		{
			maxWeight = k;
			max = tmp;
		}
		tmp = tmp.next;
		}
		System.out.printf("Max weight player Node Index: %d a:%d b:%d c:%d Weight:%d",max.index,max.a,max.b,max.c, maxWeight);
	}
	public void initializeList()
	{
		
		 for(int i=0;i<size;i++)
		 {
			addPlayer();
		    tail.a = myData[i].a;
		    tail.b = myData[i].b;
		    tail.c = myData[i].c;
		    tail.index = i;
		 }
	}
	
}
