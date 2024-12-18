#include "floor.h"

Floor::Floor(){

}

Floor::Floor(int i){
    number = i;
}

int Floor::getCountUp(){
    return countUp;
}

int Floor::getCountDown(){
    return countDown;
}

void Floor::setCountUp(int c){
    countUp = c;
}

void Floor::setCountDown(int c){
    countDown = c;
}
