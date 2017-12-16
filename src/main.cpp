//
// main.c
//

#include "main.h"
#include "stdio.h"


char credits[51]="        RPiLAB                DEMO                ";
long TimerIsrPeriod = 1;            //czas podany w milisekundach
std::string consoleInfromation;
int reset = 0;
Drone drone;
Plansza plansza;
unsigned long* SCREEN;
unsigned long SCREENBUF[640 * 480];
int mode = 0;
int stage = 0;
int frame_count = 0;

int main(void) {
	if (SystemInit())		return EXIT_HALT;
	strncpy(credits, "", sizeof(credits));
	drone.setSpeed(5);
	while (1) {
		if (UpdateIO())	return 0;
		PrintDiagnosticInfo();
		Synchronize();
		ClearScreen();
		unsigned long* GRAPH = SCREENBUF;
		if(!reset) {
			plansza.printPlansza(GRAPH);
			drone.printDrone(GRAPH);
		} else {
			if(drone.WriteToFile()){
				std::string saveInfo = "Data saved to file";
				strncpy(credits, saveInfo.c_str(), sizeof(credits));
			} else {
				std::string saveInfo = "Failed to save to file";
				strncpy(credits, saveInfo.c_str(), sizeof(credits));
			}
			reset=0;
			drone.pos_x=BOARD_MAX_WIDTH-drone.getWidth();
			drone.pos_y=BOARD_MAX_HEIGHT-drone.getHeight();
		}
		if (JoYAct.ButtonStates & BUTTON_SELECT) continue;
	}
}

volatile long presc = 0, presc2 = 0;
void DataPrepare(){

}
void TimerIsr() {
	presc++;
	presc2++;
	if ((presc / 250) % 2)
		RegisterSet(GPSET1, 1 << (35 - 32));
	else
		RegisterSet(GPCLR1, 1 << (35 - 32));
	if ((presc / 500) % 2)
		RegisterSet(GPSET1, 1 << (47 - 32));
	else
		RegisterSet(GPCLR1, 1 << (47 - 32));
	unsigned short Key= getKey();
	if(presc2==100){
		drone.fly(Key);
		drone.setCoordinates((long)presc);
		//8 will end the session
		if(Key==KEY_Pressed_8) {
			reset=1;
			presc2=0;
			return;
		}
		presc2=0;
	}
	if(presc>2000000000) {
		presc=0;
	}
}

void ClearScreen() {
	unsigned long bckgcol = 0;
	unsigned long* GRAPH = SCREENBUF;
	stage++;
	for (int a = stage % 1; a < (640 * 480); a += 1) {
		SCREEN[a] = GRAPH[a];
		GRAPH[a] = ((GRAPH[a] & 0xfefefe) >> 1) | bckgcol;
	}
}
void PrintDiagnosticInfo() {
	frame_count++;

	char strbuf[1000];
	sprintf(strbuf,"%s\r\n", credits);
	if((frame_count%20)==0) StringUart(strbuf);
}

int SystemInit()
{
	RegisterAccess(GPFSEL4,~(7<<21),1<<21);
	RegisterAccess(GPFSEL3,~(7<<15),1<<15);
	return 0;
}
int UpdateIO()
{
	GamePadGetStatus();
	KeyboardGetStatus();
	return SimulatorUpdate();
}

