// Code file containing class definitions and code to respond to the statements in the code.
#include <map>
#include <string>
#include <set>
#include <algorithm>
#include <iostream>

using namespace std;

//integer expressions
class integer_expression {
 public:
  virtual int evaluate_expression(map<string, int> &sym_tab) =0;
  
};

class plus_expr: public integer_expression {
 public:
  plus_expr(integer_expression *left, integer_expression *right) {
    l = left;
    r = right;
  }

  virtual int evaluate_expression(map<string, int> &sym_tab) {
    return l->evaluate_expression(sym_tab) + r->evaluate_expression(sym_tab);
  }
  
  private:
    integer_expression *l;
    integer_expression *r;
};

class minus_expr: public integer_expression {
 public:
  minus_expr(integer_expression *left, integer_expression *right) {
    l = left;
    r = right;
  }

  virtual int evaluate_expression(map<string, int> &sym_tab) {
    return l->evaluate_expression(sym_tab) - r->evaluate_expression(sym_tab);
  }
  
  private:
    integer_expression *l;
    integer_expression *r;
};

class mult_expr: public integer_expression {
 public:
  mult_expr(integer_expression *left, integer_expression *right) {
    l = left;
    r = right;
  }

  virtual int evaluate_expression(map<string, int> &sym_tab) {
    return l->evaluate_expression(sym_tab) * r->evaluate_expression(sym_tab);
  }
  
  private:
    integer_expression *l;
    integer_expression *r;
};

class div_expr: public integer_expression {
 public:
  div_expr(integer_expression *left, integer_expression *right) {
    l = left;
    r = right;
  }

  virtual int evaluate_expression(map<string, int> &sym_tab) {
    return l->evaluate_expression(sym_tab) / r->evaluate_expression(sym_tab);
  }
  
  private:
    integer_expression *l;
    integer_expression *r;
};

class mod_expr: public integer_expression {
 public:
  mod_expr(integer_expression *left, integer_expression *right) {
    l = left;
    r = right;
  }

  virtual int evaluate_expression(map<string, int> &sym_tab) {
    return l->evaluate_expression(sym_tab) % r->evaluate_expression(sym_tab);
  }
  
  private:
    integer_expression *l;
    integer_expression *r;
};

// string expression
class string_expression {
    public:
        virtual string evaluate_expression(map<string, string> &sym_tab)=0;
};

class concatenate_expr : public string_expression {
    public:
        concatenate_expr(string_expression* left, string_expression* right) : l(left), r(right) {}

        virtual string evaluate_expression(map<string, string>& sym_tab) {
            return l -> evaluate_expression(sym_tab) + r -> evaluate_expression(sym_tab);
        }

    private:
        string_expression* l;
        string_expression* r;
};