#ifndef PASSENGER_H
#define PASSENGER_H

using namespace std;

#include "defs.h"
#include "Elevator.h"

class Elevator;
class Floor;
class ElevatorControlSystem;


class Passenger{
public:
    Passenger(int passNum, int currFloor, bool arrived);
    ~Passenger();
    void pressFloor(Floor* request, char direction, ElevatorControlSystem* ECS);
    int pressElevatorButton(ElevatorControlSystem* ECS, int floorInput);
    void pressHelpButton(ElevatorControlSystem* ECS, Elevator* currElev);
    bool whenArrived(Elevator* elev);
    int getPassNum();
    void setCurrFloor(int floor);
    int getCurrFloor();
    void setDestFloor(int floor);
    int getDestFloor();
    int getOnElev();

  private:
    int passNum;
    int currFloor;
    int destFloor; 
    bool arrived; 
    int weight; 
    int onElev;
};

#endif // PASSENGER_H
