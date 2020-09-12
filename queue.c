/*
N26090724 NCKUEE
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* DONE: What if malloc returned NULL? */
    if (q) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* DONE: How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (!q)
        return;
    while (q->head) {
        list_ele_t *tmp = q->head;
        q->head = q->head->next;
        free(tmp->value);
        free(tmp);
    }
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q)
        return false;
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    /* DONE: What should you do if the q is NULL? */
    if (!newh)
        return false;
    newh->value = malloc(sizeof(char) * (strlen(s) + 1)); /*add 1 for '\0'*/
    if (!newh->value) {
        free(newh);
        return false;
    }
    strncpy(newh->value, s, strlen(s) + 1);
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    q->head = newh;
    if (!q->tail)
        q->tail = q->head;
    q->size++;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* DONE: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* DONE: Remove the above comment when you are about to implement. */
    if (!q)
        return false;
    list_ele_t *newt = malloc(sizeof(list_ele_t));
    if (!newt)
        return false;
    newt->value = malloc(sizeof(char) * (strlen(s) + 1));
    if (!newt->value) {
        free(newt);
        return false;
    }
    strncpy(newt->value, s, strlen(s) + 1);
    newt->next = NULL;
    if (q->tail)
        q->tail->next = newt;
    q->tail = newt;
    q->size++;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* DONE: You need to fix up this code. */
    /* DONE: Remove the above comment when you are about to implement. */
    if (!q_size(q))
        return false;
    list_ele_t *tmp = q->head;
    q->head = q->head->next;
    if (sp) {
        size_t tmp_size =
            bufsize > strlen(tmp->value) ? strlen(tmp->value) : bufsize - 1;
        memset(sp, '\0', tmp_size + 1);
        strncpy(sp, tmp->value, tmp_size);
    }
    free(tmp->value);
    free(tmp);
    q->size--;
    if (!q_size(q))
        q->tail = NULL;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    return q ? q->size : 0;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q_size(q))
        return;
    list_ele_t *cursor = NULL;
    while (q->head) {
        list_ele_t *next = q->head->next;
        q->head->next = cursor;
        cursor = q->head;
        q->head = next;
    }
    q->head = cursor;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q_size(q) || q->head == q->tail)  // empty 0 1
        return;
    merge_sort(&q->head);
    while (q->tail->next)
        q->tail = q->tail->next;
}

void merge_sort(list_ele_t **head)
{
    if (!(*head) || !((*head)->next))
        return;
    list_ele_t *l_h = *head;
    list_ele_t *l_t = (*head)->next;
    /*split*/
    while (l_t && l_t->next) {
        l_h = l_h->next;
        l_t = l_t->next->next;
    }
    l_t = l_h->next;
    l_h->next = NULL;
    l_h = *head;
    merge_sort(&l_h);
    merge_sort(&l_t);

    list_ele_t **new_head = head;
    while (l_h && l_t) {
        if (strcmp(l_h->value, l_t->value)) {
            *new_head = l_t;
            l_t = l_t->next;
        } else {
            *new_head = l_h;
            l_h = l_h->next;
        }
        new_head = &((*new_head)->next);
    }
    *new_head = l_t ? l_t : l_h;
    // new_head = &((*new_head)->next);
}
