//Your lex program file to tokenize your code. We do not need to include a main, or much auxiliary code, as this just needs to return tokens to YACC. 
//Recall, not everything NEEDS to be tokenized before going to YACC. Its fine to just pass individual symbols or operators on (such as =, +, etc)



%{
//*****************************************************************************************
// Filename: treebuilder.l
// Authors: Hunter Smith and Johnathan Reilly
// Brief: A LEX program that tokenizes tree building commands
// ****************************************************************************************

//declarations

#include <iostream>
#include <fstream>

using namespace std;

//LOOPS
#define TKFLOOP 001
#define TKWLOOP 002
#define TKDLOOP 003

//LANGUAGE SPECIFIC WORDS
#define TKBUILDNODE 004
#define TKISCHILDOF 005
#define TKNAME 006
#define TKWEIGHT 007

//OTHER
#define TKINTLITERAL 008
#define TKSTRINGLITERAL 009
#define TKUNMATCHED 255


%}

/* 
(maybe use this later?) 
D[0-9]
LD[a-zA-Z0-9]
type[(void)(int)(double)(float)] */

%%

/* Ignore comments (from CMOS, maybe needed?)*/
\/\*[^\*\/]*\*\/                  {} 
\/\/+[^\n]*\n                 {}

/* Ignore Whitespace */
[ \t\n\f\r]	{}

/* Ignore semicolon, parenthesis, and brackets*/
[;\(\)\{\}\.\,\<\>\%\'\$\_\^\[\]\:\\\?\	] {} 

/* Literals */ 
\"[^"]*\" {return TKSTRINGLITERAL;}
[0-9]+  {return TKINTLITERAL;}

/* Key words */
buildnode   {return TKBUILDNODE;}
isachildof  {return TKISCHILDOF;}
name    {return TKNAME;}
weight  {return TKWEIGHT;}

/* Single character operators (Directions say to return yytext)*/
+   {return yytext();}
=   {return yytext();}

/* Unmatched tokens */
.   {return TKUNMATCHED;}

%%

int yywrap(){
	return true;
}

