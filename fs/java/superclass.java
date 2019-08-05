public class superclass
{
    public static void main(String[] args)
    {
        /*subclass obj = new subclass();
        obj.method1();
        System.out.println(obj.var);
        System.out.println(subclass.var2);
        
        ((superclass)obj).method1();*/

        superclass obj2 = new superclass();
        obj2.method1();
        obj2.method1(5);
    }
    final int var = 5;
    static int var2 = 7;

    final void method1()
    {
        System.out.println("final superclass");
    }

    void method1(int x)
    {
        System.out.println(x);
    }
}

class subclass extends superclass
{
    /*
    void method1()
    {
        System.out.println("static subclass");
    }*/
}