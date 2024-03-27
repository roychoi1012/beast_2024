#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*
 * @brief       a node structure
 * @struct      node_t
 */
typedef struct node {
    char data;
    struct node* rlink;
    struct node* llink;
} node_t;

/*
* @brief      pointer types to a node structure
*/
typedef node_t* nodeptr_t;

/*
 * @brief     execute L-command to move backward direction (i.e., move to the left by one node) 
*/
void  
L_ftn(const nodeptr_t head, nodeptr_t* cur) 
{
    if (head != *cur) {
        *cur = (*cur)->llink;
    }

    return;
}

/*
 * @brief      execute D-command to move forward direction (i.e., move to the right by one node)
 */
void 
D_ftn(const nodeptr_t tail, nodeptr_t* cur)
{
    if (tail != *cur) {
        *cur = (*cur)->rlink;
    }

    return;
}

/*
 * @brief    execute B-command to remove a node at the left of "cursor" and 
 *           to locate the cursor at the left node of the removed node
 */
void 
B_ftn(const nodeptr_t head, nodeptr_t* cur)
{
    node_t* left_node = (head == *cur) ? head : (*cur)->llink;

    if (head != left_node) {
        (*cur)->llink = left_node->llink;
        left_node->llink->rlink = *cur;
        /// free the target node
        if (0 != left_node) {
            free(left_node);
            left_node = 0;
        }
    }

    return;
}

/*
 * @brief      execute P-command to insert a node with "data" at the left of "cursor"
 */
void
P_ftn(const nodeptr_t head, nodeptr_t* cur, const char data) 
{
    uint8_t cursor_at_head = 0;
    node_t* new_node = (node_t*)calloc(1, sizeof(node_t));

    if (0 == new_node) return;

    /// the case that the cursor is located at the head node
    if (head == *cur) {
        *cur = (*cur)->rlink;
        cursor_at_head = 1;
    }

    /// insertion
    new_node->data = data;
    new_node->llink = (*cur)->llink;
    new_node->rlink = *cur;
    (*cur)->llink->rlink = new_node;
    (*cur)->llink = new_node;

    /// rollback the cursor in that case 
    if (1 == cursor_at_head) {
        (*cur) = (*cur)->llink->llink;
    }

    return;
}

/*
 * @brief      print the list
 */
void
print(const nodeptr_t head, const nodeptr_t tail) 
{
    node_t* cursor = head->rlink;

    while (tail != cursor) {
        printf("%c", cursor->data);
        cursor = cursor->rlink;
    }
    printf("\n");

    return;
}

/*
 * @brief       deallocation
 */
void
free_list(nodeptr_t* list) 
{
    node_t* head = *list;

    while (1) {
        if (0 != head) {
            node_t* del_node = head;

            head = head->rlink;
            free(del_node); 
            del_node = 0;
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
    /// sentinel nodes
    node_t* headptr = (node_t*)calloc(1, sizeof(node_t));
    node_t* tailptr = (node_t*)calloc(1, sizeof(node_t));

    if (0 == headptr || 0 == tailptr) return -1;

    headptr->data = '!';
    tailptr->data = '?';
    headptr->rlink = headptr->llink = 0;
    tailptr->rlink = tailptr->llink = 0;

    cur = headptr;

    while ((t = getchar()) != '\n') {
        node_t* new_node = (node_t*)calloc(1, sizeof(node_t));
        if (0 == new_node) return -1;

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
            L_ftn(headptr, &cur);
        }
        /// D command
        else if (0 == strcmp(function, "D")) {
            D_ftn(tailptr, &cur);
        }

        /// B command
        else if (0 == strcmp(function, "B")) {
            B_ftn(headptr, &cur);
        }

        /// P command
        else if (!strcmp(function, "P")) {
            scanf(" %c", &data);
            P_ftn(headptr, &cur, data);
        }
    }

    print(headptr, tailptr);
    free_list(&headptr);

    return 0;
}
