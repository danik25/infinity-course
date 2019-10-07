package il.co.ilrd.chat;

import java.io.IOException;
import java.net.InetAddress;

public class client2Test {
	public static void main(String [] args) throws IOException
	{
		InetAddress ip = InetAddress.getByName("10.1.0.242");
		int port = 44444;
		ChatClient client = new ChatClient(port, ip);
		client.start();
	}
}
