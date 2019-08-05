class Overriding {
    public static void main(String[] args) {
        
        Overriding obj1 = new Overriding();
        subclass obj2 = new subclass();

        //obj1.method1(5);
        obj2.method1();
        
    }

    
    int method1()
    {
        System.out.println("superclass ");
        return(1);
    }
    
}

class subclass extends Overriding
{
    double method1()
    {
        System.out.println("subclass ");
        return(1.0);
    }
}

class other_class 
{
    ;
} 