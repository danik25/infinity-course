class SuperClass {
    int intSuperClass = 10;

    static {
        System.out.println(" 1 static initializer called of superClass");
    }

    {
        System.out.println(" 1 instance initializer called of superClass");
        System.out.println(intSuperClass);
    }

    public SuperClass() {
        System.out.println("constructor of super class");
        intSuperClass *= 2;
        System.out.println(intSuperClass);
    }

    static {
        System.out.println(" 2 static initializer called of superClass");
    }

    {
        System.out.println(" 2 instance initializer called of superClass");
    }
}

public class SubClass extends SuperClass {
    int intSubClass = 100;

    {
        System.out.println(" 1 instance initializer called of subClass");
        System.out.println(intSubClass);
    }

    public SubClass() {
        System.out.println("constructor call of subClass");
        System.out.println(intSubClass);
        intSubClass *= 2;
    }

    static {
        System.out.println(" 1 static initializer called of subClass");
    }

    {
        System.out.println(" 2 instance initializer called of subClass");
    }

    static {
        System.out.println(" 2 static initializer called of subClass");
    }

    public static void main(String[] args) {
        new SubClass();
        new SubClass();
    }
}