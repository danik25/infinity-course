package il.co.ilrd.threadpool;
import il.co.ilrd.waitablequeue.WaitableQueue;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executor;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.Executors;


public class ThreadPool implements Executor{
	private WaitableQueue<Task<?>> waitableQueue; 
	private List<Thread> threadList = new ArrayList<>();
	int threadNum;
	
	private boolean shutDownFlag = false; 
	
	static final Lock lock = new ReentrantLock();
    static final Condition pausedQueue  = lock.newCondition();
	
	public ThreadPool(int threadNumber){
		threadNum = threadNumber;
		waitableQueue = new WaitableQueue<ThreadPool.Task<?>>(Task::compareTo);
		for (int i = 0; i < threadNum; ++i) {
			threadList.add(new ThreadReference());
			threadList.get(i).start();
		}
	}
	
	public enum Priority {
		LOW(0), MEDIUM(5), HIGH(10);
		
		public final int priority; 

		private Priority(int priority){
			this.priority = priority; 
		}
	}
	
	private class ThreadReference extends Thread{
		Task <?> newTask;

		@Override
		public  void run() {
			while(shutDownFlag == false)
			{
				System.out.println("waiting");
				newTask = waitableQueue.dequeue();
				System.out.println("start running");
				newTask.run();
			}
		}
	}

	@Override
	public void execute(Runnable task) {
		submit(Executors.callable(task, null), Priority.MEDIUM);
	}
	
	public Future<Void> submit(Runnable task, Priority priority){

		return submit(Executors.callable(task, null), priority);
	}
	
	public <T> Future<T> submit(Runnable task, Priority priority, T v){
		return submit(Executors.callable(task, v), priority);
	}
	
	public <T> Future<T> submit(Callable<T> task){
		return submit(task, Priority.MEDIUM);
	}

	public <T> Future<T> submit(Callable<T> task, Priority priority){
		if(shutDownFlag == false)
		{
			Task<T> newTask = new Task<T>(task, priority);
			waitableQueue.enqueue(newTask);
			return newTask.new TaskFuture();
		}
		return null;
	}

	public void setNumOfThreads (int newNumofThreads){
		if (newNumofThreads > threadNum ) {
			int amountOfnewThreads = newNumofThreads - threadNum; 
			for (int i = 0; i < amountOfnewThreads; ++i) {
				// create and run threads;
			}
		} else {
			int amountOfnewThreads = threadNum - newNumofThreads;
			for (int i = 0; i < amountOfnewThreads; ++i) {
				//waitableQueue.enqueue(removeTask());
			}
		}
	}
	
	public void pause() {
		Runnable pauseTask = new Runnable() {
			@Override
			public void run()
			{
				lock.lock();
				try
				{
					pausedQueue.await();
					System.out.println("finish waiting");
				}catch(InterruptedException e) {System.out.println("failed pause");}
				
				lock.unlock();
			}
		};
		for(int i = 0; i < threadNum; ++i)
		{
			submit(Executors.callable(pauseTask, null), Priority.HIGH);
		}
	}
	
	public void resume() {
		lock.lock();
		pausedQueue.signalAll();
        lock.unlock();
	}
	
	public void shutdown() {
		shutDownFlag = true;
		
	}
	
	public boolean awaitTermination(long timeout, TimeUnit unit){
		try{  
			for (Thread t : threadList) {
				t.join();
			} 
			 }catch(Exception e){System.out.println(e);}
		return true; 
	}
	
	private class Task<T>  implements Comparable<Task<?>>, Runnable{
		Callable<T> task;
		Priority taskPriority;
		Future<T> futureAns = new TaskFuture();
	
		Task(Callable<T> task, Priority priority)
		{
			this.task = task;
			taskPriority = priority;
		}
		@Override
		public void run() {
			try
			{
				task.call();
			}catch (Exception e) {
				System.out.println("failed execution of a task");
				e.printStackTrace();
			}
			
		}

		@Override
		public int compareTo(Task<?> o) {
			return taskPriority.compareTo(o.taskPriority);
		}	
	
		private class TaskFuture implements Future<T>{
			
			//private  T result;
			//private boolean isCancled; 
			//private boolean isDone;
			
			@Override
			public boolean cancel(boolean mayInterruptIfRunning){
				System.out.println("trying to cancel");
				
				//TODO:
				//threadList.get(threadIndex).interrupt();
				return true;
			}

			@Override
			public boolean isCancelled() {
				return false;
			}

			@Override
			public boolean isDone() {
				return false;
			}

			@Override
			public T get() throws InterruptedException, ExecutionException {
				return null;
			}

			@Override
			public T get(long timeout, TimeUnit unit)
					throws InterruptedException, ExecutionException, TimeoutException {
				return null;
			}	
		}

	}
}
