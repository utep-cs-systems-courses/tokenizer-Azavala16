#include <stdlib.h>
#include <stdio.h>
#include "history.h"
#include "tokenizer.h"

List *history;
int tokenizeHistory; //tokenizedHist is a boolean to avoid adding repeated history

#define MAXCHARS 100
char **tokens;
int globalid;//keep track of current history id

int user_options(char *str){
	if ((str[0] == 'e' || str[0] == 'E') && str[1] == '\0') return 0;
	else if ((str[0] == 'h' || str[0] == 'H') && str[1] == '\0'){
		printf("To see overal history type o, to see specific history type ! followed by a number. to return to main menu press m.\n$-");
		fgets(str, MAXCHARS, stdin);
		
		while(str[0] != 'm'){
			switch(str[0]){
				case 'o':
				case 'O':
					printf("---You chose overall history---\n");
					if (!history->root){
						printf("List is empty, please enter some input\n$-");
						fgets(str, MAXCHARS, stdin);
						free_tokens(tokens);
					}
					else print_history(history);
					break;
				case '!':
					if (!history->root){
						printf("List is empty, please enter some input\n$-");
						fgets(str, MAXCHARS, stdin);
						free_tokens(tokens);	
					}
					else{
						tokenizeHistory = 1;//user wants to tokenize
						printf("Enter a number for specific history:\n");
						printf("Current history id: %d\n$-", globalid);
						fgets(str,MAXCHARS, stdin);
						while(atoi(str) <= 0 || atoi(str) > globalid){
							printf("Entered history id %s not found. please enter a valid history id:\n$-", str);
							fgets(str,MAXCHARS, stdin);
						
						}
						printf("---Tokenizing string at specific history place: %d---.\n", atoi(str));
						char *specificHist = get_history(history, atoi(str));
						tokens = tokenize(specificHist);
						print_tokens(tokens);
						free_tokens(tokens);
						tokenizeHistory = 0;//reset to zero so tokenized history doesnt get added to history again
					}
					break;
				default:
					printf("Please enter a valid input. ");
					break;
			}
			printf("To see overall history type o, to see specific history type !, To returm to the main menu press m\n$-");
			fgets(str, MAXCHARS, stdin);
		}
		return 2;
	}
	else return 1;
}


int main(){
	char input[MAXCHARS], *ptr, **tokens;
	int menuOption;
	history = init_history();

	printf("Welcome! please enter some input. Enter e to exit or h to see history.\n");
	while(1){
		printf("$-");
		fgets(input, MAXCHARS, stdin);
		ptr = input;
		ptr = token_start(ptr);
		finalized_options(ptr);

		menuOption = user_options(ptr);
		switch(menuOption){
			case 0:
				printf("Goodbye\n");
				free_history(history);
				return 0;
				break;
			case 1:
				tokens = tokenize(ptr);
				printf("\n---Input succesfully added to history---\n");
				print_tokens(tokens);
				break;
			case 2:
				printf("Welcome! please enter some input. Enter e to exit or h to see history\n");
			default:
				break;
		}
	}
	return 0;
}
