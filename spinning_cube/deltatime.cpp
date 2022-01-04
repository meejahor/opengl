#include "deltatime.hpp"
#include <SDL.h>

Uint64 timeLast;
Uint64 timeNow;
double timeFrequencyReciprocal;
float deltaTime = 0;

void deltaTimeInit() {
    timeNow = SDL_GetPerformanceCounter();
    timeFrequencyReciprocal = static_cast<float>(SDL_GetPerformanceFrequency());
    timeFrequencyReciprocal = 1.0f / timeFrequencyReciprocal;
}

void deltaTimeUpdate() {
    timeLast = timeNow;
    timeNow = SDL_GetPerformanceCounter();
    deltaTime = (float)((timeNow - timeLast) * timeFrequencyReciprocal);
}
