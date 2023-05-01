# Pass 1 and Pass 2 Assembler

This project is a two-pass assembler written in C. The goal of the project is to translate an assembly language program into machine code that can be executed on a computer. The first pass of the assembler creates a symbol table that stores information about each symbol in the program such as its name, value, and location in memory. The second pass uses the symbol table to translate the assembly language program into machine code.

To use this assembler, you must first run the pass 1 code which will read the input file and create a symbol table. Then, the pass 2 code will read the input file again and generate two output files. The first output file is a list file that displays all the different address values, symbols, codes, and opcode values. The second output file is the object code that can be executed on the computer.

The assembler checks the different segments of each record to ensure that symbols already exist in the symbol table and that no new symbols are introduced. It also keeps track of the opcode value of each line and uses it in the display.

## Technologies Used
- C programming language

## Getting Started
To get started with this project, follow these steps:

1. Clone this repository to your local machine
2. Open the project in your C IDE of choice
3. Build the project
4. Run the pass 1 code and provide the input file containing the SIC program to assemble
5. Run the pass 2 code and provide the same input file
6. Two output files will be generated: a list file and an object code file

## Features
- Two-pass assembler that translates assembly language program into machine code
- Pass 1 creates a symbol table
- Pass 2 generates two output files: a list file and an object code file
- Checks the different segments of each record to ensure symbols already exist in the symbol table and that no new symbols are introduced
- Keeps track of the opcode value of each line and uses it in the display

## Limitations
- This project only supports SIC assembly language
- The assembler assumes that the input program is error-free and has a correct syntax
