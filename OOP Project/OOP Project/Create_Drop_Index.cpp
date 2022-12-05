#include <iostream>
#include <stdio.h>
#include <string.h>
#include "identificator.h"

int dropIndex(char* command, char* tableName, char* indexNumber, int tokenType)
{
	char* p;
	int i;
	p = strtok(command, " ");
	if (p != NULL)
	{
		strcpy(command, command + 11);
		commandType(command, &tokenType);
		if (tokenType != IDENTIFICATOR)
		{
			printf("Error: missing index name\n");
			return 0;
		}
		else
		{
			for (i = 0; i < strlen(p);i++)
			{
				indexNumber[i] = p[i];
			}
			indexNumber[i] = '\0';

		}
		strcpy(command, command + strlen(p) + 1);
	}
	return 1;
}

int createIndex(char* tableName, char* indexNumber, char* columnName, char* command)
{
	char* p;
	char* pColumn;
	int i, id = 0, tokenType = 0;
	bool ok = false;
	p = strtok(command, " ");
	if (p != NULL)
	{
		strcpy(command, command + 13);
		commandType(command, &tokenType);
		if (tokenType != IDENTIFICATOR)
		{
			printf("Error: still waiting name'%d' '%s'\n", tokenType, p);
			return 0;
		}
		else
		{
			for (i = 0; i < strlen(p);i++)
			{
				indexNumber[i] = p[i];
			}
			indexNumber[i] = '\0';
		}
		strcpy(command, command + strlen(indexNumber) + 1);
		commandType(command, &tokenType);
		if (tokenType != ON)
		{
			printf("Error: Missing ON \n");
			return 0;
		}
		strcpy(command, command + 3);
		commandType(command, &tokenType);
		if (tokenType != IDENTIFICATOR)
		{
			printf("Error: table name is missing\n");
			return 0;
		}
		else
		{
			for (i = 0; i < strlen(p);i++)
			{
				tableName[i] = p[i];
			}
			tableName[i] = '\0';
		}
		strcpy(command, command + strlen(p) + 1);
		commandType(command, &tokenType);
		if (tokenType != '(')
		{
			printf("Error: still waiting \n");
			return 0;
		}
		strcpy(command, command + 2);
		commandType(command, &tokenType);
		if (tokenType != IDENTIFICATOR)
		{
			printf("Error: column name missing\n");
			return 0;
		}
		else
		{
			for (i = 0; i < strlen(p);i++)
			{
				columnName[i] = p[i];
			}
			columnName[i] = '\0';
		}
		strcpy(command, command + strlen(p) + 1);
		commandType(command, &tokenType);
		if (tokenType != ')')
		{
			printf("Error: still waiting \n");
			return 0;
		}
		strcpy(command, command + 2);
	}
	return 1;
}
