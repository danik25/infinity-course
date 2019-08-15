public class outerInnerTest
{
    public static void main(String[] args)
    {
        outer a = new outer();
        a.method();
    }
}

class outer
{
    int x = 5;
    void method()
    {
        //inner x = new inner();
        //x.Print();
        anonymousTestMethod();
    }

    void outerMethod()
    {
        System.out.println("outer method");
    }

    void anonymousTestMethod()
    {
        /*outer a = new outer(){
            @Override
            void outerMethod()
            {
                System.out.println("anonymous1");
            }            
        };*/

        outer b = new outer(){
            @Override
            void outerMethod()
            {
                ++x;
                System.out.println(x);
            }            
        };
        b.outerMethod();
    }

    void changer()
    {
        x = 7;
    }
    
}