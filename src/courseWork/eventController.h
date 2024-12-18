#ifndef EVENTCONTROLLER_H
#define EVENTCONTROLLER_H

#include <algorithm>
#include "displayElevator.h"

class EventController : public QWidget
{
    Q_OBJECT
    Elevator *elevator;
    DisplayElevator *display;

    QSpinBox upSpinBox;
    QSpinBox downSpinBox;
    QSpinBox floorSpinBox;
    QLabel floorLab, upLab, downLab;
    QGridLayout layout;
    QPushButton confirmButton;
public:
    EventController(Elevator *elevator, DisplayElevator *display);


public slots:
    void generatePassangers();
    void extremeFloors(int i);

};

#endif // EVENTCONTROLLER_H
