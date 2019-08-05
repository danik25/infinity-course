class IntegerAndInt
{
    public static void main(String[] args) 
    {
        Integer sum = 0;
        for(int i = 10; i < 50; i++)
        {
            sum += i;
        }
        System.out.println(sum);

        ex13();
    }

    static void ex13()
    {
        Integer one = new Integer(1);
        Integer anotherOne = new Integer(1);

        if(one.equals(anotherOne))
        {
            System.out.println("now equal");
        }
        else
        {
            System.out.println("not equal");
        }
    }
}