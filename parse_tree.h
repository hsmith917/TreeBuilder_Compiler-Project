//*****************************************************************************************
// Filename: parse_tree.h
// Authors: Hunter Smith and Johnathan Reilly
// ****************************************************************************************
#include <map>
#include <string>
#include <set>
#include <algorithm>
#include <iostream>
#include <cstddef>
#include "tree_node.h"

using namespace std;

//integer expressions
class integer_expression {
 public:
  virtual int evaluate_expression(map<string, node> &sym_tab) =0;
  
};

class int_constant:public integer_expression {
 public:
  int_constant(int val) {saved_val = val;}

  virtual int evaluate_expression(map<string, node> &sym_tab) {
    return saved_val;
  }
 private:
  int saved_val;
};

class plus_expr: public integer_expression {
 public:
  plus_expr(integer_expression *left, integer_expression *right) {
    l = left;
    r = right;
  }

  virtual int evaluate_expression(map<string, node> &sym_tab) {
    return l->evaluate_expression(sym_tab) + r->evaluate_expression(sym_tab);
  }
  
  private:
    integer_expression *l;
    integer_expression *r;
};

class variable: public integer_expression {
 public:
  variable(char *in_val) {//cout << "Found variable = " << in_val << endl; 
                          saved_val =in_val;}

  virtual int evaluate_expression(map<string, node> &sym_tab) {

    map<string,node>::iterator p;
    p =sym_tab.find(saved_val);
    //cout << "Looking up variable " << saved_val << endl;
    if (p!=sym_tab.end()) {
      //cout << "Returning value of variable " << saved_val << endl;
      //cout << "= " << p->second.weight << endl;

      return p->second.weight;
    } else {
      // ERROR .... for now return -1;
      // Should throw error!
      return -1;
    }

  }
 private:
  string saved_val;
  
};

// string expression
class string_expression {
    public:
        virtual string evaluate_expression(map<string, node> &sym_tab)=0;
};

class concatenate_expr : public string_expression {
    public:
        concatenate_expr(string_expression* left, string_expression* right) : l(left), r(right) {}

        virtual string evaluate_expression(map<string, node>& sym_tab) {
            return l -> evaluate_expression(sym_tab) + r -> evaluate_expression(sym_tab);
        }

    private:
        string_expression* l;
        string_expression* r;
};

class string_constant:public string_expression { //do we need this?
 public:
  string_constant(string val) {saved_val = val;}

  virtual string evaluate_expression(map<string, node> &sym_tab) {
    return saved_val;
  }
 private:
  string saved_val;
};

class statement {
 public:
  virtual void evaluate_statement(map<string, node> &sym_tab) =0;
};

class compound_statement: public statement {
 public:
  compound_statement(statement *first, compound_statement *rest) {
    f = first;
    r = rest;
  }
  
  virtual void evaluate_statement(map<string, node> &sym_tab) {
    if (f!=NULL) {
      f->evaluate_statement(sym_tab);
    }
    if (r!=NULL) {
      r->evaluate_statement(sym_tab);
    }
  }
 private:
  compound_statement *r;
  statement *f;
};

class build_statement: public statement { //note, this is from a version with binary trees
	public:
		build_statement(string_expression *n, integer_expression *w, string_expression *childOf)
 		{
			name = n;
			weight = w;
			isachildof = childOf;
		}
		virtual void evaluate_statement(map<string, node> &sym_tab)	
		{	//create the new node
			node *t = new node;
			t->name = name->evaluate_expression(sym_tab);
			t->weight = weight->evaluate_expression(sym_tab);	//changed from w to weight
      //cout << t->name << " and " << t->weight << endl;

			node *parent;	// find the parent
			map<string, node>::iterator p;
			p =sym_tab.find(isachildof->evaluate_expression(sym_tab));
			if (p!=sym_tab.end())
 			{	parent = &(*p).second;		} //changed from p.second
      insert(parent, t->name, t->weight, parent->name); //changed from binary tree

			sym_tab.insert(pair<string, node>(t->name, *t)); //changed from t.name to t->name
		}
	private:
		string_expression *name;
		integer_expression  *weight;
		string_expression  *isachildof;
};

class root_statement: public statement { //note, this is from a version with binary trees
public:
  root_statement(string_expression *n, integer_expression *w)
  {
    name = n;
    weight = w;
    isachildof = nullptr;
  }			
  virtual void evaluate_statement(map<string, node> &sym_tab)	
  {	//create the new node
    node *t = new node;
    t->name = name->evaluate_expression(sym_tab);
    t->weight = weight->evaluate_expression(sym_tab);	//changed from w to weight
    //cout << t->name << " and " << t->weight << endl;

    insert(t, "root", t->weight, "noone"); //changed from binary tree
    sym_tab.insert(pair<string, node>(t->name, *t)); //changed from t.name to t->name
  }
private:
  string_expression *name;
  integer_expression  *weight;
  string_expression  *isachildof;
};


class int_assignment_statement: public statement {
 public:
  int_assignment_statement(char *id, integer_expression *rhs) {
    ident = id;
    r_side = rhs;
  }
  virtual void evaluate_statement(map<string, node> &sym_tab) {
    
    int temp = r_side->evaluate_expression(sym_tab);

    //cout << "Assigning" << ident << " to " << temp << endl;

    sym_tab[ident].weight=temp; //added .weight
  }


  private: 
    string ident;
    integer_expression *r_side;
  };

class string_assignment_statement: public statement {
 public:
  string_assignment_statement(char *id, string_expression *rhs) {
    ident = id;
    r_side = rhs;
  }
  virtual void evaluate_statement(map<string, node> &sym_tab) {
    
    string temp = r_side->evaluate_expression(sym_tab);

    //cout << "Assigning" << ident << " to " << temp << endl;

    sym_tab[ident].name=temp; //added .name
  }


  private: 
    string ident;
    string_expression *r_side;
  };

