import java.util.concurrent.*;
import java.util.concurrent.atomic.*;
import java.util.concurrent.locks.ReentrantLock;

public class ex2 {
    public static void main(String[] args){
        long startTime;
        long stopTime;

        System.out.println("regular:");
        Thread thread1 = new Thread(new regular());
        Thread thread2 = new Thread(new regular());
        startTime = System.nanoTime();
        thread1.start();
        thread2.start();
        try{
            thread1.join();
            thread2.join();
        }catch (InterruptedException e){}
        

        stopTime = System.nanoTime();
        System.out.println("counter: " + regular.counter);
        System.out.println("time: " + (stopTime - startTime) / 1000);

        /*********/

        System.out.println("\nsynchronized method:");
        Thread threadSynchronizedMethod1 = new Thread(new synchronizedMethod());
        Thread threadSynchronizedMethod2 = new Thread(new synchronizedMethod());
        startTime = System.nanoTime();
        threadSynchronizedMethod1.start();
        threadSynchronizedMethod2.start();
        try{
            threadSynchronizedMethod1.join();
            threadSynchronizedMethod2.join();
        }catch (InterruptedException e){}

        stopTime = System.nanoTime();
        System.out.println("counter: " + synchronizedMethod.counter);
        System.out.println("time: " + (stopTime - startTime) / 1000);

        /*********/

        System.out.println("\nsynchronized block:");
        Thread threadSynchronizedBlock1 = new Thread(new synchronizedBlock());
        Thread threadSynchronizedBlock2 = new Thread(new synchronizedBlock());
        startTime = System.nanoTime();
        threadSynchronizedBlock1.start();
        threadSynchronizedBlock2.start();
        try{
            threadSynchronizedBlock1.join();
            threadSynchronizedBlock2.join();
        }catch (InterruptedException e){}

        stopTime = System.nanoTime();
        System.out.println("counter: " + synchronizedBlock.counter);
        System.out.println("time: " + (stopTime - startTime) / 1000);

        /*********/

        System.out.println("\natomic:");
        Thread threadAtomicVar1 = new Thread(new atomicVar());
        Thread threadAtomicVar2 = new Thread(new atomicVar());
        startTime = System.nanoTime();
        threadAtomicVar1.start();
        threadAtomicVar2.start();
        try{
            threadAtomicVar1.join();
            threadAtomicVar2.join();
        }catch (InterruptedException e){}

        stopTime = System.nanoTime();
        System.out.println("counter: " + atomicVar.atomicCounter);
        System.out.println("time: " + (stopTime - startTime) / 1000);

        /*********/

        System.out.println("\nreentrent:");
        Thread threadReentrant1 = new Thread(new reentrant());
        Thread threadReentrant2 = new Thread(new reentrant());
        startTime = System.nanoTime();
        threadReentrant1.start();
        threadReentrant2.start();
        try{
            threadReentrant1.join();
            threadReentrant2.join();
        }catch (InterruptedException e){}

        stopTime = System.nanoTime();
        System.out.println("counter: " + reentrant.counter);
        System.out.println("time: " + (stopTime - startTime) / 1000);
    }
}

class regular implements Runnable
{
    static int counter = 0;

    @Override
    public void run()
    {
        for(int i = 0; i < 10000000; ++i)
        {
            ++counter;
        }
    }
}

class synchronizedMethod implements Runnable
{
    static int counter = 0;

    @Override
    public void run()
    {
        increment();
    }

    static synchronized void increment()
    {
        for(int i = 0; i < 10000000; ++i)
        {
            ++counter;
        }
    }
}

class synchronizedBlock implements Runnable
{
    static int counter = 0;

    @Override
    public void run()
    {
        increment();
    }

    static void increment()
    {
        synchronized(synchronizedBlock.class)
        {
            for(int i = 0; i < 10000000; ++i)
            {
                ++counter;    
            }
        }
    }
}

class atomicVar implements Runnable
{
    static AtomicInteger atomicCounter = new AtomicInteger();

    @Override
    public void run()
    {
        increment();
    }

    static void increment()
    {
        for(int i = 0; i < 10000000; ++i)
        {
            atomicCounter.getAndIncrement();  
        }
    }
}


class reentrant implements Runnable
{
    static int counter = 0;
    private static ReentrantLock reLock = new ReentrantLock();

    @Override
    public void run()
    {
        increment();
    }

    static void increment()
    {
        reLock.lock(); 
        try
        {
            for(int i = 0; i < 10000000; ++i)
            {
                ++counter;    
            }
        }catch(Exception e){}
        finally
        { 
            reLock.unlock(); 
        }
    }
}