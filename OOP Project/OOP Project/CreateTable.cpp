#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string.h>
#include "identificator.h"
#include "Column.h"
#include <list>

int CreateTable(char* tableName, char* tableInfo, list<string>& columns, int* size, char* command, list<string>& columnType)
{
	char* p;
	int i, id = 0, tokenType = 0;
	bool ok = false;
	p = strtok(command, " ");
	if (p != NULL)
	{
		strcpy(command, command + 13);
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
		strcpy(command, command + strlen(tableName) + 1);
		commandType(command, &tokenType);
		if (tokenType != '(')
		{
			printf("ERROR: Missing ( \n");
			return 0;
		}

		do
		{
			strcpy(command, command + strlen(p) + 1);
			commandType(command, &tokenType);
			if (tokenType != IDENTIFICATOR)
			{
				printf("ERROR: Missing column name ' %s'\n", p);
				return 0;
			}
			else
			{
				columns.push_back(p);
				for (i = 0; i < strlen(p); i++)
				{
					tableInfo[id + i] = p[i];
				}
				tableInfo[id + i] = ' ';
				id = id + (int)strlen(p) + 1;
				//id = id + (int)strlen(p);
			}
			strcpy(command, command + strlen(p) + 1);
			commandType(command, &tokenType);
			bool isType = false;
			isType = (tokenType == INT || tokenType == FLOAT || tokenType == CHAR);
			if (isType == false)
			{
				printf("ERROR: column type expected '%s' \n", p);
				return 0;
			}
			else
			{
				if (tokenType == INT)
				{
					/*Column c1;
					intColumn c2;
					intColumn *cint = (intColumn *) &c1;
					cint->intColumnCreate(tableInfo);
					tableInfo[id + 1] = ' ';
					id++;*/
					//tableInfo[id] = 'I';
					//tableInfo[id + 1] = ' ';
					//Column c;
					//c.sint.insert(tableInfo);
					//strcat(tableInfo, "INT ");id = id + 4;tip = 1;
					columnType.push_back("INT");
				}
				else
				{
					if (tokenType == FLOAT)
					{
						//tableInfo[id] = 'F';
						//tableInfo[id+1] = ' ';
						//strcat(tableInfo, "FLOAT ");
						//id = id + 6;
						//tip = 2;
						columnType.push_back("FLOAT");
					}
					else
						if (tokenType == CHAR)
						{
							strcpy(command, command + 5);
							commandType(command, &tokenType);
							if (tokenType != '(')
							{
								printf("ERROR: Missing ( \n");
								return 0;
							}
							else
							{
								strcpy(command, command + 2);
								commandType(command, &tokenType);
								if (tokenType != INTEGER_NB)
								{
									printf("ERROR: size '%d' integer expected \n", tokenType);
									return 0;
								}
								else
								{
									//tableInfo[id] = 'C';
									//tableInfo[id + 1] = ' ';
									//strcat(tableInfo, "CHAR ");
									//id = id + 5;
									//tip = 3;
									columnType.push_back("CHAR");
									strcat(tableInfo, p);
									strcpy(command, command + strlen(p) + 1);
									commandType(command, &tokenType);
									if (tokenType != ')')
									{
										printf("ERROR: Missing '%d' '%s' ) \n", tokenType, p);
										return 0;
									}
								}
							}
						}
				}

			}
			strcpy(command, command + strlen(p) + 1);
			commandType(command, &tokenType);
			if (tokenType == ')')
			{
				ok = 1;
				strcpy(command, command + 2);
				break;
			}

		} while (tokenType == ',');
		if (!ok)
		{
			printf("ERROR: Missing ) \n");
			return 0;
		}

	}
	return 1;
}