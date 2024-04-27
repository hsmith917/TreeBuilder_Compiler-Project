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


class build_statement { //note, this is from a version with binary trees
	public:
		build_statement(map<string, node> &sym_tab, string_expression *n, integer_expression *w, string_expression *childOf)
 		{
			name = n;
			weight = w;
			isachildof = childOf;
		}				
		virtual void evaluate_statement(map<string, node> &sym_tab)	
		{	//create the new node
			node *t = new node;
			t->name = name->evaluate_expression;
			t->weight = w->evaluate_expression;	

			node *parent;	// find the parent
			map<string, node>::iterator p;
			p =sym_tab.find(isachildof->evaluate_expression);
			if (&p!=sym_tab.end())
 			{	parent = p.second;		}

			// if (parent->r_child == NULL)
			// {	t->l_sibling = NULL;	}
			// else	{t.->l_sibling = parent->r_child;	}
			// parent->r_child = t;
      // bool condition = true;
      // for(vector<node*>::iterator it = parent->children.begin(); it < parent->children.end(); ++it){
      //   if((*it)->weight > w && condition){
      //     parent->children.insert(it, tmp);
      //     condition = false;
      //   }
      // }
      // if(condition){
      //   root->children.push_back(tmp);
      // }
      insert(parent, t->name, t->weight, parent->name);
      

			sym_tab.insert(pair<string, node>(t.name, *t));
		}
	private:
		string_expression *name;
		integer_expression  *weight;
		string_expression  *isachildof;
	};
