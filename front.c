///////////////////////////////////////////////////////////////////////////////
//                   Bradley Chippi && Trent Killinger
// Title:            front.c
// Semester:         Winter 2017
// Class:	     	 CS 451
// Assignment:       HW1
//
//////////////////////////////////////////////////////////////////////////////

/* a lexical analyzer system for simple arithmetic expressions */
#include <stdio.h>
#include <ctype.h>

/* Global declarations */
/* Variables */
int charClass;
char lexeme [100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE *in_fp, *fopen();

/* Function declarations */
void addChar();
void getChar();
void getNonBlank();
int lex();

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define FOR_CODE 30
#define IF_CODE 31
#define ELSE_CODE 32
#define WHILE_CODE 33
#define DO_CODE 34
#define INT_CODE 35
#define FLOAT_CODE 36
#define SWITCH_CODE 37

const char *INPUT = "front.c";

/******************************************************/
/* main driver */
main() {
	/* Open the input data file and process its contents */
	if ((in_fp = fopen(INPUT, "r")) == NULL)
		printf("ERROR - cannot open %s\n", INPUT);
	else {
		getChar();
		do {
			lex();
		} while (nextToken != EOF);
	}
}
/*****************************************************/
/* lookup - a function to lookup operators and parentheses and return the token */
int lookup(char ch) {
	switch (ch) {
		case '(':
			addChar();
			nextToken = LEFT_PAREN;
			break;
		
		case ')':
			addChar();
			nextToken = RIGHT_PAREN;
			break;
		
		case '+':
			addChar();
			nextToken = ADD_OP;
			break;
		
		case '-':
			addChar();
			nextToken = SUB_OP;
			break;
		
		case '*':
			addChar();
			nextToken = MULT_OP;
			break;
		
		case '/':
			addChar();
			nextToken = DIV_OP;
			break;
		
		default:
			addChar();
			nextToken = EOF;
			break;
	}
	return nextToken;
}

/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar() {
	if (lexLen <= 98) {
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = 0;
	}
	else
		printf("Error - lexeme is too long \n");
}
/*****************************************************/
/* getChar - a function to get the next character of input and determine its character class */
void getChar() {
	if ((nextChar = getc(in_fp)) != EOF) {
		if (isalpha(nextChar))
			charClass = LETTER;
		else if (isdigit(nextChar))
			charClass = DIGIT;
		else charClass = UNKNOWN;
	}
	else
		charClass = EOF;
}
/*****************************************************/
/* getNonBlank - a function to call getChar until it returns a non-whitespace character */
void getNonBlank() {
	while (isspace(nextChar))
	getChar();
}

/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic expressions */
int lex() {
	lexLen = 0;
	getNonBlank();
	switch (charClass) {

		/* Parse identifiers */
		case LETTER:
			addChar();
			getChar();
			while (charClass == LETTER || charClass == DIGIT) {
				addChar();
				if(lexeme[0] == 'f' && lexeme[1] == 'o' && lexeme[2] == 'r'){
				    nextToken = FOR_CODE;
				    break;
				}else if(lexeme[0] == 'i' && lexeme[1] == 'f'){
				    nextToken = IF_CODE;
				    break;
				}else if(lexeme[0] == 'e' && lexeme[1] == 'l' && lexeme[2] == 's' && lexeme[3] == 'e'){
				    nextToken = ELSE_CODE;
				    break;
				}else if(lexeme[0] == 'w' && lexeme[1] == 'h' && lexeme[2] == 'i' && lexeme[3] == 'l' && lexeme[4] == 'e'){
					nextToken = WHILE_CODE;
					break;
				}else if(lexeme[0] == 'd' && lexeme[1] == 'o' ){
					nextToken = DO_CODE;
					break;
				}else if(lexeme[0] == 'i' && lexeme[1] == 'n' && lexeme[2] == 't'){
					nextToken = INT_CODE;
					break;
				}else if(lexeme[0] == 'f' && lexeme[1] == 'l' && lexeme[2] == 'o' && lexeme[3] == 'a' && lexeme[4] == 't'){
					nextToken = FLOAT_CODE;
					break;
				}else if(lexeme[0] == 's' && lexeme[1] == 'w' && lexeme[2] == 'i' && lexeme[3] == 't' && lexeme[4] == 'c' && lexeme[5] == 'h'){
					nextToken = SWITCH_CODE;
					break;
				}
				getChar();
			}
			nextToken = IDENT;
			break;
		
		/* Parse integer literals */
		case DIGIT:
			addChar();
			getChar();
			while (charClass == DIGIT) {
				addChar();
				getChar();
			}
			nextToken = INT_LIT;
			break;
		
		/* Parentheses and operators */
		case UNKNOWN:
			lookup(nextChar);
			getChar();
			break;
		
		/* EOF */
		case EOF:
			nextToken = EOF;
			lexeme[0] = 'E';
			lexeme[1] = 'O';
			lexeme[2] = 'F';
			lexeme[3] = 0;
			break;
	
	} /* End of switch */
	
	printf("Next token is: %d, Next lexeme is %s\n",
	nextToken, lexeme);
	return nextToken;
} /* End of function lex */
