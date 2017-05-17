/*	Christopher Snyder
	ICSI 402 Program 4
	CS146375
				*/
#include "header.h"


int main(int argc, char * argv[]){

//Error checking for number of command line arguments
if(argc != 2)
	die("Incorrect number of arguments. Exiting...\n");

//Initialize file pointers to be used later
FILE * asmFile;
FILE * symFile;
FILE * objFile;
FILE * errFile;

//If input file cannot be opened, exit program
if((asmFile = fopen(argv[1], "r")) == NULL)
	die("Could not open input file. Exiting...\n");

//File extensions 
char symExt[4] = "sym";
char objExt[4] = "obj";
char errExt[4] = "err";

//Create a filename to be used later based on the give extension
char * symFileName = malloc(sizeof(char) * strlen(argv[1]));
symFileName = (char *) appendExtension(argv[1], symExt);

char * objFileName = malloc(sizeof(char) * strlen(argv[1]));
objFileName = (char *) appendExtension(argv[1], objExt);

char * errFileName = malloc(sizeof(char) * strlen(argv[1]));
errFileName = (char *) appendExtension(argv[1], errExt);

int i;

//Initialize assemblers memory to 0
int memory[65535];
for(i=0; i < 65535; i++)
	memory[i] = 0;

//Initialize the opcode table and fill it out with data by calling buildOpcodeTable
struct opcodeNode * opcodeTable[MAX_TABLE_LEN];
buildOpcodeTable(opcodeTable);

//Initialize the symbol table and set every index equal to NULL by calling buildSymbolTable
struct symbolNode * symbolTable[MAX_TABLE_LEN];
buildSymbolTable(symbolTable);

struct errorNode * errorList = (struct errorNode *) createErrorNode("Empty"," ", 0);

int LC;

/* Function to implement the first pass of our 2 pass assembler.
The first pass will build the symbol table and check for multiply
defined symbols, while also reserving memory via the .word and .resw
directives in the .data section.				*/
LC = assemblerPass1(symbolTable, opcodeTable, errorList, asmFile, memory);

//Close asm file before pass 2
if(fclose(asmFile) == EOF)
	die("Could not close input file. Exiting...\n");

//Reopen asm file
if((asmFile = fopen(argv[1], "r")) == NULL)
	die("Could not open input file. Exiting...\n");

/* Function to implement the second pass of the assembler. Second pass
will check for illegal opcodes & undefined symbols, while also 
assembling all of the instructions and storing them in "memory" */
assemblerPass2(symbolTable, opcodeTable, errorList, asmFile, memory, LC);

//Close asm file
if(fclose(asmFile) == EOF)
	die("Could not close input file. Exiting...\n");

//Reopen asm file in case if the .err file needs to print it out
if((asmFile = fopen(argv[1], "r")) == NULL)
	die("Could not open input file. Exiting...\n");
rewind(asmFile);

//If there were no errors found, create the .obj and .sym file and write data out to them
if(strcmp(errorList->type, "Empty") == 0)
	{
		//Open symbol file
		if((symFile = fopen(symFileName, "w")) == NULL)
			die("Could not open symbol file. Exiting...\n");

		//Open object file
		if((objFile = fopen(objFileName, "w")) == NULL)
			die("Could not open object file. Exiting...\n");

		//Print the symbol table to the .sym file
		printSymbolTable(symbolTable,symFile);
	
		//Print out the assmblers memory to the .obj file
		for(i = 0; i < LC; i++)
			fprintf(objFile,"%10X\t%10X\n",i,memory[i]);
	}
//Else, there existed at least 1 error. Print out the entire .asm file and the contents of the errorList linked list to the errorFile
else
	{
		if((errFile = fopen(errFileName, "w")) == NULL)
			die("Could not open error file. Exiting...\n");

		char str[80];
		int line = 1;
		while(fgets(str, MAX_LINE_LEN, asmFile) != NULL)
			{
				fprintf(errFile, "%d\t%s",line,str);
				line++;
			}
		fprintf(errFile,"\n\n");
		printErrorList(errorList,errFile);

	}

return 0;
}

//Function to append file extensions to the given filename
char * appendExtension(char * fname, char b[]){

	int i;	
	int length = strlen(fname);
	char * newfileName = (char *) malloc(sizeof(char) * length);
	strcpy(newfileName, fname);

	for(i = 0; i < 4; i++)
		newfileName[length - i] =  b[3 - i];

	return newfileName;

}

//Function to produce an error message and kill the program
void die(char * message){
	fprintf(stderr,"%s\n", message);
	fflush(stderr);
	exit(1);
}
