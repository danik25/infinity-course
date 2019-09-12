package il.co.ilrd.waitablequeue;

import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.*; 

public class WaitableQueue<E> {

private PriorityQueue<E> pQueue;
private Semaphore sem = new Semaphore(0); 

public WaitableQueue(Comparator<E> comperator) {
	pQueue = new PriorityQueue<E>(comperator);
}

public boolean enqueue(E element) {
	boolean ans;
	synchronized(pQueue)
	{
		ans = pQueue.add(element);
		sem.release();
	}
	
	return ans;
}

public E dequeue() {
	return(dequeue(0, TimeUnit.NANOSECONDS));
}

public E dequeue(long waitTime, TimeUnit timeUnit){
	synchronized(pQueue)
	{
		try {
			if(sem.tryAcquire(waitTime, timeUnit))
			{
				return pQueue.poll();
			}
			
			
		} catch (InterruptedException e)  {
	        System.out.println("failed wait");  
	    }
		return null;
	}
}

public boolean remove(E element) {
	try {
		sem.acquire();
	} catch (InterruptedException e) {
		e.printStackTrace();
	}
	
	synchronized (pQueue) {
		return pQueue.remove(element);
	}
}
}