/*	Christopher Snyder
	ICSI 402 Program 4
	CS146375
				*/
#include "header.h"

/* File containing all functions for the symbol table. */

//Function to create a symbol node and fill out its data fields with the parameters
struct symbolNode * createSymbolNode(char * symbol, int LC){
	struct symbolNode * sym = malloc(sizeof(struct symbolNode));
	strcpy(sym->symbol, symbol);
	sym->LC = LC;
	sym->next = NULL;
	return sym;
}

//Function to insert a symbol node into a hash table.
void insertSymbol(struct symbolNode * table[], char * symbol, int LC){
	//Create the node
	struct symbolNode * sym = createSymbolNode(symbol, LC);

	//Get the index or "key" to insert the node at from the hash function
	int key = hash(symbol, MAX_TABLE_LEN);
	
	//If the tables index does not have a linked list yet, insert the node there
	if(table[key] == NULL){
		table[key] = sym;
	}
	
	//Else insert the node at the head of the current linked list
	else{
	sym->next = table[key];
	table[key] = sym;
	}
}

//Function to set every value in the given symbol table equal to NULL
void buildSymbolTable(struct symbolNode * table[]){
	
	int i;
	for(i = 0; i < MAX_TABLE_LEN; i++)
		table[i] = NULL;

}

//Function to check if a given symbol is already in the symbol table. If the symbol exists, return 1. Else it returns 0
int checkSymbolTable(struct symbolNode * table[], char * symbol){
	int i;
	int retval = 0;
	struct symbolNode * temp;
	struct symbolNode * temp2;

	for(i = 0; i < MAX_TABLE_LEN; i++){
	
		temp = table[i];

		if(table[i] != NULL){
			if(strcmp(table[i]->symbol, symbol) == 0)
				retval = 1;
	
		while(temp->next != NULL){
			if(strcmp(temp->next->symbol, symbol) == 0)
				retval = 1;
			temp2 = temp->next;
			temp = temp2;
				}
			}
	}
return retval;
}

//Function to print the contents of the symbol table to the given file
void printSymbolTable(struct symbolNode * table[], FILE * f){
	int i;
	struct symbolNode * temp;
	struct symbolNode * temp2;

	for(i = 0; i < MAX_TABLE_LEN; i++){
	
		temp = table[i];
		
		if(table[i] != NULL){
			fprintf(f,"%s\t%d\n", table[i]->symbol, table[i]->LC);

			while(temp->next != NULL){

				fprintf(f,"%s\t%d\n", temp->next->symbol, temp->next->LC);
				temp2 = temp->next;
				temp = temp2;
					}
				}
	}
}

//Function to return the LC value of a given symbol
int getSymbolLC(struct symbolNode * table[], char * symbol){
	int i;
	int retval = 0;
	struct symbolNode * temp;
	struct symbolNode * temp2;

	for(i = 0; i < MAX_TABLE_LEN; i++){
	
		temp = table[i];

		if(table[i] != NULL){
			if(strcmp(table[i]->symbol, symbol) == 0)
				retval = table[i]->LC;
	
		while(temp->next != NULL){
			if(strcmp(temp->next->symbol, symbol) == 0)
				retval = table[i]->LC;
			temp2 = temp->next;
			temp = temp2;
				}
			}
	}
return retval;
}
