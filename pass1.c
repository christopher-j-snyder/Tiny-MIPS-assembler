/*	Christopher Snyder
	ICSI 402 Program 4
	CS146375
				*/
#include "header.h"

int assemblerPass1(struct symbolNode * symbolTable[], struct opcodeNode * opcodeTable[], struct errorNode * errorList, FILE * asmFile, int memory[]){

int i;
char str[80];
int lineCount = 0;
int LC = 0;
char comment = '#';
int workingIndex;
char ** line = malloc(sizeof(char *)*15);
char ** splitLine(char * line, const char * d);
int dataFlag = 0;
char data[6] = ".data";
int memoryLocation = 0;

for(i = 0; i < 15; i++);
	line[i] = malloc(sizeof(char)*20);

//Read the assembly file line by line
while(fgets(str, MAX_LINE_LEN, asmFile) != NULL)
{
	char * token;
	char * label;
	char * label2 = malloc(sizeof(char)*30);
	char * next = malloc(sizeof(char)*30);
	char * next2 = malloc(sizeof(char)*30);
	workingIndex = 0;
	lineCount++;
	
	//If first char is a comment,line is empty, or the .text directive skip this loop
	if(str[0] == '#') continue;
	if(is_empty(str) == 1) continue;
	next2 = trimspace(str);
	if(strcmp(next2, ".text") == 0) continue;

	//Remove inline comments
	token = strtok(str, "#");	
	
	//Split the remainder of the line into an indexed char array
	line = splitLine(token, " ");
	i = 0;

	//Print the lines to console to see what we are working with
	/*
	while(line[i] != NULL)
	{
		printf("%s\t",line[i]);
		i++;
	}
	i = 0;
	*/

//If this flag is 0 we have not reached the .data directive, so we can do stuff
if(dataFlag == 0)
	{

	//If the line contains a symbol/label, look to insert it
	if(line[0][strlen(line[0]) - 1] == ':')
		{
			//Strip the whitespace and : from the label
			label = strtok(line[0], ":");
			label2 = trimspace(label);

			//If the symbol already exists, throw an error to our errorlist
			if(checkSymbolTable(symbolTable, label2) == 1)
				insertErrorNode(errorList, ERR_1, label2, lineCount);

			//Else, insert it into the symbol table
			else
				insertSymbol(symbolTable, label2, LC);
			
			workingIndex++;
		}

	//Increment LC if the line contains an instruction
	if(checkOpcodeTable(opcodeTable, line[workingIndex]) == 1)
		LC++;
		

//Check for the .data directive
next = trimspace(line[0]);
if(strcmp(data, next) == 0)
	dataFlag = 1;

}//end of dflag being 0

//if there exists a .data directive the following flag will be 1 and we do stuff
if(dataFlag == 1)
	{

	//If the line contains a symbol/label (they all should), look to insert it
	if(line[0][strlen(line[0]) - 1] == ':')
		{
			
			//Strip the : and whitespace from the label
			label = strtok(line[0], ":");
			label2 = trimspace(label);

			//If the symbol already exists, throw an error
			if(checkSymbolTable(symbolTable, label2) == 1)
			{
				//puts("Error, symbol already exists");
				insertErrorNode(errorList, ERR_1, label2, lineCount);

			}
			//Else, insert it
			else
			{
				insertSymbol(symbolTable, label2, LC);
			}
			workingIndex++;
			
			//If the directive after the label is a .word
			if(strcmp(line[workingIndex], ".word") == 0)
			{
				workingIndex++;
				//printf("leftovers: %s", line[workingIndex]); 
				int initval,numwords; 
				sscanf(line[workingIndex],"%d:%d", &initval, &numwords);
				//printf("num of words is %d",numwords);
				for(i=0;i<numwords;i++)
				{
					memory[LC] = initval;
					LC++;
				}

			}

			//If the directive after the label is a .resw
			if(strcmp(line[workingIndex], ".resw") == 0)
			{
				workingIndex++;
				//printf("leftovers: %s", line[workingIndex]); 
				int resNumWords; 
				sscanf(line[workingIndex],"%d", &resNumWords);
				
				for(i=0;i<resNumWords;i++)
				{
					memory[LC] = 0;
					LC++;
				}
				
			}

		}


	}

}//end fgets
//printSymbolTable(symbolTable);

return LC;
}

//Function to tokenize by spaces each line of the file into a character array 
char ** splitLine(char * line, const char * d)
{
	char ** charArray = malloc(sizeof(char *)*10);
	int i = 0;

	charArray[0] = strtok(line, d);
	//printf("char array zero is %s |",charArray[0]);
	i++;

	while((charArray[i] = strtok(NULL, d))!= NULL)
		i++;

	return charArray;
}

//Function to trim whitespace from a string
char *trimspace(char *string)
{
  char *end;

  // Trim leading space
  while(isspace(*string)) string++;

  if(*string == 0)  // All spaces?
    return string;

  // Trim trailing space
  end = string + strlen(string) - 1;
  while(end > string && isspace(*end)) end--;

  // Write new null terminator
  *(end+1) = 0;

  return string;
}
