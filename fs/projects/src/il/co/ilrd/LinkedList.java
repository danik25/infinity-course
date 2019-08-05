package il.co.ilrd;

public class LinkedList{
	private Node head; 

	public void pushFront(Object data){
		head = new Node(data, head);
	}
	public Object popFront()
	{
		Object ans = head.data;
		head = head.nextNode;
		
		return(ans);
	}
	public int size()
	{
		LinkedListIterator index = new LinkedListIterator(head);
		int cnt = 0;
		for(; index.hasNext(); index.next())
		{
			++cnt;
		}
		
		return(cnt);
	}
	public boolean isEmpty()
	{
		return(head == null);
	}
	/*public Iterator find(Object data);*/
	public Iterator begin()
	{
		LinkedListIterator begin = new LinkedListIterator(head);
		return(begin);
	}

	private class Node{
		private Object data;
		private Node nextNode; 
		private Node(Object data, Node nextNode)
		{
			data = data;
			nextNode = nextNode;
		}
}

	private class LinkedListIterator implements Iterator{
		private Node currentNode;
		private LinkedListIterator(Node node)
		{
			currentNode = node;
		}
		@Override 
		public boolean hasNext()
		{
			return(currentNode.nextNode != null);
			
		}
		@Override
		public Object next()
		{
			currentNode = currentNode.nextNode;
			return(currentNode.nextNode);
		}
	}
}

