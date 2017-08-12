#define  CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <string>
#include <set>
#include <algorithm>

using namespace std;

bool word_break( string input, set<string> dictionary ) {
	
	if ( input == "" || dictionary.empty() )
		return false;


	transform( input.begin(), input.end(), input.begin(), ::tolower);

	int init_size;

	while ( input.size() > 0 ) {
		init_size = input.length();

		// loop through dictionary and match values
		for ( string word : dictionary ) {
			if ( input.length() >=  word.length() && word == input.substr(0, word.length() ) ) {
				// if a match is found remove that part of the string
				input = input.substr( word.length() , input.length() - word.length() );
			}
		}
		
		// if no match in library was found return false
		if ( init_size == input.length() ) 
			return false;
	}	
	
	return true;
}

TEST_CASE("empty arguments") {
	string input;
	set<string> dictionary;
	
	string some_words = "hello you";

	set<string> some_dict;
	some_dict.insert("hey");
	
	REQUIRE( word_break( input, dictionary ) == false );
	REQUIRE( word_break( some_words, dictionary ) == false );
	REQUIRE( word_break( input, some_dict ) == false );
}

TEST_CASE("non valid input") {
	string str_1 = "weirdwordzoom";
	string str_2 = "funnyreasontwo";
	string str_3 = "thebigbrownfox";
	
	set<string> dict;
	dict.insert("word");  dict.insert("zoom");
	dict.insert("funny"); dict.insert("two");
	dict.insert("the"); dict.insert("big");
	dict.insert("brown");
	
	REQUIRE( word_break( str_1, dict ) == false );
	REQUIRE( word_break( str_2, dict ) == false );
	REQUIRE( word_break( str_3, dict ) == false );
}

TEST_CASE("valid input") {
	// test repeated words
	string hello = "hellohellohello";
	// test case sensitivity
	string up_case = "WoRdWORDword";
	// all unique words
	string fox = "bigbrownfox";
	
	set<string> dict;
	dict.insert("hello");
	dict.insert("word");
	dict.insert("big");
	dict.insert("brown");
	dict.insert("fox");
	
	REQUIRE( word_break( hello, dict ) == true );
	REQUIRE( word_break( up_case, dict ) == true );
	REQUIRE( word_break( fox, dict ) == true );
}
