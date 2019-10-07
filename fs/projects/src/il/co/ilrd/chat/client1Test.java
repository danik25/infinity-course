package il.co.ilrd.chat;

import java.net.InetAddress;
import java.net.UnknownHostException;

public class client1Test {
	public static void main(String [] args) throws UnknownHostException
	{
		InetAddress ip = InetAddress.getByName("10.1.0.242");
		int port = 44444;
		ChatClient client = new ChatClient(port, ip);
		client.start();
	}
}
