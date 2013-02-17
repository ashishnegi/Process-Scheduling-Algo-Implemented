
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
public class ReadersWriters {

    public static void main(String [] argv){
        ReadersWriters rw = new ReadersWriters();
        rw.createWriters(10);
        rw.createReaders(10);
    }
    
    volatile semaphore wrt, mutex;

    int readcount;
    

    ReadersWriters(){
        wrt = new semaphore();
        mutex = new semaphore();
        readcount = 0;
    }
    
    public void createWriters(int nItems){
        int items=0;
        while(nItems > items){
            Thread thread = new Thread(){
                    @Override
                public void run(){
                        try {
                            ReadersWriters.this.write();
                        } catch (InterruptedException ex) {
                            Logger.getLogger(ReadersWriters.class.getName()).log(Level.SEVERE, null, ex);
                        }
                     
                 }
            };
            thread.start();
            items++;
        }
    }

    

    private void write() throws InterruptedException {
        wrt.waitP();
        System.out.println("Writing");
        Thread.sleep(10);
        wrt.signalV();
    }

    public void createReaders(int nItems){
        int items=0;
        while(nItems > items){
            Thread thread = new Thread(){
                    @Override
                public void run(){
                        try {
                            ReadersWriters.this.read();
                        } catch (InterruptedException ex) {
                            Logger.getLogger(ReadersWriters.class.getName()).log(Level.SEVERE, null, ex);
                        }
                 }
            };
            thread.start();
            items++;
        }
    }
    private void read() throws InterruptedException {
        mutex.waitP();
        readcount++;
        System.out.println("Reader No Generated : " + readcount );
        if(readcount == 1){
            wrt.waitP();
        }
        mutex.signalV();

        Thread.sleep(readcount);

        mutex.waitP();
        System.out.println("Reader No Distroyed : " + readcount );
        readcount--;
        if(readcount == 0){
            wrt.signalV();
        }
        mutex.signalV();
    }
}
