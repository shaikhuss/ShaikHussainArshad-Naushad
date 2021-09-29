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
	public void initializeList()
	{
		System.out.println("Task8");
		 for(int i=0;i<size;i++)
		 {
			addPlayer();
		    tail.a = myData[i].a;
		    tail.b = myData[i].b;
		    tail.c = myData[i].c;
		 }
	}
	
}
