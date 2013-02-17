#ifndef SJF_H
#define SJF_H

#include <iostream>
#include <vector>
#include <string>
#define MAX_TIME 100000
#define MAX_NAME_SIZE 1024
#include "DynamicProcess.cpp"
using namespace std;

class SJF_Heap_Scheduler{
	
	//#define debug
	  int left;
	  int startJP;   // jobPool array is starting from startJP
	  int startRQ; 	// readyQ array is starting from startRQ
	  int endJP;	// end of the job pool
	  int endRQ;	// end of the ready Queue
	  int contextSwitches;
	  int curTime;
	  vector<DynamicProcess> readyQ;
	  vector<DynamicProcess> jobPool;
	  vector<int> finishTime;
	  vector<DynamicProcess> done;
	  bool jobPoolDone;
	  string lastTimePid; // process happened at last execution.
	  
	  public:
	  
	  SJF_Heap_Scheduler( vector<DynamicProcess> &_p) : lastTimePid("    "){
	  		jobPool.push_back(DynamicProcess ("",0,0));
	  		readyQ.push_back(DynamicProcess ("",0,0));
	  		
	  		for(int i=0; i<_p.size(); ++i){
	  				jobPool.push_back(_p[i]);
			}
	  		sort(jobPool.begin(), jobPool.end());
	  		left = jobPool.size()-1;
	  		startRQ = startJP = 1;
	  		endRQ = endJP = 1;
	  		contextSwitches = 0;
	  		curTime = 0;
	  		jobPoolDone = false;
	  }
	  
	  int getCurrentTime(){
			return curTime;
	  }
	  
	  void schedule(){
	  	   curTime=0;
	  	   curTime = jobPool[startJP].getArrivalTime();
	  	   while(left){
				#ifdef debug
				cout << "Current TIme: " << curTime << endl;
				#endif
 			   if( (!jobPoolDone) && (curTime >= jobPool[startJP].getArrivalTime())){
					
					// ok new job arrived.
					// add it to queue
					#ifdef debug
					cout << "Adding " ;
					jobPool[startJP].display();
					cout << "To readyQ\n";
					#endif
					jobPool[startJP].wait(curTime - jobPool[startJP].getArrivalTime());
					
					addToReadyQ(jobPool[startJP]);
					// remove it from the job pool
					removeJP();
  			   }
  			   
  			   // contextSwitch happens if last time Pid is not equal to current Pid
  			   //cout << "Checking context switch";
  			   string name(readyQ[startRQ].getName());
			   if(lastTimePid[1] == ' '){
					//cout << "YAA... inititalized !!!";
					lastTimePid[1] = name[1];
				} else {
					//cout << lastTimePid << " " << name;
					if(lastTimePid[1] != name[1]){
						//cout << "Context Switched !!!";
						contextSwitches++;
						lastTimePid[1] = name[1];
					}
				} 
			//cout << endl;	
				// execute the readyQ top most process for this unit of time
  			   execute();
  			   // increment the wait of others 
  			   waitOthers();
		 	   
				// incrementTime 
		 	   curTime++;
		 	   
  			   if( readyQ[startRQ].isCompleted()){
			   		// if process is finished remove from readyQ
			   		// and add to the list of done processes.
			   	   done.push_back(readyQ[startRQ]);
			   	   // note the finish time too.
		   		   finishTime.push_back(curTime);
		   		   // remove from readyQ
			   	   removeRQ();
			   	   left --;
		 	   }
		   }
	}
   	  
   	 void addToReadyQ(DynamicProcess p){
			// readyQ is implemented as a heap.
			// add to the end of heap
	  	   readyQ.push_back(p);
	  	   int size = readyQ.size();
	  	   // get the process p's index position
	  	   int child = size-1;
	  	   // its parent is at child/2
	  	   int parent = child / 2;
	  	   DynamicProcess temp("",0,0);
	  	   
			while(child > parent && parent > 0){ // only parent > 0 would work
				if(readyQ[child].remainingTime() < readyQ[parent].remainingTime()){
					// child is a shortest job so must be the parent :)
					swap(readyQ[child], readyQ[parent]);
				}
				// else if parent's remainingTime is equal to child's remainingTime
				// fcfs is done. (First Come First Serve)
				
				child = parent;
				parent = child / 2;
			}
	}
	
	
	void removeJP(){
		if(startJP < (jobPool.size()-1)){
			startJP ++;
		} else{
			startJP++;
			jobPoolDone = true;
		}
		// throw jobPool empty exveption
	}
	
	void execute(){
		// to execute from the readyQ's top most process
		// just decrement the process remainingTime
		readyQ[startRQ].incCompleted();
		// set the response time
		readyQ[startRQ].setResponseTime(getCurrentTime() - readyQ[startRQ].getArrivalTime());
	}
	
	void waitOthers(){
		for(int i=startRQ+1; i<readyQ.size(); ++i){
			readyQ[i].wait();
		}
	}
	
	void removeRQ(){
		//cout << "\n-------------------------------------------------------------------\n";
		//cout << "Ready remove ";
		// to remove from readyQ implemented as heap
		// put the last element on the	top of the heap
		// and adjust the heap
		if(readyQ.size() < 2){
			// throw readyQ empty exception.
			return;
		}
		if(readyQ.size() == 2){
			readyQ.pop_back();
			startRQ = 1;
			return;
		}
		#ifdef debug
		cout << "\nReadyQ is :\n";	
		vector<DynamicProcess> :: iterator ddit;
		int i=0;
		for(ddit = readyQ.begin(); ddit < readyQ.end(); ++ddit){
			ddit->display();
			cout << endl;
		}
		cout << "----------------------------------------\n";
		
		cout << "Removing from readyQ ";
		readyQ[startRQ].display();
		cout << endl;
	   	#endif
		// we have atleast two processes.
		vector<DynamicProcess> :: iterator dit;
		dit = readyQ.end();
		--dit;
		swap(readyQ[startRQ], *dit);
		
		//cout << "Now we have at start positon temporarily : ";
		//readyQ[startRQ].display();
		
		// now adjust the heap
		readyQ.pop_back();
		
		// put the top most at its right position.
		int nowNodeAt = 1;
		int child = 2;
		int timeC1, timeC2;
		
		while(1){
			if(child >= readyQ.size())
				break;
			timeC1 = readyQ[child].remainingTime();
			if(child+1 < readyQ.size()){
				timeC2 = readyQ[child+1].remainingTime();
			} else
				timeC2 = MAX_TIME;
				
			if(timeC1 > timeC2){
				child++;
				timeC1 = timeC2;
				// timeC1 is now smaller child time
			}
			// nowNodeAt is short than the child should be the child
			if(readyQ[nowNodeAt].remainingTime() > timeC1){
				swap(readyQ[nowNodeAt], readyQ[child]);
			} else
				break;
			nowNodeAt = child;
			child = nowNodeAt * 2;			
		}
		#ifdef debug
		cout << "\nReadyQ is :\n";	
		//vector<DynamicProcess> :: iterator ddit;
		//int i=0;
		for(ddit = readyQ.begin(); ddit < readyQ.end(); ++ddit){
			ddit->display();
			cout << endl;
		}
		cout << "----------------------------------------\n";
		#endif
	}
	
	
	void printHeading(){
			 cout << endl;
			 cout << "*********************************************************" << endl;
			 cout << "Table for Process Scheduling is:\n";
			 cout << "Shortest Job First\n";
			 cout << "(Name ArrivalTime BurstTime ResponseTime FinishTime  WaitTime):\n";
		
	}

	void display(){
		printHeading();
		vector<DynamicProcess> :: iterator dit;
		
		int i=0;
		int nP = done.size();
		float avgWait=0.0f, turnAround=0.0f, avgResponse = 0.0f;
		
		for(dit = done.begin(); i < nP; ++dit, ++i){
			dit->display();
			cout << finishTime[i] << "\t" << dit->getWaitTime() << endl;
			turnAround += (finishTime[i] - dit->getArrivalTime());
			avgWait += dit->getWaitTime();
			avgResponse += dit->getResponseTime();
		}
			
		 	avgWait /= nP;
		 	turnAround /= nP;
		 	avgResponse /= nP;
		 	cout << endl << "Avg Waiting Time :\t" <<  avgWait 
			 	 << endl << "Avg TurnAround Time:\t" << turnAround 
			 	 << endl << "Avg Response Time:\t"  << avgResponse
			 	 << endl << "Context Switches:\t"   << contextSwitches;
		}
	
	void swap(DynamicProcess &f, DynamicProcess &s){
		DynamicProcess temp = f;
		f = s;
		s = temp;
	}

	static int sjfmain(vector<DynamicProcess> process){
		/*
		int nP=0, a, b;
		vector<DynamicProcess> process;
		cout << "Enter Number Of Processes:\n";
		cin >> nP;
		cout << "Enter Processes (Name ArrivalTime BurstTime):\n";
		char _name[MAX_NAME_SIZE];
		for( int i=0;i<nP;++i){
	 		 cin.get();
			cin.get(_name,MAX_NAME_SIZE, '\n');	
			cin >> a >> b;
			process.push_back(DynamicProcess(_name, a, b));
		}
		
		sort(process.begin(), process.end());
		cout << "Sored List is" << endl;
		for(int i=0;i<nP;++i){
				process[i].display();
				cout << endl;
		}
		*/
		#ifdef debug
		cout << "\nheap constructor()-------------------------------------------------------------------\n";
		#endif
		SJF_Heap_Scheduler heap(process);
		#ifdef debug
		cout << "\nheap scheduler()-------------------------------------------------------------------\n";
		#endif
		heap.schedule();
		cout << "\n-------------------------------------------------------------------\n";
		//printHeading();
		heap.display();
		
		//cin >> nP;
		return 0;
	}
};

/*
int main(){
	SJF_Heap_Scheduler :: sjfmain();
}
*/
#endif
