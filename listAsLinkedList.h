/** listAsLinkedList.h
 * ===========================================================
 * Name: 
 * Section: 
 * Project: 
 * Purpose: 
 * ===========================================================
 */

#ifndef LISTASLINKEDLIST_H
#define LISTASLINKEDLIST_H

#include <stdbool.h>
#define MAX_STR_LEN 15
// define node type enum
typedef enum { REAL_NUMBER, MATH_OPERATOR } DataType;

// define a node of the linked list
typedef struct Node_struct {
    double number;
    char operator;
    DataType dataType;
    struct Node_struct* next;  // next node or NULL
} Node;

// Define the type (meta-data) that manages the linked list of nodes
typedef struct LinkedList_struct {
    Node* head;
    Node* tail;
    int numberOfItems;
} LinkedList;


// Functions that manipulate a linked list

/** linkedListInit()
 * @brief  - initializes the linked list structure
 * @return - pointer to linked list
 */
LinkedList* linkedListInit();

/** deleteLinkedList()
 * @brief  - deletes linked list and nodes, freeing all memory used
 * @param list - a ptr to the linked list structure
 */
void deleteLinkedList(LinkedList* list);

/** createNode()
 * @brief - allocates a Node and returns a pointer to it
 * @param type - the type of node to create
 * @param number - the number to store in the node (if applicable)
 * @param operator - the operator to store in the node (if applicable)
 * @return pointer to the allocated node or NULL if fails
 */
Node* createNode(DataType type, double number, char operator);

/** appendElementLinkedList()
 * @brief - addes a new node to the end of the linked list
 * @param list - a ptr to the linked list structure
 * @param newNode - a ptr to a Node to append to the list
 */
void appendElementLinkedList(LinkedList* list, Node* newNode);

/** lengthOfLinkedList()
 * @brief  - returns the size of the linked list
 * @param list - a ptr to the linked structure
 * @return - number of items in the linked list
 */
int lengthOfLinkedList(LinkedList* list);

/** printLinkedList()
 * @brief  - outputs the linked list to the console
 * @param list - the linked list structure
 */
void printLinkedList(LinkedList* list);

/** getElementLinkedList()
 * @brief  - Retrieves node at a given position
 * @param  list - a ptr to the linked list structure
 * @param  position - index of value requested
 * @return - ptr to Node at 'position', NULL if given an invalid position
 */
Node* getElementLinkedList(LinkedList* list, int position);

/** deleteElementLinkedList()
 * @brief  - Deletes (i.e., frees) node at a given position.  Function will print an error message
 *           if given an invalid position.
 * @param  list - a ptr to the linked list structure
 * @param  position - index of value to delete
 */
void deleteElementLinkedList(LinkedList* list, int position);

/** insertElementLinkedList()
 * @brief  - Inserts a node at a given position.  Function should print an error message
 *           if given an invalid position.
 * @param  list - a ptr to the linked list structure
 * @param  position - index of node to add
 * @param  newNode - ptr to Node to be added
 */
void insertElementLinkedList(LinkedList* list, int position, Node* newNode);

/** changeElementLinkedList()
 * @brief  - Replaces the node at a given position.  Function will print an error message
 *           if given an invalid position.
 * @param  list - a ptr to the linked list structure
 * @param  position - index of node to replace
 * @param  newNode - replacment Node
 */
void changeElementLinkedList(LinkedList* list, int position, Node* newNode);

/** copyElement()
 * @brief  - helper function, returns a copy of a node
 * @param  nodeToClone - a ptr to the Node to be copied
 * @returns another Node with the exact same data and type; pointer set to NULL
 */
Node* copyElement(Node* nodeToClone);

/** prepTestList
 * @brief  - helper function, preps a list with 5 elements
 * @returns the pointer to the list
 */
LinkedList* prepTestList();

#endif  // LISTASLINKEDLIST_H
