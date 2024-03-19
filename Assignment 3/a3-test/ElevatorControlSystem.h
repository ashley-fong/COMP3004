#ifndef ELEVATORCONTROLSYSTEM_H
#define ELEVATORCONTROLSYSTEM_H

using namespace std;

#include "defs.h"
//#include "Elevator.h"
//#include "Floor.h"
//#include "Passenger.h"
#include <iostream>
#include <unistd.h>
#include <QtGlobal>

 class Floor;
 class Elevator;
 class Passenger;


class ElevatorControlSystem {

public:
    ElevatorControlSystem(int totalFloors, int totalElevs, int totalPass);
    ~ElevatorControlSystem();
    void sendElev(int elevNum);
    int closestElev(int floorNum, char direction);
    int requestAt(int floorNum, char direction);
    void openDoors(int floorNum, int elevNum);
    void closeDoors(int floorNum, int elevNum);
    void buildingSafety(int elevNum);
    void call911();
    bool overload(int weight, int elev);
    void fire(bool fromBuilding, int elevator_number);
    void powerOut();
    void doorObstacle(int elev);
    Elevator* getElevator(int elevNum);
    Floor* getFloor(int floorNum);
    Passenger* getPassenger(int passNum);

private:
    int totalFloors;
    int totalElevs;
    int totalPass;
    Floor** floors;
    Elevator** elevators;
    Passenger** passengers;
};

#endif
