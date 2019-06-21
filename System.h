#ifndef SYSTEM_H
#define SYSTEM_H
#include <Arduino.h>
enum State
{
	NETWORK_SETUP,GAME_SELECT,CUSTOM_STATE
};
class System
{
	private:
	String SSID;
	String PWD;
	State st;
	int installedGame;
	public:
	System();
	void setState(State val);
	State getState();
	String getSSID();
	String getPWD();
	void setSSID(String val);
	void setPWD(String val);
	int updateAvailable();
	void installUpdate();
	void setInstalledGame(int value);
	int getInstalledGame();
};
extern System Sys;

#endif