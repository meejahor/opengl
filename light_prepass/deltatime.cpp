#include "deltatime.hpp"
#include <SDL.h>

Uint64 timeLast;
Uint64 timeNow;
double timeFrequencyReciprocal;

float DeltaTime::time;

void DeltaTime::init() {
    timeNow = SDL_GetPerformanceCounter();
    timeFrequencyReciprocal = static_cast<float>(SDL_GetPerformanceFrequency());
    timeFrequencyReciprocal = 1.0f / timeFrequencyReciprocal;
}

void DeltaTime::update() {
    timeLast = timeNow;
    timeNow = SDL_GetPerformanceCounter();
    DeltaTime::time = (float)((timeNow - timeLast) * timeFrequencyReciprocal);
}
