package nyapc.crawler;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;

public class DbUtil {

	  public static String getSingleQuery(Connection conn , String sql) throws Exception{
		    String rtn = null;
		    PreparedStatement pstmt = null;
		    ResultSet result  = null;
		    try{
		      pstmt = conn.prepareStatement(sql);	
		      result = pstmt.executeQuery();
		      if(result.next()){
		        rtn = result.getString(1);
		      }
		    }
		    catch(java.sql.SQLException e){
		      throw e;
		    }
		    finally {
			  if(pstmt!=null){
				pstmt.close();
			  }		    	
		      if (result!=null) {
		    	  result.close();
		      }
		    }
		    return rtn;
	}
 
	public static String getSingleQuery(Connection conn , String sql, ArrayList<String> paraList) throws Exception{
		    String rtn = null;
		    PreparedStatement pstmt = null;
		    ResultSet result  = null;
		    try{
		      pstmt = conn.prepareStatement(sql);
		      int i=1;
		      for (String str : paraList) {
		    	  pstmt.setString(i++, str);
		      }
		      result = pstmt.executeQuery();
		      if(result.next()){
		        rtn = result.getString(1);
		      }
		    }
		    catch(java.sql.SQLException e){
		      throw e;
		    }
		    finally {
			  if(pstmt!=null){
				pstmt.close();
		   	  }
		      if (result!=null) {
		    	  result.close();
		      }
		    }
		    return rtn;
	}	

    /**
     * 获得PreparedStatement向数据库提交的SQL语句
     * @param sql
     * @param paraList
     * @return
     */
    public static String getPreparedSQL(String sql, ArrayList<String> paraList) {
       //2 如果有参数，则是动态SQL语句
       StringBuffer returnSQL = new StringBuffer();
       String[] subSQL = sql.split("\\?");
       int paramNum = paraList.size();
       
       String[] paraArray = new String[paramNum];
       int j =0;
       for(String str :  paraList){
      	 paraArray[j++] = str;
       }
       for (int i = 0; i < paramNum; i++) {
               returnSQL.append(subSQL[i]).append(" '").append(paraArray[i]).append("' ");
       }

       if (subSQL.length > paraArray.length) {
           returnSQL.append(subSQL[subSQL.length - 1]);
       }
       return returnSQL.toString();
   }
	
}
