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

build_node_statement : TKBUILDNODE '{' attribute_list '}' ';'
                     ;

attribute_list : attribute
               | attribute_list attribute
               ;

attribute : TKNAME '=' TKSTRINGLITERAL ';'
          | TKWEIGHT '=' TKINTLITERAL ';'
          | TKISCHILDOF '=' TKSTRINGLITERAL ';'
          ;

loop_statement : FOR IDENTIFIER IN '{' range '}' '{' statement_list '}'
               ;

range : TKINTLITERAL ':' TKINTLITERAL
      | TKSTRINGLITERAL ',' range
      ;

%%

// Auxiliary
int main() {
    yyparse();
    return 0;
}


