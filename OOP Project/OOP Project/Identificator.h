#define _CRT_SECURE_NO_WARNINGS
enum Token
{
	IDENTIFICATOR = 128,
	INTEGER_NB,
	FLOAT_NB,
	STRING,

	ALL, CREATE, DELETE, DISPLAY, DROP, EXISTS, FLOAT, FROM, IMPORT, INDEX, INSERT, INT, INTO, NOT, ON, SELECT, SET, CSV, CHAR, TABLE, UPDATE, VALUES, WHERE
};

char* readCommands(char* in);
//char* commandLine(char* input);
void commandType(char* command, int* tokenType);