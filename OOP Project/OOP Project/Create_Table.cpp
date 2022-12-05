#include <iostream>
#include <stdio.h>
#include <string.h>
#include "identificator.h"
#include "Column.h"
#include <list>

int CreateTable(char* tableName, char* tableInfo, list<string>& columns, int* dimension, char* command, list<string>& columnsType)
{
	char* p;
	int i,id = 0,tokenType = 0;
	bool ok = false;
	p = strtok(command, " ");
	if (p != NULL)
	{
		strcpy(command, command + 13);
		commandType(command, &tokenType);
		if (tokenType != IDENTIFICATOR)
		{
			printf("Error: missing table name\n");
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
		strcpy(command, command + strlen(tableName) + 1);
		commandType(command, &tokenType);
		if (tokenType != '(')
		{
			printf("Error missing ( \n");
			return 0;
		}
		
		do
		{
			strcpy(command, command + strlen(p)+1);
			commandType(command, &tokenType);
			if (tokenType != IDENTIFICATOR)
			{
				printf("Error: missing column name ' %s'\n", p);
				return 0;
			}
			else
			{
				columns.push_back(p);
				for (i = 0;i < strlen(p);i++)
				{
					infoTable[id + i] = p[i];
				}
				infoTable[id + i] = ' ';
				id = id + (int)strlen(p) + 1;
				//id = id + (int)strlen(p);
			}
			strcpy(command, command + strlen(p) + 1);
			commandType(command, &tokenType);
			bool isType = false;
			isType = (tokenType == INT || tokenType == FLOAT || tokenType == CHAR);
			if (isType == false)
			{
				printf("Error: waiting for the column type '%s' \n", p);
				return 0;
			}
			else
			{
				if (tokenType == INT)
				{
					columnstype.push_back("INT");
				}
				else
				{
					if (tokenType == FLOAT)
					{
						columnstype.push_back("FLOAT");
					}
					else
						if (tokenType == CHAR)
						{
							strcpy(command, command + 5);
							commandType(command, &tokenType);
							if (tokenType != '(')
							{
								printf("Error: missing ( \n");
								return 0;
							}
							else
							{
								strcpy(command, command + 2);
								commandType(command, &tokenType);
								if (tokenType != INTEGER_NB)
								{
									printf("Error: waiting for dimension '%d' integer \n", tokenType);
									return 0;
								}
								else
								{
									columnstype.push_back("CHAR");
									strcat(infoTable, p);
									strcpy(command, command + strlen(p) + 1);
									commandType(command, &tokenType);
									if (tokenType != ')')
									{
										printf("Error: missing '%d' '%s' ) \n", tokenType, p);
										return 0;
									}
								}
							}
						}
				}
				
			}
			strcpy(command, command + strlen(p)+1);
			commandType(command, &tokenType);
			if (tokenType == ')')
			{
				ok = 1;
				strcpy(command, command + 2);
				break;
			}
			
		} while (tokenType==',');
		if (!ok)
		{
			printf("Error: missing ) \n");
			return 0;
		}
		
	}
	return 1;
}