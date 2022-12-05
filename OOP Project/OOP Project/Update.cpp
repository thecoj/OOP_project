#include <iostream>
#include <stdio.h>
#include <string.h>
#include "identificator.h"
using namespace std;

int Update(char* tableName, char* columnNameSet, char* setValue, int &setType, char* nameColumnWhere, char* valueWhere, int &typeWhere, char* command, char* infoTable)
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
			printf("Error: table name missing.\n");
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
		if (tokenType != SET)
		{
			printf("Error: missing keyword SET.\n");
			return 0;
		}
		strcpy(command, command + 4);
		commandType(command, &tokenType);
		if (tokenType != IDENTIFICATOR)
		{
			printf("Error: missing column name that has to be modified.\n");
			return 0;
		}
		else
		{
			for (i = 0; i < strlen(p);i++)
			{
				columnNameSet[i] = p[i];
			}
			columnNameSet[i] = '\0';
		}
		strcpy(command, command + strlen(p) + 1);
		commandType(command, &tokenType);
		if (tokenType != '=')
		{
			printf("Error: missing sign = .\n");
			return 0;
		}
		strcpy(command, command + 2);
		commandType(command, &tokenType);
		bool isValue = (tokenType == INTEGER_NB || tokenType == FLOAT_NB || tokenType == IDENTIFICATOR);
		if (!isValue)
		{
			printf("Error: missing value that needs to be changed.\n");
			return 0;
		}
		else
		{
			setType = tokenType;
			for (i = 0; i < strlen(p);i++)
			{
				setValue[i] = p[i];
			}
			setValue[i] = '\0';
		}
		strcpy(command, command + strlen(p) + 1);
		commandType(command, &tokenType);
		if (tokenType != WHERE)
		{
			printf("Error: missing condition.\n");
			return 0;
		}
		strcpy(command, command + 6);
		commandType(command, &tokenType);
		if (tokenType != IDENTIFICATOR)
		{
			printf("Error: missing column name.\n");
			return 0;
		}
		else
		{
			for (i = 0; i < strlen(p);i++)
			{
				nameColumnWhere[i] = p[i];
			}
			nameColumnWhere[i] = '\0';
		}
		strcpy(command, command + strlen(p) + 1);
		commandType(command, &tokenType);
		if (tokenType != '=')
		{
			printf("Error: incomplete condition.\n");
			return 0;
		}
		strcpy(command, command + 2);
		commandType(command, &tokenType);
		isValue = (tokenType == INTEGER_NB || tokenType == FLOAT_NB || tokenType == IDENTIFICATOR);
		if (!isValue)
		{
			printf("Error: missing value.\n");
			return 0;
		}
		else
		{
			typeWhere = tokenType;
			for (i = 0; i < strlen(p);i++)
			{
				valueWhere[i] = p[i];
			}
			valueWhere[i] = '\0';
		}
		strcpy(command, command + strlen(p) + 1);
	}
	return 1;
}
