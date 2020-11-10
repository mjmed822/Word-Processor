/* PA1.cpp : Programming Assignment 1
			 Basic Word Processor
			 Matthew Medina
			 CS280001
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

int main(in argc, char* argv[])
{
	ifstream file;
	int lineLength = 20;
	int indent = 5;
	int wordCount = 50;
	int spacing = 1;
	int curWordCount = 0;
	string unrecognized = "";
	bool found = false;
	bool found2 = false;
	string unrecognized2 = "";
	
	if (argc == 1)
	{
		cerr << "UNABLE TO OPEN FILE!" << endl;
		exit(1);
	}
		
	for (int i = 1; i < argc; i++)
		{
			char ch = *argv[i];
			unrecognized = "";
			string name = argv[i];
			
			if (ch != '-')
			{
				//string name = argv[i];
				size_t index = name.find('.');
				
				if (index == string::npos)
				{
					found = true;
					unrecognized = argv[i];
				}
			}
			else
			{
				size_t index2 = name.find('=');
				if (index2 == string::npos)
				{
					found2 = true;
					unrecognized2 = argv[i];
				}
			}
			
			if (found)
			{
				cout << name.find("=") << endl;
				cerr << "UNRECOGNIZED FLAG " << unrecognized << endl;
				exit(1);
			}
			if (found2)
			{
				cerr << "MISSING EQUALS SIGN " << unrecognized2 << endl;
				exit(1);
			}
		}
	
		for (int i = 1; i < argc; i++)
		{
			string name = argv[i];
			size_t index = name.find('.');
			if (index != string::npos)
			{
				file.open(name);

				if (!file.is_open())
				{
					cerr << "UNABLE TO OPEN FILE!" << endl;
					exit(1);
				}
			}
			else
			{
				int v = 0;
				bool known = false;
				string a;
				a.assign(argv[i], 4);
				if (a == "-LL=")
				{
					known = true;
					v = atoi(argv[i] + 4);
					if (v > 0)
						lineLength = v;
					else
					{
						cerr << "VALUE NOT INTEGER greater than 0 " << argv[i] + 4 << endl;
						exit(1);
					}
				}
				else if (a == "-IN=")
				{
					known = true;
					v = atoi(argv[i] + 4);
					if (v > 0)
						indent = v;
					else
					{
						cerr << "VALUE NOT INTEGER greater than 0 " << argv[i] + 4 << endl;
						exit(1);
					}
				}
				else if (a == "-WC=")
				{
					known = true;
					v = atoi(argv[i] + 4);
					if (v > 0)
						wordCount = v;
					else
					{
						cerr << "VALUE NOT INTEGER greater than 0 " << argv[i] + 4 << endl;
						exit(1);
					}
				}
				else if (a == "-SP=")
				{
					known = true;
					v = atoi(argv[i] + 4);
					if (v > 0)
						spacing = v;
					else
					{
						cerr << "VALUE NOT INTEGER greater than 0 " << argv[i] + 4 << endl;
						exit(1);
					}
				}

			}
		}

			//Beginning of parsing file
			string line;
			vector<string> tokens;
			char temp[1000];
			string word;
			bool blankLine;
			bool lastBlankLine = false;

			while (file.getline(temp, 1000, '\n'))
			{
				stringstream words;
				words.str(temp);
				blankLine = true;
				while (words >> word)
				{
					blankLine = false;
					lastBlankLine = false;
					curWordCount++;
					if (curWordCount < wordCount)
						tokens.push_back(word);
				}
				if ((lastBlankLine == false) && blankLine)
				{
					tokens.push_back("\n");
					lastBlankLine = true;
				}
			}

			int curLineLength = indent;
			for (int i = 0; i < indent; i++)
			{
				cout << " ";
			}
			//Outputting the data
			for (string token : tokens)
			{
				curLineLength += token.length();
				if (curLineLength > lineLength)
				{
					for (int i = 0; i < spacing; i++)
					{
						cout << "\n";
					}
					curLineLength = token.length();
				}
				//start of new paragraph
				if (token == "\n")
				{
					for (int i = 0; i <= spacing; i++)
					{
						cout << "\n";
					}
					for (int i = 0; i < indent; i++)
					{
						cout << " ";
					}
					curLineLength = indent;
				}
				else
				{
					cout << token << " ";
					curLineLength++;
				}

			}
			
			cout << "\n\nTotal number of words: " << curWordCount 
				<< "\nThe maximum allowed number of words is: " << wordCount << endl;
			if (curWordCount > wordCount)
			{
				cout << "\nThe read file contains number of words exceeding the allowed maximum."
					<< "\nIt has been truncated accordingly.";
			}
}

