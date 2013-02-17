#include <iostream>
#include <list>
#include "TableRow.cpp"
#define debug 1
#ifdef debug 
#define INITIAL_VALUE 0
#include <iostream>
	   using namespace std;
#endif

class Table{
      std::list<TableRow> row;
      int currentRow;
      const int blockSize;
      const int totalBlocks;
      int *bitVector; // array of bit vector
      
      public:
             class DiskFullException {};
             class IllegalException {};
             class FileAlreadyPresentException {};
             class FillBlocksException {};
             class FileNotFoundException {};
             
             Table(const int _blockSize, const int _totalBlocks)
             :blockSize(_blockSize), totalBlocks(_totalBlocks){
                     currentRow = 0; 
                     bitVector = new int[totalBlocks];
                     for(int i=0; i<totalBlocks; ++i){
                             setBitVector(i,INITIAL_VALUE);
                     }
             }
             
             void insert(const char _filename[], long int _sizeOfFile){
                  long int block = findNextBlock(_sizeOfFile);
                  long int lenOfBlock = getNoOfBlock(_sizeOfFile);
                  putIntoRowSort(_filename, block, lenOfBlock);
                  int value = 1;
				  fillBlocks(block, lenOfBlock, value);
             }
             long int getNoOfBlock(long int _sizeOfFile){
                  return _sizeOfFile/blockSize + 1;
             }
             // should have been a behaviour Interface
             void putIntoRowSequentially(const char _filename[], 
                  const long int _block , const long int _sizeOfFile){
                  row.push_back(TableRow(_filename, _block, _sizeOfFile));
                  currentRow++;
             }
             
			int compareFileNames(const char _first[], const char _second[]){
				if(!_first)
					return 1;
				if(!_second)
					return -1;
				int i;
				for(i=0; _first[i] && _second[i] ; ++i){
					if(_first[i] > _second[i])
						return -1;
					else
						if(_first[i] < _second[i])
							return 1;
				}
				if(_first[i])
					return -1;
				if(_second[i])
					return 1;
				return 0;
			}
			
             void putIntoRowSort(const char _filename[], const long int _block,
                  long int _lenOfBlock){
                  std::list<TableRow> :: iterator tit ;
                  int i=0;
                  bool got = false, sameFile = false;
                  for( tit=row.begin(); tit != row.end(); ++tit){
                       const char *rowFile = tit->getFileName();
                       switch(compareFileNames(rowFile, _filename)){
							case -1:
								row.insert(tit, TableRow(_filename, _block, _lenOfBlock));
								return;
							case 0:
								FileAlreadyPresentException exp;
	                            throw exp;
	                        case 1:
								continue;
						}
					}
                  // insert at last
				  row.push_back(TableRow(_filename, _block, _lenOfBlock));
             }
             
             void deleteRecord(const char _filename[]){
				std::list<TableRow> :: iterator tit;
				for(tit = row.begin(); tit != row.end(); ++tit){
					if(!compareFileNames(_filename, tit->getFileName())){
						char c;
						cout << "\nAre you sure you want to DELETE:(y/n)\t";
						cin >> c;
						if(c != 'y' && c != 'Y')
							return;
						int value = INITIAL_VALUE;
						fillBlocks(tit->getBlockNo(), tit->getLenOfBlocks(), value);
						row.erase(tit);
						return;
					}
				}			
				FileNotFoundException exp;
				throw exp;		
			}
			
             long int findNextBlock(long int _sizeOfFile){
                  long int lenReq = getNoOfBlock(_sizeOfFile);
                  // string matching algorithm would be fast
                  long int j=0, i=0;
				  for( i=0; i<=totalBlocks-lenReq; ){
				  	   j = 1;
                       if( bitVector[i] == INITIAL_VALUE){
                           for( j=0; j<lenReq; ++j){
                                if( bitVector[i+j] != INITIAL_VALUE)
                                    break;
						   }
				           if(j == lenReq)
							  return i;
			  		  }
			   		  i += j;		
                  }
                  DiskFullException exp;
                  throw exp;
             }
             
             void fillBlocks(const long int &blockNo, const long int &lenOfBlock, 
			 	  int &value){
		  		  if(value > 0)
		  		  		   value /= value;
				  for( int i=blockNo; i<lenOfBlock+blockNo; ++i){
				  	   if( i >= totalBlocks){
		                  IllegalException exp;
		                  throw exp;
					   }
					   
					   if( bitVector[i] == value){
  	   				   	   FillBlocksException exp;
  	   				   	   throw exp;
					   }
					   setBitVector(i,value);  
				  }
             }
             
             void display(){
                  std::list<TableRow> :: iterator tit;
                  for(tit = row.begin(); tit != row.end(); ++tit){
                          tit->display();
                  }
             }
             
             void setBitVector(int blockNo, int val){
			 	  bitVector[blockNo] = val;
			}
			
			void reset(){
				currentRow = 0; 
				bitVector = new int[blockSize];
				for(int i=0; i<blockSize; ++i){
				     setBitVector(i,1);
				}
				row.clear();
			}
			
			
			TableRow getRow(const char _filename[]){
				std::list<TableRow> :: iterator tit;
				for(tit = row.begin(); tit != row.end(); ++tit){
					if(!compareFileNames(_filename, tit->getFileName()))
						return *tit;
				}			
				FileNotFoundException exp;
				throw exp;
			}
		 	  
             ~Table(){
			 		  delete bitVector;
			 		  row.clear();
	 		  }
};

