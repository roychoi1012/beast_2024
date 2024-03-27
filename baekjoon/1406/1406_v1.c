#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*
@brief      a node structure
*/
typedef struct node {
    char data;
    struct node* rlink;
    struct node* llink;
} node_t;

/*
@brief      pointer types to a node structure
*/
typedef node_t* nodeptr_t;

/*
@brief     execute L-command to move backward direction (i.e., move to the left by one node) 
*/
void  
L_ftn(nodeptr_t* cur) 
{
    if ('!' != (*cur)->llink->data) {
        *cur = (*cur)->llink;
    }

    return;
}

/*
@brief      execute D-command to move forward direction (i.e., move to the right by one node)
*/
void 
D_ftn(nodeptr_t* cur)
{
    if ('@' != (*cur)->rlink->data) {
        *cur = (*cur)->rlink;
    }

    return;
}

/*
@brief      execute B-command to remove a node at the left of "cursor" and 
            to locate the cursor at the left node of the removed node
*/
void 
B_ftn(nodeptr_t* cur)
{
    node_t* del_node = (*cur)->llink;

    if ('!' != (*cur)->llink->data) {
        (*cur)->llink = del_node->llink;
        del_node->llink->rlink = *cur;
        del_node->llink = del_node->rlink = 0;
    }

    return;
}

/*
@brief      execure P-command to insert a node with "data" at the left of "cursor"
*/
void
P_ftn(nodeptr_t* cur, const char data) 
{
    node_t* new_node = (node_t*)calloc(1, sizeof(node_t));

    if (0 == new_node) return;

    new_node->data = data;
    new_node->llink = (*cur)->llink;
    new_node->rlink = *cur;
    (*cur)->llink->rlink = new_node;
    (*cur)->llink = new_node;

    return;
}

/*
@brief      print the list
*/
void
print(const nodeptr_t list) 
{
    node_t* cursor = list->rlink;

    printf("[");
    while ('@' != cursor->data) {
        printf("%c ", cursor->data);
        cursor = cursor->rlink;
    }
    printf("]\n");

    return;
}

void
free_list(nodeptr_t* list) 
{
    node_t* head = *list;

    while (1) {
        if (0 != head) {
            node_t* del_node = head;
            head = head->rlink;
            free(del_node); del_node = 0;
        }
        else
            break;
    }
    
    return;
}

int main(int argc, char** argv) 
{
    const size_t max_ftn = 10;

    char t = 0;
    node_t* cur = 0;
    node_t* headptr = (node_t*)calloc(1, sizeof(node_t));
    node_t* tailptr = (node_t*)calloc(1, sizeof(node_t));

    if (0 == headptr || 0 == tailptr) return -1;

    headptr->data = '!';
    tailptr->data = '@';
    headptr->rlink = headptr->llink = 0;
    tailptr->rlink = tailptr->llink = 0;

    cur = headptr;

    while ((t = getchar()) != '\n') {
        node_t* new_node = (node_t*)calloc(1, sizeof(node_t));
        if (NULL == new_node) return -1;

        new_node->data = t;
        new_node->llink = cur;
        new_node->rlink = 0;
        cur->rlink = new_node;
        cur = new_node;         /// locate the cursor at the rightmost non-null node
    }
    cur->rlink = tailptr;
    tailptr->llink = cur;
    cur = tailptr;

    int32_t num = 0;            /// the number of commands
    scanf("%d", &num);

    char function[max_ftn] = {0};
    char data = 0;

    while (num--) {
        scanf("%s", function);

        /// L command
        if (0 == strcmp(function, "L")) {
            L_ftn(&cur);
        }
        /// D command
        else if (0 == strcmp(function, "D")) {
            D_ftn(&cur);
        }

        /// B command
        else if (0 == strcmp(function, "B")) {
            B_ftn(&cur);
        }

        /// P command
        else if (!strcmp(function, "P")) {
            scanf(" %c", &data);
            P_ftn(&cur, data);
        }
    }

    print(headptr);
    free_list(&headptr);

    return 0;
}
