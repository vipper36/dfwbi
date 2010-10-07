package nyapc.crawler.dao;

import java.util.HashMap;
import java.util.List;

public interface AgentDao {
    int save(AgentAtt agentAtt);
	int del(int id);
	AgentAtt get(int id);
    List list();
}
