package il.co.ilrd.logmonitor;

import java.util.Observable;
import java.util.Observer;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.ClosedWatchServiceException;
import java.nio.file.FileSystems;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardWatchEventKinds;
import java.nio.file.WatchEvent;
import java.nio.file.WatchKey;
import java.nio.file.WatchService;

public class LogMonitor {
	
	private innerObservable observable;
	private Path filePath;
	
	private String fileName;
	private String fullName;
	
	WatchService watchService;
	BufferedReader br;
	
	private boolean monitoringFlag = true;
	
	public LogMonitor(String monitoredPath) 
	{
		fullName = monitoredPath;
		observable = new innerObservable();
		filePath = Paths.get(monitoredPath);
		
		fileName = filePath.getFileName().toString();	
	}
	
	public void startMonitoring() throws IOException{
		watchService = FileSystems.getDefault().newWatchService();
		filePath.getParent().register(watchService, StandardWatchEventKinds.ENTRY_MODIFY);
		
		new Thread(new monitor()).start();
	}
	
	public void stopMonitoring() throws  IOException{
		watchService.close();
	}
	
	public void registerObserver(Observer observer) {
		observable.addObserver(observer);
	}
	
	public void unregisterObserver(Observer observer) {
		observable.deleteObserver(observer);
	}
	
	class monitor implements Runnable
	{
		BufferedReader br;
		String line;
		
		monitor()
		{
			try {
				br = new BufferedReader(new FileReader(fullName));
			} catch (FileNotFoundException e) {
				System.out.println("creating new file buffer failed");
				e.printStackTrace();
			}
		}
		
		@Override
		public void run() 
		{
			try {
				readAndNotify(br);
				
				WatchKey key;	
				while (monitoringFlag && (key = watchService.take()) != null) 
				{
				    for (WatchEvent<?> event : key.pollEvents()) {
				    	if(event.context().equals(Paths.get((fileName))))
				    	{
				    		readAndNotify(br);
				    	}
				    }
				    key.reset();
				} 
				
			}catch (InterruptedException e) {
				System.out.println("iterating on the key");
				e.printStackTrace();
			}catch (ClosedWatchServiceException e)
			{
				try {
					br.close();
				} catch (IOException e1) {
					e1.printStackTrace();
				}
				System.out.println("closed");
			} 
		}
		void readAndNotify(BufferedReader br)
		{
			try {
				while ((line = br.readLine()) != null) {
					observable.signalAll(line);
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}
	
	private class innerObservable extends Observable
	{
	    void signalAll(String changes)
	    {
	        setChanged();
	        notifyObservers(changes);
	    }
	}
}

