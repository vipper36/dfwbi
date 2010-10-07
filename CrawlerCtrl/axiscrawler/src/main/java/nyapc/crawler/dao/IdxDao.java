package nyapc.crawler.dao;

import java.util.List;


public interface IdxDao {
	boolean send(List<IdxAtt> idxList);
}
