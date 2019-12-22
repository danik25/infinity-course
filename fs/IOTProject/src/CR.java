import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.fasterxml.jackson.core.JsonParseException;
import com.fasterxml.jackson.databind.JsonMappingException;
/* jackson, json parsing API */
import com.fasterxml.jackson.databind.ObjectMapper;


/* lior */


/**
 * Servlet implementation class CR
 */
@WebServlet("/CR")
public class CR extends HttpServlet {
	private SqlCrudTomcat sqlCon;
	private static final long serialVersionUID = 1L;
	
	String url = "jdbc:mysql://localhost:3306/?useSSL=false";
	String user = "root";
	String pass = "password";
	String databaseName = "managmentDatabase";
       
    public CR() {
    	super();
    	sqlCon = new SqlCrudTomcat(url, user, pass, databaseName);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
    	/*response.setContentType("text/html");
		String name = request.getParameter("name");
	   
	    PrintWriter out = response.getWriter();
	    out.println("<h1>" + name + " just got registered" + "</h1>");*/
	    System.out.println("here");
	    //RequestDispatcher rd = request.getRequestDispatcher("registrationPage.html");
	    //rd.forward(request, response);
	}
	
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		updateCompanyDatabase(request); 
		/* requestToGatewayServer(); */
		 
	}
	
	@SuppressWarnings("unchecked")
	void updateCompanyDatabase(HttpServletRequest request) throws JsonParseException, JsonMappingException, IOException
	{
		String tableName = "companies";
		
		ObjectMapper mapper = new ObjectMapper();
		Map<String,String> myMap = new HashMap<String, String>();
		myMap = mapper.readValue(request.getInputStream(),HashMap.class);
		
		String query = "INSERT INTO " + tableName + " (`companyName`)" +  " VALUES(\"" + myMap.get("companyName") + "\");" ; 
		System.out.println(query);
		sqlCon.create(query);
	}
	
	void requestToGatewayServer() throws IOException
	{
		System.out.println("here");
		URL url = new URL("http://localhost:8500/src/gatewayServer");
		HttpURLConnection connection = (HttpURLConnection) url.openConnection();
	}
}
