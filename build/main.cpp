#include <iostream>
#include <vector>
#include <string>

#include "dataStructures/CircularList.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

using dataStructures::CircularList;

struct Index{
	string word;
};

int main(int argc, char** argv){

	auto searchWordsSize = argc -1;
	auto searchWords = vector<string> {};

	for(auto i = 0; i < searchWordsSize; i++){
		searchWords.push_back(argv[i +1]);
	}

	for(auto word : searchWords){
		cout << word << endl;
	}
}