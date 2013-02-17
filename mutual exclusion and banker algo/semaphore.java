/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author 109769
 */
class semaphore {
    semaphore(){
        val = 1;
    }
    
    public int val;
    public void waitP(){
        while(val==0){;}
        val--;
    }
    synchronized void signalV(){
        val++;
    }
}
