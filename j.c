/*	Christopher Snyder
	ICSI 402 Program 4
	CS146375
				*/
#include "header.h"

/* Function to assemble J type tinymips instructions. opcode parameter 
represents the opcode of the given instruction and operands parameter
represents the operands of that instruction. Given the opcode, we can 
assume what the operands should be and call sscanf accordingly to get 
the operands. J type also needs the symbol table and error list as 
parameters to check for undefined symbols as an instruction operand and
the linecount to report where the undefined symbol was referenced. 
									*/

int jTypeAssembler(int opcode, char * operands, struct errorNode * errorList, struct symbolNode * symbolTable[], int lineCount){

int instruction = 0;
int rs = 0;
int rt = 0;
int address = 0;
char * label = malloc(sizeof(char)*30);

//lwa swa
if(opcode == 26 || opcode == 27)
{
	sscanf(operands, "$%d,%s", &rt, label);
	address = getSymbolLC(symbolTable, label);
	//printf("label is %s|",label);
	if(checkSymbolTable(symbolTable, label) == 1)
	{
		instruction = instruction | (opcode << 26);
		instruction = instruction | (rs << 21);
		instruction = instruction | (rt << 16);
		instruction = instruction | (address);
	}
	else
		insertErrorNode(errorList, ERR_0,label, lineCount);
	
}

//j jal
if(opcode == 28 || opcode == 29)
{
	//printf("label is %s|",operands);
	if(checkSymbolTable(symbolTable, operands) == 1)
	{
		address = getSymbolLC(symbolTable, operands);
		instruction = instruction | (opcode << 26);
		instruction = instruction | (rs << 21);
		instruction = instruction | (rt << 16);
		instruction = instruction | (address);
	}
	else
		insertErrorNode(errorList, ERR_0, operands, lineCount);

}

//jeq jne jlt jle jgt jde
if(opcode == 30 || opcode == 31 || opcode == 32 || opcode == 33 || opcode == 34 || opcode == 35)
{
	sscanf(operands, "$%d,$%d,%s", &rt, &rs, label);
	if(checkSymbolTable(symbolTable, label) == 1)
	{
		sscanf(operands, "$%d,$%d,%s", &rt, &rs, label);
		//printf("label is %s|",label);
		address = getSymbolLC(symbolTable, label);
		instruction = instruction | (opcode << 26);
		instruction = instruction | (rs << 21);
		instruction = instruction | (rt << 16);
		instruction = instruction | (address);
	}
	else
		insertErrorNode(errorList, ERR_0,label, lineCount);
}
return instruction;
}
