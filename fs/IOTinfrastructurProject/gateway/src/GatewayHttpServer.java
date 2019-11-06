import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.UnsupportedEncodingException;
import java.net.InetSocketAddress;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.sun.net.httpserver.HttpServer;
import com.sun.net.httpserver.HttpContext;
import com.sun.net.httpserver.HttpExchange;

@SuppressWarnings("restriction")
public class GatewayHttpServer {
	static ExecutorService pool = Executors.newFixedThreadPool(10);
	
	public static void main(String[] args) throws IOException {
	      HttpServer server = HttpServer.create(new InetSocketAddress(8500), 0);
	      HttpContext context = server.createContext("/request");
	      context.setHandler(GatewayHttpServer::handleRequest);
	      server.start();
	  }
	
	@SuppressWarnings("unchecked")
	private static void handleRequest(HttpExchange exchange) throws IOException {
	      String response = "Hi hi there!";
	      System.out.println(response);
	      exchange.sendResponseHeaders(200, response.getBytes().length);
	      OutputStream os = exchange.getResponseBody();
	     
	     
	      ObjectMapper mapper = new ObjectMapper();
		  Map<String,String> pairsMap = new HashMap<String, String>();
		  exchange.getRequestBody();
		  
		  pairsMap = mapper.readValue(getBody(exchange) ,HashMap.class);
		 
	      class task implements Runnable
	      {
	    	  Map<String,String> pairsMap;
	    	  task(Map<String,String> pairsMap)
	    	  {
	    		  this.pairsMap = pairsMap;
	    	  }
	    	  @Override
	    	  public void run() {
					System.out.println("getting: " + commandFactory.getCommand(pairsMap.get("type")));
				}
	      } 
	      pool.execute(new task(pairsMap)); 
	      
	      os.write(response.getBytes());
	      os.close();
	  }
	
	static String getBody(HttpExchange exchange) throws IOException
	{
		InputStreamReader isr =  new InputStreamReader(exchange.getRequestBody(),"utf-8");
		BufferedReader br = new BufferedReader(isr);
		int b;
		StringBuilder buf = new StringBuilder(512);
		while ((b = br.read()) != -1) {
		    buf.append((char) b);
		}

		br.close();
		isr.close();
		
		return buf.toString();
	}
	
	void submit()
	{
		
	}
	
	enum command
	{
		CR{
			@Override
			String getURL() {
				return "/CR";
			}
			
		},
		PR{
			@Override
			String getURL() {
				return "/PR";
			}
		};
		
		abstract String getURL();
	}
	
	static class commandFactory
	{
		static command getCommand(String commandName)
		{
			switch(commandName)
			{
				case "CR":
					return command.CR;
					
				case "PR":
					return command.PR;	
					
				default:
					return null;
			}
		}
	}
}