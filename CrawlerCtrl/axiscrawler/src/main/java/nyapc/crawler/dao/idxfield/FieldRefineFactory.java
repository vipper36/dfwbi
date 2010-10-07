package nyapc.crawler.dao.idxfield;

import com.apc.indextask.idx.Idx;

public class FieldRefineFactory {

	static FieldRefinement	fr1 = new PublishDateRefinement();
	static FieldRefinement	fr2 = new SourceRefinement();
	static FieldRefinement	fr3 = new AuthorRefinement();
	
	public static void idxFieldRefine(Idx idx){
		fr1.refine(idx);
		fr2.refine(idx);
		fr3.refine(idx);
		idx.removeField("attr");
		return;
	}
	
	
}
