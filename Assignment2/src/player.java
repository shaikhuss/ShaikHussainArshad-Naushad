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
	public seLinkList findMaxWeight()
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
		return max;
		//System.out.printf("Max weight player Node Index: %d a:%d b:%d c:%d Weight:%d",max.index,max.a,max.b,max.c, maxWeight);
	}
	
	public seLinkList findMinWeight()
	{
		int minWeight = 99999;
		if(size==0)
		{
			return null;	
		}
		else if(size<2)
		{
			return head;
		}
		seLinkList tmp = head;
		seLinkList min = tmp;
		for(int i =0;i<size;i++)
		{
		int k = tmp.a+tmp.b+tmp.c;
		if(k<minWeight)
		{
			minWeight = k;
			min = tmp;
		}
		tmp = tmp.next;
		}
		return min;
	}
	
	public seLinkList[] findMinMaxWeight()
	{
		
		int minWeight = 99999;
		int maxWeight = 0;
		seLinkList tmp = head;
		seLinkList min = tmp;
		seLinkList max = tmp;
		for(int i =0;i<size;i++)
		{
		int k = tmp.a+tmp.b+tmp.c;
		
		if(k<minWeight)
		{
			minWeight = k;
			min = tmp;
		}
		if(k>maxWeight)
		{
			maxWeight = k;
			max = tmp;
		}
		tmp = tmp.next;
		}
		return new seLinkList[]{min,max};
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
