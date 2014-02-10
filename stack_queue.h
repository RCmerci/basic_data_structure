#ifndef __STACK_QUEUE__

#define __STACK_QUEUE__
struct stack_node{
    void *data;
    struct stack_node *previous;
};

struct stack{
      struct stack_node *top;
      int count;
};
//Initialize a stack.
void stack_init(struct stack *xstack);
//return 0 if stack is empty,rather -1.
int stack_empty(struct stack *xstack);
//push a new data at the top of stack.
//return 0 on sucess,-1 on failure.
int stack_push(struct stack *xstack, void *data);
//pop a data at the top of stack.
//return a pointer to data on sucess,NULL on failure.
void *stack_pop(struct stack *xstack);
/*==================simple queue(not deque)==========================*/
struct queue_node{
    void *data;
    struct queue_node *next;
    struct queue_node *previous;
};

struct queue{
    struct queue_node *first;
    struct queue_node *last;
    int count;
};
//Initialize a queue.
void queue_init(struct queue *queue);
//if queue is empty or not.
//return 0 if empty,else -1.
int queue_empty(struct queue *queue);
//add a data at the tail.
//return 0 on sucess,-1 on failure.
int queue_add(struct queue *queue, void *data);
//delete a data at the first of queue.
//return a pointer to data on sucess,NULL on failure.
void *queue_del(struct queue *queue);


#endif
