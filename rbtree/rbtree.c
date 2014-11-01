//红黑树实现(熄灯了无聊写写)
#include <stdio.h>

#define RED 0
#define BLK 1
struct Node {
    char color;
    struct Node * l;
    struct Node * r;
    struct Node * p;
    int v;
};
struct TREE {
    struct Node * root;
};
typedef struct TREE TREE;
typedef struct Node Node;
Node * NIL;
void init(TREE * tree);
void insert(TREE * tree, int value);
void BlanceIt(TREE * tree, Node * z);
void printTree(TREE * tree);
void printNodes(Node * rnode);
void rotateR(TREE * t, Node * z);
void rotateL(TREE * t, Node * z);
int main(){
    TREE tree;
    init(&tree);
    printTree(&tree);
    printf("\n");
    insert(&tree, 23);
    printTree(&tree);
    printf("\n");
    insert(&tree, 53);
    printTree(&tree);
    printf("\n");
    insert(&tree, 11);
    printTree(&tree);
    printf("\n");
    insert(&tree, 21);
    printTree(&tree);
    printf("\n");
}
void init(TREE * tree){
    NIL = (Node*)malloc(sizeof(Node));
    NIL->color = BLK;
    NIL->l = NULL;
    NIL->r = NULL;
    NIL->v = 0;
    NIL->p = NULL;
    tree->root = NIL;
}
void insert(TREE * tree,int value){
    Node * x = tree->root;
    Node * y;
    Node * z = (Node*)malloc(sizeof(Node));
    z->color = RED;
    z->l = NIL;
    z->r = NIL;
    z->v = value;
    if(x==NIL){
        z->p = x;
        tree->root = z;
        tree->root->color = BLK;
        return;
    }
    while(x!=NIL){
        if(x->v > z->v){
            y = x;
            x = x->l;
        }
        else{
            y = x;
            x = x->r;
        }
    }
    if(y->v > z->v){
        y->l = z;
    }
    else{
        y->r = z;
    }
    z->p = y;
    InsertBlance(tree, z);
}
void rotateR(TREE * t, Node * z){
    z->l->p = z->p;
    if(z->p == NIL){
        t->root = z->l->p;
    }
    z->p = z->l;
    z->l = z->l->r;
    if(z->l->r != NIL){
        z->l->r->p = z;
    }
    z->l->r = z;
}
void rotateL(TREE * t, Node * z){
    z->r->p = z->p;
    if(z->p == NIL){
        t->root = z->r->p;
    }
    z->p = z->r;
    z->r = z->r->l;
    if(z->r->l != NIL){
        z->r->l->p = z;
    }
    z->r->l = z;
}
void InsertBlance(TREE * tree, Node * z){
    while(z->p->color == RED){
//        printf("v:%d,clr:%d\n", z->p->v, z->p->color);
        if(z->p->p->l == z->p){
            if(z->p->p->r->color == RED){
                z->p->p->color = RED;
                z->p->p->r->color = BLK;
                z->p->color = BLK;
            }
            else{
                if(z->p->r == z){
                    z = z->p;
                    rotateL(tree, z);
                }
                rotateR(tree, z->p->p);
                z->p->color = BLK;
                z->p->r->color = RED;
            }
        }
        else{
            if(z->p->p->l->color == RED){
                z->p->p->color = RED;
                z->p->p->l->color = BLK;
                z->p->color = BLK;
            }
            else{
                if(z->p->l == z){
                    z = z->p;
                    rotateR(tree, z);
                }
                rotateL(tree, z->p->p);
                z->p->color = BLK;
                z->p->l->color = RED;
            }
        }
    }
    tree->root->color = BLK;
//    printf("%d, %d\n", tree->root->v, tree->root->color);
}
//--------------------printf whole tree for test
void printTree(TREE * tree){
    Node * x = tree->root;
    if(x == NIL){
        printf("NIL ");
        return;
    }
    printNodes(x->l);
    printf("%d ", x->v);
    printNodes(x->r);
    return;
}
void printNodes(Node * rnode){
    if(rnode==NIL){
        printf("NIL ");
        return;
    }
    printNodes(rnode->l);
    printf("%d ", rnode->v);
    printNodes(rnode->r);
    return;
}
