

int main(int argc, char** argv){
	auto arguments = argumentVector(argc, argv);

	auto argument = arguments.begin();

	if( *argument == "comand"){
		//search for manpages of the follow comands and print the manpage's text
	}
	if( *argument == "word"){
		//search in all manpages for the word, print the name of all manpages that have that word.
	}

	for( ++argument; argument != arguments.end(); ++argument){
		
	}




	return 0;
}