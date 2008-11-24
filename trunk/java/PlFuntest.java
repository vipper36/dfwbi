import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

import oracle.jdbc.OracleCallableStatement;
import oracle.jdbc.OracleTypes;
import oracle.sql.ARRAY;
import oracle.sql.ArrayDescriptor;
import oracle.sql.STRUCT;
import oracle.sql.StructDescriptor;

public class PlFuntest {
	public static void main(java.lang.String[] args) {

		try{
			//Load the driver
			Class.forName ("oracle.jdbc.driver.OracleDriver");

			// Connect to the database 
			Connection conn = DriverManager.getConnection ("jdbc:oracle:thin:@192.168.4.82:1521:apc","fa", "fa");

			// Declare the callable statement.
			// This must be of type OracleCallableStatement. 
			OracleCallableStatement ocs = (OracleCallableStatement)conn.prepareCall("{?=call SqlJavaTestpro.testCallFunFromJava()}");

			ocs.registerOutParameter(1, OracleTypes.CURSOR);
			ocs.execute();
			ResultSet rs = (ResultSet) ocs.getObject(1);

			//Iterate the ResultSet to fetch the accounts.

			while (rs.next())
			{

				//Put information about each account into the list.

				System.out.println(rs.getString("CNTY_CODE") + " - " + rs.getString("NUM_CODE")+" - " + rs.getString("TWO_CODE")+" - "  + rs.getString("SHORT_NAME")+" - "  + rs.getString("FULL_NAME"));
			}

			//And then we tidy up by closing the ResultSet and the Statement.

			rs.close();
			ocs.close();
		}catch (Exception ex){
			System.out.println("Exception-->"+ex.getMessage());
		}
	}
}
