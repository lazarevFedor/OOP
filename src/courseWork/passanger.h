#ifndef PASSANGER_H
#define PASSANGER_H

#include <random>

enum direction{
    LAST,
    FIRST
};

class Passanger
{
    int currentFloor;
    int destinationFloor;
    int randFloor();

public:
    direction dir;
    Passanger();
    Passanger(int floor, direction dir);
    int getDestFloor();
};

#endif // PASSANGER_H
