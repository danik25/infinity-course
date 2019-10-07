package il.co.ilrd.chat;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

public class ChatClient{
	private String clientName;
	private SocketChannel socketChannel;
	boolean contFlag = true;
	
	private int port;
	private InetAddress ip;
	private String token;
	
	ChatClient(int port, InetAddress ip)
	{
		this.port = port;
		this.ip = ip;	
	}
	
	public void start()
	{
		try {
			socketChannel = SocketChannel.open();
			socketChannel.connect(new InetSocketAddress(ip, port));
			
			new Thread(new readFromServerAndPrint()).start();
			new readFromUserSendToSocket().run();
			
		} catch (IOException e) {
			System.err.println("failed in creating the socket");
			e.printStackTrace();
		}
	}
	class readFromUserSendToSocket implements Runnable
	{
		ByteBuffer readBuffer = ByteBuffer.allocate(100);
		@Override
		public void run()
		{
			try 
			{
				System.out.println("please enter a name:");
				BufferedReader buff = new BufferedReader(new InputStreamReader(System.in));
				connectionMessage(buff.readLine());
				System.out.println("start chatting!");

				while(contFlag )
				{
					readBuffer.clear();
					String msgLine = buff.readLine();
					if(msgLine.contentEquals("exit"))
					{
						msgLine = disconnectMsg(msgLine);
					}
					else
					{
						msgLine = regularMsg(msgLine);
					}
					readBuffer.put(msgLine.getBytes());
					readBuffer.flip();
					socketChannel.write(readBuffer);
				}
			} catch (IOException e) {
				System.err.println("client: failed at reading from user");
				e.printStackTrace();
			}
		}
	}
	
	class readFromServerAndPrint implements Runnable
	{
		@Override
		public void run()
		{
			while(contFlag )
			{
				try {		
					ByteBuffer serverMsgBytesBuffer = ByteBuffer.allocate(100);
					socketChannel.read(serverMsgBytesBuffer);
					String stringMsg = new String(serverMsgBytesBuffer.array()).trim();
					
					if(stringMsg.startsWith("<con:"))
					{
						token = stringMsg;
						token = token.substring(token.indexOf(":") + 1);
						token = token.substring(0, token.indexOf(">"));
					}
					else if(stringMsg.startsWith("<dis:"))
					{
						System.out.println(clientName + " exiting");
					}
					else
					{
						System.out.println(stringMsg);
					}
					
				} catch (IOException e) {
					System.err.println("failed at reading from server");
					e.printStackTrace();
				}
			}
			try {
				socketChannel.close();
			} catch (IOException e) {
				System.err.println("failed at closing the socket");
				e.printStackTrace();
			}
		}
	}
/* private methods */
/*******************************************/	
	private void connectionMessage(String name) throws IOException
	{
		ByteBuffer connectionBuffer = ByteBuffer.allocate(100);
		
		clientName = name;
		
		String newMsg = new String("<con:" + name + ">");
		connectionBuffer.put(newMsg.getBytes());
		connectionBuffer.flip();
		socketChannel.write(connectionBuffer);
	}
	
	private String regularMsg(String msg)
	{
		return "<msg:" + token + ", " + clientName + " | " + msg + " >";
	}
	private String disconnectMsg(String msg)
	{
		contFlag = false;
		return "<dis:" + token + ">";
	}
	
}



