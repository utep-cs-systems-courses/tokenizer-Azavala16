#include <stdlib.h>
#include <stdio.h>
#include "history.h"
#include "tokenizer.h"

List* init_history(){
	List *list = malloc(sizeof(List));
	list->root = NULL;
	return list;
}

void add_history(List *list, char *token){
	Item *newItem = (Item*) malloc(sizeof(Item)); //pointer of items
	newItem->str = token;
	newItem->id = 1;

	if (list->root == NULL){
		list->root = newItem;
		list->root->id = newItem->id ; //edited
	}
	else{
		Item *current = list->root;
		while(current->next != NULL){

			//if (countids == current->next->id) sentenceid++;
			newItem->id++;
			current->next->id = newItem->id;
			current = current->next;
		}

		current->next = newItem;
		newItem->id++;
		globalid = current->next->id = newItem->id;
	}
}

char *get_history(List *list, int id){
	Item *current = list->root;
	while(current != NULL){
		if (current->id == id) return current->str;
		current = current->next;
	}
	return NULL;
}

int newline;
void print_history(List *list){
	int i=0;
	Item *current = list->root;
	printf(" ");
	while(current != NULL){
		//len = token_length(current->str);
		if(newline){ printf("\n%d.", i+1); newline=0;}
		//printf("ID:%d ", current->id);
		printf("%s ", current->str);
		current = current->next;
	}
	printf("\n");
	printf("\n");
}

void free_history(List *list){
	Item *holder;
	Item *cell = list->root;
	while(cell){
		holder = cell;
		cell = cell->next;
		free(holder);
	}
}
