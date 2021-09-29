class Assignment2{
    public static void main(String args[])
    {
     
       player obj = new player();
       seLinkList max = obj.findMaxWeight();
       seLinkList min = obj.findMinWeight();
       System.out.printf("Max Weight is %d node", max.index);
       System.out.printf("\nMin Weight is %d node", min.index);
    }
}

