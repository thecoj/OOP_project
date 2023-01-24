#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "identificator.h"
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

char* readCommands(char* input)
{
	*input = '\0';
	string tmp;
	while (std::getline(std::cin, tmp))
	{
		if (tmp.empty())
			break;
		else
		{
			transform(tmp.begin(), tmp.end(), tmp.begin(), ::toupper);
			strcat(input, tmp.c_str());
		}
	}
	return input;
}

/*char* commandLine(char* input)
{
	char* commandLine;
	char *newCommandLine;
	commandLine = strtok(input, ";");
	newCommandLine = input + strlen(commandLine);
	return newCommandLine;
}*/

void commandType(char* command, int* tokenType)
{
	char* p;
	p = strtok(command, " ");
	if (p != NULL)
	{
		if (strlen(p) == 1)
		{
			if (isdigit(*p))
				*tokenType = INTEGER_NB;
			else if (isalpha(*p))
				*tokenType = IDENTIFICATOR;
			else
				*tokenType = *p;
		}
		else {
			if (isalpha(*p))
			{
				int totalCharacters = 0;
				int totalNumbers = 0;
				int pos = 0;
				for (int i = 0; i < strlen(p); i++)
				{
					if (isalpha(*(p + i)))
						totalCharacters++;
					else if (isdigit(*(p + i)))
						totalNumbers++;
				}
				if (totalCharacters == strlen(p))
				{
					if (strcmp(p, "CREATE") == 0)
						*tokenType = CREATE;
					else if (strcmp(p, "DELETE") == 0)
						*tokenType = DELETE;
					else if (strcmp(p, "DISPLAY") == 0)
						*tokenType = DISPLAY;
					else if (strcmp(p, "DROP") == 0)
						*tokenType = DROP;
					else if (strcmp(p, "SELECT") == 0)
						*tokenType = SELECT;
					else if (strcmp(p, "UPDATE") == 0)
						*tokenType = UPDATE;
					else if (strcmp(p, "TABLE") == 0)
						*tokenType = TABLE;
					else if (strcmp(p, "INT") == 0)
						*tokenType = INT;
					else if (strcmp(p, "FLOAT") == 0)
						*tokenType = FLOAT;
					else if (strcmp(p, "CHAR") == 0)
						*tokenType = CHAR;
					else if (strcmp(p, "CSV") == 0)
						*tokenType = CSV;
					else if (strcmp(p, "IMPORT") == 0)
						*tokenType = IMPORT;
					else if (strcmp(p, "INSERT") == 0)
						*tokenType = INSERT;
					else if (strcmp(p, "INTO") == 0)
						*tokenType = INTO;
					else if (strcmp(p, "VALUES") == 0)
						*tokenType = VALUES;
					else if (strcmp(p, "FROM") == 0)
						*tokenType = FROM;
					else if (strcmp(p, "WHERE") == 0)
						*tokenType = WHERE;
					else if (strcmp(p, "SET") == 0)
						*tokenType = SET;
					else if (strcmp(p, "ALL") == 0)
						*tokenType = ALL;
					else if (strcmp(p, "INDEX") == 0)
						*tokenType = INDEX;
					else if (strcmp(p, "ON") == 0)
						*tokenType = ON;
					else
						*tokenType = IDENTIFICATOR;
				}
			}
			else if (isdigit(*p))
			{
				int decimal = 0;
				int pos = 1;
				for (int i = 1; i < strlen(p); i++)
				{
					if (!isdigit(*(p + i)) && decimal < 1)
					{
						if (*(p + i) == '.')
						{
							decimal++;
							pos++;
						}
						else
						{
							*(p + i) = '\0';
							break;
						}
					}
					else if (!isdigit(*(p + i)) && decimal == 1)
					{
						*(p + i) = '\0';
						break;
					}
					else
						pos++;
				}
				if (pos == 1)
					*tokenType = INTEGER_NB;
				else if (decimal != 0)
					*tokenType = FLOAT_NB;
				else
					*tokenType = INTEGER_NB;
			}
		}
	}
}