package il.co.ilrd.LinkedList;


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
		LinkedListIterator iter = new LinkedListIterator(head);
		int cnt = 0;
		
		for(; iter.hasNext(); iter.next())
		{
			++cnt;
		}
		
		return(cnt);
	}
	public boolean isEmpty()
	{
		return(head == null);
	}
	
	public Iterator find(Object data)
	{
		LinkedListIterator iter = new LinkedListIterator(head);
		for(; iter.hasNext(); iter.next())
		{
			if(iter.currentNode.data.equals(data))
			{
				return(iter);
			}
		}
		return(null);
	}
	
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
			this.data = data;
			this.nextNode = nextNode;
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
			return(currentNode != null);
			
		}
		@Override
		public Object next()
		{
			Object ans = currentNode.data;
			currentNode = currentNode.nextNode;
			
			return(ans);
		}
	}
}
