// Your YACC program to parse the grammar and perform syntactic analysis

// Includes
%{
#include <iostream>
#include <vector>
#include <string>
#include "parse_tree.h"
using namespace std;

extern int yylex(); 
extern char* yytext; 
extern int yylval; 
%}

//Declarations
%union {
    int int_literal;
    string string_literal;
}

%token TKBUILDNODE FOR IN TKNAME TKWEIGHT TKISCHILDOF
%token <string_literal> TKSTRINGLITERAL 
%token <int_literal> TKINTLITERAL
%token SEMICOLON COLON
%token COMMA PLUS EQUALS
%token L_BRACE R_BRACE
%token IDENTIFIER



// Rules
%%

program : statement_list
        ;

statement_list : statement
               | statement_list statement
               ;

statement : build_node_statement
          | loop_statement
          ;

build_node_statement : TKBUILDNODE L_BRACE attribute_list R_BRACE SEMICOLON
                     ;

attribute_list : attribute
               | attribute_list attribute
               ;

attribute : TKNAME EQUALS TKSTRINGLITERAL SEMICOLON
          | TKWEIGHT EQUALS TKINTLITERAL SEMICOLON
          | TKISCHILDOF EQUALS TKSTRINGLITERAL SEMICOLON
          ;

loop_statement : FOR IDENTIFIER IN L_BRACE range R_BRACE L_BRACE statement_list R_BRACE
               ;

range : TKINTLITERAL COLON TKINTLITERAL
      | TKSTRINGLITERAL COMMA range
      ;

%%

// Auxiliary
int main() {
    yyparse();
    return 0;
}


