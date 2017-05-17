/*	Christopher Snyder
	ICSI 402 Program 4
	CS146375
				*/
#include "header.h"

/* Function to assemble R type tinymips instructions. opcode parameter 
represents the opcode of the given instruction and operands parameter
represents the operands of that instruction. Given the opcode, we can 
assume what the operands should be and call sscanf accordingly to get 
the operands.
									*/


int rTypeAssembler(int opcode, char * operands){

int instruction = 0;
int rs1 = 0;
int rs2 = 0;
int rt = 0;
int shamt = 0;

if(opcode == 0)
	instruction = 0;

//instruction is add sub mul div mod and or xor
if(opcode == 1 || opcode == 2 || opcode == 3 || opcode == 4 || opcode == 5 || opcode == 7 || opcode == 8 || opcode == 9)
{
	sscanf(operands, "$%d,$%d,$%d", &rt, &rs1, &rs2);

	instruction = instruction | (opcode << 26);
	instruction = instruction | (rs1 << 21);
	instruction = instruction | (rs2 << 16);
	instruction = instruction | (rt << 11);
	instruction = instruction | (shamt << 6);
}

//move or com
if(opcode == 6 || opcode == 10)
{
	sscanf(operands, "$%d,$%d", &rt, &rs1);

	instruction = instruction | (opcode << 26);
	instruction = instruction | (rs1 << 21);
	instruction = instruction | (rs2 << 16);
	instruction = instruction | (rt << 11);
	instruction = instruction | (shamt << 6);
}

//sll srl sra
if(opcode == 11 || opcode == 12 || opcode == 13)
{
	sscanf(operands, "$%d,$%d,%d", &rt, &rs1, &shamt);

	instruction = instruction | (opcode << 26);
	instruction = instruction | (rs1 << 21);
	instruction = instruction | (rs2 << 16);
	instruction = instruction | (rt << 11);
	instruction = instruction | (shamt << 6);
}

//jr rdr prr prh
if(opcode == 14 || opcode == 15 || opcode == 16 || opcode == 17)
{
	sscanf(operands, "$%d", &rt);

	instruction = instruction | (opcode << 26);
	instruction = instruction | (rs1 << 21);
	instruction = instruction | (rs2 << 16);
	instruction = instruction | (rt << 11);
	instruction = instruction | (shamt << 6);
}
return instruction;
}
