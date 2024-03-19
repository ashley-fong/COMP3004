#ifndef ELEVATOR_H
#define ELEVATOR_H
using namespace std;

#include <iostream>
#include <QtGlobal>
#include "ElevatorControlSystem.h"
#include "Passenger.h"

class AudioSystem;
class Display;

class Elevator{
public:
    Elevator(int elevNum, int currFloor, bool obstructed, bool overloaded);
    ~Elevator();
    void start();
    void stop();
    bool addDest(int floor); 
    bool clearDest();
    int* getDestReqs();
    int getReqSize();
    int getElevNumber();
    char getDirection();
    void setDirection(char dir);
    void setCurrFloor(int floor);
    int getCurrFloor();
    void ringBell();
    void display(char* message);
    void displayFloor();
    void audioMessage(char* message);
    bool overload(int totalWeight);
    void helpButton(ElevatorControlSystem* owner, Passenger* p);


private:
    int destReqs[7];
    int elevNum;
    int currFloor;  
    bool obstructed;
    bool overloaded;
    int totalWeight; 
    char direction;
    int reqSize;
    AudioSystem* as;
    Display* d;

};

#endif // ELEVATOR_H
