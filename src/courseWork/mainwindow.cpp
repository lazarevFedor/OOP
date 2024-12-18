#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800, 800);
    setWindowTitle(QString::fromStdString("Симулятор Лифта"));

    elevatorDisplay1 = new DisplayElevator(&(elevator1));
    elevatorDisplay2 = new DisplayElevator(&(elevator2));

    elevators.addWidget(elevatorDisplay1);
    elevators.addWidget(elevatorDisplay2);

    controller1 = new EventController(&(elevator1), (elevatorDisplay1));
    controller2 = new EventController(&(elevator2), (elevatorDisplay2));


    controllers.addWidget(controller1);
    controllers.addWidget(controller2);

    Layout.addLayout(&(elevators));
    Layout.addLayout(&(controllers));

    start.setText("Запуск");
    Layout.addWidget(&(start));

    QWidget *widget = new QWidget(this);
    widget->setLayout(&(Layout));
    setCentralWidget(widget);

    QObject::connect(&(elevator1), SIGNAL(floorChanged(int, int)), elevatorDisplay1, SLOT(redraw(int, int)));
    QObject::connect(&(elevator2), SIGNAL(floorChanged(int, int)), elevatorDisplay2, SLOT(redraw(int, int)));

    QObject::connect(&(elevator1), SIGNAL(passangerTaken(int)), elevatorDisplay1, SLOT(take(int)));
    QObject::connect(&(elevator2), SIGNAL(passangerTaken(int)), elevatorDisplay2, SLOT(take(int)));

    QObject::connect(&(elevator1), SIGNAL(passangerReleased(int, int)), elevatorDisplay1, SLOT(release(int, int)));
    QObject::connect(&(elevator2), SIGNAL(passangerReleased(int, int)), elevatorDisplay2, SLOT(release(int, int)));

    QObject::connect(&(start), SIGNAL(clicked()), this, SLOT(elevatorsConnect()));

    QObject::connect(&(elevator1), SIGNAL(finished()), this, SLOT(stop1()));
    QObject::connect(&(elevator2), SIGNAL(finished()), this, SLOT(stop2()));
}

void MainWindow::elevatorsConnect(){
    elevator1.moveToThread(&(thread1));
    elevator2.moveToThread(&(thread2));

    QObject::connect(&(thread1), SIGNAL(started()), &(elevator1), SLOT(loop()));
    QObject::connect(&(thread2), SIGNAL(started()), &(elevator2), SLOT(loop()));

    thread1.start();
    thread2.start();
}

void MainWindow::stop1(){
    thread1.quit();
}

void MainWindow::stop2(){
    thread2.quit();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete elevatorDisplay1;
    delete elevatorDisplay2;
    delete controller1;
    delete controller2;
}

