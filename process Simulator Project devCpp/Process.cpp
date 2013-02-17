#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <iostream>
using namespace std;

class Process{
	  protected:
	  int arrivalTime,burstTime,responseTime;
	  std::string name;
	  
	  public:

	  Process(std::string _name, int _a, int _b){
	  			 name = _name;
	  			 arrivalTime = _a;
	  	  		 burstTime = _b;
	  	  		 responseTime = -1;
	  }
	  
	  string getName(){
			return name;
		}
	  bool operator<(const Process &p)const{
			if(arrivalTime == p.arrivalTime)
				return burstTime < p.burstTime;
	  	   return arrivalTime < p.arrivalTime;
   	  }
   	  
   	  int getArrivalTime(){
	  	  return arrivalTime;
	  }
	  
	  int getBurstTime(){
	  	  return burstTime;
	  }
   	  
   	  void setResponseTime(int time){
			// only first time
			if(time < 0)
				cout << "\n\n\nHello see the time\n\n\n";
			if(responseTime == -1){
				responseTime = time;	
			}
	  }
	  
	  int getResponseTime(){
	  	return responseTime;
	  }
			
   	  void display(){
	  	   cout << "" << name
			 	<< "\t\t" << arrivalTime
		 		<< "\t\t" << burstTime << "\t\t";
   	  }
};
#endif
