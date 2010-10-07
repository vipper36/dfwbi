package test;

import java.util.concurrent.BlockingQueue;


public class Customer implements Runnable {
private BlockingQueue<Integer> DataQueue;
public Customer(BlockingQueue<Integer> DataQueue) {
   this.DataQueue = DataQueue;
}
@Override
public void run() {
   Integer i;
   while (!Thread.interrupted()){
    try {
    i = DataQueue.take();
     System.out.println("消费：" + i);
    } catch (InterruptedException e) {
     e.printStackTrace();
    }
   }
}

}
