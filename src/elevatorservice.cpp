/**
 * @brief This program service (running as mutliple threads). 
 * It takes requests (call or drop-off) from the user 
 */

#include <iostream>
#include "elevator.h"
#include "controller.h"
#include <thread>

using namespace std;

#define numElevators 2
int main(int argc, char* argv[])
{

    //started controller
    Controller myController(numElevators);
    
    //starting service
    myController.simulate();
    return 0;
}