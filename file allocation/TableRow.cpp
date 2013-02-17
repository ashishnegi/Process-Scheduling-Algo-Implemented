#ifndef TABLEROW_H
#define TABLEROW_H

#include <iostream>

const int  MAX_SIZE = 24;
class TableRow{
      public:
      char filename[MAX_SIZE];
      long int startBlock;
      long int lenOfBlocks;
      
             TableRow(){
             }
      
             TableRow(const char _filename[], long int _startBlock, long int _lenOfBlocks){
                     copyFileName(_filename);
                     startBlock = _startBlock;
                     lenOfBlocks = _lenOfBlocks;
             }
             
             void copyFileName(const char _filename[]){
                  long int _size = strlen(_filename);
                  
                  for(long int i=0; (i<_size) && (i < MAX_SIZE-1) && (_filename[i] != '\0'); ++i){
                          filename[i] = _filename[i];
                  }
                  filename[_size] = '\0';
             }
             
             void insert(const char _filename[], long int _startBlock, 
                  long int _lenOfBlocks){
                  copyFileName(_filename);
                  startBlock = _startBlock;
                  lenOfBlocks = _lenOfBlocks;
             }
             
             const char *getFileName(){
                   return filename;
             }
             
             long int getLenOfBlocks(){
                  return lenOfBlocks;
             }
             
             long int getBlockNo(){
                  return startBlock;
             }
             
             void display(){
					std::cout << "FileName: " << getFileName() 
							  << "\tStartBlock: " << getBlockNo()
							  << "\tLen Of Block: " << getLenOfBlocks()
							  << std::endl;
			}
};
#endif
