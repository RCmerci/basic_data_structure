#ifndef __LINKED_LIST__
#define __LINKED_LIST__

#define __MAX(a,b) (((a)>(b))?(a):(b))
#define __MIN(a,b) (((a)<(b))?(a):(b))

#define BTOS 0
#define STOB 1
/*actually,i wanna circular,doubly linked list without a sentinel*/
struct linked_list_node{
    void *data;
    struct linked_list_node *next;
    struct linked_list_node *previous;
};

struct linked_list{
    struct linked_list_node *first_node;
    int count;
};

//Initialize a linked list.
void list_init(struct linked_list *list);
//return list->count;
int list_size(struct linked_list *list);
//return the first data,NULL when list is empty
void *list_first(struct linked_list *list);
//check if a list is empty or not.
//return 0 if empty,otherwise -1.
int list_empty(struct linked_list *list);
//insert a data at the first node of list.
//return 0 on success,-1 on failure.
int list_insert(struct linked_list *list, void *data);
//insert data at pos of list.
//return 0 on success,-1 on failure.pos -->from -count to 0 to count-1.
int list_insert_pos(struct linked_list *list, void *data,int pos);
//delete a node from a list specified by a compare function(compare the data,on 2nd argument).
//return a pointer to data,NULL on failure.
//hint for 'func':return 0 when the case is what you want.
//func should like this: int func(void *);
void *list_delete_func(struct linked_list *list, void *func);
//delete a node by pos.
void *list_delete_pos(struct linked_list *list, int pos);
//sort the list by a function spported by "cmp_func".
//return 0 on success,-1 on failure.
//ps for cmp_func:return 0 when the case is what you want.
//cmp_func should like this: int cmp_func(void *,void *);
int list_sort_func(struct linked_list *list, void *cmp_func);
//sort a list,if cond==STOB,the node's data turn out to be small-to-big,otherwise  BTOS.
//return 0 on success,-1 on failure.(suppose the data is a number)
int list_sort_num(struct linked_list *list, int cond);
//traverse over the list,return the number of times of func success.
int list_traverse(struct linked_list *list ,void *func);
//traverse a list,and apply func on each node.
//return -1 on failure,other numbers mean how many times 'func' success.
//hint for 'func':func should like "int func(void *)";
//func return 0 for success,-1 on failure.
//return value is 0 to count-1.same way as other function (e.g. 'list_insert_pos)
int list_traverse_till(struct linked_list *list, void *func);
//same as the one before,except positions at start(end).{not complete}
int list_traverse_pos(struct linked_list *list, void *func, int pos_s, int pos_e);
//search data by a function.
//return pos.-1 on failure.(pos:0---count)
//func: int func(void*)
//func:return 0,if success,else -1.
int list_search_func(struct linked_list *list, void *func);
#endif
