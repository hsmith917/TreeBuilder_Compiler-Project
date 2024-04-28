#ifndef PARSE_TREE_H
#define PARSE_TREE_H

#include <map>
#include <string>
#include "tree_node.h"

using namespace std;

class integer_expression {
public:
    virtual int evaluate_expression(map<string, node>& sym_tab) = 0;
    virtual ~integer_expression() {}
};

class int_constant : public integer_expression {
public:
    int_constant(int val) : saved_val(val) {}

    virtual int evaluate_expression(map<string, node>& sym_tab) {
        return saved_val;
    }

private:
    int saved_val;
};

class plus_expr : public integer_expression {
public:
    plus_expr(integer_expression* left, integer_expression* right) : l(left), r(right) {}

    virtual int evaluate_expression(map<string, node>& sym_tab) {
        return l->evaluate_expression(sym_tab) + r->evaluate_expression(sym_tab);
    }

private:
    integer_expression* l;
    integer_expression* r;
};

class variable : public integer_expression {
public:
    variable(const string& in_val) : saved_val(in_val) {}

    virtual int evaluate_expression(map<string, node>& sym_tab) {
        auto it = sym_tab.find(saved_val);
        if (it != sym_tab.end()) {
            return it->second.weight;
        } else {
            cerr << "Variable " << saved_val << " not found!" << endl;
            return -1; // Error: Variable not found
        }
    }

private:
    string saved_val;
};

class string_expression {
public:
    virtual string evaluate_expression(map<string, node>& sym_tab) = 0;
    virtual ~string_expression() {}
};

class concatenate_expr : public string_expression {
public:
    concatenate_expr(string_expression* left, string_expression* right) : l(left), r(right) {}

    virtual string evaluate_expression(map<string, node>& sym_tab) {
        return l->evaluate_expression(sym_tab) + r->evaluate_expression(sym_tab);
    }

private:
    string_expression* l;
    string_expression* r;
};

class string_constant : public string_expression {
public:
    string_constant(const string& val) : saved_val(val) {}

    virtual string evaluate_expression(map<string, node>& sym_tab) {
        return saved_val;
    }

private:
    string saved_val;
};

class statement {
public:
    virtual void evaluate_statement(map<string, node>& sym_tab) = 0;
    virtual ~statement() {}
};

class compound_statement : public statement {
public:
    compound_statement(statement* first, compound_statement* rest) : f(first), r(rest) {}

    virtual void evaluate_statement(map<string, node>& sym_tab) {
        if (f) f->evaluate_statement(sym_tab);
        if (r) r->evaluate_statement(sym_tab);
    }

private:
    statement* f;
    compound_statement* r;
};

class build_statement : public statement {
public:
    build_statement(string_expression* n, integer_expression* w, string_expression* childOf)
        : name(n), weight(w), isachildof(childOf) {}

    virtual void evaluate_statement(map<string, node>& sym_tab) {
        node t;
        t.name = name->evaluate_expression(sym_tab);
        t.weight = weight->evaluate_expression(sym_tab);
        insert(sym_tab["root"], t.name, t.weight, isachildof->evaluate_expression(sym_tab));
    }

private:
    string_expression* name;
    integer_expression* weight;
    string_expression* isachildof;
};

class loop_statement : public statement {
public:
    loop_statement(const string& identifier, const pair<int, int>& range, compound_statement* body)
        : id(identifier), rng(range), stmts(body) {}

    virtual void evaluate_statement(map<string, node>& sym_tab) {
        for (int i = rng.first; i <= rng.second; ++i) {
            sym_tab[id] = node(id, i);
            stmts->evaluate_statement(sym_tab);
        }
    }

private:
    string id;
    pair<int, int> rng;
    compound_statement* stmts;
};

class root_statement : public statement {
public:
    root_statement(string_expression* n, integer_expression* w) : name(n), weight(w) {}

    virtual void evaluate_statement(map<string, node>& sym_tab) {
        node t;
        t.name = name->evaluate_expression(sym_tab);
        t.weight = weight->evaluate_expression(sym_tab);
        insert(sym_tab["root"], t.name, t.weight, "");
    }

private:
    string_expression* name;
    integer_expression* weight;
};

class int_assignment_statement : public statement {
public:
    int_assignment_statement(const string& id, integer_expression* rhs) : ident(id), r_side(rhs) {}

    virtual void evaluate_statement(map<string, node>& sym_tab) {
        sym_tab[ident].weight = r_side->evaluate_expression(sym_tab);
    }

private:
    string ident;
    integer_expression* r_side;
};

class string_assignment_statement : public statement {
public:
    string_assignment_statement(const string& id, string_expression* rhs) : ident(id), r_side(rhs) {}

    virtual void evaluate_statement(map<string, node>& sym_tab) {
        sym_tab[ident].name = r_side->evaluate_expression(sym_tab);
    }

private:
    string ident;
    string_expression* r_side;
};

#endif // PARSE_TREE_H
