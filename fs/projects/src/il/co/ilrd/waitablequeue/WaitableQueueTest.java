package il.co.ilrd.waitablequeue;

import java.util.Random;
import java.util.concurrent.TimeUnit;

public class WaitableQueueTest {

	
	WaitableQueue<Integer> queue = new WaitableQueue<Integer>(Integer::compareTo);

	public static void main(String[] args) {
		
		/*
		 * testEnqDeq();*/			
			
		testTimeOutDeq(); 	
		testRemove();
		 
	}
	
	private static void testEnqDeq()
	{
		WaitableQueueTest wqt = new WaitableQueueTest();
		Thread[] adders = new Thread[4];
		Thread[] removers = new Thread[2];
		
		for (int i = 0; i < 4; ++i)
		{
			adders[i] = new Thread(wqt.new Adder());
			adders[i].start();
		}
		
		for (int i = 0; i < 2; ++i)
		{
			removers[i] = new Thread(wqt.new Remover());
			removers[i].start();
		}
		
		for (int i = 0; i < 4; ++i)
		{
			try {
				adders[i].join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		
		for (int i = 0; i < 2; ++i)
		{
			try {
				removers[i].join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
	}
	
	private static void testTimeOutDeq()
	{
		WaitableQueue<Integer> q = new WaitableQueue<Integer>(Integer::compareTo);
		
		q.enqueue(100);
		Long startTime = System.currentTimeMillis();
		q.dequeue();
		System.out.println(System.currentTimeMillis() - startTime);
		
		Runnable r1 = new Runnable() {
			
			@Override
			public void run() {
				try {
					Thread.sleep(5000);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
				q.enqueue(100);
			}
		};
		
		Runnable r2 = new Runnable() {
			
			@Override
			public void run() {
				q.dequeue(10000, TimeUnit.MILLISECONDS);
			}
		};
		
		Thread tr1 = new Thread(r1);
		Thread tr2 = new Thread(r2);
			
		tr1.start();
		tr2.start();
		
		try {
			tr1.join();
			tr2.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
	
	private static void testRemove()
	{
		WaitableQueue<String> queue = new WaitableQueue<String>(String::compareTo);
		
		queue.enqueue("David");
		queue.enqueue("Tali");
		queue.enqueue("Itay");
		queue.enqueue("Baruch");
		
		queue.remove("David");
		
		System.out.println(queue.dequeue());
		System.out.println(queue.dequeue());
		System.out.println(queue.dequeue());
		System.out.println(queue.dequeue());
	}
	
	private class Adder implements Runnable {

		@Override
		public void run() {
			Random r = new Random();
			Integer randInt = 0;
			
			while (true)
			{				
				randInt = Math.abs(r.nextInt() % 1000);
				queue.enqueue(randInt);
				System.out.println("Enqueued: " + randInt);
			}			
		}
	}

	private class Remover implements Runnable {

		@Override
		public void run() {			
			while (true)
			{
				System.out.println("Dequeued: " + queue.dequeue());
			}			
		}			
	}
}

