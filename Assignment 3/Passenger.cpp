#include "Passenger.h"
#include "Elevator.h"
#include "ElevatorControlSystem.h"
#include "Floor.h"

#include <unistd.h>
using namespace std;

Passenger::Passenger(int passNum, int currFloor, bool arrived)
    : passNum(passNum), currFloor(currFloor), arrived(arrived){
        
    destFloor = -1;
    onElev = -1;
}

Passenger::~Passenger(){}

void Passenger::pressFloor(Floor* request, char direction, ElevatorControlSystem* ECS){
    onElev = request->carReqButton(ECS,direction,currFloor);

}

int Passenger::pressElevatorButton(ElevatorControlSystem* ECS, int floorInput){

    int currElev = onElev;

    bool inserted = ECS->getElevator(currElev)->addDest(floorInput);
    qInfo("Dest floor added: %s", inserted ? "true" : "false");
    sleep(2);
    setDestFloor(floorInput);

    return currElev;
}

void Passenger::pressHelpButton(ElevatorControlSystem* ECS, Elevator* currElev){
    currElev->helpButton(ECS,this);
}

bool Passenger::whenArrived(Elevator* elev){
    if(elev->getCurrFloor() == destFloor){
        currFloor = destFloor;
        destFloor = -1;
        arrived = true;
        onElev = -1;
        return true;
    }
    return false;
}

int Passenger::getPassNum(){
    return passNum;
}
void Passenger::setCurrFloor(int floor){
    currFloor = floor;
}

int Passenger::getCurrFloor(){
    return currFloor;
}

void Passenger::setDestFloor(int floor){
    destFloor = floor;
}

int Passenger::getDestFloor(){
    return destFloor; 
}

int Passenger::getOnElev(){
    return onElev;
}
