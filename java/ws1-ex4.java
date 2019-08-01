import java.util.ArrayList;

class LangRunTime 
{
    public static void main(String[] args) 
    {
        ArrayList<int[]> listArray = new ArrayList<int[]>();
        
        int i = 0;
        //int j = 0;
                
        while(true)
        {
            int a1[]= new int[1];
            
            listArray.add(a1); 
            /*for(j = 0; j < 3; ++j)
            {
                System.out.print(" " + listArray.get(i)[j]);
            }
            System.out.println("");*/
        
            System.out.println("" + Runtime.getRuntime().freeMemory() + " " + i);
        }
    }
}