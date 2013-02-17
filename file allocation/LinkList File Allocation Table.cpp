#include <iostream>
#include <vector>
#include <list>
#include "LinkTableRow.cpp"
#define debug 1
#ifdef debug 

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
                     bitVector = new int[blockSize];
                     for(int i=0; i<blockSize; ++i){
                             setBitVector(i,1);
                     }
             }
             
             void insert(const char _filename[], long int _sizeOfFile){
                  vector<int> block = findNextBlock(_sizeOfFile);
                  long int lenOfBlock = getNoOfBlock(_sizeOfFile);
                  putIntoRowSort(_filename, block);
                  int value = 0;
				  fillBlocks(block, value);
             }
             long int getNoOfBlock(long int _sizeOfFile){
                  return _sizeOfFile/blockSize + 1;
             }
             // should have been a behaviour Interface
             void putIntoRowSequentially(const char _filename[], 
                  const long int _block , const long int _sizeOfFile){
		  		  vector<int> nothing;
                  row.push_back(TableRow(_filename, _block, _sizeOfFile, nothing));
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
			
             void putIntoRowSort(const char _filename[], const vector<int> &_blockNos){
                  std::list<TableRow> :: iterator tit ;
                  int i=0;
                  bool got = false, sameFile = false;
                  for( tit=row.begin(); tit != row.end(); ++tit){
                       const char *rowFile = tit->getFileName();
                       switch(compareFileNames(rowFile, _filename)){
							case -1:
								row.insert(tit, TableRow(_filename, *_blockNos.begin(), 
								*(--_blockNos.end()),
								 _blockNos));
								return;
							case 0:
								FileAlreadyPresentException exp;
	                            throw exp;
	                        case 1:
								continue;
						}
					}
                  // insert at last
				  row.push_back(TableRow(_filename, *_blockNos.begin(), 
								*(--_blockNos.end()), _blockNos));
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
						int value = 1;
						fillBlocks(tit->getListOfBlocks(), value);
						row.erase(tit);
						return;
					}
				}			
				FileNotFoundException exp;
				throw exp;		
			}
			
             vector<int> findNextBlock(long int _sizeOfFile){
                  long int lenReq = getNoOfBlock(_sizeOfFile);
                  // string matching algorithm would be fast
                  long int j=0, i=0;
                  vector <int> listOfBlocks;
				  for( i=0, j=0; i<=totalBlocks && j<lenReq; ++i){
				  	   if( bitVector[i] == 1){
				  	   	   listOfBlocks.push_back(i);			   
				  	   	   j++;
			   		   }
                  }
                  if( listOfBlocks.size() == lenReq)
                  	  return listOfBlocks;					 
                  DiskFullException exp;
                  throw exp;
             }
             
             void fillBlocks(vector<int> &_blockNo, int &value){
				  vector<int> :: iterator vit = _blockNo.begin();
				  if(value > 0)
		  		  		   value /= value;
 			      for( vit = _blockNo.begin(); vit < _blockNo.end(); ++vit){
				  	   if( *vit >= totalBlocks || *vit < 0){
		                  IllegalException exp;
		                  throw exp;
					   }
					   
					   if( bitVector[*vit] == value){
  	   				   	   FillBlocksException exp;
  	   				   	   throw exp;
					   }
					   setBitVector(*vit,value);  
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

