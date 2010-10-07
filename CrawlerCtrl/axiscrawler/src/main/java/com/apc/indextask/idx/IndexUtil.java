/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.apc.indextask.idx;

import com.autonomy.aci.exceptions.IndexingException;
import com.autonomy.aci.services.IndexingService;
import java.io.*;
import java.net.*;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author ray
 */
public class IndexUtil {

    private static IndexUtil iu = new IndexUtil();

    public static IndexUtil getIndexUtil() {
        return iu;
    }

    public void exportRemoteByStateId(String stateId,
            String srcHost, String srcPort, String dstHost, String dstPort) {
        String url = "http://" + srcHost + ":" + srcPort + "/DREEXPORTREMOTE?" +
                "&TargetEngineHost=" + dstHost + "&TargetEnginePort=" + dstPort +
                "&StateMatchID=" + stateId + "&blocking=false";
        try {
            URL export = new URL(url);
            URLConnection connection = export.openConnection();
            connection.connect();
            BufferedReader rd = new BufferedReader(new InputStreamReader(connection.getInputStream()));
            String line = null;
            while ((line = rd.readLine()) != null) {
                // Process line...
                System.out.println(line);
            }
            rd.close();
        } catch (Exception ex) {
            Logger.getLogger(IndexUtil.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public void dreAddData(String data, String dstHost, String dstPort) {
        IndexingService indexer = new IndexingService(dstHost, Integer.valueOf(dstPort));
        indexer.setIndexEncoding("UTF-8");
        try {
            long i = indexer.dreAdd(data, new ArrayList());
            System.out.println("index "+i);
        } catch (IndexingException ex) {
            Logger.getLogger(IndexUtil.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
