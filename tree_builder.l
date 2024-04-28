%{
//*****************************************************************************************
// Filename: tree_builder.l
// Authors: Hunter Smith and Johnathan Reilly
// Brief: A LEX program that tokenizes tree building commands
// ****************************************************************************************

//Your lex program file to tokenize your code. We do not need to include a main, or much auxiliary code, as this just needs to return tokens to YACC. 
//Recall, not everything NEEDS to be tokenized before going to YACC. Its fine to just pass individual symbols or operators on (such as =, +, etc)

//declarations

#include <iostream>
#include <fstream>
#include "y.tab.h" //for yacc tokens

using namespace std;

//LOOPS
// #define TKFLOOP 001
// #define TKWLOOP 002
// #define TKDLOOP 003

// //LANGUAGE SPECIFIC WORDS
// #define TKBUILDNODE 004
// #define TKISCHILDOF 005
// #define TKNAME 006
// #define TKWEIGHT 007

// //OTHER
// #define TKINTLITERAL 010
// #define TKSTRINGLITERAL 011
// #define TKUNMATCHED 255


%}

/* 
(maybe use this later?) 
D[0-9]
LD[a-zA-Z0-9]
type[(void)(int)(double)(float)] */

%%

\/\*[^\*\/]*\*\/                  {} /* Ignore comments (from CMOS, maybe needed?)*/
\/\/+[^\n]*\n                 {}

[ \t\n\f\r]	{} /* Ignore Whitespace */

buildnode   {return TKBUILDNODE;} 
isachildof  {return TKISCHILDOF;}
name    {return TKNAME;}
weight  {return TKWEIGHT;}

[+\-*/%{},;=\<\>]                          {return yytext[0];}

\"[^"]*\" {return TKID;} /* Literals TKSTRINGLITERAL*/
[0-9]+  {return TKINT;} /*TKINTLITERAL */

[;\(\)\{\}\.\,\<\>\%\'\$\_\^\[\]\:\\\?\	] {} /* Ignore semicolon, parenthesis, and brackets*/



%%


int yywrap(){
	return true;
}

//temporary to test lex
/* buildnode   {return TKBUILDNODE;} / Key words 
isachildof  {return TKISCHILDOF;}
name    {return TKNAME;}
weight  {return TKWEIGHT;}
int main(){
	int token = 0;
	ofstream fout;

	//open the file
	fout.open("scanner_out.txt");
	if(fout.is_open()){
		token = yylex();
		fout << token;
		while(token){
			//output to file with a " " before it
			fout << " " << token;
			token = yylex();
		}
	}
	else{
		cout << "failed to open scanner out file" << endl;
	}
} */