package il.co.ilrd.threadpool;

import il.co.ilrd.waitablequeue.WaitableQueue;

import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executor;
import java.util.concurrent.Future;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;

import java.util.Comparator;



public class ThreadPool implements Executor{
	private WaitableQueue<Task<?>> waitableQueue; 
	
	public ThreadPool(int threadNumber){
		waitableQueue = new WaitableQueue<Task<?>>(new taskCompare());
	}
	
	public enum Priority {
		LOW(0), MEDIUM(5), HIGH(10);
		
		private final int priority; 

		private Priority(int priority){
			this.priority = priority; 
		}
	}

	private class Manager extends Thread{
	}


	@Override
	public void execute(Runnable task) {}
	
	public Future<Void> submit(Runnable task, int priority){
		return null; 
	}
	
	public <T> Future<T> submit(Runnable task, int priority, T v){
		return null; 
	}
	
	public <T> Future<T> submit(Callable<T> task){
		return null; 
	}

	public <T> Future<T> submit(Callable<T> task, int priority){
		return null; 
	}

	public void setNumOfThreads (int newNumofThreads){
		
	}
	
	public void pause() {
		
	}
	
	public void resume() {
		
	}
	
	public void shutdown() {
		
	}
	
	public List<Runnable> shutdownNow(){
		return null; 
	}
	
	public boolean awaitTermination(long timeout, TimeUnit unit){
		return false; 
	}
	
	private class Task<T>  implements Comparable<Task<?>>, Runnable{
		
		@Override
		public void run() {}

		@Override
		public int compareTo(Task<?> t) {
			return 0;
		}
	
		private class TaskFuture implements Future<T>{
			
			//private  T result;
			//private boolean isCancled; 
			//private boolean isDone;
			
			@Override
			public boolean cancel(boolean mayInterruptIfRunning) {
				return false;
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
			
			class taskCompare implements Comparator<Task<?>> 
			{ 
				@Override
			    public int compare(Task a, Task b) 
			    { 
			        return a.compareTo(b); 
			    } 
			}
		}	
	}
}


