#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include<Arduino.h>

#define CONTROLS_UP 0x01
#define CONTROLS_DOWN 0x02
#define CONTROLS_LEFT 0x04
#define CONTROLS_RIGHT 0x08
#define CONTROLS_PUSH 0x10
#define CONTROLS_BTN1 0x20
#define CONTROLS_BTN2 0x40

#define CMD1 10
#define CMD2 9
#define PUSH 5
#define BTN1 4 //Black
#define BTN2 2 //Red

class InputController
{
public:
InputController();
void readInput();

int getBtn1();
int getBtn2();
int getPush();
int getUp();
int getDown();
int getLeft();
int getRight();
private:
void init();

int currentInput;
};
extern InputController Controls;
#endif