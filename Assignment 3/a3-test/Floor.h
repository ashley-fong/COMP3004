#ifndef FLOOR_H
#define FLOOR_H

#include <iostream>
#include <unistd.h>
#include <QtGlobal>
#include "ElevatorControlSystem.h"

class ElevatorControlSystem;

using namespace std;

class Floor{
public:
    Floor(int floorNum);
    ~Floor();
    int carReqButton(ElevatorControlSystem *ECS, char direction, int floorNum);

private:
    int floorNum;

};
#endif // FLOOR_H
