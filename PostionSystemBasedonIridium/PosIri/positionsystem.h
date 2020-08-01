/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* 基于铱星信号的定位的总界面程序、可配合Novelta实现GPS基准记录
* 输入：基于TEk数据处理后的数据
* 输出：
* 进程：
* 2020/08/01 sun 20:52:总程序框架基础搭成，GPS和TLE部分完成；
**********************************************************************************************/
#ifndef POSITIONSYSTEM_H
#define POSITIONSYSTEM_H

#include <QByteArray>
#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include <QDesktopWidget>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMainWindow>
#include <QMessageBox>
#include <QMetaEnum>
#include <QProcess>
#include <QScreen>
#include <QString>
#include <QtCore>
#include <QtNetwork>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QWebEngineView>


QT_BEGIN_NAMESPACE
namespace Ui { class PositionSystem; }
QT_END_NAMESPACE




class PositionSystem : public QMainWindow
{
    Q_OBJECT

public:
    PositionSystem(QWidget *parent = nullptr);
    ~PositionSystem();

    //Acquisition
    struct GPSInfo
    {
        QDateTime time;
        double latitude;
        double longitude;
        double high;
        double deltalatitude;
        double deltalongitude;
        double deltahigh;
        int satnum;
        QString sol_state;
        QString posname;
    };

    //Update TLE
    struct DateTime
    {
        int Y;
        int M;
        int D;
        int h;
        int m;
        double s;
    };

private slots:

    //GPS Loc and Log

    void on_GPSSearchPort_clicked();

    void ReadPort();

    void on_GPSOpenPort_clicked();

    void on_GPSReceive_clicked();

    void on_GPSSentCommand_clicked();

    //Acquisition



    //Update TLE
    void on_Iridium_clicked();

    void on_IridiumNext_clicked();

    void on_UpdateTLE_clicked();

    void timerUpdate();


private:
    Ui::PositionSystem *ui;

    //GPS Loc and Log

    //Acquisition

    //Update TLE
    QString CalculateTimeVSTLE(QString line);

    DateTime days2ymdhms(int y,double d);

    int fix(double a);

    DateTime UTC2BJT(DateTime U);
};
#endif // POSITIONSYSTEM_H
