package il.co.ilrd.chat;

import java.io.BufferedReader;
import java.io.IOException;
import java.net.Socket;
import java.nio.channels.Channel;
import java.nio.channels.SelectionKey;
import java.nio.ByteBuffer;

/*
 * Protocols for setting and maintaining client - server communication: 
 * 
 * 	 	1 - "<con:[usr_name]>" (for example "<con:Dr.Piglet>" )
 * 			asks from server to connect user 
 * 			server will return a unique token to the user in format of <con:[token]> (for example <con:%@621afrat52>)
 * 			
 * 		2 - "<dis:[token]>" - servers closes connection with the message sender and removes him from map
 * 
 * 		3 - all other messages will be sent with the prefix <msg:[token][name]:[msg]> to everyone including sender
 * 
 */

import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.HashMap;
import java.util.Set;

import com.sun.corba.se.impl.ior.ByteBuffer;

import il.co.ilrd.LinkedList.Iterator;

public class ChatServer {
	private HashMap <String,Peer > namesMap; 
	private Selector selector;
	private ServerSocketChannel serverSocketChannel;
	SelectionKey key;
	int port;
	
	public ChatServer (int port) throws IOException {
		serverSocketChannel = ServerSocketChannel.open();
		serverSocketChannel.configureBlocking(false);
		
		selector = Selector.open();
		key = serverSocketChannel.register(selector, SelectionKey.OP_READ);
		
		namesMap = new HashMap<String, ChatServer.Peer>();
		this.port = port;
	}
	
	private static class Peer{
		private String name; 
		private Socket socket; 
		
		/*method for parsing message */ 
		public void close() {
			
		}
		
		public void send(String message) {
			
		}
	}
	
	private void broadcast(String message) {
		
	}
	
	private void runMainLoop() 
	{
		selector.select();
		Set<SelectionKey> selectedKeys = selector.selectedKeys();

		Iterator keyIterator = (Iterator) selectedKeys.iterator();

		while(keyIterator.hasNext()) 
		{
		    SelectionKey key = (SelectionKey)keyIterator.next();

		    if(key.isAcceptable()) {
		  
                SocketChannel client = serverSocketChannel.accept();
                if(client!=null){
                    System.out.println("Client accepted!");
                    client.configureBlocking(false);
                    SelectionKey selectionKey = client.register(selector, SelectionKey.OP_READ);
                }

		    } else if (key.isConnectable()) {
		        // a connection was established with a remote server.

		    } else if (key.isReadable()) {
		    	ByteBuffer msgbuffer = ByteBuffer.allocate(100);
		    	SocketChannel clientSocket = (SocketChannel) key.channel();
		    	clientSocket.read(msgbuffer);
		    	
		    	PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
		        // a channel is ready for reading

		    } else if (key.isWritable()) {
		        // a channel is ready for writing
		    }

		    keyIterator.remove();
		}

	}
	
	public void start() {
		runMainLoop();
	}
	
}