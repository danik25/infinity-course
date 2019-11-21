import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.fasterxml.jackson.databind.ObjectMapper;
import tomcatServer.SqlCrudTomcat;


@WebServlet("/PR")
public class PR extends HttpServlet {
	private static final long serialVersionUID = 1L;
	private SqlCrudTomcat sqlCon;   

	String url = "jdbc:mysql://localhost:3306/?useSSL=false";
	String user = "root";
	String pass = "password";
	String databaseName = "managmentDatabase";
	String tableName = "products";
	
    public PR() {
        super();
		sqlCon = new SqlCrudTomcat(url, user, pass, databaseName);
    }

	
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		response.setContentType("text/html");
		String name = request.getParameter("name");
	    
	    PrintWriter out = response.getWriter();
	    out.println("<h1>" + name + " just got registered" + "</h1>");
	}

	
	@SuppressWarnings("unchecked")
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		System.out.println("my name is dani");
		ObjectMapper mapper = new ObjectMapper();
		Map<String,String> myMap = new HashMap<String, String>();
		myMap = mapper.readValue(request.getInputStream(),HashMap.class);
		String query = "INSERT INTO " + tableName + " (`companyName`, `productName`)" +  
				" VALUES(\"" + myMap.get("companyName") + "\" , \"" + myMap.get("productName") + "\");" ; 
		
		sqlCon.create(query);
	}
}
