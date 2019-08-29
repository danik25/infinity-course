import java.util.Arrays;
import java.util.HashMap; 
import java.util.Map; 

import java.util.stream.Collectors; 
import java.util.stream.Stream; 
import java.util.*; 

public class collectionTest{
    public static void main(String[] args){
        //ex1.arrayMethod();
        //ex1.mapMethod();
        ex1.sumArrayMethod();
    }
}

class ex1
{
    static void arrayMethod()
    {
        int [] intArray = {1, 4, 6, 2, 3};
        System.out.println(Arrays.toString(intArray));

        Arrays.sort(intArray);
        System.out.println(Arrays.toString(intArray));
    }
    static void mapMethod()
    {
        Map< String,Integer> week =  new HashMap< String,Integer>(); 
        week.put("Sunday", 1); 
        week.put("Monday", 2); 
        week.put("Tuesday", 3); 
        week.put("Wednesday", 4);
        week.put("Thursday", 5); 
        week.put("Friday", 6);
        week.put("Saturday", 7);

        // System.out.println(week);
        // System.out.println(week.values());

        for(Map.Entry<String, Integer> a : week.entrySet())
        {
            System.out.println(a);
            System.out.println(a.getValue());
        }
    }
    static void sumArrayMethod()
    {
        DataObject[] dataArray = {new DataObject("one", 1), new DataObject("two", 1), 
                                    new DataObject("three", 1), new DataObject("two", 1), new DataObject("three", 2)};
    
        Map< String,Integer> hashArray =  new HashMap< String,Integer>(); 
        for(DataObject d : dataArray)
        {
            int val = d.value;
            if(hashArray.containsKey(d.code))
            {
                val += hashArray.get(d.code);
            }

            hashArray.put(d.code, val);
            
            
        }
        
        for(Map.Entry<String, Integer> a : hashArray.entrySet())
        {
            System.out.println(a);
        }
    }
}

class DataObject
{
    String code;
    int value;

    DataObject(String code, int value)
    {
        this.code = code;
        this.value = value;
    }
}