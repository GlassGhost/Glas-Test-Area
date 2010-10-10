/**********************************License(s)***********************************
Copyright 2010 Roy Pfund.                                   All rights reserved.
Use of this source code is governed by a BSD-style License(the "License");  that
can be found in the LICENSE file.  You may obtain another copy of the License at
    http://github.com/GlassGhost/Glas-Test-Area/raw/master/LICENSE.txt
*************************************Inputs*************************************
The grammar for the language accepted by the calculator
program:
		END						 END is end-of-input
		expr_list END
expr_list:
		expression PRINT			 PRINT is semicolon
		expression PRINT expr_list
expression:
		expression + term
		expression - term
		term
term:
		term / primary
		term * primary
		primary
primary:
		NUMBER
		NAME
		NAME = expression
		- primary
		(expression)
*********************************Pre-Conditions*********************************
none
******************************PROGRAM DESCRIPTION*******************************
A calculator from pages 107-175 of The C++ Programming Language 3rd Ed.; Bjarne
Stroustrup

compile with: any ISO/IEC-14882 or C++2003 compliant compiler
*********************************Post-Conditions********************************
none
*************************************Output*************************************
The evaluation of the expressions you give it
***********************************Revisions************************************
(10-11-2009)-0.1-Got it working!
(10-10-2009)-0.01-File created
*********************************System Headers********************************/
#include <iostream>
#include <string>
#include <map>
#include <cctype>
using namespace std;
/********************************Local Headers*********************************/
typedef unsigned short UINT16; typedef short	INT16;
typedef unsigned	   UINT32; typedef int		INT32; typedef float  FLOAT32;
typedef unsigned long  UINT64; typedef long int INT64; typedef double FLOAT64;
/************************************Macros************************************/
/**********************************Variables***********************************/
enum Token_value{
	NAME, NUMBER, END,
	PLUS='+', MINUS='-', MUL='*', DIV='/',
	PRINT=';', ASSIGN='=', LP='(',	RP=')'
};
Token_value curr_tok = PRINT;
double number_value;
string string_value;
map <string, double> table;
int no_of_errors;
/*****************************Feature Test Switches****************************/
/*hopefully someday I will be able to define this with 1*/
#define _POSIX_SOURCE 0
kill_arg_bool = 1;
/*****************************File scope variables*****************************/
/******************************External variables******************************/
/*****************************Structures and Unions****************************/
/**********************************Functions***********************************/
double expr(bool get);
double error(const string& s);
double prim(bool get);
double term(bool get);
Token_value get_token();
/******************************External Functions******************************/

/***************************Signal catching functions**************************/

int main(int argc, char *argv[]){/*MAIN logic**********************************/
	table["pi"] = 3.1415926535897932385; // insert predefined names
	table["e"] = 2.7182818284590452354;
	printf("Enter a mathematical expression (e.g. \"2 + 2\"), or Type \"exit\" to exit:\n");
	while (cin) {
		get_token();
		if (curr_tok == END) break;
		if (curr_tok == PRINT) continue;
		cout << expr(false) <<'\n';
	}
	/*system("pause");/*keeps Microsoft command prompt from going bananas*/
	return no_of_errors;
}/**********************************End MAIN***********************************/

FLOAT64 expr(bool get){
/*Input(s)		:nothing
PreCondition(s) :none
Description		:add and subtract
PostCondition(s):none
Output(s)		:nothing
*/	FLOAT64 left=term(get);
	for(;;) //"forever"
		switch (curr_tok) {
			case PLUS:
				left += term(true);
				break;
			case MINUS:
				left -= term(true);
				break;
			default:
				return left;
		}
}/*END expr___________________________________________________________________*/

FLOAT64 term(bool get){
/*Input(s)		:nothing
PreCondition(s) :none
Description		:
PostCondition(s):none
Output(s)		:nothing
*/	FLOAT64 left = prim(get);
	for(;;){
		switch (curr_tok){
			case MUL:
				left *= prim(true);
				break;
			case DIV:
				if (FLOAT64 d = prim(true)){
					left /= d;
					break;
				}
				return error("divide by 0");
			default:
				return left;
		}
	}
}/*END term___________________________________________________________________*/

FLOAT64 prim(bool get){
/*Input(s)		:nothing
PreCondition(s) :none
Description		:handle primaries
PostCondition(s):none
Output(s)		:nothing
*/	
	if (get) get_token();

	switch (curr_tok){
		case NUMBER:		// floating-point constant
		{	FLOAT64 v = number_value;
			get_token();
			return v;
		}
		case NAME:
		{	FLOAT64 &v = table[string_value];
			if (get_token() == ASSIGN) v = expr(true);
			return v;
		}
		case MINUS:			// unary minus
			return -prim(true);
		case LP:
		{	FLOAT64 e = expr(true);
			if (curr_tok != RP) return error(") expected");
			get_token();	// eat ')'
			return e;
		}
		default:
			return error("primary expected");
	}
}/*END prim___________________________________________________________________*/

Token_value get_token(){
/*Input(s)		:nothing
PreCondition(s) :none
Description		:
PostCondition(s):none
Output(s)		:nothing
*/	char ch=0;
	do { if(!cin.get(ch))return curr_tok=END;}
		while(ch!='\n' && isspace(ch));// skip whitespace except ’\n’
	switch (ch) {
		case 0:
			return curr_tok=END;
		case';':	case'\n':
			return curr_tok = PRINT;
		case'*':	case'/':	case'+':	case'-':
		case'(':	case')':	case'=':
			return curr_tok=Token_value(ch);
		case'0': case'1': case'2': case'3': case'4':
		case'5': case'6': case'7': case'8': case'9':
		case'.':
			cin.putback(ch);
			cin >> number_value;
			return curr_tok=NUMBER;
		default:	// NAME, NAME =, or error
			if (isalpha(ch)) {
				string_value = ch;
				while (cin.get(ch) && isalnum(ch)) string_value.push_back(ch);
				cin.putback(ch);
				if (string_value == "exit") return curr_tok = END;
				return curr_tok=NAME;
			}
			error("bad token");
			return curr_tok=PRINT;
	}
}/*END get_token______________________________________________________________*/

FLOAT64 error(const string& s){
/*Input(s)		:nothing
PreCondition(s) :none
Description		:
PostCondition(s):none
Output(s)		:nothing
*/	
	no_of_errors++;
	cerr << "error: " << s << '\n';
	return 1;
}/*END error__________________________________________________________________*/
