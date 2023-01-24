#define _CRT_SECURE_NO_WARNINGS
#include "TextFile.h"

class VectorFile
{
public:
	TextFile* files;
	int fileNumber = 0;

	void addFileCreated();
};
