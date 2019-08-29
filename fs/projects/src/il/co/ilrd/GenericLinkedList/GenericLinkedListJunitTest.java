package il.co.ilrd.GenericLinkedList;

import static org.junit.jupiter.api.Assertions.*;

import java.util.Iterator;

import org.junit.jupiter.api.Test;

class GenericLinkedListJunitTest {

	@Test
	void testSizeNIsEmpty() {
		GenericLinkedList <Integer> newList = new GenericLinkedList<>();
		assertTrue(newList.isEmpty(), "not empty, while empty");
		for(int i = 0; i < 3; ++i)
		{
			assertEquals(newList.size(), i , "wrong size");
			newList.push(i);
		}
		assertFalse(newList.isEmpty(), "empty, while not empty");
	}
	@Test
	void testPushNPop() {
		GenericLinkedList <Integer> newList = new GenericLinkedList<>();
		
		for(int i = 0; i < 100; ++i)
		{
			newList.push(i);
		}
		
		for(int i = 100; i > 0; --i)
		{
			assertEquals(newList.pop(), i - 1 , "failed pop");
		}
	}
	
	@Test
	void testFind() {
		GenericLinkedList <Integer> newList = new GenericLinkedList<>();
		
		for(int i = 0; i < 3; ++i)
		{
			newList.push(i);
		}
		assertNotNull(newList.find(1), "failed to find existing value");
		assertNull(newList.find(4), "found a non existing value");
	}
	
	@Test
	void ReversTest() {
		GenericLinkedList <Integer> original = new GenericLinkedList<>();
		GenericLinkedList <Integer> rev;
		
		for(int i = 0; i < 3; ++i)
		{
			original.push(i);
		}
		rev = GenericLinkedList.Reverse(original);
		
		Iterator<Integer> revIter = rev.iterator();
		int i = 0;
		while(revIter.hasNext())
		{
			assertEquals(i, revIter.next(), "failed reverse");
			++i;
		}
	}
	
	@Test
	void Mergetest() {
		GenericLinkedList <Integer> first = new GenericLinkedList<>();
		GenericLinkedList <Integer> second = new GenericLinkedList<>();
		GenericLinkedList <Integer> mer;
		
		for(int i = 0; i < 3; ++i)
		{
			first.push(i);
			second.push(i + 3);
		}
		mer = GenericLinkedList.merge(second, first);
		
		Iterator<Integer> merIter = mer.iterator();
		int i = 0;
		while(merIter.hasNext())
		{
			assertEquals(i, merIter.next(), "failed merge");
			++i;
		}
	}
}
