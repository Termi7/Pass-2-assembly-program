#include "headers.h"

#define COMMENT 35
#define INDEX_STRING ",X"
#define INPUT_BUF_SIZE 60
#define NEW_LINE 10
#define SPACE 32
#define SYMBOL_TABLE_SIZE 100

// Pass 2 constants
#define BLANK_INSTRUCTION 0x000000
#define OPCODE_MULTIPLIER 0x10000
#define OUTPUT_BUF_SIZE 70
#define RSUB_INSTRUCTION 0x4C0000
#define X_MULTIPLER 0x8000


void performPass1(struct symbol* symbolArray[], char* filename, address* addresses);
struct segment* prepareSegments(char* line);
void trim(char string[]);

// Pass 2 function prototypes
char* createFilename(char* filename, const char* extension);
void performPass2(struct symbol* symbolTable[], char* filename, address* addresses);
void resetObjectFileData(objectFileData* objectData, address* addresses);
void writeToLstFile(FILE* file, int address, segment* segments, int opcode);
void writeToObjFile(FILE* file, objectFileData *data);

int main(int argc, char* argv[])
{
	address addresses = { 0x00, 0x00, 0x00 };

	// Your code should start here
  if (argc <  2) /* argc should be 3 for correct execution */
    {
					displayError(MISSING_COMMAND_LINE_ARGUMENTS, argv[0]);    
        	exit(1);
    }
    

    else{

			symbol *symbolTable[SYMBOL_TABLE_SIZE];
			initializeSymbolTable(symbolTable);
			// performPass1(symbolTable,"test3.sic",&addresses);
			performPass1(symbolTable,argv[1],&addresses);
			displaySymbolTable( symbolTable);
			performPass2(symbolTable,argv[1],&addresses);
		

      // printf("\n");
			// printf("Assembly Summary\n");
      // printf("----------------\n");
    	// printf("Starting Address: 0x%X\n", addresses.start);
      // printf("Ending Address: 0x%X\n", addresses.current);
      // printf("Program Size (bytes):   %d\n", addresses.current -addresses.start);
		}

	
}

// To implement Pass 2 of the assembler for Project 3,
// Add the following function to your existing Project 2 code
char* createFilename(char* filename, const char* extension)
{
	char* temp = (char*)malloc(sizeof(char) * strlen(filename) + 1);
	
	strcpy(temp, filename);
	strcpy(temp, strtok(temp, "."));
	strcat(temp, extension);
	return temp;
}

void performPass1(struct symbol* symbolTable[], char* filename, address* addresses)
{
	// Do not forget to use the following functions:

	
	// memset() - fill the buffer array with the specified character
		printf("Symbol Table Log\n");
		printf("--------------\n");
	char buffer [INPUT_BUF_SIZE];
	FILE *ptr;
	int index=0;
	ptr= fopen(filename,"r");
	int x = 0 ;
	int typeDirective=0;
	

	if(!ptr){
		// printf("File Not found");
		displayError(FILE_NOT_FOUND, filename);
		exit(1);
	}
	else{
   
	 	int i = 0;
		// printf("Hash Table Log\n");
		// printf("--------------\n");
		while ( fgets(buffer, INPUT_BUF_SIZE, ptr)){

			char *p = strstr(buffer,"\r");
			 if(p!=NULL){
			buffer[(int)(p-buffer)]='\0';
			}
      char text[20]; 
			// printf("%s\n", buffer);
			// if(addresses->current>8000){
					if(addresses->current>32768){
						sprintf(text, "%X", addresses->current);
				displayError(OUT_OF_MEMORY,text);
				exit(1);
       
			 }
			else{
			if(buffer[0]<32){

			displayError(BLANK_RECORD, &buffer[0]);
			exit(1);

			}
			else if(buffer[0]=='#'){
			  continue;
			
			}
			
			   segment *temp = prepareSegments(buffer);
				
        // printf("%d",isDirective(temp->first));
			 if (isDirective(temp->first)!=0  || isOpcode(temp->first)) {
	
				////display the illegal symbol error message
				displayError(ILLEGAL_SYMBOL, temp->first);
				exit(1);
						 
			 }

			

			 if((isDirective(temp->second)!=0)){
				// printf("%i\n",isDirective(temp->first));

				if(isStartDirective(isDirective(temp->second))){
			
//  printf("%d",atoi(temp->third));
				 long n = (int )strtol(temp->third, NULL, 16);
				
				  
				 addresses->start= n;
         addresses->current= n;
				
				}
				else{
					
					addresses->increment = getMemoryAmount(isDirective(temp->second), temp->third);
			
				}
			 }
			  else if(isOpcode(temp->second)){
				addresses->increment= 3;


			 }
			//  else{
			  if (isDirective(temp->second)==0 && !isOpcode(temp->second)){

       /// display illegal opcode directive
			 displayError(ILLEGAL_OPCODE_DIRECTIVE, temp->second);
			 exit(1);

			}


			
			if(strlen(temp->first)>0){

				insertSymbol(symbolTable,temp->first, addresses->current);

			 }


			 addresses->current += addresses->increment;
			memset(buffer, '\0', INPUT_BUF_SIZE);
		

			
			}
		}
		
		fclose(ptr);
	}
}

// To implement Pass 2 of the assembler for Project 3,
// Add the following function to your existing Project 2 code
void performPass2(struct symbol* symbolTable[], char* filename, address* addresses)
{
	// Do not modify this statement
	char buffer [OUTPUT_BUF_SIZE];
	objectFileData objectData = { 0, { 0x0 }, { "\0" }, 0, 0x0, 0, { 0 }, 0, '\0', 0x0 };
	createFilename('program.txt', 'lst');
	createFilename('program.txt', 'obj');

	FILE *ptr1;
	FILE *wptr1;
	FILE *wptr2;
	int index=0;
	ptr1= fopen(filename,"r");
	// int x = 0 ;
	// int typeDirective=0;

	if(!ptr1){
		// printf("File Not found");
		displayError(FILE_NOT_FOUND, filename);
		exit(1);
	}
	else{

		wptr1 = fopen("program.obj","w");
		wptr2 = fopen("program.lst","w");
   
	 	int i = 0;
		// printf("Hash Table Log\n");
		// printf("--------------\n");
		while ( fgets(buffer, INPUT_BUF_SIZE, ptr1)){

			// char *p = strstr(buffer,"\r");
			//  if(p!=NULL){
			// buffer[(int)(p-buffer)]='\0';
			// }

			 if(buffer[0]=='#'){
			  continue;
			
			}
       objectFileData *object ;
			segment *temp1 = prepareSegments(buffer);

			if((isDirective(temp1->second)!=0)){
		

				if(isStartDirective(isDirective(temp1->second))){
			
       
				
				
				// object->programName= 'xx0';
				object->recordType ='H';
				strcpy(object->programName,temp1->first );
				// object->programName=temp1->first;
				object->startAddress=addresses->start;
				object->recordAddress= addresses->start;
				object->programSize= addresses->current - addresses->start;

				addresses->current = addresses->start;
				writeToObjFile(wptr1, object);
				writeToLstFile( wptr2,addresses,temp1, 35);
				}
				// call the is end directive
				if(isEndDirective(temp1->second)){
					if (object->recordByteCount>0){

						writeToObjFile(wptr1, object);
					resetObjectFileData(object, addresses);
					}
						object->recordType='E';
						writeToObjFile(wptr1, object);
						writeToLstFile(wptr2,addresses,temp1, 35);
					}
					if(isReserveDirective(temp1->second)){

						if(object->recordByteCount>0){
							writeToObjFile(wptr1, object);
							resetObjectFileData(object, addresses);

						}
						writeToLstFile(wptr2,addresses,temp1,35);
						addresses->increment = getMemoryAmount(isDirective(temp1->second), temp1->third);
						// getMemoryAmount();
						object->recordAddress=addresses->increment;

						}
			


					if(isDataDirective(temp1->second)){
            addresses->increment = getMemoryAmount(isDirective(temp1->second), temp1->third);
						  if( object->recordByteCount >(MAX_RECORD_BYTE_COUNT- addresses->increment)){
								writeToObjFile(wptr1, object);
								resetObjectFileData(object, addresses);




							}
							getByteWordValue(isDirective(temp1->second), temp1->third);
              object->recordEntries->numBytes= addresses->increment;
							object->recordEntries->value = getByteWordValue(isDirective(temp1->second), temp1->third);
							object->recordEntryCount+=1;
							object->recordByteCount+=1;

							writeToLstFile(wptr2, addresses, temp1, getByteWordValue(isDirective(temp1->second), temp1->third));

							

						
					}



				}

				if(isOpcode(temp1->second)){

					if (object->recordByteCount>(MAX_RECORD_BYTE_COUNT- 3)){

						writeToObjFile(wptr1, object);
						resetObjectFileData(object, addresses);

					}

					int vic=0 ;
					vic=getOpcodeValue(temp1->second) * OPCODE_MULTIPLIER;
					if(strchr(temp1->third, 'X')!=NULL){
						vic+=X_MULTIPLER;
						vic +=getSymbolAddress(symbolTable, temp1->third);



					}

					if(strcmp(temp1->second, 'RSUB')!=0){

						if(getSymbolAddress(symbolTable, temp1->third)==-1){

							displayError(UNDEFINED_SYMBOL, temp1->third);
						}
						vic+=getSymbolAddress(symbolTable, temp1->third);


					}
					object->recordEntries->numBytes= 3;
					object->recordEntries->value=vic;
					object->recordEntryCount+= 1;
					object-> recordByteCount+=1;

          writeToLstFile(wptr2, addresses, temp1, vic);

					addresses->increment = 3;

				}



        addresses->current+=addresses->increment;
				memset(buffer, '\0', INPUT_BUF_SIZE);
			}

		}


		fclose(ptr1);
		fclose(wptr1);
		fclose(wptr2);

	

	// Your code should start here
}

segment* prepareSegments(char* statement)
{
	struct segment* temp = (segment*)malloc(sizeof(segment));
	strncpy(temp->first, statement, SEGMENT_SIZE - 1);
	strncpy(temp->second, statement + SEGMENT_SIZE - 1, SEGMENT_SIZE - 1);
	strncpy(temp->third, statement + (SEGMENT_SIZE - 1) * 2, SEGMENT_SIZE - 1);

	trim(temp->first);
	trim(temp->second);
	trim(temp->third);
	return temp;
}

// To implement Pass 2 of the assembler for Project 3,
// Add the following function to your existing Project 2 code
void resetObjectFileData(objectFileData* objectData, address* addresses)
{
	objectData->recordAddress= addresses->current;
	objectData->recordByteCount= 0;
	objectData->recordEntryCount=0;
}

// To implement Pass 2 of the assembler for Project 3,
// Use the following function to replace the function
// In your existing Project 2 code
void trim(char value[])
{
	for (int x = 0; x < SEGMENT_SIZE; x++)
	{
		if (value[x] == SPACE || x == (SEGMENT_SIZE - 1))
		{
			value[x] = '\0';
		}
	}
}

// To implement Pass 2 of the assembler for Project 3,
// Add the following function to your existing Project 2 code
void writeToLstFile(FILE* file, int address, segment* segments, int opcode)
{
	if(isDirective(segments->second)){
    if(isStartDirective || isReserveDirective){

fprintf(file, "\t%.8X %.8s %.8s %.8s \n", address,segments->first,segments->second, segments->third);
		}
		if(isEndDirective){

			printf(file, "\t%.8X %.8s %.8s %.8s", address,segments->first,segments->second, segments->third);
		}

		if(isDataDirective(segments->second)){

fprintf(file, "\t%.8X %.8s %.8s %.8s %8X \n", address,segments->first,segments->second, segments->third, opcode);
		}
	}

	if(isOpcode(segments->second)){
fprintf(file, "\t%.8X %.8s %.8s %.8s %8X \n", address,segments->first,segments->second, segments->third, opcode);

	}
}

// To implement Pass 2 of the assembler for Project 3,
// Add the following function to your existing Project 2 code
void writeToObjFile(FILE* file, objectFileData *fileData)
{
	switch (fileData->recordType)
	{
	case 'H':
	    fprintf(file, "\t%.6c %.6s %.6X \n", 'H',fileData->programName,fileData->programSize);
		break;
	case 'T':
	 fprintf(file, "\t%.6c %.6X %.6X", 'T',fileData->recordAddress,fileData->recordByteCount);

	 for(int x=0; x<len(fileData->recordEntries);x+=1){
		
		fprintf(file, "\t%.6X \n", fileData->recordEntries[x]);
	 }
	 fprintf(file, "\n");
		break;
	case 'E':

	 fprintf(file, "\t%.6c %.6X ", 'E',fileData->startAddress);
	break;
	
	}
}