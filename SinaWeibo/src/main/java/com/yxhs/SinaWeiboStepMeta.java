package com.yxhs;

import java.util.List;
import java.util.Map;

import org.eclipse.swt.widgets.Shell;
import org.pentaho.di.core.*;
import org.pentaho.di.core.database.DatabaseMeta; 
import org.pentaho.di.core.exception.*;
import org.pentaho.di.core.row.*;
import org.pentaho.di.core.variables.VariableSpace;
import org.pentaho.di.core.xml.XMLHandler;
import org.pentaho.di.i18n.BaseMessages;
import org.pentaho.di.repository.*;
import org.pentaho.di.trans.*;
import org.pentaho.di.trans.step.*;
import org.w3c.dom.Node;

public class SinaWeiboStepMeta extends BaseStepMeta implements StepMetaInterface {

	private static Class<?> PKG = SinaWeiboStepMeta.class; // for i18n purposes
	private String user;
	private String passwd;
	private String Key;
	


	public String getUser() {
		return user;
	}

	public void setUser(String user) {
		this.user = user;
	}

	public String getPasswd() {
		return passwd;
	}

	public void setPasswd(String passwd) {
		this.passwd = passwd;
	}

	public String getKey() {
		return Key;
	}

	public void setKey(String key) {
		Key = key;
	}

	public SinaWeiboStepMeta() {
		super(); 
	}


	public String getXML() throws KettleValueException {
		String retval = "";
		retval += "		<user>" + getUser() + "</user>" + Const.CR;
		retval += "		<passwd>" + getPasswd() + "</passwd>" + Const.CR;
		retval += "		<key>" + getUser() + "</key>" + Const.CR;
		return retval;
	}

	public void getFields(RowMetaInterface r, String origin, RowMetaInterface[] info, StepMeta nextStep, VariableSpace space) {
		ValueMetaInterface v = new ValueMeta();
		v.setName("ID");
		v.setType(ValueMeta.TYPE_INTEGER);
		v.setTrimType(ValueMeta.TRIM_TYPE_BOTH);
		v.setOrigin(origin);
		r.addValueMeta(v);
		
		v = new ValueMeta();
		v.setName("TEXT");
		v.setType(ValueMeta.TYPE_STRING);
		v.setTrimType(ValueMeta.TRIM_TYPE_BOTH);
		v.setOrigin(origin);
		r.addValueMeta(v);
		
		v = new ValueMeta();
		v.setName("NAME");
		v.setType(ValueMeta.TYPE_STRING);
		v.setTrimType(ValueMeta.TRIM_TYPE_BOTH);
		v.setOrigin(origin);
		r.addValueMeta(v);
		
		v = new ValueMeta();
		v.setName("TIME");
		v.setType(ValueMeta.TYPE_DATE);
		v.setTrimType(ValueMeta.TRIM_TYPE_BOTH);
		v.setOrigin(origin);
		r.addValueMeta(v);
	}

	public Object clone() {
		Object retval = super.clone();
		return retval;
	}

	public void loadXML(Node stepnode, List<DatabaseMeta> databases, Map<String, Counter> counters) throws KettleXMLException {

		try {
			setUser(XMLHandler.getNodeValue(XMLHandler.getSubNode(stepnode, "user")));
			setPasswd(XMLHandler.getNodeValue(XMLHandler.getSubNode(stepnode, "passwd")));
			setKey(XMLHandler.getNodeValue(XMLHandler.getSubNode(stepnode, "key")));
		} catch (Exception e) {
			throw new KettleXMLException("Template Plugin Unable to read step info from XML node", e);
		}

	}


	public void check(List<CheckResultInterface> remarks, TransMeta transmeta, StepMeta stepMeta, RowMetaInterface prev, String input[], String output[], RowMetaInterface info) {

    	
	}

	public StepDialogInterface getDialog(Shell shell, StepMetaInterface meta, TransMeta transMeta, String name) {
		return new SinaWeiboStepDialog(shell, meta, transMeta, name);
	}

	public StepInterface getStep(StepMeta stepMeta, StepDataInterface stepDataInterface, int cnr, TransMeta transMeta, Trans disp) {
		return new SinaWeiboStep(stepMeta, stepDataInterface, cnr, transMeta, disp);
	}

	public StepDataInterface getStepData() {
		return new SinaWeiboStepData();
	}

	public void readRep(Repository rep, ObjectId id_step, List<DatabaseMeta> databases, Map<String, Counter> counters) throws KettleException {
		try
		{
			user  = rep.getStepAttributeString(id_step, "user"); //$NON-NLS-1$
			passwd  = rep.getStepAttributeString(id_step, "passwd"); //$NON-NLS-1$
			Key  = rep.getStepAttributeString(id_step, "key"); //$NON-NLS-1$
		}
		catch(Exception e)
		{
			throw new KettleException(BaseMessages.getString(PKG, "TemplateStep.Exception.UnexpectedErrorInReadingStepInfo"), e);
		}
	}

	public void saveRep(Repository rep, ObjectId id_transformation, ObjectId id_step) throws KettleException
	{
		try
		{
			rep.saveStepAttribute(id_transformation, id_step, "user", user); //$NON-NLS-1$
			rep.saveStepAttribute(id_transformation, id_step, "passwd", passwd); //$NON-NLS-1$
			rep.saveStepAttribute(id_transformation, id_step, "key", Key); //$NON-NLS-1$
		}
		catch(Exception e)
		{
			throw new KettleException(BaseMessages.getString(PKG, "TemplateStep.Exception.UnableToSaveStepInfoToRepository")+id_step, e); 
		}
	}

	public void setDefault() {
		user="1d163e7b428169940e7f7c1d95cfdae4";
		passwd="7ceb2f84bd21d429453945c0aa241ec8";
		Key="市场传闻";
		
	}
}
