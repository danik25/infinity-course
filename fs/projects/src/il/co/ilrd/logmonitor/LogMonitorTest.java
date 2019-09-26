package il.co.ilrd.logmonitor;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Observable;
import java.util.Observer;



class LogMonitorTest {	
	public static void main(String [] args) throws Exception 
	{
		CRUD <String, String> c = new CrudFile();
		Observer reg = new Observer() {
			@Override
			public void update(Observable arg0, Object arg) {
				c.create((String)arg);
			}
		};
		LogMonitor logger = new LogMonitor("/var/log/syslog");
		logger.registerObserver(reg);
		logger.startMonitoring();
		
		try {
			Thread.sleep(8000);
		}catch(InterruptedException e) {;}
		System.out.println("stopping");
		logger.stopMonitoring();
		c.close();
	}
}

class CrudFile implements CRUD<String, String>
{	
	BufferedWriter fileWriter;
	
	CrudFile()
	{
		try
		{
			fileWriter = new BufferedWriter(new FileWriter("/home/student/Desktop/syslog_logger.txt"));
		}catch(IOException e){System.out.println("creation if a file failed");}
	}
	
	@Override
	public void close() throws Exception {
		fileWriter.close();
	}

	@Override
	public String create(String item) {		
		
		try {
			 fileWriter.write(item + "\n");
		} catch (IOException e) {
			System.out.println("writing the information to a log failed");
			System.out.println(e);
		}
		
		return null;
	}

	@Override
	public String read(String key) {
		return null;
	}

	@Override
	public void update(String key, String item) {
		;
	}

	@Override
	public void delete(String key) {
		;
	}
}
