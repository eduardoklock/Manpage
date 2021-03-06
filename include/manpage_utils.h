#ifndef _MANPAGE_UTILS_H_
#define _MANPAGE_UTILS_H_

#include <string>

#include "doubly_linked_list.h"

using std::string;

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
		manualNames()
	{}

	string word;
	doubly_linked_list<string> manualNames;

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

doubly_linked_list<string> thingsThatShouldNotEnterIntheTree(){
	doubly_linked_list<string> aux;
	return aux.push_back(string { "a" }).push_back(string { "an" }).push_back(string { "the" }).push_back(string { "no" }).push_back(string { "for" }).push_back(string { "and" }).push_back(string { "nor" }).push_back(string { "but" }).push_back(string {"or" }).push_back(string { "yet" }).push_back(string { "so" }).push_back(string { "I" }).push_back(string { "me" }).push_back(string { "we" }).push_back(string { "us" }).push_back(string { "you" }).push_back(string { "she" }).push_back(string {"her" }).push_back(string { "he" }).push_back(string { "him" }).push_back(string { "it" }).push_back(string { "they" }).push_back(string {"them" }).push_back(string { "what" }).push_back(string { "which" }).push_back(string { "who" }).push_back(string { "whom" }).push_back(string {"whose" }).push_back(string { "whichever" }).push_back(string {"whoever" }).push_back(string { "whomever" }).push_back(string { "aboard" }).push_back(string { "about" }).push_back(string { "above" }).push_back(string { "across" }).push_back(string { "after" }).push_back(string { "against" }).push_back(string { "ahead" }).push_back(string { "along" }).push_back(string {"amid" }).push_back(string { "amidst" }).push_back(string { "among" }).push_back(string { "around" }).push_back(string { "as" }).push_back(string { "aside" }).push_back(string {"at" }).push_back(string { "athwart" }).push_back(string { "atop" }).push_back(string { "barring" }).push_back(string { "because" }).push_back(string { "before" }).push_back(string { "behind" }).push_back(string { "below" }).push_back(string { "beneath" }).push_back(string { "beside" }).push_back(string { "besides" }).push_back(string { "between" }).push_back(string { "beyond" }).push_back(string { "but" }).push_back(string { "by" }).push_back(string {"circa" }).push_back(string { "concerning" }).push_back(string {"despite" }).push_back(string { "down" }).push_back(string {"during" }).push_back(string { "except" }).push_back(string {"excluding" }).push_back(string { "following" }).push_back(string {"for" }).push_back(string { "from" }).push_back(string { "in" }).push_back(string { "including" }).push_back(string { "inside" }).push_back(string { "instead" }).push_back(string { "into" }).push_back(string { "like" }).push_back(string { "minus" }).push_back(string {"near" }).push_back(string { "of" }).push_back(string { "off" }).push_back(string { "on" }).push_back(string { "onto" }).push_back(string {"opposite" }).push_back(string { "out" }).push_back(string {"outside" }).push_back(string { "over" }).push_back(string { "past" }).push_back(string { "plus" }).push_back(string {"prior" }).push_back(string { "regarding" }).push_back(string {"regardless" }).push_back(string { "save" }).push_back(string {"since" }).push_back(string { "tan" }).push_back(string { "through" }).push_back(string { "till" }).push_back(string { "to" }).push_back(string { "toward" }).push_back(string {"towards" }).push_back(string { "under" }).push_back(string {"underneath" }).push_back(string { "unlike" }).push_back(string {"until" }).push_back(string { "up" }).push_back(string { "upon" }).push_back(string { "versus" }).push_back(string { "via" }).push_back(string {"with" }).push_back(string { "within" }).push_back(string {"without" }).push_back(string { "this" }).push_back(string { "these" }).push_back(string { "that" }).push_back(string { "those" }).push_back(string { "myself" }).push_back(string { "ourselves" }).push_back(string { "yourself" }).push_back(string { "yourselves" }).push_back(string { "himself" }).push_back(string { "herself" }).push_back(string { "itself" }).push_back(string { "themselves" }).push_back(string { "anybody" }).push_back(string { "anyone" }).push_back(string { "anything" }).push_back(string { "each" }).push_back(string { "either" }).push_back(string { "everybody" }).push_back(string { "everyone" }).push_back(string { "everything" }).push_back(string { "neither" }).push_back(string { "nobody" }).push_back(string { "nothing" }).push_back(string { "one" }).push_back(string {"somebody" }).push_back(string { "someone" }).push_back(string {"something" }).push_back(string { "both" }).push_back(string { "few" }).push_back(string { "many" }).push_back(string {"several" }).push_back(string { "all" }).push_back(string { "any" }).push_back(string { "most" }).push_back(string { "none" }).push_back(string {"some" }).push_back(string { "my" }).push_back(string { "your" }).push_back(string { "his" }).push_back(string { "its" }).push_back(string {"our" }).push_back(string { "your" }).push_back(string { "their" }).push_back(string { "mine" }).push_back(string { "yours" }).push_back(string {"his" }).push_back(string { "hers" }).push_back(string { "ours" }).push_back(string { "yours" }).push_back(string { "theirs" });
}

#endif