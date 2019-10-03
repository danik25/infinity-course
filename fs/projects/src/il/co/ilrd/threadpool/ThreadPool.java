package il.co.ilrd.threadpool;
import il.co.ilrd.waitablequeue.WaitableQueue;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executor;
import java.util.concurrent.Future;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;
import java.util.concurrent.Executors;


public class ThreadPool implements Executor{
	private WaitableQueue<Task<?>> waitableQueue; 
	private int threadNum;
	private int initialThreadNum;
	private Semaphore pauseSemaphore = new Semaphore(0);
	private Semaphore terminationSemaphore = new Semaphore(0);
	
	private boolean shutDownFlag = false; 
	private boolean isPaused = false;
	
	public ThreadPool(int threadNumber) {
		threadNum = threadNumber;
		initialThreadNum = threadNumber;
		
		waitableQueue = new WaitableQueue<ThreadPool.Task<?>>(Task::compareTo);
		for (int i = 0; i < threadNum; ++i) {
			new ThreadReference().start();
		}
	}
	
	public enum Priority {
		LOW(0), MEDIUM(5), HIGH(10);
		
		final int priority; 

		private Priority(int priority){
			this.priority = priority; 
		}
	}
	
	private class ThreadReference extends Thread{
		private Task <?> newTask;
		private boolean threadShutDown = false;
		
		@Override
		public  void run() {
			while(threadShutDown == false)
			{
				newTask = waitableQueue.dequeue();
				newTask.run();
			}
			terminationSemaphore.release();
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
			Task<T> newTask = new Task<T>(task, priority.priority);
			waitableQueue.enqueue(newTask);
			return newTask.futureAns;
		}
		return null;
	}
	
/*************************/	
	private <T> void submitInnerTasks(Runnable task, int priority)
	{
		Task<T> newTask = new Task<T>(Executors.callable(task, null), priority);
		waitableQueue.enqueue(newTask);
		
	}
/*************************/	
	
	public void setNumOfThreads (int newNumofThreads){
		if(shutDownFlag || isPaused)
		{
			return;
		}
		if (newNumofThreads > threadNum ) { 
			initialThreadNum = newNumofThreads;
			
			for (int i = threadNum; i < newNumofThreads; ++i) {
				new ThreadReference().start();
			}
		} else {
			for (int i = 0; i < threadNum - newNumofThreads; ++i) {
				PoisionPill p = new PoisionPill();
				submitInnerTasks(p, Priority.HIGH.priority + 1);
			}
		}
		threadNum = newNumofThreads;
	}
	
	public void pause() {
		Runnable pauseTask = new Runnable() {
			@Override
			public void run()
			{
				try
				{
					pauseSemaphore.acquire();
				}catch(InterruptedException e) {System.out.println("failed pause");}
			}
		};
		isPaused = true;
		for(int i = 0; i < threadNum; ++i)
		{
			submitInnerTasks(pauseTask, Priority.HIGH.priority + 1); 
		}
	}

	/**********************/
	private class PoisionPill implements Runnable
	{
		@Override
		public void run()
		{
			((ThreadReference)Thread.currentThread()).threadShutDown = true;
		}
	}
	/**********************/
	
	public void resume() {
		pauseSemaphore.release(threadNum);
		isPaused = false;
	}
	
	public void shutdown() {
		
		if(shutDownFlag) //not allowing double shutdown
		{
			return ;
		}
		
		shutDownFlag = true;
		PoisionPill p = new PoisionPill();
		
		for(int i = 0; i < threadNum; ++i)
		{
			submitInnerTasks(p, Priority.LOW.priority - 1);
		}	
	}
	
	public boolean awaitTermination(long timeout, TimeUnit unit){
		boolean ans = true;
		try{
			ans = terminationSemaphore.tryAcquire(initialThreadNum, timeout, unit);

		}catch(InterruptedException e){System.out.println(e);}
		return ans; 
	}
	
	private static class Task<T>  implements Comparable<Task<?>>, Runnable{
		private Callable<T> task;
		private int taskPriority;
		private State state = State.WAITING;
		private TaskFuture futureAns = new TaskFuture();
		
		Task(Callable<T> task, int priority)
		{
			this.task = task;
			taskPriority = priority;
		}
		
		private enum State
		{
			RUNNING, WAITING, DONE, CANCELED, PAUSED;
		}
		
		@Override
		public void run() {
			try
			{
				futureAns.result = task.call();
				if(state != State.CANCELED)
				{
					state = State.DONE;
				}

				futureAns.taskIsDoneSem.release();
			}catch (Exception e) {
				System.out.println("failed execution of a task");
				e.printStackTrace();
			}
			
		}

		@Override
		public int compareTo(Task<?> otherTask) {
			return otherTask.taskPriority - taskPriority;
		}	
	
		private class TaskFuture implements Future<T>{
			
			private T result;
			private Semaphore taskIsDoneSem = new Semaphore(0);
			
			@Override
			public boolean cancel(boolean mayInterruptIfRunning){
				task = () -> {return null;};
				state = State.CANCELED;
				
				return true;
			}

			@Override
			public boolean isCancelled() {

				return (state == State.CANCELED);
			}

			@Override
			public boolean isDone() {
				return (state == State.DONE || state == State.CANCELED);
			}

			@Override
			public T get() throws InterruptedException, ExecutionException {
				if(state == State.CANCELED)
				{
					throw new ExecutionException("the task has been cancelled!", null);
				}
				taskIsDoneSem.acquire();
				return result;
			}

			@Override
			public T get(long timeout, TimeUnit unit)
					throws InterruptedException, ExecutionException, TimeoutException {
				if(state == State.CANCELED)
				{
					throw new ExecutionException("the task has been cancelled!", null);
				}
				if (false == taskIsDoneSem.tryAcquire(timeout, unit))
				{
					throw new TimeoutException("time out!");
				}
				return result;
			}	
		}
	}
}
