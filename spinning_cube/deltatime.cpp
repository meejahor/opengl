#include "deltatime.hpp"
#include <SDL.h>

float timeLast;
float timeNow;
float timeFrequencyReciprocal;
float deltaTime;

void deltaTimeInit() {
    timeNow = static_cast<float>(SDL_GetPerformanceCounter());
    timeFrequencyReciprocal = static_cast<float>(SDL_GetPerformanceFrequency());
    timeFrequencyReciprocal = 1.0f / timeFrequencyReciprocal;
}

void deltaTimeUpdate() {
    timeLast = timeNow;
    timeNow = static_cast<float>(SDL_GetPerformanceCounter());
    float timeDiff = timeNow - timeLast;
    timeDiff *= timeFrequencyReciprocal;
    deltaTime = timeDiff;
}
