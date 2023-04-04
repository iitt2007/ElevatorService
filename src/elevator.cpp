/**
 * @brief Implementation of elevator class
 */

#include <iostream>
#include <set>
#include "elevator.h"
#include <chrono>
#include <ctime>
#include <algorithm>
#include <mutex>

int Elevator::generateID=0;


Elevator::Elevator()
{
    noOfFloors=5;
    elevatorID=generateID++;
    current=0;
    next=0;

    state=STOPPED_CLOSED;
    direction=UP;

    isrunning=0;
}

void Elevator::run()
{
    isrunning=true;
    while(true)
    {
        //list_mutex.lock();
        
        //if direction set to up
        if(direction==UP)
        {   //if list has floors
            if (!upList.empty())
            {   
                //destination set to lowest floor in uplist
                auto it=upList.begin();
                next=*it;
                //go up if you haven't arrived at destination
                if(current<next)
                {
                    goUp();
                }
                //if you've arrived, open the door and remove that floor from the list
                if(current==next)
                {
                    openDoor();
                    upList.erase(it);
                    closeDoor();
                }
            }
            //if list is empty, reverse direction
            else
            {
                direction=DOWN;
            }
        }      
        //if direction set to down
        else if (direction==DOWN)
        {   
            //if list has floors
            if (!downList.empty())
            {
                //destination set to highest floor in downList
                auto it=downList.end();
                it--;
                next=*it;
                //go down if you haven't arrived at destination
                if(current>next)
                {
                    goDown();
                }
                //if arrived, open the door and remove floor from list
                if(current==next)
                {
                    openDoor();
                    downList.erase(it);
                    closeDoor();
                }
            }
            //if list is empty, reverse direction
            else
            {  
                direction=UP;
            }
        }
   
    }
}

bool Elevator::getifrunning() const
{
    return isrunning;
}

bool Elevator::requestHandler(int floor)
{   
    //if requested floor is below the current floor
    if(floor<current)
    {
        downList.insert(floor);
      
        return true;
    }

    //if requested floor is above the current floor
    else if(floor>current)
    {
        upList.insert(floor);
       
        return true;
    }

    //if request is for current floor
    else
    {
        if(state==STOPPED_OPEN)
        {
            //do nothing if doors are already open
        }
        else
        {
            //if its moving or its closed, add to queue in reverse direction
            if(direction==0)
            {
                downList.insert(floor);
                //list_mutex.unlock();
                return true;
            }
            else
            {
                upList.insert(floor);
                //list_mutex.unlock();
                return true;
            }
        }
    }
    return false;
}


void Elevator::goUp()
{
    state=MOVING_UP;
 
    current++;
}

void Elevator::goDown()
{
    state=MOVING_DOWN;

    current--;
}

void Elevator::openDoor()
{
    state=STOPPED_OPEN;
 
}

void Elevator::closeDoor()
{

    state=STOPPED_CLOSED;
}

int Elevator::getState() const
{
    return state;
}

int Elevator::getCurrent() const
{
    return current;
}

int Elevator::getNext() const
{
    return next;
}

int Elevator::getElevatorID() const
{
    return elevatorID;
}

int Elevator::getNoOfFloors() const
{
    return noOfFloors;
}

void Elevator::printAll() const
{
    std::cout<<elevatorID<<"\t"<<current<<"\t"<<next<<"\t";
    switch(state)
    {
        case 0:
            std::cout<<"STOPPED_OPEN"<<std::endl;
            break;
        case 1:
            std::cout<<"STOPPED_CLOSED"<<std::endl;
            break;
        case 2:
            std::cout<<"MOVING_UP"<<std::endl;
            break;
        case 3:
            std::cout<<"MOVING_DOWN"<<std::endl;
            
    }
}


