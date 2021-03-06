/********************************************************************************
** Form generated from reading UI file 'positionsystem.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POSITIONSYSTEM_H
#define UI_POSITIONSYSTEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>
#include "qwebengineview.h"

QT_BEGIN_NAMESPACE

class Ui_PositionSystem
{
public:
    QAction *actionAcqiration;
    QAction *actionTLEupdation;
    QAction *actionLocation;
    QAction *actionsunguiyu96_gmail_com;
    QAction *actionCNT;
    QAction *actionVersion;
    QAction *actionsunguiyu96_gmail_com_2;
    QAction *actionhttps_github_com_BIOSmode;
    QAction *actionGPS_Locotion;
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *Home;
    QWebEngineView *HomWelcome;
    QWidget *GPS;
    QPushButton *GPSOpenPort;
    QLabel *GPSLati;
    QPushButton *GPSSearchPort;
    QComboBox *GPSRatecomboBox;
    QLineEdit *GPSHighlineEdit;
    QLabel *GPSHigh;
    QPushButton *GPSReceive;
    QLineEdit *GPSLonglineEdit;
    QLabel *GPSPort;
    QLineEdit *GPSSatNumlineEdit;
    QLabel *GPSTitle;
    QLabel *GPSLong;
    QLabel *GPSSatNum;
    QLabel *GPSState;
    QLineEdit *GPSLatilineEdit;
    QComboBox *GPSPortcomboBox;
    QLabel *GPSPortRate;
    QLineEdit *GPSStatelineEdit;
    QCheckBox *GPSLogcheckBox;
    QPushButton *GPSSentCommand;
    QDateTimeEdit *GPSdateTimeEdit;
    QWebEngineView *GPSMapView;
    QTextEdit *GPStextEdit;
    QLabel *GPSTitle_2;
    QPushButton *TekStartpushButton;
    QSpinBox *TekIndexEspinBox;
    QPushButton *TekEndpushButton;
    QLineEdit *TekOut_namelineEdit;
    QProgressBar *TekprogressBar;
    QLabel *TekIndexE;
    QSpinBox *TekIndexBspinBox;
    QLabel *TekOut_name;
    QLabel *TekDATA_name;
    QLabel *TekIndexB;
    QPushButton *TekWriteCpushButton;
    QLineEdit *TekDATA_namelineEdit;
    QPushButton *TekReadpushButton;
    QTextEdit *TektextEdit;
    QWidget *Acq;
    QLabel *AcqIndexE;
    QLabel *AcqDb2;
    QDoubleSpinBox *AcqDb2doubleSpinBox;
    QLabel *AcqIndexB;
    QPushButton *AcqStartpushButton;
    QLabel *AcqDb1;
    QPushButton *AcqReadApushButton;
    QProgressBar *AcqprogressBar;
    QPushButton *AcqWriteCpushButton;
    QCustomPlot *AcqFigure;
    QLineEdit *AcqDATA_namelineEdit;
    QPushButton *AcqEndpushButton;
    QLabel *AcqDATA_name;
    QTextEdit *AcqConfigtextEdit;
    QLabel *AcqOut_name;
    QDoubleSpinBox *AcqDb1doubleSpinBox;
    QLabel *AcqPro;
    QSpinBox *AcqIndexEspinBox;
    QSpinBox *AcqIndexBspinBox;
    QLineEdit *AcqOut_namelineEdit;
    QTextEdit *AcqStatetextEdit;
    QPushButton *AcqReadCpushButton;
    QWidget *Upd;
    QDateTimeEdit *UpdateTimeEdit;
    QWebEngineView *TLEVIew;
    QPushButton *UpdateTLE;
    QPushButton *IridiumNext;
    QTextEdit *UptextEdit;
    QPushButton *Iridium;
    QTextEdit *UptextEdit_2;
    QLabel *Uplabel;
    QLineEdit *UpTLElineEdit;
    QLabel *UpTLEDlabel;
    QLineEdit *UpTLEDlineEdit;
    QPushButton *UpCopypushButton;
    QLabel *UpTLElabel;
    QWidget *Loc;
    QPushButton *LocConfigRead;
    QLabel *Loclabel_2;
    QPushButton *LocMapRefCircle;
    QLineEdit *LocLongitude;
    QLabel *Loclabel_6;
    QPushButton *LocMapAll;
    QLineEdit *LocLatitude;
    QLineEdit *LocPosIterL;
    QLabel *Loclabel_5;
    QLabel *Loclabel;
    QLineEdit *LocHighlight;
    QPushButton *LocMapDisplay;
    QPushButton *LocMapOne;
    QRadioButton *LocHighAissradioButton;
    QTextEdit *LoctextEdit;
    QLabel *Loclabel_3;
    QPushButton *LocMapResCircle;
    QLabel *Loclabel_4;
    QTextEdit *LoctextEdit_2;
    QWebEngineView *LocMapView;
    QLabel *Loclabel_7;
    QPushButton *LocConfigWrite;
    QPushButton *LocStartLoc;
    QPushButton *LocEndLoc;
    QDateTimeEdit *LocdateTimeEdit;
    QProgressBar *LocprogressBar;
    QMenuBar *menubar;
    QMenu *menuPosition_System_based_on_Iridium;
    QMenu *menuCNTLab;
    QMenu *menuCreater;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PositionSystem)
    {
        if (PositionSystem->objectName().isEmpty())
            PositionSystem->setObjectName(QStringLiteral("PositionSystem"));
        PositionSystem->resize(1085, 854);
        actionAcqiration = new QAction(PositionSystem);
        actionAcqiration->setObjectName(QStringLiteral("actionAcqiration"));
        actionTLEupdation = new QAction(PositionSystem);
        actionTLEupdation->setObjectName(QStringLiteral("actionTLEupdation"));
        actionLocation = new QAction(PositionSystem);
        actionLocation->setObjectName(QStringLiteral("actionLocation"));
        actionsunguiyu96_gmail_com = new QAction(PositionSystem);
        actionsunguiyu96_gmail_com->setObjectName(QStringLiteral("actionsunguiyu96_gmail_com"));
        actionCNT = new QAction(PositionSystem);
        actionCNT->setObjectName(QStringLiteral("actionCNT"));
        actionVersion = new QAction(PositionSystem);
        actionVersion->setObjectName(QStringLiteral("actionVersion"));
        actionsunguiyu96_gmail_com_2 = new QAction(PositionSystem);
        actionsunguiyu96_gmail_com_2->setObjectName(QStringLiteral("actionsunguiyu96_gmail_com_2"));
        actionhttps_github_com_BIOSmode = new QAction(PositionSystem);
        actionhttps_github_com_BIOSmode->setObjectName(QStringLiteral("actionhttps_github_com_BIOSmode"));
        actionGPS_Locotion = new QAction(PositionSystem);
        actionGPS_Locotion->setObjectName(QStringLiteral("actionGPS_Locotion"));
        centralwidget = new QWidget(PositionSystem);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 1071, 801));
        tabWidget->setMinimumSize(QSize(0, 50));
        tabWidget->setAutoFillBackground(true);
        tabWidget->setStyleSheet(QStringLiteral("font: 16pt \"Arial\";"));
        tabWidget->setTabShape(QTabWidget::Triangular);
        Home = new QWidget();
        Home->setObjectName(QStringLiteral("Home"));
        HomWelcome = new QWebEngineView(Home);
        HomWelcome->setObjectName(QStringLiteral("HomWelcome"));
        HomWelcome->setGeometry(QRect(130, 60, 801, 711));
        HomWelcome->setStyleSheet(QStringLiteral("border:1px solid grey"));
        tabWidget->addTab(Home, QString());
        GPS = new QWidget();
        GPS->setObjectName(QStringLiteral("GPS"));
        GPSOpenPort = new QPushButton(GPS);
        GPSOpenPort->setObjectName(QStringLiteral("GPSOpenPort"));
        GPSOpenPort->setGeometry(QRect(160, 110, 161, 31));
        GPSOpenPort->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSLati = new QLabel(GPS);
        GPSLati->setObjectName(QStringLiteral("GPSLati"));
        GPSLati->setGeometry(QRect(10, 309, 61, 31));
        GPSLati->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSSearchPort = new QPushButton(GPS);
        GPSSearchPort->setObjectName(QStringLiteral("GPSSearchPort"));
        GPSSearchPort->setGeometry(QRect(10, 110, 121, 31));
        GPSSearchPort->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSRatecomboBox = new QComboBox(GPS);
        GPSRatecomboBox->setObjectName(QStringLiteral("GPSRatecomboBox"));
        GPSRatecomboBox->setGeometry(QRect(240, 150, 81, 31));
        GPSRatecomboBox->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSHighlineEdit = new QLineEdit(GPS);
        GPSHighlineEdit->setObjectName(QStringLiteral("GPSHighlineEdit"));
        GPSHighlineEdit->setGeometry(QRect(100, 390, 221, 31));
        GPSHighlineEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSHigh = new QLabel(GPS);
        GPSHigh->setObjectName(QStringLiteral("GPSHigh"));
        GPSHigh->setGeometry(QRect(10, 390, 61, 31));
        GPSHigh->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSReceive = new QPushButton(GPS);
        GPSReceive->setObjectName(QStringLiteral("GPSReceive"));
        GPSReceive->setGeometry(QRect(160, 190, 161, 31));
        GPSReceive->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSLonglineEdit = new QLineEdit(GPS);
        GPSLonglineEdit->setObjectName(QStringLiteral("GPSLonglineEdit"));
        GPSLonglineEdit->setGeometry(QRect(100, 350, 221, 31));
        GPSLonglineEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSPort = new QLabel(GPS);
        GPSPort->setObjectName(QStringLiteral("GPSPort"));
        GPSPort->setGeometry(QRect(10, 150, 81, 41));
        GPSPort->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSSatNumlineEdit = new QLineEdit(GPS);
        GPSSatNumlineEdit->setObjectName(QStringLiteral("GPSSatNumlineEdit"));
        GPSSatNumlineEdit->setGeometry(QRect(100, 232, 131, 31));
        GPSSatNumlineEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSTitle = new QLabel(GPS);
        GPSTitle->setObjectName(QStringLiteral("GPSTitle"));
        GPSTitle->setGeometry(QRect(290, 10, 481, 51));
        GPSTitle->setStyleSheet(QLatin1String("font: 100 30pt \"Times New Roman\";\n"
""));
        GPSLong = new QLabel(GPS);
        GPSLong->setObjectName(QStringLiteral("GPSLong"));
        GPSLong->setGeometry(QRect(10, 350, 71, 31));
        GPSLong->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSSatNum = new QLabel(GPS);
        GPSSatNum->setObjectName(QStringLiteral("GPSSatNum"));
        GPSSatNum->setGeometry(QRect(10, 232, 61, 31));
        GPSSatNum->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSState = new QLabel(GPS);
        GPSState->setObjectName(QStringLiteral("GPSState"));
        GPSState->setGeometry(QRect(10, 275, 61, 21));
        GPSState->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSLatilineEdit = new QLineEdit(GPS);
        GPSLatilineEdit->setObjectName(QStringLiteral("GPSLatilineEdit"));
        GPSLatilineEdit->setGeometry(QRect(100, 310, 221, 31));
        GPSLatilineEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSPortcomboBox = new QComboBox(GPS);
        GPSPortcomboBox->setObjectName(QStringLiteral("GPSPortcomboBox"));
        GPSPortcomboBox->setGeometry(QRect(60, 150, 71, 31));
        GPSPortcomboBox->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSPortRate = new QLabel(GPS);
        GPSPortRate->setObjectName(QStringLiteral("GPSPortRate"));
        GPSPortRate->setGeometry(QRect(160, 150, 61, 31));
        GPSPortRate->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSStatelineEdit = new QLineEdit(GPS);
        GPSStatelineEdit->setObjectName(QStringLiteral("GPSStatelineEdit"));
        GPSStatelineEdit->setGeometry(QRect(100, 270, 221, 31));
        GPSStatelineEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSLogcheckBox = new QCheckBox(GPS);
        GPSLogcheckBox->setObjectName(QStringLiteral("GPSLogcheckBox"));
        GPSLogcheckBox->setGeometry(QRect(250, 230, 71, 31));
        GPSLogcheckBox->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSSentCommand = new QPushButton(GPS);
        GPSSentCommand->setObjectName(QStringLiteral("GPSSentCommand"));
        GPSSentCommand->setGeometry(QRect(10, 190, 141, 31));
        GPSSentCommand->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSdateTimeEdit = new QDateTimeEdit(GPS);
        GPSdateTimeEdit->setObjectName(QStringLiteral("GPSdateTimeEdit"));
        GPSdateTimeEdit->setGeometry(QRect(10, 70, 311, 31));
        GPSdateTimeEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSMapView = new QWebEngineView(GPS);
        GPSMapView->setObjectName(QStringLiteral("GPSMapView"));
        GPSMapView->setGeometry(QRect(630, 70, 421, 351));
        GPSMapView->setStyleSheet(QLatin1String("font: 12pt \"Times New Roman\";\n"
"border:1px solid grey\n"
""));
        GPStextEdit = new QTextEdit(GPS);
        GPStextEdit->setObjectName(QStringLiteral("GPStextEdit"));
        GPStextEdit->setGeometry(QRect(340, 70, 271, 351));
        GPStextEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSTitle_2 = new QLabel(GPS);
        GPSTitle_2->setObjectName(QStringLiteral("GPSTitle_2"));
        GPSTitle_2->setGeometry(QRect(100, 440, 861, 41));
        GPSTitle_2->setStyleSheet(QLatin1String("font: 100 30pt \"Times New Roman\";\n"
""));
        TekStartpushButton = new QPushButton(GPS);
        TekStartpushButton->setObjectName(QStringLiteral("TekStartpushButton"));
        TekStartpushButton->setGeometry(QRect(10, 690, 241, 41));
        TekStartpushButton->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        TekIndexEspinBox = new QSpinBox(GPS);
        TekIndexEspinBox->setObjectName(QStringLiteral("TekIndexEspinBox"));
        TekIndexEspinBox->setGeometry(QRect(410, 580, 101, 31));
        TekIndexEspinBox->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        TekIndexEspinBox->setMaximum(100000);
        TekEndpushButton = new QPushButton(GPS);
        TekEndpushButton->setObjectName(QStringLiteral("TekEndpushButton"));
        TekEndpushButton->setGeometry(QRect(280, 690, 231, 41));
        TekEndpushButton->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        TekOut_namelineEdit = new QLineEdit(GPS);
        TekOut_namelineEdit->setObjectName(QStringLiteral("TekOut_namelineEdit"));
        TekOut_namelineEdit->setGeometry(QRect(140, 540, 371, 31));
        TekOut_namelineEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        TekprogressBar = new QProgressBar(GPS);
        TekprogressBar->setObjectName(QStringLiteral("TekprogressBar"));
        TekprogressBar->setGeometry(QRect(540, 700, 511, 31));
        TekprogressBar->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        TekprogressBar->setValue(0);
        TekIndexE = new QLabel(GPS);
        TekIndexE->setObjectName(QStringLiteral("TekIndexE"));
        TekIndexE->setGeometry(QRect(290, 580, 91, 41));
        TekIndexE->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        TekIndexBspinBox = new QSpinBox(GPS);
        TekIndexBspinBox->setObjectName(QStringLiteral("TekIndexBspinBox"));
        TekIndexBspinBox->setGeometry(QRect(140, 580, 111, 31));
        TekIndexBspinBox->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        TekOut_name = new QLabel(GPS);
        TekOut_name->setObjectName(QStringLiteral("TekOut_name"));
        TekOut_name->setGeometry(QRect(20, 540, 101, 31));
        TekOut_name->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        TekDATA_name = new QLabel(GPS);
        TekDATA_name->setObjectName(QStringLiteral("TekDATA_name"));
        TekDATA_name->setGeometry(QRect(20, 500, 101, 31));
        TekDATA_name->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        TekIndexB = new QLabel(GPS);
        TekIndexB->setObjectName(QStringLiteral("TekIndexB"));
        TekIndexB->setGeometry(QRect(20, 580, 101, 41));
        TekIndexB->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        TekWriteCpushButton = new QPushButton(GPS);
        TekWriteCpushButton->setObjectName(QStringLiteral("TekWriteCpushButton"));
        TekWriteCpushButton->setGeometry(QRect(280, 630, 231, 41));
        TekWriteCpushButton->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        TekDATA_namelineEdit = new QLineEdit(GPS);
        TekDATA_namelineEdit->setObjectName(QStringLiteral("TekDATA_namelineEdit"));
        TekDATA_namelineEdit->setGeometry(QRect(140, 500, 371, 31));
        TekDATA_namelineEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        TekReadpushButton = new QPushButton(GPS);
        TekReadpushButton->setObjectName(QStringLiteral("TekReadpushButton"));
        TekReadpushButton->setGeometry(QRect(10, 630, 241, 41));
        TekReadpushButton->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        TektextEdit = new QTextEdit(GPS);
        TektextEdit->setObjectName(QStringLiteral("TektextEdit"));
        TektextEdit->setGeometry(QRect(540, 500, 491, 171));
        TektextEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        tabWidget->addTab(GPS, QString());
        Acq = new QWidget();
        Acq->setObjectName(QStringLiteral("Acq"));
        AcqIndexE = new QLabel(Acq);
        AcqIndexE->setObjectName(QStringLiteral("AcqIndexE"));
        AcqIndexE->setGeometry(QRect(300, 500, 91, 41));
        AcqIndexE->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        AcqDb2 = new QLabel(Acq);
        AcqDb2->setObjectName(QStringLiteral("AcqDb2"));
        AcqDb2->setGeometry(QRect(290, 560, 121, 41));
        AcqDb2->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        AcqDb2doubleSpinBox = new QDoubleSpinBox(Acq);
        AcqDb2doubleSpinBox->setObjectName(QStringLiteral("AcqDb2doubleSpinBox"));
        AcqDb2doubleSpinBox->setGeometry(QRect(420, 560, 101, 31));
        AcqDb2doubleSpinBox->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        AcqIndexB = new QLabel(Acq);
        AcqIndexB->setObjectName(QStringLiteral("AcqIndexB"));
        AcqIndexB->setGeometry(QRect(30, 500, 101, 41));
        AcqIndexB->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        AcqStartpushButton = new QPushButton(Acq);
        AcqStartpushButton->setObjectName(QStringLiteral("AcqStartpushButton"));
        AcqStartpushButton->setGeometry(QRect(20, 690, 231, 41));
        AcqStartpushButton->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        AcqDb1 = new QLabel(Acq);
        AcqDb1->setObjectName(QStringLiteral("AcqDb1"));
        AcqDb1->setGeometry(QRect(30, 560, 121, 41));
        AcqDb1->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        AcqReadApushButton = new QPushButton(Acq);
        AcqReadApushButton->setObjectName(QStringLiteral("AcqReadApushButton"));
        AcqReadApushButton->setGeometry(QRect(20, 620, 151, 41));
        AcqReadApushButton->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        AcqprogressBar = new QProgressBar(Acq);
        AcqprogressBar->setObjectName(QStringLiteral("AcqprogressBar"));
        AcqprogressBar->setGeometry(QRect(550, 700, 511, 31));
        AcqprogressBar->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        AcqprogressBar->setValue(0);
        AcqWriteCpushButton = new QPushButton(Acq);
        AcqWriteCpushButton->setObjectName(QStringLiteral("AcqWriteCpushButton"));
        AcqWriteCpushButton->setGeometry(QRect(370, 620, 151, 41));
        AcqWriteCpushButton->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        AcqFigure = new QCustomPlot(Acq);
        AcqFigure->setObjectName(QStringLiteral("AcqFigure"));
        AcqFigure->setGeometry(QRect(550, 210, 511, 471));
        AcqFigure->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        AcqDATA_namelineEdit = new QLineEdit(Acq);
        AcqDATA_namelineEdit->setObjectName(QStringLiteral("AcqDATA_namelineEdit"));
        AcqDATA_namelineEdit->setGeometry(QRect(150, 380, 371, 31));
        AcqDATA_namelineEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        AcqEndpushButton = new QPushButton(Acq);
        AcqEndpushButton->setObjectName(QStringLiteral("AcqEndpushButton"));
        AcqEndpushButton->setGeometry(QRect(300, 690, 221, 41));
        AcqEndpushButton->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        AcqDATA_name = new QLabel(Acq);
        AcqDATA_name->setObjectName(QStringLiteral("AcqDATA_name"));
        AcqDATA_name->setGeometry(QRect(30, 380, 101, 31));
        AcqDATA_name->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        AcqConfigtextEdit = new QTextEdit(Acq);
        AcqConfigtextEdit->setObjectName(QStringLiteral("AcqConfigtextEdit"));
        AcqConfigtextEdit->setGeometry(QRect(30, 100, 491, 251));
        AcqConfigtextEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        AcqOut_name = new QLabel(Acq);
        AcqOut_name->setObjectName(QStringLiteral("AcqOut_name"));
        AcqOut_name->setGeometry(QRect(30, 440, 101, 31));
        AcqOut_name->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        AcqDb1doubleSpinBox = new QDoubleSpinBox(Acq);
        AcqDb1doubleSpinBox->setObjectName(QStringLiteral("AcqDb1doubleSpinBox"));
        AcqDb1doubleSpinBox->setGeometry(QRect(150, 560, 111, 31));
        AcqDb1doubleSpinBox->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        AcqPro = new QLabel(Acq);
        AcqPro->setObjectName(QStringLiteral("AcqPro"));
        AcqPro->setGeometry(QRect(340, 20, 431, 51));
        AcqPro->setStyleSheet(QLatin1String("font: 100 30pt \"Times New Roman\";\n"
""));
        AcqIndexEspinBox = new QSpinBox(Acq);
        AcqIndexEspinBox->setObjectName(QStringLiteral("AcqIndexEspinBox"));
        AcqIndexEspinBox->setGeometry(QRect(420, 500, 101, 31));
        AcqIndexEspinBox->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        AcqIndexBspinBox = new QSpinBox(Acq);
        AcqIndexBspinBox->setObjectName(QStringLiteral("AcqIndexBspinBox"));
        AcqIndexBspinBox->setGeometry(QRect(150, 500, 111, 31));
        AcqIndexBspinBox->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        AcqOut_namelineEdit = new QLineEdit(Acq);
        AcqOut_namelineEdit->setObjectName(QStringLiteral("AcqOut_namelineEdit"));
        AcqOut_namelineEdit->setGeometry(QRect(150, 440, 371, 31));
        AcqOut_namelineEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        AcqStatetextEdit = new QTextEdit(Acq);
        AcqStatetextEdit->setObjectName(QStringLiteral("AcqStatetextEdit"));
        AcqStatetextEdit->setGeometry(QRect(550, 100, 511, 91));
        AcqStatetextEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        AcqReadCpushButton = new QPushButton(Acq);
        AcqReadCpushButton->setObjectName(QStringLiteral("AcqReadCpushButton"));
        AcqReadCpushButton->setGeometry(QRect(200, 620, 141, 41));
        AcqReadCpushButton->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        tabWidget->addTab(Acq, QString());
        Upd = new QWidget();
        Upd->setObjectName(QStringLiteral("Upd"));
        UpdateTimeEdit = new QDateTimeEdit(Upd);
        UpdateTimeEdit->setObjectName(QStringLiteral("UpdateTimeEdit"));
        UpdateTimeEdit->setGeometry(QRect(880, 90, 181, 31));
        UpdateTimeEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        TLEVIew = new QWebEngineView(Upd);
        TLEVIew->setObjectName(QStringLiteral("TLEVIew"));
        TLEVIew->setGeometry(QRect(30, 220, 571, 451));
        TLEVIew->setStyleSheet(QStringLiteral("border:1px solid grey"));
        UpdateTLE = new QPushButton(Upd);
        UpdateTLE->setObjectName(QStringLiteral("UpdateTLE"));
        UpdateTLE->setGeometry(QRect(730, 90, 131, 31));
        UpdateTLE->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        IridiumNext = new QPushButton(Upd);
        IridiumNext->setObjectName(QStringLiteral("IridiumNext"));
        IridiumNext->setGeometry(QRect(360, 90, 351, 31));
        IridiumNext->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        UptextEdit = new QTextEdit(Upd);
        UptextEdit->setObjectName(QStringLiteral("UptextEdit"));
        UptextEdit->setGeometry(QRect(30, 140, 571, 71));
        UptextEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        Iridium = new QPushButton(Upd);
        Iridium->setObjectName(QStringLiteral("Iridium"));
        Iridium->setGeometry(QRect(30, 90, 311, 31));
        Iridium->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        UptextEdit_2 = new QTextEdit(Upd);
        UptextEdit_2->setObjectName(QStringLiteral("UptextEdit_2"));
        UptextEdit_2->setGeometry(QRect(620, 140, 441, 531));
        UptextEdit_2->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        Uplabel = new QLabel(Upd);
        Uplabel->setObjectName(QStringLiteral("Uplabel"));
        Uplabel->setGeometry(QRect(370, 30, 371, 31));
        Uplabel->setStyleSheet(QLatin1String("font: 100 30pt \"Times New Roman\";\n"
""));
        UpTLElineEdit = new QLineEdit(Upd);
        UpTLElineEdit->setObjectName(QStringLiteral("UpTLElineEdit"));
        UpTLElineEdit->setGeometry(QRect(810, 700, 251, 31));
        UpTLElineEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        UpTLEDlabel = new QLabel(Upd);
        UpTLEDlabel->setObjectName(QStringLiteral("UpTLEDlabel"));
        UpTLEDlabel->setGeometry(QRect(360, 700, 111, 41));
        UpTLEDlabel->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        UpTLEDlineEdit = new QLineEdit(Upd);
        UpTLEDlineEdit->setObjectName(QStringLiteral("UpTLEDlineEdit"));
        UpTLEDlineEdit->setGeometry(QRect(480, 700, 251, 31));
        UpTLEDlineEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        UpCopypushButton = new QPushButton(Upd);
        UpCopypushButton->setObjectName(QStringLiteral("UpCopypushButton"));
        UpCopypushButton->setGeometry(QRect(260, 700, 91, 41));
        UpCopypushButton->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        UpTLElabel = new QLabel(Upd);
        UpTLElabel->setObjectName(QStringLiteral("UpTLElabel"));
        UpTLElabel->setGeometry(QRect(740, 700, 71, 41));
        UpTLElabel->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        tabWidget->addTab(Upd, QString());
        Loc = new QWidget();
        Loc->setObjectName(QStringLiteral("Loc"));
        LocConfigRead = new QPushButton(Loc);
        LocConfigRead->setObjectName(QStringLiteral("LocConfigRead"));
        LocConfigRead->setGeometry(QRect(50, 70, 151, 31));
        LocConfigRead->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        Loclabel_2 = new QLabel(Loc);
        Loclabel_2->setObjectName(QStringLiteral("Loclabel_2"));
        Loclabel_2->setGeometry(QRect(60, 190, 71, 41));
        Loclabel_2->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        LocMapRefCircle = new QPushButton(Loc);
        LocMapRefCircle->setObjectName(QStringLiteral("LocMapRefCircle"));
        LocMapRefCircle->setGeometry(QRect(800, 70, 141, 31));
        LocMapRefCircle->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        LocLongitude = new QLineEdit(Loc);
        LocLongitude->setObjectName(QStringLiteral("LocLongitude"));
        LocLongitude->setGeometry(QRect(160, 150, 211, 31));
        LocLongitude->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        Loclabel_6 = new QLabel(Loc);
        Loclabel_6->setObjectName(QStringLiteral("Loclabel_6"));
        Loclabel_6->setGeometry(QRect(350, 240, 21, 21));
        Loclabel_6->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        LocMapAll = new QPushButton(Loc);
        LocMapAll->setObjectName(QStringLiteral("LocMapAll"));
        LocMapAll->setGeometry(QRect(500, 70, 101, 31));
        LocMapAll->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        LocLatitude = new QLineEdit(Loc);
        LocLatitude->setObjectName(QStringLiteral("LocLatitude"));
        LocLatitude->setGeometry(QRect(160, 190, 211, 31));
        LocLatitude->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        LocPosIterL = new QLineEdit(Loc);
        LocPosIterL->setObjectName(QStringLiteral("LocPosIterL"));
        LocPosIterL->setGeometry(QRect(300, 270, 71, 31));
        LocPosIterL->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        Loclabel_5 = new QLabel(Loc);
        Loclabel_5->setObjectName(QStringLiteral("Loclabel_5"));
        Loclabel_5->setGeometry(QRect(190, 260, 101, 51));
        Loclabel_5->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        Loclabel = new QLabel(Loc);
        Loclabel->setObjectName(QStringLiteral("Loclabel"));
        Loclabel->setGeometry(QRect(60, 160, 71, 21));
        Loclabel->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        LocHighlight = new QLineEdit(Loc);
        LocHighlight->setObjectName(QStringLiteral("LocHighlight"));
        LocHighlight->setGeometry(QRect(160, 230, 171, 31));
        LocHighlight->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        LocMapDisplay = new QPushButton(Loc);
        LocMapDisplay->setObjectName(QStringLiteral("LocMapDisplay"));
        LocMapDisplay->setGeometry(QRect(390, 70, 101, 31));
        LocMapDisplay->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        LocMapOne = new QPushButton(Loc);
        LocMapOne->setObjectName(QStringLiteral("LocMapOne"));
        LocMapOne->setGeometry(QRect(610, 70, 181, 31));
        LocMapOne->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        LocHighAissradioButton = new QRadioButton(Loc);
        LocHighAissradioButton->setObjectName(QStringLiteral("LocHighAissradioButton"));
        LocHighAissradioButton->setGeometry(QRect(60, 260, 107, 51));
        LocHighAissradioButton->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        LoctextEdit = new QTextEdit(Loc);
        LoctextEdit->setObjectName(QStringLiteral("LoctextEdit"));
        LoctextEdit->setGeometry(QRect(50, 310, 321, 361));
        LoctextEdit->setStyleSheet(QStringLiteral("font: 10pt \"Times New Roman\";"));
        Loclabel_3 = new QLabel(Loc);
        Loclabel_3->setObjectName(QStringLiteral("Loclabel_3"));
        Loclabel_3->setGeometry(QRect(60, 230, 54, 31));
        Loclabel_3->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        LocMapResCircle = new QPushButton(Loc);
        LocMapResCircle->setObjectName(QStringLiteral("LocMapResCircle"));
        LocMapResCircle->setGeometry(QRect(950, 70, 111, 31));
        LocMapResCircle->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        Loclabel_4 = new QLabel(Loc);
        Loclabel_4->setObjectName(QStringLiteral("Loclabel_4"));
        Loclabel_4->setGeometry(QRect(60, 120, 41, 21));
        Loclabel_4->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        LoctextEdit_2 = new QTextEdit(Loc);
        LoctextEdit_2->setObjectName(QStringLiteral("LoctextEdit_2"));
        LoctextEdit_2->setGeometry(QRect(390, 580, 671, 161));
        LoctextEdit_2->setStyleSheet(QStringLiteral("font: 10pt \"Times New Roman\";"));
        LocMapView = new QWebEngineView(Loc);
        LocMapView->setObjectName(QStringLiteral("LocMapView"));
        LocMapView->setGeometry(QRect(390, 110, 671, 461));
        LocMapView->setStyleSheet(QLatin1String("font: 12pt \"Times New Roman\";\n"
"border:1px solid grey\n"
""));
        Loclabel_7 = new QLabel(Loc);
        Loclabel_7->setObjectName(QStringLiteral("Loclabel_7"));
        Loclabel_7->setGeometry(QRect(310, 10, 491, 51));
        Loclabel_7->setStyleSheet(QLatin1String("font: 100 30pt \"Times New Roman\";\n"
""));
        LocConfigWrite = new QPushButton(Loc);
        LocConfigWrite->setObjectName(QStringLiteral("LocConfigWrite"));
        LocConfigWrite->setGeometry(QRect(220, 70, 151, 31));
        LocConfigWrite->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        LocStartLoc = new QPushButton(Loc);
        LocStartLoc->setObjectName(QStringLiteral("LocStartLoc"));
        LocStartLoc->setGeometry(QRect(50, 710, 151, 31));
        LocStartLoc->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        LocEndLoc = new QPushButton(Loc);
        LocEndLoc->setObjectName(QStringLiteral("LocEndLoc"));
        LocEndLoc->setGeometry(QRect(220, 710, 151, 31));
        LocEndLoc->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        LocdateTimeEdit = new QDateTimeEdit(Loc);
        LocdateTimeEdit->setObjectName(QStringLiteral("LocdateTimeEdit"));
        LocdateTimeEdit->setGeometry(QRect(160, 111, 211, 31));
        LocdateTimeEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        LocprogressBar = new QProgressBar(Loc);
        LocprogressBar->setObjectName(QStringLiteral("LocprogressBar"));
        LocprogressBar->setGeometry(QRect(50, 680, 321, 23));
        LocprogressBar->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        LocprogressBar->setValue(0);
        tabWidget->addTab(Loc, QString());
        PositionSystem->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PositionSystem);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1085, 26));
        menubar->setAutoFillBackground(true);
        menuPosition_System_based_on_Iridium = new QMenu(menubar);
        menuPosition_System_based_on_Iridium->setObjectName(QStringLiteral("menuPosition_System_based_on_Iridium"));
        menuCNTLab = new QMenu(menubar);
        menuCNTLab->setObjectName(QStringLiteral("menuCNTLab"));
        menuCreater = new QMenu(menuCNTLab);
        menuCreater->setObjectName(QStringLiteral("menuCreater"));
        PositionSystem->setMenuBar(menubar);
        statusbar = new QStatusBar(PositionSystem);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        PositionSystem->setStatusBar(statusbar);

        menubar->addAction(menuPosition_System_based_on_Iridium->menuAction());
        menubar->addAction(menuCNTLab->menuAction());
        menuPosition_System_based_on_Iridium->addAction(actionAcqiration);
        menuPosition_System_based_on_Iridium->addAction(actionGPS_Locotion);
        menuPosition_System_based_on_Iridium->addAction(actionTLEupdation);
        menuPosition_System_based_on_Iridium->addAction(actionLocation);
        menuCNTLab->addAction(actionVersion);
        menuCNTLab->addAction(menuCreater->menuAction());
        menuCreater->addAction(actionsunguiyu96_gmail_com_2);
        menuCreater->addAction(actionhttps_github_com_BIOSmode);

        retranslateUi(PositionSystem);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(PositionSystem);
    } // setupUi

    void retranslateUi(QMainWindow *PositionSystem)
    {
        PositionSystem->setWindowTitle(QApplication::translate("PositionSystem", "PositionSystem", Q_NULLPTR));
        actionAcqiration->setText(QApplication::translate("PositionSystem", "Acqiration", Q_NULLPTR));
        actionTLEupdation->setText(QApplication::translate("PositionSystem", "TLEupdation", Q_NULLPTR));
        actionLocation->setText(QApplication::translate("PositionSystem", "Location", Q_NULLPTR));
        actionsunguiyu96_gmail_com->setText(QApplication::translate("PositionSystem", "sunguiyu96@gmail.com", Q_NULLPTR));
        actionCNT->setText(QApplication::translate("PositionSystem", "CNTLAB", Q_NULLPTR));
        actionVersion->setText(QApplication::translate("PositionSystem", "Version", Q_NULLPTR));
        actionsunguiyu96_gmail_com_2->setText(QApplication::translate("PositionSystem", "sunguiyu96@gmail.com", Q_NULLPTR));
        actionhttps_github_com_BIOSmode->setText(QApplication::translate("PositionSystem", "https://github.com/BIOSmode", Q_NULLPTR));
        actionGPS_Locotion->setText(QApplication::translate("PositionSystem", "GPS Locotion", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Home), QApplication::translate("PositionSystem", "HomePage", Q_NULLPTR));
        GPSOpenPort->setText(QApplication::translate("PositionSystem", "Open Port", Q_NULLPTR));
        GPSLati->setText(QApplication::translate("PositionSystem", "Latitude", Q_NULLPTR));
        GPSSearchPort->setText(QApplication::translate("PositionSystem", "Search Port", Q_NULLPTR));
        GPSRatecomboBox->clear();
        GPSRatecomboBox->insertItems(0, QStringList()
         << QApplication::translate("PositionSystem", "9600", Q_NULLPTR)
         << QApplication::translate("PositionSystem", "115200", Q_NULLPTR)
         << QApplication::translate("PositionSystem", "4800", Q_NULLPTR)
         << QApplication::translate("PositionSystem", "1200", Q_NULLPTR)
        );
        GPSHigh->setText(QApplication::translate("PositionSystem", "High", Q_NULLPTR));
        GPSReceive->setText(QApplication::translate("PositionSystem", "Receive GPS INF", Q_NULLPTR));
        GPSPort->setText(QApplication::translate("PositionSystem", "Port", Q_NULLPTR));
        GPSTitle->setText(QApplication::translate("PositionSystem", "GPS LOCATION AND LOG", Q_NULLPTR));
        GPSLong->setText(QApplication::translate("PositionSystem", "Longitude", Q_NULLPTR));
        GPSSatNum->setText(QApplication::translate("PositionSystem", "Sat Num", Q_NULLPTR));
        GPSState->setText(QApplication::translate("PositionSystem", "State", Q_NULLPTR));
        GPSPortcomboBox->clear();
        GPSPortcomboBox->insertItems(0, QStringList()
         << QApplication::translate("PositionSystem", "none", Q_NULLPTR)
        );
        GPSPortRate->setText(QApplication::translate("PositionSystem", "Port Rate", Q_NULLPTR));
        GPSLogcheckBox->setText(QApplication::translate("PositionSystem", "LOG", Q_NULLPTR));
        GPSSentCommand->setText(QApplication::translate("PositionSystem", "Sent GPS Command", Q_NULLPTR));
        GPSTitle_2->setText(QApplication::translate("PositionSystem", "TEKTRONIX DATA PRE-PROCESSING", Q_NULLPTR));
        TekStartpushButton->setText(QApplication::translate("PositionSystem", "Start Tek2File", Q_NULLPTR));
        TekEndpushButton->setText(QApplication::translate("PositionSystem", "End Tek2File", Q_NULLPTR));
        TekIndexE->setText(QApplication::translate("PositionSystem", "Index_End", Q_NULLPTR));
        TekOut_name->setText(QApplication::translate("PositionSystem", "DataOut_name", Q_NULLPTR));
        TekDATA_name->setText(QApplication::translate("PositionSystem", "DATA_name", Q_NULLPTR));
        TekIndexB->setText(QApplication::translate("PositionSystem", "Index_Begin", Q_NULLPTR));
        TekWriteCpushButton->setText(QApplication::translate("PositionSystem", "Write TEK.config", Q_NULLPTR));
        TekReadpushButton->setText(QApplication::translate("PositionSystem", "Read TEK.config", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(GPS), QApplication::translate("PositionSystem", "GPS Location", Q_NULLPTR));
        AcqIndexE->setText(QApplication::translate("PositionSystem", "Index_End", Q_NULLPTR));
        AcqDb2->setText(QApplication::translate("PositionSystem", "Db2_comparition", Q_NULLPTR));
        AcqIndexB->setText(QApplication::translate("PositionSystem", "Index_Begin", Q_NULLPTR));
        AcqStartpushButton->setText(QApplication::translate("PositionSystem", "Start Acq", Q_NULLPTR));
        AcqDb1->setText(QApplication::translate("PositionSystem", "Db1_comparition", Q_NULLPTR));
        AcqReadApushButton->setText(QApplication::translate("PositionSystem", "Read ACQ.config", Q_NULLPTR));
        AcqWriteCpushButton->setText(QApplication::translate("PositionSystem", "Write Acq.config", Q_NULLPTR));
        AcqEndpushButton->setText(QApplication::translate("PositionSystem", "End Acq", Q_NULLPTR));
        AcqDATA_name->setText(QApplication::translate("PositionSystem", "DATA_name", Q_NULLPTR));
        AcqOut_name->setText(QApplication::translate("PositionSystem", "AcqOut_name", Q_NULLPTR));
        AcqPro->setText(QApplication::translate("PositionSystem", "ACQUISITION PRO", Q_NULLPTR));
        AcqReadCpushButton->setText(QApplication::translate("PositionSystem", "Read Config", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Acq), QApplication::translate("PositionSystem", "Acquisition", Q_NULLPTR));
        UpdateTLE->setText(QApplication::translate("PositionSystem", "Update", Q_NULLPTR));
        IridiumNext->setText(QApplication::translate("PositionSystem", "Update Iridium NEXT TLE from Network", Q_NULLPTR));
        Iridium->setText(QApplication::translate("PositionSystem", "Update Iridium TLE from Network", Q_NULLPTR));
        Uplabel->setText(QApplication::translate("PositionSystem", "TLE UPDATE TOOL", Q_NULLPTR));
        UpTLEDlabel->setText(QApplication::translate("PositionSystem", " TLEDownload /", Q_NULLPTR));
        UpCopypushButton->setText(QApplication::translate("PositionSystem", "Copy", Q_NULLPTR));
        UpTLElabel->setText(QApplication::translate("PositionSystem", " to TLE /", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Upd), QApplication::translate("PositionSystem", "Update TLE ", Q_NULLPTR));
        LocConfigRead->setText(QApplication::translate("PositionSystem", "Read LOC.config", Q_NULLPTR));
        Loclabel_2->setText(QApplication::translate("PositionSystem", "Latitude", Q_NULLPTR));
        LocMapRefCircle->setText(QApplication::translate("PositionSystem", "Reference Circle", Q_NULLPTR));
        Loclabel_6->setText(QApplication::translate("PositionSystem", "m", Q_NULLPTR));
        LocMapAll->setText(QApplication::translate("PositionSystem", "Show All Pos", Q_NULLPTR));
        Loclabel_5->setText(QApplication::translate("PositionSystem", "Number of Loc", Q_NULLPTR));
        Loclabel->setText(QApplication::translate("PositionSystem", "Longitude", Q_NULLPTR));
        LocMapDisplay->setText(QApplication::translate("PositionSystem", "Show Map", Q_NULLPTR));
        LocMapOne->setText(QApplication::translate("PositionSystem", "Show Pos Sequentially", Q_NULLPTR));
        LocHighAissradioButton->setText(QApplication::translate("PositionSystem", "HighAssitant", Q_NULLPTR));
        Loclabel_3->setText(QApplication::translate("PositionSystem", "High", Q_NULLPTR));
        LocMapResCircle->setText(QApplication::translate("PositionSystem", "Result Circle", Q_NULLPTR));
        Loclabel_4->setText(QApplication::translate("PositionSystem", "Time", Q_NULLPTR));
        Loclabel_7->setText(QApplication::translate("PositionSystem", "LOCATION AND DISPLAY ", Q_NULLPTR));
        LocConfigWrite->setText(QApplication::translate("PositionSystem", "Write LOC.config", Q_NULLPTR));
        LocStartLoc->setText(QApplication::translate("PositionSystem", "Start Loc", Q_NULLPTR));
        LocEndLoc->setText(QApplication::translate("PositionSystem", "End Loc", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Loc), QApplication::translate("PositionSystem", "Location", Q_NULLPTR));
        menuPosition_System_based_on_Iridium->setTitle(QApplication::translate("PositionSystem", "Menu", Q_NULLPTR));
        menuCNTLab->setTitle(QApplication::translate("PositionSystem", "About", Q_NULLPTR));
        menuCreater->setTitle(QApplication::translate("PositionSystem", "Creater", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PositionSystem: public Ui_PositionSystem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POSITIONSYSTEM_H
