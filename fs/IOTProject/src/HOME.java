

import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import com.fasterxml.jackson.databind.ObjectMapper;

/**
 * Servlet implementation class LOGIN
 */


@WebServlet("/HOME")
public class HOME extends HttpServlet {
	private static final long serialVersionUID = 1L;
	private SqlCrudTomcat sqlCon;   

	String url = "jdbc:mysql://localhost:3306/?useSSL=false";
	String user = "root";
	String pass = "password";
	String databaseName = "managmentDatabase";
	String tableName = "products";
	
	
	
    public HOME() {
        super();
		sqlCon = new SqlCrudTomcat(url, user, pass, databaseName);
    }

	/**
	 * @see HttpServlet#doGet(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// TODO Auto-generated method stub
		//response.getWriter().append("Served at: ").append(request.getContextPath());
		RequestDispatcher view = request.getRequestDispatcher("/WebContent/html/HomePage.html");
		 
		view.forward(request, response);
	}

	/**
	 * @see HttpServlet#doPost(HttpServletRequest request, HttpServletResponse response)
	 */
	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		String tableName = "companies";
		String columnName = "companyName";
		String byKey = "password";
		
		ObjectMapper mapper = new ObjectMapper();
		Map<String,String> myMap = new HashMap<String, String>();
		myMap = mapper.readValue(request.getInputStream(),HashMap.class);
		
		String answer = sqlCon.read(tableName, columnName, byKey, myMap.get("password"));
		
		if(answer != null && answer.equals(myMap.get("companyName")))
		{
			System.out.println("correct!");
			response.setContentType("text/html");
			response.setCharacterEncoding("UTF-8");
			
			// create HTML response
			PrintWriter writer = response.getWriter();
			writer.append("CompanyPage.html");
		}
		else
		{
			System.out.println("wrong");
		}
		
	}

}
