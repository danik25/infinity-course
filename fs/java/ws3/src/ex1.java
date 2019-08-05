
public class ex1 
{
	public static void main(String[] args) 
	{
		//class1 obj1 = new class1();
		//class2 obj2 = new class2(5);
		//class2 obj3 = new class3();
	}		
}

class class1
{
	class1()
	{
		System.out.println("new class 1");
	}
}

class class2
{
	class2(int a)
	{
		System.out.println("new class 2, with:" + a);
	}
}

class class3 extends class2
{
	
	class3()
	{
		super(6);
		System.out.println("new class 3");
	}
	
	{
		System.out.println("initialization block");
	}
}
