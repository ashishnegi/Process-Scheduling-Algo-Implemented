#ifndef FIFO_H
#define FIFO_H

#include <iostream>
#include <vector>
#include <string>
#define MAX_NAME_SIZE 1024
#include "DynamicProcess.cpp"

using namespace std;
static void fifoprintHeading();
static int fifomain();

static void fifoprintHeading(){
		 cout << endl;
		 cout << "*********************************************************" << endl;
		 cout << "Table for Process Scheduling is:\n";
		 cout << "First Come First Serve\n";
		 cout << "Name\tArrivalTime\tBurstTime\tFinishTime\tWaitTime):\n";
}

static int fifomain(vector<DynamicProcess> process){
	/*
	int nP=0, a, b;
	vector<Process> process;
	cout << "Enter Number Of Processes:\n";
	cin >> nP;
	cout << "Enter Processes (Name ArrivalTime BurstTime):\n";
	char _name[MAX_NAME_SIZE];
	for( int i=0;i<nP;++i){
 		 cin.get();
		cin.get(_name,MAX_NAME_SIZE, '\n');	
		cin >> a >> b;
		process.push_back(Process(_name, a, b));
	}
	
	sort(process.begin(), process.end());
	cout << "Sored List is" << endl;
	for(int i=0;i<nP;++i){
			 process[i].display();
			 cout << endl;
	}
	*/
	
	int nP=process.size();
	fifoprintHeading();
	int wait=0, finish=0, current=0;
	float avgWait=0, turnAround = 0,avgResponse=0.0f;
	current = process[0].getArrivalTime();
	for(int i=0;i<nP;++i){
			if(current > process[i].getArrivalTime())
				wait = current - process[i].getArrivalTime();
			else{
				wait = 0;
				current = process[i].getArrivalTime();
			}
			avgWait += wait;
			finish = current + process[i].getBurstTime();
			turnAround += finish;
			cout << finish << "\t" << wait << endl;
			process[i].setResponseTime(current - process[i].getArrivalTime());
			current += process[i].getBurstTime();
			process[i].display();
 			avgResponse += process[i].getResponseTime();
	}
			
 	avgWait /= nP;
 	turnAround /= nP;
 	avgResponse /= nP;
 	cout << endl << "Avg Waiting Time :\t" <<  avgWait 
	 	 << endl << "Avg TurnAround Time:\t" << turnAround 
	 	 << endl << "Avg Response Time:\t"  << avgResponse
	 	 << endl << "Context Switches:\t"   << nP;
	return 0;
}
#endif
