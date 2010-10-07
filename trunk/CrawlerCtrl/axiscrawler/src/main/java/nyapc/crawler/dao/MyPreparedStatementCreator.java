package nyapc.crawler.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

import org.springframework.jdbc.core.PreparedStatementCreator;

public class MyPreparedStatementCreator implements PreparedStatementCreator {
    private String chl_stat;
    private String chl_id;
    
	@Override
	public PreparedStatement createPreparedStatement(Connection conn)
			throws SQLException {
		// TODO Auto-generated method stub
			PreparedStatement pstmt = conn.prepareStatement("update chl_list set chl_stat=? where chl_id=?");  
			pstmt.setString(1, chl_stat);  
			pstmt.setString(2, chl_id);  
			return pstmt;  
	}

	public String getChl_stat() {
		return chl_stat;
	}

	public void setChl_stat(String chlStat) {
		chl_stat = chlStat;
	}

	public String getChl_id() {
		return chl_id;
	}

	public void setChl_id(String chlId) {
		chl_id = chlId;
	}

}
