#include <stdio.h>
#include <stdlib.h>
#include "history.h"
#include "tokenizer.h"

int space_char(char c){
	int yes = ( (c == ' ' || c == '\t') && c != '\0') ? 1: 0; //c is space, tab and not yet '\0'
    	    	return yes;
}

int non_space_char(char c){
	int no = ( (!(c == ' ' || c == '\t')) && c != '\0') ? 1 : 0; //c is not space, tab, and not yet '\0'
    	return no;
}

char *token_start(char *str){

	int indx = 0;
    	while(space_char(str[indx]) ) //get rid of extra spaces, tabs in fron of input
		indx++;

	return str + indx; //return pointer to first char in token
}

char *token_terminator(char *str){

	int indx = 0;
    	while(non_space_char(str[indx])) ++indx;

	return str + indx; //return pointer to last char in token
}

int count_tokens(char *str){
	int tokenCount =0;
	char *holder = str;
	while(*holder){ 
		if(non_space_char(*holder) ){
			tokenCount++;
		}
		holder = token_start(token_terminator(holder));
	}
	return tokenCount;
}

char *copy_str(char *inStr, short len){
	char *inStrCopy = malloc( (len+1) * sizeof(char)), loopCount = '0';//'0'
	int i;
	for(i =0; i< len; i++){
		//if (inStr[i] == '\n') { inStr[i] = '\0'; newline =1;}//change to '\0' to make sure history doesn't get new line
		inStrCopy[i] = inStr[i];
		loopCount++;
	}
		//newline=0;
	inStrCopy[i] = '\0';
	//printf("Wordlength for word %s: %d\n", inStrCopy, len);
	return inStrCopy;
}


char **tokenize(char *str){
	int i, length, wordCount = count_tokens(str);
	char **tokens = malloc((wordCount+1) * sizeof(char *) );
	char *p = str;
	
	i=0;	
	//printf("Words in sentence %d: %d\n", i+1,  wordCount);
	for( ; i < wordCount; i++){
		p = token_start(p);
		length = token_terminator(p) - p;
		tokens[i] = copy_str(p, length);
		if (!tokenizeHistory) add_history(history, tokens[i]);//if user doesnt want to tokenize
		p = token_terminator(p);
	}
	tokens[i] = '\0';
	return tokens;
}

void print_tokens(char **tokens){
	for(int i=0; tokens[i]; i++) printf("Token[%d]: %s\n\n", i+1, tokens[i]);
}

void free_tokens(char **tokens){
	int i=0;
	while(tokens[i]){
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

void finalized_options(char *str){
	if (str[1] == '\n') str[1] = '\0';
}

