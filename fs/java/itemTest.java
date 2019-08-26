import java.util.*;
public class itemTest
{
    public static void main(String[] args) 
    {
        List<String> strings = new ArrayList<String>();
        unsafeAdd(strings, new Integer(42));
        String s = strings.get(0); // Compiler-generated cast

        
    }

    private static void unsafeAdd(List<Object> list, Object o) 
    {
        list.add(o);
    }
}

    