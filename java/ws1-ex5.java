
class RecStackCalls
{
    public static void main(String[] args) 
    {
        Rec(0);
    }

    static void Rec(int i)
    {
        if(i == 10774)
        {
            return;
        }
        System.out.println(i);
         Rec(i + 1);
    }
}