#include <list>
#include <vector>
using namespace std;
class MyProcess {
	  int pid;
	  int size;
	  public:
	  MyProcess( int id, int s){
	  		   pid = id;
	  		   size = s;
	  }	  
	  
	  int getPid() const {
	  	   return pid;
   	  }
   	  
   	  int getSize() const {
	  	  return size;
	  }
};


class Memory {
	  protected:
	  			
      list<MyProcess> procList;
      list<int> startPos;
      int totalSize;
      
	  public:
      Memory( int t): totalSize(t){             
      }
      virtual void insert(MyProcess) = 0;
      virtual void deleteP(int pid){
              int i=0;
              list<MyProcess> :: iterator pit;
              pit = procList.begin();
              int nProcess = procList.size();
              list<int> :: iterator sit = startPos.begin();
              
			  for( ;sit != startPos.end() ;++pit, ++sit){
			  	   if( pit->getPid() == pid){
	   				   procList.erase(pit);
	   				   startPos.erase(sit);
	   				   break;				
				   }	   
		 	  }
      }
      
      virtual void display() = 0;
      
	  list<int> getStartPos(){
	  			return startPos;
	  }
	  
	  list<MyProcess> getProcList(){
			return procList;
	  }
	  
	  int getTotalSize() const {
	  	  return totalSize;
	  }
};

class MFT : Memory{
	  int parts; // how many partitions
	  public:
	  MFT( int t, int p) : Memory(t){
	  	   parts = p;				
	  }
	  void insert(MyProcess p){
	  	   int pos = findSpace(p.getSize());
	  	   
	  	   startPos.insert();
	  	   		  
   	  }
	  
	  int findSpace(Process p){
	  	  if( parts == startPos.size()){
		  	  return -1;
				// no space no empty partition	   
   		  }
   		  
		  int partSize = getTotalSize()/parts;
          if(p->getSize() >= partSize)	 
   		  
   		  list<MyProcess> :: iterator pit = procList.begin();
          pit = procList.begin();
          list<int> :: iterator sit = startPos.begin();
          
          int current = 0, fragment = 0;
          
		  
		  for( ; current < parts, sit != startPos.end(); ++sit, ++pit){
		  	   if( *sit == current){
			   	   current += partSize;
			   	   continue;
   		   	   }
   		   	   sit->insert(current);
   		   	   pit->insert(process);
   		   	   return current/partSize;
		  }			  
	  }		 
};








