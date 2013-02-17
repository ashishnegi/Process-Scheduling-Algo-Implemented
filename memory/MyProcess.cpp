#ifndef MyProcess_H
#define MyProcess_H

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
	  
	  void setPid(int p){
	  	   pid = p;
   	  }
   	  
   	  void setSize(int s){
	  	  size = s;
	  }
	  
};

#endif
