#include <iostream>
#define MAX_PRO 20
#define MAX_RES 100 
using namespace std;

int nP, nR, available[MAX_RES], work[MAX_RES], req[MAX_RES], 
    maxT[MAX_PRO][MAX_RES], allocation[MAX_PRO][MAX_RES],
    need[MAX_PRO][MAX_RES], ans[MAX_PRO];
    
bool  finish[MAX_PRO];

int main(){
    cout << "enter nP and nR:\t";
    cin >> nP;
    cin >> nR;
    
    cout << "\nEnter Max table " << nP << " * " << nR << "\n";
    for(int i=0; i<nP; ++i){
          for(int j=0; j<nR; ++j){
                  cin >> maxT[i][j];
          }
    }
    
    cout << "\nEnter Current Allocation table " << nP << " * " << nR << "\n";
    for(int i=0; i<nP; ++i){
          for(int j=0; j<nR; ++j){
                  cin >> allocation[i][j];
                  need[i][j] = maxT[i][j] - allocation[i][j];
                  if(need[i][j] < 0){
                     cout<<"Wrong Table Input";
                     exit(-1);
                  }
          }
    }
    
    cout << "\nEnter Avaiable table size: " << nR << "\n";
    for(int i=0; i<nR; ++i){
            cin >> available[i];
            work[i] = available[i];
    }
    
    int reqP;
    cout << "\nEnter No of process requesting (0-" << nP-1 << endl;
    cin >> reqP;
    
    cout << "\nEnter Request Vector of size: " << nR << "\n";
    for(int i=0; i<nR; ++i){
            cin >> req[i];
    }
    
    // algo starting...
    int start=0;
    for(int i=0; i<nR; ++i){
            if( req[i] > available[i]){
                // input is itself contradictory.
                cout << "System is unstable :( !!!";
                cin >> start;
                return 0; 
            }
    }
    
    for( int i=0; i<nR; ++i){
         available[i] -= req[i];
         work[i] = available[i];
         need[reqP][i] -= req[i];
         allocation[reqP][i] += req[i];   
    }
    
    for(int i=0; i<nP; ++i)
            finish[i] = false;
            
    bool allFinish;
    int  j=0,z,k=0;
    j=start=0;
    while(1){
             cout << "Outer from " << j << endl;
             j = start;
             allFinish = false;
             
             while(! allFinish){
                      cout << "inner from " << j << endl;
                      
                 // find somebody satisfying needj <= work
                 while(finish[j]){
                        j++;
                        j %= nP;
                        cout << "\n" << j << " "<< start << endl;
                        if( j==start){
                            // all finished
                            allFinish = true;
                            break;
                        }
                 }
                 if( allFinish){
                    break;
                 }
                 cout << "Got (1) " << j << endl;
                 
                 int i;
                 for(i=0; i<nR; ++i){
                         if( need[j][i] > work[i])
                             break;
                 }
                 
                 if(i==nR)
                 // got somebody such that finish[j] = false and needj <= work
                    break;
                    
                 j++;
                 j %= nP;
                 if(j==start)
                    allFinish = true;
                 cin >> z;
                 
             }
             
             if(allFinish)
                break;
             for(int i=0; i<nP; ++i){
                     for(int j=0; j<nR; ++j){
                             cout << need[i][j] << "\t";
                  } 
                  cout << "\n";
             }
             cout << "work" << endl;
             for(int i=0; i<nR; ++i)
                     cout << work[i] << "\t";
             cout << endl;
             start = j;
             cout << "Got (finally) " << j << endl;
             
             //work = work + allocationj
             for( int i=0; i<nR; ++i){
                  work[i] += allocation[j][i];
             }
             ans[k++] = j;
             finish[j] = true;
    }
    
    for(int i=0; i<nP; ++i)
            if(! finish[i]){
                 cout << "System is unstable :( !!!";
                 cin >> start;
                 return 0;          
            }
   cout << "System is stable :) !!!\nSequence of processes is:\n";
   
   for(int i=0; i<k; ++i)
           cout << "P" << ans[i] << " " ;
   cin >> start;
   return 0;          
} 
    

