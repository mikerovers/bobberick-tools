#include "FrameHandler.h"

FrameHandler::FrameHandler(const int target): target(target), delayTime(1000 / target)
{

}

void FrameHandler::handleFrame()
{
    int frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < delayTime) {
        SDL_Delay(static_cast<Uint32>(delayTime - frameTime));
    }
}

void FrameHandler::updateTicks()
{
    frameStart = SDL_GetTicks();
}

void FrameHandler::setTarget(int targetFrames)
{
    target = targetFrames;
    delayTime = 1000 / target;
}
