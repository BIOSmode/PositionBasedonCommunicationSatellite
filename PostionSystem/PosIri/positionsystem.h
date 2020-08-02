/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* The overall interface program based on the positioning of the Communication Satellite signal,
* can cooperate with Novelta to achieve GPS reference recording
* input：Hardware collection data + TLE
* output：
* Process：
* 2020/08/01 sun 20:52:The basic framework of the overall program is built;
* 2020/08/01 sun 20:52:GPS and TLE Part are completed；
* 2020/08/02 sun 19:12:Acquisiton Part is completed；
* 2020/08/02 sun 20:13:Position part's interface redeployment is completed;
* 2020/08/02 sun 23:23:Position part's original function is completed;
* 2020/08/03 sun 00:34:Almost all parts are completed;
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

    //Location
    struct ititude
    {
        double latitude;
        double longitude;
        double h;
    };

private slots:

    //GPS Loc and Log
    void on_GPSSearchPort_clicked();

    void ReadPort();

    void on_GPSOpenPort_clicked();

    void on_GPSReceive_clicked();

    void on_GPSSentCommand_clicked();

    //Acquisition
    void on_AcqReadApushButton_clicked();

    void on_AcqReadCpushButton_clicked();

    void on_AcqWriteCpushButton_clicked();

    void on_AcqStartpushButton_clicked();

    void on_AcqEndpushButton_clicked();

    void on_AcqRefreshpushButton_clicked();

    void refreshacqout();

    void ReadData();

    void PlotData();

    void RefreshBar();

    //Update TLE
    void on_Iridium_clicked();

    void on_IridiumNext_clicked();

    void on_UpdateTLE_clicked();

    void timerUpdate();

    //Location
    void on_LocConfigRead_clicked();

    void on_LocConfigWrite_clicked();

    void on_LocMapDisplay_clicked();

    void on_LocMapAll_clicked();

    void on_LocMapOne_clicked();

    void on_LocMapRefCircle_clicked();

    void on_LocMapResCircle_clicked();

    void on_LocStartLoc_clicked();

    void on_LocEndLoc_clicked();

    void refreshlocout(void);

private:

    Ui::PositionSystem *ui;

    //GPS Loc and Log

    //Acquisition

    //Update TLE
    QString CalculateTimeVSTLE(QString line);

    DateTime days2ymdhms(int y,double d);

    int fix(double a);

    DateTime UTC2BJT(DateTime U);

    //Location
    ititude togeod(double semimajor, double Rec_flat, double X, double Y, double Z);

    QDateTime intToQDatetime(int year,int month,int day,int hour,int minute,double second);

    void MapLoadFinished(void);
};
#endif // POSITIONSYSTEM_H
