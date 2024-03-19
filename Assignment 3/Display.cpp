#include "Display.h"
#include <QtGlobal>
#include <unistd.h>

Display::Display(){}

Display::~Display(){}

void Display::updateTo(int newFloor){
    floorNum = newFloor;
}

void Display::displayFloor(){
    qInfo("Current Floor: %d", floorNum);
}

void Display::displayMess(int elev, char* message){
    qInfo("Elevator %d Display: %s" , elev, message);

}
