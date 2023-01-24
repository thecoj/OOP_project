#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "identificator.h"

char Delete(char check, char* tableName, char* columnName, char* value, int& typeWhere, char* command, int tokenType)
{
	char* p;
	int i;
	p = strtok(command, " ");
	if (p != NULL)
	{
		strcpy(command, command + strlen(p) + 1);
		commandType(command, &tokenType);
		if (tokenType != FROM)
		{
			printf("ERROR: Missing FROM keyword\n");
			check = 'N';
			return check;
		}
		strcpy(command, command + 5);
		commandType(command, &tokenType);
		if (tokenType != IDENTIFICATOR)
		{
			printf("ERROR: Missing table name\n");
			check = 'N';
			return check;
		}
		else
		{
			for (i = 0; i < strlen(p); i++)
			{
				tableName[i] = p[i];
			}
			tableName[i] = '\0';
		}
		strcpy(command, command + strlen(tableName) + 1);
		commandType(command, &tokenType);
		if (tokenType != WHERE)
		{
			printf("ERROR: Missing condition\n");
			check = 'N';
			return check;
		}
		strcpy(command, command + 6);
		commandType(command, &tokenType);
		if (tokenType != IDENTIFICATOR)
		{
			printf("ERROR: Missing column name\n");
			check = 'N';
			return check;
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
		if (tokenType != '=')
		{
			printf("ERROR: incomplete condition\n");
			check = 'N';
			return check;
		}
		strcpy(command, command + 2);
		commandType(command, &tokenType);
		bool isValue = (tokenType == INTEGER_NB || tokenType == FLOAT_NB || tokenType == IDENTIFICATOR);
		if (!isValue)
		{
			printf("ERROR: Missing value\n");
			check = 'N';
			return check;
		}
		else
		{
			typeWhere = tokenType;
			for (i = 0; i < strlen(p); i++)
			{
				value[i] = p[i];
			}
			value[i] = '\0';
		}
		strcpy(command, command + strlen(p) + 1);

	}
	check = 'Y';
	return check;
}
