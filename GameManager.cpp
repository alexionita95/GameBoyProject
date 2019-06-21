#include<GameManager.h>
#include<Colors.h>
#include<ShapeRenderer.h>
#include<TextRenderer.h>

#include <FS.h>
#include <System.h>
#include<TextBox.h>
#include<ListBox.h>
#include<Header.h>
#include<Footer.h>
#include<Keyboard.h>
#include<InputController.h>
#include<WIFIManager.h>

void GameManager::init()
{
	
	Top.setTitle("GAME LIBRARY");
	Bottom.setTopText("JOYSTICK - UP/DOWN");
	Bottom.setBottomText("PUSH - Select Game to Download/Play");
	Text.setTextColor(TFT_WHITE);
	Text.drawString("GAMES",10,42,2);

	netList = ListBox(5,60,230,180,0);
	netList.render();
	String result=NetworkManager.getGameList();
	
	if(result != ""){
	int gameCount;
	char** games=splitString(result.c_str(),&gameCount,"\n");
	Serial.println(gameCount);
	int n = gameCount;
	
	if (n == 0) {
	netList.setItemCount(1);
    netList.addItem("No Games");
	} else {
    netList.setItemCount(n);
	files=(char**)malloc(n*sizeof(char*));
    for (int i = 0; i < n; ++i) {
      // Print SSID and RSSI for each network found

	  int items;
	  char** currentGame=splitString(games[i],&items,"|");
	  netList.addItem(currentGame[1]);
	  Serial.println(currentGame[2]);
	  files[i]=(char*)malloc(strlen(currentGame[i])*sizeof(char));
	  strcpy(files[i],currentGame[2]);
	  	  	if(Sys.getInstalledGame()!=0)
		{
			if(i+1==Sys.getInstalledGame())
			{
				
				String str="Instaled game: " + String(currentGame[1]);
				Text.drawString(str,10,245,2);
			}
		}
    }
  }
  
	//download(String(files[netList.getSelectedIndex()]));
	
	
	netList.render();
	netList.update();

	
	}
}
void GameManager::run()
{
	
	while(Sys.getState()==GAME_SELECT)
	{
		
		Controls.readInput();
			 if(Controls.getDown()==1)
			{
				netList.setSelectedIndex(netList.getSelectedIndex()+1);
			}
			if(Controls.getUp()==1)
			{
				netList.setSelectedIndex(netList.getSelectedIndex()-1);
			}
			if(Serial.available())
			{
				byte ser=Serial.read();
				if(ser =='a'){
					NetworkManager.download("gboy");
				return;
				}
			}
		if(Controls.getPush()==1)
		{
			if(Sys.getInstalledGame() != netList.getSelectedIndex()+1)
				//download("gboy");
				NetworkManager.download(String(files[netList.getSelectedIndex()]));
			else
			Sys.setState(CUSTOM_STATE);	
		}
		netList.update();
		delay(200);
	}

	
}


char** GameManager::splitString(const char* string, int* count, const char* separator)
{

	int cnt = 0;
	char* aux = (char*)malloc(strlen(string) * sizeof(char));
	strcpy(aux, string);
	char* ptr = strtok(aux, separator);
	while (ptr != NULL)
	{
		cnt++;
		ptr = strtok(NULL, separator);
	}
	char** result;
	result = (char**)malloc(cnt * sizeof(char*));
	int currentIndex = 0;
	strcpy(aux, string);
	ptr = strtok(aux, separator);
	while (ptr != NULL)
	{
		result[currentIndex] = (char*)malloc(strlen(ptr) * sizeof(char));
		strcpy(result[currentIndex], ptr);
		ptr = strtok(NULL, separator);
		currentIndex++;
	}
	*count = cnt;
	return result;
}

GameManager GameLibrary;


