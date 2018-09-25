#ifndef BOBBERICK_TOOLS_FRAMEHANDLER_H
#define BOBBERICK_TOOLS_FRAMEHANDLER_H

#include <iostream>
#include "SDL.h"

class FrameHandler
{
public:
    explicit FrameHandler(int target);
    void handleFrame();
    void updateTicks();
    void setTarget(int target);

private:
    int target;
    int delayTime;
    Uint32 frameStart;
};


#endif //BOBBERICK_TOOLS_FRAMEHANDLER_H
