class Assignment2{
    public static void main(String args[])
    {
     System.out.println("Shaik hussain Arshad Naushad-Git Assignment");
       player obj = new player();
       seLinkList minmax[];
       minmax = obj.findMinMaxWeight();
       //System.out.printf("Min Weight is %d th node & Max Weight is %d th node", minmax[0].index,minmax[1].index);
       obj.removeNode(minmax[0].index);
       obj.removeNode(minmax[1].index);
       System.out.println("Done");
    }
}

