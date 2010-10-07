package nyapc.crawler.dao.idxfield;

import java.util.*;
import cnnlp.lexical.segment.WordAtoms;
import com.apc.indextask.idx.Idx;
import com.apc.searchapi.giant.GiantNLP;

public class AuthorRefinement implements FieldRefinement {

	@Override
	public void refine(Idx idx) {
		// TODO Auto-generated method stub
		String attr = idx.getTagValue("attr");
		String author = idx.getTagValue("author");
		String title = idx.getTitle();

		if (null != attr && !"".equals(attr) && !title.equals(attr)) {
			String ret = findAuthor(attr.replaceAll("[\r\n]", ""), title);
			if (!"".equals(ret)) {
				idx.removeField("author");
				idx.addField("author", ret);
				return;
			}
		} else if (null != author && !"".equals(author)
				&& !title.equals(author)) {
			String ret = findAuthor(author.replaceAll("[\r\n]", ""), title);
			if (!"".equals(ret)) {
				idx.removeField("author");
				idx.addField("author", ret);
				return;
			}
		}

		String content = idx.getTagValue("DRECONTENT");
		if (content.length() > 100) {
			content = content.substring(0, 99);
		}
		String ret = findAuthorInContent(content);
		idx.removeField("author");
		idx.addField("author", ret);

	}

	private String findAuthor(String attr, String title) {
		String ret = "";

		// boolean hasWordAuthor = false;
		WordAtoms words = GiantNLP.getNlpTool().segment(attr);
		Map<String, Integer> names = new HashMap<String, Integer>();
		for (int i = 0; i < words.length(); i++) {
			switch (words.getTags(i)) {
			// 自定义分词其tag总是1
			case 1:
				String word = words.getWords(i);
				// if (word.matches("^(记者|作者)")) {
				// hasWordAuthor = true;
				// }
				if (10001 == words.getMarks(i)) {
					names.put(word, i);
				}
				break;
			case cnnlp.lexical.dict.POSUtil.POS_NR:
				names.put(words.getWords(i), i);
				break;
			default:
				break;
			}
		}

		Set<String> nameSet = names.keySet();
		int count = nameSet.size();
		if (count > 0) {
			int average = 0;
			for (String key : nameSet) {
				average += names.get(key);
			}

			average /= count;
			for (String key : nameSet) {
				int pos = names.get(key);
				if (pos - average > 6 || pos - average < -6) {
					return ret;
				}
			}

			for (String key : nameSet) {
				if (title.indexOf(key) < 0) {
					ret += key + " ";
				} else {
					return "";
				}
			}
		}
		return ret.trim();
	}

	private String findAuthorInContent(String content) {
		String ret = "";

		boolean hasWordAuthor = false;
		int positionWordAuthor = 0;
		WordAtoms words = GiantNLP.getNlpTool().segment(content);
		Map<String, Integer> names = new HashMap<String, Integer>();
		for (int i = 0; i < words.length(); i++) {
			switch (words.getTags(i)) {
			// 自定义分词其tag总是1
			case 1:
				String word = words.getWords(i);
				if (word.matches("^(记者|作者)") && !hasWordAuthor) {
					hasWordAuthor = true;
					positionWordAuthor = i;
				}
				if (10001 == words.getMarks(i)) {
					names.put(word, i);
				}
				break;
			case cnnlp.lexical.dict.POSUtil.POS_NR:
				names.put(words.getWords(i), i);
				break;
			default:
				break;
			}
		}

		Set<String> nameSet = names.keySet();
		int count = nameSet.size();
		if (count > 0 && hasWordAuthor) {
			for (String key : nameSet) {
				if (key.length() > 1) {
					int pos = names.get(key);
					if (pos - positionWordAuthor < 3
							&& pos - positionWordAuthor >= 0) {
						ret += key + " ";
					}
				}
			}
		}
		return ret.trim();
	}

	public static void main(String args[]) {
		// CrawlerCtrl ctrl=new CrawlerCtrl();
		GiantNLP.getNlpTool().setZhidaHome("zhida");
		String str = "#DREREFERENCE http%3A%2F%2F61%2E167%2E35%2E147%2Fxwb%2Fhtml%2F2010%2D01%2F17%2Fcontent%5F4154713%2Ehtm\n"
				+ "#DRETITLE 山西一煤矿发生事故\n"
				+ "#DREDBNAME NEWS\n"
				+ "#DREFIELD PUBLISHDATE=\"新商报首页 > \n 21日\n 星期四\"\n"
				+ "#DREFIELD AUTHOR=\"新商报首页 > \n 21日\n 星期四 \"\n"
				+ "#DREFIELD CHANNELNAME=\"第03版：周刊国内\"\n"
				+ "#DREFIELD JOBNAME=\"61_167_35_147_27013\"\n"
				+ "#DRECONTENT\n"
				+ "　　客场3比0战胜瓦拉多利德 巴萨斩获半程冠军   本报讯 （记者皮勇）北京时间昨天，西甲联赛第19轮先赛3场。巴塞罗那队客场3比0大胜瓦拉多利德队，在多赛一场的情况下领先皇马8分，获得半程冠军。另外，塞维利亚队主场以1比0战胜阿尔梅里亚队，拉科鲁尼亚队主场以3比1战胜毕尔巴鄂竞技队。  巴萨客场挑战瓦拉多利德队。主队采取紧逼战术，巴萨一度没有思索的空间，但球星们的个人能力让巴萨2分钟内解决了战斗。第20分钟，阿尔维斯右路传中，哈维8码处侧身凌空抽射破门。2分钟后，梅西头球摆渡，阿尔维斯右路似传似射，皮球吊入球门远角，2比0。第57分钟，伊布拉辛莫维奇禁区内停球后冷静横传，梅西10码处左脚推射破门，这是他本赛季第15粒联赛进球。最终，巴萨以3比0取得4连胜。  目前，巴萨积49分，仅比上赛季同期少一个积分，“红蓝军团”依旧是本赛季西甲联赛冠军的最大热门。另外，巴萨10个联赛丢球也比上赛季同期少了3球。不过，49个联赛进球比上赛季同期少了10球，这很大程度上得归因于亨利的状态低迷和伊布尚未真正找到球队配合的节奏，堪称完美的“梦之队”依然有可以提高的空间。\n"
				+ "\n" + "#DREENDDOC\n";

		FieldRefinement refine = new AuthorRefinement();

		Idx idx = new Idx(str);
		refine.refine(idx);

		System.out.println(idx.toString());
	}
}
