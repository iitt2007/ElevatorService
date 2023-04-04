# Elevator Service

## About
This program uses up to 2 elevators (running as mutliple threads). It takes requests (call or drop-off) from the user and shows the status of elevators. 

## Build instructions and usage
1. Clone repository
```
git clone <>
cd elevator
```
2. Inside repository (install CMake first)
```
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```
3. Run executable
```
./elevatorservice
```

## Code Description
`/include`

  `controller.h`: Controller class header. Represents a controller object. A controller acts as an interface that simulates multiple elevators, takes requests from the user and shows the status of the elevators.
  
  `elevator.h`: Elevator class header. Represents an elevator object, along with its scheduling and request handling methods.

`/src`

  `controller.cpp`: Implementation of the controller class
  
  `elevator.cpp`: Implementation of the elevator class
  
  `elevatorservice.cpp`: Contains the `main()` function

## Scheduling algorithm
Keep moving in one direction until there are no more requests in that direction. Then reverse the direction. 

Requests made to an elevator are handled in `Elevator::requestHandler(int floor)`, which places the requested floor in sets `upList` or `downList`.

`Elevator::run()` continuously checks if there are pending requests in `upList` or `downList`. It continues moving the elevator in one direction until the request list for that direction is empty, then changes direction.


## Further improvements
This sample POC  was designed in a short time period with minimal business rules and can be improved and optimized. 
This can also be implemented as  FCFS.
The object oriented design and general functionality can be improved. 

TODO :
sample BR  : 
1. Improve Scheduling algorithm
   1.1 If elevator 1 is going up, it should  continue going up 
2. Improve elevator class
     2.1 Count people in the elevator
     2.2 List of people waiting on each floor
3. Improve controller 
    3.1 Add more business rules
4. Decouple business rules - may be define business rules in JSON file, and consume JSON in the application
5. Make design scalable
6. Performance enhancements
    


