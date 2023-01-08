#include <iostream>
#include <stdio.h>
#include <string.h>
#include "identificator.h"
using namespace std;

int Update(char* tableName, char* columnNameSet, char* valueSet, int& setType, char* nameColumnWhere, char* valueWhere, int& typeWhere, char* command, char* tableInfo)
{
	char* p;
	int i, tokenType = 0;
	p = strtok(command, " ");
	if (p != NULL)
	{
		strcpy(command, command + strlen(p) + 1);
		commandType(command, &tokenType);
		if (tokenType != IDENTIFICATOR)
		{
			printf("ERROR: Missing table name.\n");
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
		if (tokenType != SET)
		{
			printf("ERROR: Missing keyword SET.\n");
			return 0;
		}
		strcpy(command, command + 4);
		commandType(command, &tokenType);
		if (tokenType != IDENTIFICATOR)
		{
			printf("ERROR: Missing table name to be updated.\n");
			return 0;
		}
		else
		{
			for (i = 0; i < strlen(p); i++)
			{
				columnNameSet[i] = p[i];
			}
			columnNameSet[i] = '\0';
		}
		strcpy(command, command + strlen(p) + 1);
		commandType(command, &tokenType);
		if (tokenType != '=')
		{
			printf("ERROR: Missing = sign .\n");
			return 0;
		}
		strcpy(command, command + 2);
		commandType(command, &tokenType);
		bool isValue = (tokenType == INTEGER_NB || tokenType == FLOAT_NB || tokenType == IDENTIFICATOR);
		if (!isValue)
		{
			printf("ERROR: Missing value to be updated.\n");
			return 0;
		}
		else
		{
			setType = tokenType;
			for (i = 0; i < strlen(p); i++)
			{
				valueSet[i] = p[i];
			}
			valueSet[i] = '\0';
		}
		strcpy(command, command + strlen(p) + 1);
		commandType(command, &tokenType);
		if (tokenType != WHERE)
		{
			printf("ERROR: Missing condition.\n");
			return 0;
		}
		strcpy(command, command + 6);
		commandType(command, &tokenType);
		if (tokenType != IDENTIFICATOR)
		{
			printf("ERROR: Missing table name.\n");
			return 0;
		}
		else
		{
			for (i = 0; i < strlen(p); i++)
			{
				nameColumnWhere[i] = p[i];
			}
			nameColumnWhere[i] = '\0';
		}
		strcpy(command, command + strlen(p) + 1);
		commandType(command, &tokenType);
		if (tokenType != '=')
		{
			printf("ERROR: Incomplete condition.\n");
			return 0;
		}
		strcpy(command, command + 2);
		commandType(command, &tokenType);
		isValue = (tokenType == INTEGER_NB || tokenType == FLOAT_NB || tokenType == IDENTIFICATOR);
		if (!isValue)
		{
			printf("ERROR: Missing value.\n");
			return 0;
		}
		else
		{
			typeWhere = tokenType;
			for (i = 0; i < strlen(p); i++)
			{
				valueWhere[i] = p[i];
			}
			valueWhere[i] = '\0';
		}
		strcpy(command, command + strlen(p) + 1);
	}
	return 1;
}
