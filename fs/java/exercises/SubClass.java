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
        // new SubClass();
        // new SubClass();

        // C c = new C();
        // C.C1 c1 = c.new C1();
        // c1.fooCall();

        // C.C2 c2 = c.new C2();

        A<Integer> a = new A<Integer>();

    }
}

class C {
    private String s = "123";

    class C1 {
        private C c = new C();
        private String str = "hello world";

        private void foo() {
            s = "456";
            System.out.println(str);
        }

        void fooCall() {
            foo();
        }
    }

    class C2 {
        private C1 c1 = new C1();

        private void foo2() {
            c1.c.s = "abc";
        }
    }

    private static class C3 {
        private static int i = 3;

        static void foo() {
            i = 5;
        }
    }
}

class A<T> {
    public void foo(Object o) {
    }

    public <Z extends Number> void foo(Z t) {
    }

}