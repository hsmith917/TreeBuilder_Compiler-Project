// Your YACC program to parse the grammar and perform syntactic analysis


%{
#include <stdio.h>
#include "tree_node.h" // Include header file for tree node definitions
#include "parse_tree.h" // Include header file for parsing functions

%}

//Declarations
%token BUILDNODE FOR IN NAME WEIGHT ISACHILDOF
%token STRING_LITERAL INT_LITERAL
%token RANGE SEMICOLON 
%token COMMA PLUS EQUALS
%token L_BRACE R_BRACE L_PAREN R_PAREN
%token IDENTIFIER

//Rules
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

attribute : NAME '=' STRING_LITERAL SEMICOLON
          | WEIGHT '=' INT_LITERAL SEMICOLON
          | ISACHILDOF '=' STRING_LITERAL SEMICOLON
          ;

loop_statement : FOR IDENTIFIER IN '[' range ']' L_BRACE statement_list R_BRACE
               ;

range : INT_LITERAL ':' INT_LITERAL
      | STRING_LITERAL ',' range
      ;

%%

//Auxiliary
int main() {
    // Code to initiate parsing
    yyparse();
    return 0;
}


