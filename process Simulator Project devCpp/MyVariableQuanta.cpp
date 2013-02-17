#ifndef MY_H
#define MY_H

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

class My_JobCircularQ{
	vector<DynamicProcess> jobs;
	int current;
	Scheduler *scheduler;
	
	public:
		My_JobCircularQ(Scheduler *_scheduler){
			current = -1;
			scheduler = _scheduler;
		}
		
		class NoJobException{};
		class JobDoneException{
			DynamicProcess process;
			public :
			
			int done;
			JobDoneException(const DynamicProcess &p, int _done): process(p), done(_done){
			
			}
			DynamicProcess getProcess(){
				return process;
			}
		};
		void execute(int quanta = 1){
			if(jobs.empty()){
				NoJobException exp;
				throw exp;
			}
			current ++;
			current %= jobs.size();
			// did the job
			for(int i=0; i<quanta; ++i){
				jobs[current].incCompleted();
				// set the response time
				jobs[current].setResponseTime(scheduler->getCurrentTime()+i - jobs[current].getArrivalTime());
					
				cout << jobs[current].getName() << "\t";
				// add the wait quantum to everybody other than current
				int size = jobs.size();
				for(int j=0;j<size;++j){
					if(j == current)
						continue;
					jobs[j].wait();				
				}
				
				// if completed tell the My_Scheduler
				if(jobs[current].isCompleted()){
					JobDoneException exp(jobs[current], i+1);
					removeCurrent();
					if(jobs.size()){
						current += (jobs.size()-1);
						current %= jobs.size();
					}
					throw exp;
				}
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

class My_Scheduler : public Scheduler{
	vector<DynamicProcess> jobPool;
	vector<DynamicProcess> done;
	vector<int> finishTime;
	My_JobCircularQ readyQ;
	int curJP;
	int quanta;
	int contextSwitches;
	int curTime;
	bool jobPoolDone;
	int MIN_QUANTA;
	int MAX_QUANTA;
	
	public:
		My_Scheduler(vector<DynamicProcess> &_jobs, int _quanta)
		:jobPool(_jobs),quanta(_quanta), readyQ(this){
			sort(jobPool.begin(), jobPool.end());
			curJP = -1;
			jobPoolDone = false;
			MIN_QUANTA = 4;
			MAX_QUANTA = 8;
			contextSwitches = 0;
			curTime = 0;
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
					readyQ.execute(quanta);
					// increment time
					curTime += quanta;
					// i see that this quanta has not been able to complete the task
					// then just increment it.
					incQuanta();
					cout << "( CT: " << curTime <<")< Q: " << quanta << ">\n";
				} catch(My_JobCircularQ :: JobDoneException exp){
					// job is compeleted add to done
					done.push_back(exp.getProcess());
					curTime += exp.done;
					// change the quanta may be waitTime or turn around time 
					// might play some role too
					int wait = exp.getProcess().getWaitTime();
					int burst = exp.getProcess().getBurstTime();
					
					if(wait > 2/3*burst){
						cout << "\nWait > \n";
						decQuanta();
					} else {
						cout << "\nWait <\n";
						quanta = (quanta + exp.getProcess().getBurstTime())/2;	
					}
					// add the finish time for this process
					finishTime.push_back(curTime);	
					left--;			
					cout << "InExp Catch{} ( CT: " << curTime <<")< Q: " << quanta << ">\n";
				}
				// increment Context Switches
				contextSwitches++;	
			}
		}
		
		void incQuanta(){
			++quanta;
			truncQuanta();
		}
		
		void decQuanta(){
			--quanta;
			truncQuanta();
		}
		
		void truncQuanta(){
			if(quanta < MIN_QUANTA)
				quanta = MIN_QUANTA;
			else if(quanta > MAX_QUANTA)
				quanta = MAX_QUANTA;
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
		void display(){
			cout << endl;
			cout << "*********************************************************" << endl;
			cout << "Table for Process Scheduling is:\n";
			cout << "My Variable Quanta Method:\n" << MIN_QUANTA << " : "  << MAX_QUANTA << endl;
			cout << "(Name ArrivalTime BurstTime ResponseTime FinishTime WaitTime):\n";
			
			//cout << "\nDisplay():\n";
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
		
		static int mymain(vector<DynamicProcess> process){
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
					process[i].display();
					cout << endl;
			}
			*/
			cout << "\n-------------------------------------------------------------------\n";
			My_Scheduler heap(process, 4);
			//cout << "\n-------------------------------------------------------------------\n";
			heap.schedule();
			cout << "\n-------------------------------------------------------------------\n";
			heap.display();
			
			//cin >> nP;
			return 0;
		}


};

#endif
