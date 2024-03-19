#include "Elevator.h"
#include "ElevatorControlSystem.h"
#include "Passenger.h"
#include "Display.h"
#include "AudioSystem.h"

#include <iostream>
#include <unistd.h>
#include <QtGlobal>
using namespace std;

Elevator::Elevator(int elevNum, int currFloor, bool obstructed, bool overloaded)
    : elevNum(elevNum), currFloor(currFloor), obstructed(obstructed), overloaded(overloaded) {
    
    direction = 'x'; // x meaning idle
    reqSize = 0;
    d = new Display();
    as = new AudioSystem();
}

Elevator::~Elevator(){
    delete d;
    delete as;
}

void Elevator::start(){

    if(direction == 'u'){
        currFloor++;
    } else if(direction == 'd'){
        currFloor--;
    }
    qInfo("Elevator %d: Moving to Floor %d", elevNum, currFloor);
    this->d->updateTo(currFloor);
    this->d->displayFloor();

    sleep(2);
    
}

void Elevator::stop(){

    qInfo("Stopping elevator");
    sleep(2);
    
}

int Elevator::getElevNumber(){

    return this->elevNum;
}

char Elevator::getDirection(){
    return this->direction;
}

void Elevator::setDirection(char dir){
    direction = dir;
}

void Elevator::setCurrFloor(int floor){
    currFloor = floor;
}

int Elevator::getCurrFloor(){
    return this->currFloor;
}

void Elevator::ringBell(){
    this->as->ringBell(elevNum);
}

void Elevator::display(char* message){
    this->d->displayMess(elevNum, message);
}

void Elevator::displayFloor(){
    this->d->displayFloor();
}

void Elevator::audioMessage(char* message){
    this->as->audioMessage(elevNum, message);
}

bool Elevator::addDest(int floor){
    int insert = -1;

    if(reqSize == 0){
        destReqs[0] = floor;
        reqSize++;
        return true;
    }

    for (int i = 0; i < reqSize; i++){
        if (destReqs[i] > floor){
            insert = i;
            break;
        } else if (destReqs[i] == floor){
            qInfo("%d == %d", destReqs[i], floor);
            return false;
        }
    }

    if(insert == -1){
        insert = reqSize;
    }

    for (int i = reqSize; i > insert; i--){
        destReqs[i] = destReqs[i-1];
    }

    destReqs[insert] = floor;
    reqSize++;

    return true;

}

//remove dest
bool Elevator::clearDest(){
    for (int i = 0; i < reqSize; i++) {
        destReqs[i] = 0;
    }

    reqSize = 0;
}

int* Elevator::getDestReqs(){
    return destReqs;
}

int Elevator::getReqSize(){

    return reqSize;
}


bool Elevator::overload(int totalWeight){

    if(totalWeight >= OVERLOAD){
        stop();
        qInfo("Overload");
        return true;
    } else {
        qInfo("Weight okay");
        return false; 
    }
}

void Elevator::helpButton(ElevatorControlSystem* ECS, Passenger* p){

    qInfo("Help button pressed");
    ECS->buildingSafety(this->elevNum);
}
