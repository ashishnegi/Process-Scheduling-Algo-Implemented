#ifndef FIRST_FIT_H
#define FIRST_FIT_H
#include "FindEmptyAlgo.cpp"
#include <>
#include <list>

class FirstFit : public FindEmptyAlgo {
	  public:
	  int findSpace(const int &spaceReq){
	  	  using namespace std;
	  	  list<int> startPos = memory->getStartPos();
	  	  list<int> :: iterator sit = startPos.begin();
	  	  
	  	  list<Process> proc = memory->getProcList();
		  int current = 0, fragment = 0;
		  for( ; sit != startPos.end(); ++sit){
		  	   fragment = *sit - current;
		  	   if( fragment >= spaceReq)
				   return current;
				 
			   current = *sit + proc->getSize();		   
		  }
	  }	  
};
#endif
