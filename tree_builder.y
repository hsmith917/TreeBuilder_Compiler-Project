%{
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "parse_tree.h"

using namespace std;

extern int yylex();
extern void yyerror(const char *);

map<string, node> sym_tab;
%}

%union {
  char* s_val;
  statement *s_ptr;
  integer_expression *int_ptr;
  string_expression *str_ptr;
  compound_statement *c_ptr;
}

%token <s_val> TKBUILDNODE TKSTRINGLITERAL FOR IN IDENTIFIER TKINTLITERAL
%token <s_val> TKISCHILDOF TKNAME TKWEIGHT TKID TKINT
%left '*' '/'
%left '+' '-'

%type <s_val> string_expression
%type <int_ptr> integer_expression
%type <s_ptr> statement build_statement loop_statement range
%type <c_ptr> prog start_var

%start start_var

%%

start_var : prog { $$ = $1; }

prog : statement prog { $$ = new compound_statement($1, $2); }
     | { $$ = NULL; };

statement : build_statement { $$ = $1; }
          | loop_statement { $$ = $1; };

loop_statement : FOR IDENTIFIER IN '[' range ']' '{' prog '}' { $$ = new loop_statement($2, $5, $9); };

range : TKINTLITERAL ':' TKINTLITERAL { $$ = make_pair(atoi($1), atoi($3)); }
      | TKSTRINGLITERAL ',' range { $$ = $1 + ", " + $3; }
      | TKSTRINGLITERAL { $$ = $1; };

build_statement : TKBUILDNODE '{' TKNAME '=' string_expression ';' TKWEIGHT '=' integer_expression ';' TKISCHILDOF '=' string_expression ';' '}' ';' {
                    $$ = new build_statement($5, $9, $13);
                    sym_tab[$5->evaluate_expression(sym_tab)] = node($5->evaluate_expression(sym_tab), $9->evaluate_expression(sym_tab));
                  }
                | TKBUILDNODE '{' TKNAME '=' string_expression ';' TKWEIGHT '=' integer_expression ';' '}' ';' {
                    $$ = new root_statement($5, $9);
                    sym_tab[$5->evaluate_expression(sym_tab)] = node($5->evaluate_expression(sym_tab), $9->evaluate_expression(sym_tab));
                  };

integer_expression : TKINT { $$ = new int_constant(atoi($1)); }
                | TKID { $$ = new variable($1); }
                | integer_expression '+' integer_expression { $$ = new plus_expr($1, $3); }
                | '(' integer_expression ')' { $$ = $2; };

string_expression : TKID { $$ = new string_constant($1); }
                | string_expression '+' string_expression { $$ = new concatenate_expr($1, $3); }
                | '(' string_expression ')' { $$ = $2; };

%%

int main() {
  yyparse();
  return 0;
}
