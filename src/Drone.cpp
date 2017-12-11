/**
 * \class Drone
 * @authors Radoslaw Kierzkowski zadek, Wojciech Mielczarek kermit10000000
 *
 */

#include "Drone.h"


Drone::Drone() {
    this -> coordinates.reserve(5000);
//    this -> pos_x = 0;
//    this -> pos_y = BOARD_MAX_HEIGHT-getHeight();
    this -> pos_x = 220;
    this -> pos_y = 300;
}

void Drone::setSpeed(const std::size_t &speed) {
    this -> speed = speed;
}

void Drone::setCoordinates(const long &time){
    Txtparams params;
    std::stringstream time_s;
    time_s << time;
    std::stringstream pos[2];
    pos[0] << this -> pos_x;
    pos[1] << this -> pos_y;
    params.time = time_s.str();
    params.pos_x = pos[0].str();
    params.pos_y = pos[1].str();
    this -> coordinates.push_back(params);
}


void Drone::fly(const unsigned short &Key) {
	switch(Key){
	case KEY_Pressed_5:
		pos_y+=getSpeed();
		break;
	case KEY_Pressed_0:
		pos_y-=getSpeed();
		break;
	case KEY_Pressed_3:
		pos_x+=getSpeed();
		break;
	case KEY_Pressed_1:
		pos_x-=getSpeed();
		break;
	};
}

void Drone::printAlert() {

}

bool Drone::WriteToFile(){
    std::ofstream fileWithCoordinates("coordinates.txt", std::ofstream::out | std::ofstream::trunc);
    if(fileWithCoordinates.is_open()){
        std::vector<Txtparams>::iterator pos;
        for(pos=coordinates.begin();pos!=coordinates.end();pos++){
            fileWithCoordinates << pos->time << " " << pos->pos_x << " " << pos->pos_y << "\n"; 
        }
    }
    fileWithCoordinates.close();
    return 1;
}

void Drone::printDrone(unsigned long *GRAPH){
    for (std::size_t x=0;x<height;x++){
        for (std::size_t y=0;y<width;y++) {
            GRAPH[x+pos_x+((y+pos_y)*640)]=color;
        }
    }
}

std::size_t Drone::getSpeed(){
    return this->speed;
}

    
std::size_t Drone::getHeight(){
    return this->height;
}

std::size_t Drone::getWidth(){
    return this->width;
}
