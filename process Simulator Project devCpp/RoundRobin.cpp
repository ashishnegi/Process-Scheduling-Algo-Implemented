#ifndef RR_H
#define RR_H
#define MAX_NAME_SIZE 1024

/*
Round Robin algorithm:
	A circular queue of processes.
		At any time check if any job arrived. if yes add to CQ.
		Execute the job and see if remaining time > 0 . if it is 0 ==> job done remove from queue.
*/

#include <iostream>
#include <vector>
#include "DynamicProcess.cpp"
#include "Scheduler.cpp"
using namespace std;

class RR_JobCircularQ{
	vector<DynamicProcess> jobs;
	Scheduler *scheduler;
	int current;
	
	public:
		RR_JobCircularQ(Scheduler *_scheduler){
			current = -1;
			scheduler = _scheduler;
		}
		
		class NoJobException{};
		class JobDoneException{
			DynamicProcess process;
			public:
			JobDoneException(const DynamicProcess &p): process(p){
			}
			DynamicProcess getProcess(){
				return process;
			}
		};
		void execute(){
			if(jobs.empty()){
				NoJobException exp;
				throw exp;
			}
			current ++;
			current %= jobs.size();
			// did the job
			jobs[current].incCompleted();
			// set the response time
			jobs[current].setResponseTime(scheduler->getCurrentTime() - jobs[current].getArrivalTime());
				
			cout << jobs[current].getName() << "\t";
			// add the wait quantum to everybody other than current
			int size = jobs.size();
			for(int i=0;i<size;++i){
				if(i == current)
					continue;
				jobs[i].wait();				
			}
			
			// if completed tell the RR_Scheduler
			if(jobs[current].isCompleted()){
				JobDoneException exp(jobs[current]);
				removeCurrent();
				if(jobs.size()){
					current += (jobs.size()-1);
					current %= jobs.size();
				}
				throw exp;
			}
		}
		
		void removeCurrent(){
			//vector<DynamicProcess> :: iterator dit = jobs.begin();
			//dit = dit + current;
			//jobs.erase(dit);
			int size = jobs.size();
			for(int i=current;i<size-1;++i){
				jobs[i] = jobs[i+1];
			}
			jobs.pop_back();
		}
		
		void add(DynamicProcess &p){
			jobs.push_back(p);
		}
};

class RR_Scheduler : public Scheduler{
	vector<DynamicProcess> jobPool;
	vector<DynamicProcess> done;
	vector<int> finishTime;
	RR_JobCircularQ readyQ;
	int curJP;
	int curTime;
	int contextSwitches;
	bool jobPoolDone ;
	
	public:
		RR_Scheduler(vector<DynamicProcess> &_jobs):
			jobPool(_jobs),readyQ(this){
			sort(jobPool.begin(), jobPool.end());
			curJP = -1;
			contextSwitches = 0;
			jobPoolDone = false;
		}
		
		void removeJP(){
			if(curJP < (jobPool.size()-1)){
				curJP ++;
			} else{
				curJP++;
				jobPoolDone = true;
			}
			// throw jobPool empty exveption
		}
		
		int getCurrentTime(){
			return curTime;
		}
		
		void schedule(){
			curTime = 0;
			curJP = 0;
			int left = jobPool.size();
			curTime = jobPool[curJP].getArrivalTime();
			while(left){
				// if any job arrived at this time.
				if((!jobPoolDone) && (curTime >= jobPool[curJP].getArrivalTime())){
					// currently i am adding waitime here may be one day i would go for something ai for process
					jobPool[curJP].wait(curTime - jobPool[curJP].getArrivalTime());
					// add to queue
					readyQ.add(jobPool[curJP]);
					// remove from jobPool
					removeJP();
					//curJP++;
				}
				try{
					// execute the readyQ
					readyQ.execute();
					// increment the time
				} catch(RR_JobCircularQ :: JobDoneException exp){
					// job is compeleted add to done
					done.push_back(exp.getProcess());
					// add the finish time for this process
					finishTime.push_back(curTime+1);	
					left--;			
				}
				// increment the time
				curTime++;
				// increment Context Switches
				contextSwitches++;	
			}
		}
		
		void display(){
			cout << endl;
			cout << "*********************************************************" << endl;
			cout << "Table for Process Scheduling is:\n";
			cout << "Round Robin Method: Time Quanta is always 1\n";
			cout << "(Name ArrivalTime BurstTime ResponseTime FinishTime WaitTime):\n";
			
			//cout << "\nDisplay():\n";
			vector<DynamicProcess> :: iterator dit;
			int i=0;
			int nP = done.size();
			float avgWait=0.0f, turnAround=0.0f, avgResponse=0.0f;
			
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
		
		
		
		static int rrmain(vector<DynamicProcess> process){
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
			//cout << "Sored List is" << endl;
			for(int i=0;i<nP;++i){
					//process[i].display();
					//cout << endl;
			}
			*/
			cout << "\n-------------------------------------------------------------------\n";
			RR_Scheduler heap(process);
			//cout << "\n-------------------------------------------------------------------\n";
			heap.schedule();
			cout << "\n-------------------------------------------------------------------\n";
			heap.display();
			
			//cin >> nP;
			return 0;
		}
		

};


#endif
