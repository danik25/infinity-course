import java.sql.*;

public class SqlCrudTomcat
{	
	// JDBC driver name and database URL
    private static String driverName = "com.mysql.jdbc.Driver";  

    //  Database credentials
    private String pass;
    private String databaseName;
	
	Connection conn = null;
	Statement stmt = null;
	
	static {
		try {
			Class.forName(driverName);
		} catch (ClassNotFoundException e) {
			System.err.println("failed lodaing of driver");
		}
	}
	   
	public SqlCrudTomcat(String url, String user, String password, String databaseName)
	{
		this.pass = password;
		this.databaseName = databaseName;

		try {
			conn = DriverManager.getConnection(url, user, pass);
			stmt = conn.createStatement();
			String usageOfDatabase = "USE " + databaseName + ";";
			stmt.executeQuery(usageOfDatabase);
		} catch (SQLException e) {
			System.out.println("failed connection");
			e.printStackTrace();
		}
		
	}
	
	public void close() throws Exception {
         if(conn!=null)
         {
            conn.close();
         }
	}
	
	public Integer create(String query) {		
		Integer ans = 0;
		
		try {
			ans = stmt.executeUpdate(query);
		} catch (SQLException e) {
			System.err.println("failed insertion");
			System.err.println(e);
		}
		
		return ans;
	}

	public String read(String tableName, String columnName, String byKey, String key) {
		String askedMessage = "SELECT " + columnName + " FROM " + tableName + " WHERE " + byKey + " = \"" +  key + "\";";
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

	public void update(String tableName, String column, String byKey, String key, String newVal) {
		String updateMessage = "UPDATE " + tableName + " SET " + column + " = '" + newVal + "', WHERE " + byKey + " = " + key + ";";
		try {
			stmt.executeUpdate(updateMessage);
		} catch (SQLException e) {
			System.err.println("failed updating");
		}
	}

	public void delete(String tableName, String columnName, String condition) {
		String query = "DELETE FROM " + tableName + " WHERE " + columnName + " = " + condition + ";";
		try {
			stmt.executeUpdate(query);
		} catch (SQLException e) {
			System.err.println("failed closing of the database");
		}
	}
}