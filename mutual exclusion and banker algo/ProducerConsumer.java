
import java.util.logging.Level;
import java.util.logging.Logger;

/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author 109769
 */
public class ProducerConsumer {
    public static void main(String []argv){
        ProducerConsumer pro = new ProducerConsumer();
        pro.producer(5000);
        pro.consumer(5000);
    }
 int BUF_SIZE = 1000;
 int buffer[];
 int pdone, cdone;
 
 volatile semaphore full, empty, mutex;

 ProducerConsumer(){
        full = new semaphore();
        empty = new semaphore();
        mutex = new semaphore();
        buffer = new int[BUF_SIZE+1];
        full.val = 0;
        empty.val = BUF_SIZE;
        mutex.val = 1;
        pdone = cdone = 0;
 }

 void wait(semaphore var) throws InterruptedException{
     //synchronized (var){
      while(var.val == 0)
      {
            //Thread.sleep(1);
      }
      var.val--;
     //}
 }

 void signal(semaphore var){
     //synchronized (var){
      var.val++;
     //}
 }

 private void produce() throws InterruptedException{
      wait(empty);
      wait(mutex);
      System.out.println("Procuce: "+ full.val);
      buffer[full.val] = full.val;
      signal(full);
      signal(mutex);
 }

 private void consume() throws InterruptedException{
      wait(full);
      wait(mutex);
      System.out.println("Consume: "+ (full.val));
      buffer[full.val] = 0;
      signal(empty);
      signal(mutex);
}
void producer(final int nItems){
    Thread thread = new Thread(){
            @Override
        public void run(){
         int items=0;
         while(nItems > items){
                    try {
                        produce();
                    } catch (InterruptedException ex) {
                        Logger.getLogger(ProducerConsumer.class.getName()).log(Level.SEVERE, null, ex);
                    }
                      items++;
         }
         pdone = 1;
        }
    };
    thread.start();
}

void consumer(final int nItems){
    Thread thread = new Thread(){
            @Override
     public void run(){
      int items=0;
        while(nItems > items){
                    try {
                        consume();
                    } catch (InterruptedException ex) {
                        Logger.getLogger(ProducerConsumer.class.getName()).log(Level.SEVERE, null, ex);
                    }
                  items++;
        }
        cdone = 1;
     }
    };
    thread.start();
}
}
