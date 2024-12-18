#include "elevator.h"

Elevator::Elevator(){
    for (int i = 0; i < 9; i++){
        Floor floor(i);
        floors.push_back(floor);
    }

    queue.resize(9);
}

int Elevator::getCurPas(){
    return currentPas.size();
}

void Elevator::takePassangers(){
    if (currentPas.size() == 4) return;
    if (queue[currentFloor].size() == 0) return;

    int taken = 0;
    direction dir;
    if (status == UP) dir = LAST;
    else if (status == DOWN) dir = FIRST;

    for (int i = 0; i < queue[currentFloor].size(); i++){
        if (queue[currentFloor][i].dir == dir){
            currentPas.push_back(queue[currentFloor][i]);
            queue[currentFloor].remove(i);
            i--;
            if (dir == LAST) floors[currentFloor].setCountUp(floors[currentFloor].getCountUp()-1);
            else floors[currentFloor].setCountDown(floors[currentFloor].getCountDown()-1);
            taken++;
            if (currentPas.size() == 4) break;
        }
    }
    emit passangerTaken(currentFloor);
}

int Elevator::mDestFloor(){
    if (getCurPas() == 0) return -1;
    if (status == UP){
        int max_dest_floor = 0;
        for (int i = 0; i < currentPas.size(); i++){
            if (max_dest_floor < currentPas[i].getDestFloor())
                max_dest_floor = currentPas[i].getDestFloor();
        }
        return max_dest_floor;
    }
    else if (status == DOWN){
        int min_dest_floor = 8;
        for (int i = 0; i < currentPas.size(); i++){
            if (min_dest_floor > currentPas[i].getDestFloor())
                min_dest_floor = currentPas[i].getDestFloor();
        }
        return min_dest_floor;
    }
    return -1;
}

void Elevator::releasePassangers(){
    if (getCurPas() == 0){
        return;
    }
    for (int i = 0; i < currentPas.size(); i++){
        if (currentPas[i].getDestFloor() == currentFloor){
            currentPas.remove(i);
            i--;
        }
    }
    emit passangerReleased(currentFloor, status);
}

bool Elevator::isWaiting(){
    for (int i = 0; i < queue.size(); i++){
        if (!queue[i].empty()) return true;
    }
    return false;
}

int Elevator::chooseDestFloor(){
    int dist = -1, dist2 = -2, destFloor = -1, destFloor2= -2;

    for (int i = 0; i <= currentFloor; i++){
        if (!queue[i].empty()){
            dist = (currentFloor - i);
            destFloor = i;
            break;
        }
    }

    for (int i = 8; i >= currentFloor; i--){
        if (!queue[i].empty()){
            dist2 = i - currentFloor;
            destFloor2 = i;
            break;
        }
    }

    if (dist >= 0 && dist2 >= 0) {
        if (dist < dist2) {
            status = DOWN;
            return destFloor;
        } else if (dist > dist2) {
            status = UP;
            return destFloor2;
        } else if (dist == dist2) {
            if (status == UP) {
                return destFloor2;
            } else {
                return destFloor;
            }
        }
    } else if (dist >= 0 && dist2 < 0) {
        status = DOWN;
        return destFloor;
    } else if (dist < 0 && dist2 >= 0) {
        status = UP;
        return destFloor2;
    } else if (dist == 0 && dist2 == 0) {
        if (status == UP) {
            return destFloor2;
        } else {
            return destFloor;
        }
    }
    return -1;
}


void Elevator::loop(){
    int destFloor;
    while (isWaiting()){

        destFloor = chooseDestFloor();
        do{
            if (currentFloor == 8 && status == UP) status = DOWN;
            if (currentFloor == 0 && status == DOWN) status = UP;
            takePassangers();
            if (getCurPas() != 0) destFloor = mDestFloor();
            QThread::msleep(500);
            if (status == UP && currentFloor != 8) currentFloor++;
            else if (status == DOWN && currentFloor != 0) currentFloor--;
            emit (floorChanged(currentFloor, status));
            QThread::msleep(500);
            releasePassangers();
        } while (currentFloor != destFloor);
    }
    status = IDLE;
    emit passangerReleased(currentFloor, status);
    emit finished();
}
