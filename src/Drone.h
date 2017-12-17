/**
 * \class Drone
 * @file Drone.hpp
 *
 * @authors Radoslaw Kierzkowski zadek, Wojciech Mielczarek kermit10000000
 *
 */


#ifndef Drone_HPP
#define Drone_HPP

#define BOARD_MAX_WIDTH 640
#define BOARD_MAX_HEIGHT 480

#define KEY_Pressed_0 0x62
#define KEY_Pressed_1 0x59
#define KEY_Pressed_3 0x5b
#define KEY_Pressed_4 0x5c
#define KEY_Pressed_5 0x5d
#define KEY_Pressed_6 0x5e
#define KEY_Pressed_7 0x5f
#define KEY_Pressed_8 0x60
#define KEY_Pressed_9 0x61
#define KEY_Pressed_kreska 0x54
#define KEY_Pressed_enter 0x58

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <fstream>

struct Txtparams{
    std::string time;
    std::string pos_x;
    std::string pos_y;
};

class Drone {

private: 
 /**
  * @brief  parameters
  * width is the drone width
  * height is the drone height
  * speed is the drone speed (how many pixels per each keyboard move)
  * movementDirection is the direction in which the
  * drone moves
  * 
  */
    const static std::size_t width = 20;
    const static std::size_t height = 20;
    const static long color = 0xff00ff;
    std::size_t speed = 1;
    std::vector <Txtparams> coordinates;
    
public:

    static const std::size_t centerOfGravity_x=width/2;
    static const std::size_t centerOfGravity_y=height/2;
    std::size_t pos_x;
    std::size_t pos_y;
/**
 * @brief Constructor of Drone code object
 * none params are needed
 * 
 */
    Drone();
 
 /**
  * @brief movement of the Drone
  *
  * @return nothing
  */
    void fly(const unsigned short &Key);
    
/**
  * @brief prints alert message in case of failure
  *
  * @return nothing
  */
    void printAlert();

/**
  * @brief prints Drone on the board
  * @param GRAPH - table of the simulation
  * @return nothing
  */
    void printDrone(unsigned long *GRAPH);
    
/**
  * @brief Setter for param speed
  * @param speed - speed of the drone
  *
  * @return nothing
  */
    void setSpeed(const std::size_t &speed);
    
/**
  * @brief Setter for param speed
  *
  * @return speed
  */
    std::size_t getSpeed();
    
/**
  * @brief Setter for param speed
  *
  * @return speed
  */
    std::size_t getHeight();

/**
  * @brief Setter for param speed
  *
  * @return speed
  */
    std::size_t getWidth();
/**
  * @brief Setter for param setCoordinates
  * @param time - time stamp for each pos_x & pos_y read
  * @return nothing
  */
    void setCoordinates(const double &time);
    
/**
  * @brief Function to write coordinates to file
  *
  * @return if proccess success
  */
    bool WriteToFile();
};

#endif // Drone_HPP

