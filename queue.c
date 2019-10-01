/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
   Create empty queue.
   Return NULL if could not allocate space.
   */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q == NULL)
        return;
    list_ele_t *temp = NULL;

    while (q->head != NULL) {
        temp = q->head;
        q->head = temp->next;
        free(temp->value);
        free(temp);
    }
    free(q);
}

/*
   Attempt to insert element at head of queue.
   Return true if successful.
   Return false if q is NULL or could not allocate space.
   Argument s points to the string to be stored.
   The function must explicitly allocate space and copy the string into it.
   */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;

    if (q == NULL || s == NULL)
        return false;
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
        return false;
    char *value = malloc(strlen(s) * sizeof(char) + 1);
    if (value == NULL) {
        free(newh);
        return false;
    }
    strcpy(value, s);
    // Insert the value into newh
    newh->value = value;
    if (q->size == 0)
        q->tail = newh;
    newh->next = q->head;
    q->head = newh;
    q->size++;
    return true;
}


/*
   Attempt to insert element at tail of queue.
   Return true if successful.
   Return false if q is NULL or could not allocate space.
   Argument s points to the string to be stored.
   The function must explicitly allocate space and copy the string into it.
   */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    list_ele_t *newt;
    if (q == NULL || s == NULL)
        return false;
    newt = malloc(sizeof(list_ele_t));
    if (newt == NULL)
        return false;
    char *value = malloc(strlen(s) * sizeof(char) + 1);
    if (value == NULL) {
        free(newt);
        return false;
    }
    strcpy(value, s);
    newt->value = value;

    newt->next = NULL;
    if (q->size != 0)
        q->tail->next = newt;
    else
        q->head = newt;
    q->tail = newt;

    q->size++;

    return true;
}

/*
   Attempt to remove element from head of queue.
   Return true if successful.
   Return false if queue is NULL or empty.
   If sp is non-NULL and an element is removed, copy the removed string to *sp
   (up to a maximum of bufsize-1 characters, plus a null terminator.)
   The space used by the list element and the string should be freed.
   */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (q == NULL || sp == NULL)
        return false;
    if (q->size == 0)
        return false;

    // sp = malloc(bufsize * sizeof(char));
    if (sp != NULL && bufsize > 0) {
        strncpy(sp, q->head->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    list_ele_t *temp;
    temp = q->head;
    q->head = temp->next;
    free(temp->value);
    free(temp);
    q->size--;
    return true;
}

/*
   Return number of elements in queue.
   Return 0 if q is NULL or empty
   */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL)
        return 0;
    return q->size;
}

/*
   Reverse elements in queue
   No effect if q is NULL or empty
   This function should not allocate or free any list elements
   (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
   It should rearrange the existing ones.
   */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (q == NULL)
        return;
    if (q->size == 0)
        return;
    list_ele_t *temp1 = NULL;
    list_ele_t *temp2 = q->head;
    list_ele_t *temp3 = q->head->next;

    while (temp3 != NULL) {
        temp3 = temp2->next;
        temp2->next = temp1;
        temp1 = temp2;
        temp2 = temp3;
    }

    temp1 = q->head;
    q->head = q->tail;
    q->tail = temp1;
}
