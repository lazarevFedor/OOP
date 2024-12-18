#include "eventController.h"

EventController::EventController(Elevator* elev, DisplayElevator *display) : QWidget{}{

    elevator = elev;
    this->display = display;

    floorLab.setText("С этажа № :");
    floorLab.setAlignment(Qt::AlignRight);
    floorSpinBox.setMinimum(1);
    floorSpinBox.setMaximum(9);
    layout.addWidget(&(floorLab), 0, 0);
    layout.addWidget(&(floorSpinBox), 0, 1);

    upLab.setText("Вверх:");
    upLab.setAlignment(Qt::AlignRight);
    upSpinBox.setMinimum(0);
    upSpinBox.setMaximum(6);
    layout.addWidget(&(upLab), 1, 0);
    layout.addWidget(&(upSpinBox), 1, 1);

    downLab.setText("Вниз:");
    downLab.setAlignment(Qt::AlignRight);
    downSpinBox.setMinimum(0);
    downSpinBox.setMaximum(0);
    layout.addWidget(&(downLab), 2, 0);
    layout.addWidget(&(downSpinBox), 2, 1);

    confirmButton.setText("OK");


    layout.addWidget(&(confirmButton), 3, 1);

    setLayout(&(layout));

    QObject::connect(&(confirmButton), SIGNAL(clicked()), this, SLOT(generatePassangers()));
    QObject::connect(&(floorSpinBox), SIGNAL(valueChanged(int)), this, SLOT(extremeFloors(int)));
}

void EventController::extremeFloors(int i){
    switch (i) {
    case (9):
        upSpinBox.setMaximum(0);
        break;
    case (1):
        downSpinBox.setMaximum(0);
        break;
    default:
        upSpinBox.setMaximum(6);
        downSpinBox.setMaximum(6);
    }
}

void EventController::generatePassangers(){

    int upCount, downCount, currentFloor;
    upCount = upSpinBox.value();
    downCount = downSpinBox.value();
    currentFloor = floorSpinBox.value()-1;
    for (int i = 0; i < upCount; i++){
        Passanger Bob(currentFloor, LAST);
        elevator->queue[currentFloor].push_back(Bob);
        elevator->floors[currentFloor].setCountUp(elevator->floors[currentFloor].getCountUp()+1);
    }


    for (int i = 0; i < downCount; i++){
        Passanger Bob(currentFloor, FIRST);
        elevator->queue[currentFloor].push_back(Bob);
        elevator->floors[currentFloor].setCountDown(elevator->floors[currentFloor].getCountDown()+1);
    }
    display->display.setItem(8-currentFloor, 1,
                          new QTableWidgetItem("↑: " + QString::number(elevator->floors[currentFloor].getCountUp()) +
                                               " ↓:" + QString::number(elevator->floors[currentFloor].getCountDown())));
}
