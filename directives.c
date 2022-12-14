#include "headers.h"

#define SINGLE_QUOTE 39

enum directives {
	ERROR, BYTE, END, RESB, RESW, START, WORD
};

// To implement Pass 2 of the assembler for Project 3,
// Add the following function to your existing Project 2 code
int getByteWordValue(int directiveType, char* string)
{
	char buf[80];
	// printf("%s\n", string);
		int c = 0;
	switch (directiveType)
	{
	case BYTE:
		/* code */

		if(strchr(string, 'X')!=NULL){
				int number1;
				char val1[10]="";
			for(int x= 2; x<strlen(string);x++){
						

						if(strcmp(&string[x],"'")!=0){
							strcat(val1, &string[x]);
							// string[x];
							 number1 = strtol(val1, NULL, 16);


						}
			return number1;

						}


		}

		else if(strchr(string, 'C')!=NULL){
			int countV=0;
			char val[10]="";
			char hex[5];
			int number;
			
			

					for(int x= 2; x<strlen(string);x++){
						

						if(strcmp(&string[x],"'")!=0){
							// printf("%X\n",atoi(&string[x]));
							// printf("%C\n",string[x]);
							countV = (string[x]);

							

							sprintf(hex, "%X", countV);
							// printf("%s\n",hex);

						 
							
							// count+=1;
							strcat(val, hex);
							// string[x];
							 number = (int)strtol(val, NULL, 16);

             
						}
						
						
						
					}
						// printf("%s\n",val);
					return number;
				


		}
		break;
	


	case WORD:
		/* code */
	
		 c =strtol(string, NULL, 10);
		sprintf(buf,"%X", c);

		return strtol(buf, NULL, 16);

		break;
	
	}
	return-1;
}

int getMemoryAmount(int directiveType, char* string)
{
	char hex[80];
		int temp =0;
			int m=0;
			
	int i = 0;


	 switch (directiveType)
	 {
	 case ERROR:
     return 0;

		/* code */
		break;
		case BYTE:

		if(strchr(string, 'X')!=NULL){
				
				for(i=2; i<strlen(string);i++){
				// if(string[i]!='\0' ){
				while(strcmp(&string[i],"'")!=0){
					
	 				m = string[i]+ m;
   				i++;
						}

					// printf("%d", m);
				 if(m<0 ||  m>255){
		
		displayError(OUT_OF_RANGE_BYTE, string);
		exit(1);
		}
				}
	return 1;
		
			
		// strtol(string, NULL, 16);
					//out of range
		}
	 
	 	 
				 else if(strchr(string, 'C')!=NULL){
					int count=0;

					for(int x= 2; x<strlen(string);x++){

						if(strcmp(&string[x],"'")!=0){
							count+=1;


						}
					}
					
					
					return count; 

				 }
	 

	 
		/* code */
		break;
		case END:
		
		
		return 0;
	 
		/* code */
		break;
		case RESB:
		
		// temp =strtol(string, NULL, 10);
		// sprintf( hex,"%X", temp);
// printf("%ld", strtol(hex, NULL, 16));

		// return strtol(hex, NULL, 16);
		// printf("%d", atoi(string));
		return atoi(string);
	 
		/* code */
		break;
		case RESW:
		// printf("%d", atoi(string));
		return 3*atoi(string);
		// return 3*strtol(string, NULL, 10);


	 
		/* code */
		break;
		case START:
		return 0;

	 
		/* code */
		break;
		case WORD:
		if(atoi(string)<-16777216 ||atoi(string)> 16777215){
			displayError(OUT_OF_RANGE_WORD, string);
			exit(1);
		}
		return 3;
		}
	  
		return 0;
	
}

// To implement Pass 2 of the assembler for Project 3,
// Add the following function to your existing Project 2 code
bool isDataDirective(int directiveType)
{
	if(directiveType== BYTE || directiveType==WORD){
		return true;

 }
 else{
	return false;
 }
}

int isDirective(char* string) {
	if((strcmp ("BYTE", string)==0)){
		return BYTE;

	 }else if((strcmp ("END", string)==0)){
		return END;
	 }else if((strcmp ("RESB", string)==0)){
		return RESB;
	 }else if((strcmp ("RESW", string)==0)){
		return RESW;
	 }else if((strcmp ("START", string)==0)){
		return START;
		
	 }else if((strcmp ("WORD", string)==0)){
		return WORD;
	 }
	 else{
 return ERROR;

	 }

}

// To implement Pass 2 of the assembler for Project 3,
// Add the following function to your existing Project 2 code
bool isEndDirective(int directiveType)
{
	if(directiveType== END){
		return true;

 }
 else{
	return false;
 }
}

// To implement Pass 2 of the assembler for Project 3,
// Add the following function to your existing Project 2 code
bool isReserveDirective(int directiveType)
{
	if(directiveType==  RESB || directiveType==RESW){
		return true;

 }
 else{
	return false;
 }
}

bool isStartDirective(int directiveType)
{
	if(directiveType== START){
		return true;

 }
 else{
	return false;
 }
	
}