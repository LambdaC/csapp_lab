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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if(q == NULL)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->length = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    list_ele_t *ele;
    /* How about freeing the list elements and the strings? */
    if(q == NULL)
        return;
    while(q->head)
    {
        ele = q->head;
        q->head = ele->next;
        free(ele->value);
        free(ele);
    }
    /* Free queue structure */
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
    /* What should you do if the q is NULL? */
    if(q == NULL)
        return false;
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
        return false;
    /* Don't forget to allocate space for the string and copy it */
    char *value = malloc(sizeof(char) * (strlen(s)+1));
    if(value == NULL)
    {
        free(newh);
        return false;
    }
    strcpy(value, s);
    newh->value = value;
    /* What if either call to malloc returns NULL? */
    if(q->tail == NULL)     /* This is the first ele */
        q->tail = newh;
    if(q->head != NULL)
        q->head->prev = newh;
    newh->next = q->head;
    newh->prev = NULL;
    q->head = newh;
    q->length++;
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
    if(q == NULL)
        return false;
    newt = malloc(sizeof(list_ele_t));
    if(newt == NULL)
        return false;
    char *value = malloc(sizeof(char) * (strlen(s)+1));
    if(value == NULL)
    {
        free(newt);
        return false;
    }
    strcpy(value, s);
    newt->value = value;
    newt->next = NULL;
    newt->prev = q->tail;
    if(q->head == NULL)     /* This is the first element */
        q->head = newt;
    if(q->tail != NULL)
        q->tail->next = newt;
    q->tail = newt;
    q->length++;
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
    if(q == NULL || q->head == NULL)
        return false;
    list_ele_t *ele = q->head;
    q->head = q->head->next;
    if(q->head !=NULL)
        q->head->prev = NULL;
    if(sp != NULL)
    {
        strncpy(sp, ele->value, bufsize);
        sp[bufsize-1] = '\0';
    }
    free(ele->value);
    free(ele);
    q->length--;
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
    return q==NULL?0:q->length;
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
    if(q == NULL || q->head == NULL)
        return;
    list_ele_t *tmp_head, *ele, *tmp_next;
    tmp_head = q->head;
    q->head = q->tail;
    q->tail = tmp_head;
    while(tmp_head)
    {
        ele = tmp_head;
        tmp_head = tmp_head->next;
        tmp_next = ele->prev;
        ele->prev = ele->next;
        ele->next = tmp_next;
    }
}

