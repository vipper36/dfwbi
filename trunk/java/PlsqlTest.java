import java.sql.Connection;
import java.sql.DriverManager;

import oracle.jdbc.OracleCallableStatement;
import oracle.jdbc.OracleTypes;
import oracle.sql.ARRAY;
import oracle.sql.ArrayDescriptor;
import oracle.sql.STRUCT;
import oracle.sql.StructDescriptor;


public class PlsqlTest {
	public static void main(java.lang.String[] args) {

		try{
			//Load the driver
			Class.forName ("oracle.jdbc.driver.OracleDriver");

			// Connect to the database 
			Connection conn = DriverManager.getConnection ("jdbc:oracle:thin:@192.168.4.82:1521:apc","fa", "fa");

			// First, declare the Object arrays that will store the data (for TONERECORDTEST OBJECT TYPE)

			// Declare the Object Arrays to hold the STRUCTS (for TTESTTABLE TYPE)
			Object [] p2arrobj;

			// Declare two descriptors, one for the ARRAY TYPE
			// and one for the OBJECT TYPE. 
			StructDescriptor desc1=StructDescriptor.createDescriptor("CONTREC",conn);
			ArrayDescriptor desc2=ArrayDescriptor.createDescriptor("CONTTABLE",conn); 

			// Set up the ARRAY object.
			ARRAY p2arr;

			// Declare the callable statement.
			// This must be of type OracleCallableStatement. 
			OracleCallableStatement ocs = (OracleCallableStatement)conn.prepareCall("{call SqlJavaTestpro.testCallProcedureFromJava(?)}");


			// Register OUT parameter
			ocs.registerOutParameter(1,OracleTypes.ARRAY,"CONTTABLE");

			// Execute the procedure 
			ocs.execute();

			// Associate the returned arrays with the ARRAY objects. 
			p2arr = ocs.getARRAY(1);

			// Get the data back into the data arrays. 
			//p1arrobj = (Object [])p1arr.getArray(); 
			p2arrobj = (Object [])p2arr.getArray(); 

			System.out.println("Number of rows="+p2arrobj.length);
			System.out.println("Printing results...");
			for (int i=0; i<p2arrobj.length; i++){
				Object [] piarrobj = ((STRUCT)p2arrobj[i]).getAttributes();
				System.out.println();
				System.out.print("Row "+i);
				for (int j=0; j<desc1.getLength(); j++){
					System.out.print("|"+piarrobj[j]);
				}
			}
			ocs.close();

		}catch (Exception ex){
			System.out.println("Exception-->"+ex.getMessage());
		}
	}
}
