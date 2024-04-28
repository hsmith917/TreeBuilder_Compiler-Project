all:a.out
a.out:y.tab.c lex.yy.c parse_tree.h
	g++ -o a.out y.tab.c -ll
y.tab.c:tree_builder.y parse_tree.h
	bison tree_builder.y
	cat y.tab.c | sed 's/  __attribute__ ((__unused__))/\/\/ /g' >temp.cc
	mv temp.cc y.tab.c
lex.yy.c:tree_builder.l
	flex tree_builder.l
