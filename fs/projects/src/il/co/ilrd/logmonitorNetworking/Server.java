package il.co.ilrd.logmonitorNetworking;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;

public class Server {
	public static void main(String [] args) throws Exception 
	{
		System.out.println("server");
		CRUDNetworking <String, String> c = new CrudFile();
		DatagramSocket serverSocket = new DatagramSocket(1234); 
		byte[] receive = new byte[65535]; 
		boolean serverFlag = true;
		System.out.println("starting");
        while (serverFlag) 
        { 
        	DatagramPacket DpReceive = new DatagramPacket(receive, receive.length); 
        	serverSocket.receive(DpReceive);
            c.create(new String(receive, 0, DpReceive.getLength()));
        }
        serverSocket.close();
        c.close();
	}
}

class CrudFile implements CRUDNetworking<String, String>
{	
	BufferedWriter fileWriter;
	
	CrudFile()
	{
		try
		{
			fileWriter = new BufferedWriter(new FileWriter("/home/student/Desktop/syslogNetworking_logger.txt"));
		}catch(IOException e){System.out.println("creation if a file failed");}
	}
	
	@Override
	public void close() throws Exception {
		fileWriter.close();
	}

	@Override
	public String create(String item) {		
		
		try {
			System.out.println("writing: " + item);
			 fileWriter.write(item + "\n");
			 fileWriter.flush();
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