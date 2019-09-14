import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ScheduledThreadPoolExecutor;
import java.util.concurrent.ScheduledExecutorService;
import java.util.concurrent.TimeUnit;

public class ex2 {
    public static void main(String[] args){
        
        ExecutorService executor1 = Executors.newSingleThreadExecutor();
        ExecutorService executor2 = Executors.newFixedThreadPool(3);
        ExecutorService executor3 = Executors.newCachedThreadPool();
        ExecutorService executor4 = Executors.newScheduledThreadPool(3);

        //single thread pool
        System.out.println("single thread pool");
        /**************/
        for (int i = 0; i < 5; ++i) {
			Runnable worker = new singleThreadPoll(i);
			executor1.execute(worker);
		}
		executor1.shutdown();

		while (!executor1.isTerminated())
			;
        System.out.println("All threads finished");
        /**************/

        // fixed thread pool of size 3
        System.out.println("\nsingle thread pool");
        /**************/
        for (int i = 0; i < 5; ++i) {
			Runnable worker = new singleThreadPoll(i);
			executor2.execute(worker);
		}
		executor2.shutdown();

		while (!executor2.isTerminated())
			;
        System.out.println("All threads finished");
        /**************/

        // cached thread pool
        System.out.println("\ncached thread pool");
        /**************/
        for (int i = 0; i < 5; ++i) {
			Runnable worker = new singleThreadPoll(i);
			executor3.execute(worker);
		}
		executor3.shutdown();

		while (!executor3.isTerminated())
			;
        System.out.println("All threads finished");
        /**************/

        // scheduled thread pool
        System.out.println("\nscheduled thread pool");
        /**************/
        for (int i = 0; i < 5; ++i) {
			Runnable worker = new singleThreadPoll(i);
			executor4.execute(worker);
		}
		executor4.shutdown();

		while (!executor4.isTerminated())
			;
        System.out.println("All threads finished");
        /**************/
    }
}

class singleThreadPoll implements Runnable {
    int num;
    singleThreadPoll(int num)
    {
        this.num = num;
    }
    @Override
    public void run() {
        System.out.println("singleThreadPoll number: " + num);
    }
}

