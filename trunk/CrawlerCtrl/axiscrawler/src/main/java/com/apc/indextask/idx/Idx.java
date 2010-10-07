/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.apc.indextask.idx;

import java.io.*;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import org.apache.log4j.Logger;

/**
 * 预先解析idx文件，后来设计对idx文件的解析由数据库完成，此段代码没有意义。
 * @author ray
 */
public class Idx {

    public Idx(String text) {
        this.text = text;
        parseSingleDoc();
    }

    public String getTitle() {
        if (null != IDX) {
            return getTagValue("DRETITLE");
        }
        return null;
    }

    public String getReference() {
        if (null != IDX) {
            return getTagValue("DREREFERENCE");
        }
        return null;
    }

    public String getTagValue(String Tag) {
        if (null != IDX) {
            List<String> set = IDX.get(Tag.toUpperCase());
            if (null != set && set.iterator().hasNext()) {
                return set.iterator().next();
            }
        }
        return null;
    }

    public List<String> getTagValues(String Tag) {
        if (null != IDX) {
            return IDX.get(Tag.toUpperCase());
        }
        return null;
    }

    public void addField(String fieldname, String value) {
        fieldname = fieldname.toUpperCase();
        if (!isReservedField(fieldname)) {
            put(fieldname, value);
        } else {
            log.debug(fieldname + " is a reserved field, you can not modify it.");
        }
    }

    public void removeField(String fieldname) {
        fieldname = fieldname.toUpperCase();
        if (!isReservedField(fieldname)) {
            if (IDX.containsKey(fieldname)) {
                List<String> list = IDX.get(fieldname);
                if (null != list) {
                    list.clear();
                }

                IDX.remove(fieldname);
            }
        } else {
            log.debug(fieldname + " is a reserved field, you can not modify it.");
        }
    }

    public void removeField(String fieldname, String value) {
        fieldname = fieldname.toUpperCase();
        if (!isReservedField(fieldname)) {
            if (IDX.containsKey(fieldname)) {
                List<String> list = IDX.get(fieldname);
                if (null != list && list.contains(value)) {
                    list.remove(value);
                }
            }
        } else {
            log.debug(fieldname + " is a reserved field, you can not modify it.");
        }
    }

    /**
     * 解析IDX文件，把一篇文档从中找出来
     * @param text
     * @param offset
     * @return
     */
    public static String parsePlainText(BufferedReader text) throws IOException {
        StringBuffer sb = new StringBuffer();

        String line = null;

        line = text.readLine();
        if (null == line) {
            return null;
        }

        sb.append(line).append('\n');

        int startPos = line.indexOf("#DREREFERENCE");
        while (startPos < 0) {
            line = text.readLine();
            if (null == line) {
                return null;
            }
            sb.append(line).append('\n');
            startPos = sb.indexOf("#DREREFERENCE");
        }

        line = text.readLine();
        if (null == line) {
            return null;
        }
        sb.append(line).append('\n');
        int endPos = line.indexOf("#DREENDDOC");
        while (endPos < 0) {
            line = text.readLine();
            if (null == line) {
                return null;
            }
            sb.append(line).append('\n');
            endPos = sb.indexOf("#DREENDDOC");
        }

        if (startPos >= 0 && endPos > 0) {
            return sb.substring(startPos, endPos + 10);
        } else {
            return null;
        }
    }

    public void parseSingleDoc() {
        if (null == text) {
            return;
        }
        String doc = text;

        IDX = new HashMap<String, List<String>>();
        String drereference = "";
        String dretitle = "";
        String dredate = "";
        String dredbname = "";
        String drecontent = "";
        //Get DREREFERENCE
        int startPos = doc.indexOf("#DREREFERENCE");
        int endPos = doc.indexOf("\n#", startPos);

        if (startPos >= 0 && endPos > 0) {
            drereference = doc.substring(startPos + 13, endPos).trim();
        }

        //Get DRETITLE
        startPos = doc.indexOf("#DRETITLE");
        endPos = doc.indexOf("\n#", startPos);

        if (startPos >= 0 && endPos > 0) {
            dretitle = doc.substring(startPos + 9, endPos).trim();
        }

        //Get DREDATE
        startPos = doc.indexOf("#DREDATE");
        endPos = doc.indexOf("\n#", startPos);

        if (startPos > 0 && endPos > 0) {
            dredate = doc.substring(startPos + 8, endPos).trim();
        }

        //Get DREDBNAME
        startPos = doc.indexOf("#DREDBNAME");
        endPos = doc.indexOf("\n#", startPos);

        if (startPos > 0 && endPos > 0) {
            dredbname = doc.substring(startPos + 10, endPos).trim();
        }

        //Get DRECONTENT
        startPos = doc.indexOf("#DRECONTENT");
        endPos = doc.indexOf("\n#DRE", startPos);
        if (startPos > 0 && endPos > 0) {
            if (doc.charAt(startPos + 12) == '\n') {
                drecontent = doc.substring(startPos + 12, endPos);
            } else {
                drecontent = doc.substring(startPos + 11, endPos);
            }

            parseDreField(doc.substring(0, startPos + 2), IDX);
        }



        put("DREREFERENCE", drereference);
        put("DRETITLE", dretitle);
        put("DREDATE", dredate);
        put("DREDBNAME", dredbname);
        put("DRECONTENT", drecontent);

        return;
    }

    private void put(String tag, String value) {
        List<String> list = null;
        if (IDX.containsKey(tag)) {
            list = IDX.get(tag);
        }

        if (null == list) {
            list = new ArrayList<String>();
            list.add(value);
            IDX.put(tag, list);
        } else {
            if (!list.contains(value)) {
                list.add(value);
            }
        }
    }

    /**
     * 把一篇文档中的DREFIELD找出来,并存储在用户指定的文件中
     * @param doc
     * @return
     */
    private void parseDreField(String doc, Map<String, List<String>> map) {
        int startPos = doc.indexOf("#DREFIELD");
        if (startPos < 0) {
            return;
        }

        int endPos = doc.indexOf("\n#", startPos + 1);

        if (null == map) {
            map = new HashMap<String, List<String>>();
        }

        while (startPos > 0 && endPos > 0) {
//            log.debug("startPos: " + startPos +" endPos: " + endPos);
            String field = doc.substring(startPos, endPos).trim().replaceAll("\n", "");

            Matcher m = drefieldPattern.matcher(field);
            if (m.matches()) {
                String tag = m.group(1).trim().toUpperCase();
                String value = m.group(2).trim();
                put(tag, value);

            }

            startPos = doc.indexOf("#DREFIELD", endPos);
            endPos = doc.indexOf("\n#", startPos + 1);
        }
    }

    private String getDreFieldsString() {
        StringBuffer sb = new StringBuffer();

        Object[] keySet = IDX.keySet().toArray();
        Arrays.sort(keySet);
        for (Object k : keySet) {
            String key = (String) k;
            if (isReservedField(key)) {
                continue;
            }

            List<String> values = IDX.get(key);
            if (null != values) {
                for (String value : values) {
                    sb.append("#DREFIELD ").append(key).
                            append("=\"").append(value.replaceAll("\"", "")).append("\"\n");
                }
            }
        }

        return sb.toString();
    }

    private boolean isReservedField(String tag) {
        if (tag.startsWith("DRE")) {
            return true;
        }
        return false;
    }

    private void removeDreField(StringBuffer doc) {
        int start = doc.indexOf("#DREFIELD");
        int end = start >= 0 ? doc.indexOf("\n#", start + 1) : -1;
        while (start >= 0 && end >= 0) {
            doc.delete(start, end + 1);

            start = doc.indexOf("#DREFIELD");
            end = start >= 0 ? doc.indexOf("\n#", start + 1) : -1;
        }
    }

    @Override
    public String toString() {
        StringBuffer doc = new StringBuffer(text);
        removeDreField(doc);
        int startPos = doc.indexOf("#DRECONTENT");
        if (startPos > 0) {
            String fields = getDreFieldsString();
            doc.insert(startPos, fields);
        }
        return doc.toString();
    }
    private static Pattern drefieldPattern = Pattern.compile("#DREFIELD\\s*(.*?)=\\\"(.*?)\\\".*", Pattern.MULTILINE);
    private Map<String, List<String>> IDX = null;
    private String text = null;

    static {
        //BaseData.loadLog4jConfigFile();
    }
    private static Logger log = Logger.getLogger("com.apc.idx");

    public static void main(String args[]) {
        String field = "#DREFIELD PUBLISHDATE=\"新商报首页 > \n 2010年1月21日\n 星期四\"\n";
        Matcher m = drefieldPattern.matcher(field);
        if(m.matches()){
        	System.out.print(m.group(1));
        }
    }
}
