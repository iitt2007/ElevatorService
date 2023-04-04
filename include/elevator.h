/**
 * @brief Elevator class header.
 * 
 * @file elevator.h
 */

#ifndef ELEVATOR
#define ELEVATOR

#include <vector>
#include <set>
#include <chrono>
#include <ctime>
#include <set>
#include <mutex>

/**
 * @brief Represents an elevator object, along with its scheduling and request handling methods.
 * 
 */
class Elevator
{
public:
    static int generateID;
    /**
     * @brief Construct a new Elevator object 
     */
    Elevator();

    /**
     * @brief Runs the elevator. 
     * 
     */
    void run();

    /**
     * @brief Inserts pickup and drop requests in UpList or DownList. 
     * 
     * @param floor: The floor number requested for
     * @return true If request was succesfully handled
     * @return false 
     */
    bool requestHandler(int floor);

    /**
     * @brief Moves the elevator
     * 
     */
    void goUp();
    void goDown();
    void openDoor();
    void closeDoor();


    int getState() const;
    int getCurrent() const;
    int getNext() const;
    int getElevatorID() const;
    int getNoOfFloors() const;

    bool getifrunning() const;

    void printAll() const;    

    enum ElevatorState
    {
        STOPPED_OPEN,
        STOPPED_CLOSED,
        MOVING_UP,
        MOVING_DOWN,
    };

    enum ElevatorDirection
    {
        UP,
        DOWN,
    };

private:
    int elevatorID;
    int noOfFloors;

    int current;
    int next;

    std::set<int> upList;
    std::set<int> downList;

    ElevatorState state;
    ElevatorDirection direction;

    bool isrunning;
};

#endif