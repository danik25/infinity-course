package il.co.ilrd.logmonitorSQL;
import java.sql.*;
import il.co.ilrd.logmonitor.CRUD;


class Crudsql implements CRUD<String, Integer>
{	
	// JDBC driver name and database URL
    private static String driverName = "com.mysql.jdbc.Driver";  

    //  Database credentials
    private String pass;
    private String databaseName;
    private String tableName;
	
	Connection conn = null;
	Statement stmt = null;
	
	static {
		try {
			Class.forName(driverName);
		} catch (ClassNotFoundException e) {
			System.err.println("failed lodaing of driver");
		}
	}
	
	   
	Crudsql(String url, String user, String password, String databaseName, String tableName)
	{
		this.pass = password;
		this.databaseName = databaseName;
		this.tableName = tableName;
		
		try {
			conn = DriverManager.getConnection(url, user, pass);
			stmt = conn.createStatement();
		} catch (SQLException e) {
			System.out.println("failed creating a connection");
			System.out.println(e);
		}
		
		createDatabase();
		createTable();
	}
	
	@Override
	public void close() throws Exception {
         if(conn!=null)
         {
            conn.close();
         }
	}

	@Override
	public Integer create(String message) {		
		System.out.println("inserting");
		Integer ans = 0;
		message = message.replace('\"', '\'');
		String insertion = "INSERT INTO " + tableName + " (`message`)" +  " VALUES(\"" + message + "\");" ; 
		try {
			ans = stmt.executeUpdate(insertion);
		} catch (SQLException e) {
			System.err.println("failed insertion");
			System.err.println(e);
		}
		
		return ans;
	}

	@Override
	public String read(Integer key) {
		String askedMessage = "SELECT message FROM " + tableName + " WHERE id = " + key + ";";
		try {
			ResultSet answer = stmt.executeQuery(askedMessage);
			if (answer.next()) 
			{
				return answer.getString(1);
			}

		} catch (SQLException e) {
			System.out.println("failed reading");
		}
		return null;
	}

	@Override
	public void update(Integer key, String newMessage) {
		String updateMessage = "UPDATE " + tableName + " SET message = '" + newMessage + "', WHERE id = " + key + ";";
		try {
			stmt.executeUpdate(updateMessage);
		} catch (SQLException e) {
			System.err.println("failed updating");
		}
	}

	@Override
	public void delete(Integer key) {
		String sql = "DROP DATABASE " + databaseName + ";";
		try {
			stmt.executeUpdate(sql);
		} catch (SQLException e) {
			System.err.println("failed closing of the database");
		}
	}
	
/**********************************************************/	
	private void createDatabase()
	{
		try {
			// creating the database 
			String sql = "CREATE DATABASE " + databaseName;
		    stmt.executeUpdate(sql);
		    sql = "USE " + databaseName;
		    stmt.executeUpdate(sql);

		} catch (SQLException e) {
			System.err.println("failed creation of a database");
			e.printStackTrace();
		} 
	}
	
	private void createTable()
	{
		try {
			// creating the table
			stmt = conn.createStatement();
			String sql = "CREATE TABLE " + tableName +
					" (id int NOT NULL AUTO_INCREMENT, message TEXT, PRIMARY KEY (id));";
		    stmt.executeUpdate(sql);

		} catch (SQLException e) {
			System.err.println("failed creation of the table");
			e.printStackTrace();
		} 
	}
}