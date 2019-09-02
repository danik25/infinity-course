package il.co.ilrd.genericfactory;

//import static org.junit.jupiter.api.Assertions.*;
import java.util.function.Function;

import org.junit.jupiter.api.Test;

class genericfactoryTest {

	@Test
	void AnonymousClassCTest() {
		Factory<Shape, String, String> myFactory = new Factory<>();
		
		myFactory.add("circle", new Function<String, Circle>(){
			//@Override
		    public Circle apply(String color) {   
		        return new Circle(color); 
		    }
		});
		Circle c = (Circle)myFactory.create("circle", "red");
		c.method();
		System.out.println("\n");
		
	}
	
	@Test
	void lambdaTest() {
		Factory<Shape, String, String> myFactory = new Factory<>();
		Function<String, Rectangle> lam = (String color)-> new Rectangle(color);
		myFactory.add("rectangle", lam);
		myFactory.create("rectangle", "green"); 
		
		System.out.println("\n");
	}
	
	@Test
	void inheritanceTest() {
		Factory<Shape, String, String> myFactory = new Factory<>();
		squareCreator inheritFunc = new squareCreator();
		myFactory.add("square", inheritFunc);
		myFactory.create("square", "yellow");
		
		System.out.println("\n");
	}
}

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
	Circle()
	{
		System.out.println("im a circle");
	}
	Circle(String color)
	{
		this.color = color;
		System.out.println("a " + color + " circle was created!");
	}
	void method()
	{
		System.out.println("my color is: " + color);
	}
}

class Rectangle extends Shape
{
	Rectangle(String color)
	{
		this.color = color;
		System.out.println("im a rectangle of color " + color);
	}
}

class Square extends Shape
{
	Square(String color)
	{
		this.color = color;
		System.out.println("im a square with the beautiful color of: " + color);
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
class squareCreator implements Function<String, Square>
{
	@Override
	public Square apply(String color)
	{
		return new Square(color);
	}
}