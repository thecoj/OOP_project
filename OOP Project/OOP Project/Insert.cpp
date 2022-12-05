#include <iostream>
#include <stdio.h>
#include <string.h>
#include "identificator.h"
#include <vector>
using namespace std;

int Insert(char* tableName, char* command, char* values, vector<int>& valueType)
{
	char* p;
	int i, tokenType;
	bool ok = 0, isValue = 0;
	strcpy(values, "");
	p = strtok(command, " ");
	if (p != NULL)
	{
		strcpy(command, command + strlen(p) + 1);
		commandType(command, &tokenType);
		if (tokenType != INTO)
		{
			printf("Error: Missing INTO keyword\n");
			return 0;
		}
		strcpy(command, command + 5);
		commandType(command, &tokenType);
		if (tokenType != IDENTIFICATOR)
		{
			printf("Error: Missing table name\n");
			return 0;
		}
		else
		{
			for (i = 0; i < strlen(p); i++)
			{
				tableName[i] = p[i];
			}
			tableName[i] = '\0';
		}
		strcpy(command, command + strlen(p) + 1);
		commandType(command, &tokenType);
		if (tokenType != VALUES)
		{
			printf("Error: Missing VALUES keyword\n");
			return 0;
		}
		strcpy(command, command + strlen(p) + 1);
		commandType(command, &tokenType);
		if (tokenType != '(')
		{
			printf("Error: missing ( \n");
			return 0;
		}
		do
		{
			strcpy(command, command + strlen(p) + 1);
			commandType(command, &tokenType);
			isValue = (tokenType == INTEGER_NB || tokenType == FLOAT_NB || tokenType == IDENTIFICATOR);
			if (isValue == 0)
			{
				printf("Error: '%d' '%s' expected values\n", tokenType, p);
				return 0;
			}
			else
			{
				strcat(values, p);
				valueType.push_back(tokenType);
				strcat(values, " ");
			}
			strcpy(command, command + strlen(p) + 1);
			commandType(command, &tokenType);
			if (tokenType == ')')
			{
				ok = 1;
				strcpy(command, command + 2);
				break;
			}
		} while (tokenType == ',');
		values[strlen(values) + 1] = '\0';
		if (!ok)
		{
			printf("Error: missing ) \n");
			return 0;
		}
	}
	return 1;
}
