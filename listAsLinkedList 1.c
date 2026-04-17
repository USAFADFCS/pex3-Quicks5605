/** listAsLinkedList.c
 * ===========================================================
 * Name: 
 * Section:
 * Project: PEX 3 - RPN Calculator
 * Purpose: List ADT as linked list
 * ===========================================================
 */

#include "listAsLinkedList.h"
#include <stdio.h>
#include <stdlib.h>
  
/** linkedListInit()
 * @brief  - initializes the linked list structure
 * @return - pointer to linked list
 */
LinkedList* linkedListInit() {
    LinkedList* LL = (LinkedList*)malloc(sizeof(LinkedList));
    LL -> head = NULL;
    LL -> tail = NULL;
    LL -> numberOfItems = 0;
    return LL;
}

/** deleteLinkedList(()
 * @brief  - deletes linked list and nodes, freeing all memory used
 * @param list - a ptr to the linked list structure
 */
void deleteLinkedList(LinkedList* list) {
    Node* current = list->head;
    Node* temp = NULL;
    while(current != NULL){
        temp = current;
        free(temp);
        current = current->next;
        list->numberOfItems--;
    }
    free(current);
    free(list);
}

/** createNode()
 * @brief - allocates a Node and returns a pointer to it
 * @param type - the type of node to create
 * @param number - the number to store in the node (if applicable)
 * @param operator - the operator to store in the node (if applicable)
 * @return pointer to the allocated node or NULL if fails
 */
Node* createNode(DataType type, double number, char operator) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    //printf("malloced node\n");
    if (type == REAL_NUMBER) {
        newNode->dataType = REAL_NUMBER;
        newNode->number = number;
        newNode->operator = operator;
        newNode->next = NULL;
    }
    else {//only 2 choices
        newNode->dataType = MATH_OPERATOR;
        newNode->number = number;
        newNode->operator = operator;
        newNode->next = NULL;
    }
    return newNode;
}

/** appendElementLinkedList()
 * @brief - addes a new node to the end of the linked list
 * @param list - a ptr to the linked list structure
 * @param newNode - a ptr to a Node to append to the list
 */
void appendElementLinkedList(LinkedList* list, Node* newNode) {
    newNode -> next = NULL;
    if (list->numberOfItems == 0){
        list -> head = newNode;
        list -> tail = newNode;
    }
    else{
        list -> tail -> next = newNode;
        list -> tail = newNode;
    }
    list -> numberOfItems++;
}

/** lengthOfLinkedList()
 * @brief  - returns the size of the linked list
 * @param list - a ptr to the linked structure
 * @return - number of items in the linked list
 */
int lengthOfLinkedList(LinkedList* list) {
    return list->numberOfItems;
}

/** printLinkedList()
 * @brief  - outputs the linked list to the console
 * @param list - the linked list structure
 */
void printLinkedList(LinkedList* list) {
    Node* current = list->head;
    if (list->numberOfItems == 0){
        printf("Empty List\n");
        exit(1);
    }
    while (current != NULL){
        printf("%.3lf -> ", current->number);
        current = current->next;
    }
    printf("NULL\n");
    // //one extra to take care of final node ( i think this may not be necessary)
    // printf("%.2lf, %c\n", current->number, current->operator);
    // current = current->next;

}

/** getElementLinkedList()
 * @brief  - Retrieves node at a given position
 * @param  list - a ptr to the linked list structure
 * @param  position - index of value requested
 * @return - ptr to Node at 'position', NULL if given an invalid position
 */
Node* getElementLinkedList(LinkedList* list, int position) {
    int index = 0;
    Node* current = list->head;
    //checks valid pos
    if(position >= list->numberOfItems || position < 0){
        printf("Error, position not within list\n");
        return NULL;
    }

    while(current != NULL){ // loop through list to find position.
        if (index == position){
            return current;
        }
        index++;
        current = current->next;
    }
    return NULL; // failed to find position
}

/** deleteElementLinkedList()
 * @brief  - Deletes (i.e., frees) node at a given position.  Function will print an error message
 *           if given an invalid position.
 * @param  list - a ptr to the linked list structure
 * @param  position - index of value to delete
 */
void deleteElementLinkedList(LinkedList* list, int position){
    int index = 0;
    Node* current = list->head;
    Node* prior = NULL;

    //checks valid pos
    if(position >= list->numberOfItems || position < 0){
        printf("Error, position not within list\n");
        exit(1);
    }

    if (position == 0){//change head
        list->head = current->next;
        free(current);
    }

    else{
        while(index != position){ // loop through list to find position.
            index++;
            prior = current;
            current = current->next;
        }
        prior->next = current->next;
        free(current);
        if (position == (list->numberOfItems)-1){
            list->tail = prior;
        }
        
    }
    (list->numberOfItems)--;//subtract in all cases
}

/** insertElementLinkedList()
 * @brief  - Inserts a node at a given position.  Function should print an error message
 *           if given an invalid position.
 * @param  list - a ptr to the linked list structure
 * @param  position - index of node to add
 * @param  newNode - ptr to Node to be added
 */
void insertElementLinkedList(LinkedList* list, int position, Node* newNode) {
    Node* temp = list->head;
    Node* prior = NULL;
    int index = 0;

    //checks valid pos
    if(position > list->numberOfItems || position < 0){
        printf("Error, position not within list\n");
        exit(1);
    }

    if ( lengthOfLinkedList(list) == 0) { //empty case
        list->head = newNode;
        list->tail = newNode;
    }
    if (position == 0){ // change head on prepend
        list -> head = newNode;
    }
    else{
        while(index != position){
            prior = temp;
            temp = temp->next;
            index++;
        }
        prior->next = newNode;

    }
    newNode->next = temp; //set in all cases
    if (newNode->next == NULL){ //in case someone uses like append...
        list->tail = newNode;
    }
    list -> numberOfItems++; //increment for all
}

/** changeElementLinkedList()
 * @brief  - Replaces the node at a given position.  Function will print an error message
 *           if given an invalid position.
 * @param  list - a ptr to the linked list structure
 * @param  position - index of node to replace
 * @param  newNode - replacment Node
 */
void changeElementLinkedList(LinkedList* list, int position, Node* newNode) {
    int index = 0;
    Node* current = list->head;
    Node* prior = NULL;
    //checks valid pos
    if(position >= list->numberOfItems || position < 0){
        printf("Error, position not within list\n");
        exit(1);
    }
    while(index != position){ //find node
        prior = current;
        current = current->next;
        index++;
    }
    //replace node
    newNode->next = current->next;
    prior->next = newNode;
    free(current);
}

/** copyElement()
 * @brief  - helper function, returns a copy of a node
 * @param  nodeToClone - a ptr to the Node to be copied
 * @returns another Node with the exact same data and type; pointer set to NULL
 */
Node* copyElement(Node* nodeToClone) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->dataType = nodeToClone->dataType;
    newNode->next = nodeToClone->next;
    newNode->number = nodeToClone->number;
    newNode->operator = nodeToClone->operator;
    return newNode;
}

/** prepTestList
 * @brief  - helper function, preps a list with 5 elements
 * @returns the pointer to the list
 */
LinkedList* prepTestList(){
    LinkedList* list;
    list = linkedListInit();

    Node* testNode = createNode(REAL_NUMBER,   7.0, '\0'); // assumes there is a helper function
    Node* testNode1 = createNode(REAL_NUMBER, 14.0, '\0'); // assumes there is a helper function
    Node* testNode2 = createNode(REAL_NUMBER, 21.0, '\0'); // assumes there is a helper function
    Node* testNode3 = createNode(REAL_NUMBER, 28.0, '\0'); // assumes there is a helper function
    Node* testNode4 = createNode(REAL_NUMBER, 35.0, '\0'); // assumes there is a helper function
    appendElementLinkedList(list, testNode);  // append new node
    appendElementLinkedList(list, testNode1);  // append new node
    appendElementLinkedList(list, testNode2);  // append new node
    appendElementLinkedList(list, testNode3);  // append new node
    appendElementLinkedList(list, testNode4);  // append new node

    return list;
}
