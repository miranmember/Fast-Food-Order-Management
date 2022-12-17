#include "program.h"

void doAdd(struct QUEUE * q, int debug) {
  /*get number of burgers ordered from input */
  int NumBurgers = getPosInt();
  if (NumBurgers < 0) {
    printf("Error: Add command requires an integer value of at least 0\n");
    printf("Add command format: a<# burgers><# salads><name>\n");
    return;
  }

  /*get number of salads ordered from input */
  int NumSalads = getPosInt();
  if (NumSalads < 0) {
    printf("Error: Add command requires an integer value of at least 0\n");
    printf("Add command format: a<# burgers><# salads><name>\n");
    return;
  }

  /*get group name from input */
  char * name = getName();
  if (NULL == name) {
    printf("Error: Add command requires a name to be given\n");
    printf("Add command format: a<# burgers><# salads><name>\n");
    return;
  }

  if (doesNameExist(q, name)) {
    printf("An order with the given name already exists. Try another name.\n");
  } else {
    printf("Adding In-restaurant order for \"%s\": %d burgers and %d salads\n", name, NumBurgers, NumSalads);
    addToList(q, 'a', NumBurgers, NumSalads, name, debug);
  }
  free(name);
}

void doCallAhead(struct QUEUE * q, int debug) {
  /*get number of burgers ordered from input */
  int NumBurgers = getPosInt();
  if (NumBurgers < 0) {
    printf("Error: Call-ahead command requires an integer value of at least 0\n");
    printf("Call-ahead command format: c<# burgers><# salads><name>\n");
    return;
  }

  /*get number of salads ordered from input */
  int NumSalads = getPosInt();
  if (NumSalads < 0) {
    printf("Error: Call-ahead command requires an integer value of at least 0\n");
    printf("Call-ahead command format: c<# burgers><# salads><name>\n");
    return;
  }

  /*get group name from input */
  char * name = getName();
  if (NULL == name) {
    printf("Error: Call-ahead command requires a name to be given\n");
    printf("Call-ahead command format: c<# burgers><# salads><name>\n");
    return;
  }

  if (doesNameExist(q, name)) {
    printf("An order with the given name already exists. Try another name.\n");
  } else {
    printf("Adding Call-ahead order for \"%s\": %d burgers and %d salads\n", name, NumBurgers, NumSalads);

    addToList(q, 'c', NumBurgers, NumSalads, name, debug);
  }
  free(name);
}

void doWaiting(struct QUEUE * q) {
  /*get order name from input */
  char * name = getName();
  if (NULL == name) {
    printf("Error: Waiting command requires a name to be given\n");
    printf("Wait command format: w<name>\n");
    return;
  }
  if (!doesNameExist(q, name)) {
    printf("No match found for the given name. Try again!\n");
  } else {
    printf("Call-ahead order \"%s\" is now waiting in the restaurant\n", name);

    updateStatus(q, name);
  }
  free(name);
}

void doRetrieve(struct QUEUE * q, int debug) {
  /*get info of prepared food ready on the counter from input */
  int PreparedBurgers = getPosInt();
  if (PreparedBurgers < 0) {
    printf("Error: Retrieve command requires an integer value of at least 0\n");
    printf("Retrieve command format: r<# burgers><# salads>\n");

    return;
  }

  int PreparedSalads = getPosInt();
  if (PreparedSalads < 0) {
    printf("Error: Retrieve command requires an integer value of at least 0\n");
    printf("Retrieve command format: r<# burgers><# salads>\n");
    return;
  }

  clearToEoln();
  printf("Retrieve and remove the first group that can pick up the order of %d burgers and %d salads\n", PreparedBurgers, PreparedSalads);
  if (orderIndex(q, PreparedBurgers, PreparedSalads) == -1)
    printf("No matching orders found\n");
  else
    retrieveAndRemove(q, PreparedBurgers, PreparedSalads, debug);
}

void doList(struct QUEUE * q) {
  /*get order name from input */
  char * name = getName();
  if (NULL == name) {
    printf("Error: List command requires a name to be given\n");
    printf("List command format: l<name>\n");
    return;
  }

  if (doesNameExist(q, name)) {
    printf("Order for \"%s\" is behind the following orders\n", name);
    countOrdersAhead(q, name);
  } else {
    printf("No match found for the given name. Try again!");
  }
  free(name);
}

void doDisplay(struct QUEUE * q) {
  clearToEoln();
  printf("Display information about all orders\n");

  displayListInformation(q);
}

void doEstimateTime(struct QUEUE * q, int debug) {
  /*get order name from input */

  char * name = getName();
  if (NULL == name) {
    printf("Error: Time command requires a name to be given\n");
    printf("Time command format: t<name>\n");
    return;
  }

  if (!doesNameExist(q, name)) {
    printf("No match found for the given name. Try again!\n");
  } else {
    printf(" Estimated wait time for %s is %d minutes.\n", name, displayWaitingTime(q, name, debug));
  }
  free(name);
}