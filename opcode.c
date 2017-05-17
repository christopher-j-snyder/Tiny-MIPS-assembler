/*	Christopher Snyder
	ICSI 402 Program 4
	CS146375
				*/
#include "header.h"

/* File containing all functions for the opcode table */

//Function to create an opcode node and fill out it's members with data from the function parameters
struct opcodeNode * createOpcodeNode(char * instr, char * format, int opcode, int numOperands){
	struct opcodeNode * n = malloc(sizeof(struct opcodeNode));
	strcpy(n->instruction, instr);
	strcpy(n->format, format);
	n->opcode = opcode;
	n->numOperands = numOperands;
	n->next = NULL;
	return n;
}

//Function to insert a node into a hash table.
void insertOpcode(struct opcodeNode * table[], char * instr, char * format, int opcode, int numOperands){
	//Create the node
	struct opcodeNode * n = createOpcodeNode(instr, format, opcode, numOperands);

	//Get the index or "key" to insert the node at from the hash function
	int key = hash(instr, MAX_TABLE_LEN);
	
	//If the tables index does not have a linked list yet, insert the node there
	if(table[key] == NULL){
		table[key] = n;
	}
	
	//Else insert the node at the head of the current linked list
	else{
	n->next = table[key];
	table[key] = n;
	}
}

//Function to initialize the opcode hash table and hard code the contents
void buildOpcodeTable(struct opcodeNode * table[]){
	int i;

	//Set every entry in the hash table to NULL 
	for(i = 0; i < MAX_TABLE_LEN; i++)
		table[i] = NULL;

	//Hard code the entire opcode table by making 36 calls to insert opcode
	insertOpcode(table, "hlt", "R", 0, 0);
	insertOpcode(table, "add", "R", 1, 3);
	insertOpcode(table, "sub", "R", 2, 3);
	insertOpcode(table, "mul", "R", 3, 3);
	insertOpcode(table, "div", "R", 4, 3);
	insertOpcode(table, "mod", "R", 5, 3);
	insertOpcode(table, "move", "R", 6, 2);
	insertOpcode(table, "and", "R", 7, 3);
	insertOpcode(table, "or", "R", 8, 3);
	insertOpcode(table, "xor", "R", 9, 3);
	insertOpcode(table, "com", "R", 10, 2);
	insertOpcode(table, "sll", "R", 11, 3);
	insertOpcode(table, "srl", "R", 12, 3);
	insertOpcode(table, "sra", "R", 13, 3);
	insertOpcode(table, "jr", "R", 14, 1);
	insertOpcode(table, "rdr", "R", 15, 1);
	insertOpcode(table, "prr", "R", 16, 1);
	insertOpcode(table, "prh", "R", 17, 1);
	insertOpcode(table, "li", "I", 18, 2);
	insertOpcode(table, "addi", "I", 19, 3);
	insertOpcode(table, "subi", "I", 20, 3);
	insertOpcode(table, "muli", "I", 21, 3);
	insertOpcode(table, "divi", "I", 22, 3);
	insertOpcode(table, "modi", "I", 23, 3);
	insertOpcode(table, "lwb", "I", 24, 3);
	insertOpcode(table, "swb", "I", 25, 3);
	insertOpcode(table, "lwa", "J", 26, 2);
	insertOpcode(table, "swa", "J", 27, 2);
	insertOpcode(table, "j", "J", 28, 1);
	insertOpcode(table, "jal", "J", 29, 1);
	insertOpcode(table, "jeq", "J", 30, 3);
	insertOpcode(table, "jne", "J", 31, 3);
	insertOpcode(table, "jlt", "J", 32, 3);
	insertOpcode(table, "jle", "J", 33, 3);
	insertOpcode(table, "jgt", "J", 34, 3);
	insertOpcode(table, "jge", "J", 35, 3);
}

//Function  (not actually used in assembler) to get the number of operands of a given instruction
int getNumOperands(struct opcodeNode * table[], char * inst){
	int i;
	int retval;
	struct opcodeNode * temp;
	struct opcodeNode * temp2;

	for(i = 0; i < MAX_TABLE_LEN; i++){
	
		temp = table[i];
		
		if(table[i] != NULL){
			if(strcmp(table[i]->instruction, inst) == 0)
				retval = table[i]->numOperands;
	
		while(temp->next != NULL){
			if(strcmp(temp->next->instruction, inst) == 0)
				retval = temp->next->numOperands;
			temp2 = temp->next;
			temp = temp2;
				}
			}
	}
return retval;
}

//Function to check if a given instruction is already in the opcode table. If the opcode exists, return 1. Else it returns 0
int checkOpcodeTable(struct opcodeNode * table[], char * inst){
	int i;
	int retval = 0;
	struct opcodeNode * temp;
	struct opcodeNode * temp2;

	for(i = 0; i < MAX_TABLE_LEN; i++){
	
		temp = table[i];

		if(table[i] != NULL){
			if(strcmp(table[i]->instruction, inst) == 0)
				retval = 1;
	
		while(temp->next != NULL){
			if(strcmp(temp->next->instruction, inst) == 0)
				retval = 1;
			temp2 = temp->next;
			temp = temp2;
				}
			}
	}
return retval;
}

//Function to get and return the format (R, I, or J) of a given instruction
char * getOpcodeFormat(struct opcodeNode * table[], char * inst){
	int i;
	char * retval = malloc(sizeof(char)*2);
	struct opcodeNode * temp;
	struct opcodeNode * temp2;

	for(i = 0; i < MAX_TABLE_LEN; i++){
	
		temp = table[i];
		
		if(table[i] != NULL){
			if(strcmp(table[i]->instruction, inst) == 0)
				strcpy(retval, table[i]->format);

		while(temp->next != NULL){
			//puts("hey");
			fflush(stdout);
			if(strcmp(temp->next->instruction, inst) == 0)
				strcpy(retval, temp->next->format);
			temp2 = temp->next;
			temp = temp2;
				}
			}
	}
return retval;
}

//Function to get and return the opcode of a given instruction
int getOpcode(struct opcodeNode * table[], char * inst){
	int i;
	int retval;
	struct opcodeNode * temp;
	struct opcodeNode * temp2;

	for(i = 0; i < MAX_TABLE_LEN; i++){
	
		temp = table[i];
		if(table[i] != NULL){
			if(strcmp(table[i]->instruction, inst) == 0)
				retval = table[i]->opcode;
	
		while(temp->next != NULL){
			if(strcmp(temp->next->instruction, inst) == 0)
				retval = temp->next->opcode;
			temp2 = temp->next;
			temp = temp2;
				}
			}
	}
return retval;
}
