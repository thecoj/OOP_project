#define _CRT_SECURE_NO_WARNINGS
#include "TextFile.h"

class VectorFiles
{
public:
	TextFile* files;
	int noFiles = 0;

	void addFileCreated();
};
