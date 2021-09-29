class Assignment2{
    public static void main(String args[])
    {
     
       player obj = new player();
       seLinkList minmax[];
       minmax = obj.findMinMaxWeight();
       System.out.printf("Min Weight is %d th node & Max Weight is %d th node", minmax[0].index,minmax[1].index);
      
    }
}

