#ifndef __PARSER__H__
#define __PARSER__H__
#include "lexer.h"
#include <string>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
 class Parser
{
	private:
	LexicalAnalyzer lexer;
	
	void syntax_error();
	
	
	
	
	public:
	Token peek();
	void expect(TokenType expected_type);
	void parse_program();
	int parse_request();
	//std::vector<ValueNode*> valList;
	Parser()
	{
	}
	~Parser()
	{
		//valList.clear();
	}
	std::vector<std::vector<std::string> > sentences;
	std::vector<std::string> words, uniqueWords;
	std::vector<int> wordCount,sentRank,sentSort;
	//StateList List;
	//void make();
	std::vector<Token*> value;
	std::vector<Token> master;
	std::vector<std::string>  commonWords;
	
	void importance();
	void unique();
	int lookup(std::string s);
	void printSent(int request);
	void makeWord()
	{
		//std::cout<<"lol";
		std::ifstream myFile;
		std::string line;

		myFile.open("smart_common_words.txt");
		
		if (myFile.is_open())
		 {
		    while ( getline (myFile,line) )
		    {
		  		//make
		  		//std::cout<<line;
		    	commonWords.push_back(line);
		    }
		    myFile.close();
		  }
	}

};

#endif
