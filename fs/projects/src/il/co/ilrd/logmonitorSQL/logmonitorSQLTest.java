package il.co.ilrd.logmonitorSQL;
import java.util.Observable;
import java.util.Observer;

import il.co.ilrd.logmonitor.CRUD;



public class logmonitorSQLTest {	
	public static void main(String [] args) throws Exception 
	{
		String url = "jdbc:mysql://localhost/";
		String user = "root";
		String pass = "password";
		String database = "Syslog";
		String table = "Log";
		   
		CRUD <String, Integer> c = new Crudsql(url, user, pass, database, table);
		Observer reg = new Observer() {
			@Override
			public void update(Observable arg0, Object arg) {
				c.create((String)arg);
			}
		};
		LogmonitorSQL logger = new LogmonitorSQL("/var/log/syslog");
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