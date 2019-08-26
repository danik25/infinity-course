import java.io.*;

public class ExceptionTest {
	public static void main(String[] args){
        try{
            Foo.func1();
        }catch(IOException e){
            System.out.println(e.getMessage());
            System.out.println("declared");
        }
        System.out.println("\n");
        try{
            Foo.func2();
        }catch(NullPointerException e){
            System.out.println(e.getMessage());
            System.out.println("not declared");
        }
        System.out.println("\n");
        try{
            Foo.func3();
        }catch(myException1 e){
            System.out.println(e.getMessage());
            System.out.println("1");
        }
        System.out.println("\n");
        try{
            Foo.func4();
        }catch(myException2 e){
            System.out.println(e.getMessage());
            System.out.println("2");
        }  

        System.out.println("\n");
        byte[] array = new byte[100];
        try{
            System.out.println(array[101]);
        }catch(ArrayIndexOutOfBoundsException e){
            System.out.println(e.getMessage());
            System.out.println("out of index");
        } 
        
    }
}

class Foo{
    static void func1() throws IOException
    {
        throw new IOException();
    }

    static void func2()
    {
        throw new NullPointerException();
    }

    static void func3()
    {
        throw new myException1();
    }
    static void func4() throws myException2
    {
        throw new myException2();
    }
}

class myException1 extends RuntimeException { 
    public myException1() {
       ;
    }
}

class myException2 extends IOException { 
    public myException2() {
       ;
    }
}