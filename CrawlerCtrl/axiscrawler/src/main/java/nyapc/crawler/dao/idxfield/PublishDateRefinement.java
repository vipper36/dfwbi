package nyapc.crawler.dao.idxfield;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import com.apc.indextask.idx.Idx;

public class PublishDateRefinement implements FieldRefinement {

	@Override
	public void refine(Idx idx) {
		// TODO Auto-generated method stub
		String value = "";
		String format = idx.getTagValue("dateformat");
		if (null != idx) {
			String pubdate = idx.getTagValue("publishdate");
			if (null != pubdate) {
				value = pubdate.replaceAll("[\r\n]", "");
			}
		}
		// System.out.println(value);
		String date = "";
		try {
			if (null != format && !"".equals(format)) {
				//当含有DATEFORMAT标签的时候：
				String pat = ".*?(" + 
					format.replaceAll("(M+|E+)", "[0-9a-zA-Z]+").replaceAll("(d|D|y|w|W|F)", "[0-9]")
						+ ").*?";
				Pattern p = Pattern.compile(pat);
				Matcher matcher = p.matcher(value);
				String dateStr = null;
				if (matcher.matches()) {
					dateStr = matcher.group(1);
				}else{
					//在URL中按照指定格式搜索日期：
					String ref = java.net.URLDecoder.decode(idx.getReference(), "UTF-8");
					matcher = p.matcher(ref);
					if(matcher.matches()){
						dateStr = matcher.group(1);
					}
				}
				
				if(null != dateStr && !"".equals(dateStr)){
					SimpleDateFormat df = new SimpleDateFormat(format.replaceAll("\\+", ""));
					Date d = null;
					try {
						d = df.parse(dateStr);
					} catch (ParseException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					date = standardDF2.format(d);
				}
			} else {
				//当没有DATEFORMAT标签的时候：
				Matcher m = hasChineseYear.matcher(value);
				if (m.matches()) {
					date = processPatternChineseYear(m);
				} else {
					m = datePattern.matcher(value);
					if (m.matches()) {
						date = processPatternNormalFormat(m);
					}
				}

				//在URL中搜索日期：
				if ("".equals(date)) {
					String ref = java.net.URLDecoder.decode(idx.getReference(),
							"UTF-8");
					m = datePattern.matcher(ref);
					if (m.matches()) {
						date = processPatternNormalFormat(m);
					}
				}
			}
		} catch (Exception e) {
		}
		// System.out.println("-----------------1");
		if (!"".equals(date)) {
			date = toStandardDateFormat(date);
			if (null != date && !"".equals(date)) {
				Matcher m = standardFormatPattern.matcher(date);
				if (m.matches()) {
					String g1 = m.group(1);
					String g2 = m.group(2);
					String g3 = m.group(3);
					String statdate = g1 + "-" + g2 + "-" + g3;
					String statmonth = g1 + "-" + g2;
					String statyear = g1;
					idx.removeField("statdate");
					idx.addField("statdate", statdate);
					idx.removeField("statmonth");
					idx.addField("statmonth", statmonth);
					idx.removeField("statyear");
					idx.addField("statyear", statyear);
				}
			}
		}
		// System.out.println("-----------------2");
		idx.removeField("publishdate");
		idx.addField("publishdate", date);
		return;
	}

	public String toStandardDateFormat(String date) {
		String ret = "";

		SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd");
		Date d = null;
		try {
			d = df.parse(date);
		} catch (ParseException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		if (null != d) {
			// System.out.println(d.getTime());
			if (d.getTime() < 0) {
				d.setYear(d.getYear() + 1900);
			}
			ret = standardDF2.format(d);
		}

		return ret;
	}

	public String processPatternChineseYear(Matcher m) {
		String g1 = m.group(1);
		String g2 = m.group(2);
		String g3 = m.group(3);
		String g4 = m.group(4);
		String g5 = m.group(5);
		String g6 = m.group(6);

		// System.out.println(g1 + "-" + g3 + "-" + g5);

		String ret = "";
		if ("年".equals(g2) && "月".equals(g4)) {
			ret = g1 + "-" + g3 + "-" + g5;
		} else if ("年".equals(g6) && "月".equals(g4)) {
			ret = g5 + "-" + g3 + "-" + g1;
		}

		return ret;
	}

	public String processPatternNormalFormat(Matcher m) {
		String g1 = m.group(1);
		String g2 = m.group(2);
		String g3 = m.group(3);

		String ret = "";
		if (g1.length() == 4 && g2.length() <= 2 && g3.length() <= 2) {
			ret = g1 + "-" + g2 + "-" + g3;
		} else if (g3.length() == 4 && g2.length() <= 2 && g1.length() <= 2) {
			ret = g3 + "-" + g2 + "-" + g1;
		}

		return ret;
	}

	private static SimpleDateFormat standardDF2 = new SimpleDateFormat(
			"yyyy-MM-dd");

	private static Pattern hasChineseYear = Pattern
			.compile(".*?([0-9]+) *([年月日]) *([0-9]+) *([年月日]) *([0-9]+) *([年月日]).*");

	private static Pattern datePattern = Pattern
			.compile("^.*?(\\d{1,4}) *[-/\\.\\\\] *(\\d{1,4}) *[-/\\.\\\\] *(\\d{1,4}).*$");

	private static Pattern standardFormatPattern = Pattern
			.compile("^(\\d{4})-(\\d{2})-(\\d{2}).*$");

	public static void main(String args[]) {
		String str = "#DREREFERENCE http%3A%2F%2F220%2E189%2E220%2E29%2Frp%2Ffs%2Fcp%2F17%2F41%2F2010-05/01%2F4%2Ficontent%5F0%2Ehtm\n"
				+ "#DRETITLE 山西一煤矿发生事故\n"
				+ "#DREDBNAME NEWS\n"
		//		+ "#DREFIELD PUBLISHDATE=\"山西省灵石煤矿有限公司 Wed, Jul 4, 01\"\n"
				+ "#DREFIELD PUBLISHDATE=\"05-12\"\n"
		//		+ "#DREFIELD DATEFORMAT=\"EEE, MMMMMMM d, yy\"\n"
				+ "#DREFIELD DATEFORMAT=\"MM-dd\"\n"
		//		+ "#DREFIELD PUBLISHDATE=\"[08:19 June 11 2010]\"\n"
		//		+ "#DREFIELD DATEFORMAT=\"M dd yyyy\"\n"
				+ "#DREFIELD CHANNELNAME=\"第03版：周刊国内\"\n"
				+ "#DREFIELD JOBNAME=\"61_167_35_147_27013\"\n"
				+ "#DRECONTENT\n"
				+ "　　据新华社太原电（记者 高风）山西省灵石煤矿有限公司15日16时30分许发生透水事故，当班6人，2人安全出井，目前尚有4人被困。　　记者从灵石县政府了解到，事故发生后，山西省委、省政府领导作出批示，要求立即组织专业人员全力搜救被困人员，防止发生次生事故。山西省煤炭厅、安监局、煤监局和晋中市领导已率有关部门赶赴现场指挥抢险。目前已组织两支矿山救护队60余名专业救护人员，调集多台抽水机具在井下全力组织抽水，抢险救援正在紧张进行。　　据介绍，发生事故的煤矿为山西省煤炭厅2009年8月20日批准的年产90万吨机械化采煤升级改造矿井。2009年12月经晋中市和灵石县煤矿复工复产验收工作领导组办公室批准复工建设。目前事故原因仍在调查之中。\n"
				+ "\n" + "#DREENDDOC\n";

		FieldRefinement refine = new PublishDateRefinement();

		Idx idx = new Idx(str);
		refine.refine(idx);

		System.out.println(idx.toString());
	}

}
