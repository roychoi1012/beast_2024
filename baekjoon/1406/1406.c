#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct node {
    char data;
    struct node* rlink;
    struct node* llink;
}node;

//typedef node* dllptr_t;


node*  L(node** cur) 
{
    if ((*cur)->llink != NULL) {
        *cur = (*cur)->llink;
    }
}

node* D(node** cur)
{
    if ((*cur)->rlink != NULL) {
        *cur = (*cur)->rlink;
    }
}

node* B(node** cur)
{
    if ((*cur)->llink != NULL) {
        if ((*cur)->rlink == NULL) {
            *cur = (*cur)->llink;
            (*cur)->rlink = NULL;
        }
        else {
            (*cur)->llink->rlink = (*cur)->rlink;
            (*cur)->rlink->llink = (*cur)->llink;
            (*cur) = (*cur)->llink;
        }
    }
}

node* P(node** cur, const char new_) 
{
    node* add = (node*)malloc(sizeof(node));
    add->data = new_;
    add->llink = add->rlink = NULL;
    //printf("data of add is : %c\n", add->data);

    if ((*cur)->rlink == NULL) {
        (*cur)->rlink = add;
        add->llink = *cur;
        add->rlink = NULL;
        *cur = (*cur)->rlink;
    }
    else if (*cur == NULL) {
        add->llink = NULL;
        add->rlink = *cur;
        (*cur)->llink = add;
        *cur = (*cur)->llink;
    }
    else {
        add->rlink = (*cur)->rlink;
        add->llink = *cur;
        (*cur)->rlink->llink = add;
        (*cur)->rlink = add;
        *cur = (*cur)->rlink;

    }
}

int main() 
{
    //dllptr_t* ptr = NULL;

    node* cur = (node*)malloc(sizeof(node));
    cur->data = '!';
    cur->rlink = cur->llink = NULL;

    char t;
    while ((t = getchar()) != '\n') {
        node* newnode = (node*)malloc(sizeof(node));
        newnode->data = t;

        newnode->llink = cur;
        newnode->rlink = NULL;
        cur->rlink = newnode;
        cur = newnode;
    }


    int32_t num;
    scanf("%d", &num);

    char function[10];
    char new_;
    while (num--) {
        scanf("%s", function);

        // L
        if (!strcmp(function, "L")) {
            L(&cur);
        }

        // D
        else if (!strcmp(function, "D")) {
            D(&cur);
        }

        // B
        else if (!strcmp(function, "B")) {
            B(&cur);
        }

        // P
        else if (!strcmp(function, "P")) {
            scanf(" %c", &new_);
            P(&cur, new_);
        }
    }


    while (cur->llink == NULL) {
        cur = cur->llink;
    }
    cur = cur->rlink;


    while (cur != NULL) {
        printf("%c", cur->data);
        cur = cur->rlink;
    }

    return 0;
}
