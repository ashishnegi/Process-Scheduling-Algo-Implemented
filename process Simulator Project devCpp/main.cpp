/*
my response time method is wrong for atleast everyone.
it should be first time it was touched.
not when it was added to the ready queue.
*/
#include <cstdlib>
#include <iostream>
#include "FirstInFirstOut.cpp"
#include "RoundRobin.cpp"
#include "RoundRobinQuantaTime.cpp"
#include "ShortestJobFirst.cpp"
#include "MyVariableQuanta.cpp"
using namespace std;

extern int fifomain() ;
			
int main(int argc, char *argv[])
{
	int choice;
	if(argc == 1){
		cout << "Enter choice for FIFO RR RRVT SJF MY (1/2/3/4/5)";
		cin >> choice;
	} else {
		choice = atoi(argv[1]);
	}
	
	
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
		
	switch(choice){
		case 1:
			fifomain(process);
			break;
		case 2:
			RR_Scheduler::rrmain(process);
			break;
		case 3:
			RRVT_Scheduler :: rrvtmain(process);
			break;
		case 4: 
			SJF_Heap_Scheduler :: sjfmain(process);
			break;
		case 5:			
			My_Scheduler::mymain(process);
			break;
		case 6: 
			fifomain(process );
			SJF_Heap_Scheduler :: sjfmain(process);
			RR_Scheduler::rrmain(process);
			RRVT_Scheduler :: rrvtmain(process);
			My_Scheduler::mymain(process);	
			break;
	}
    system("PAUSE");
    return EXIT_SUCCESS;
}
