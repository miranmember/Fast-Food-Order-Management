#ifndef PROGRAM_H
#define PROGRAM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct LIST { 
    int burgers;
    int salads; 
    char status;
    char* name;
    struct LIST* next; 
}; 
struct QUEUE { 
    struct LIST *head, *tail; 
}; 

int getNextNWSChar();
int getPosInt();
char *getName();
void clearToEoln();
void printCommands();

void doAdd (struct QUEUE * q, int debug);
void doCallAhead(struct QUEUE * q, int debug);
void doWaiting(struct QUEUE * q);
void doRetrieve(struct QUEUE * q, int debug);
void doList(struct QUEUE * q);
void doDisplay(struct QUEUE * q);
void doEstimateTime(struct QUEUE * q, int debug);

struct LIST* newNode(char status, int burgers, int salads, char * name);
struct QUEUE* createQueue();
void addToList(struct QUEUE* q, char status, int burgers, int salads, char * name, int debug);
void deQueue(struct QUEUE* q);
void resetQueue(struct QUEUE * q);
void deleteQueue(struct QUEUE * q);
int nameIndex(struct QUEUE * q, char * name);
int orderIndex(struct QUEUE * q, int burgers, int salads);
int doesNameExist(struct QUEUE * q, char * name);
int inRestaurant(struct QUEUE * q, char * name);
int updateStatus(struct QUEUE * q, char * name);
void retrieveAndRemove(struct QUEUE * q, int burgers, int salads, int debug);
void countOrdersAhead(struct QUEUE * q, char * name);
int displayWaitingTime(struct QUEUE * q, char * name, int debug);
void displayListInformation(struct QUEUE * q);

#endif