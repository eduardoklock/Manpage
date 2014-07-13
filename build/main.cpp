#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "doubly_linked_list.h"
#include "AvlTree.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

using std::fstream;
using std::stringstream;

struct Manual {

	Manual(string name, string text){
		this->name = name;
		this->text = text;
	}

	string name;
	string text;
};

struct Index {

	Index(string word);

private:
	string word;
	doubly_linked_list<Manual> manuals;
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

	for (auto manual : manuals) {
		cout << "{ "<< manual.name << " , " << manual.text << " }" << endl;
	}
}