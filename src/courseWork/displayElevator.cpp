#include "displayElevator.h"

DisplayElevator::DisplayElevator(Elevator *elev) : QWidget{}{
    elevator = elev;

    display.setColumnCount(2);
    display.setRowCount(9);

    display.setHorizontalHeaderLabels({"", "Л и ф т"});
    display.setVerticalHeaderLabels({"9", "8", "7", "6", "5", "4", "3", "2", "1"});

    QTableWidgetItem *cell = new QTableWidgetItem(QString::number(elevator->getCurPas()) + " ↑");
    cell->setBackground(Qt::cyan);
    cell->setTextAlignment(Qt::AlignCenter);
    display.setItem(8, 0, cell);

    display.resizeColumnsToContents();
    display.horizontalHeader()->setStretchLastSection(true);
    display.verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    layout.addWidget(&(display));
    setLayout(&(layout));
}

void DisplayElevator::redraw(int floor, int direction){

    QString text = QString::number(elevator->getCurPas());

    QTableWidgetItem *cell2 = new QTableWidgetItem("");
    cell2->setBackground(Qt::white);

    if (direction == UP){
        text += " ↑";
        display.setItem(8-floor+1, 0, cell2);
    }
    else if (direction == DOWN){
        text += " ↓";
        display.setItem(8-floor-1, 0, cell2);
    }



    QTableWidgetItem *cell = new QTableWidgetItem(text);
    cell->setBackground(Qt::cyan);
    cell->setTextAlignment(Qt::AlignCenter);
    display.setItem(8-floor, 0, cell);
}

void DisplayElevator::release(int curFloor, int direction){
    QString text = QString::number(elevator->getCurPas());
    if (direction == UP) text += " ↑";
    else if (direction == DOWN) text += " ↓";
    else text += "  ";

    QTableWidgetItem *qTableItem = new QTableWidgetItem(text);
    qTableItem->setBackground(Qt::cyan);
    qTableItem->setTextAlignment(Qt::AlignCenter);
    display.setItem(8-curFloor, 0, qTableItem);
}

void DisplayElevator::take(int curFloor) {
    QTableWidgetItem *qTableItem = new QTableWidgetItem("↑: " + QString::number(elevator->floors[curFloor].getCountUp()) + " ↓: " + QString::number(elevator->floors[curFloor].getCountDown()));
    display.setItem(8-curFloor, 1, qTableItem);
}
