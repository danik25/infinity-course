package il.co.ilrd.GenericLinkedList;

import java.util.Iterator;
import java.util.ConcurrentModificationException;

public class GenericLinkedList<E> implements Iterable<E> 
{
    private Node<E> head;
    private int size;
    private int listVersion;

    public GenericLinkedList() {
        head = new Node<E>(null, null);
    }

    public int size() {      
        return(size);
    }

    public void push(E data) {
        head = new Node<>(data, head);
        ++size;
        ++listVersion;
    }

    public E pop() {
    	E ans= null;
    	if(!isEmpty())
    	{
    		ans = head.data;
            head = head.nextNode;
            --size;
            ++listVersion;
    	}        
        return(ans);
    }

    public boolean isEmpty() {
        return(0 == size);
    }

    public Iterator<E> find(E data) {
    	Node<E> tmpNode = head;
        while(tmpNode.nextNode != null)
        {
            if(tmpNode.data.equals(data))
            {
                return(new GenericLinkedListIterator<E>(tmpNode));
            }
            tmpNode = tmpNode.nextNode;
        }
        return(null);
    }

    public static <T> GenericLinkedList<T> Reverse(GenericLinkedList<T> list) {
    	GenericLinkedList<T> revList = new GenericLinkedList<>();
    	
    	Iterator<T> srcList = list.iterator();
    
    	while(srcList.hasNext())
    	{
    		revList.push(srcList.next());
    	}
    	
    	return(revList);
    }

    public static <T> GenericLinkedList<T> merge(GenericLinkedList<T> list1, GenericLinkedList<T> list2) {
    	GenericLinkedList<T> mergedList = new GenericLinkedList<>();
    	Iterator<T> firstList = list1.iterator();
    	Iterator<T> secondList = list2.iterator();
    	
    	while(firstList.hasNext())
    	{
    		mergedList.push(firstList.next());
    	}
    	
    	while(secondList.hasNext())
    	{
    		mergedList.push(secondList.next());
    	}
    	
    	return(mergedList);
    }

    @Override
    public Iterator<E> iterator() {
        return new GenericLinkedListIterator<E>(head);
    }


    private static class Node<T> {
        private T data;
        private Node<T> nextNode;

        private Node(T data, Node<T> nextNode) {
            this.data = data;
            this.nextNode = nextNode;
        }
    }

    private class GenericLinkedListIterator<T> implements Iterator<E> {
        private int version;
        private Node<E> currentNode;

        public GenericLinkedListIterator(Node<E> head) {
			currentNode = head;
			version = listVersion;
		}
        @Override
        public boolean hasNext() {
            return(currentNode.nextNode != null);
        }

        @Override
        public E next(){
            E currData = currentNode.data;
            currentNode = currentNode.nextNode;
            
            if(version != listVersion)
            {
            	throw new ConcurrentModificationException();
            }
            
            return(currData);
        }       
    }
} 
