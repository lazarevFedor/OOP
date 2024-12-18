#include "passanger.h"

Passanger::Passanger(){}

Passanger::Passanger(int floor, direction dir){
    currentFloor = floor;
    this->dir = dir;
    destinationFloor = randFloor();
}

int Passanger::randFloor(){
    int min_floor = 0;
    int max_floor = 8;
    std::random_device dice;
    std::mt19937 gen(dice());
    if (dir == LAST){
        std::uniform_int_distribution<> dis(currentFloor + 1, max_floor);
        return dis(gen);
    } else{
        std::uniform_int_distribution<> dis(min_floor, currentFloor - 1);
        return dis(gen);
    }
}

int Passanger::getDestFloor(){
    return destinationFloor;
}
