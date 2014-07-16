#ifndef _SEARCH_H_
#define _SEARCH_H_

#include "manpage_utils.h"
#include "avl_tree.h"

class Search {
public:
	Search() {
		ifstream file;

		file.open("word.dat");

		if(file.is_open()) {

		}
		
	}
private:
	avl_tree<Index> secondaryKeyTree;
	doubly_linked_list<Manual> manuals;

};


#endif