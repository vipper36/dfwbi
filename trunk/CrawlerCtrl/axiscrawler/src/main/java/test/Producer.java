package test;

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.TimeUnit;


public class Producer implements Runnable {
private BlockingQueue<Integer> DataQueue;
private static int i = 0;
public Producer(BlockingQueue<Integer> DataQueue) {
   this.DataQueue = DataQueue;
}

@Override
public void run() {
   while (!Thread.interrupted()){
    try {
    DataQueue.add(new Integer(++i));
     System.out.println("生产：" + i);
     TimeUnit.MILLISECONDS.sleep(1000);
    } catch (InterruptedException e) {
     e.printStackTrace();
    }
   }
}

}
