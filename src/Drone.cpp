/**
 * \class Drone
 * @authors Radoslaw Kierzkowski zadek, Wojciech Mielczarek kermit10000000
 *
 */

#include "Drone.h"


Drone::Drone() {
    this -> coordinates.reserve(5000);
    this -> pos_x = BOARD_MAX_WIDTH-getWidth();
    this -> pos_y = BOARD_MAX_HEIGHT-getHeight();
}

void Drone::setSpeed(const std::size_t &speed) {
    this -> speed = speed;
}

void Drone::setCoordinates(const double &time){
    Txtparams params;
    std::stringstream time_s;
    time_s << time;
    std::stringstream pos[2];
    pos[0] << this -> pos_x;
    pos[1] << BOARD_MAX_HEIGHT - this -> pos_y - getHeight();
    params.time = time_s.str();
    std::size_t dot_pos;
    if((dot_pos = params.time.find(".")) != std::string::npos){
    	params.time.replace(params.time.begin() + dot_pos, params.time.begin() + dot_pos + 1, ",");
    }
    params.pos_x = pos[0].str();
    params.pos_y = pos[1].str();
    this -> coordinates.push_back(params);
}


void Drone::fly(const unsigned short &Key) {
	switch(Key){
	case KEY_Pressed_0:
		pos_y+=getSpeed();
		break;
	case KEY_Pressed_5:
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
    std::ofstream fileWithCoordinates;
    bool succededToWrite=false;
    fileWithCoordinates.open("coordinates.txt", std::ios::out | std::ios::trunc);
    if(fileWithCoordinates.is_open()){
        std::vector<Txtparams>::iterator pos;
        for(pos=coordinates.begin();pos!=coordinates.end();pos++){
            fileWithCoordinates << pos->time << " " << pos->pos_x << " " << pos->pos_y << "\n"; 
        }
        succededToWrite=true;
    }
    fileWithCoordinates.close();
    return succededToWrite;
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
