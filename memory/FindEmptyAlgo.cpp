#ifndef FindEmptyAlgo_H
#define FindEmptyAlgo_H

#include "Memory.cpp"

class FindEmptyAlgo {
	  protected:
	  Memory *memory;
	  public:
	  void setMemory(Memory *mem){
	  	   memory = mem;
   	  }
   	  
   	  virtual int findSpace(const int &spaceReq) = 0;
};

#endif
