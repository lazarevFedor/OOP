#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "eventController.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    DisplayElevator *elevatorDisplay1, *elevatorDisplay2;
    EventController *controller1, *controller2;

    QThread thread1, thread2;

    QPushButton start;
    QVBoxLayout Layout;
    QHBoxLayout elevators, controllers;

    Elevator elevator1, elevator2;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void stop1();
    void stop2();
    void elevatorsConnect();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
