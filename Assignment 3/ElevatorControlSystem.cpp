#include "ElevatorControlSystem.h"
#include "Passenger.h"
#include "Elevator.h"
#include "Floor.h"

#include <iostream>
#include <unistd.h>
#include <QtGlobal>
using namespace std;

ElevatorControlSystem::ElevatorControlSystem(int totalFloors, int totalElevs, int totalPass)
    : totalFloors(7), totalElevs(3), totalPass(3) {

    floors = new Floor*[totalFloors+1];
    elevators = new Elevator*[totalElevs+1];
    passengers = new Passenger*[totalPass+1];

    for(int i = 1; i < totalFloors+1; i++){
        floors[i] = new Floor(i);
    }

    for(int i = 1; i < totalElevs+1; i++){
        elevators[i] = new Elevator(i, 1, false, false);
    }

    for(int i = 1; i < totalPass+1; i++){
        passengers[i] = new Passenger(i,1,false);
    }

    this->totalFloors = totalFloors;
    this->totalElevs = totalElevs;
    this->totalPass = totalPass; 
}

ElevatorControlSystem::~ElevatorControlSystem(){
    for(int i = 1; i <= totalFloors; i++){
        delete floors[i];
    }

    for(int i = 1; i <= totalElevs; i++){
        delete elevators[i];
    }

//    for(int i = 1; i <= totalPass; i++){
//        delete passengers[i];
//    }
}

int ElevatorControlSystem::closestElev(int floorNum, char direction){

    int smallestDist = 10; 
    int optimal = -1;

    if(floorNum == 1){
        direction = 'd';
    } else if (floorNum == 7){
        direction = 'u';
    }

    for (int i = 1; i <= totalElevs; ++i) {
        Elevator* elevator = this->elevators[i];
        
        if (elevator->getDirection() == direction || elevator->getDirection() == 'x'){
            if (abs(elevator->getCurrFloor() - floorNum) < smallestDist){
                smallestDist = abs(elevator->getCurrFloor() - floorNum); 
                optimal = elevator->getElevNumber(); 
            }
        }
    }

    if(optimal == -1){
        return 1;
    }

    return optimal;
}

int ElevatorControlSystem::requestAt(int floorNum, char direction){

    int closest = closestElev(floorNum, direction);
    qInfo("Closest elevator is %d", closest);

    if(elevators[closest]->getCurrFloor() == floorNum){
        sleep(2);
        this->openDoors(floorNum, closest);
        return closest;
    } else {
        bool added = getElevator(closest)->addDest(floorNum); 
        qInfo("Dest floor added: %s", added ? "true" : "false");
        sendElev(closest);
        return closest;
    }

}

void ElevatorControlSystem::sendElev(int elevNum){
    
    int* array = getElevator(elevNum)->getDestReqs();

    int elevCurrFloor = getElevator(elevNum)->getCurrFloor();

    if(elevCurrFloor < array[0]){
        getElevator(elevNum)->setDirection('u');

        elevCurrFloor++;

        for(int i = 0; i < getElevator(elevNum)->getReqSize(); i++){
            while(elevCurrFloor != array[i] && elevCurrFloor <= totalFloors){
                getElevator(elevNum)->start();
                elevCurrFloor++;
            }

            if(elevCurrFloor == array[i] && getElevator(elevNum)->getReqSize()-1 != i){
                getElevator(elevNum)->start();
                this->getElevator(elevNum)->stop();
                getElevator(elevNum)->ringBell();
                openDoors(elevCurrFloor,getElevator(elevNum)->getElevNumber());
                qInfo("Passenger has arrived at floor %d", elevCurrFloor);
                sleep(10);
                closeDoors(elevCurrFloor,getElevator(elevNum)->getElevNumber());
                elevCurrFloor++;
            } else if (elevCurrFloor == array[i] && getElevator(elevNum)->getReqSize()-1 == i){
                getElevator(elevNum)->start();
                getElevator(elevNum)->setDirection('x');
                this->getElevator(elevNum)->stop();
                getElevator(elevNum)->ringBell();
                openDoors(elevCurrFloor,getElevator(elevNum)->getElevNumber());
                //sleep(10);
                //closeDoors(elevCurrFloor,getElevator(elevNum)->getElevNumber());
                qInfo("Passenger has arrived at floor %d", elevCurrFloor);
                getElevator(elevNum)->clearDest();
                return;
            }
        }

    } else {
        getElevator(elevNum)->setDirection('d');

        elevCurrFloor--;

        for(int i = getElevator(elevNum)->getReqSize()-1; i >= 0; i--){
            while(elevCurrFloor != array[i] && elevCurrFloor > 1){
                getElevator(elevNum)->start();
                elevCurrFloor--;

            }

            if(elevCurrFloor == array[i] && getElevator(elevNum)->getReqSize() == i+getElevator(elevNum)->getReqSize()){
                getElevator(elevNum)->start();
                getElevator(elevNum)->setDirection('x');
                this->getElevator(elevNum)->stop();
                getElevator(elevNum)->ringBell();
                openDoors(elevCurrFloor,getElevator(elevNum)->getElevNumber());
                //sleep(10);
                //closeDoors(elevCurrFloor,getElevator(elevNum)->getElevNumber());
                getElevator(elevNum)->clearDest();
                return; 

            } else if (elevCurrFloor == array[i] && getElevator(elevNum)->getReqSize()-1 != i){
                getElevator(elevNum)->start();
                this->getElevator(elevNum)->stop();
                getElevator(elevNum)->ringBell();
                openDoors(elevCurrFloor,getElevator(elevNum)->getElevNumber());
                sleep(10);
                closeDoors(elevCurrFloor,getElevator(elevNum)->getElevNumber());
                elevCurrFloor--;
            }
        }
    }
}

void ElevatorControlSystem::openDoors(int floorNum, int elevNum){
    qInfo("Floor %d Doors Opening", floorNum);
    // floors[floorNum]->
    qInfo("Elevator %d Doors Opening", elevNum);

}

void ElevatorControlSystem::closeDoors(int floorNum, int elevNum){
    qInfo("Floor %d Doors Closing", floorNum);
    // floors[floorNum]->
    qInfo("Elevator %d Doors Closing", elevNum);
}

Elevator* ElevatorControlSystem::getElevator(int elevNum){

    return elevators[elevNum];
}

Floor* ElevatorControlSystem::getFloor(int floorNum){

    return floors[floorNum];
}

Passenger* ElevatorControlSystem::getPassenger(int passNum){
    return passengers[passNum];
}

void ElevatorControlSystem::buildingSafety(int elevNum){

    qInfo("Elevator %d connected to Building Safety", elevNum);
    qInfo("Press 'Respond' to respond");
    
}

void ElevatorControlSystem::call911(){
    qInfo("Calling 911");
}

void ElevatorControlSystem::doorObstacle(int elev){
    this->openDoors(elevators[elev]->getCurrFloor(),elev);
    //this->getElevator()->audioMessage("Door obstructed remove obstacle");
    //this->getElevator()->display("Door obstructed remove obstacle");
}

bool ElevatorControlSystem::overload(int weight, int elev){
    bool overloaded = elevators[elev]->overload(weight);

    if(overloaded){
        openDoors(elevators[elev]->getCurrFloor(), elev);
        elevators[elev]->audioMessage("Please deacrease the weight");
        elevators[elev]->display("Please deacrease the weight");

    }

    return overloaded;
}

void ElevatorControlSystem::fire(bool fromElev, int elevNum){
    //Fire() simulates the ECS receiving a fire signal either from the building or a specific elevator

    if(fromElev){
        qInfo("Fire signal from elevator");

        elevators[elevNum]->display("Fire Warning");
        elevators[elevNum]->audioMessage("Fire Warning");
        this->elevators[elevNum]->clearDest();
        this->elevators[elevNum]->addDest(SAFEFLOOR);
        this->sendElev(elevNum);
        this->elevators[elevNum]->display("Leave building immediately");
        this->elevators[elevNum]->audioMessage("Leave building immediately");

    }else{
        qInfo("Fire signal from building");

        for(int i = 1; i < this->totalElevs+1; i++){
            this->elevators[i]->display("Fire Warning");
            this->elevators[i]->audioMessage("Fire Warning");
        }

        for(int i = 1; i < this->totalElevs+1; i++){
            this->elevators[i]->clearDest();
            this->elevators[i]->addDest(SAFEFLOOR); 
            this->sendElev(i);
            this->elevators[i]->display("Leave building immediately");
            this->elevators[i]->audioMessage("Leave building immediately");
        
        }
    }
}

void ElevatorControlSystem::powerOut(){

    for(int i = 1; i <= totalElevs; i++){
        this->elevators[i]->display("Power Outage");
        this->elevators[i]->audioMessage("Power Outage");
    }

    for(int i = 1; i <= totalElevs; i++){
        this->elevators[i]->clearDest();
        this->elevators[i]->addDest(SAFEFLOOR); 
        this->sendElev(i);
        this->elevators[i]->display("Leave building immediately");
        this->elevators[i]->audioMessage("Leave building immediately");
    }

}
