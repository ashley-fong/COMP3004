#include "Floor.h"
#include <QtGlobal>
#include <unistd.h>
#include "ElevatorControlSystem.h"
using namespace std;

Floor::Floor(int floorNum) : floorNum(floorNum){
}

Floor::~Floor(){}

int Floor::carReqButton(ElevatorControlSystem *ECS, char direction, int floorNum){
    //qInfo("request is at %d", floorNum);
    return ECS->requestAt(floorNum, direction);
}

