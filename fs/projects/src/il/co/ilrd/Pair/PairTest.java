package il.co.ilrd.Pair;

import static org.junit.jupiter.api.Assertions.*;
import java.util.*; 

import org.junit.jupiter.api.Test;

class PairTest {

	@Test
	void setNGetTest() {
		String firstName = "dani";
		Integer age = 26;
		String anotherFirstName = "roni";
		Pair <String,Integer> name = Pair.of(firstName, age);
		
		assertEquals(firstName, name.getKey(), "failed get key");
		assertEquals(age, name.getValue(), "failed get value");
		
		name.setKey(anotherFirstName);
		assertEquals(anotherFirstName, name.getKey(), "failed set key");
	}
	@Test
	void minMaxComparatorTest() {
		String firstName1 = "dani";
		Integer age1 = 26;
		String firstName2 = "roni";
		Integer age2 = 27;
		String firstName3 = "yossi";
		Integer age3 = 33;
		
		Pair <String,Integer> name1 = Pair.of(firstName1, age1);
		Pair <String,Integer> name2 = Pair.of(firstName2, age2);
		Pair <String,Integer> name3 = Pair.of(firstName3, age3);
		
		Pair[] pairArray = {name1, name2, name3};
		
		Pair <String,Integer> minMax = Pair.minMax(pairArray, new comparePair());
		
		assertEquals(minMax.getKey(), name1, "failed min max with comperator");
		assertEquals(minMax.getValue(), name3, "failed min max with comperator");
	}
	
	@Test
	void minMaxComparableTest() {	
		Integer[] intArray = {0, 2, 1, 8, 11, 12};
		
		Pair <Integer,Integer> minMax = Pair.minMax(intArray);
		assertEquals(minMax.getKey(), 0, "failed min with comperator");
		assertEquals(minMax.getValue(), 12, "failed max with comperator");
	}
	
	@Test
	void swapTest() {	
		String firstName = "dani";
		Integer age = 26;
		Pair <String,Integer> name = Pair.of(firstName, age);
		Pair <Integer, String> swappedName = Pair.swap(name);
		
		assertEquals(swappedName.getKey(), age, "failed swap");
		assertEquals(swappedName.getValue(), firstName, "failed swap");
	}
}


/*-------------------------------------------------------------------*/
class comparePair implements Comparator<Pair<String, Integer>> 
{ 
	@Override
    public int compare(Pair<String,Integer> a, Pair<String,Integer> b) 
    { 
        return ((Integer)a.getValue() - (Integer)b.getValue()); 
    } 
} 
