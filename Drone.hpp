/**
 * \class Drone
 * @file Drone.hpp
 *
 * @authors Radoslaw Kierzkowski zadek, Wojciech Mielczarek kermit10000000
 *
 */

#ifndef Drone_HPP
#define Drone_HPP

#include <string>

class Drone{

private: 
 /**
  * @brief  parameters
  * width is the drone width
  * length is the drone length
  * speed is the drone speed
  * movementDirection is the direction in which the
  * drone moves
  * 
  */
    const std::size_t width=20;
    const std::size_t lenght=20;
    std::size_t speed;
    std::string movementDirection;
    
public:   
/**
 * @brief Constructor of Drone code object
 * none params are needed
 * 
 */
    Drone();


 
 /**
  * @brief fly
  *
  * @return nothing
  */
    void fly();
    
/**
  * @brief Setter for param speed
  *
  * @return nothing
  */
    void setSpeed(std::size_t speed);
    
/**
  * @brief Setter for param movementDirection
  *
  * @return nothing
  */
    void setMovementDirection(std::string movementDirection);

};

#endif // Drone_HPP

