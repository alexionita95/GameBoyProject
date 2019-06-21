#include <System.h>

#include <Arduino.h>
#include <TextRenderer.h>
#include <WIFIManager.h>
#include <FS.h>
	System::System()
	{
		st=NETWORK_SETUP;
	}
	void System::setState(State val)
	{
		st=val;
	}
	State System::getState()
	{
		return st;
	}
	String System::getSSID()
	{
		return SSID;
	}
	String System::getPWD()
	{
		return PWD;
	}
	void System::setSSID(String val)
	{
		SSID=val;
	}
	void System::setPWD(String val)
	{
		PWD=val;
	}
	int System::updateAvailable()
	{
		if(SPIFFS.begin()){
		File f = SPIFFS.open("/update.txt", "r");
		
		if (f) 
		{
			f.close();
			return 1;
		}
	}
		return 0;
	}
	void System::installUpdate()
	{
		if(SPIFFS.begin())
		{
			File f = SPIFFS.open("/update.txt", "r");
			String test="";
			if (!f) {
				Serial.println("file open failed");
			}
			else
			{
				while(f.available()){
					test+=String((char)(f.read()));
				}
				 Serial.println("File: "+test);
				Text.setTextSize(1);
				Text.drawCenterString("Installing...",120,140,4);
				NetworkManager.download(test);
				f.close();
			}
		}
	else
	{
		Serial.println("Baaaaaad");
	}

}

void System::setInstalledGame(int value){
installedGame=value;
}
int System::getInstalledGame()
{
	return installedGame;
}

System Sys;
