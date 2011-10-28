package com.yxhs;

import java.text.SimpleDateFormat;
import java.util.List;
import java.util.Stack;

import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.TableItem;
import org.pentaho.di.core.Const;
import org.pentaho.di.core.exception.KettleException;
import org.pentaho.di.core.row.RowDataUtil;
import org.pentaho.di.core.row.RowMeta;
import org.pentaho.di.core.row.RowMetaInterface;
import org.pentaho.di.trans.Trans;
import org.pentaho.di.trans.TransMeta;
import org.pentaho.di.trans.step.*;

import weibo4j.Paging;
import weibo4j.Status;
import weibo4j.Weibo;
import weibo4j.WeiboException;


public class SinaWeiboStep extends BaseStep implements StepInterface {

	private SinaWeiboStepData data;
	private SinaWeiboStepMeta meta;
	
	public SinaWeiboStep(StepMeta s, StepDataInterface stepDataInterface, int c, TransMeta t, Trans dis) {
		super(s, stepDataInterface, c, t, dis);
	}

	public boolean processRow(StepMetaInterface smi, StepDataInterface sdi) throws KettleException {
		meta = (SinaWeiboStepMeta) smi;
		data = (SinaWeiboStepData) sdi;


		if (first) {
			first = false;

			data.outputRowMeta = new RowMeta();
			meta.getFields(data.outputRowMeta, getStepname(), null, null, this);
			QueryData();
			logBasic("initialized successfully");

		}

		Object[] outputRow=null;
		if(!data.s.empty())
		{
			outputRow= (Object[]) data.s.pop();
		}

		if (outputRow == null) // no more input to be expected...
		{
			setOutputDone();
			return false;
		}
		logBasic("outputRow size: " + outputRow.length);
		putRow(data.outputRowMeta, outputRow); // copy row to possible alternate rowset(s)

		if (checkFeedback(getLinesRead())) {
			logBasic("Linenr " + getLinesRead()); // Some basic logging
		}

		return true;
	}

	public boolean init(StepMetaInterface smi, StepDataInterface sdi) {
		meta = (SinaWeiboStepMeta) smi;
		data = (SinaWeiboStepData) sdi;

		return super.init(smi, sdi);
	}

	public void dispose(StepMetaInterface smi, StepDataInterface sdi) {
		meta = (SinaWeiboStepMeta) smi;
		data = (SinaWeiboStepData) sdi;

		super.dispose(smi, sdi);
	}

	//
	// Run is were the action happens!
	public void run() {
		logBasic("Starting to run...");
		try {
			
			while (processRow(meta, data) && !isStopped())
				;
		} catch (Exception e) {
			logError("Unexpected error : " + e.toString());
			logError(Const.getStackTracker(e));
			setErrors(1);
			stopAll();
		} finally {
			dispose(meta, data);
			logBasic("Finished, processing " + getLinesRead() + " rows");
			markStop();
		}
	}
	private void QueryData()
	{
		logBasic("reading records.............");
		System.setProperty("weibo4j.oauth.consumerKey", Weibo.CONSUMER_KEY);
    	System.setProperty("weibo4j.oauth.consumerSecret", Weibo.CONSUMER_SECRET);
    	Paging paging = new Paging();
    	paging.setCount(20);
	    paging.setPage(1);
		try{
			Weibo weibo = new Weibo();
		    weibo.setToken(meta.getUser(),meta.getPasswd());
			List<Status> status = weibo.getTrendStatus(meta.getKey(),paging);
			for(Status statuses:status){
				Object[] r=new Object[4];
				RowDataUtil.addValueData(r,0,statuses.getId());
				RowDataUtil.addValueData(r,1,statuses.getText());
				RowDataUtil.addValueData(r,2,statuses.getUser().getName());
				RowDataUtil.addValueData(r,3,statuses.getCreatedAt());
				data.s.push(r);
			}
			logBasic("read:"+data.s.size()+" record!");
		}catch (WeiboException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
