#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_selectButton_clicked();

    void on_replayButton_clicked();

    void on_recordButton_clicked();

    void on_powerButton_clicked();

    void on_intensity1_clicked();

    void on_intensity2_clicked();

    void on_intensity3_clicked();

    void on_intensity4_clicked();

    void on_intensity5_clicked();

    void on_intensity6_clicked();

    void on_intensity7_clicked();

    void on_intensity8_clicked();

    void on_type1Button_clicked();

    void on_type2Button_clicked();

    void on_type3Button_clicked();

    void on_type4Button_clicked();

    void on_twentyTimeButton_clicked();

    void on_fortyFiveTimeButton_clicked();

    void on_userDesTimeButton_clicked();

    void on_upButton_clicked();

    void on_downButton_clicked();

    void on_connectionButton_clicked();

    void enableType();
    void enableIntensity();
    void enableConnection();
    void timer();
    void enableRecord();

    //void on_startButton_clicked();

private:
    Ui::MainWindow *ui;

    //QTimer* stime;
};
#endif // MAINWINDOW_H
