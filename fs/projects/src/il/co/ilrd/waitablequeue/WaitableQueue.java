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
	try {
		sem.acquire();		
	} catch (InterruptedException e) {
		e.printStackTrace();
	}
	
	synchronized (pQueue) {
		return pQueue.poll();
	}

}

public E dequeue(long waitTime, TimeUnit timeUnit){
	try {
		if (false == sem.tryAcquire(waitTime, timeUnit))
		{
			return null;
		}
	} catch (InterruptedException e) {
		e.printStackTrace();
	}
	
	synchronized (pQueue) {
		return pQueue.poll();
	}
}

public boolean remove(E element) {
	try {
		sem.acquire();
	} catch (InterruptedException e) {
		e.printStackTrace();
	}
	
	synchronized (pQueue) {
		if (false == pQueue.remove(element))
		{
			sem.release();
			return false;
		}
		return true;
	}
}
}