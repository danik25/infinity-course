package il.co.ilrd.logmonitorNetworking;

//import java.io.BufferedWriter;
//import java.io.FileWriter;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
//import java.net.SocketException;
import java.util.Observable;
import java.util.Observer;



public class LogMonitorNetworkingTest {	
	public static void main(String [] args) throws Exception 
	{
		InetAddress ip = InetAddress.getByName("127.0.1.1"); 
		System.out.println(ip);
		Observer reg = new Observer() {
			@Override
			public void update(Observable arg0, Object arg) {
				try {
					DatagramSocket clientSocket = new DatagramSocket();
					DatagramPacket sendPacket = new DatagramPacket(((String)arg).getBytes(), ((String)arg).length(), ip, 1234);
					clientSocket.send(sendPacket); 
				} catch (IOException e) {
					e.printStackTrace();
				} 

			}
		};
		LogMonitorNetworking logger = new LogMonitorNetworking("/var/log/syslog");
		logger.registerObserver(reg);
		logger.startMonitoring();
		
		try {
			Thread.sleep(8000);
		}catch(InterruptedException e) {;}
		System.out.println("stopping");
		logger.stopMonitoring();
		//clientSocket.close();
	}
}


