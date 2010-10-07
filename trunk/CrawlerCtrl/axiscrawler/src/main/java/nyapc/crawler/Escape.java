package nyapc.crawler;

import java.io.*;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

public class Escape {
	private static Log log = LogFactory.getLog(Escape.class.getName());

	public static void main(String args[]) {
		log.debug("Startup...");
		try {
			BufferedReader br = new BufferedReader(new InputStreamReader(
					new FileInputStream("title.dat"), "UTF-8"));
			BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(
					new FileOutputStream("title.escaped.txt")));
			try {
				String line = br.readLine();
				while (line != null) {
					String l = escape(line, "UTF-8");
					// log.debug(l);
					bw.write(l);
					bw.write("\r\n");
					line = br.readLine();
				}

				bw.close();
				br.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				log.debug(e.toString());
			}
		} catch (UnsupportedEncodingException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			log.debug(e.toString());
		}
		log.debug("Exiting...");
	}

	public static String escape(String src, String encoding) {
		if (!(src instanceof String)) {
			return null;
		}

		byte[] b = null;
		if (encoding != null && !encoding.equals("")) {
			try {
				b = src.getBytes(encoding);
			} catch (UnsupportedEncodingException e) {
				// TODO Auto-generated catch block
				log.debug(e.toString());
			}
		} else {
			b = src.getBytes();
		}
		StringBuffer tmp = new StringBuffer();
		tmp.ensureCapacity(src.length() * 9);
		for (int i = 0; i < b.length; i++) {
			if (Character.isDigit(b[i]) || Character.isLowerCase(b[i])
					|| Character.isUpperCase(b[i]))
				tmp.append((char) b[i]);
			else
				tmp.append("%" + getHexString(b[i]));
		}
		return tmp.toString();
	}

	public static String escapech(String src, String encoding) {
		if (!(src instanceof String)) {
			return null;
		}

		StringBuffer tmp = new StringBuffer();
		tmp.ensureCapacity(src.length() * 9);

		for (int i = 0; i < src.length(); i++) {
			char ch = src.charAt(i);
			if (ch < 128) {
				tmp.append(ch);
			} else {
				byte[] b = null;
				if (encoding != null && !encoding.equals("")) {
					try {
						b = String.valueOf(ch).getBytes(encoding);
					} catch (UnsupportedEncodingException e) {
						// TODO Auto-generated catch block
						log.debug(e.toString());
					}
				} else {
					b = String.valueOf(ch).getBytes();
				}
				for (int j = 0; j < b.length; j++) {
					tmp.append("%" + getHexString(b[j]));
				}
			}
		}
		return tmp.toString();
	}

	private static String getHexString(byte b) {
		String hexStr = Integer.toHexString(b).toUpperCase();
		int m = hexStr.length();
		if (m < 2) {
			hexStr = "0" + hexStr;
		} else {
			hexStr = hexStr.substring(m - 2);
		}
		return hexStr;
	}
}
