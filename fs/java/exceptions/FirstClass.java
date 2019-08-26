public class FirstClass {
    public static void main(String[] args){
        SecondClass.anotherMethod();
    }
}

class myClass
{
    static void myMethod()
    {
        System.out.println("first");
    }
}

class SecondClass {
    static void anotherMethod()
    {
        myClass.myMethod();
    }
}

