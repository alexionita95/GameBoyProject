#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H

#include<Arduino.h>
#include<TextBox.h>
#include<ListBox.h>

#include <ESP8266WiFiMulti.h>


enum ConfigState
{
	NET_SELECTING, NET_PASSOWRD
};
class WIFIManager
{
public:
WIFIManager()
{
}
void init();
void run();
void download(String file);
String getGameList();

private:
ESP8266WiFiMulti WiFiMulti;
ConfigState state;
ListBox netList;
TextBox passwordText;

void WiFiConnect();
void WiFiConnect(String ssid, String pwd);

};
extern WIFIManager NetworkManager;
#endif