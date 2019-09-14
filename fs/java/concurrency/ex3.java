
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicBoolean;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import java.util.LinkedList;
import java.util.List;

public class ex3 {
    public static void main(String[] args){
        
        //onePerKindSemaphore.start();
        //onePerKindAtomic.start();
        //TwoMultLinkedNSync.start();
        //TwoMultLinkedNSyncNSemaphore.start();
        oneConsMultProd.start();
    }
}

class oneConsMultProd
{
    static Integer prodMessage = 0;
    static int i = 0;

    static final Lock lock = new ReentrantLock();
    static final Condition notFull  = lock.newCondition();

    static void start()
    {
        Semaphore sem = new Semaphore(0);
    
        class prod implements Runnable{
            @Override
            public void run()
            {
                while(true)
                {
                    try{
                        Thread.sleep(1500);
                    }catch(InterruptedException e){};

                    if(sem.availablePermits() == 3)
                    {   
                        lock.lock();
                        prodMessage = ++i;
                        
                        try{
                            sem.acquire(3);
                        }catch(InterruptedException e){};
                        notFull.signalAll();
                        
                        lock.unlock();
                    }
            }    
        }
    }
    
    
        class cons implements Runnable{
            @Override
            public void run()
            {
                while(true)
                { 
                    lock.lock();
                    try{
                        sem.release();

                        notFull.await();
                        System.out.println(prodMessage);
                        
                    }catch(InterruptedException e){};
                    lock.unlock();
                }
            }
        }
        
        
        Thread producer = new Thread(new prod());
        Thread consumer1 = new Thread(new cons());
        Thread consumer2 = new Thread(new cons());
        Thread consumer3 = new Thread(new cons());

        producer.start();
        consumer1.start();
        consumer2.start();
        consumer3.start();
    }
    
    
}

class onePerKindSemaphore
{
    static void start()
    {
        Semaphore sem1 = new Semaphore(1); 
        Semaphore sem2 = new Semaphore(0); 
        Runnable r1 = new Runnable(){
            @Override
            public void run() 
            {
                while(true)
                {
                    try{
                        sem1.acquire(); 
                    }catch(InterruptedException e){};
                    System.out.println("\tping");
                    sem2.release();
                }
            }
        };
        Runnable r2 = new Runnable(){
            @Override
            public void run()
            {
                while(true)
                {
                    try{
                        sem2.acquire(); 
                    }catch(InterruptedException e){};
                    System.out.println("pong");
                    sem1.release();
                }
            }
        };
    

        Thread producer = new Thread(r1);
        Thread consumer = new Thread(r2);

        producer.start();
        consumer.start();
     
    }  
}

class onePerKindAtomic
{
    static void start()
    {
        AtomicBoolean flag = new AtomicBoolean(true);

        Runnable r1 = new Runnable(){
            @Override
            public void run() 
            {
                while(true)
                {
                    if(flag.get())
                    {
                        System.out.println("\tping");
                        flag.set(false);
                    }
                }
            }
        };
        Runnable r2 = new Runnable(){
            @Override
            public void run()
            {
                while(true)
                {
                    if(!flag.get())
                    {
                        System.out.println("pong");
                        flag.set(true);
                    }
                }
            }
        };
    

        Thread producer = new Thread(r1);
        Thread consumer = new Thread(r2);

        producer.start();
        consumer.start();
     
    }  
}

class TwoMultLinkedNSync
{
    static LinkedList<Integer> list = new LinkedList<>();
    static int i = 0;

    static void start()
    {
        Runnable cons = new Runnable(){
            @Override
            public void run() 
            {
                while(true)
                {

                    synchronized(list)
                    {
                        if(list.size() > 0)
                        {
                            System.out.println(list.remove());
                        }
                    }
                }
            }
        };
        Runnable prod = new Runnable(){
            @Override
            public void run()
            {
                while(true)
                {
                    synchronized(list)
                    {
                        list.add(i);
                    }
                    ++i;
                }
            }
        };

        Thread producer1 = new Thread(prod);
        Thread producer2 = new Thread(prod);
        Thread consumer1 = new Thread(cons);
        Thread consumer2 = new Thread(cons);

        producer1.start();
        consumer1.start();
        producer2.start();
        consumer2.start();
    } 
}

class TwoMultLinkedNSyncNSemaphore
{
    static LinkedList<Integer> list = new LinkedList<>();
    static int i = 0;
    static Semaphore sem = new Semaphore(0); 

    static void start()
    {
        Runnable cons = new Runnable(){
            @Override
            public void run() 
            {
                while(true)
                {
                    try{
                        sem.acquire(); 
                    }catch(InterruptedException e){};
                    synchronized(list)
                    {
                        System.out.println(list.remove());
                    }
                }
            }
        };
        Runnable prod = new Runnable(){
            @Override
            public void run()
            {
                while(true)
                {
                    synchronized(list)
                    {
                        list.add(i);
                        sem.release();
                    }
                    ++i;
                }
            }
        };

        Thread producer1 = new Thread(prod);
        Thread producer2 = new Thread(prod);
        Thread consumer1 = new Thread(cons);
        Thread consumer2 = new Thread(cons);

        producer1.start();
        consumer1.start();
        producer2.start();
        consumer2.start();
    } 
}