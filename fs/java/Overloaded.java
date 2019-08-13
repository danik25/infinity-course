public class Overloaded
{
    public static void main(String[] args)
    {
        foo(10);
    }
    public static void foo(short i){System.out.println("short");}

    public static void foo(int ...i){System.out.println("int");}
    
    public static void foo(Integer i){System.out.println("Integer");}
    public static void foo(long i){System.out.println("long");}
}