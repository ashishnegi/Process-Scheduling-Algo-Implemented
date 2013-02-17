#ifndef PROCESS_H
#define PROCESS_H

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

#endif
