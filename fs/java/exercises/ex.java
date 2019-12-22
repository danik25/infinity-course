import java.lang.StringBuffer;

public class ex{
    public static void main(String[] args) {
        //exs exStr = new exs();
        //exStr.strReplace();

        //Point point = new Point(1, 2);

        //base obj = new base1();
        //((base2)obj).test();
        //obj.test();

        //SomeClass someclass = new SomeClass();
        //someclass.foo();

        //Singleton<Integer> s;
        //s.getInstance();

        Sam sam = new Sam();
        sam.sayHello();
    }
}

class exs{
    void strReplace(){
        StringBuffer strBuffer = new StringBuffer("this, that, etc.!");
        System.out.println(strBuffer.replace(12, 15, "etcetera"));

        Boolean b = null;
        System.out.println(b ? true : false);
    }
}

class Point {
    private int x = 2, y;
    {
        System.out.println(x);
    }
    

    Point(int x, int y)
    {
        this(x, y, 5);
        System.out.println("const1");
        
        this.x = x;
        this.y = y;
    }
/*
    Point(){
        this(0, 0);
        System.out.println("const");
    }
*/
    Point(){
        
        //this(x, 0);
        System.out.println("const");
    }
    Point(int x, int y, int z)
    {
        super();

        System.out.println("3");
    }
}

class base{
    public void test()
    {
        System.out.println("base");
    }
}

class base1 extends base{
    @Override
    public void test()
    {
        System.out.println("base1");
    }
}

class base2 extends base{
    @Override
    public void test()
    {
        System.out.println("base2");
    }
}

interface SomeInterface{
    default void foo(){
        System.out.println("my foo");
    }
}

class SomeClass implements SomeInterface{
    //@Override
    /*public void foo()
    {
        System.out.println("my new foo");
    }*/
}
/*
class Singleton<T>{
    
    static <C> Singleton<C> getInstance(){
        if(instance == null){
            System.out.println("create nstance");
            instance = new Singleton<C>();
        }
        System.out.println("return instance");
        return instance;
    }
    private static Singleton<T> instance = null;
}*/

interface Person{
    void sayHello();
}

interface Male{
    default void sayHello(){
        System.out.println("Hi");
    }
}

class Sam implements Person, Male{
    @Override
    public void sayHello()
    {
        System.out.println("sam");
    }
}