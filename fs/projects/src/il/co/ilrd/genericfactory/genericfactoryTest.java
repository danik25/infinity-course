package il.co.ilrd.genericfactory;

import static org.junit.jupiter.api.Assertions.*;
import java.util.function.Function;

import org.junit.jupiter.api.Test;

class genericfactoryTest {

	@Test
	void test() {
		Factory<Shape, String, Integer> myFactory = new Factory<>();
		myFactory.add("Circle", new Function<Integer, Circle>(){
			@Override
		    public Circle apply(Integer a) {   
		        return new Circle(); 
		    }
		});
		
		Circle c = (Circle)myFactory.create("circle", 0);
		
	}
}

/*Age oj1 = new Age() { 
    @Override
    public void getAge() { 
         // printing  age 
        System.out.print("Age is "+x); 
    }*/

//Function<Integer, Double> half = a -> a / 2.0; 

class Shape
{
	Shape()
	{
		System.out.println("im a shape");
	}
}

class Circle extends Shape
{
	Circle()
	{
		System.out.println("im a circle");
	}
	void method()
	{
		System.out.println("circle");
	}
}

class Rectangle extends Shape
{
	Rectangle()
	{
		System.out.println("im a rectangle");
	}
}

class Square extends Shape
{
	Square()
	{
		System.out.println("im a square");
	}
}