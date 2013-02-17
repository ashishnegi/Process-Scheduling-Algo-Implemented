#ifndef MEMORY_H
#define MEMORY_H
class Memory;

#include "FindEmptyAlgo.cpp"
#include "Process.cpp"
#include <list>
#include <vector>

using namespace std;
class Memory {
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
              
			  for( i=0; i<nProcess; ++i, ++pit, ++sit){
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
};

#endif
