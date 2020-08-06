/************************************************************************************************************************
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
* 2020/08/03 sun 11:50:IridiumLoc.exe can be run, the Loc part is fully completed;
* 2020/08/03 sun 11:52:Added a tool to automatically copy the updated .tle to the TLE folder;
* 2020/08/03 sun 15:28:Refer to other people's Js to modify the homepage and initial page;
* 2020/08/05 sun 12:31:Modify IridiumAcq.exe mode to read its output and refresh the interface display；
* 2020/08/05 sun 19:46:Modify IridiumLoc.exe mode to read its output and refresh the interface display；
* 2020/08/05 sun 19:46:The method of determining the end of exe has been modified to make it more reliable；
* 2020/08/06 sun 00:47:Tek data preprocessing interface has been added to modify;
* 2020/08/06 sun 00:47:Location: serial number can be read and progress can be refreshed as the sunmber;
* 2020/08/07 sun 00:48:Add Icon、Title and rersion.rc for the system;
***************************************************************************************************************************/

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

    //Tek2File
    void on_TekReadpushButton_clicked();

    void on_TekWriteCpushButton_clicked();

    void on_TekStartpushButton_clicked();

    void on_TekEndpushButton_clicked();

    void refreshtekout(void);

    //Acquisition
    void on_AcqReadApushButton_clicked();

    void on_AcqReadCpushButton_clicked();

    void on_AcqWriteCpushButton_clicked();

    void on_AcqStartpushButton_clicked();

    void on_AcqEndpushButton_clicked();

    //void on_AcqRefreshpushButton_clicked();

    void refreshacqout();

    void ReadData();

    void PlotData();

    void RefreshBar(int ind);

    //Update TLE
    void on_Iridium_clicked();

    void on_IridiumNext_clicked();

    void on_UpdateTLE_clicked();

    void on_UpCopypushButton_clicked();


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

    //Mutiple Part
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

    //Location
    ititude togeod(double semimajor, double Rec_flat, double X, double Y, double Z);

    QDateTime intToQDatetime(int year,int month,int day,int hour,int minute,double second);

    void MapLoadFinished(void);
};
#endif // POSITIONSYSTEM_H
