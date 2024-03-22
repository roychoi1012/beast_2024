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

typedef node* dllptr_t;

//void
//insert_tail(dllptr_t* L, char* data)
//{
//		cursor = L;
//	// calloc => create a node (llink, data,rlink)
//	if (0 == L) {
//
//	}
//	else {
//		while (0 != cursor->rlink)
//			cursor = cursor->rlink;
//		// conect
//	}
//}

int main() {
	dllptr_t* L = NULL;

	node* cur = (node*)malloc(sizeof(node));
	cur->data = NULL;
	cur->rlink = cur->llink = NULL;

	// create node until input text is '\n'
	char t;
	int32_t len = 0;
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
		//fflush(stdin);
		scanf("%s", function);

		// L
		if (!strcmp(function, "L")) {
			if (cur->llink != NULL) {
				cur = cur->llink;
			}
			//printf("cursor node is : %c\n", cur->data);
		}

		// D
		else if (!strcmp(function, "D")) {
			if (cur->rlink != NULL) {
				cur = cur->rlink;
			}
			//printf("cursor node is : %c\n", cur->data);
		}

		// B
		else if (!strcmp(function, "B")) {
			if (cur->llink != NULL) {
				if (cur->rlink == NULL) {
					cur = cur->llink;
					cur->rlink = NULL;
				}
				else {
					cur->llink->rlink = cur->rlink;
					cur->rlink->llink = cur->llink;
					cur = cur->llink;
				}
			}
			//printf("now cursor in on : %c\n", cur->data);
		}


		// P
		else if (!strcmp(function, "P")) {
			scanf(" %c", &new_);

			node* add = (node*)malloc(sizeof(node));
			add->data = new_;
			//printf("data of add is : %c\n", add->data);

			if (cur->rlink == NULL) {
				cur->rlink = add;
				add->llink = cur;
				add->rlink = NULL;
				cur = cur->rlink;
			}
			else if (cur->llink == NULL) {
				add->llink = NULL;
				add->rlink = cur;
				cur->llink = add;
				cur = cur->llink;
			}
			else {
				add->rlink = cur->rlink;
				add->llink = cur;
				cur->rlink->llink = add;
				cur->rlink = add;
				cur = cur->rlink;

			}

			//printf("current cursor is on : %c\n", cur->data);
		}
		//fflush(stdin);

	}
	
	//printf("let's print\n");

	while (cur->llink != NULL) {
		cur = cur->llink;
	}

	//printf("current cursor is on : %c\n", cur->data);

	while(cur->rlink != NULL){
		printf("%c", cur->data);
		cur = cur->rlink;
	}
	printf("%c", cur->data);


	return 0;
}
