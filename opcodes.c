// No changes required to implement Pass 2 for Project 3
#include "headers.h"

#define INPUT_BUF_SIZE 30
#define MOD_SIZE 5
#define NEW_LINE 10
#define OPCODE_ARRAY_SIZE 26

typedef struct opcode
{
	char name[NAME_SIZE];
	int value;
} opcode;

opcode opcodes[OPCODE_ARRAY_SIZE] = {
	{"ADD",0x18},{"AND",0x40},{"COMP",0x28},{"DIV",0x24},
	{"J",0x3C},{"JEQ",0x30},{"JGT",0x34},{"JLT",0x38},
	{"JSUB",0x48},{"LDA",0x00},{"LDCH",0x50},{"LDL",0x08},
	{"LDX",0x04},{"MUL",0x20},{"OR",0x44},{"RD",0xD8},
	{"RSUB",0x4C},{"STA",0x0C},{"STCH",0x54},{"STL",0x14},
	{"STSW",0xE8},{"STX",0x10},{"SUB",0x1C},{"TD",0xE0},
	{"TIX",0x2C},{"WD",0xDC}
};

int getOpcodeValue(char* opcode)
{
	// printf("%s", opcode);
	for( int x = 0; x<OPCODE_ARRAY_SIZE;x++){
		if(strcmp(opcode,opcodes[x].name) == 0){
			// printf("%X",opcodes[x].value);
			// printf("%X", opcodes[x].value);
			return opcodes[x].value;
		}		
	}
	return -1;
	
}

bool isOpcode(char* string)
{
	int value;
  value= getOpcodeValue(string);

	if(value != -1){
		return true;
	}
	// else if(value>=0){

		return false;
}