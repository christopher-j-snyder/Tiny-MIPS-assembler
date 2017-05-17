/*	Christopher Snyder
	ICSI 402 Program 4
	CS146375
				*/
#include "header.h"

//Function to create and return an error node
struct errorNode * createErrorNode(char * err, char * name, int line){

	struct errorNode * e = malloc(sizeof(struct errorNode));
	strcpy(e->type, err);
	strcpy(e->name, name);
	e->line = line;
	e->next = NULL;
	return e;
}

//Function to insert an error node into the linked list. If the head of the list is labeled as "Empty" the list is empty and the node is the head. Otherwise, insert the node at the end of the linked list. 
void insertErrorNode(struct errorNode * list, char * err,char * name, int line){
	struct errorNode * e = (struct errorNode *) createErrorNode(err, name, line);
	struct errorNode * temp;
	struct errorNode * temp2;	
	temp = list;

	if(strcmp(list->type, "Empty")==0)
		{
		strcpy(list->type, err);
		list->line = line;
		strcpy(list->name, name);
		}

	else if(temp->next == NULL)
			temp->next = e;

	else 
	{
		while(temp->next != NULL)
		{
			temp2 = temp->next;
			temp = temp2;		
		}

			temp->next = e;
	}	
}

//Function to print the error list in order to the specified file, in the assemblers case it would be the "error" .err file
void printErrorList(struct errorNode * list, FILE * f){
	struct errorNode * temp;
	struct errorNode * temp2;
	temp = list;

	while(temp->next != NULL)
	{
		fprintf(f,"ERROR: Line %d: %s\t|\t%s\n",temp->line, temp->type, temp->name);
		temp2 = temp->next;
		temp = temp2;
	}
	
	fprintf(f,"ERROR: Line %d: %s\t|\t%s\n",temp->line, temp->type, temp->name);

}
