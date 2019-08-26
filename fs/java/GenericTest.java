import java.util.*;

public class GenericTest {
    public static void main(String[] args){
        List<String> stringList = new ArrayList<>();
        List<Integer> integerList = new ArrayList<>();
        List<Double> doubleList = new ArrayList<>();

        stringList.add("a");
        stringList.add("b");
        stringList.add("c");

        integerList.add(1);
        integerList.add(2);
        integerList.add(3);

        doubleList.add(1.0);
        doubleList.add(2.0);
        doubleList.add(3.0); 

        PrintArray(stringList);
        PrintArray(integerList);
        PrintArray(doubleList);

        FooReference<String> ref = new FooReference<>();
        ref.setter("dani");
        System.out.println(ref.getter());

    }

    static <T> void PrintArray(List<T> array)
    {
        for(T a : array)
        {
            System.out.println(a);
        }
        System.out.println("\n");
    }
}

class FooReference <T>{
    private T val;

    T getter()
    {
        return val;
    }

    void setter(T value)
    {
        val = value;
    }
}

