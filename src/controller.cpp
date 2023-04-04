/**
 * @brief Implementation of controller class
 * 
 */

#include <iostream>
#include <string>
#include <thread>
#include "elevator.h"
#include "controller.h"
#include <functional>
#include <string>
#include <sstream>
#include <chrono>

Controller::Controller()
{
    for (int i=0;i<5;i++) //TODO 
    {
        Elevator temp;
        elevator.push_back(temp);
    }
}

Controller::Controller(int numElevator)
{
    
    for (int i=0;i< numElevator;i++)
    {
        Elevator temp;
        elevator.push_back(temp);
    }
  

}

void Controller::simulate()
{
    //creating threads
    std::vector<std::thread> runningElevator;
    for (auto it=elevator.begin();it!=elevator.end();++it)
    {
        std::thread th(std::bind(&Elevator::run, it));
        runningElevator.push_back(std::move(th));
    }
    std::cout<<"Running elevators. Please wait..."<<std::endl;
    if(checkIfRunning())
    {
        std::cout<<"All elevators are now running."<<std::endl;
        cli();
    }
    else
    {
        std::cout<<"Could not run elevators. Some error occured. Please try again"<<std::endl;
        exit(1);
    }

    //joining threads
    for (unsigned int i=0; i< runningElevator.size(); ++i)
    {
        if (runningElevator[i].joinable())
        {
            runningElevator.at(i).join();
        }
    }
}

bool Controller::checkIfRunning()
{
    unsigned int count=0;
    while(count!=elevator.size())
    {
//std::this_thread::sleep_for (std::chrono::seconds(2));
        count=0;
        for(auto it=elevator.begin();it!=elevator.end();++it)
        {
            if(it->getifrunning())
            {
                count++;
            }
        }
    }
    if (count==elevator.size())
    {
        return true;
    }
    else
    {
        return false;
    }    
}

void Controller::cli()
{
    bool status=0;
    while(1)
    {
        std::string input;
        std::cout<<"Enter a command ('help' for usage): "<<std::endl;

        std::string allwords;
        std::getline(std::cin, allwords);
        if(allwords.empty())
        {
            printStatus();
        }
        // Parse words into a vector
        std::vector<std::string> word;
        std::string mystring;
        std::istringstream iss(allwords);
        while(iss >> mystring) word.push_back(mystring);

        if(word.size()==1)
        {
            if(word[0].compare("status")==0)
            {
                printStatus();
            }

            else if(word[0].compare("exit")==0)
            {
                exit(1);
            }

            else if(word[0].compare("help")==0)
            {
                std::cout<<"usage:"<<std::endl; 
                std::cout<<"<Elevator_ID> <Requested_floor> - Make a floor request to an elevator"<<std::endl;
                std::cout<<"eg: '1 4' - makes a request to elevator 1, for floor 4"<<std::endl;
                std::cout<<"'help' - show help message"<<std::endl;
                std::cout<<"'status' or press enter - show status chart of elevators"<<std::endl;
                std::cout<<"'exit' - stop service"<<std::endl;
            }
            else
            {

            }
        }

        else if(word.size()==2)
        {
            int first = atoi(word[0].c_str());
            int second = atoi(word[1].c_str());
            if(first>=0 && first<(int)elevator.size() && second>=0 && second<=elevator[first].getNoOfFloors())
            {   status=false;
                std::cout<<"Making request. Please wait..."<<std::endl;
                do
                {
                    status=elevator[first].requestHandler(second);
                }
                while(status==false);
                if (status==true)
                {
                    std::cout<<"Request made - Elevator "<<first<<" to floor "<<second<<std::endl;
                    status=false;
                }
                else
                {
                    std::cout<<"Request unsuccesful. Try again."<<std::endl;
                }
            }

            else
            {
                std::cout<<"Request unsuccesful. Try again."<<std::endl;
            }
        }
        else
        {
            
        }
    }
}


void Controller::printStatus()
{
    std::cout<<"ID\tCurrent\tNext\tStatus"<<std::endl;
    for(auto it = elevator.begin();it!=elevator.end();++it)
    {
        it->printAll();
    }
}