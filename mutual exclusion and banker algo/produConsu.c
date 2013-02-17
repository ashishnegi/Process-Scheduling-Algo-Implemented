 #include <stdio.h>
 #ifdef __MSVCRT__
 #undef __MSVCRT__
 #endif
 #include <process.h>
 #define BUF_SIZE 100
 #define semaphore volatile int
 int buffer[BUF_SIZE];
 int pdone, cdone;
 unsigned a = 0,b=0;
 semaphore full, empty, mutex;
 
 void initialize(){
      full = 0;
      empty = BUF_SIZE;
      mutex = 1;
      pdone = cdone = 0;
 }
 
 void wait(semaphore *var){
      //printf("var wait %d" , *var);
      fflush(stdout);
      while(!(*var))
      {
             ;    
      }
      (*var)--;
 }
 
 void signal(semaphore *var){
      //printf("signal %d", *var);
      fflush(stdout);
      (*var)++;
 }
 
 void produce(){
      wait(&empty);
      wait(&mutex);
      printf("\nProcuce: %d", full);
      buffer[full] = full;
      signal(&mutex);
      signal(&full);
 }
 
 void consume(){
      wait(&full);
      wait(&mutex);
      printf("\nConsume: %d", full);
      buffer[full] = 0;
      signal(&mutex);
      signal(&empty);
}
void producer(void* nItems){
     int items=0;
     int nItem = 50;//*(int*)nItems;
     //printf("\n%d",nItem);
     fflush(stdout);
     while(nItem > items){
                  produce();
                  items++;
     }
     pdone = 1;
     _endthreadex(a);
}

void consumer(void* nItems){
     //sleep(100);
     int items=0;
     int nItem = 50;//*(int*)nItems;
     //printf("%d",nItem);
     fflush(stdout);
     while(nItem > items){
                  consume();
                  items++;
     }
     cdone = 1;
     _endthreadex(b);
}

int main(){
    initialize();
    int i=0;
    //scanf("%d",&i);
    //for(i=0; i<100;++i){
    _beginthread(producer, 0,(void*)200);
    _beginthread(consumer, 0,(void*)200);
    //_beginthreade(NULL,a,producer, (void*)200,a,&a);
    //_beginthread(NULL,a,consumer, (void*)200,a,&b);
 
    //}
    while(!pdone || !cdone){sleep(1000);}
    scanf("%d",&i);
    return ;
}


