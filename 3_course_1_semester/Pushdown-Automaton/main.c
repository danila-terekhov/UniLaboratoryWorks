#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum{
	WRONG = -1,
	PUSH = 0,
	POP = 1,
	FINAL = 2
};

#define ALPHABET 5
#define STACK_ALPHABET 3
#define MAX 100

FILE *fd;
char string[MAX];
int top, stack[MAX]={'$'};

void push(int x){
	if (top != MAX)
		stack[++top] = x;
}
int pop(void){
	return (top+1)?stack[top--]:-1;
}
void clear(void){
	while (top+1)
		pop();
	push('$');
}

int D[STACK_ALPHABET][ALPHABET] =
{    //  {, [, }, ],\n
	{0, 0, 1,-1,-1}, // {
	{0, 0,-1, 1,-1}, // [
	{0,-1,-1,-1, 2}, // $
};

int class(int c){
	switch (c){
		case '{': return 0;
		case '[': return 1;
		case '$':
		case '}': return 2;
		case ']': return 3;
		case '\n': return 4;
		default : return -1;
	}
}
int lexan(void){
	int ch,st,i,cc,sc;
	i = st = 0;
	while ( (ch = string[i++]) != '\0'){ // {{ }} {} \n \0
		cc = class(ch);
		sc = class(stack[top]);
		if ( cc >= 0 ){
			st = D[sc][cc];
			switch (st){
			case PUSH:{
				push(ch);
				break;}
			case POP:{
				pop();
				break;}
			case WRONG:
				return WRONG;
			case FINAL:
				return FINAL;
			}
		}
	}
	return FINAL; // never
}

int main(void){

	if (!(fd = fopen( "input.txt", "r"))){
		perror("File");
		exit(EXIT_FAILURE);
	}
	while (fgets(string, MAX, fd))
		printf( "Bracket sequence: %s\tResult: %s\n\n",
			string,(lexan()==FINAL)?"accept":"reject" );
	exit(EXIT_SUCCESS);
}
