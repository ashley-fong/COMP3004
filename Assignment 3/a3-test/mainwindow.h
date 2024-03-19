#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Passenger.h"
#include "Elevator.h"
#include "Floor.h"
#include "ElevatorControlSystem.h"
#include "AudioSystem.h"
#include "Display.h"
#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ElevatorControlSystem* ECS;
    Passenger* p;
    QTimer *timerD;
    QTimer *timerH;

private slots:
    void Help();
    void Obstacle();
    void fireElev();
    void fireBuilding();
    void checkOverload();
    void PowerOut();
    void on_f1_toggled(bool checked);
    void on_f2_toggled(bool checked);
    void on_f3_toggled(bool checked);
    void on_f4_toggled(bool checked);
    void on_f5_toggled(bool checked);
    void on_f6_toggled(bool checked);
    void on_f7_toggled(bool checked);
    void on_upButton_toggled(bool checked);
    void on_downButton_toggled(bool checked);
    void buttonUncheck();
    void respondButton();
    void safetyTimeout();
    void closingDoors();
    void sending();
    void on_openDoor_toggled(bool checked);
    void on_closeDoor_toggled(bool checked);

};


#endif // MAINWINDOW_H
