#include "parser.h"
using namespace std;

void Parser::syntax_error()
{
    cout << "Syntax Error";
    exit(0);
}



void Parser::expect(TokenType expected_type)
{
	Token t =  lexer.GetToken();
	if(t.token_type!=expected_type)
	{
		syntax_error();
	}
	

}
Token Parser::peek()
{
	Token t = lexer.GetToken();
	lexer.UngetToken(t);
	return t;
}
int Parser::parse_request()
{
	cout<<"How many sentences do you want?";
	Token T=lexer.GetToken();
	T.Print();
	int request=0;
	stringstream num(T.lexeme);
	num>>request;
	return request;
		
}
void Parser::parse_program()
{
	
	Token T= lexer.GetToken();
	master.push_back(T);
	T=peek();
	if(T.token_type==END_OF_FILE)
	{
		expect(END_OF_FILE);
		lexer.GetToken();	
	}
	else
	{
		parse_program();

	}
}
int Parser:: lookup(string s)
{
	for(int i=0;i<uniqueWords.size();i++)
	{
		if(s==uniqueWords[i])
		{
			return wordCount[i];
		}
	}
}
void Parser::importance()
{
	for(int i =0;i<uniqueWords.size();i++)
	{
		for(int j=0;j<commonWords.size();j++)
		{
			if(uniqueWords[i]==commonWords[j])
			{
				wordCount[i]=0;
			}
		}
	}
	for (int i = 0; i < sentences.size(); ++i)
	{
		sentRank.push_back(0);
	}
	int sentImp=0;
	for (int i = 0; i < sentences.size(); ++i)
	{	sentImp=0;
		for (int j = 0; j < sentences[i].size(); ++j)
		{
			sentImp=sentImp+lookup(sentences[i][j]);
		}
		sentRank[i]=sentImp;
	}
	for (int i = 0; i < sentRank.size(); ++i)
	{
		sentSort.push_back(sentRank[i]);
	}
	sort(sentSort.begin(),sentSort.end());
}
void Parser::unique()
{
//check for duplicates
	for(int i=0; i<master.size();i++)
	{
		if(master[i].token_type==ID)
		{
			words.push_back(master[i].lexeme);
		}
	}
	sort(words.begin(),words.end());
	//now maybe it's sorted?
	
	for(int i=0; i<words.size();i++)
	{
		//cout<<words[i];
		if(i==0)
		uniqueWords.push_back(words[0]);
		else if(i>0)
		{
			if(words[i]!=words[i-1])
			{
				uniqueWords.push_back(words[i]);
			}
		}
	}
	//cout<<endl;
	for (int i = 0; i < uniqueWords.size(); ++i)
	{
		/* code */
		//cout<<uniqueWords[i]<<endl;
		wordCount.push_back(0);
	}
	for(int i=0; i<words.size();i++)
	{
		for(int j=0;j<uniqueWords.size();j++)
		{
			if(words[i]==uniqueWords[j])
			{
				wordCount[j]++;
			}
		}
	}
}
void Parser::printSent(int request)
{
	
	//cout<< request;
	//bool moveOn = false;
	for(int i=0;i<request-1;i++)
	{
		for(int j=0;j<sentences.size();j++)
		{ 
			//cout<<"compare: "<<sentRank[i]<<" "<<sentSort[j]<<endl;
			if(sentRank[i]==sentSort[j])
			{
				for(int k=0;k<sentences[i].size();k++)
				{
					cout<<sentences[i][k]<<" ";
				}
			}
		}
		cout<<endl;
	}

}
int main()
{
	Parser parser;
	parser.makeWord();
	//cout<<parser.commonWords.size();
	int request=parser.parse_request();
	parser.parse_program();//
	

	int size=parser.master.size();
	int sentenceCount= 0;
	vector<string> dummy;
	parser.sentences.push_back(dummy);
	for(int i=0;i<size;i++)
	{
		if(parser.master[i].token_type==ID||parser.master[i].token_type==NUM)
		{
			parser.sentences[sentenceCount].push_back(parser.master[i].lexeme);
		}
		else
		{
			vector <string>  dummy;
			parser.sentences.push_back(dummy);
			sentenceCount++;
		}
	}
	/*
	for (int i = 0; i < parser.sentences.size(); ++i)
	{
		for (int j = 0; j < parser.sentences[i].size(); ++j)
		{
			//cout<<parser.sentences[i][j];
		}
		//cout<<endl;
	}
	 */
	
	parser.unique();
	parser.importance();
	//int x=0;

	parser.printSent(request);
	/*
	
	 for(int i =0;i<parser.commonWords.size();i++)
	{
		cout<<parser.commonWords[i]<<endl;
	}

	
	 */
		//cout<<x;
	return 0;
}