#include "headers.h"

// To implement Pass 2 of the assembler for Project 3,
// Add the UNDEFINED_SYMBOL error to the displayError() function
void displayError(int errorType, char* errorInfo)
{
	 switch (errorType)
  {
  case MISSING_COMMAND_LINE_ARGUMENTS:
    printf("Error: Missing Command-line Arguments");
    break;
  case FILE_NOT_FOUND:
    printf("Error: File Not Found error message\n");
    break;
  case BLANK_RECORD:
    printf("Error: Source File Contains Blank Lines\n");
    break;
  case ILLEGAL_OPCODE_DIRECTIVE:
    printf("Error: Illegal Opcode or Directive (%s) Found in Source File.\n", errorInfo);
    break;
  case ILLEGAL_SYMBOL:
   printf("Error: Symbol Name (%s) Cannot be a Command or Directive.\n", errorInfo);
    break;
  case DUPLICATE:
    printf("Error: Duplicate Symbol Name (%s) Found in Source File.\n", errorInfo);
    break;
  case OUT_OF_MEMORY:
    printf("Error: Program Address (0x%s) Exceeds Maximum Memory Address [0x8000]\n", errorInfo);
    break;
  case OUT_OF_RANGE_BYTE:
    printf("Error: Byte Value (%s) Out of Range [00 to FF]\n", errorInfo);
    break;
  case OUT_OF_RANGE_WORD:
    printf("Error: Word Value (%s) Out of Range [-16,777,216 to 16,777,215]\n", errorInfo);
    break;
  
  
  }
}