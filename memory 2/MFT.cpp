#include <list>
#include <queue>
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
			int blockReq ;
			blockReq = p.getSize()/partSize;
	  	   
			 if(p.getSize()%partSize)
			 	blockReq++;
			 
	  	   int pos;
			pos = findSpace(blockReq);
			
		   for(int i=0; i< blockReq; ++i){
				parts[pos+i] = true;
				procs[pos+i] = p.getPid();
		   }
   	  }
   	  
   	  int findSpace(int blockReq){
			cout << "First Fit";
	  	   for(int i=0; i<nBlock-blockReq; ++i){
		   		   if( parts[i] == false){
				   	   int temp = blockReq, j =0;
					   while( temp){
					   		  if( parts[i+j] == true)
					   		  	  break;
					   			temp--;
					   			j++;
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
			cout << "\n***********Memory Model***********\n";
			cout << "Total Blocks: " << nBlock << " Partition Size: " << partSize << endl;
			for(int i=0; i<nBlock; ++i){
				cout << " | "  ;
				if(parts[i]){
					cout << procs[i];
				} else {
					cout << "Empty";
				}
			}
			cout << " | ";
  		}
  	   
  	   ~My_MFT(){
	   		  delete parts;
	   		  delete procs;
	   }
};



class Simulater {
	  My_MFT memory;
	  list<MyProcess> waitQueue;
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
				   		try{
							memory.insert(process);
						} catch (My_MFT::NoMemory exp){
							cout << "Memory is Full Putting in the Wait Queue";
							waitQueue.push_back(process);
						}
				   		break;
		   		
			       case 'd':
				   		memory.display();
				   		displayWaitQ();
				   		break;
				   		
		   		   case 'q':
				   		exit(0);
		   		   case 'x':
				   		cout << "Enter Pid of process to delete:\t";
				   		cin >> pid;
				   		memory.deleteP(pid);
				   		list<MyProcess> :: iterator qit;
				   		for(qit=waitQueue.begin(); qit != waitQueue.end();){
								try{
									memory.insert(*qit);
									cout << "\nAble to insert Process with pid " << qit->getPid() 
										 << " into Memory " ;
									qit = waitQueue.erase(qit);
								} catch (My_MFT::NoMemory exp){
									++qit;
								}							
						}
				   		break;
   				}		
			}
   	  }
   	  
   	  void displayWaitQ(){
			cout << "\n******Wait Queue (Pid)******\n";
			if(!waitQueue.size()){
				cout << "Empty";
				return;
			}
			list<MyProcess> :: iterator qit;
			for(qit=waitQueue.begin(); qit != waitQueue.end();++qit){
				cout << " | " << qit->getPid();
			}			
			cout << " | \n" ;
	}
		 	  
};


int main(){
	int totalSize= 100, partSize = 20;
	Simulater sim(totalSize, partSize);
	sim.simulate();
	return 0;
}
