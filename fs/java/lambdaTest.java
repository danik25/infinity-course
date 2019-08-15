public class lambdaTest
{
    public static void main(String[] args)
    {
        lambda x = new lambda();
        x.func(5);
    }

}

interface dani
{
    void dig();
}
class lambda
    {
        void PrintMessage()
        {
            System.out.println("outer");
        }
        
        void func(int x)
        {
            /*lambda a = new lambda(){
                @Override
                void PrintMessage()
                {
                    System.out.println("inner");
                } 
            };*/
            
            dani a = () -> System.out.println(x);
        
            a.dig();
        }
        
    }