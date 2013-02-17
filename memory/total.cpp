#include <list>
#include <vector>
using namespace std;

class Memory;

class FindEmptyAlgo {
	  protected:
	  Memory *memory;
	  public:
	  void setMemory(Memory *mem){
	  	   memory = mem;
   	  }
   	  
   	  virtual int findSpace(const int &spaceReq) = 0;
};


class Process {
	  int pid;
	  int size;
	  public:
	  Process( int id, int s){
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
	  			
      FindEmptyAlgo * findAlgo;    
      list<Process> procList;
      list<int> startPos;
      list<int> endPos;
      
      int totalSize;
      int nProcess;
      
	  public:
      Memory( FindEmptyAlgo *f, int t): findAlgo(f), totalSize(t){             
	  		  f->setMemory(this);			   
      }
      virtual void insert(Process) = 0;
      virtual void deleteP(int pid){
              int i=0;
              list<Process> :: iterator pit;
              pit = procList.begin();
              int nProcess = procList.size();
              list<int> :: iterator sit = startPos.begin();
              list<int> :: iterator eit = endPos.begin();
              
			  for( ;sit != startPos.end() ;++pit, ++sit){
			  	   if( pit->getPid() == pid){
	   				   procList.erase(pit);
	   				   startPos.erase(sit);
	   				   endPos.erase(eit);
			  		   break;				
				   }	   
		 	  }
      }
      
      virtual void display() = 0;
      
	  list<int> getStartPos(){
	  			return startPos;
	  }
	  
	  list<Process> getProcList(){
			return procList;
	  }
	  
	  int getTotalSize() const {
	  	  return totalSize;
	  }
};


class FirstFitMVT : public FindEmptyAlgo {
	  public:
	  int findSpace(const int &spaceReq){
	  	  using namespace std;
	  	  list<int> startPos = memory->getStartPos();
	  	  list<int> :: iterator sit = startPos.begin();
	  	  
	  	  list<Process> procList = memory->getProcList();
	  	  list<Process> :: iterator pit = procList.begin();
	  	  
		  int current = 0, fragment = 0;
		  for( ; sit != startPos.end(); ++sit, ++pit){
		  	   fragment = *sit - current;
		  	   if( fragment >= spaceReq)
				   return current;
				 
			   current = *sit + pit->getSize();		   
		  }
		  int totalSize = memory->getTotalSize();
		  fragment = totalSize - current;
		  
		  if( fragment >= spaceReq)
	   	  	  return current;
			 
	      return -1;	   
	  }	  
};

class FirstFitMFT : public FindEmptyAlgo {
	  public:
	  int findSpace(const int &spaceReq){
	  	  
	  }
};

class MFT : Memory{
	  int parts; // how many partitions
	  public:
	  MFT( FindEmptyAlgo *f, int t, int p) : Memory(f, t){
	  	   parts = p;				
	  }
	  void insert(Process p){
	  	   
   	  }
	  
	  int findSpace(const int &spaceReq){
	  	  if( parts == startPos.size()){
		  	  return -1;
				// no space no empty partition	   
   		  }
   		  
   		  
					  
	  }		 
};




