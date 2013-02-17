#ifndef TABLEROW_H
#define TABLEROW_H

#include <iostream>
#include <vector>

const int  MAX_SIZE = 24;
class TableRow{
      private:
      char filename[MAX_SIZE];
      long int startBlock;
      long int endBlock;
	  std::vector<int> listOfBlocks;
      public:
             TableRow(){
             }
      
             TableRow(const char _filename[], const long int _startBlock, const long int _endBlock,
			 				const std::vector<int> &_listOfBlocks) : listOfBlocks(_listOfBlocks){
                     copyFileName(_filename);
                     startBlock = _startBlock;
                     endBlock = _endBlock;
             }
             
             void copyFileName(const char _filename[]){
                  long int _size = strlen(_filename);
                  
                  for(long int i=0; (i<_size) && (i < MAX_SIZE-1) && (_filename[i] != '\0'); ++i){
                          filename[i] = _filename[i];
                  }
                  filename[_size] = '\0';
             }
             
             void insert(const char _filename[], long int _startBlock, 
                  long int _endBlock){
                  copyFileName(_filename);
                  startBlock = _startBlock;
                  endBlock = _endBlock;
             }
             
             const char *getFileName(){
                   return filename;
             }
             
             long int getEndBlock(){
                  return endBlock;
             }
             
             long int getStartBlock(){
                  return startBlock;
             }
             
             std::vector<int> &getListOfBlocks(){
			 			 return listOfBlocks;	 
		 	 }
             
             void display(){
			 	  std::cout << "FileName: " << getFileName() 
							  << " | Start Block: " << getStartBlock()
							  << " | End Block: " << getEndBlock()
							  << std::endl;
 				  std::vector<int> :: iterator vit;
		   		  std::cout << "Path is :\n";
				  for( vit = listOfBlocks.begin(); vit < listOfBlocks.end(); ++vit){
				 	  std::cout << *vit << " --> ";
	  	 	      }
	  	 	      std::cout << "|X|" << std::endl;
			}
};
#endif
