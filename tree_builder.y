// Your YACC program to parse the grammar and perform syntactic analysis
//*****************************************************************************************
// Filename: tree_builder.y
// Authors: Hunter Smith and Johnathan Reilly
// Brief: A YACC program
// ****************************************************************************************
// Includes
%{
#include <vector>
#include <string>
#include "parse_tree.h"

%}

%union {
  char* s_val;
  statement *s_ptr;
  integer_expression *int_ptr;
  string_expression *str_ptr;
  compound_statement *c_ptr;
  int int_constant;
}

%{
extern int yylex();
extern void yyerror(char *String);  

using namespace std;
#include <iostream>

%}

%start start_var
%token <s_val> TKBUILDNODE TKSTRINGLITERAL FOR IN IDENTIFIER
%token <s_val> TKISCHILDOF TKNAME TKWEIGHT TKID TKINT
%token <int_constant> TKINTLITERAL
%left '*' '/' '%'
%left '+' '-'

//%type <s_val> TKID TKINT TKNAME TKWEIGHT TKISCHILDOF //FOR IN IDENTIFIER
%type <str_ptr> string_expression //TKSTRINGLITERAL
%type <int_ptr> integer_expression //TKINTLITERAL
%type <s_ptr> statement build_statement attribute loop_statement attribute_list range int_assignment_statement string_assignment_statement
%type <c_ptr> prog start_var

//Declarations

%%

start_var : prog { // At this point, the 
                   // the program is done --- let's evaluate the
                   // program
                   map<string,node> my_sym_tab;
                   $$= $1;
                   $1->evaluate_statement(my_sym_tab);
}

prog : statement prog {$$ = new compound_statement($1,$2);}
        | {$$ = NULL;}
        ;

statement : build_statement {$$ = $1;}
          | loop_statement {$$ = $1;}
          | int_assignment_statement {$$ = $1;}
          | string_assignment_statement {$$ = $1;}
          ;

int_assignment_statement : TKID '=' integer_expression ';' {$$ = new int_assignment_statement($1,$3);}

string_assignment_statement : TKID '=' string_expression ';' {$$ = new string_assignment_statement($1,$3);}

integer_expression : TKINT {$$ = new int_constant(atoi($1));}
                | TKID {$$= new variable($1);}
                | integer_expression '+' integer_expression {$$=new plus_expr($1,$3);}
                | '(' integer_expression ')' {$$ = $2;} 
                ;

string_expression : TKID {$$ = new string_constant($1);}
                | string_expression '+' string_expression {$$ = new concatenate_expr($1,$3);}
                | '(' string_expression ')' {$$ = $2;}
                ;

build_statement : TKBUILDNODE '{' string_expression ';' integer_expression ';' string_expression ';' '}' ';' {$$ = new build_statement($3, $5, $7);}
                | TKBUILDNODE '{' string_expression ';' integer_expression ';' '}' ';' {$$ = new root_statement($3, $5);}
                ;

/* attribute_list : attribute
               | attribute_list attribute
               ; */

/* attribute : TKNAME '=' string_expression ';' {$$ = $3;}
          | TKWEIGHT '=' integer_expression ';' {$$ = new int_assignment_statement($1,$3);}
          | TKISCHILDOF '=' string_expression ';' {$$ = new string_assignment_statement($1,$3);}
          ;  */

loop_statement : FOR IDENTIFIER IN '[' range ']' '{' prog '}' {}
               ;

range : TKINTLITERAL ':' TKINTLITERAL {}
      | TKSTRINGLITERAL ',' range {}
      | TKSTRINGLITERAL {}
      ;

%%
#include "lex.yy.c"

void yyerror(char *error_string)
{
  cout << "Error : " << error_string << endl;
  exit(-1);
}

// Auxiliary
int main() {
    yyparse();
    return 0;
}
