/*	Christopher Snyder
	ICSI 402 Program 4
	CS146375
				*/
#include "header.h"

/* Function to assemble I type tinymips instructions. opcode parameter 
represents the opcode of the given instruction and operands parameter
represents the operands of that instruction. Given the opcode, we can 
assume what the operands should be and call sscanf accordingly to get 
the operands.
									*/
int iTypeAssembler(int opcode, char * operands){

int instruction = 0;
int rt = 0;
int rs = 0;
int immediate = 0;

//instruction is li
if(opcode == 18)
{
	sscanf(operands, "$%d,%d", &rt, &immediate);

	instruction = instruction | (opcode << 26);
	instruction = instruction | (rs << 21);
	instruction = instruction | (rt << 16);
	instruction = instruction | (immediate);
}

//instruction is addi subi muli divi modi
if(opcode == 19 || opcode == 20 || opcode == 21 || opcode == 22 || opcode == 23)
{
	sscanf(operands, "$%d,$%d,%d", &rt, &rs, &immediate);

	instruction = instruction | (opcode << 26);
	instruction = instruction | (rs << 21);
	instruction = instruction | (rt << 16);
	instruction = instruction | (immediate);
}

//instruction is lwb or swb
if(opcode == 24 || opcode == 25)
{
	sscanf(operands, "$%d,%d($%d)", &rt, &immediate, &rs);

	instruction = instruction | (opcode << 26);
	instruction = instruction | (rs << 21);
	instruction = instruction | (rt << 16);
	instruction = instruction | (immediate);
}




return instruction;
}
