#include <iostream>
#include "Continuous File Table.cpp"
using namespace std;
int main(){
    
    Table continuousTable(100,5);
    using namespace std;
    char choice;
    char filename[MAX_SIZE];
    int sizeOfFile;
    TableRow row;
    
	while( true){
		
		cout << "\nChoose a Command (i, d, f, s, x)"
			 << "\ni--> Insert"
			 << "\nd--> Display"
			 << "\nf--> Format Disk"
			 << "\ns--> Search File"
			 << "\nr--> Delete File"
			 << "\nx--> exit"
			 << endl << endl;
		
		cin >> choice;   
		try{
			switch(choice){
				case 'I':
				case 'i' :
					cout << "Enter filename:\t";
					fflush(stdin);
					cin.get(filename, MAX_SIZE, '\n');
					cout << "Enter Sizeof File:\t";
					cin >> sizeOfFile;
					continuousTable.insert(filename, sizeOfFile);
					break;
				case 'D':
				case 'd':
					continuousTable.display();
					break;
				case 'F':
				case 'f':
					char c;
					cout << "\nAre you sure you want to FORMAT:(y/n)\t";
					cin >> c;
					if(c != 'y' && c != 'Y')
						break;
					continuousTable.reset();
					break;
				case 'S':
				case 's':
					cout << "\nEnter Filename to SEARCH:\t";
					fflush(stdin);
					cin.get(filename, MAX_SIZE, '\n');
					row = continuousTable.getRow(filename);
					row.display();
					break;
				case 'R':
				case 'r':
					cout << "\nEnter Filename to DELETE:\t";
					fflush(stdin);
					cin.get(filename, MAX_SIZE, '\n');
					continuousTable.deleteRecord(filename);
					break;
				case 'X':
				case 'x':
					break;
				default:
					cerr << "\nCommand Not Found";
			}
		} catch( Table::FileAlreadyPresentException exp){
		       std::cerr << "\nException : File Already Present\n";                                                      
		} catch( Table ::  DiskFullException) {
			   std::cerr << "\nException : Disk Full\n";
		} catch( Table ::  IllegalException) {
		  		 std::cerr << "\nException : Illegal Exception\n";	 
	 	} catch ( Table ::  FillBlocksException) {
		  		std::cerr << "\nException : Some programming mistake Fill Blocks Exception\n";	
		} catch ( Table ::  FileNotFoundException) {
		  		std::cerr << "\nException : File Not Present\n";	
		}
		if(choice == 'x' || choice == 'X')
			break;  
	}    
	return 0;  
}
