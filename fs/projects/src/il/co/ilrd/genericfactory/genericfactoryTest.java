package il.co.ilrd.genericfactory;


//import static org.junit.jupiter.api.Assertions.*;

import java.util.function.Function;

import org.junit.jupiter.api.Test;

class genericfactoryTest 
{
	@Test
	void anonymousClassTest() 
	{
		Factory<Shape, String, String> myFactory = new Factory<>();
		myFactory.add("Circle", new Function<String, Circle>()
		{
			@Override
		    public Circle apply(String color) 
			{   
		        return new Circle(color); 
		    }
		});
		Circle c = (Circle)myFactory.create("circle", "red");
		c.method();
		System.out.println("\n");
	}
	/*
	@Test
	void lambdaTest() 
	{
		Factory<Shape, String, String> myFactory = new Factory<>();
		Function<String, Rectangle> lam = (String color)-> new Rectangle(color);
		myFactory.add("rectangle", lam);
		myFactory.create("rectangle", "green"); 
		myFactory.create("Circle", "red");
		System.out.println("\n");

	}*/
	@Test
	void lambdaTest() 
	{
		Factory<Shape, String, String> myFactory = new Factory<>();
		Function<String, Rectangle> lam = (String color)->new Rectangle(color); 
		myFactory.add("Rectangle", lam);
		myFactory.create("Rectangle", "green");
		System.out.println("\n");
	}
	
	@Test
	void inheritanceTest() 
	{
		Factory<Shape, String, String> myFactory = new Factory<>();
		squareCreator inheritFunc = new squareCreator();
		myFactory.add("square", inheritFunc);
		myFactory.create("square", "yellow");
		squareCreator creator = new squareCreator();
		myFactory.add("Square", creator);
		myFactory.create("Square", "yellow");
		System.out.println("\n");
	}
	
	@Test
	void StaticMethodReferenceTest() 
	{
		Factory<Shape, String, String> myFactory = new Factory<>();
		myFactory.add("Triangle", staticMethodClass :: staticMethod);
		myFactory.create("Triangle", "black");
		System.out.println("\n");
	}
	
	@Test
	void instanceMethodReferenceTest() 
	{
		Factory<Shape, String, String> myFactory = new Factory<>();
		instanceMethodClass instance = new instanceMethodClass();
		myFactory.add("Circle", instance :: instanceMethod);
		myFactory.create("Circle", "white");
		System.out.println("\n");
	}
	
	@Test
	void constrcutorMethodReferenceTest() 
	{
		Factory<Shape, String, String> myFactory = new Factory<>();
		myFactory.add("Circle", Circle :: new);
		myFactory.create("Circle", "pink");
		System.out.println("\n");
	}
}

/* classes */
class Shape
{
	String color;
	Shape()
	{
		System.out.println("im a shape\n");
	}
}

class Circle extends Shape
{
	Circle(String color)
	{
		this.color = color;
		System.out.println("a " + color + " circle was created!");
	}
	void method()
	{
		System.out.println("my color is: " + color);
		System.out.println("im a circle of " + color + " color");
	}
}

class Rectangle extends Shape
{
	Rectangle(String color)
	{
		this.color = color;
		System.out.println("im a rectangle of color " + color);
		System.out.println("im a rectangle with the color of: " + color + "!!!");
	}
}

class Square extends Shape
{
	Square(String color)
	{
		this.color = color;
		System.out.println("im a square with the beautiful color of: " + color);
		System.out.println("im a magnificent square, with a magnificent " + color + " color :)");
	}
}

class Triangle extends Shape
{
	Triangle(String color)
	{
		this.color = color;
		System.out.println("wow! a triangle!! with color: " + color);
	}
}

/*inheriting class */
/*class squareCreator implements Function<String, Square>
{
	@Override
	public Square apply(String color)
	{
		return new Square(color);
	{
		this.color = color;
		System.out.println("triangle,  with color: " + color);
	}
}*/

/* inheritance */
class squareCreator implements Function<String, Square>
{
	public Square apply(String color)
	{
		return new Square(color);
	}
}

/* static method */
class staticMethodClass
{
	static Triangle staticMethod(String color)
	{
		return new Triangle(color);
	}
}

/* instance method */
class instanceMethodClass
{
	Circle instanceMethod(String color)
	{
		return new Circle(color);
	}
}



