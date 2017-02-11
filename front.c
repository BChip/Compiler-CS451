/*
 Bradley Chippi && Trent Killinger
 Title:				front.c
 Semester:			Winter 2017
 Class:				CS 451
 Assignment:		HW1
*/

/* front.c - a lexical analyzer system for simple arithmetic expressions */
#include <stdio.h>
#include <ctype.h>

/* Global declarations */
/* Variables */
int charClass;
char lexeme[100];
char currentChar;
int lexLen;
int currentToken;
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
#define COMMENT 27

/******************************************************/
/* main driver */
main() {
	/* Open the input data file and process its contents */
	char* filename;
	scanf("", &filename);
	if ((in_fp = fopen("front.c", "r")) == NULL)
		printf("ERROR - cannot open  file.\n");
	else {
		getChar();
		do {
			lex();
		} while (currentToken != EOF);
	}
	printf("Press [Enter] key to continue.\n");
	while (getchar() != '\n');
}
/*****************************************************/
/* lookup - a function to lookup operators and parentheses and return the token */
int lookup(char ch) {
switch (ch) {
	case '(':
		currentToken = LEFT_PAREN;
		break;
	
	case ')':
		currentToken = RIGHT_PAREN;
		break;
	
	case '+':
		currentToken = ADD_OP;
		break;
	
	case '-':
		currentToken = SUB_OP;
		break;
	
	case '*':
		currentToken = MULT_OP;
		break;
	
	case '/':
		currentToken = DIV_OP;
		break;
	
	default:
		currentToken = EOF;
		break;
}
return currentToken;
}

/*****************************************************/
/* addChar - a function to add currentChar to lexeme */
void addChar() {
	if (lexLen <= 98) {
		lexeme[lexLen++] = currentChar;
		lexeme[lexLen] = 0;
	}
	else
		printf("Error - lexeme is too long \n");
}
/*****************************************************/
/* getChar - a function to get the next character of input and determine its character class */
void getChar() {
	if ((currentChar = getc(in_fp)) != EOF) {
		if (isalpha(currentChar))
			charClass = LETTER;
		else if (isdigit(currentChar))
			charClass = DIGIT;
		else charClass = UNKNOWN;
	}
	else
		charClass = EOF;
}
/*****************************************************/
/* getNonBlank - a function to call getChar until it returns a non-whitespace character */
void getNonBlank() {
	while (isspace(currentChar))
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
				getChar();
			}
			currentToken = IDENT;
			break;
		
		/* Parse integer literals */
		case DIGIT:
			addChar();
			getChar();
			while (charClass == DIGIT) {
				addChar();
				getChar();
			}
			currentToken = INT_LIT;
			break;
		
		/* Parentheses and operators */
		case UNKNOWN:
			if (lookup(currentChar) == DIV_OP) {
				addChar();
				getChar();
				if (lookup(currentChar) == MULT_OP) {
					do {
						addChar();
						getChar();
					} while (lexeme[lexLen - 2] != '*' && lexeme[lexLen - 1] != '/');
					currentToken = COMMENT;
				}
				else if (lookup(currentChar) == DIV_OP) {
					while (currentChar != '\n') {
						addChar();
						getChar();
					}
					currentToken = COMMENT;
				}
			}
			else {
				addChar();
				getChar();
			}
			break;
		
		/* EOF */
		case EOF:
			currentToken = EOF;
			lexeme[0] = 'E';
			lexeme[1] = 'O';
			lexeme[2] = 'F';
			lexeme[3] = 0;
			break;
	
	} /* End of switch */
	
	printf("Next Token is: %d, Next lexeme is %s\n",
	currentToken, lexeme);
	return currentToken;
} /* End of function lex */
