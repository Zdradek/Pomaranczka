//
// main.c
//

#include "main.h"
#include "stdio.h"


char credits[51]="        RPiLAB                DEMO                ";
long TimerIsrPeriod = 1;            //czas podany w milisekundach

int reset = 0;
Drone drone;
unsigned long* SCREEN;
unsigned long SCREENBUF[640 * 480];
int mode = 0;
int stage = 0;
int frame_count = 0;

int main(void) {
	if (SystemInit())		return EXIT_HALT;
	drone.setSpeed(5);
	while (1) {
		if (UpdateIO())	return 0;
		PrintDiagnosticInfo();
		Synchronize();
		ClearScreen();
		unsigned long* GRAPH = SCREENBUF;
        if(!reset) {
            drone.printDrone(GRAPH);
        }
        else {
            std::size_t writeSucceded=drone.WriteToFile();
            if(writeSucceded);
            reset=0;
        //    drone.pos_x=300;
       //     drone.pos_y=BOARD_MAX_HEIGHT-drone.getHeight();
       //     drone.pos_y=200;
        }
		if (JoYAct.ButtonStates & BUTTON_SELECT) continue;

	}
}

volatile long presc = 0, presc2 = 0;
void DataPrepare(){

}
void TimerIsr() {
	presc++;
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
	sprintf(strbuf,"%i: %i, %x\r\n",frame_count,getKey(), JoYAct.ButtonStates);
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

