package il.co.ilrd.hashmap;

import static org.junit.jupiter.api.Assertions.*;

import java.util.Map;

import org.junit.jupiter.api.Test;

class HashMapTest {

	@Test
	void removeTest() {
		HashMap<String, Integer> myHash = new HashMap<String, Integer>(10);
		myHash.put("A", 11);
		myHash.put("B", 12);
		myHash.put("C", 13);
		myHash.put("D", 14);
		
		assertEquals(myHash.containsKey("B"), true);
		assertEquals(myHash.size(), 4);
		myHash.remove("B");
		assertEquals(myHash.containsKey("B"), false);
		assertEquals(myHash.size(), 3);
		
		myHash.put("A", 12);
		assertEquals(myHash.size(), 3, "failed inserion of same key Pair");
		
		assertEquals(myHash.get("A"), 12);
	}
	
	@Test
	void putAllTest() {
		System.out.println("put all test:");
		HashMap<String, Integer> myHash = new HashMap<String, Integer>(1);
		myHash.put("a", 11);
		myHash.put("b", 12);
		myHash.put("c", 13);
		myHash.put("d", 14);
		
		HashMap <String, Integer> putAllMap = new HashMap<String, Integer>();
		putAllMap.put("e", 5);
		putAllMap.put("f", 6);
		
		assertEquals(myHash.size(), 4);
		
		myHash.putAll(putAllMap);
		
		assertEquals(myHash.size(), 6);

		for(Map.Entry<String,Integer> pair : myHash.entrySet())
		{
			System.out.println("key: " + pair.getKey() + ", val: " + pair.getValue());
		}

	}
	@Test
	void containsKeyTest() {
		HashMap<String, Integer> myHash = new HashMap<String, Integer>(10);
		myHash.put("a", 1);
		myHash.put("b", 2);
		myHash.put("d", 4);
		
		assertEquals(myHash.containsKey("a"), true);
		assertEquals(myHash.containsKey("A"), false);
	}
	@Test
	void containsValueTest() {
		HashMap<String, Integer> myHash = new HashMap<String, Integer>(10);
		myHash.put("a", 1);
		myHash.put("b", 2);
		myHash.put("c", 3);
		myHash.put("d", 4);
		
		assertEquals(myHash.containsValue(1), true);
		assertEquals(myHash.containsValue(20), false);
	}
	
	@Test
	void clearTest() {
		System.out.println("clearTest:");
		HashMap<String, Integer> myHash = new HashMap<String, Integer>(10);
		myHash.put("a", 1);
		myHash.put("b", 2);
		myHash.put("c", 3);
		myHash.put("d", 4);
		
		assertEquals(myHash.size(), 4);
		myHash.clear();
		assertEquals(myHash.size(), 0);
		
		for(Map.Entry<String,Integer> pair : myHash.entrySet())
		{
			System.out.println("key: " + pair.getKey() + ", val: " + pair.getValue());
		}
		System.out.println("done\n");
		
		myHash.put("d", 4);
		assertEquals(myHash.size(), 1);
	}
	@Test
	void IteratorTest() {
		HashMap<String, Integer> myHash = new HashMap<String, Integer>(4);
		String [] keys = {"a", "b", "c", "d", "e"};
		int [] vals = {1, 2, 3, 4, 5};
		
		for(int i = 0; i < keys.length; ++i)
		{
			myHash.put(keys[i], vals[i]);
		}
		
		System.out.println("\niteratorTest");
		System.out.println("set: " + myHash.entrySet());
		System.out.println("\nkeys: " + myHash.keySet());
		System.out.println("\nvalues: " + myHash.values());
		
		assertEquals(myHash.size(), 5);
		
	}
	
	@Test
	void getTest() {
		HashMap<String, Integer> myHash = new HashMap<String, Integer>(10);
		myHash.put("a", 1);
		myHash.put("b", 2);
		myHash.put("c", 3);
		myHash.put("d", 4);
		
		assertEquals(myHash.get("a"), 1);
		assertEquals(myHash.get("e"), null);
	}

}
