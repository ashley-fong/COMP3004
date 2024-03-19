#ifndef AUDIOSYSTEM_H
#define AUDIOSYSTEM_H

#include "defs.h"
#include "Elevator.h"

class AudioSystem
{

  public:
    AudioSystem();
    ~AudioSystem();
    void buildingSafety(); 
    void ringBell(int elev);
    void leaveBuilding(int elev);
    void audioMessage(int elev, char* message);

  private:


};

#endif
