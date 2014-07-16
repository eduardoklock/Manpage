#include <string>

#include <iostream>
#include <fstream>
#include <sstream>

#include "doubly_linked_list.h"
#include "avl_tree.h"
#include "manpage_utils.h"

using std::cout;
using std::endl;
using std::string;
using std::ofstream;
using std::fstream;
using std::stringstream;
using std::pair;

int main(int argc, char** argv){

	auto filePaths = argumentVector(argc, argv);

	auto manuals = doubly_linked_list<Manual>();

	pair<unsigned long,unsigned long> largestManual(0, 0);

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

			if(fileText.size()>largestManual.first) {
				largestManual.first = fileText.size();
			}
			if(fileName.size()>largestManual.second) {
				largestManual.second = fileName.size();
			}


			file.close();
		}
	}

	auto thingsThatShouldNotEnterIntheTreeList = thingsThatShouldNotEnterIntheTree();

	auto secondaryKeyTree = avl_tree<Index>();

	for (auto manual : manuals){
		stringstream textStream;
		textStream << manual.text;

		string word;
		while(textStream >> word){

			Index search = Index(word);
			if(!thingsThatShouldNotEnterIntheTreeList.has(word)){
				if(!secondaryKeyTree.has(search)){
				
					search.manualNames.push_back(manual.name);
					secondaryKeyTree.insert(search);
				}
				else
				{
					secondaryKeyTree.find(search).manualNames.push_back(manual.name);
				}
			}
		}
	}

	ofstream file;
	file.open("words.dat");

	if(file.is_open()){
		auto secondaryKeyList = secondaryKeyTree.in_order();
 
		for (auto index : secondaryKeyList){
			file << index.word << " ";
			for (auto name : index.manualNames){
				file << name << " ";
			}
			file << endl;
		}
		file.close();
	}

	file.open("manpage.dat");
	if(file.is_open()){
		file << largestManual.second << " " << largestManual.first << " ";
		for(auto manual : manuals){
			string manualName = manual.name;
			manualName.resize(largestManual.second, ' ');
			file << manualName;
			string manualText = manual.text;
			manualText.resize(largestManual.first, ' ');
			file << manualText;
		}

		file.close();		
	}


}