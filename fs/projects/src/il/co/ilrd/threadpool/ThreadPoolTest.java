package il.co.ilrd.threadpool;

import static org.junit.jupiter.api.Assertions.*;

import java.util.concurrent.TimeUnit;

import org.junit.jupiter.api.Test;

import il.co.ilrd.threadpool.ThreadPool.Priority;

import java.util.concurrent.Callable;
import java.util.concurrent.Future;

class ThreadPoolTest {
	@Test
	void cancelTest() {
		System.out.println("cancel test:");
		Run1 r1 = new Run1();
		Run2 r2 = new Run2();
		
		ThreadPool myPool = new ThreadPool(3);
		
		Future<Void> f1 = myPool.submit(r1, Priority.LOW);
		Future<Void> f2 = myPool.submit(r2, Priority.LOW);
		
		try{
            Thread.sleep(3000);
        }catch(InterruptedException e){}
		f1.cancel(true);
		
		myPool.awaitTermination(500, TimeUnit.MILLISECONDS);
		
		System.out.println("done");
	}
	//@Test
	void pauseReasumeTest() {
		System.out.println("pause and resume test:");
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
		
		
		//myPool.shutdown();
		myPool.awaitTermination(500, TimeUnit.MILLISECONDS);
	}

}

/**********************************/
class Run1 implements Runnable
{
	@Override
	public void run()
	{
		int i = 0;
		while(true)
		{
			try{
                Thread.sleep(1500);
            }catch(InterruptedException e){}
			System.out.println("r1");
			++i;
		}
	}
	
}

class Run2 implements Runnable
{
	@Override
	public void run()
	{
		int i = 0;
		while(true)
		{
			try{
                Thread.sleep(1500);
            }catch(InterruptedException e){}
			System.out.println("r2");
			++i;
		}
	}
}

class Run3 implements Runnable
{
	@Override
	public void run()
	{
		int i = 0;
		while(true)
		{
			try{
                Thread.sleep(1500);
            }catch(InterruptedException e){}
			System.out.println("r3");
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
		while(true)
		{
			try{
                Thread.sleep(1500);
            }catch(InterruptedException e){}
			System.out.println("r3");
			++i;
		}
	}
}
