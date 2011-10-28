package com.yxhs;


import java.text.SimpleDateFormat;
import java.util.List;

import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Text;
import org.eclipse.swt.events.ModifyEvent;
import org.eclipse.swt.events.ModifyListener;
import org.eclipse.swt.events.ShellAdapter;
import org.eclipse.swt.events.ShellEvent;
import org.eclipse.swt.layout.FormLayout;
import org.eclipse.swt.layout.FormData;
import org.eclipse.swt.layout.FormAttachment;
import org.eclipse.swt.widgets.Event;
import org.eclipse.swt.widgets.Listener;
import org.eclipse.swt.widgets.TabFolder;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.TabItem;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Combo;
import org.eclipse.swt.widgets.Table;
import org.eclipse.swt.widgets.TableColumn;
import org.eclipse.swt.widgets.TableItem;
import org.pentaho.di.i18n.BaseMessages;
import org.pentaho.di.trans.TransMeta;
import org.pentaho.di.trans.step.BaseStepMeta;
import org.pentaho.di.trans.step.StepDialogInterface;
import org.pentaho.di.ui.trans.step.BaseStepDialog;

import weibo4j.Paging;
import weibo4j.Status;
import weibo4j.User;
import weibo4j.Weibo;
import weibo4j.WeiboException;

public class SinaWeiboStepDialog extends BaseStepDialog implements StepDialogInterface {

	private static Class<?> PKG = SinaWeiboStepMeta.class; // for i18n purposes
	
	private SinaWeiboStepMeta input;
	
	private TabFolder tabFolder;

	private TabItem tbtmLogin;
	private Composite composite;
	private TabItem tbtmQuery;
	private Composite composite_1;
	private Text text_user;
	private Label lblUser;
	private Label lblPassword;
	private Text text_pass;
	private Label lblKeyWord;
	private Text text_key;
	private Table table;

	/**
	 * Create the dialog.
	 * @param parent
	 * @param style
	 */
	public SinaWeiboStepDialog(Shell parent, Object in, TransMeta transMeta, String sname) {
		super(parent, (BaseStepMeta) in, transMeta, sname);
		input = (SinaWeiboStepMeta) in;
	}

	/**
	 * Open the dialog.
	 * @return the result
	 */
	public String open() {
		createContents();
		
		getData();
		
		input.setChanged(changed);
		
		shell.open();
		shell.layout();
		Display display = getParent().getDisplay();
		while (!shell.isDisposed()) {
			if (!display.readAndDispatch()) {
				display.sleep();
			}
		}
		return stepname;
	}

	/**
	 * Create contents of the dialog.
	 */
	private void createContents() {
		shell = new Shell(getParent(), SWT.DIALOG_TRIM | SWT.RESIZE | SWT.MIN | SWT.MAX);
		
		shell.setLayout(new FormLayout());
		
		shell.setText(BaseMessages.getString(PKG, "SinaWeibo.Shell.Title")); 
		setShellImage(shell, input);
		
		ModifyListener lsMod = new ModifyListener() {
			public void modifyText(ModifyEvent e) {
				input.setChanged();
			}
		};
		changed = input.hasChanged();
		
		wlStepname = new Label(shell, SWT.NONE);
		FormData fd_lblStepName = new FormData();
		wlStepname.setLayoutData(fd_lblStepName);
		wlStepname.setText(BaseMessages.getString(PKG, "SinaWeibo.Label.StepName"));
		
		wStepname = new Text(shell, SWT.BORDER);
		fd_lblStepName.top = new FormAttachment(wStepname, 0, SWT.TOP);
		FormData fd_text = new FormData();
		fd_text.left = new FormAttachment(0, 200);
		fd_text.right = new FormAttachment(100, -10);
		fd_text.top = new FormAttachment(0, 10);
		wStepname.setLayoutData(fd_text);
		wStepname.setText(stepname);
		wStepname.addModifyListener(lsMod);
		
		tabFolder = new TabFolder(shell, SWT.NONE);
		fd_lblStepName.left = new FormAttachment(tabFolder, 0, SWT.LEFT);
		FormData fd_tabFolder = new FormData();
		fd_tabFolder.top = new FormAttachment(wStepname, 6);
		fd_tabFolder.left = new FormAttachment(0, 10);
		fd_tabFolder.bottom = new FormAttachment(100, -31);
		fd_tabFolder.right = new FormAttachment(100, -10);
		tabFolder.setLayoutData(fd_tabFolder);
		
		tbtmLogin = new TabItem(tabFolder, SWT.NONE);
		tbtmLogin.setText("Login");
		
		composite = new Composite(tabFolder, SWT.NONE);
		tbtmLogin.setControl(composite);
		composite.setLayout(new FormLayout());
		
		
		lblUser = new Label(composite, SWT.NONE);
		FormData fd_lblUser = new FormData();
		fd_lblUser.top = new FormAttachment(0, 25);
		fd_lblUser.left = new FormAttachment(0, 10);
		lblUser.setLayoutData(fd_lblUser);
		lblUser.setText("Token:");
		
		text_user = new Text(composite, SWT.BORDER);
		FormData fd_text_user = new FormData();
		fd_text_user.right = new FormAttachment(100, -10);
		fd_text_user.top = new FormAttachment(0, 25);
		fd_text_user.left = new FormAttachment(0, 129);
		text_user.setLayoutData(fd_text_user);
		text_user.addModifyListener(lsMod);
		
		
		
		lblPassword = new Label(composite, SWT.NONE);
		FormData fd_lblPassword = new FormData();
		fd_lblPassword.top = new FormAttachment(lblUser, 31);
		fd_lblPassword.left = new FormAttachment(0, 10);
		lblPassword.setLayoutData(fd_lblPassword);
		lblPassword.setText("Token secret:");
		
		text_pass = new Text(composite, SWT.BORDER);
		FormData fd_text_pass = new FormData();
		fd_text_pass.right = new FormAttachment(text_user, 0, SWT.RIGHT);
		fd_text_pass.top = new FormAttachment(text_user, 25);
		fd_text_pass.left = new FormAttachment(text_user, 0, SWT.LEFT);
		text_pass.setLayoutData(fd_text_pass);
		text_pass.addModifyListener(lsMod);
		
		tbtmQuery = new TabItem(tabFolder, SWT.NONE);
		tbtmQuery.setText("Query");
		
		composite_1 = new Composite(tabFolder, SWT.NONE);
		tbtmQuery.setControl(composite_1);
		composite_1.setLayout(new FormLayout());
		
		lblKeyWord = new Label(composite_1, SWT.NONE);
		FormData fd_lblKeyWord = new FormData();
		fd_lblKeyWord.top = new FormAttachment(0, 10);
		fd_lblKeyWord.left = new FormAttachment(0, 10);
		lblKeyWord.setLayoutData(fd_lblKeyWord);
		lblKeyWord.setText("Key Word:");
		
		text_key = new Text(composite_1, SWT.BORDER);
		fd_lblKeyWord.right = new FormAttachment(text_key, -6);
		FormData fd_text_4 = new FormData();
		fd_text_4.right = new FormAttachment(100, -100);
		fd_text_4.top = new FormAttachment(0, 10);
		fd_text_4.left = new FormAttachment(0, 75);
		text_key.setLayoutData(fd_text_4);
		text_key.addModifyListener(lsMod);
		
		
		table = new Table(composite_1, SWT.BORDER | SWT.FULL_SELECTION);

		FormData fd_table = new FormData();
		fd_table.right = new FormAttachment(100, -10);
		fd_table.top = new FormAttachment(0, 40);
		fd_table.bottom = new FormAttachment(100, -10);
		fd_table.left = new FormAttachment(0, 10);
		table.setLayoutData(fd_table);
		table.setHeaderVisible(true);
		table.setLinesVisible(true);
		TableColumn tblclmnId = new TableColumn(table, SWT.NONE);
		tblclmnId.setWidth(100);
		tblclmnId.setText("ID");
		
		TableColumn tblclmnText = new TableColumn(table, SWT.NONE);
		tblclmnText.setWidth(100);
		tblclmnText.setText("Text");
		
		TableColumn tblclmnUser = new TableColumn(table, SWT.NONE);
		tblclmnUser.setWidth(100);
		tblclmnUser.setText("User");
		
		TableColumn tblclmnTime = new TableColumn(table, SWT.NONE);
		tblclmnTime.setWidth(100);
		tblclmnTime.setText("time");
		
		
		Button btnPreview = new Button(composite_1, SWT.PUSH);

		FormData fd_btnPreview = new FormData();
		fd_btnPreview.left = new FormAttachment(100, -77);
		fd_btnPreview.top = new FormAttachment(0, 6);
		fd_btnPreview.right = new FormAttachment(100, -10);
		btnPreview.setLayoutData(fd_btnPreview);
		btnPreview.setText("Preview");

		
		wOK = new Button(shell, SWT.PUSH);
		FormData fd_btnOk = new FormData();
		fd_btnOk.bottom = new FormAttachment(100, -1);
		wOK.setLayoutData(fd_btnOk);
		wOK.setText(BaseMessages.getString(PKG, "System.Button.OK")); 
		
		wCancel = new Button(shell, SWT.PUSH);
		fd_btnOk.left = new FormAttachment(wCancel, -73, SWT.LEFT);
		fd_btnOk.right = new FormAttachment(wCancel, -6);
		FormData fd_btnCancel = new FormData();
		fd_btnCancel.left = new FormAttachment(100, -85);
		fd_btnCancel.bottom = new FormAttachment(100, -1);
		fd_btnCancel.right = new FormAttachment(100, -10);
		wCancel.setLayoutData(fd_btnCancel);
		wCancel.setText(BaseMessages.getString(PKG, "System.Button.Cancel")); 
		
		lsPreview = new Listener() {
			public void handleEvent(Event e) {
				preview();
			}
		};
		
		lsCancel = new Listener() {
			public void handleEvent(Event e) {
				cancel();
			}
		};
		lsOK = new Listener() {
			public void handleEvent(Event e) {
				ok();
			}
		};

		wCancel.addListener(SWT.Selection, lsCancel);
		wOK.addListener(SWT.Selection, lsOK);
		btnPreview.addListener(SWT.Selection, lsPreview);
		
		shell.addShellListener(new ShellAdapter() {
			public void shellClosed(ShellEvent e) {
				cancel();
			}
		});

	}
	public void getData() {
		wStepname.selectAll();
		wStepname.setText(stepname);
		text_user.setText(input.getUser());
		text_pass.setText(input.getPasswd());
		text_key.setText(input.getKey());
	}
	private void preview() {
		if(changed)
		{
			table.removeAll();
			System.setProperty("weibo4j.oauth.consumerKey", Weibo.CONSUMER_KEY);
	    	System.setProperty("weibo4j.oauth.consumerSecret", Weibo.CONSUMER_SECRET);
	    	Paging paging = new Paging();
	    	paging.setCount(20);
		    paging.setPage(1);
			try{
				Weibo weibo = new Weibo();
			    weibo.setToken(text_user.getText(),text_pass.getText());
				List<Status> status = weibo.getTrendStatus(text_key.getText(),paging);
				SimpleDateFormat myFmt=new SimpleDateFormat("yyyy-MM-dd HH-mm-ss");
				for(Status statuses:status){
					TableItem tm = new TableItem(table, SWT.NONE);
				    tm.setText(new String[]{""+statuses.getId(),statuses.getText(),statuses.getUser().getName(),myFmt.format(statuses.getCreatedAt())});
				}
			}catch (WeiboException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	private void cancel() {
		stepname = null;
		input.setChanged(changed);
		dispose();
	}
	
	// let the plugin know about the entered data
	private void ok() {
		if(input.hasChanged())
		{
			stepname = wStepname.getText(); // return value
			input.setUser(text_user.getText());
			input.setPasswd(text_pass.getText());
			input.setKey(text_key.getText());
		}
		dispose();
	}
}
