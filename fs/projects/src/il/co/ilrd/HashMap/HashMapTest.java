package il.co.ilrd.HashMap;
import java.util.Collection;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

class HashMapTest {

	@Test
	void test() {
		HashMap<String, Integer> myHash = new HashMap<String, Integer>(4);
		myHash.put("a", 1);
		myHash.put("b", 2);
		myHash.put("c", 3);
		myHash.put("d", 4);
		
		Collection<Integer> myValues = myHash.values();
		for(Integer a : myValues)
		{
			System.out.println(a);
		}
		
		myHash.remove("b");
		System.out.println("\n");
		myValues = myHash.values();
		for(Integer a : myValues)
		{
			System.out.println(a);
		}
		
		assertEquals(0, 0);
	}

}
