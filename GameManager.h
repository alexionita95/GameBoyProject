#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include<Arduino.h>
#include<ListBox.h>


class GameManager
{
public:
GameManager()
{
}
void init();
void run();
private:
ListBox netList;
char** files;

char** splitString(const char* string, int* count, const char* separator);

};
extern GameManager GameLibrary;
#endif