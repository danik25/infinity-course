package il.co.ilrd.LinkedList;

public class LinkedListTest {
	public static void main(String[] args) {
				
		LinkedList newList = new LinkedList();
			
		System.out.println("empty? " + newList.isEmpty());
		System.out.println("size: " + newList.size());
		
		System.out.println("pushing 3 elements");
		newList.pushFront(1);
		newList.pushFront(2);
		newList.pushFront(3);
		
		System.out.println("empty? " + newList.isEmpty());
		System.out.println("size: " + newList.size());
		
		System.out.println("finding existing value:");
		if(newList.find(1) != null)
		{
			System.out.println("exists");
		}
		
		System.out.println("finding not existing value:");
		if(newList.find(5) == null)
		{
			System.out.println("not exists");
		}
		System.out.println("\npoping the list");
		Iterator iter = newList.begin();
		for(; iter.hasNext(); iter.next())
		{
			System.out.println(newList.popFront());
		}
	}
}
