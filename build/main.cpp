#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "doubly_linked_list.h"

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


vector<string> argumentVector(int argc, char** argv){
	auto numberOfArguments = argc -1;
	auto arguments = vector<string> {};

	for(auto i = 0; i < numberOfArguments; i++){
		arguments.push_back(argv[i + 1]);
	}

	return arguments;
}

int main(int argc, char** argv){

	auto fileNames = argumentVector(argc, argv);

	auto manuals = CircularList<Manual>();

	for (string fileName : fileNames) {
		fstream file;
		file.open(fileName);
		if(file.is_open()){
			stringstream fileTextStream;
			fileTextStream << file.rdbuf();
			auto fileText = fileTextStream.str();

			//

			file.close();
		}
	}

	auto manpage = Manual(fileNames.at(0), fileText);
}