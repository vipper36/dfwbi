package nyapc.crawler.dao.idxfield;

import java.util.regex.Matcher;
import java.util.regex.Pattern;
import com.apc.indextask.idx.Idx;

public class SourceRefinement implements FieldRefinement {

	@Override
	public void refine(Idx idx) {
		// TODO Auto-generated method stub
		String attr = idx.getTagValue("attr");
		String source = idx.getTagValue("sourcename");
		if(null == source || "".equals(source)){
			source = idx.getTagValue("source");
		}
		idx.removeField("source");

		if (null != attr && !"".equals(attr)) {
			String ret = findSource(attr.replaceAll("[\r\n]", ""));
			if (!"".equals(ret)) {
				idx.removeField("sourcename");
				idx.addField("sourcename", ret);
				return;
			}
		} else if (null != source && !"".equals(source)) {
			String ret = findSource(source.replaceAll("[\r\n]", ""));
			if (!"".equals(ret)) {
				idx.removeField("sourcename");
				idx.addField("sourcename", ret);
				return;
			}
		}

		String content = idx.getTagValue("DRECONTENT");
		if (content.length() > 100) {
			attr = content.substring(0, 49) + "\n"
					+ content.substring(content.length() - 50);
			String ret = findSourceInContent(attr);
			if (!"".equals(ret)) {
				idx.removeField("sourcename");
				idx.addField("sourcename", ret);
				return;
			}
		}

		idx.removeField("sourcename");
		idx.addField("sourcename", "");
	}

	private String findSource(String attr) {
		String ret = "";

		Matcher m = hasSource.matcher(attr);
		if (m.matches()) {
			ret = m.group(2);
		}

		return ret;
	}

	private String findSourceInContent(String attr) {
		String ret = "";

		if (attr.indexOf("本报讯") >= 0) {
			return ret;
		}

		attr = attr.replaceAll("[（）]", " ");
		String[] list = attr.split("[？｜！，。\n　 ]+");
		if (null != list) {
			for (String str : list) {
				ret = findMatchedSourcePattern(str);
				if (!"".equals(ret)) {
					break;
				}
			}
		}

		return ret;
	}

	private String findMatchedSourcePattern(String str) {
		String ret = "";

		Matcher m = patSource1.matcher(str);
		if (m.matches()) {
			// System.out.println(m.group(1) +" "+ m.group(2) +" "+ m.group(3));
			if (!"通报".equals(m.group(3)) && !"预报".equals(m.group(3))) {
				ret = m.group(2) + m.group(3);
				return ret;
			} else {
				return ret;
			}
		}

		m = patSource2.matcher(str);
		if (m.matches()) {
			String group1 = m.group(1);
			String group2 = m.group(2);
			if (!"电网".equals(group2) && !"互联网".equals(group2)
					&& group1.indexOf("据") < 0) {
				ret = m.group(1) + m.group(2);
			}
			return ret;
		}

		m = patSource3.matcher(str);
		if (m.matches()) {
			ret = m.group(2);
			return ret;
		}

		return ret;
	}

	private static Pattern hasSource = Pattern
			.compile(".*(来源|转载)[:： 　]+([一-龥]{2,10})(作者|记者| |　|$).*");

	private static Pattern patSource1 = Pattern
			.compile("^(据)([一-龥]{2,10}?)(预报|通报|社|网|报)[^道告会民区]*");
	// .compile("^(另据|据)([一-龥]{2,10}?)(社|网|报)[^道告会民].*");
	private static Pattern patSource2 = Pattern
			.compile("^([一-龥]{2,10}?)(互联网|电网|社|网|报)[^道告会民区]*(电)[^话视信息]?$");
	private static Pattern patSource3 = Pattern
			.compile("^.{0,3}(来源|转载)[:： 　]+([一-龥]{2,10})$");

	public static void main(String args[]) {
		String str = "#DREREFERENCE http%3A%2F%2F61%2E167%2E35%2E147%2Fxwb%2Fhtml%2F2010%2D01%2F17%2Fcontent%5F4154713%2Ehtm\n"
				+ "#DRETITLE 山西一煤矿发生事故\n"
				+ "#DREDBNAME NEWS\n"
				+ "#DREFIELD PUBLISHDATE=\"新商报首页 > \n 21日\n 星期四 杨一民\"\n"
				+ "#DREFIELD AUTHOR=\"新商报首页 > \n 21日\n 星期四 杨一民\"\n"
				+ "#DREFIELD SOURCENAME=\"\"\n"
				+ "#DREFIELD CHANNELNAME=\"第03版：周刊国内\"\n"
				+ "#DREFIELD JOBNAME=\"61_167_35_147_27013\"\n"
				+ "#DRECONTENT\n"
				+ "　　 据当地媒体报告，   关注的体育人物姚明位列榜首新华社 （张美容） 1月21日，在泰宁县下渠乡乌凤鸡养殖基地，工人们正加紧建设厂房，争取月底完工。建成后的养殖基地有6座鸡舍，1座预藏室，共1700平方米，预计年可产乌凤鸡10万只以上。  金湖乌凤鸡是泰宁特有的家禽品种资源，肉质细嫩、风味鲜美、营养丰富，是福建省优良地方品种、国家级畜禽遗传资源。今年泰宁将乌凤鸡养殖作为与旅游相配套的农业产业化项目来抓，计划在全县推广养殖100万只。泰宁出台优惠政策鼓励大户养殖，农户新建鸡舍150平方米以上，每平方米补助20元；新建鸡舍1500平方米以上的乌凤鸡专业村，每个村以奖代补1万元。目前，泰宁已建立金湖乌凤鸡原种场和保护核心群，存栏种鸡达8000套，落实养殖户68户，养殖场面积16400平方米，养殖专业村2个。三农报道泰宁\n"
				+ "\n" + "#DREENDDOC\n";

		SourceRefinement refine = new SourceRefinement();

		Idx idx = new Idx(str);
		refine.refine(idx);

		System.out.println(idx.toString());

		String test[] = { "　　新华社北京1月25日专电",
				"    2009-11-04    □本报记者 袁军宝     来源：经济参考报", "市场报讯",
				"　　据当地媒体报道，", " 　　据媒体报道，", "据中广网消息  累计捐赠十亿元、", "以上均据新华社电",
				"　　数据来源：广州市国土房管局　　", "河南日报讯 （记者 刘亚辉）", "据中新社１月２６日电 ２５日，",
				"据美联社报道，", "据《扬子晚报》报道", "不少在校大学生给本报打电话", "世博专线将全线触网完成永久受电",
				"　　据中国之声报道，", "中小学须装上网过滤软件确保校园网络处在可监控状态  本报讯  据《新京报》报道",
				"唐某与本屯村民在八腊乡五福村花洞屯一带拉农网电线", "中国女将首进澳网八强郑洁书写新辉煌报讯 ", "据今晨媒体报道",
				"南京交通违法照片可网上查询  新华社南京１月２４日电", "内蒙古电网独立于国家电网", "另据新华社电",
				"据国家海洋局北海预报中心利用卫星遥感等手段监测显示", "南涧县经济社会发展质量全面提升",
				"好姐妹隔网相对金花“反目”不成仇  新华网墨尔本１月２５日电 ", "希望引来更多人去回报社会  据中新社电",
				"向纳税人发放，并公开投诉举报电话，", "并通报了这一喜讯", "建三江分局青龙山社区客运站居民楼突然停电",
				"汽车国家电网一线城市布局电动汽车充电站", "省政协十届三次会议隆重开幕陆浩徐守盛出席  陈学亨作报告  本报讯",
				"我国网管符合国际通行做法，   关注的体育人物姚明位列榜首新华社",
				"雄嘎社区冻裂的水管修好了  商报讯（记者 李睿）昨日", "但邯郸各家旅行社已经是门庭若市",
				"早报网网友“yypphh”：", "无论是LED液晶电视还是互联网电视", "陈学亨作报告" };
		for (String attr : test) {
			String src = refine.findSourceInContent(attr);
			System.out.println(attr + "\n" + src + "\n\n");
		}
	}
}
