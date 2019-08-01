class MySecondClass 
{
    public static void main(String[] args) 
    {
        MySecondClass obj = new MySecondClass();
        foo1();
        obj.foo2();
    }

    static void foo1()
    {
        System.out.println("static");
    }
    void foo2()
    {
        System.out.println("non static");
    }
}
