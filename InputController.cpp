#include<InputController.h>
#include<Arduino.h>

InputController::InputController()
{
	init();
}
void InputController::init()
{
  pinMode(PUSH,INPUT_PULLUP);
  pinMode(BTN1,INPUT_PULLUP);
  pinMode(BTN2,INPUT_PULLUP);
  pinMode(CMD1,OUTPUT);
  pinMode(CMD2,OUTPUT);
  pinMode(A0,INPUT);
  digitalWrite(CMD1, LOW);
  digitalWrite(CMD2,LOW);
  currentInput=0;
}

int InputController::getBtn1()
{
	if((currentInput&CONTROLS_BTN1) !=0)
	{
		return 1;
	}
	return 0;
}

int InputController::getBtn2()
{
	if((currentInput & CONTROLS_BTN2) !=0)
		return 1;
	return 0;
}

int InputController::getPush()
{
	if((currentInput & CONTROLS_PUSH)!=0)
		return 1;
	return 0;
}

int InputController::getUp()
{
	if((currentInput & CONTROLS_UP)!=0)
		return 1;
	return 0;
}

int InputController::getDown()
{
	if((currentInput & CONTROLS_DOWN)!=0)
		return 1;
	return 0;
}

int InputController::getLeft()
{
	if((currentInput & CONTROLS_LEFT)!=0)
		return 1;
	return 0;
}

int InputController::getRight()
{
	if((currentInput & CONTROLS_RIGHT)!=0)
		return 1;
	return 0;
}
void InputController::readInput()
{
	currentInput=0;
	
  digitalWrite(CMD1,HIGH);
  int val1=analogRead(A0);
  digitalWrite(CMD1,LOW);
  digitalWrite(CMD2,HIGH);
  int val2=analogRead(A0);
  digitalWrite(CMD2,LOW);
  int push = digitalRead(PUSH);
  int b1=digitalRead(BTN1);
  int b2=digitalRead(BTN2);
  
  if(b1 == LOW)
  {
	  currentInput |= CONTROLS_BTN1;
  }
  if(b2 == LOW)
  {
	  currentInput |= CONTROLS_BTN2;
  }
  if(push == LOW)
  {
	  currentInput |= CONTROLS_PUSH;
  }
  
  
  if(val1 < 200)
  {
	currentInput |= CONTROLS_LEFT;
  }
  if(val1 > 800)
  {
	currentInput |= CONTROLS_RIGHT;  
  }
  
  if(val2 < 200)
  {
	currentInput |= CONTROLS_DOWN;
  }
  if(val2 > 800)
  {
	currentInput |= CONTROLS_UP;  
  }
  
  
}

InputController Controls;

