import java.lang.reflect.*;
import java.lang.*;
import java.util.*;

public class reflectionTest
{
    public static void main(String[] args)
    {
    	System.out.println("ancestor:");
    	Foo a = new Foo();

    	Class <?> c = a.getClass();
    	while(c.getSuperclass() != null)
    	{
    		System.out.println(c.getSuperclass());
    		c = c.getSuperclass();
    	}
    	
    	c = a.getClass();
    	System.out.println("\nmodifiers:");
    	String retval = Modifier.toString(c.getModifiers());
    	System.out.println(retval);

    	System.out.println("\ninterfaces:");
    	System.out.println(Arrays.asList(c.getInterfaces()));

    	c = a.getClass();
    	System.out.println("\nfields:");
    	Field f[] = c.getFields();
         for (int i = 0; i < f.length; i++) {
            System.out.println(f[i]);
        }

        System.out.println("\ncreating new instance:");
        try {
        	Object obj = c.newInstance();
        	System.out.println(obj);
        }catch (Exception e) {
         System.out.println("Exception: " + e);
     }
     try {
     	System.out.println("\ncalling f1:");
     	Method m = Foo.class.getMethod("f1");
     	Foo foo = new Foo();
     	m.invoke(foo);
     }catch (Exception e) {
         System.out.println("Exception: " + e);
     }
    }
}


interface fooInterface
{
	public void abstractMethod();
}

class fooParent{
	;
}
class Foo extends fooParent implements fooInterface{
	private int x;
	Foo()
	{
		//System.out.println("no arguments constructor");
		x = 0;
	}
	Foo(int x)
	{
		this.x = x;
		System.out.println("arguments constructor: " + x);
	}

	public int getX()
	{
		return x;
	}
	public void f1()
	{
		privateMethod();
		System.out.println("i am f1");
	}
	private void privateMethod()
	{
		System.out.println("i am private");
	}

	public static void staticMethod()
	{
		System.out.println("i am static");
	}
	@Override
	public void abstractMethod()
	{
		System.out.println("i am interface implementation");
	}
	@Override
	public String toString()
	{
		return("foo!!!!!");
	}
}