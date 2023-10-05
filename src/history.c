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
	newItem->str = copy_str(token, token_length(token));
	newItem->id = 1;

	if (list->root == NULL){
		list->root = newItem;
		list->root->id = newItem->id ; 
	}
	else{
		Item *current = list->root;
		while(current->next != NULL){
			newItem->id++;
			current->next->id = newItem->id;
			current = current->next;
		}

		current->next = newItem;
		newItem->id++;
		current->next->id = newItem->id;
	}
	globalid = newItem->id;
}

char *get_history(List *list, int id){
	Item *current = list->root;
	while(current != NULL){
		if (current->id == id) return current->str;
		current = current->next;
	}
	return NULL;
}

void print_history(List *list){
	Item *current = list->root;
	printf(" ");
	while(current != NULL){
		printf("ID:%d ", current->id);
		printf("%s ", current->str);
		current = current->next;
	}
	printf("\n");
}

void free_history(List *list){
	Item *holder;
	Item *current = list->root;
	while(current){
		holder = current;
		current = current->next;
		free(holder);
	}
}
