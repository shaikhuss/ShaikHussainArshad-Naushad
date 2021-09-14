import java.util.Scanner;
class Assignment1{
    static void fibo(int n)
    {
        int num1 = 0, num2 = 1;
        int counter = 0;
        while (counter < n) {
            System.out.print(num1 + " ");
            int num3 = num2 + num1;
            num1 = num2;
            num2 = num3;
            counter = counter + 1;
        }
    }
  
    public static void main(String args[])
    {
       int num;
       Scanner in = new Scanner(System.in);
       System.out.println("Enter an integer: ");
       num = in.nextInt();
        fibo(num);
    }
}