#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#pragma once

using namespace std;

class TextFile
{
private:
    char* fileName;
    char* info;
public:
    /*TextFile()
    {
        fileName = nullptr;
        info = nullptr;
    }
    TextFile(char* fileName)
    {
        this->fileName = new char[strlen(fileName) + 1];
        strcpy(this->fileName, fileName);
    }*/
    void fileTextCreate(char* fileName, char* info);
    void fileTextDrop(char* fileName, int& rez);
    void fileTextDisplay(char* fileName, char* info);
    char* getFileName();
    void setFileName(char* fileName);
    char* getInfo();
    void deserialization(char* fileName, char* info);
};

class TextFileCommands : public TextFile
{
public:
    void fileTextRead(int argc, char* argv[], int i);
};
