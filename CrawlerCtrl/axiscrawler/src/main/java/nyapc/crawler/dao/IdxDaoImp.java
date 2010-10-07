package nyapc.crawler.dao;

import java.io.IOException;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.Writer;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.ContentProducer;
import org.apache.http.entity.EntityTemplate;
import org.apache.http.impl.client.DefaultHttpClient;

import java.util.List;


public class IdxDaoImp implements IdxDao {
	private static Log log = LogFactory.getLog(IdxDaoImp.class.getName());
	private String address;
	
	
	public String getAddress() {
		return address;
	}
	public void setAddress(String address) {
		this.address = address;
	}
	/*
	@Override
	public boolean send(IdxAtt idx) {
		DefaultHttpClient httpClient= new DefaultHttpClient();
		HttpPost httppost = new HttpPost( address );
		final IdxAtt ia=idx;
		// Set parameters on POST  
		ContentProducer cp = new ContentProducer() { 

			public void writeTo(OutputStream outstream) throws IOException { 
				Writer writer = new OutputStreamWriter(outstream, "UTF-8"); 
				writer.write(ia.toString()); 
				writer.flush(); 
			} 
		}; 
		HttpEntity entity = new EntityTemplate(cp); 
		httppost.setEntity(entity); 

		// Execute and print response
		try {
			HttpResponse response = httpClient.execute(httppost);
			if(response.getStatusLine().getStatusCode()==200)
			{
				HttpEntity resentity = response.getEntity();
				long len=resentity.getContentLength();
				byte [] cont=new byte[(int)len+1];
				resentity.getContent().read(cont);
				String contStr=new String(cont,"UTF-8");
			}
		} catch (ClientProtocolException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
		}

		return false;
	}
	*/
	@Override
	public boolean send(List<IdxAtt> idxList) {
		try
		{
			// TODO Auto-generated method stub
			DefaultHttpClient httpClient= new DefaultHttpClient();
			HttpPost httppost = new HttpPost( address );
			
			StringBuffer sb = new StringBuffer();
			//log.debug("befor IdxAtt loop");
			if(idxList!=null){
				for(IdxAtt idx : idxList){
					sb.append(idx.toString());
				}
			}
			//log.debug("befor IdxAtt end");
			sb.append("#DREENDDATA\n");
			sb.append("\n\n");
			
			
			
			final String str = sb.toString();
			
			//log.debug(str);
			// Set parameters on POST  
			ContentProducer cp = new ContentProducer() { 
	
				public void writeTo(OutputStream outstream) throws IOException { 
					Writer writer = new OutputStreamWriter(outstream, "UTF-8"); 
					writer.write(str); 
					writer.flush(); 
				} 
			}; 
			HttpEntity entity = new EntityTemplate(cp); 
			httppost.setEntity(entity); 
	
			// Execute and print response
			try {
				HttpResponse response = httpClient.execute(httppost);
				if(response.getStatusLine().getStatusCode()==200)
				{
					HttpEntity resentity = response.getEntity();
					long len=resentity.getContentLength();
					byte [] cont=new byte[(int)len+1];
					resentity.getContent().read(cont);
					String contStr=new String(cont,"UTF-8");
				}
			} catch (ClientProtocolException e) {
				// TODO Auto-generated catch block
				log.debug(e.toString());
			} catch (IOException e) {
				// TODO Auto-generated catch block
				log.debug(e.toString());
			}
		}catch (Exception e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
		}

		return true;		
	}
}
