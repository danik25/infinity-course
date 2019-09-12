import java.util.concurrent.*;
import java.util.concurrent.atomic.*;

public class ex1 {
    public static void main(String[] args){
        System.out.println("with runnable:");
        runnableImplement threadRunnable = new runnableImplement();
        new Thread(threadRunnable).start();
        try{
            Thread.sleep(400);
        }catch (InterruptedException e){}

        threadRunnable.stop();
        
        System.out.println("\nwith thread:");
        Thread threadThread = new threadExtend();
        threadThread.start();
        try{
            Thread.sleep(2);
        }catch (InterruptedException e){}
        threadThread.interrupt();

        
    }

}

class runnableImplement implements Runnable
{
    private final AtomicBoolean runningRunnable = new AtomicBoolean(true);

    @Override
    public void run(){
        int cnt = 0;
        while(runningRunnable.get())
        {
            System.out.println("runnable number :" + cnt);
            try{
                Thread.sleep(200);
            }catch (InterruptedException e){}
            ++cnt;
        }
    }

    public void stop() {
        runningRunnable.set(false);
    }
}

class threadExtend extends Thread
{
    @Override
    public void run(){
        int cnt = 0;
        while(Thread.interrupted() == false)
        {
            System.out.println("thread number :" + cnt);
            ++cnt;
        }
    }
}