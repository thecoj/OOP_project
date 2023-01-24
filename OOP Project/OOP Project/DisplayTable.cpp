#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "identificator.h"

int DisplayTable(char* tableName, char* command)
{
	char* p;
	int i, tokenType = 0;
	p = strtok(command, " ");
	if (p != NULL)
	{
		strcpy(command, command + strlen(p) + 1);
		commandType(command, &tokenType);
		if (tokenType != TABLE)
		{
			printf("ERROR: Missing or misspelt TABLE keyword.\n");
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
				tableName[i] = p[i];
			}
			tableName[i] = '\0';
		}
		strcpy(command, command + strlen(p) + 1);
	}
	return 1;
}
