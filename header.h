/*	Christopher Snyder
	ICSI 402 Program 4
	CS146375
				*/

#define MAX_SYMBOL_LEN 10
#define MAX_INST_LEN 10
#define MAX_TABLE_LEN 35
#define MAX_LINE_LEN 80
#define ERR_0 "undefinedSymbol"
#define ERR_1 "multiplyDefinedSymbol"
#define ERR_2 "illegalOpcode"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct symbolNode{
	char symbol[MAX_SYMBOL_LEN];
	int LC;
	struct symbolNode * next;
};

struct opcodeNode{
	char instruction[MAX_INST_LEN];
	char format[1];
	int opcode;
	int numOperands;
	struct opcodeNode * next;
};

enum errorType{
	undefinedSymbol,
	multiplyDefinedSymbol,
	illegalOpcode
};
typedef enum errorType errorType;

struct errorNode{
	char type[30];
	char name[50];
	int line;
	struct errorNode * next;
};


//Function prototypes
char * appendExtension(char * fname, char b[]);
void die(char * message);
int  hash (char *s,  int T);
char *trimspace(char *string);

//Opcode function prototypes
struct opcodeNode * createOpcodeNode(char * instr, char * format, int opcode, int numOperands);
void insertOpcode(struct opcodeNode * table[], char * instr, char * format, int opcode, int numOperands);
void buildOpcodeTable(struct opcodeNode * table[]);
int getNumOperands(struct opcodeNode * table[], char * inst);
int checkOpcodeTable(struct opcodeNode * table[], char * inst);
char * getOpcodeFormat(struct opcodeNode * table[], char * inst);
int getOpcode(struct opcodeNode * table[], char * inst);

//Symbol function prototypes
struct symbolNode * createSymbolNode(char * symbol, int LC);
void insertSymbol(struct symbolNode * table[], char * symbol, int LC);
void buildSymbolTable(struct symbolNode * table[]);
int checkSymbolTable(struct symbolNode * table[], char * symbol);
void printSymbolTable(struct symbolNode * table[], FILE * f);
int getSymbolLC(struct symbolNode * table[], char * symbol);

