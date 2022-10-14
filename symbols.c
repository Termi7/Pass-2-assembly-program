#include "headers.h"

#define MOD_SIZE 10
#define SYMBOL_TABLE_SEGMENTS 10
#define SYMBOL_TABLE_SIZE 100

int computeHash(char* symbolName);

int computeHash(char* symbolName)
{
	int hashValue=0;
	int i = 0;
	while(symbolName[i]!='\0'){
	 hashValue = symbolName[i]+ hashValue;
   i++;
	}
	return (int)(hashValue%MOD_SIZE*SYMBOL_TABLE_SEGMENTS);

}

void displaySymbolTable(struct symbol* symbolTable[])
{
	printf("Symbol Table Content\n");
	printf("-----------------\n");
	printf("%s", " ");
	printf("Index  	Name                  	     Address\n");
	printf("-----  	--------------------  	    	     ---------\n");
   for(int index = 0; index<SYMBOL_TABLE_SIZE; index++) {
		if(symbolTable[index] != NULL){

				 
				  printf("%4d  		%-20s         0x%-5X \n", index, symbolTable[index]->name, symbolTable[index]->address);
	
      
   }
	 }
	
}

// To implement Pass 2 of the assembler for Project 3,
// Add the following function to your existing Project 2 code
int getSymbolAddress(struct symbol* symbolArray[], char* string)
{
	
}

void initializeSymbolTable(struct symbol* symbolTable[])
{
	for(int i=0;i<SYMBOL_TABLE_SIZE; i++){
        symbolTable[i] =NULL;
				
    }
}

void insertSymbol(struct symbol* symbolTable[], char symbolName[], int symbolAddress)
{
	int key;
	    key = computeHash(symbolName);
      
      struct symbol *ptrMemory = malloc (sizeof(struct symbol));
      
      strcpy(ptrMemory->name, symbolName);
		  ptrMemory->address= symbolAddress;

      int target=key;

      while(symbolTable[key]!= NULL){
					if(strcmp (symbolTable[key]->name, ptrMemory->name)==0){
				   displayError(DUPLICATE,symbolTable[key]->name);
				   exit(1);
					}
				
				key = key +1;
				

         key %=SYMBOL_TABLE_SIZE;
			
		}
			// int actual = key;
			
	
      symbolTable[key]= ptrMemory;


      // printf("Added %s to Symbol Table at  Index %-2d\n", symbolTable[key]->name, key);
}