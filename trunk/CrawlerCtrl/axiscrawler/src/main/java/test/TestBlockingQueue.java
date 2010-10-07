package test;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;


public class TestBlockingQueue {

public static void main(String[] args) {
  BlockingQueue<Integer> DataQueue = new LinkedBlockingQueue<Integer>();
  
   Thread pt = new Thread(new Producer(DataQueue));
   pt.start();
  
   Thread ct = new Thread(new Customer(DataQueue));
   ct.start();
   }

}