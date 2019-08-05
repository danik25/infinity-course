import java.lang.Math.*;

public class testShape
{
	public static void main(String[] args) 
	{
		test test1 = new test();
		test1.testShape();
	}
}

class test
{
	void testShape()
	{
		Shape s1 = new Circle(5.5, "RED", false);
		System.out.println(s1);
		System.out.println(s1.getArea());
		System.out.println(s1.getPerimeter());
		System.out.println(s1.getColor());
		System.out.println(s1.isFilled());
		System.out.println(((Circle)s1).getRadius());
		
		System.out.println("\n-----------------------------------------\n");
		
		Circle c1 = (Circle)s1;
		System.out.println(c1);
		System.out.println(c1.getArea());
		System.out.println(c1.getPerimeter());
		System.out.println(c1.getColor());
		System.out.println(c1.isFilled());
		System.out.println(c1.getRadius());
		
		//Shape s2 = new Shape();
		
		System.out.println("\n-----------------------------------------\n");
		
		Shape s3 = new Rectangle(1.0, 2.0, "RED", false);
		System.out.println(s3);
		System.out.println(s3.getArea());
		System.out.println(s3.getPerimeter());
		System.out.println(s3.getColor());
		System.out.println(((Rectangle)s3).getLength());
		
		System.out.println("\n-----------------------------------------\n");
		
		Rectangle r1 = (Rectangle)s3;
		System.out.println(r1);
		System.out.println(r1.getArea());
		System.out.println(r1.getColor());
		System.out.println(r1.getLength());
		
		System.out.println("\n-----------------------------------------\n");
		
		Shape s4 = new Square(6.6);
		System.out.println(s4);
		System.out.println(s4.getArea());
		System.out.println(s4.getColor());
		System.out.println(((Square)s4).getLength());
		
		System.out.println("\n-----------------------------------------\n");
		
		Rectangle r2 = (Rectangle)s4;
		System.out.println(r2);
		System.out.println(r2.getArea());
		System.out.println(r2.getColor());
		System.out.println(((Square)r2).getSide());
		System.out.println(r2.getLength());
		
		System.out.println("\n-----------------------------------------\n");
		
		Square sq1 = (Square)r2;
		System.out.println(sq1);
		System.out.println(sq1.getArea());
		System.out.println(sq1.getColor());
		System.out.println(sq1.getSide());
		System.out.println(sq1.getLength());
		
	}
	
	
}

abstract class Shape 
{
	String color;
	boolean filled;
	
	Shape()
	{
		System.out.println("no args constructor");
		color = "green";
		filled = true;
	}
	Shape(String userColor, boolean ans)
	{
		System.out.println("args constructor");
		color = userColor;
		filled = ans;
	}
	
	void setColor(String userColor)
	{
		color = userColor;
	}
	void filledSetter(boolean ans)
	{
		filled = ans;
	}
	
	String getColor()
	{
		return(color);
	}
	boolean isFilled()
	{
		return(filled);
	}
	
	public String toString()
	{
		return("A Shape with color " + color + " and " + filled);
	}
	
	abstract double getArea();
	abstract double getPerimeter();
}

class Circle extends Shape
{
	double radius;
	
	
	Circle()
	{
		System.out.println("circle, no args");
		radius = 1.0;
	}
	
	Circle(double userRadius)
	{
		radius = userRadius;
	}
	
	Circle(double userRadius, String userColor, boolean userFilled)
	{
		super(userColor, userFilled);
		radius = userRadius;
	}

	double getRadius() 
	{
		return radius;
	}

	void setRadius(double radius) 
	{
		this.radius = radius;
	}
	
	double getArea()
	{
		return(Math.PI * radius * radius);
	}
	
	double getPerimeter()
	{
		return(Math.PI * radius * 2);
	}
	
	public String toString()
	{
		return("A Circle with radius '" + radius + "' which is sublclass of '"
					+ getClass().getSuperclass() + "', where\n'" + super.toString() + 
					"'\nis the output of the toString method from superclass");
	}
}

class Rectangle extends Shape
{
	double length;
	double width;
	
	Rectangle()
	{
		System.out.println("Rectangle, no args");
		width = 1.0;
		length = 1.0;
	}
	
	Rectangle(double userLength, double userWidth)
	{
		width = userWidth;
		length = userLength;
	}
	
	Rectangle(double userLength, double userWidth, String userColor, boolean userFilled)
	{
		super(userColor, userFilled);
		width = userWidth;
		length = userLength;
	}

	public double getLength() 
	{
		return length;
	}

	public void setLength(double length) 
	{
		this.length = length;
	}

	public double getWidth() 
	{
		return width;
	}

	public void setWidth(double width) 
	{
		this.width = width;
	}
	
	double getArea()
	{
		return(length * width );
	}
	
	double getPerimeter()
	{
		return(length * 2 + width * 2);
	}
	
	public String toString()
	{
		return("A Rectangle with width '" + width + "', and length '" + length + "' which is sublclass of '"
					+ getClass().getSuperclass() + "', where\n'" + super.toString() + 
					"'\nis the output of the toString method from superclass");
	}
}

class Square extends Rectangle
{
	double side;
	
	Square(double userSide)
	{
		super(userSide, userSide);
		side = userSide;
	}

	public double getSide() 
	{
		return side;
	}

	public void setSide(double side) 
	{
		this.side = side;
	}
}












