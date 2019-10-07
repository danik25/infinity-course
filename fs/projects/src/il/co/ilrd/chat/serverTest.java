package il.co.ilrd.chat;

import java.io.IOException;

public class serverTest {
	public static void main(String [] args) throws IOException
	{
		int port = 44444;
		ChatServer chatServer = new ChatServer(port);
		chatServer.start();
	}
}
