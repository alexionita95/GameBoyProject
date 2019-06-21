#include<WIFIManager.h>
#include<Colors.h>
#include<ShapeRenderer.h>
#include<TextRenderer.h>
#include "ESP8266WiFi.h"
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <WiFiClient.h>
#include <FS.h> 
#include <System.h>
#include<TextBox.h>
#include<ListBox.h>
#include<Header.h>
#include<Footer.h>
#include<Keyboard.h>
#include<InputController.h>
#include<Dialog.h>

void WIFIManager::init()
{
	WiFi.mode(WIFI_STA);
	WiFi.disconnect();
	delay(100);
	
	const char* filename = "/netconfig.txt";
	String ssid="";
	String pwd="";
	if(SPIFFS.begin())
	{
		Serial.println("SPIFFS Initialize....ok");
	}
	else
	{
		Serial.println("SPIFFS Initialization...failed");
	}
		

	File f = SPIFFS.open(filename, "r");
  
  if (!f) {
    Serial.println("file open failed");
	}
	else
	{
      Serial.println("Reading Data from File:");
      //Data from file
      while(f.available()) {
      //Lets read line by line from the file
      ssid = f.readStringUntil('\n');
      pwd=f.readStringUntil('\n');
      Serial.println(ssid);
      Serial.println(pwd);
    }
      f.close();  //Close file
      Serial.println("File Closed");
	}
	if(ssid != "")
	{
		WiFiConnect(ssid,pwd);
		return;
	}
	
	Sys.setState(NETWORK_SETUP);
	state=NET_SELECTING;
	Top.setTitle("WIFI CONNECT");
	Bottom.setTopText("JOYSTICK - UP/DOWN");
	Bottom.setBottomText("PUSH - Select Network");
	passwordText=TextBox(10,180,220,20);
	Text.setTextColor(TFT_WHITE);
	Text.drawString("NETWORKS",10,42,2);
    Text.drawString("PASSWORD:",10,165,2);
	
	netList = ListBox(5,60,230,100,0);
	netList.render();
	passwordText.render();
	Keys.render();
	int n = WiFi.scanNetworks();
	if (n == 0) {
    netList.addItem("No Networks");
	} else {
    netList.setItemCount(n);
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found
      netList.addItem(WiFi.SSID(i).c_str());
     
    }
  }
  
  
	netList.render();
	Keys.render();
	netList.update();
	Keys.update();
}
void WIFIManager::run()
{
	while(Sys.getState()==NETWORK_SETUP)
	{
		Controls.readInput();
		if(state==NET_SELECTING)
		{
			 if(Controls.getDown()==1)
			{
				netList.setSelectedIndex(netList.getSelectedIndex()+1);
			}
			if(Controls.getUp()==1)
			{
				netList.setSelectedIndex(netList.getSelectedIndex()-1);
			}
		if(Controls.getPush()==1)
		{
			state=NET_PASSOWRD;
			Bottom.setTopText("JOYSTICK-U/D/L/R PUSH-Select Key");
			Bottom.setBottomText("Black-Delete Red-Connect");
		}
			
		}
		if(state==NET_PASSOWRD)
		{
			if(Controls.getDown()==1)
			{
				Keys.setSelKey(Keys.getSelRow()+1,Keys.getSelCol());
			}
		if(Controls.getUp()==1)
		{
			Keys.setSelKey(Keys.getSelRow()-1,Keys.getSelCol());
		}
		if(Controls.getRight()==1)
		{
			Keys.setSelKey(Keys.getSelRow(),Keys.getSelCol()+1);
		}
		if(Controls.getLeft()==1)
		{
			Keys.setSelKey(Keys.getSelRow(),Keys.getSelCol()-1);
		}
		if(Controls.getPush()==1)
			Keys.addToCurrentWord();

		if(Controls.getBtn1()==1)
			Keys.backspace();
		if(Controls.getBtn2()==1)
			WiFiConnect();
		}
		passwordText.setText(Keys.getCurrentWord());
		Keys.update();
		netList.update();
		delay(200);
	}
	
}

void WIFIManager::WiFiConnect()
{
	
	WiFi.mode(WIFI_STA);
	Sys.setSSID(String(netList.getSelectedItem()));
	Sys.setPWD(Keys.getCurrentWord());
	WiFiMulti.addAP(netList.getSelectedItem(), Keys.getCurrentWord().c_str());
	
	WiFi.begin();
	Bottom.setTopText("Connecting...");
	Bottom.setBottomText("");
	while(WiFiMulti.run() != WL_CONNECTED)
	{
		delay(100);
	}
	if ((WiFiMulti.run() == WL_CONNECTED)){
	Top.render();

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
	Sys.setState(GAME_SELECT);
	Bottom.setTopText("Connection succes!");
	}
}
void WIFIManager::WiFiConnect(String ssid, String pwd)
{
	ssid.trim();
	pwd.trim();
	Sys.setSSID(ssid);
	Sys.setPWD(pwd);
	Serial.println(ssid);
	Serial.println(pwd);
	WiFi.mode(WIFI_STA);
	WiFiMulti.addAP(ssid.c_str(), pwd.c_str());
	
	WiFi.begin();
	Bottom.setTopText("Connecting...");
	Bottom.setBottomText("");
	while(WiFiMulti.run() != WL_CONNECTED)
	{
		delay(100);
	}
	if (WiFiMulti.run() == WL_CONNECTED){
	Top.render();

	Sys.setState(GAME_SELECT);

	Bottom.setTopText("Connection succes!");
	}
	else
	{
		Bottom.setTopText("Connection error!");
	}
}

String WIFIManager::getGameList()
{
	String result="";
	if (WiFiMulti.run() == WL_CONNECTED){
	 WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://serverfiles.hi2.ro/gameboy/games.txt")) {  // HTTP

      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();
      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          result = http.getString();
          Serial.println(result);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
	}
	else
	{
		Serial.printf("Bad stuff\n");
	}
	return result;
}

void WIFIManager::download(String file)
{
	if(	SPIFFS.begin())
	{
			SPIFFS.remove("/update.txt");
			SPIFFS.remove("/netconfig.txt");
	}
	String uri="http://serverfiles.hi2.ro/gameboy/files/"+file +".bin";

			
			File net=SPIFFS.open("/netconfig.txt", "w");
			if(net)
			{
				net.print(Sys.getSSID()+"\n");
				net.print(Sys.getPWD()+"\n");
				net.close();
			}
	Serial.println(uri);
	if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;


    ESPhttpUpdate.setLedPin(LED_BUILTIN, LOW);

    t_httpUpdate_return ret = ESPhttpUpdate.update(client, uri);
	Serial.println("Downloading...");
    // Or:
    //t_httpUpdate_return ret = ESPhttpUpdate.update(client, "server", 80, "file.bin");

    switch (ret) {
      case HTTP_UPDATE_FAILED:
	  {
		File f = SPIFFS.open("/update.txt", "w");
	
		if (!f) {
				Serial.println("file open failed");
			}
			else
			{
				 f.print(file);
				 f.close();
			}
        Bottom.setBottomText("Reset the device");
		Dialog::show("Reboot device","Press the Reset button","to install the game");

	  }
        break;

      case HTTP_UPDATE_NO_UPDATES:
        Bottom.setBottomText("WTFFFFFFF");
        break;

      case HTTP_UPDATE_OK:
        Bottom.setBottomText("Are you here?");
        break;
    }
  }
  else
  {
    Bottom.setBottomText("Error!");
    delay(1000);
  }
}

WIFIManager NetworkManager;


