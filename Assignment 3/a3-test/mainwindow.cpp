#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string.h>
#include <QTimer>

#include "defs.h"
#include "Passenger.h"
#include "Elevator.h"
#include "Floor.h"
#include "ElevatorControlSystem.h"
#include "AudioSystem.h"
#include "Display.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ECS = new ElevatorControlSystem(7,3,3);
    p = new Passenger(-1,-1, false);

    timerD = new QTimer(this);
    timerH = new QTimer(this);
    ui->setupUi(this);

    connect(ui->Help, SIGNAL(clicked()), this, SLOT(Help()));
    connect(ui->Door_Obstructed,SIGNAL(clicked()), this, SLOT(Obstacle()));
    connect(ui->fireElev,SIGNAL(clicked()), this, SLOT(fireElev()));
    connect(ui->fireBuilding,SIGNAL(clicked()), this, SLOT(fireBuilding()));
    connect(ui->enterWeight,SIGNAL(clicked()), this, SLOT(checkOverload()));
    connect(ui->Power_Out,SIGNAL(clicked()), this, SLOT(PowerOut()));
    connect(timerD, &QTimer::timeout, this, &MainWindow::closingDoors);
    connect(ui->respond, SIGNAL(clicked()), this, SLOT(respondButton()));
    connect(timerH, &QTimer::timeout, this, &MainWindow::safetyTimeout);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete ECS;
}

void MainWindow::buttonUncheck(){
    if(ui->downButton->isChecked() == true){
        ui->downButton->setChecked(false);

    } else if (ui->upButton->isChecked() == true){
        ui->upButton->setChecked(false);

    } else if(ui->openDoor->isChecked()){
        ui->openDoor->setChecked(false);

    } else if (ui->closeDoor->isChecked()){
        ui->closeDoor->setChecked(false);

    }else if(ui->f1->isChecked() == true){
        ui->f1->setChecked(false);

    } else if(ui->f2->isChecked() == true){
        ui->f2->setChecked(false);

    } else if(ui->f3->isChecked() == true){
        ui->f3->setChecked(false);

    } else if(ui->f4->isChecked() == true){
        ui->f4->setChecked(false);

    } else if(ui->f5->isChecked() == true){
        ui->f5->setChecked(false);

    } else if(ui->f6->isChecked() == true){
        ui->f6->setChecked(false);

    } else if(ui->f7->isChecked() == true){
        ui->f7->setChecked(false);
    }
}

void MainWindow::Help(){

    if(p->getOnElev() == -1){
        qInfo("Passenger is not on elevator");
    } else {
        qInfo("Help Requested");
        p->pressHelpButton(ECS,ECS->getElevator(p->getOnElev()));

        timerH->start(5000);
    }
}

void MainWindow::checkOverload(){

    bool overload = true;

    if(p->getOnElev() == -1){
        qInfo("Passenger is not on elevator");
    } else {
        int weight = ui->weightInput->toPlainText().toInt();
        overload = ECS->overload(weight, p->getOnElev());

        if(!ui->weightInput->toPlainText().isEmpty() && overload == true){
            qInfo("Weight exceeds limit");
        } else {
             qInfo("Weight good");
             this->closingDoors();
        }
    }
}

void MainWindow::Obstacle(){

    if(p->getOnElev() == -1){
        qInfo("Passenger is not on elevator");
    } else {
        qInfo("Door Obstructed");
        ECS->doorObstacle(p->getOnElev());
    }
}

void MainWindow::fireBuilding(){

    qInfo("Fire Signal Received");
    ECS->fire(false,-1);

}

void MainWindow::fireElev(){
    timerD->stop();
    if(p->getOnElev() == -1){
        qInfo("Passenger is not on elevator");
    } else {
        qInfo("Fire Signal Received");
        ECS->fire(true, p->getOnElev());
    }
}

void MainWindow::PowerOut(){

    qInfo("Power Out Signal Received");
    ECS->powerOut();
    qInfo("\n");

}

void MainWindow::on_f1_toggled(bool checked){
    if(checked){

        if(p->getOnElev() == -1){
            qInfo("Passenger is not on elevator");
            this->buttonUncheck();

        } else {
            qInfo("Floor 1 toggled");
            p->pressElevatorButton(ECS,1);
            return;
        }

    }
}

void MainWindow::on_f2_toggled(bool checked)
{
    if(checked){

        if(p->getOnElev() == -1){
            qInfo("Passenger is not on elevator");
            this->buttonUncheck();
        } else {
            qInfo("Floor 2 toggled");
            p->pressElevatorButton(ECS,2);
            return;
        }
    }
}

void MainWindow::on_f3_toggled(bool checked)
{
    if(checked){

        if(p->getOnElev() == -1){
            qInfo("Passenger is not on elevator");
            this->buttonUncheck();
        } else {
            qInfo("Floor 3 toggled");
            p->pressElevatorButton(ECS,3);
            return;
        }

    }
}

void MainWindow::on_f4_toggled(bool checked)
{
    if(checked){
        if(p->getOnElev() == -1){
            qInfo("Passenger is not on elevator");
            this->buttonUncheck();
        } else {
            qInfo("Floor 4 toggled");
            p->pressElevatorButton(ECS,4);
            return;
        }
    }
}

void MainWindow::on_f5_toggled(bool checked)
{
    if(checked){

        if(p->getOnElev() == -1){
            qInfo("Passenger is not on elevator");
            this->buttonUncheck();
        } else {
            qInfo("Floor 5 toggled");
            p->pressElevatorButton(ECS,5);
            return;
        }
    }
}

void MainWindow::on_f6_toggled(bool checked)
{
    if(checked){
        if(p->getOnElev() == -1){
            qInfo("Passenger is not on elevator");
            this->buttonUncheck();
        } else {
            qInfo("Floor 6 toggled");
            p->pressElevatorButton(ECS,6);
            return;
        }
    }
}

void MainWindow::on_f7_toggled(bool checked)
{
    if(checked){
        if(p->getOnElev() == -1){
            qInfo("Passenger is not on elevator");
            this->buttonUncheck();
        } else {
            qInfo("Floor 7 toggled");
            p->pressElevatorButton(ECS,7);
            return;
        }
    }
}


void MainWindow::on_upButton_toggled(bool checked)
{
    if(checked){
        QString selected = ui->floorStart->currentText();
        string s = selected.toStdString();
        int f = stoi(s);
        qInfo("Floor %d Selected", f);

        p = new Passenger(1,f, false);

        p->pressFloor(ECS->getFloor(f), 'u', ECS);
        this->buttonUncheck();

        timerD->start(10000);

    }
}

void MainWindow::on_downButton_toggled(bool checked)
{
    if(checked){
        QString selected = ui->floorStart->currentText();
        string s = selected.toStdString();
        int f = stoi(s);
        qInfo("Floor %d Selected", f);

        p = new Passenger(1, f, false);
        //Floor* floor = new Floor(f);
        //ElevatorControlSystem* temp = new ElevatorControlSystem(7,3,3);

        p->pressFloor(ECS->getFloor(f), 'd', ECS);

        this->buttonUncheck();

        timerD->start(10000);
    }
}

void MainWindow::respondButton()
{
    timerH->stop();
    qInfo("responded, talking to building safety");
}

void MainWindow::safetyTimeout(){
    timerH->stop();
    qInfo("No response");
    ECS->call911();
    
}

void MainWindow::closingDoors(){
    timerD->stop();
    ECS->closeDoors(ECS->getElevator(p->getOnElev())->getCurrFloor(),p->getOnElev());
    bool a = p->whenArrived(ECS->getElevator(p->getOnElev()));

    this->sending();
}

void MainWindow::sending(){

    if (p->getOnElev() == -1){
            return;
    } else if (ECS->getElevator(p->getOnElev())->getReqSize() > 0 && p->getOnElev() != -1){
        ECS->sendElev(p->getOnElev());
        this->buttonUncheck();

        timerD->start(10000);
    }
}

void MainWindow::on_openDoor_toggled(bool checked)
{
    if(checked){
        ECS->openDoors(ECS->getElevator(p->getOnElev())->getCurrFloor(), p->getOnElev());

        this->buttonUncheck();
        timerD->start(10000);
    }
}

void MainWindow::on_closeDoor_toggled(bool checked)
{
    if(checked){
        this->buttonUncheck();
        this->closingDoors();
    }
}
