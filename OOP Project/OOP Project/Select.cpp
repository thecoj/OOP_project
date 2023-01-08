#include <iostream>
#include <stdio.h>
#include <string.h>
#include "identificator.h"

int Select(char* tableName, char* command, char* columns)
{
	char* p;
	int i, tokenType = 0;
	bool moreColumns = 0;
	p = strtok(command, " ");
	if (p != NULL)
	{
		strcpy(command, command + strlen(p) + 1);
		commandType(command, &tokenType);
		if (tokenType == ALL || tokenType == IDENTIFICATOR)
		{
			if (tokenType == ALL)
			{
				strcpy(command, command + 4);
				commandType(command, &tokenType);
				if (tokenType != FROM)
				{
					printf("ERROR: Missing keyword FROM.\n");
					return 0;
				}
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
				return 2;
			}
			else
			{

				//for (i = 0; i < strlen(p); i++)
				//{
				//	columns[i] = p[i];
				//}
				//columns[i] = ' ';
				int ok = 0, id = 0;
				do
				{
					if (ok != 0)
					{
						strcpy(command, command + strlen(p) + 1);
						commandType(command, &tokenType);
					}
					for (int i = 0; i < strlen(p); i++)
					{
						columns[id] = p[i];
						id++;
					}
					columns[id] = ' ';
					id++;
					strcpy(command, command + strlen(p) + 1);
					commandType(command, &tokenType);
					ok++;
				} while (tokenType == ',');
				/*
				strcpy(command, command + strlen(p) + 1);
				commandType(command, &tokenType);
				while (tokenType == ',')
				{
					moreColumns = 1;
					strcpy(command, command + strlen(p) + 1);
					commandType(command, &tokenType);
					if (tokenType != IDENTIFICATOR)
					{
						printf("ERROR: Missing table name. ' %s'\n", p);
						return 0;
					}
					else
					{
						strcat(columns, p);
						strcat(columns, " ");
					}
				}
				if (moreColumns)
				{
					strcpy(command, command + strlen(p) + 1);
					commandType(command, &tokenType);
				}*/
				columns[strlen(columns) + 1] = '\0';
				if (tokenType != FROM)
				{
					printf("ERROR: Misspelt FROM keyword.\n");
					return 0;
				}
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

			}
		}
		else
		{
			printf("ERROR: Selected columns do not exist.\n");
			return 0;
		}
	}
	return 1;
}
