package il.co.ilrd.logmonitorNetworking;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;

import il.co.ilrd.logmonitor.CRUD;
//import il.co.ilrd.logmonitor.CrudFile;

public class Server {
	public static void main(String [] args) throws Exception 
	{
		CRUDNetworking <String, String> c = new CrudFile();
		DatagramSocket ds = new DatagramSocket(1234); 
		byte[] receive = new byte[65535]; 
		DatagramPacket DpReceive = null; 
        while (true) 
        { 
  
            // Step 2 : create a DatgramPacket to receive the data. 
            DpReceive = new DatagramPacket(receive, receive.length); 
  
            // Step 3 : revieve the data in byte buffer. 
            ds.receive(DpReceive); 
            c.create((receive).toString());
  
            // Exit the server if the client sends "bye" 
            /*if (data(receive).toString().equals("bye")) 
            { 
                System.out.println("Client sent bye.....EXITING"); 
                break; 
            } */
  
            // Clear the buffer after every message. 
            receive = new byte[65535]; 
        }
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