/*	Christopher Snyder
	ICSI 402 Program 4
	CS146375
				*/
#include "header.h"

void assemblerPass2(struct symbolNode * symbolTable[], struct opcodeNode * opcodeTable[], struct errorNode * errorList, FILE * asmFile, int memory[], int memoryLocation){
memoryLocation = 0;
int i;
int workingIndex;
int lineCount = 0;
char str[80];
int op = 0;
char ** line = malloc(sizeof(char *)*15);
for(i = 0; i < 15; i++);
	line[i] = malloc(sizeof(char)*20);
int dataFlag = 0;
char data[6] = ".data";

char ** splitLine(char * line, const char * d);
int is_empty(const char *s);

//Read the assembly file line by line
while(fgets(str, MAX_LINE_LEN, asmFile) != NULL)
{

	char * token;
	char * label;
	char * next = malloc(sizeof(char)*30);
	char * next2 = malloc(sizeof(char)*30);
	workingIndex = 0;
	lineCount++;
	
	//If first char is a comment, skip this loop
	if(str[0] == '#') continue;
	
	//If line is empty or .text directive skip this loop
	if(is_empty(str) == 1) continue;
	next = trimspace(str);
	if(strcmp(next, ".text") == 0) continue;

	
	if(strcmp(data, next) == 0)
	dataFlag = 1;
	
	token = strtok(str, "#");
	
	//Split the remainder of the line into an indexed char array
	line = splitLine(token, " ");
	i = 0;

	//Make sure we are not in the .data section since it doesn't contain any opcodes
	next2 = trimspace(line[0]);
	if(strcmp(data, next2) == 0)
		dataFlag = 1;

if(dataFlag == 0)
{
	//If the line contains a label skip it since we are only interested in instructions
	if(line[0][strlen(line[0]) - 1] == ':')
		workingIndex++;

/*
	while(line[i] != NULL)
	{
		printf("%s\t",line[i]);
		i++;
	}
*/
	//If the opcode exists, check it's format type and call the proper assembly instruction
	if(checkOpcodeTable(opcodeTable, line[workingIndex]) == 1)
		{

			//If opcode format is R type call that function
			if(strcmp(getOpcodeFormat(opcodeTable, line[workingIndex]), "R") == 0)
			{
				//puts("R type");
				op = getOpcode(opcodeTable, line[workingIndex]);
				workingIndex++;
				memory[memoryLocation] = rTypeAssembler(op, line[workingIndex]);
				memoryLocation++;
			}

			//Else if I type call function
			else if(strcmp(getOpcodeFormat(opcodeTable, line[workingIndex]), "I") == 0)
			{
				//puts("I type");
				op = getOpcode(opcodeTable, line[workingIndex]);
				workingIndex++;
				memory[memoryLocation] = iTypeAssembler(op, line[workingIndex]);
				memoryLocation++;
			}

			//Else if J type call that function
			else if(strcmp(getOpcodeFormat(opcodeTable, line[workingIndex]), "J") == 0)
			{
				//puts("J type");
				op = getOpcode(opcodeTable, line[workingIndex]);
				workingIndex++;
				memory[memoryLocation] = jTypeAssembler(op, line[workingIndex], errorList, symbolTable, lineCount);
				memoryLocation++;
			}
		}
	//Else if the opcode does not exist in our table, throw an error
	else
		insertErrorNode(errorList, ERR_2, " ", lineCount);


}	

}//end fgets

}//end pass2

//Function to check if a line is all whitespace
int is_empty(const char *s) {
  while (*s != '\0') {
    if (!isspace(*s))
      return 0;
    s++;
  }
  return 1;
}
