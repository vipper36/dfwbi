package nyapc.crawler.dao;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import com.apc.indextask.idx.Idx;

import nyapc.crawler.Escape;
import nyapc.crawler.dao.idxfield.FieldRefineFactory;
import nyapc.crawler.dao.idxfield.FieldRefinement;

public class IdxAtt {

	public boolean addAtts(String name, String value) {
		AttValue att = new AttValue();
		att.name = name;
		att.value = nyapc.crawler.Util.strNotNull(value);

		return atts.add(att);
	}

	public String getContent() {
		return Content;
	}

	public void setContent(String content) {
		Content = content;
	}

	@Override
	public String toString() {
		StringBuffer sb = new StringBuffer();
		for (int i = 0; i < atts.size(); i++) {
			AttValue att = atts.get(i);
			if (att.name.length() > 0) {
				if (att.name.equals("#DREREFERENCE ")) {
					att.value = Escape.escape(att.value, "UTF-8");
				}
				if (att.name.equals("#DRETITLE ")) {
					if(att.value==null||att.value.length()==0)
						att.value= nyapc.crawler.Util.strNotNull(dbTitle);
				}
				if (att.value.length() > 0)
				{
					sb.append(att.name);
					if (att.name.indexOf("#DREFIELD") >= 0)
						sb.append("\"");
					
					
					sb.append(att.value);
					if (att.name.indexOf("#DREFIELD") >= 0)
						sb.append("\"");
					sb.append("\n");
				}
			}
		}
		
		String dredate =  String.valueOf(new java.util.Date().getTime() / 1000);
		sb.append("#DREDATE ").append(dredate).append("\n");
		
		sb.append("#DRECONTENT\n");
		sb.append(Content);
		sb.append("\n");
		sb.append("#DREENDDOC\n");
		sb.append("\n\n");
		// sb.append("#DREENDDATA\n");
		// sb.append("\n\n");

		Idx idx = new Idx(sb.toString());

		FieldRefineFactory.idxFieldRefine(idx);
		
		return idx.toString();
	}

	List<AttValue> atts = new ArrayList<AttValue>();
	String Content;
	public String getDbTitle() {
		return dbTitle;
	}

	public void setDbTitle(String dbTitle) {
		this.dbTitle = dbTitle;
	}

	String dbTitle;
}
