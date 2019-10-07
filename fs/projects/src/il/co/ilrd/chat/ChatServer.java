package il.co.ilrd.chat;



/*
 * Protocols for setting and maintaining client - server communication: 
 * 
 * 	 	1 - "<con:[usr_name]>" (for example "<con:Dr.Piglet>" )
 * 			asks from server to connect user 
 * 			server will return a unique token to the user in format of <con:[token]> (for example <con:%@621afrat52>)
 * 			
 * 		2 - "<dis:[token]>" - servers closes connection with the message sender and removes him from map
 * 
 * 		3 - all other messages will be sent with the prefix <msg:[token],[name]|[msg]> to everyone including sender
 * 
 */

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Set;
import java.util.UUID;

public class ChatServer {
	private HashMap <String,Peer > namesMap; 
	private Selector selector;
	private ServerSocketChannel serverSocketChannel;
	SelectionKey key;
	int port;
	
	public ChatServer (int port) throws IOException {
		this.port = port;
		
		serverSocketChannel = ServerSocketChannel.open();
		serverSocketChannel.configureBlocking(false);
		serverSocketChannel.socket().bind(new InetSocketAddress(port));
		
		selector = Selector.open();
		key = serverSocketChannel.register(selector, SelectionKey.OP_ACCEPT);

		namesMap = new HashMap<String, ChatServer.Peer>();
	}
	
	private class Peer{
		private SocketChannel socket; 
		
		Peer(String name, SocketChannel socket)
		{
			this.socket = socket;
		}
		
		public void close() throws IOException {
			socket.close();
		}
		
		public void send(String message) {
			try {
				sendMessege(message, this.socket);
			} catch (IOException e) {
				System.err.println("failed at sending the message");
				e.printStackTrace();
			}
		}
	}
	
	private void runMainLoop() throws IOException
	{
		while(true)
		{
			selector.select();
			Set<SelectionKey> selectedKeys = selector.selectedKeys();
			Iterator<SelectionKey> keyIterator = selectedKeys.iterator();
			
			while(keyIterator.hasNext()) 
			{
			    SelectionKey key = (SelectionKey)keyIterator.next();

			    if(key.isAcceptable()) {
			  
	                SocketChannel clientSocket = serverSocketChannel.accept();
	                clientSocket.configureBlocking(false);
	                clientSocket.register(selector, SelectionKey.OP_READ);
			    } 
			    else if (key.isReadable()) {
			    	readableHandle(key);
			    } 

			    keyIterator.remove();
			}
		}
	}
	
	public void start() {
		try {
			System.out.println("server starts");
			runMainLoop();
		} catch (IOException e) {
			System.err.println("failed server");
			e.printStackTrace();
		}
	}
	
/* private methods */
/*************************************************************/	
	private String isConnection(String input, SocketChannel clientSocket)
	{
		UUID uuid = UUID.randomUUID();
		String token = uuid.toString();
		String name = input.substring(input.indexOf(":") + 1);
		namesMap.put(token, new Peer(name, clientSocket));
		
		return "<con:" + token + ">";
	}

	private void readableHandle(SelectionKey key)
	{
		try
		{
			SocketChannel clientSocket = (SocketChannel) key.channel();
			ByteBuffer msgBuffer =  ByteBuffer.allocate(100);
	    	clientSocket.read(msgBuffer);

	    	String input = new String(msgBuffer.array()).trim();
	    	
	    	/* if it is a connection */
	    	if(input.startsWith("<con:"))
	    	{
	    		input = isConnection(input, clientSocket);
				sendMessege(input, clientSocket);
	    	}
	    	
	    	else if(input.startsWith("<dis:"))
			{
	    		disconnection(input.substring(input.indexOf(":") + 1, input.indexOf(">")), key);
			}
	    	
	    	/* if it is a regular message */
	    	else
	    	{
	    		broadcast(input);
	    	}
		}catch (Exception e) {
			System.err.println("server: failed reading from user");
			e.printStackTrace();
			return;
		}
	}
	
	private void sendMessege(String msg, SocketChannel socket) throws IOException
	{
		ByteBuffer msgBuffer = ByteBuffer.allocate(100);
		msgBuffer.clear();
		msgBuffer.put(msg.getBytes());
		msgBuffer.flip();
		socket.write(msgBuffer);
	}
	
	private void broadcast(String msg) {
		for(Peer p : namesMap.values())
		{
			p.send(msg);
		}
	}
	private void disconnection(String token, SelectionKey key)
	{
		try {
			namesMap.get(token).close();
		} catch (IOException e) {
			System.err.println("failed closing of a client");
			e.printStackTrace();
		}
		namesMap.remove(token);
	}
/*************************************************************/
}