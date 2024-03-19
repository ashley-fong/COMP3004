#include "AudioSystem.h"
#include "Elevator.h"
#include "ElevatorControlSystem.h"
#include <QtGlobal>
#include <unistd.h>

AudioSystem::AudioSystem(){}

AudioSystem::~AudioSystem(){}

void AudioSystem::buildingSafety(){}

void AudioSystem::ringBell(int elev){
    qInfo("Elevator %d: Bell ring", elev);
}

void AudioSystem::leaveBuilding(int elev){
    qInfo("Elevator %d Audio Message: Please leave the building" , elev);
}

void AudioSystem::audioMessage(int elev, char* message){
    qInfo("Elevator %d Audio Message: %s" , elev, message);
}
