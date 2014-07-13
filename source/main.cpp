#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "doubly_linked_list.h"
#include "avl_tree.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

using std::fstream;
using std::stringstream;

struct Manual {

	Manual(string name, string text):
		name(name),
		text(text)
	{}

	string name;
	string text;
};

struct Index {

	Index(string word):
		word(word),
		manuals()
	{}

	string word;
	doubly_linked_list<Manual> manuals;

	bool operator==(const Index& rhs) const
    {
        return this->word == rhs.word;
    }
    bool operator<(const Index& rhs) const
    {
        return this->word < rhs.word;
    }
    
    bool operator>(const Index& rhs) const
    {
        return this->word > rhs.word;
    }
};


doubly_linked_list<string> argumentVector(int argc, char** argv){
	auto numberOfArguments = argc -1;
	auto arguments = doubly_linked_list<string>();

	for(auto i = 0; i < numberOfArguments; i++){
		arguments.push_back(argv[i + 1]);
	}

	return arguments;
}

int main(int argc, char** argv){

	auto filePaths = argumentVector(argc, argv);

	auto manuals = doubly_linked_list<Manual>();

	for (string path : filePaths) {
		fstream file;
		file.open(path);

		if(file.is_open()){
			stringstream fileTextStream;
			fileTextStream << file.rdbuf();
			auto fileText = fileTextStream.str();

			auto last_slash = path.find_last_of('/');
			auto last_dot = path.find_last_of('.');

			auto fileName = path.substr(last_slash + 1, last_dot - (last_slash + 1));

			manuals.push_back(Manual(fileName, fileText));

			file.close();
		}
	}

	auto primaryKeyTree = avl_tree<Index>();

	for (auto manual : manuals){
		stringstream textStream;
		textStream << manual.text;

		string word;
		while(textStream >> word){

			Index search = Index(word);

			if(!primaryKeyTree.has(search)){
				
				search.manuals.push_back(manual);
				primaryKeyTree.insert(search);
			}
			else
			{
				primaryKeyTree.find(search).manuals.push_back(manual);
			}
		}
	}

	fstream file{"manpage.dat"};

	if(file.is_open()){
		auto primaryKeyList = primaryKeyTree.in_order();

		for(auto index : primaryKeyList){
			cout << index.word << endl;
		}

		file.close();
	}
}