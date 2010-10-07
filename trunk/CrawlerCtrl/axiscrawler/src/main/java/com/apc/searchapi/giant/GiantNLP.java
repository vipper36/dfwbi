package com.apc.searchapi.giant;

import cnnlp.lexical.segment.SegmentFactory;
import cnnlp.lexical.segment.WordAtoms;
import cnnlp.resource.domain.DomainFactory;

public class GiantNLP {

	static GiantNLP nlp = new GiantNLP();

	public static GiantNLP getNlpTool() {
		return nlp;
	}

	GiantNLP() {
		// ZHIDA_HOME=WebRoot/WEB-INF/config/zhida/
		
	}

	public String getSynonym(String word) {
		String ret = word;
		String[] synonyms = df.getAllSynonym(word);
		if (null != synonyms) {
			ret = synonyms[synonyms.length - 1];
			ret = doHalfShape(ret);
		}
		return ret;
	}

	private final boolean isWordStartWithAlphabeticalOrDigital(char c1) {
		boolean flag = false;
		if (c1 >= 'A' && c1 <= 'Z' || c1 >= 'a' && c1 <= 'z' || c1 >= '0'
				&& c1 <= '9' || c1 >= '\uFF21' && c1 <= '\uFF41'
				|| c1 >= '\uFF3A' && c1 <= '\uFF5A' || c1 >= '\uFF10'
				&& c1 <= '\uFF19') {
			flag = true;
		}
		return flag;
	}

	private final String doHalfShape(String s1) {
		String s2 = null;
		char ac[] = s1.toCharArray();
		for (int i1 = 0; i1 < ac.length; i1++) {
			if (isWordStartWithAlphabeticalOrDigital(ac[i1])) {
				if (ac[i1] >= '\uFF21' && ac[i1] <= '\uFF41'
						|| ac[i1] >= '\uFF3A' && ac[i1] <= '\uFF5A'
						|| ac[i1] >= '\uFF10' && ac[i1] <= '\uFF19') {
					ac[i1] = (char) (ac[i1] - 65248);
				}
			}
		}

		s2 = new String(ac);
		return s2;
	}

	/**
	 * 分词
	 * 
	 * @param text
	 * @return
	 */
	public synchronized WordAtoms segment(String text) {
		return segment(text, true);
	}

	/**
	 * 分词
	 * 
	 * @param text
	 * @return
	 */
	public synchronized WordAtoms segment(String text, boolean useDomainDict) {
		sf.setUseDomainDictionary(useDomainDict);
		return sf.segment2(text);
	}

	public String getZhidaHome() {
		return ZhidaHome;
	}
	
	public void setZhidaHome(String zhida) {
		ZhidaHome = zhida;
		cnnlp.core.Configure.setCnnlpPath(ZhidaHome);
		if (sf == null) {
			sf = SegmentFactory.getInstance();
		}
		if (df == null) {
			df = DomainFactory.getInstance();
		}
	}

	SegmentFactory sf = null;
	DomainFactory df = null;
	String ZhidaHome = "";
}
