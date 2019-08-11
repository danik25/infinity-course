public class singletonTest
{
    public static void main(String[] args)
    {
        /*Color enum1 = Color.RED;
        Color enum2 = Color.GREEN;

        System.out.println(enum1);
        System.out.println(enum2);

        if(enum1 == enum2)
        {
            System.out.println("same");
        }*/
        
        System.out.println("no constructor, only printing. lazy");
        SimpleSingleton c1;
        SimpleSingleton.printMethod();

        System.out.println("\nconstructor ans printing. not lazy");
        NotLazySimpleSingleton c2;
        NotLazySimpleSingleton.printMethod();
        

        
    }
}

class SimpleSingleton 
{
    private static SimpleSingleton instance;
    
    private SimpleSingleton (){
        System.out.println("lazy constructor");
    }
 
    public static SimpleSingleton getInstance() 
    {
        if (instance == null) 
        {
            instance = new SimpleSingleton();
        }
        return instance;
    }

    public static void printMethod()
    {
        System.out.println("SimpleSingleton");
    }
}

class NotLazySimpleSingleton 
{
    //the variable will be created when the class is loaded 
    private static final NotLazySimpleSingleton instance = new NotLazySimpleSingleton();
    private NotLazySimpleSingleton(){
        System.out.println("not lazy constructor");
    }
    public static NotLazySimpleSingleton getInstance()
    {
        return instance;
    }

    public static void printMethod()
    {
        System.out.println("NotLazySimpleSingleton");
    }
}

class SyncSingleton 
{
    private static SyncSingleton instance;
    private SyncSingleton (){}
    public synchronized static SyncSingleton getInstance() 
    {
        if(instance == null) 
        {
            instance = new SyncSingleton();
        }
        return instance;
    }
}

class SyncCriticalSingleton  
{
    private static SyncCriticalSingleton instance;
    private SyncCriticalSingleton  (){}
    public static SyncCriticalSingleton  getInstance() 
    {
        if(instance == null) 
        {
            synchronized(SyncCriticalSingleton.class) 
            { 
                instance = new SyncCriticalSingleton();
            }
        }
        return instance;
    }
}

class DoubleLockSingleton  
{
    private static DoubleLockSingleton instance;
    private DoubleLockSingleton(){}
    public static DoubleLockSingleton getInstance() 
    {
        if(instance == null) 
        {
            synchronized(DoubleLockSingleton.class) 
            {
                if(instance == null) 
                {
                    instance = new DoubleLockSingleton();
                }
            }
        }
        return instance;
    }
}

class VolatileSingleton {
    private volatile static VolatileSingleton instance; // volatile
    private VolatileSingleton (){}
 
    public static VolatileSingleton getSingleton() 
    {
        if (instance == null) 
        {                         
            synchronized (VolatileSingleton.class) 
            {
                if (instance == null) 
                {       
                    instance = new VolatileSingleton();
                }
            }
        }
        return instance;
    }
}

// Correct lazy initialization in Java 
//@ThreadSafe
class UltimateSingleton 
{
    private static class SingletonHolder 
    {
       public static UltimateSingleton instance = new UltimateSingleton();
    }
 
    public static UltimateSingleton getInstance() 
    {
        return SingletonHolder.instance;
    }
}

enum Color 
{
    RED(1), GREEN(2), YELLOW(3);
 
    private int nCode ;
 
    private Color(int _nCode) 
    {
        System.out.println("enum cons");
        this.nCode = _nCode;
    }
 
}