package il.co.ilrd.threadpool;

import static org.junit.jupiter.api.Assertions.*;

import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

import org.junit.jupiter.api.Test;

import il.co.ilrd.threadpool.ThreadPool.Priority;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;

class ThreadPoolTest {
	
	//@Test
	void isDoneTest()
	{
		System.out.println("\nis done test");
		Run5 r5 = new Run5();
		ThreadPool myPool = new ThreadPool(2);
		Future<Void> f5 = myPool.submit(r5, Priority.MEDIUM);
		
		try{
            Thread.sleep(5000);
        }catch(InterruptedException e){}
		
		myPool.shutdown();
		myPool.awaitTermination(9000, TimeUnit.MILLISECONDS);
		
		assertTrue(f5.isDone());
		System.out.println("done");
	}
	
	//@Test
	void getTest()
	{
		System.out.println("\nget test");
		Call1 c1 = new Call1();
		ThreadPool myPool = new ThreadPool(2);
		Future<Integer> f3 = myPool.submit(c1, Priority.MEDIUM);
		
		try
		{
			System.out.println("f3: " + f3.get(15000, TimeUnit.MILLISECONDS));
		}catch(TimeoutException | InterruptedException | ExecutionException e) {System.out.println(e);};
		
		
		myPool.shutdown();
		boolean ans = myPool.awaitTermination(10000, TimeUnit.MILLISECONDS);
		
		System.out.println("done");
		assertTrue(ans);
	}

	//@Test
	void SetNumberOfThreadsTest()
	{
		System.out.println("\nset number of threads test:");
		boolean ans;
		Run4 r4 = new Run4();
		Run3 r3 = new Run3();
		ThreadPool myPool = new ThreadPool(1);
		
		myPool.submit(r3, Priority.MEDIUM);
		myPool.submit(r4, Priority.MEDIUM);
		
		try{
            Thread.sleep(8000);
        }catch(InterruptedException e){}
		System.out.println("setting the thread number:");
		myPool.setNumOfThreads(2);
		
		myPool.shutdown();
		ans = myPool.awaitTermination(15000, TimeUnit.MILLISECONDS);
		
		System.out.println("done");
		assertFalse(ans);
	}
	
	
	@Test
	void shutDownTest() {
		System.out.println("\nshutDown test:");
		Run4 r4 = new Run4();
		Run3 r3 = new Run3();		
		
		ThreadPool myPool = new ThreadPool(3);
		
		myPool.submit(r4, Priority.LOW);
		myPool.shutdown();

		try{
            Thread.sleep(2000);
        }catch(InterruptedException e){}
		
		myPool.submit(r3, Priority.LOW);
		
		boolean ans = myPool.awaitTermination(15000, TimeUnit.MILLISECONDS);
		System.out.println("done");
		assertTrue(ans);
	}
	//@Test
	void cancelTest() {
		System.out.println("\ncancel test:");
		System.out.println("not suposed printing 'r4'");
		Run4 r4 = new Run4(); 
		Run5 r5 = new Run5();
		
		ThreadPool myPool = new ThreadPool(1);
		
		myPool.submit(r5, Priority.HIGH);
		Future<Void> f4 = myPool.submit(r4, Priority.LOW);
		
		f4.cancel(true);
		
		myPool.shutdown();
		myPool.awaitTermination(15000, TimeUnit.MILLISECONDS);
		
		System.out.println("done");
		assertTrue(f4.isCancelled());
	}
	
	//@Test
	void pauseReasumeTest() {
		System.out.println("\npause and resume test:");
		System.out.println("not suposed to print 'r3' until resuming:");
		Run1 r1 = new Run1();
		Run2 r2 = new Run2();
		Run3 r3 = new Run3();
		
		ThreadPool myPool = new ThreadPool(3);
		
		myPool.submit(r1, Priority.LOW);
		myPool.submit(r2, Priority.MEDIUM);
		
		try{
            Thread.sleep(4000);
        }catch(InterruptedException e){}
		System.out.println("pausing....");
		myPool.pause();
		
		// prevent the entrance of the this task before the submission of "pause"
		try{
            Thread.sleep(1000);
        }catch(InterruptedException e){}
		
		myPool.submit(r3, Priority.MEDIUM);
		
		try{
            Thread.sleep(4000);
        }catch(InterruptedException e){}
		
		System.out.println("resuming....");
		myPool.resume();
		
		myPool.shutdown();
		boolean ans = myPool.awaitTermination(15000, TimeUnit.MILLISECONDS);
		System.out.println("done");
		assertFalse(ans);
	}

}

/**********************************/
class Run1 implements Runnable
{
	@Override
	public void run()
	{
		while(true)
		{
			try{
                Thread.sleep(1500);
            }catch(InterruptedException e){}
			System.out.println("r1");
		}
	}
	
}

class Run2 implements Runnable
{
	@Override
	public void run()
	{
		while(true)
		{
			try{
                Thread.sleep(1500);
            }catch(InterruptedException e){}
			System.out.println("r2");
		}
	}
}

class Run3 implements Runnable
{
	@Override
	public void run()
	{
		while(true)
		{
			try{
                Thread.sleep(1500);
            }catch(InterruptedException e){}
			System.out.println("r3");
		}
	}
}

class Run4 implements Runnable
{
	@Override
	public void run()
	{
		int i = 0;
		while(i < 5)
		{
			try{
                Thread.sleep(1500);
            }catch(InterruptedException e){}
			System.out.println("r4");
			++i;
		}
	}
}

class Run5 implements Runnable
{
	@Override
	public void run()
	{
		int i = 0;
		while(i < 5)
		{
			try{
                Thread.sleep(1500);
            }catch(InterruptedException e){}
			System.out.println("r5");
			++i;
		}
	}
}

/**********************************/

class Call1 implements Callable<Integer>
{
	@Override
	public Integer call()
	{
		int i = 0;
		while(i < 5)
		{
			try{
                Thread.sleep(1500);
            }catch(InterruptedException e){}
			System.out.println("call running ");
			++i;
		}
		System.out.println("task call1 is finished");
		return 1;
	}
}
