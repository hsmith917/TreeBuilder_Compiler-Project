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

%token BUILDNODE FOR IN NAME WEIGHT ISACHILDOF
%token <string_literal> STRING_LITERAL 
%token <int_literal> INT_LITERAL
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

build_node_statement : BUILDNODE L_BRACE attribute_list R_BRACE SEMICOLON
                     ;

attribute_list : attribute
               | attribute_list attribute
               ;

attribute : NAME EQUALS STRING_LITERAL SEMICOLON
          | WEIGHT EQUALS INT_LITERAL SEMICOLON
          | ISACHILDOF EQUALS STRING_LITERAL SEMICOLON
          ;

loop_statement : FOR IDENTIFIER IN L_BRACE range R_BRACE L_BRACE statement_list R_BRACE
               ;

range : INT_LITERAL COLON INT_LITERAL
      | STRING_LITERAL COMMA range
      ;

%%

// Auxiliary
int main() {
    yyparse();
    return 0;
}


