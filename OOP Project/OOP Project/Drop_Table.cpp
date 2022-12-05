#include <iostream>
#include <stdio.h>
#include <string.h>
#include "identificator.h"

int ParseDrop( char* tableName, char* command, int tokenType)
{
	char* p;
	int i;
	p = strtok(command, " ");
	if (p != NULL)
	{
		strcpy(command, command + 11);
		tip_command(command, &tokenType);
		if (tokenType != IDENTIFICATOR)
		{
			printf("Eroare: lipseste nume tabela\n");
			return 0;
		}
		else
		{
			for (i = 0; i < strlen(p);i++)
			{
				tableName[i] = p[i];
			}
			tableName[i] = '\0';
			//return 1;
		}
		strcpy(command, command + strlen(p) + 1);
	}
	return 1;
}
