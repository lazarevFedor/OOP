#ifndef DISPLAYELEVATOR_H
#define DISPLAYELEVATOR_H

#include <QTableWidget>
#include <QHeaderView>
#include "elevator.h"

class DisplayElevator : public QWidget
{
    Q_OBJECT

    Elevator *elevator;
    QHBoxLayout layout;
public:
    QTableWidget display;
    DisplayElevator(Elevator *elev);

public slots:
    void redraw(int floor, int direction);
    void release(int floor, int direction);
    void take(int floor);
};

#endif // DISPLAYELEVATOR_H
