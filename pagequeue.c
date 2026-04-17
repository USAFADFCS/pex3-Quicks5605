/** pagequeue.c
 * ===========================================================
 * Name: _______________________, __ ___ 2026
 * Section: CS483 / ____
 * Project: PEX3 - Page Replacement Simulator
 * Purpose: Implementation of the PageQueue ADT — a doubly-linked
 *          list for LRU page replacement.
 *          Head = LRU (eviction end), Tail = MRU end.
 * =========================================================== */
#include <stdio.h>
#include <stdlib.h>

#include "pagequeue.h"

/**
 * @brief Create and initialize a page queue with a given capacity
 */
PageQueue *pqInit(unsigned int maxSize) {
    // TODO: malloc a PageQueue, set head and tail to NULL,
    //       size to 0, maxSize to maxSize, and return the pointer
    PageQueue* PQ = (PageQueue*)malloc(sizeof(PageQueue));
    PQ -> head = NULL;
    PQ -> tail = NULL;
    PQ -> size = 0;
    PQ->maxSize = maxSize;
    return PQ;
}

/**
 * @brief Access a page in the queue (simulates a memory reference)
 */
long pqAccess(PageQueue *pq, unsigned long pageNum) {
    // TODO: Search the queue for pageNum (suggest searching tail->head
    //       so you naturally count depth from the MRU end).
    //
    // HIT path (page found at depth d):
    //   - Remove the node from its current position and re-insert
    //     it at the tail (most recently used).
    //   - Return d.
    //
    // MISS path (page not found):
    //   - Allocate a new node for pageNum and insert it at the tail.
    //   - If size now exceeds maxSize, evict the head node (free it).
    //   - Return -1.

    long depth = 0;
    PqNode *current = pq->tail;

    while (current != NULL) {
        if (current->pageNum == pageNum) {
            // HIT path
            if (current != pq->tail) {
                if (current->prev != NULL)
                    current->prev->next = current->next;
                else
                    pq->head = current->next;  // current was head (Null prev)

                //if (current->next != NULL)
                current->next->prev = current->prev;

                // Append to tail
                current->prev = pq->tail;
                current->next = NULL;
                pq->tail->next = current;
                pq->tail = current;
            }
            return depth;
        }

        depth++;
        current = current->prev;
    }

    // MISS path
    PqNode *newNode = (PqNode *)malloc(sizeof(PqNode));
    newNode->pageNum = pageNum;
    newNode->next = NULL;
    newNode->prev = pq->tail;

    if (pq->tail != NULL) //check not empty list
        pq->tail->next = newNode;
    else 
        //empty list case, must add to head too
        pq->head = newNode;  

    pq->tail = newNode;
    pq->size++;

    // Decapitations haha
    if (pq->size > pq->maxSize) { // size greater than max
        PqNode *leaving = pq->head;
        pq->head = leaving->next;
        pq->head->prev = NULL;
        free(leaving);
        pq->size--;
    }

    return -1;
}

/**
 * @brief Free all nodes in the queue and reset it to empty
 */
void pqFree(PageQueue *pq) {
    // TODO: Walk from head to tail, free each node, then free
    //       the PageQueue struct itself.
    PqNode* current = pq->head;
    PqNode* temp = NULL;
    while(current != NULL){
        temp = current;
        current = current->next;
        free(temp);
        pq->size--;
    }
    //free(current);
    free(pq);
}

/**
 * @brief Print queue contents to stderr for debugging
 */
void pqPrint(PageQueue *pq) {
    // TODO (optional): Print each page number from head to tail,
    //                  marking which is head and which is tail.
    //                  Useful for desk-checking small traces.
    printf("(Head)\n");

    PqNode* current = pq -> head;
    if (pq->size == 0){
        printf("Empty Queue\n");
        exit(1);
    }
    while (current != NULL){
        printf("%ld -> ", current->pageNum);
        current = current->next;
    }
    printf("(Tail)\n");

}
