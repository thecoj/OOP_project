#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "identificator.h"

int Import(char* tableName, char* command, char* fileName)
{
	char* p;
	int i, tokenType;
	bool ok = 0, isValue = 0;
	p = strtok(command, " ");
	if (p != NULL)
	{
		strcpy(command, command + strlen(p) + 1);
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
		if (tokenType != IDENTIFICATOR)
		{
			printf("ERROR: Missing file name\n");
			return 0;
		}
		else
		{
			for (i = 0; i < strlen(p); i++)
			{
				fileName[i] = p[i];
			}
			fileName[i] = '\0';
		}
		strcpy(command, command + strlen(p) + 1);
		commandType(command, &tokenType);
		if (tokenType != '.')
		{
			printf("ERROR: Missing . \n");
			return 0;
		}
		strcpy(command, command + strlen(p) + 1);
		commandType(command, &tokenType);
		if (tokenType != CSV)
		{
			printf("ERROR: Not a CSV file\n");
			return 0;
		}

	}
	return 1;
}
