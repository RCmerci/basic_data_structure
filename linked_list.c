#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "linked_list.h"
static struct linked_list_node *init_linked_list_node(struct linked_list_node *prev,struct linked_list_node *next,void *data){
    struct linked_list_node *p;
    if((p = malloc(sizeof(struct linked_list_node)))==NULL)return NULL;
    p->data = data;
    p->next = next;
    p->previous = prev;
    return p;
}

static int delete_linked_list_node(struct linked_list *list, struct linked_list_node *node){
    //this node is the only one 
    if(list->count == 1){
        free(node);
        list->first_node = NULL;
        return 0;
    }
    else{
        node->previous->next = node->next;
        node->next->previous = node->previous;
        if(list->first_node == node)
            list->first_node = node->next;
        free(node);
        return 0;
    }
}

static void swap_linked_list_node(struct linked_list_node *node_1, struct linked_list_node *node_2){
    void *swap;
    swap = node_1->data;
    node_1->data = node_2->data;
    node_2->data = swap;
}

static int list_partition(struct linked_list *list, int pos_s, int pos_e, void *cmp_func){
    struct linked_list_node *pivot = list->first_node, *node, *node2;
    int (*func)(void*,void*) = cmp_func;
    int i,j;
    for(i=0;i<pos_s;++i)
        pivot = pivot->next;
    node2 = pivot;
    j = random()%(pos_e-pos_s+1);
    /*
    printf("t:%d\n",j);
    */
    for(i=0;i<j;++i)
        pivot = pivot->next;
    node = list->first_node;
    for(i=0;i<pos_e;++i)
        node = node->next;
    swap_linked_list_node(pivot,node);
    pivot = node;
    node = node2;
    /*
    printf("t:%s\n",(char*)pivot->data);
    printf("t:%s\n",(char*)node->data);
    printf("t:%s\n",(char*)node2->data);
    */
    i = pos_s-1;
    for(j=pos_s;j<pos_e;++j){
        if(func(pivot->data, node2->data)){
            ++i;
            swap_linked_list_node(node2,node);
            node = node->next;
        }
        node2 = node2->next;
    }
    swap_linked_list_node(pivot,node);
    /*
    int k;
    struct linked_list_node *l = list->first_node;
    printf(":%s\n",(char*)l->data);
    for(k=0;k<pos_e-pos_s;++k){
        l = l->next;
        printf(":%s\n",(char*)l->data);
    }
    */
    return (i+1);
}

static void list_qsort_r(struct linked_list *list, void *cmp_func, int pos_s, int pos_e){
    if(pos_s>=pos_e)return;
    int pos = list_partition(list, pos_s, pos_e, cmp_func);
    list_qsort_r(list, cmp_func, pos+1, pos_e);
    list_qsort_r(list, cmp_func, pos_s, pos-1);
    
}

static void list_qsort(struct linked_list *list, void *cmp_func){
    if(list->count == 0||list->count == 1)return;
    srandom(time(NULL));
    list_qsort_r(list, cmp_func, 0, list->count-1);
}

static int list_sort_func_btos(void *data_1, void *data_2){
    return ((*(int*)data_1) >= (*(int*)data_2))?0:(-1);
}

static int list_sort_func_stob(void *data_1, void *data_2){
    return ((*(int*)data_1) <= (*(int*)data_2))?0:(-1);
}

void list_init(struct linked_list *list){
    list->count = 0;
    list->first_node = NULL;
}

int list_size(struct linked_list *list){
    return list->count;
}

void *list_first(struct linked_list *list){
    if(!list_empty(list))return NULL;
    return list->first_node->data;
}

int list_empty(struct linked_list *list){
    if(list->count == 0)return 0;
    return (-1);
}

int list_insert(struct linked_list *list, void *data){
    return list_insert_pos(list, data,0);
}

int list_insert_pos(struct linked_list *list, void *data, int pos){
    struct linked_list_node *node,*xnode;
    int i;
    xnode = list->first_node;
    if((pos >= list->count&&pos!=0)||pos < (-list->count))return (-1);
    if(!list_empty(list)){
        if((node=init_linked_list_node(NULL,NULL,data))==NULL)
            return (-1);
        node->previous = node;
        node->next = node;
    }
    else if(pos < 0){
        for(i=0;i<(-pos);++i)
            xnode = xnode->previous;
        if((node=init_linked_list_node(xnode,xnode->next,data))==NULL)
            return (-1);
        xnode->next->previous = node;
        xnode->next = node;
    }
    else{
        for(i=0;i<pos;++i)
            xnode = xnode->next;
        if((node=init_linked_list_node(xnode->previous,xnode,data))==NULL)
            return (-1);
        xnode->previous->next = node;
        xnode->previous = node;
    }
    if(pos == 0)
        list->first_node = node;
    list->count += 1;
    return 0;
}

void *list_delete_func(struct linked_list *list, void *func){
    int (*xfunc)(void *) = func;
    int i;
    struct linked_list_node *node;
    void *data;
    node = list->first_node;
    for(i=0;i<list->count;++i){
        if(!xfunc(node->data)){
            data = node->data;
            delete_linked_list_node(list, node);
            list->count -= 1;
            return data;
        }
        node = node->next;
    }
    return NULL;
}

void *list_delete_pos(struct linked_list *list, int pos){
    if(pos>=list->count||pos<(-list->count))
        return NULL;
    int i;
    void *data;
    struct linked_list_node *xnode;
    xnode = list->first_node;
    if(pos<0){
        for(i=0;i<(-pos);++i)
            xnode = xnode->previous;
        data = xnode->data;
        delete_linked_list_node(list,xnode);
        list->count -= 1;
        return data;
    }
    else{
        for(i=0;i<pos;++i)
            xnode = xnode->next;
        data = xnode->data;
        delete_linked_list_node(list,xnode);
        list->count -= 1;
        return data;
    }
}

int list_sort_func(struct linked_list *list, void *cmp_func){
    list_qsort(list, cmp_func);
    return 0;
}

int list_sort_num(struct linked_list *list, int cond){
    if(cond == STOB)
        return list_sort_func(list, list_sort_func_stob);
    else if(cond == BTOS)
        return list_sort_func(list, list_sort_func_btos);
    else 
        return (-1);
}

int list_traverse(struct linked_list *list, void *func){
    if(list->count == 0)return 0;
    struct linked_list_node *node = list->first_node;
    int i=0,j=0;
    do{
        if(!((int(*)(void*))func)(node->data)){
            ++j;
        }
        node = node->next;
        ++i;
    }while(i < list->count);
    return j;
}

int list_traverse_till(struct linked_list *list, void *func){
    if(list->count == 0)return 0;
    int (*xfunc)(void *) = func;
    struct linked_list_node *node;
    int i=0;
    node = list->first_node;
    do{
        if(xfunc(node->data)){
            return i;   
        }
        ++i;
        node = node->next;
    }while(i < list->count);
    return i;
}
/* not complete.
int list_traverse_pos(struct linked_list *list, void *func, int pos_s, int pos_e){
    
}
*/
int list_search_func(struct linked_list *list, void *func){
    int xfunc(void *data){
        return ((((int(*)(void*))func)(data))+1);
    }
    int i = list_traverse_till(list, xfunc);
    if(i<list->count)return i;
    return (-1);
}
