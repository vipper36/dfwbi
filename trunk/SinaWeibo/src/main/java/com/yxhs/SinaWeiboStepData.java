package com.yxhs;

import java.util.Stack;

import org.pentaho.di.core.row.RowMetaInterface;
import org.pentaho.di.trans.step.BaseStepData;
import org.pentaho.di.trans.step.StepDataInterface;

public class SinaWeiboStepData extends BaseStepData implements StepDataInterface {

	public RowMetaInterface outputRowMeta;
	public Stack s;
    public SinaWeiboStepData()
	{
		super();
		s=new Stack();
	}
}
	
