/**
 * @brief Class declaration for Elevator Controller. 
 * 
 * @file controller.h 
 */

#ifndef CONTROLLER
#define CONTROLLER

#include <iostream>
#include <vector>
#include "elevator.h"

/**
 * @brief Take requests from the user and simulate multiple elevators.
 * 
 */
class Controller
{
public:
    /**
     * @brief Construct a new Controller object
     * 
     */
    Controller();

    /**
     *       
     * @param numElevators : The number of elevators you want
     */
    Controller(int numElevators);

    /**
     * @brief Simulates elevators with mutiple threads, 
     * 
     */
    void simulate();


    /**
     * @brief Prints status of elevators
     * 
     */
    void printStatus();
    
private:
    /**
     * @brief Vector of elevators
     * 
     */
    std::vector<Elevator> elevator;
    /**
     * @brief cli to be used in simulate()
     * 
     */
    void cli();
    /**
     * @brief Checks if the elevators are running
     * 
     * @return true 
     * @return false 
     */
    bool checkIfRunning();
};

#endif