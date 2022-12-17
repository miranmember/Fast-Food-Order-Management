#define TRUE 1
#define FALSE 0

#include "program.h"

// A utility function to create a new linked list node. 
struct LIST* newNode(char status, int burgers, int salads, char * name) 
{ 
    struct LIST* temp = (struct LIST*)malloc(sizeof(struct LIST)); 
    temp->status = status;
    temp->burgers = burgers; 
    temp->salads = salads;
    temp->name = (char *) malloc(100);;
    strcpy(temp->name, name);
    temp->next = NULL; 
    return temp; 
} 
  
// A utility function to create an empty queue 
struct QUEUE* createQueue() 
{ 
    struct QUEUE* q = (struct QUEUE*)malloc(sizeof(struct QUEUE)); 
    q->head = q->tail = NULL; 
    return q; 
} 
  
int nameIndex(struct QUEUE * q, char * name) {
  struct LIST * temp = q->head;
  int counter = 0;
  while (temp != NULL) {
    if (!strcmp(temp->name, name)) return counter;
    temp = temp->next;
    counter++;
  }
  return -1;
}

int orderIndex(struct QUEUE * q, int burgers, int salads) {
  int counter = 0;
  for (struct LIST * temp = q->head; temp != NULL; temp = temp->next) {
    if (!inRestaurant(q, temp->name)) {
      counter++;
      continue;
    }
    if (temp->burgers <= burgers && temp->salads <= salads) 
      return counter;
    counter++;
  }
  return -1;
}

// The function to add a key k to q 
void addToList(struct QUEUE* q, char status, int burgers, int salads, char * name, int debug) 
{ 
  // Create a new LL node 
  struct LIST* temp = newNode(status, burgers, salads, name); 

  // If queue is empty, then new node is head and tail both 
  if (q->tail == NULL) { 
      q->head = q->tail = temp; 
      return; 
  } 

  // Add the new node at the end of queue and change tail 
  q->tail->next = temp; 
  q->tail = temp; 

  if (debug) {
    struct LIST * debugList = q->head;
    int counter = 0; 
    if (nameIndex(q, name) != 0) {
      while (counter < nameIndex(q, name)){
        printf("Visiting node %s with values %d and %d\n", debugList->name, debugList->burgers, debugList->salads);
        debugList = debugList->next;
        counter++;
      }
    }
  }
} 
  
// Function to remove a key from given queue q 
void deQueue(struct QUEUE* q) 
{ 
    // If queue is empty, return NULL. 
    if (q->head == NULL) 
        return; 
  
    // Store previous head and move head one node ahead 
    struct LIST* temp = q->head; 
  
    q->head = q->head->next; 
  
    // If head becomes NULL, then change tail also as NULL 
    if (q->head == NULL) 
        q->tail = NULL; 
  
    free(temp); 
} 

void resetQueue(struct QUEUE * q) {
  while(q->head != NULL) {
    free(q->head->name);
    deQueue(q);
  }
}

void deleteQueue(struct QUEUE * q) {
  resetQueue(q);
  free(q);
}

int doesNameExist(struct QUEUE * q, char * name) {
  if (nameIndex(q, name) != -1) 
    return TRUE;
  return FALSE;
}

int inRestaurant(struct QUEUE * q, char * name) {
  struct LIST * temp = q->head;
  if (!doesNameExist(q, name)) return FALSE;
  for (int i = 0; i < nameIndex(q, name); i++) 
    temp = temp->next;
  if (temp->status == 'a') 
    return TRUE;
  return FALSE;
}

int updateStatus(struct QUEUE * q, char * name) {
  struct LIST * temp = q->head;
  if (inRestaurant(q, name)) return FALSE;
  for (int i = 0; i < nameIndex(q, name); i++)
    temp = temp->next;
  temp->status = 'a';
  return TRUE;
}

void retrieveAndRemove(struct QUEUE * q, int burgers, int salads, int debug) {
  struct LIST * afterTarget = NULL,
              * beforeTarget = NULL;
  int index = orderIndex(q, burgers, salads), counter = 0;
  if (debug) {
    struct LIST * debugList = q->head;
    int counter = 0; 
    if (index != 0) {
      while (counter < index){
        printf("Visiting node %s with values %d and %d\n", debugList->name, debugList->burgers, debugList->salads);
        debugList = debugList->next;
        counter++;
      }
      printf("Visiting node %s with values %d and %d\n", debugList->name, debugList->burgers, 
      debugList->salads);
    }
  }

  for (struct LIST * currentNode = q->head; currentNode != NULL; currentNode = currentNode->next) {
    if (index == 0) {
      deQueue(q);
      return;
    }
    if (counter == index - 1) {
      beforeTarget = currentNode;
    }
    if (counter == index + 1) {
      if (currentNode->next == NULL)
        afterTarget = NULL;
      else 
        afterTarget = currentNode;
    }
    counter++;
  }
  if (afterTarget == NULL) {
    beforeTarget->next = afterTarget;
    free(afterTarget);
    q->tail = beforeTarget;
  }
  else
    beforeTarget->next = afterTarget;
}

void countOrdersAhead(struct QUEUE * q, char * name) {
  struct LIST * temp = q->head;
  for (int i = 0; i < nameIndex(q, name); i++) {
    printf(" %s: %d burgers and %d salads \n", temp->name, temp->burgers, temp->salads);
    temp = temp->next;
  }
}

int displayWaitingTime(struct QUEUE * q, char * name, int debug) {
  struct LIST * temp = q->head;
  int burgerTime = 0, saladTime = 0;
  for (int i = 0; i < nameIndex(q, name); i++) {
    burgerTime += temp->burgers;
    saladTime += temp->salads;
    if (debug) {
      printf("Visiting node %s with values %d and %d\n", temp->name, temp->burgers, temp->salads);
    }
    temp = temp->next;
  }
  return (burgerTime * 5) + (saladTime * 2);
}

void displayListInformation(struct QUEUE * q) {
  struct LIST * temp = q->head;
  while (temp != NULL) {
    printf("%s: %d burgers and %d salads, currently ", temp->name, temp->burgers, temp->salads);
    if (!inRestaurant(q, temp->name))
      printf("not ");
    printf("in the restaurant.\n");
    temp = temp->next;
  }
}