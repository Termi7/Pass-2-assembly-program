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
void writeToObjFile(FILE* file, objectFileData data);

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
				// displaySymbolTable( symbolTable);
		
			performPass2(symbolTable,argv[1],&addresses);
		}

	
}

// To implement Pass 2 of the assembler for Project 3,
// Add the following function to your existing Project 2 code
char* createFilename(char* filename, const char* extension)
{
	char* temp = (char*)malloc(sizeof(char) * strlen(filename) + 1);
	char* temp1 = (char*)malloc(sizeof(char) * strlen(filename) + 1);
	
	strcpy(temp1, filename);
	strcpy(temp, strtok(temp1, "."));
	strcat(temp, extension);
	return temp;
}

void performPass1(struct symbol* symbolTable[], char* filename, address* addresses)
{
	// Do not forget to use the following functions:

	
	// memset() - fill the buffer array with the specified character
		// printf("Symbol Table Log\n");
		// printf("--------------\n");
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
		// printf("here I am"); 
	char* c =createFilename(filename, ".obj");
	char* n =createFilename(filename, ".lst");
	int startAdress= 0x0000;
	// printf("here I am");

	FILE *ptr1;
	FILE *wptr1;
	FILE *wptr2;
	int index=0;
	ptr1= fopen(filename,"r");
	

	if(!ptr1){
		// printf("File Not found");
		displayError(FILE_NOT_FOUND, filename);
		exit(1);
	}
	else{
		wptr1 = fopen(c,"w");
		wptr2 = fopen(n,"w");
   
	 	int i = 0;
		
		while ( fgets(buffer, INPUT_BUF_SIZE, ptr1)){

			 if(buffer[0]=='#'){
			  continue;
			
			}
      //  objectFileData *object ;
			segment *temp1 = prepareSegments(buffer);
			objectData.recordType='T';
			startAdress =0x0000;

			if((isDirective(temp1->second)!=0)){
		

				if(isStartDirective(isDirective(temp1->second))){



					/////

				
				// objectData.startAddress=startAdress;
				// objectData.recordAddress= startAdress;
				// objectData.programSize= addresses->current - startAdress;

				// addresses->current = startAdress;
					//////
			
      
				objectData.recordType ='H';
				strcpy(objectData.programName,temp1->first );
				objectData.startAddress=startAdress;
				objectData.recordAddress= startAdress;
				objectData.programSize= addresses->current - startAdress;

				addresses->current = startAdress;
				writeToObjFile(wptr1, objectData);
				writeToLstFile( wptr2,addresses->current,temp1,BLANK_INSTRUCTION);
				}
				// call the is end directive
				if(isEndDirective(isDirective(temp1->second))){
					if (objectData.recordByteCount>0){

						writeToObjFile(wptr1, objectData);
					resetObjectFileData(&objectData, addresses);

					}

						objectData.recordType='M';
						writeToObjFile(wptr1, objectData);

						objectData.recordType='E';
						writeToObjFile(wptr1, objectData);
						writeToLstFile(wptr2,addresses->current,temp1, BLANK_INSTRUCTION);
					}
					if(isReserveDirective(isDirective(temp1->second))){

						if(objectData.recordByteCount>0){
							writeToObjFile(wptr1, objectData);
							resetObjectFileData(&objectData, addresses);

						}
						writeToLstFile(wptr2,addresses->current,temp1,BLANK_INSTRUCTION);
						addresses->increment = getMemoryAmount(isDirective(temp1->second), temp1->third);
						// getMemoryAmount();
						objectData.recordAddress+=addresses->increment;

						}
			


					if(isDataDirective(isDirective(temp1->second))){
            addresses->increment = getMemoryAmount(isDirective(temp1->second), temp1->third);
						  if( objectData.recordByteCount >(MAX_RECORD_BYTE_COUNT- addresses->increment)){
								writeToObjFile(wptr1, objectData);
								resetObjectFileData(&objectData, addresses);




							}
							getByteWordValue(isDirective(temp1->second), temp1->third);
             objectData.recordEntries->numBytes= addresses->increment;

							 objectData.recordEntries[objectData.recordEntryCount].value = getByteWordValue(isDirective(temp1->second), temp1->third);
							objectData.recordEntryCount+=1;
							objectData.recordByteCount+=addresses->increment;
							// objectData.recordType='T';
///
							writeToLstFile(wptr2, addresses->current, temp1, getByteWordValue(isDirective(temp1->second), temp1->third));

							

						
					}



				}

				if(isOpcode(temp1->second)){

					if (objectData.recordByteCount>(MAX_RECORD_BYTE_COUNT- 3)){

						writeToObjFile(wptr1, objectData);
						resetObjectFileData(&objectData, addresses);

					}

					int vic=0 ;
					vic=getOpcodeValue(temp1->second) * OPCODE_MULTIPLIER;
					// printf("%X", vic);
					if(strstr(temp1->third, ",X")!=NULL){
						vic+=X_MULTIPLER;
						// printf("%lu",strlen(temp1->third)-2 );

						char string [20]="";

						 int lenghtVal = strlen(temp1->third);
						 strncpy(string, temp1->third, lenghtVal-2);
						 string[lenghtVal-2]='\0';

						
					

						// vic +=(getSymbolAddress(symbolTable, string) 1000);
						vic +=getSymbolAddress(symbolTable, string);



							printf("%X", getSymbolAddress(symbolTable, string));
// ///dddd
// 						if(vic >1000){
// vic=vic-1000;
// 						}

						///dd
						
						

						/////
							objectData.modificationEntries[objectData.modificationCount]= addresses->current+ 1 ;
						objectData.modificationCount+=1;





					}

					else if(strcmp(temp1->second, "RSUB")!=0){

						if(getSymbolAddress(symbolTable, temp1->third)==-1){

							displayError(UNDEFINED_SYMBOL, temp1->third);
							exit(1);
							
						}
						vic+=(getSymbolAddress(symbolTable, temp1->third) -0x1000);

						
// 						if(vic >1000){
// vic=vic-1000;
// 						}

						//////////
					

						// objectData.modificationEntries[objectData.modificationCount]=  objectData.recordEntries[objectData.recordByteCount].value;
						// objectData.modificationCount+=1;
						// printf("%X\n",objectData.recordEntries[objectData.recordByteCount].value);


					}
					
					objectData.recordEntries[objectData.recordEntryCount].numBytes= 3;
					objectData.recordEntries[objectData.recordEntryCount].value=vic;
					objectData.recordEntryCount+= 1;
					objectData.recordByteCount+=3;
					// objectData.recordType='T';



				if(getSymbolAddress(symbolTable, temp1->third)!=-1  && (strcmp(temp1->second, "RSUB")!=0)){
					objectData.modificationEntries[objectData.modificationCount]= addresses->current+ 1 ;
						objectData.modificationCount+=1;
						// printf("%X\n",objectData.recordEntries[objectData.recordByteCount].value);
	}

          writeToLstFile(wptr2, addresses->current, temp1, vic);

					addresses->increment = 3;

				}



        addresses->current+=addresses->increment;
				memset(buffer, '\0', INPUT_BUF_SIZE);
			}

		}

		fclose(wptr1);
		fclose(wptr2);

		fclose(ptr1);
		
	

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
    if((isStartDirective(isDirective(segments->second))) || (isReserveDirective(isDirective(segments->second)))){

fprintf(file, "%-8X %-8s %-8s %-8s \n", address,segments->first,segments->second, segments->third);
		}
		else if(isEndDirective(isDirective(segments->second))){

			fprintf(file, "%-8X %-8s %-8s %-8s", address,segments->first,segments->second, segments->third);
		}

		else if(isDataDirective(isDirective(segments->second))){
			if(strcmp(segments->second, "WORD")==0){

fprintf(file, "%-8X %-8s %-8s %-8s %06X \n", address,segments->first,segments->second, segments->third, opcode);
		}
		else {

			if(opcode<10){

fprintf(file, "%-8X %-8s %-8s %-8s %02X \n", address,segments->first,segments->second, segments->third, opcode);

			}
			else{
			fprintf(file, "%-8X %-8s %-8s %-8s %-6X \n", address,segments->first,segments->second, segments->third, opcode);
			}
		}
		}
	}

	if(isOpcode(segments->second)){
fprintf(file, "%-8X %-8s %-8s %-8s %06X \n", address,segments->first,segments->second, segments->third, opcode);

	}
}




	void writeToObjFile(FILE* file, objectFileData fileData)
{
	int x;
	printf("%c\n",fileData.recordType);
	switch (fileData.recordType)
	{
	case 'H':
	    fprintf(file, "%c%s  %06X%06X \n", 'H',fileData.programName, fileData.startAddress, fileData.programSize-0x1000);
		break;
	case 'T':
	//  fprintf(file, "%c%06X%06X \n", 'T',fileData.recordAddress,fileData.recordByteCount);
	  fprintf(file, "%c%06X%02X", 'T',fileData.recordAddress,fileData.recordByteCount);

     for (int x = 0  ; x<fileData.recordEntryCount;x++){

			if(fileData.recordEntries[x].value <= 1000 && fileData.recordEntries[x].value!=0 && fileData.recordEntries[x].value!=3 && fileData.recordEntries[x].value!=  0X2D ){

				fprintf(file, "%02X", fileData.recordEntries[x].value);
			}
			else{

				// printf("%X\n", fileData.recordEntries[x].value);
				// 	printf("%X\n", fileData.recordEntries[x].numBytes);
fprintf(file, "%06X", fileData.recordEntries[x].value);
		 }
		 }
		 fprintf(file, "\n");
		break;
  case'E':

	 fprintf(file, "%c%06X \n", 'E',fileData.startAddress);
	break;




	case 'M':


	
	// fprintf(file, "%c", 'M');
	for (int x = 0  ; x<fileData.modificationCount;x++){

	fprintf(file, "%c%06X%s%s%s\n", 'M',fileData.modificationEntries[x],"04","+", fileData.programName);
	// printf("%X\n",fileData.modificationEntries[x] );
	// fprintf(file, "%06X",fileData.modificationEntries[x]);

	}
	// fprintf(file, "%X%s%s\n",04,"+", fileData.programName);

	break;

	} 
}