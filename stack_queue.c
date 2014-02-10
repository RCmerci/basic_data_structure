#include <stdlib.h>
#include <stdio.h>
#include "stack_queue.h"
/*===================stack===========================================*/
static struct stack_node *init_stack_node(struct stack_node *previous,void *data){
    struct stack_node *p = malloc(sizeof(struct stack_node));
    if (NULL == p)return NULL;
    else{
        p->data = data;
        p->previous = previous;
        return p;
    }
}

void stack_init(struct stack *xstack){
    xstack->top = NULL;
    xstack->count = 0;
}

int stack_empty(struct stack *xstack){
    if (!xstack->count)return 0;
    return (-1);
}

int stack_push(struct stack *xstack, void *data){
    struct stack_node *node;
    if((node = init_stack_node(xstack->top,data)) == NULL)return (-1);
    else{
        xstack->top = node;
        xstack->count += 1;
        return 0;
    }
}

void *stack_pop(struct stack *xstack){
    if(stack_empty(xstack) == 0)return NULL;
    else{
        struct stack_node *p = xstack->top;
        void *data = p->data;
        xstack->top = p->previous;
        xstack->count -= 1;
        free(p);
        return data;
    }
}
/*=================simple queue====================================*/
static struct queue_node *init_queue_node(struct queue_node *previous, void *data){
    struct queue_node *p;
    if((p = malloc(sizeof(struct queue_node)))==NULL)return NULL;
    else{
        p->data = data;
        p->next = NULL;
        p->previous = previous;
        return p;
    }
}

void queue_init(struct queue *queue){
    queue->first = NULL;
    queue->last  = NULL;
    queue->count = 0;
}

int queue_empty(struct queue *queue){
    if(queue->count == 0)return 0;
    return -1;
}

int queue_add(struct queue *queue,void *data){
    struct queue_node *node;
    if((node = init_queue_node(queue->last,data))==NULL)return (-1);
    else{
        if(!queue_empty(queue)){
            queue->first = node;
            queue->last  = node;
        }
        else{
            queue->last->next = node;
            queue->last = node;
        }
        queue->count += 1;
        return 0;
    }
}

void *queue_del(struct queue *queue){
    if(!queue_empty(queue))return NULL;
    struct queue_node *node;
    void *data;
    node = queue->first;
    queue->first = queue->first->next;
    if(queue->first != NULL)
        queue->first->previous = NULL;
    else{
        queue->last = NULL;
    }
    queue->count -= 1;
    data = node->data;
    free(node);
    return data;
}
