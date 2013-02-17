#include <list>
#include <vector>
#include <iostream>
#include "MyProcess.cpp"
using namespace std;

class My_MFT {
	  int partSize;
	  int nBlock;
	  bool *parts;
	  int *procs;
	  public:
	  
	  class WrongPart {};
	  class NoMemory{};
	  
	  My_MFT(int totalSize, int partS) : partSize(partS), nBlock(0){
	  		  nBlock = totalSize / partSize;
			  if( totalSize >= partSize){
				  parts = new bool[nBlock];
				  procs = new int[nBlock];
			  }
 			  else {
			  	   WrongPart exp;
			  	   throw exp;
  	   		  }
  	   		  
  	   		  for(int i=0; i<nBlock; ++i)
  	   		  		  parts[i] = false;
	  }
	  
	  void insert(MyProcess p){
	  	   int blockReq = p.getSize()/partSize;
	  	   int pos;
		   
  	   	   pos = findSpace(blockReq);
  	   	   
		   for(int i=0; i< blockReq; ++i){
				parts[pos+i] = true;
				procs[pos+i] = p.getPid();
		   }
   	  }
   	  
   	  int findSpace(int blockReq){
	  	   for(int i=0; i<nBlock-blockReq; ++i){
		   		   if( parts[i] == false){
				   	   int temp = blockReq, j =0;
					   while( temp--){
					   		  if( parts[i+j] == true)
					   		  	  break;
   				 	   }		   
   				 	   if(!temp)
   				 	   			return i;
			           else i += j;
	   			   }
		   }
		   NoMemory exp;
		   throw exp;
  	   }
  	   
  	   void deleteP(int pid){
	   		for(int i=0; i<nBlock; ++i){
	   				if( parts[i] && procs[i] == pid){
						while(procs[i] == pid){
					          parts[i] = false;
					          i++;
					 	}		
					 	break;
					}
			}
	   }
	   
	   void display(){
  		}
  	   
  	   ~My_MFT(){
	   		  delete parts;
	   		  delete procs;
	   }
};



class Simulater {
	  My_MFT memory;
	  vector<MyProcess> waitQueue;
	  public:
	  Simulater(int t, int p) : memory(t, p){
	  }
	  void simulate(){
	  	   char ch;
	  	   MyProcess process(0,0);
	  	   int pid, psize;
	  	   while(1){
	   			cout << "\nInsert a Process: (i)\n";
	   			cout << "Delete a Process: (x)\n";
	   			cout << "Display Memory Info: (d)\n";
   				cout << "Exit: (q)\n";
	   			
	   			cout << "Enter Your Choice : (i d t x)\t";
	   			cin >> ch;
	   			
	   			switch(ch){
				   case 'i':
				   		cout << "Enter Pid and Size:\t";
				   		
				        cin >> pid >> psize;
				   		process.setPid(pid);
				   		
				   		process.setSize(psize);
				   		memory.insert(process);
				   		break;
		   		
			       case 'd':
				   		memory.display();
				   		break;
				   		
		   		   case 'q':
				   		exit(0);
		   		   case 'x':
				   		cout << "Enter Pid of process to delete:\t";
				   		cin >> pid;
				   		memory.deleteP(pid);
				   		break;
   				}		
			}
   	  }	  
};


int main(){
	Simulater sim(100,20);
	sim.simulate();
	
}
