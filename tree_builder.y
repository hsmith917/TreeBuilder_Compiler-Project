// Your YACC program to parse the grammar and perform syntactic analysis

// Includes
%{
#include <iostream>
#include <vector>
#include <string>

%}

%union {
    char* s_val;
    statement *s_ptr;
    integer_expression *int_ptr;
    string_expression *str_ptr;
    compound_statement *c_ptr;
}

%{
extern int yylex();
extern void yyerror(char *String);  

#include <iostream>
 using namespace std;
 #include "parse_tree.h"

%}

%start program
%token TKBUILDNODE TKISCHILDOF TKNAME TKWEIGHT TKSTRINGLITERAL TKINTLITERAL FOR IN IDENTIFIER

%left '*' '/' '%'
%left '+' '-'

%type <s_ptr> TKBUILDNODE FOR IN TKNAME TKWEIGHT TKISCHILDOF
%type <str_ptr> TKSTRINGLITERAL
%type <int_ptr> TKINTLITERAL
%type <c_ptr> compound_statement

//Declarations

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
