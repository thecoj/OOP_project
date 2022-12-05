#include <iostream>
#include <stdio.h>
#include <string.h>
#include "identificator.h"

int displayTable(char* tableName, char* command)
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
			printf("Error: TABLE keyword is missing or doesn't exist.\n");
			return 0;
		}
		strcpy(command, command + 6);
		commandType(command, &tokenType);
		if (tokenType != IDENTIFICATOR)
		{
			printf("Error: Table name missing.\n");
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
	}
	return 1;
}
