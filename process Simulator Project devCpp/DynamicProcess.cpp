#ifndef DYNAMIC_PROCESS_H
#define DYNAMIC_PROCESS_H

#include "Process.cpp"
class DynamicProcess : public Process{
	  int completed;
	  int waitTime;
	  public:
	  DynamicProcess(std::string _name, int _a, int _b): 
	  Process(_name, _a, _b){
	  				 completed = 0;
	  				 waitTime = 0;
   	  } 
	  void incCompleted(){
	  	   completed++;
   	  }
   	  bool isCompleted(){
	  	   return completed >= burstTime;
	  }
	  int remainingTime(){
	  	  return burstTime - completed;
	  }
	  void wait(int time=1){
			waitTime += time;
	}
	int getWaitTime(){
		return waitTime;
	}
	
	void display(){
  	   cout << "" << name
		 	<< "\t" << arrivalTime
			<< "\t" << burstTime << "\t"
			//<< "\t" << waitTime  << "\t"
			<< "\t" << responseTime << "\t";
   	}
};
#endif
