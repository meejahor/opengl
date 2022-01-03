#ifndef DELTATIME_H
#define DELTATIME_H

extern float timeLast;
extern float timeNow;
extern float timeFrequencyReciprocal;
extern float deltaTime;

void deltaTimeInit();
void deltaTimeUpdate();

#endif
