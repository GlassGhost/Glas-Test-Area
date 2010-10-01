/******************************PROGRAM DESCRIPTION******************************
A Calculator
************************************Author(s)***********************************
Roy Pfund, 
original from pages 107-175 of The C++ Programming Language 3rd Ed.; Bjarne
Stroustrup
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
*************************************Output*************************************
The evaluation of the expressions you give it
***********************************Revisions************************************
(10-11-2009)-0.1-Got it working!
(10-10-2009)-0.01-File created
***********************************License(s)***********************************
NO RIGHTS, NO WARRANTY of any kind. NOT EVEN AN IMPLIED ONE. Just a quick hack.
/******************************************************************************/
#include <iostream>
#include <string>
#include <map>
#include <cctype>
using namespace std;
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
/**********************************Functions***********************************/
double expr(bool get);
double error(const string& s);
double prim(bool get);
double term(bool get);
Token_value get_token();

int main(int argc, char *argv[]){/*Main logic**********************************/
	if(argc > 1){/*************Command line args*******************************/
		if(argv[0]!="-")//Tests if user argument is legitimate.
			goto end_of_command_line_args;
		std::string arg = argv[--argc];//insert new aruments after this line.
		if(arg.find("-help") != -1)//a standard command line argument
			std::cout <<"Command line args are:\n\t-help\n";
	} end_of_command_line_args:/***********************************************/
	table["pi"] = 3.1415926535897932385; // insert predefined names
	table["e"] = 2.7182818284590452354;
	printf("Enter a mathematical expression (e.g. \"2 + 2\"), or Type \"exit\" to exit:\n");
	while (cin) {
		get_token();
		if (curr_tok == END) break;
		if (curr_tok == PRINT) continue;
		cout << expr(false) <<'\n';
	}
	system("pause"); //keeps Microsoft command prompt from going bananas
	return no_of_errors;
}/**********************************End Main***********************************/

/**********************************Functions**********************************/
double expr(bool get){// add and subtract
	double left=term(get);
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
}

double term(bool get){
	double left = prim(get);
	for(;;){
		switch (curr_tok){
			case MUL:
				left *= prim(true);
				break;
			case DIV:
				if (double d = prim(true)){
					left /= d;
					break;
				}
				return error("divide by 0");
			default:
				return left;
		}
	}
}

double prim(bool get){		// handle primaries
	if (get) get_token();

	switch (curr_tok){
		case NUMBER:		// floating-point constant
		{	double v = number_value;
			get_token();
			return v;
		}
		case NAME:
		{	double &v = table[string_value];
			if (get_token() == ASSIGN) v = expr(true);
			return v;
		}
		case MINUS:			// unary minus
			return -prim(true);
		case LP:
		{	double e = expr(true);
			if (curr_tok != RP) return error(") expected");
			get_token();	// eat ')'
			return e;
		}
		default:
			return error("primary expected");
	}
}

Token_value get_token(){
	char ch=0;
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
}

double error(const string& s){
	no_of_errors++;
	cerr << "error: " << s << '\n';
	return 1;
}
