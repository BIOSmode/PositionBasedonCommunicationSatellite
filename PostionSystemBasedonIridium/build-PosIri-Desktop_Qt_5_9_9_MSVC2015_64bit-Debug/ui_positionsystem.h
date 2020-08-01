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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <qwebengineview.h>

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
    QWidget *GPS;
    QPushButton *GPSOpenPort;
    QLabel *GPSLati;
    QPushButton *GPSSearchPort;
    QComboBox *GPSRatecomboBox;
    QLineEdit *GPSHighlineEdit;
    QTextEdit *GPStextEdit;
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
    QWidget *Acq;
    QWidget *Upd;
    QDateTimeEdit *UpdateTimeEdit;
    QWebEngineView *TLEVIew;
    QPushButton *UpdateTLE;
    QPushButton *IridiumNext;
    QTextEdit *UptextEdit;
    QPushButton *Iridium;
    QTextEdit *UptextEdit_2;
    QLabel *Uplabel;
    QWidget *Loc;
    QMenuBar *menubar;
    QMenu *menuPosition_System_based_on_Iridium;
    QMenu *menuCNTLab;
    QMenu *menuCreater;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PositionSystem)
    {
        if (PositionSystem->objectName().isEmpty())
            PositionSystem->setObjectName(QStringLiteral("PositionSystem"));
        PositionSystem->resize(1085, 802);
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
        tabWidget->setGeometry(QRect(10, 10, 1271, 811));
        tabWidget->setStyleSheet(QLatin1String("\n"
"QTabBar::tab{ min-height: 60px; min-width:60px;}"));
        tabWidget->setTabShape(QTabWidget::Rounded);
        Home = new QWidget();
        Home->setObjectName(QStringLiteral("Home"));
        tabWidget->addTab(Home, QString());
        GPS = new QWidget();
        GPS->setObjectName(QStringLiteral("GPS"));
        GPSOpenPort = new QPushButton(GPS);
        GPSOpenPort->setObjectName(QStringLiteral("GPSOpenPort"));
        GPSOpenPort->setGeometry(QRect(110, 210, 271, 41));
        GPSOpenPort->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSLati = new QLabel(GPS);
        GPSLati->setObjectName(QStringLiteral("GPSLati"));
        GPSLati->setGeometry(QRect(110, 499, 61, 31));
        GPSLati->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSSearchPort = new QPushButton(GPS);
        GPSSearchPort->setObjectName(QStringLiteral("GPSSearchPort"));
        GPSSearchPort->setGeometry(QRect(110, 160, 271, 41));
        GPSSearchPort->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSRatecomboBox = new QComboBox(GPS);
        GPSRatecomboBox->setObjectName(QStringLiteral("GPSRatecomboBox"));
        GPSRatecomboBox->setGeometry(QRect(260, 310, 121, 31));
        GPSRatecomboBox->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSHighlineEdit = new QLineEdit(GPS);
        GPSHighlineEdit->setObjectName(QStringLiteral("GPSHighlineEdit"));
        GPSHighlineEdit->setGeometry(QRect(200, 580, 181, 31));
        GPSHighlineEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPStextEdit = new QTextEdit(GPS);
        GPStextEdit->setObjectName(QStringLiteral("GPStextEdit"));
        GPStextEdit->setGeometry(QRect(470, 110, 481, 561));
        GPStextEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSHigh = new QLabel(GPS);
        GPSHigh->setObjectName(QStringLiteral("GPSHigh"));
        GPSHigh->setGeometry(QRect(110, 580, 61, 31));
        GPSHigh->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSReceive = new QPushButton(GPS);
        GPSReceive->setObjectName(QStringLiteral("GPSReceive"));
        GPSReceive->setGeometry(QRect(110, 630, 271, 41));
        GPSReceive->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSLonglineEdit = new QLineEdit(GPS);
        GPSLonglineEdit->setObjectName(QStringLiteral("GPSLonglineEdit"));
        GPSLonglineEdit->setGeometry(QRect(200, 540, 181, 31));
        GPSLonglineEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSPort = new QLabel(GPS);
        GPSPort->setObjectName(QStringLiteral("GPSPort"));
        GPSPort->setGeometry(QRect(110, 260, 81, 31));
        GPSPort->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSSatNumlineEdit = new QLineEdit(GPS);
        GPSSatNumlineEdit->setObjectName(QStringLiteral("GPSSatNumlineEdit"));
        GPSSatNumlineEdit->setGeometry(QRect(200, 420, 91, 31));
        GPSSatNumlineEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSTitle = new QLabel(GPS);
        GPSTitle->setObjectName(QStringLiteral("GPSTitle"));
        GPSTitle->setGeometry(QRect(260, 30, 481, 51));
        GPSTitle->setStyleSheet(QLatin1String("font: 100 30pt \"Times New Roman\";\n"
""));
        GPSLong = new QLabel(GPS);
        GPSLong->setObjectName(QStringLiteral("GPSLong"));
        GPSLong->setGeometry(QRect(110, 540, 71, 31));
        GPSLong->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSSatNum = new QLabel(GPS);
        GPSSatNum->setObjectName(QStringLiteral("GPSSatNum"));
        GPSSatNum->setGeometry(QRect(110, 420, 61, 31));
        GPSSatNum->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSState = new QLabel(GPS);
        GPSState->setObjectName(QStringLiteral("GPSState"));
        GPSState->setGeometry(QRect(110, 465, 61, 21));
        GPSState->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSLatilineEdit = new QLineEdit(GPS);
        GPSLatilineEdit->setObjectName(QStringLiteral("GPSLatilineEdit"));
        GPSLatilineEdit->setGeometry(QRect(200, 500, 181, 31));
        GPSLatilineEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSPortcomboBox = new QComboBox(GPS);
        GPSPortcomboBox->setObjectName(QStringLiteral("GPSPortcomboBox"));
        GPSPortcomboBox->setGeometry(QRect(260, 260, 121, 31));
        GPSPortcomboBox->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSPortRate = new QLabel(GPS);
        GPSPortRate->setObjectName(QStringLiteral("GPSPortRate"));
        GPSPortRate->setGeometry(QRect(110, 310, 91, 31));
        GPSPortRate->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSStatelineEdit = new QLineEdit(GPS);
        GPSStatelineEdit->setObjectName(QStringLiteral("GPSStatelineEdit"));
        GPSStatelineEdit->setGeometry(QRect(200, 460, 181, 31));
        GPSStatelineEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSLogcheckBox = new QCheckBox(GPS);
        GPSLogcheckBox->setObjectName(QStringLiteral("GPSLogcheckBox"));
        GPSLogcheckBox->setGeometry(QRect(310, 418, 71, 31));
        GPSLogcheckBox->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSSentCommand = new QPushButton(GPS);
        GPSSentCommand->setObjectName(QStringLiteral("GPSSentCommand"));
        GPSSentCommand->setGeometry(QRect(110, 350, 271, 41));
        GPSSentCommand->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        GPSdateTimeEdit = new QDateTimeEdit(GPS);
        GPSdateTimeEdit->setObjectName(QStringLiteral("GPSdateTimeEdit"));
        GPSdateTimeEdit->setGeometry(QRect(110, 110, 271, 31));
        GPSdateTimeEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        tabWidget->addTab(GPS, QString());
        Acq = new QWidget();
        Acq->setObjectName(QStringLiteral("Acq"));
        tabWidget->addTab(Acq, QString());
        Upd = new QWidget();
        Upd->setObjectName(QStringLiteral("Upd"));
        UpdateTimeEdit = new QDateTimeEdit(Upd);
        UpdateTimeEdit->setObjectName(QStringLiteral("UpdateTimeEdit"));
        UpdateTimeEdit->setGeometry(QRect(880, 60, 181, 31));
        UpdateTimeEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        TLEVIew = new QWebEngineView(Upd);
        TLEVIew->setObjectName(QStringLiteral("TLEVIew"));
        TLEVIew->setGeometry(QRect(10, 190, 541, 481));
        UpdateTLE = new QPushButton(Upd);
        UpdateTLE->setObjectName(QStringLiteral("UpdateTLE"));
        UpdateTLE->setGeometry(QRect(730, 60, 131, 31));
        UpdateTLE->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        IridiumNext = new QPushButton(Upd);
        IridiumNext->setObjectName(QStringLiteral("IridiumNext"));
        IridiumNext->setGeometry(QRect(360, 60, 351, 31));
        IridiumNext->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        UptextEdit = new QTextEdit(Upd);
        UptextEdit->setObjectName(QStringLiteral("UptextEdit"));
        UptextEdit->setGeometry(QRect(10, 100, 541, 71));
        UptextEdit->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        Iridium = new QPushButton(Upd);
        Iridium->setObjectName(QStringLiteral("Iridium"));
        Iridium->setGeometry(QRect(10, 60, 331, 31));
        Iridium->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        UptextEdit_2 = new QTextEdit(Upd);
        UptextEdit_2->setObjectName(QStringLiteral("UptextEdit_2"));
        UptextEdit_2->setGeometry(QRect(570, 100, 491, 571));
        UptextEdit_2->setStyleSheet(QStringLiteral("font: 12pt \"Times New Roman\";"));
        Uplabel = new QLabel(Upd);
        Uplabel->setObjectName(QStringLiteral("Uplabel"));
        Uplabel->setGeometry(QRect(370, 10, 371, 31));
        Uplabel->setStyleSheet(QLatin1String("font: 100 30pt \"Times New Roman\";\n"
""));
        tabWidget->addTab(Upd, QString());
        Loc = new QWidget();
        Loc->setObjectName(QStringLiteral("Loc"));
        tabWidget->addTab(Loc, QString());
        PositionSystem->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PositionSystem);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1085, 22));
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

        tabWidget->setCurrentIndex(1);


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
        tabWidget->setTabText(tabWidget->indexOf(GPS), QApplication::translate("PositionSystem", "GPS Location", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Acq), QApplication::translate("PositionSystem", "Acquisition", Q_NULLPTR));
        UpdateTLE->setText(QApplication::translate("PositionSystem", "Update", Q_NULLPTR));
        IridiumNext->setText(QApplication::translate("PositionSystem", "Update Iridium NEXT TLE from Network", Q_NULLPTR));
        Iridium->setText(QApplication::translate("PositionSystem", "Update Iridium TLE from Network", Q_NULLPTR));
        Uplabel->setText(QApplication::translate("PositionSystem", "TLE UPDATE TOOL", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Upd), QApplication::translate("PositionSystem", "Update TLE ", Q_NULLPTR));
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
