#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QDateTime"
#include "Machine.h"
#include "QTimer"
#include "QString"
#include "signal.h"

Machine* machine = new Machine();
int connectionColor;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Disable all buttons until Power Buttons is pressed
    ui->selectButton->setEnabled(false);
    ui->replayButton->setEnabled(false);
    ui->recordButton->setEnabled(false);
    ui->intensity1->setEnabled(false);
    ui->intensity2->setEnabled(false);
    ui->intensity3->setEnabled(false);
    ui->intensity4->setEnabled(false);
    ui->intensity5->setEnabled(false);
    ui->intensity6->setEnabled(false);
    ui->intensity7->setEnabled(false);
    ui->intensity8->setEnabled(false);
    ui->type1Button->setEnabled(false);
    ui->type2Button->setEnabled(false);
    ui->type3Button->setEnabled(false);
    ui->type4Button->setEnabled(false);
    ui->twentyTimeButton->setEnabled(false);
    ui->fortyFiveTimeButton->setEnabled(false);
    ui->userDesTimeButton->setEnabled(false);
    ui->connectionButton->setVisible(false);
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->listWidget->setVisible(false);
    ui->listWidget->setFocus();
    ui->Battery->setVisible(false);
    ui->dateTimeEdit->setVisible(false);



}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_selectButton_clicked()
{
    machine->ok_button();

    enableType();

    enableConnection();

    enableRecord();

    if(machine->getState() == 4){
        this->on_selectButton_clicked();

    }

    if(machine->getState() == 0){
        ui->selectButton->setEnabled(false);
        ui->replayButton->setEnabled(false);
        ui->recordButton->setEnabled(false);
        ui->intensity1->setEnabled(false);
        ui->intensity2->setEnabled(false);
        ui->intensity3->setEnabled(false);
        ui->intensity4->setEnabled(false);
        ui->intensity5->setEnabled(false);
        ui->intensity6->setEnabled(false);
        ui->intensity7->setEnabled(false);
        ui->intensity8->setEnabled(false);
        ui->type1Button->setEnabled(false);
        ui->type2Button->setEnabled(false);
        ui->type3Button->setEnabled(false);
        ui->type4Button->setEnabled(false);
        ui->twentyTimeButton->setEnabled(false);
        ui->fortyFiveTimeButton->setEnabled(false);
        ui->userDesTimeButton->setEnabled(false);
        ui->connectionButton->setVisible(false);
        ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
        ui->listWidget->setVisible(false);
        ui->listWidget->setFocus();
        ui->Battery->setVisible(false);
        ui->dateTimeEdit->setVisible(false);
        ui->connectionButton->setStyleSheet("background-color: rgb(211, 215, 207)");
        ui->connectionButton->setText("Connection");
        ui->connectionButton->setVisible(false);
        machine->turnOff();
        ui->selectButton->setChecked(false);
        ui->replayButton->setChecked(false);
        ui->recordButton->setChecked(false);
        ui->intensity1->setChecked(false);
        ui->intensity2->setChecked(false);
        ui->intensity3->setChecked(false);
        ui->intensity4->setChecked(false);
        ui->intensity5->setChecked(false);
        ui->intensity6->setChecked(false);
        ui->intensity7->setChecked(false);
        ui->intensity8->setChecked(false);
        ui->type1Button->setChecked(false);
        ui->type2Button->setChecked(false);
        ui->type3Button->setChecked(false);
        ui->type4Button->setChecked(false);
        ui->twentyTimeButton->setChecked(false);
        ui->fortyFiveTimeButton->setChecked(false);
        ui->userDesTimeButton->setChecked(false);

    }

}

void MainWindow::on_replayButton_clicked()
{
    qDebug() <<"Replaying....";
    ui->selectButton->setEnabled(true);
    QListWidgetItem* item = ui->listWidget->currentItem();
    QString st = item->text();
//    qDebug() <<st;
    string text = st.toStdString();

    machine->replay_button(true, text);

    ui->connectionButton->setEnabled(true);

}

void MainWindow::on_recordButton_clicked()
{
    qDebug() <<"Recording....";
    ui->recordButton->setEnabled(true);
        machine->record_button(ui->recordButton->isChecked());

        machine->get_recorded_session();
        QStringList list;
        ui->listWidget->clear();
        for (int i=0;i<machine->get_recorded();i++){

//            qDebug() <<"rec "<<i<<": ";
//            machine->get_recorded_session()[i].print();
            const string test = machine->session_string(machine->get_recorded_session()[i],i);
            //qDebug() <<QString::fromStdString(test);

            ui->listWidget->addItem(QString::fromStdString(test));
        }
}

void MainWindow::on_powerButton_clicked()
{
    ui->connectionButton->setStyleSheet("background-color: light grey");
    if(machine->checkOffState() == true){
        ui->twentyTimeButton->setEnabled(true);
        ui->fortyFiveTimeButton->setEnabled(true);
        ui->userDesTimeButton->setEnabled(true);
        ui->listWidget->setVisible(true);
        ui->listWidget->setFocus();
        ui->Battery->setVisible(true);
        ui->dateTimeEdit->setVisible(true);
        ui->connectionButton->setVisible(true);
        ui->connectionButton->setEnabled(false);
        machine->setState(1);
        machine->setTemp(Session());
        ui->Battery->setValue(machine->get_battery_life());
    }else{
        qDebug() <<"in the power button";
        qDebug() <<machine->getState();
        ui->selectButton->setEnabled(false);
        ui->replayButton->setEnabled(false);
        ui->recordButton->setEnabled(false);
        ui->intensity1->setEnabled(false);
        ui->intensity2->setEnabled(false);
        ui->intensity3->setEnabled(false);
        ui->intensity4->setEnabled(false);
        ui->intensity5->setEnabled(false);
        ui->intensity6->setEnabled(false);
        ui->intensity7->setEnabled(false);
        ui->intensity8->setEnabled(false);
        ui->type1Button->setEnabled(false);
        ui->type2Button->setEnabled(false);
        ui->type3Button->setEnabled(false);
        ui->type4Button->setEnabled(false);
        ui->twentyTimeButton->setEnabled(false);
        ui->fortyFiveTimeButton->setEnabled(false);
        ui->userDesTimeButton->setEnabled(false);
        ui->connectionButton->setVisible(false);
        ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
        ui->listWidget->setVisible(false);
        ui->listWidget->setFocus();
        ui->Battery->setVisible(false);
        ui->dateTimeEdit->setVisible(false);
        if(ui->recordButton->isChecked()){
            ui->recordButton->setChecked(false);
        }
        if(ui->replayButton->isChecked()){
            ui->replayButton->setChecked(false);
        }
        ui->selectButton->setChecked(false);
        ui->replayButton->setChecked(false);
        ui->recordButton->setChecked(false);
        ui->intensity1->setChecked(false);
        ui->intensity2->setChecked(false);
        ui->intensity3->setChecked(false);
        ui->intensity4->setChecked(false);
        ui->intensity5->setChecked(false);
        ui->intensity6->setChecked(false);
        ui->intensity7->setChecked(false);
        ui->intensity8->setChecked(false);
        ui->type1Button->setChecked(false);
        ui->type2Button->setChecked(false);
        ui->type3Button->setChecked(false);
        ui->type4Button->setChecked(false);
        ui->twentyTimeButton->setChecked(false);
        ui->fortyFiveTimeButton->setChecked(false);
        ui->userDesTimeButton->setChecked(false);
        ui->Battery->setValue(machine->getBatteryLevel());
        machine->setStateOff();
}
}

void MainWindow::on_intensity1_clicked()
{
    qDebug() <<"Intensity 1 selected";
    machine->setTempInt(1);
}

void MainWindow::on_intensity2_clicked()
{
    qDebug() <<"Intensity 2 selected";
    machine->setTempInt(2);
}

void MainWindow::on_intensity3_clicked()
{
    qDebug() <<"Intensity 3 selected";
    machine->setTempInt(3);
}

void MainWindow::on_intensity4_clicked()
{
    qDebug() <<"Intensity 4 selected";
    machine->setTempInt(4);
}

void MainWindow::on_intensity5_clicked()
{
    qDebug() <<"Intensity 5 selected";
    machine->setTempInt(5);
}

void MainWindow::on_intensity6_clicked()
{
    qDebug() <<"Intensity 6 selected";
    machine->setTempInt(6);
}

void MainWindow::on_intensity7_clicked()
{
    qDebug() <<"Intensity 7 selected";
    machine->setTempInt(7);
}

void MainWindow::on_intensity8_clicked()
{
    qDebug() <<"Intensity 8 selected";
    machine->setTempInt(8);
}


void MainWindow::on_type1Button_clicked()
{
    qDebug() <<"Type 1 selected";
    machine->setTempType(1);
    enableIntensity();
}

void MainWindow::on_type2Button_clicked()
{
    qDebug() <<"Type 2 selected";
    machine->setTempType(2);
    enableIntensity();
}

void MainWindow::on_type3Button_clicked()
{
    qDebug() <<"Type 3 selected";
    machine->setTempType(3);
    enableIntensity();
}

void MainWindow::on_type4Button_clicked()
{
    qDebug() <<"Type 4 selected";
    machine->setTempType(4);
    enableIntensity();
}

void MainWindow::on_twentyTimeButton_clicked()
{
    qDebug() <<"20mins selected";
    qDebug() << "SELECT A TYPE: ";
    machine->setTempDur(20);
    ui->selectButton->setEnabled(true);
}

void MainWindow::on_fortyFiveTimeButton_clicked()
{
    qDebug() <<"45mins selected";
    qDebug() << "SELECT A TYPE: ";
    machine->setTempDur(45);
    ui->selectButton->setEnabled(true);
}

void MainWindow::on_userDesTimeButton_clicked()
{
    qDebug() <<"User Destinated selected";
    qDebug() << "SELECT A TYPE: ";
    machine->setTempDur(60);
    ui->selectButton->setEnabled(true);
}

void MainWindow::on_upButton_clicked()
{
    int row = ui->listWidget->currentRow()-1;
    if(row < 0){
        row = ui->listWidget->count()-1;
    }
    ui->listWidget->setCurrentRow(row);
    ui->replayButton->setEnabled(true);
}

void MainWindow::on_downButton_clicked()
{
    int row = ui->listWidget->currentRow()+1;
    if(row >= ui->listWidget->count()){
        row = 0;
    }
    ui->listWidget->setCurrentRow(row);
    ui->replayButton->setEnabled(true);
}

void MainWindow::on_connectionButton_clicked()
{
    connectionColor = machine->connectionButton();
    if(connectionColor == 2){
        ui->connectionButton->setStyleSheet("background-color:green");
    }else if(connectionColor == 5){
        ui->connectionButton->setStyleSheet("background-color:yellow");
    }else{
        ui->connectionButton->setStyleSheet("background-color:red");
    }
    //Flicks connection light
    if(ui->connectionButton->isChecked()){
        QTimer::singleShot(10,[this](){
             ui->connectionButton->setVisible(false);
        QTimer::singleShot(500,[this](){
             ui->connectionButton->setVisible(true);
            });
        QTimer::singleShot(400,[this](){
             ui->connectionButton->setVisible(false);
            });
        QTimer::singleShot(100,[this](){
             ui->connectionButton->setVisible(true);
            });
        QTimer::singleShot(300,[this](){
             ui->connectionButton->setVisible(false);
            });
             ui->connectionButton->setVisible(true);
        });

    }

}

void MainWindow::enableType(){
    if(ui->twentyTimeButton->isChecked()||ui->fortyFiveTimeButton->isChecked()||
            ui->userDesTimeButton->isChecked()){
        ui->type1Button->setEnabled(true);
        ui->type2Button->setEnabled(true);
        ui->type3Button->setEnabled(true);
        ui->type4Button->setEnabled(true);
        ui->twentyTimeButton->setEnabled(false);
        ui->fortyFiveTimeButton->setEnabled(false);
        ui->userDesTimeButton->setEnabled(false);
        ui->connectionButton->setEnabled(false);
     }
}

void MainWindow::enableIntensity(){
    if(ui->type1Button->isChecked()||ui->type2Button->isChecked()
            ||ui->type3Button->isChecked()||ui->type4Button->isChecked()){
        qDebug() << "SELECT AN INTENSITY: ";
        ui->intensity1->setEnabled(true);
        ui->intensity2->setEnabled(true);
        ui->intensity3->setEnabled(true);
        ui->intensity4->setEnabled(true);
        ui->intensity5->setEnabled(true);
        ui->intensity6->setEnabled(true);
        ui->intensity7->setEnabled(true);
        ui->intensity8->setEnabled(true);
    }
}

void MainWindow::enableConnection(){
    if(machine->getState()==3){
        qDebug() << "Connecting..";
         ui->connectionButton->setEnabled(true);
    }
}

void MainWindow::timer(){
    int time = machine->getcurrInt();
    if(ui->connectionButton->isChecked()){
    }
}

void MainWindow::enableRecord(){
    if(ui->type1Button->isChecked()||ui->type2Button->isChecked()
            ||ui->type3Button->isChecked()||ui->type4Button->isChecked()
            && ui->intensity1->isChecked()||ui->intensity2->isChecked()||ui->intensity3->isChecked()
            ||ui->intensity4->isChecked()||ui->intensity5->isChecked()||ui->intensity6->isChecked()
            ||ui->intensity7->isChecked()||ui->intensity8->isChecked() && ui->selectButton->isChecked()){
        ui->recordButton->setEnabled(true);
    }
}

