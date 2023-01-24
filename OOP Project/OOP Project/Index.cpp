#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "identificator.h"

int DropIndex(char* command, char* tableName, char* indexName, int tokenType)
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
			printf("ERROR: Missing index name\n");
			return 0;
		}
		else
		{
			for (i = 0; i < strlen(p); i++)
			{
				indexName[i] = p[i];
			}
			indexName[i] = '\0';

		}
		strcpy(command, command + strlen(p) + 1);
	}
	return 1;
}

int CreateIndex(char* tableName, char* indexName, char* columnName, char* command)
{
	char* p;
	char* pColumns;
	int i, id = 0, tokenType = 0;
	bool ok = false;
	p = strtok(command, " ");
	if (p != NULL)
	{
		strcpy(command, command + 13);
		commandType(command, &tokenType);
		if (tokenType != IDENTIFICATOR)
		{
			printf("ERROR: '%d' '%s' names expected \n", tokenType, p);
			return 0;
		}
		else
		{
			for (i = 0; i < strlen(p); i++)
			{
				indexName[i] = p[i];
			}
			indexName[i] = '\0';
		}
		strcpy(command, command + strlen(indexName) + 1);
		commandType(command, &tokenType);
		if (tokenType != ON)
		{
			printf("ERROR: Missing ON \n");
			return 0;
		}
		strcpy(command, command + 3);
		commandType(command, &tokenType);
		if (tokenType != IDENTIFICATOR)
		{
			printf("ERROR: Missing table name\n");
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
		if (tokenType != '(')
		{
			printf("ERROR: ( expected \N");
			return 0;
		}
		strcpy(command, command + 2);
		commandType(command, &tokenType);
		if (tokenType != IDENTIFICATOR)
		{
			printf("ERROR: Missing column name\n");
			return 0;
		}
		else
		{
			for (i = 0; i < strlen(p); i++)
			{
				columnName[i] = p[i];
			}
			columnName[i] = '\0';
		}
		strcpy(command, command + strlen(p) + 1);
		commandType(command, &tokenType);
		if (tokenType != ')')
		{
			printf("ERROR: ')' expected \n");
			return 0;
		}
		strcpy(command, command + 2);
	}
	return 1;
}
