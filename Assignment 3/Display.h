#ifndef DISPLAY_H
#define DISPLAY_H

#include "defs.h"
#include "Elevator.h"
#include "ElevatorControlSystem.h"

class Display
{

  public:
    Display();
    ~Display();
    void displayFloor();
    void updateTo(int floorNum);
    void displayMess(int elev, char* message);

  private:
    int floorNum;
};

#endif
