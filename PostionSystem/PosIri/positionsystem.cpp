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
* 2020/08/06 sun 00:47:Location: serial number can be read and progress can be refreshed as the number;
* 2020/08/07 sun 00:48:Add Icon、Title and rersion.rc for the system;
* 2020/08/12 sun 15:38:Added multiple capture modes: including multi-process, and capture after preprocessing;
* 2020/08/12 sun 18:26:Modified the way to judge the end of the Acqisition;
* 2020/08/13 sun 13:38:Modified GPS page, added TekAPI-based deployed and collection function;
* 2020/09/01 sun 15:07:Added TekAPI-based external Ref input and external Tirgger,and displayed progress in a bar;
***************************************************************************************************************************/

#include "positionsystem.h"
#include "ui_positionsystem.h"

#include <QWebEngineView>

PositionSystem::PositionSystem(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PositionSystem)
{
    ui->setupUi(this);

    //set Icon and Title
    setWindowIcon(QIcon(":/image/position.ico"));
    setWindowTitle("IPoS -- IPositon System");

    //In order to show current time
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);

    //Set the range of the serial number Index in Acqsition part
    ui->AcqIndexBspinBox->setRange(0,100000);
    ui->AcqIndexEspinBox->setRange(0,100000);

    //Set GPS Location's button disabled
    ui->GPSOpenPort->setEnabled(false);
    ui->GPSSentCommand->setEnabled(false);
    ui->GPSReceive->setEnabled(false);

    //Set Tek2File's button disabled
    ui->TekWriteCpushButton->setEnabled(false);
    ui->TekStartpushButton->setEnabled(false);
    ui->TekEndpushButton->setEnabled(false);

    //Set Acqisition's button disabled
    ui->AcqWriteCpushButton->setEnabled(false);
    ui->AcqStartpushButton->setEnabled(false);
    ui->AcqEndpushButton->setEnabled(false);

    //Set TLEUpdate's button disabled
    ui->UpCopypushButton->setEnabled(false);

    //Set Location's button disabled
    ui->LocConfigWrite->setEnabled(false);
    ui->LocMapDisplay->setEnabled(false);
    ui->LocMapAll->setEnabled(false);
    ui->LocMapOne->setEnabled(false);
    ui->LocMapRefCircle->setEnabled(false);
    ui->LocMapResCircle->setEnabled(false);
    ui->LocStartLoc->setEnabled(false);
    ui->LocEndLoc->setEnabled(false);

    //Set Homepage
    ui->tabWidget->setCurrentIndex(0);
    QString currentpath = QApplication::applicationDirPath();       //Read the path where the .exe is located
    QString path = currentpath + "/Welcome.html";
    QUrl url(path);
    ui->HomWelcome->load(url);
    ui->HomWelcome->show();

    //Initialize part of the interface
    QString pathGPS = currentpath + "/Json/GPSWelcome.html";
    QUrl urlGPS(pathGPS);
    ui->GPSMapView->load(urlGPS);
    ui->GPSMapView->show();
    QString pathUpd = currentpath + "/Json/UpdWelcome.html";
    QUrl urlUpd(pathUpd);
    ui->TLEVIew->load(urlUpd);
    ui->TLEVIew->show();
    QString pathLoc = currentpath + "/Json/LocWelcome.html";
    QUrl urlLoc(pathLoc);
    ui->LocMapView->load(urlLoc);
    ui->LocMapView->show();

    //add QButtonGroup
    AcqMode = new QButtonGroup(this);
    AcqMode->addButton(ui->AcqRawradioButton,0);
    AcqMode->addButton(ui->AcqProradioButton,1);
    AcqMode->addButton(ui->AcqSelfradioButton,2);
    connect(ui->AcqRawradioButton,SIGNAL(clicked()),this,SLOT(onAcqModeClick()));
}


PositionSystem::~PositionSystem()
{
    delete ui;
}

/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* Multiple Part
* Time update slot function
* input：
* output：
* Process：
* 2020/06/14 sun 01:08:Finished；
* 2020/08/01 sun 19:38:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::timerUpdate(void)
{
    QDateTime time = QDateTime::currentDateTime();
    //GPS
    ui->GPSdateTimeEdit->setDisplayFormat("yyyy/MM/dd  HH:mm:ss");   //设置显示格式
    ui->GPSdateTimeEdit->setDateTime(time);
    //Update
    ui->UpdateTimeEdit->setDisplayFormat("yyyy/MM/dd  HH:mm:ss");   //设置显示格式
    ui->UpdateTimeEdit->setDateTime(time);

}

/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* Multiple Part
* Time Non-blocking delay
* input：
* output：
* Process：
* 2020/06/14 sun 01:08:Finished；
* 2020/08/01 sun 19:38:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::Delay_MSec(unsigned int msec)
{
    QTime _Timer = QTime::currentTime().addMSecs(msec);

    while( QTime::currentTime() < _Timer )

    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

//GPS Loc and Log's Global Variable
QByteArray currentDATA;     //串口读取数据
QSerialPort *serial_c = new QSerialPort;        //打开并读取数据的串口
PositionSystem::GPSInfo GPSOut;     //储存所需的GPS信息
int nn = 0;         //从上一次清空text接收到的信息次数

//Tek2File's Global Variable
static int TekTotalIndex = 0;     //总的块数
static int TekBeginIndex = 0;  //起始块数
QString Tekout = "";
QString TekCout = "";
static int TekLongth_msec = 0 ;
static int TekCurrent_msec = 0;

//Acquisition's Global Variable
static int CurruntIndex = 0;
static int TotalIndex = 0;     //总的块数
static int BeginIndex = 0;  //起始块数
QVector<int>Index(10);
QVector<double>Time(10);
QVector<double>Dop(10);
QString AcqOutPathandName;
QString AcqCout = "";
int AcqExemode = 10;

//TLEupdate's Global Varible
//QString currentTLEname;

//Location's Global Variable
QString LoCoutPathandName;
QString LoCoutPathandName_L;
QVector<PositionSystem::ititude>LocData(10);
QVector<int>index(10);
static PositionSystem::ititude Loc_Ititude;
static int Iter = 0;
static int current_i = 0;
QString LocCout = "";

/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* GPS Loc and Log Part
* 自动寻找串口（为接收Novatel数据）
* input：
* output：
* Process：
* 2020/01/02 sun 12:38:开始；
* 2020/01/02 sun 19:27:达到预想效果；
* 2020/08/01 sun 20:22:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::on_GPSSearchPort_clicked()
{
    //先清空所有选项
    ui->GPSPortcomboBox->clear();
    QString SerialInfo;
    int n = 0;
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;

        serial.setPort(info);
        SerialInfo = SerialInfo + "Name : " + info.portName() + "\nDescription : " + info.description() + "\n";
        ui->GPStextEdit->setPlainText(SerialInfo);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->GPSPortcomboBox->addItem(serial.portName());
            serial.close();
            n++;
        }
    }//查找可用串口并加入下拉列表

    //设置下拉列表默认最后一项
    ui->GPSPortcomboBox->setCurrentIndex(n-1);

//    ui->comboBox->setEnabled(false);        //关闭该选项

    //Set GPS Location's button disabled
    ui->GPSOpenPort->setEnabled(true);
}

/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* GPS Loc and Log Part
* Receive serial port data, subcontract and display on the interface (for receiving Novatel data)
* input：
* output：Store in the GPS folder
* Process：
* 2020/01/02 sun 18:52:Start；
* 2020/01/08 sun 11:15:Achieve the desired effect；
* 2020/01/08 sun 21:10:Complete ASCII valid data separation and write file function；
* 2020/01/09 sun 00:20:Complete the subcontracting procedure according to the data head and tail；
* 2020/08/01 sun 20:31:Complete the modification to make it run within the integral program；
* 2020/08/05 sun 15:03:Show the location of the record on baidu map；
**********************************************************************************************/
void PositionSystem::ReadPort()
{
    GPSOut.time = QDateTime::currentDateTime();
    QByteArray buf;
    buf = serial_c->readAll();

//    QString buf_string = buf;
//    qDebug() << "YYY:" <<buf_string;

    //Solve the problem of incomplete data according to data subcontracting
    QByteArray ReadyDATA = NULL;
    //Headless and null variables
    if((!buf.contains("#")) & (currentDATA.isNull()))
    {
        return;
    }
    //Head and tailess,empty the contents and add more
    if((buf.contains("#")) & (!buf.contains("\n")))
    {
        currentDATA.clear();
        currentDATA.append(buf);
    }
    //Headless, tailless and variable with existing content->middle end of data, directly attached
    if((!buf.contains("#")) & (!buf.contains("\n")) & (!currentDATA.isNull()))
    {
        currentDATA.append(buf);
    }
    //Headless, tail and variable with existing content->complete reading，the output will be emptied after attachment
    if((!buf.contains("#")) & (buf.contains("\n")) & (!currentDATA.isNull()))
    {
        currentDATA.append(buf);
        ReadyDATA = currentDATA;
        currentDATA.clear();
    }
    //head and tail，first empty the original content, then attach, and then output again empty
    if((buf.contains("#")) & (buf.contains("\n")))
    {
        currentDATA.clear();
        currentDATA.append(buf);
        int b_index = currentDATA.indexOf("#");
        int e_index = currentDATA.indexOf("\n");
        ReadyDATA = currentDATA.mid(b_index,e_index - b_index);
        currentDATA.clear();
    }

    if(!ReadyDATA.isEmpty())
    {
        //Receive ASCII GPS information
        QString bufstr = ReadyDATA;
//        qDebug() << bufstr << "\n";
        int Length = 0;
        int HeaderLength = 0;
        int CRCLength = 0;
        Length = bufstr.length();
        HeaderLength = bufstr.indexOf(";");
        CRCLength = bufstr.lastIndexOf("*");
        QString datastr = bufstr.mid(HeaderLength + 1,Length - 2 - HeaderLength - CRCLength);
        QStringList datalist = datastr.split(",");
//        qDebug() << datalist[0] << datalist.length();
        GPSOut.sol_state=datalist[0];
        GPSOut.latitude = datalist[2].toDouble();
        GPSOut.longitude = datalist[3].toDouble();
        GPSOut.high = datalist[4].toDouble();
        GPSOut.deltalatitude = datalist[7].toDouble();
        GPSOut.deltalongitude = datalist[8].toDouble();
        GPSOut.deltahigh = datalist[9].toDouble();
        GPSOut.satnum = datalist[15].toInt();
//        qDebug() << datalist[15];

        //output at interface
        ui->GPSLatilineEdit->setText(datalist[2]);
        ui->GPSLonglineEdit->setText(datalist[3]);
        ui->GPSHighlineEdit->setText(datalist[4]);
        ui->GPSStatelineEdit->setText(GPSOut.sol_state);
        ui->GPSSatNumlineEdit->setText(datalist[15]);
        //output at BaiduMap
        QString currentpath = QApplication::applicationDirPath();       //Read the path where the .exe is located
        QString path = currentpath + "/LoctiononBaiduMap.html";
    //    QString path = "C:/Qt/BaiduMapTest/BaiduMap2/BaiduMap2.html";        //Fixed path
        QUrl url(path);

        ui->LocMapView->load(url);
        ui->LocMapView->show();

        QString command = QString("addpoint(%1,%2)").arg(QString::number(GPSOut.longitude)).arg(QString::number(GPSOut.latitude));
        ui->LocMapView->page()->runJavaScript(command);

        QString str = ui->GPStextEdit->toPlainText();       //Associate a string with text
        int n =0 ;
        str += QString("\n%1: ").arg(nn + 1);
        str += QDateTime::currentDateTime().toString("hh:mm:ss");
        str += "\n";

        //Output the file if the record flag is Yes
        if(ui->GPSLogcheckBox->isChecked()==true) //Record the data
        {
            //Written to the file
            QString currentpath = QApplication::applicationDirPath();       //Read in the path of .exe
            QString logpath = currentpath + "/GPS/";
            QString filename = logpath + GPSOut.posname;
            QString strout;
            if(filename.isEmpty() == false)
            {
                QFile file(filename);
                bool isok = file.open(QIODevice::WriteOnly|QIODevice::Append);
                if(isok == true)
                {
                    strout = GPSOut.time.toString("yyyy-MM-dd hh:mm:ss") + " ";
                    strout = strout + QString::number(GPSOut.latitude,'f',8) + " " + QString::number(GPSOut.longitude,'f',8)+ " " + QString::number(GPSOut.high,'f',8) + " ";
                    strout = strout + QString::number(GPSOut.deltalatitude,'f',8) + " " + QString::number(GPSOut.deltalongitude,'f',8)+ " " + QString::number(GPSOut.deltahigh,'f',8) + " " + QString::number(GPSOut.satnum) +"\n";
                    file.write(strout.toUtf8());
                }
                file.close();
                str += "LOG SUCCESS\n";
            }
        }


        str += tr(ReadyDATA);
        n = str.length();
        ui->GPStextEdit->clear();
        ui->GPStextEdit->append(str);
        nn++;

    }
    if(nn > 200)            //Too much reading will block
    {
        ui->GPStextEdit->setPlainText("");
        nn = 0;
    }


}

/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* 打开串口serial_c
* input：
* output：
* Process：
* 2020/01/08 sun 21:29:开始；
* 2020/01/08 sun 21:30:达到预想效果；
* 2020/08/01 sun 20:37:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::on_GPSOpenPort_clicked()
{
    //打开串口->读取数据 步骤

    //1 设置串口名（选取串口）
    serial_c->setPortName(ui->GPSPortcomboBox->currentText());

    //2 打开串口
    serial_c->open(QIODevice::ReadWrite);

    //3 设置波特率
    //qDebug() << ui->GPSRatecomboBox->currentText();
    serial_c->setBaudRate(ui->GPSRatecomboBox->currentText().toInt());

    //4 设置数据位
    serial_c->setDataBits(QSerialPort::Data8);

    //5 设置校验位
    serial_c->setParity(QSerialPort::NoParity);

    //6 设置停止位
    serial_c->setStopBits((QSerialPort::OneStop));

    //7 设置无流控制
    serial_c->setFlowControl(QSerialPort::NoFlowControl);

    //将选项置为关闭
    //ui->comboBox_2->setEnabled(false);

    ui->GPStextEdit->setText("Port has been opened!");
    ui->GPSSentCommand->setEnabled(true);
    ui->GPSReceive->setEnabled(true);
}

/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* 串口接收数据（为接收Novatel数据）
* input：
* output：
* Process：
* 2020/01/08 sun 21:29:开始；
* 2020/01/08 sun 21:30:达到预想效果；
* 2020/08/01 sun 20:37:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::on_GPSReceive_clicked()
{
    //清空缓存中之前读取的数据
    QByteArray buf;
    buf = serial_c->readAll();

    //串口读取
    QObject::connect(serial_c,&QSerialPort::readyRead,this,&PositionSystem::ReadPort);

    //显示可读取
    QString str = ui->GPStextEdit->toPlainText();
    QString DStr = str + "\nReady to read " + ui->GPSPortcomboBox->currentText();
    ui->GPStextEdit->setPlainText(DStr);

    //得到GPS信息output文件的文件名
    QDateTime currenttime = QDateTime::currentDateTime();
    GPSOut.posname = currenttime.toString("yyyy_MM_dd_hh_mm_ss") + ".txt";
}

/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* 从串口发送命令（为接收Novatel数据）
* input：
* output：
* Process：
* 2020/01/08 sun 21:29:开始；
* 2020/01/08 sun 21:30:达到预想效果；
* 2020/08/01 sun 20:44:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::on_GPSSentCommand_clicked()
{
    QString command = "log bestposa ontime 1";
    serial_c->write(command.toUtf8());
    QString str = ui->GPStextEdit->toPlainText();
    ui->GPStextEdit->setText(str + "\n" + "Command has been sent!");
}

/*********************************************************************************************
* sun 20200813
* By sunguiyu96@gmail.com
* Tek2File Part
* Read information, deploy r3fcapture.bat and start r3fcapture.exe
* input:
* output:
* Process:
* 2020/08/13 sun 12:49:Complete the modification to make it run within the integral program；
* 2020/08/13 sun 13:37:Finished moditfication；
* 2020/08/27 sun 19:45:Add External Rel input option;
* 2020/08/31 sun 15:34:Add External Trigger option;
**********************************************************************************************/
void PositionSystem::on_TekCapturepushButton_clicked()
{
    //Call r3fcature.bat in this folder
    QString currentpath = QApplication::applicationDirPath();       //Read the path where the .rat is located
    QString batpath = currentpath + "/r3fcapture/r3fcapture.bat";
    QString workpath = currentpath + "/r3fcapture";

    if(batpath.isEmpty() == false)
    {
        QFile file(batpath);
        bool isok = file.open(QIODevice::WriteOnly);     //Open the file as read-only
        if(isok == true)
        {
            int DEV = ui->TekDEV_lineEdit->text().toInt();           // ID of device connect
            int RL= ui->TekRL_lineEdit->text().toInt();          //Reference Level
            double CF = ui->TekCF_lineEdit->text().toDouble();       //Center Frequency  MHz
            double SEC = ui->TekTREC_lineEdit->text().toDouble();       //Output time length in sec
            int MSEC = SEC * 1000;      //Output time length in msec
            TekLongth_msec = MSEC;
            QString FP = ui->TekFP_lineEdit->text();     // Output File Path

            //qDebug() << "DEV=" << DEV << " RL=" << RL << " FP=" << FP << endl;

            //set bat contains
            QString bat;
            bat = ":run\nr3fcapture dev=" + QString::number(DEV);
            if(ui->TekExtcheckBox->isChecked())
            {
                bat = bat + " extref";      //set external Ref input true;
            }
            if(ui->TekTricomboBox->currentIndex() == 1)
            {
                bat = bat + " trig=100";        //set external trigger
                bat = bat + " trigx=1";         //Set rising edge trigger
            }
            if(ui->TekTricomboBox->currentIndex() == 2)
            {
                bat = bat + " trig=100";        //set external trigger
                bat = bat + " trigx=-1";         //Set falling edge trigger
            }
            bat = bat + " rl=" + QString::number(RL) + " cf=" + QString::number(CF)
                    + "e6 msec=" + QString::number(MSEC) + " fp=" + FP + " fn=I fnsfx=-1 fm=0";

            //qDebug() << bat << endl;
            file.write(bat.toUtf8());
        }
        file.close();
    }

    //QMessageBox::warning(0,"PATH",exepath,QMessageBox::Yes);

    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_dt =current_date_time.toString("\nyyyy.MM.dd hh:mm:ss");
    QString currentText = ui->TektextEdit->toPlainText();
    ui->TektextEdit->setText(currentText + "\n" + current_dt + ":C3FCAPTURE.BAT HAS DEPLOYED!!  \n");
    //Keep it at the bottom
    QTextCursor cursor = ui->TektextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->TektextEdit->setTextCursor(cursor);

    QProcess *TekProcess;
    if (QFileInfo(batpath).exists())
    {
        TekProcess = new QProcess(this);
        connect(TekProcess, SIGNAL(readyRead()),this, SLOT(refreshTekout()));
        QStringList TekList("R3fcapture is running...");
        TekProcess->setWorkingDirectory(workpath);
        TekProcess->start(batpath,TekList);
       //AcqProcess->startDetached(exepath,QStringList(),workpath);

        //In order to show current time
        QTimer *timer1 = new QTimer(this);
        connect(timer1,SIGNAL(timeout()),this,SLOT(TekCapProgressbarUpdate()));
        timer1->start(1000);

        current_date_time =QDateTime::currentDateTime();
        current_dt =current_date_time.toString("\nyyyy.MM.dd hh:mm:ss");
        currentText = ui->TektextEdit->toPlainText();
        ui->TektextEdit->setText(currentText + "\n" + current_dt + ":C3FCAPTURE.BAT HAS STARTED!!  \n");
        //Keep it at the bottom
        cursor = ui->TektextEdit->textCursor();
        cursor.movePosition(QTextCursor::End);
        ui->TektextEdit->setTextCursor(cursor);
    }

}

/*********************************************************************************************
* sun 20200827
* By sunguiyu96@gmail.com
* Location Part
* turn off R3Fcapture.exe
* input:
* output:
* Process:
* 2020/08/27 sun 19:55:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::on_TekEndCapturepushButton_clicked()
{
    QString c = "taskkill /im R3Fcapture.exe /f";
    int pInt = QProcess::execute(c);    //Close the background R3Fcaptyre.exe Process, blocking operation, always occupy the cpu, success returns 0, failure returns 1
    if(pInt == 0)
    {
        QMessageBox::warning(0,"PATH","SUCCESS KILL R3FCAPTURE.EXE!",QMessageBox::Yes);
    }
}

/*********************************************************************************************
* sun 20200827
* By sunguiyu96@gmail.com
* Tek2File Part
* Read R3FCapture.bat's std out
* input：
* output：
* Process：
* 2020/08/27 sun 19:27:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::refreshTekout(void)
{
    QProcess *AcqProcess = (QProcess *)sender();
    QString TekCout1 = AcqProcess->readAll();
    Tekout += TekCout1;

    QString currentText = ui->TektextEdit->toPlainText();
    ui->TektextEdit->setText(currentText + "\n" + Tekout);
    //Move the cursor to the end
    QTextCursor cursor = ui->TektextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->TektextEdit->setTextCursor(cursor);
}

/*********************************************************************************************
* sun 20200831
* By sunguiyu96@gmail.com
* Tek2File Part
* Refresh TekCap Progress bar
* input：
* output：
* Process：
* 2020/08/31 sun 15:49:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::TekCapProgressbarUpdate()
{
    if(TekCurrent_msec < TekLongth_msec)
    {
        TekCurrent_msec += 1000;
        int value = (TekCurrent_msec * 100) / TekLongth_msec ;
        //qDebug() << value << "="<<TekCurrent_msec << "/" << TekLongth_msec << endl;
        ui->TekCapprogressBar->setValue(value);
    }
}
/*********************************************************************************************
* sun 20200805
* By sunguiyu96@gmail.com
* Tek2File Part
* Read TEK.conifg
* input:
* output:
* Process:
* 2020/08/05 sun 23:46:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::on_TekReadpushButton_clicked()
{
    //Read TEk.config（The default configuration file）
    QString currentpath = QApplication::applicationDirPath();       //Read in the path of .exe
    QString configpath = currentpath + "/config/" + "Tek.config";
    QString filename = configpath;
    if(filename.isEmpty() == false)
    {
        QFile file(filename);
        bool isok = file.open(QIODevice::ReadOnly);     //Open the file as read-only
        if(isok == true)
        {
            QByteArray array;
            QByteArray configline;
            int index_b=0,index_e=0;
            while(file.atEnd() == false)
            {
                configline = file.readLine();      //For each row read
                array += configline;        //stores the reads in the file in a byte array
                QString tekline;
                tekline.prepend(configline);
//              qDebug() << acqline;

                //Gets the input data's path and name
                if(tekline[0]=="D" && tekline[1]=="A")
                {
                    QString DataName;
                    int n_name = tekline.length() - 13;
                    DataName = tekline.mid(11,n_name);
                    ui->TekDATA_namelineEdit->setText(DataName);
                }
                //Gets the output file's path and name
                if(tekline[0]=="o" && tekline[1]=="u")
                {
                    QString AcqOutName;
                    int n_name = tekline.length() - 12;
                    AcqOutName = tekline.mid(10,n_name);
                    ui->TekOut_namelineEdit->setText(AcqOutName);
                    //qDebug() <<  AcqOutPathandName;
                    //ui ->textEdit_2 ->setText(AcqOutPathandName);
                }
                //Get the total amount
                if(tekline[0]=="I" && tekline[6]=="B")
                {
                    QString i_b;
                    int n = tekline.length() - 8;
                    i_b = tekline.mid(8,n);
                    index_b = i_b.toInt();
                    TekBeginIndex = index_b;
                    ui->TekIndexBspinBox->setValue(index_b);
                }
                if(tekline[0]=="I" && tekline[6]=="E")
                {
                    QString i_e;
                    int n = tekline.length() - 8;
                    i_e = tekline.mid(8,n);
                    index_e = i_e.toInt();
                    TekTotalIndex = index_e - index_b + 1;
                    QString total = QString::number(TotalIndex);
                    ui->TektextEdit->setText("\nTek2File Total: " + total);
                    ui->TekIndexEspinBox->setValue(index_e);
                }
            }
            ui->TektextEdit->setText(array);
        }
        file.close();       //Close the file after it has been read
    }

    ui->TekWriteCpushButton->setEnabled(true);
    ui->TekStartpushButton->setEnabled(true);
    ui->TekEndpushButton->setEnabled(true);
}

/*********************************************************************************************
* sun 20200805
* By sunguiyu96@gmail.com
* Tek2File Part
* Write TEK.conifg
* input:
* output:
* Process:
* 2020/08/05 sun 23:57:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::on_TekWriteCpushButton_clicked()
{
    //Write config
    QString currentpath = QApplication::applicationDirPath();       //读入.exe所在的路径
    QString configpath = currentpath + "/config/";
    //QString filename = QFileDialog::getOpenFileName(this, "打开文件", configpath, "config files(*.config);;Txt(*.txt)");
    QString filename = configpath + "TEK.config";
    QString str;
    if(filename.isEmpty() == false)
    {
        QFile file(filename);
        bool isok = file.open(QIODevice::WriteOnly);
        if(isok == true)
        {
            //Reading information from the interface is overridden
            str = "20200805TekV1.2\n\n";
            str += "#TEK\n";
            QString DataName;
            DataName = ui->TekDATA_namelineEdit->text();
            str = str + "DATA_name:\"" + DataName + "\"\n";
            QString OutName;
            OutName = ui->TekOut_namelineEdit->text();
            str = str + "out_name:\"" + OutName + "\"\n";
            int index1;
            index1 = ui->TekIndexBspinBox->value();
            str = str + "INDEX_B:" + QString::number(index1) +"\n";
            index1 = ui->TekIndexEspinBox->value();
            str = str + "INDEX_E:" + QString::number(index1) +"\n";
            double db;
            file.write(str.toUtf8());
        }
        file.close();
        //ui->AcqConfigtextEdit->setText(str + "\n" + "Write " + filename + " OK!!");
    }

    //Read the config file written above (the default configuration file)
    if(filename.isEmpty() == false)
    {
        QFile file(filename);
        bool isok = file.open(QIODevice::ReadOnly);     //Open the file as read-only
        if(isok == true)
        {
            QByteArray array;
            QByteArray configline;
            int index_b=0,index_e=0;
            while(file.atEnd() == false)
            {
                configline = file.readLine();      //For each row read
                array += configline;        //stores the reads in the file in a byte array
                QString tekline;
                tekline.prepend(configline);
//              qDebug() << acqline;

                //Gets the input data's path and name
                if(tekline[0]=="D" && tekline[1]=="A")
                {
                    QString DataName;
                    int n_name = tekline.length() - 13;
                    DataName = tekline.mid(11,n_name);
                    ui->TekDATA_namelineEdit->setText(DataName);
                }
                //Gets the output file's path and name
                if(tekline[0]=="o" && tekline[1]=="u")
                {
                    QString AcqOutName;
                    int n_name = tekline.length() - 12;
                    AcqOutName = tekline.mid(10,n_name);
                    ui->TekOut_namelineEdit->setText(AcqOutName);
                    //qDebug() <<  AcqOutPathandName;
                    //ui ->textEdit_2 ->setText(AcqOutPathandName);
                }
                //Get the total amount
                if(tekline[0]=="I" && tekline[6]=="B")
                {
                    QString i_b;
                    int n = tekline.length() - 8;
                    i_b = tekline.mid(8,n);
                    index_b = i_b.toInt();
                    TekBeginIndex = index_b;
                    ui->TekIndexBspinBox->setValue(index_b);
                }
                if(tekline[0]=="I" && tekline[6]=="E")
                {
                    QString i_e;
                    int n = tekline.length() - 8;
                    i_e = tekline.mid(8,n);
                    index_e = i_e.toInt();
                    TekTotalIndex = index_e - index_b + 1;
                    QString total = QString::number(TotalIndex);
                    ui->TektextEdit->setText("\nTek2File Total: " + total);
                    ui->TekIndexEspinBox->setValue(index_e);
                }
            }
            ui->TektextEdit->setText(array);
        }
        file.close();       //Close the file after it has been read
    }


    //Write success signs
    QString currentText = ui->TektextEdit->toPlainText();
    ui->TektextEdit->setText(currentText + "\n\nWrite " + filename + " OK!!");
    //Keep at the bottom
    QTextCursor cursor = ui->TektextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->TektextEdit->setTextCursor(cursor);
}

/*********************************************************************************************
* sun 20200805
* By sunguiyu96@gmail.com
* Tek2File Part
* Run Tek2File.exe
* input:
* output:
* Process:
* 2020/08/06 sun 00:10:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::on_TekStartpushButton_clicked()
{
    //Run Tek2File.exe
    QString currentpath = QApplication::applicationDirPath();       //Read in the path of. Exe
    QString exepath = currentpath + "/Tek2File.exe";
    //qDebug() << "exepath:" << exepath << endl;
    QString workpath = currentpath;
    //QMessageBox::warning(0,"PATH",exepath,QMessageBox::Yes);           //View current path

    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_dt =current_date_time.toString("\nyyyy.MM.dd hh:mm:ss");
    QString currentText = ui->TektextEdit->toPlainText();
    ui->TektextEdit->setText(currentText + "\n\n" + current_dt + ":TEK@FILE.EXE HAS START!!  \n");
    //使保持在最下面
    QTextCursor cursor = ui->TektextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->TektextEdit->setTextCursor(cursor);

    QProcess *TekProcess;
    if (QFileInfo(exepath).exists())
    {
        TekProcess = new QProcess(this);
        connect(TekProcess, SIGNAL(readyRead()),this, SLOT(refreshtekout()));
        QStringList AcqList("TEK is running...");
        TekProcess->setWorkingDirectory(workpath);
        TekProcess->start(exepath,AcqList);
        //AcqProcess->startDetached(exepath,QStringList(),workpath);
    }
}

/*********************************************************************************************
* sun 20200806
* By sunguiyu96@gmail.com
* Tek2File Part
* kill Tek2File.exe
* input:
* output:
* Process:
* 2020/08/06 sun 00:13:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::on_TekEndpushButton_clicked()
{
    //close Tek2File.exe Process
    QString c = "taskkill /im Tek2File.exe /f";
    int pInt = QProcess::execute(c);    //Close the background Tek2File.exeProcess, run blocking mode, using CPU all the time, return 0 on success, return 1 on failure
    if(pInt==0)
    {
        QMessageBox::warning(0,"PATH","SUCCESS KILL TEK2FILE.EXE!",QMessageBox::Yes);
    }
}

/*********************************************************************************************
* sun 20200806
* By sunguiyu96@gmail.com
* Tek2File Part
* Refresh Tek2File's std output
* input:
* output:
* Process:
* 2020/08/06 sun 00:21:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::refreshtekout(void)
{
    QProcess *TekProcess = (QProcess *)sender();
    QString TekCout1 = TekProcess->readAll();
    TekCout += TekCout1;
    ui->TektextEdit->setText(TekCout);
    //Move the cursor to the end
    QTextCursor cursor = ui->TektextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->TektextEdit->setTextCursor(cursor);

    //qDebug() << AcqCout1;
    QChar qch = TekCout1.at(0);
    char ch = qch.toLatin1();
    int ind = 0;
    for(int i = 2;i < 8; i++)
    {
        qch = TekCout1.at(i);
        ch = qch.toLatin1();
        if(ch==' ')
        {
            continue;
        }
        if(ch >= 48 && ch < 58)
        {
            ind = ind * 10 + ch - 48;
        }
        //qDebug() << i <<  " qch:" << qch <<  " ch:" << ch;
    }


    //qDebug() <<  " Ind:" << ind << endl;
    int x = round(double((ind - TekBeginIndex) * 100) / TekTotalIndex);
    //qDebug() << ind << x;
    ui->TekprogressBar->setValue(x);
}


/*********************************************************************************************
* sun 20200802
* By sunguiyu96@gmail.com
* Acquisition Part
* 读取Acq.config文件(默认配置文件)函数
* input：
* output：
* Process：
* 2020/08/02 sun 17:42:Complete the modification to make it run within the integral program；
；
**********************************************************************************************/
void PositionSystem::on_AcqReadApushButton_clicked()
{
    //读acq.config（默认的配置文件）
    QString currentpath = QApplication::applicationDirPath();       //读入.exe所在的路径
    QString configpath = currentpath + "/config/" + "ACQ.config";
    QString filename = configpath;
    if(filename.isEmpty() == false)
    {
        QFile file(filename);
        bool isok = file.open(QIODevice::ReadOnly);//以只读的方式打开文件
        if(isok == true)
        {
            QByteArray array;
            QByteArray configline;
            int index_b=0,index_e=0;
            while(file.atEnd() == false)
            {
                configline = file.readLine();      //读的每行
                array += configline;//将文件中的读取的内容保存在字节数组中。
                QString acqline;
                acqline.prepend(configline);
//                        qDebug() << acqline;
                //得到数据路径及数据名
                if(acqline[0]=="D" && acqline[1]=="A")
                {
                    QString DataName;
                    int n_name = acqline.length() - 13;
                    DataName = acqline.mid(11,n_name);
                    ui->AcqDATA_namelineEdit->setText(DataName);
                }
                //得到捕获结果文件路径及名字
                if(acqline[0]=="a" && acqline[7]=="n")
                {
                    QString AcqOutName;
                    int n_name = acqline.length() - 15;
                    AcqOutName = acqline.mid(13,n_name);
                    AcqOutPathandName = currentpath + "/ACQ/" +AcqOutName;
                    ui->AcqOut_namelineEdit->setText(AcqOutName);
                    //qDebug() <<  AcqOutPathandName;
                    //ui ->textEdit_2 ->setText(AcqOutPathandName);
                }
                //得到总的数量
                if(acqline[0]=="I" && acqline[6]=="B")
                {
                    QString i_b;
                    int n = acqline.length() - 8;
                    i_b = acqline.mid(8,n);
                    index_b = i_b.toInt();
                    BeginIndex = index_b;
                    ui->AcqIndexBspinBox->setValue(index_b);
                }
                if(acqline[0]=="I" && acqline[6]=="E")
                {
                    QString i_e;
                    int n = acqline.length() - 8;
                    i_e = acqline.mid(8,n);
                    index_e = i_e.toInt();
                    TotalIndex = index_e - index_b + 1;
                    QString total = QString::number(TotalIndex);
                    ui->AcqStatetextEdit->setText(AcqOutPathandName + "\n" + "Total:" + total);
                    ui->AcqIndexEspinBox->setValue(index_e);
                }
                //得到捕获门限
                if(acqline[0]=="c" && acqline[35]=="1")
                {
                    QString db1;
                    int n = acqline.length() - 37;
                    db1 = acqline.mid(37,n);
                    double c_db1 = db1.toDouble();
                    ui->AcqDb1doubleSpinBox->setValue(c_db1);
                }
                if(acqline[0]=="c" && acqline[35]=="2")
                {
                    QString db2;
                    int n = acqline.length() - 37;
                    db2 = acqline.mid(37,n);
                    double c_db2 = db2.toDouble();
                    ui->AcqDb2doubleSpinBox->setValue(c_db2);
                }
            }
            ui->AcqConfigtextEdit->setText(array);
        }
        file.close();//文件读取完毕后关闭文件。
    }
    //Enable Acqisition's button
    ui->AcqWriteCpushButton->setEnabled(true);
    ui->AcqStartpushButton->setEnabled(true);
    ui->AcqEndpushButton->setEnabled(true);
}

/*********************************************************************************************
* sun 20200802
* By sunguiyu96@gmail.com
* Acquisition Part
* 读取xx.config文件函数
* input：
* output：
* Process：
* 2020/08/02 sun 17:48:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::on_AcqReadCpushButton_clicked()
{
    //读config
    QString currentpath = QApplication::applicationDirPath();       //读入.exe所在的路径
    QString configpath = currentpath + "/config/";
    QString filename = QFileDialog::getOpenFileName(this, "打开文件", configpath, "config files(*.config);;Txt(*.txt)");
    if(filename.isEmpty() == false)
    {
        QFile file(filename);
        bool isok = file.open(QIODevice::ReadOnly);//以只读的方式打开文件
        if(isok == true)
        {
            QByteArray array;
            QByteArray configline;
            int index_b=0,index_e=0;
            while(file.atEnd() == false)
            {
                configline = file.readLine();      //读的每行
                array += configline;//将文件中的读取的内容保存在字节数组中。
                QString acqline;
                acqline.prepend(configline);
                //qDebug() << acqline;
                //得到数据路径及数据名
                if(acqline[0]=="D" && acqline[1]=="A")
                {
                    QString DataName;
                    int n_name = acqline.length() - 13;
                    DataName = acqline.mid(11,n_name);
                    ui->AcqDATA_namelineEdit->setText(DataName);
                }
                //得到捕获结果文件路径及名字
                if(acqline[0]=="a" && acqline[7]=="n")
                {
                    QString AcqOutName;
                    int n_name = acqline.length() - 15;
                    AcqOutName = acqline.mid(13,n_name);
                    AcqOutPathandName = currentpath + "/ACQ/" +AcqOutName;
                    ui->AcqOut_namelineEdit->setText(AcqOutName);
                    //qDebug() <<  AcqOutPathandName;
                    //ui ->textEdit_2 ->setText(AcqOutPathandName);
                }
                //得到总的数量
                if(acqline[0]=="I" && acqline[6]=="B")
                {
                    QString i_b;
                    int n = acqline.length() - 8;
                    i_b = acqline.mid(8,n);
                    index_b = i_b.toInt();
                    BeginIndex = index_b;
                    ui->AcqIndexBspinBox->setValue(index_b);
                }
                if(acqline[0]=="I" && acqline[6]=="E")
                {
                    QString i_e;
                    int n = acqline.length() - 8;
                    i_e = acqline.mid(8,n);
                    index_e = i_e.toInt();
                    TotalIndex = index_e - index_b + 1;
                    QString total = QString::number(TotalIndex);
                    ui ->AcqStatetextEdit ->setText(AcqOutPathandName + "\n" + "Total:" + total);
                    ui->AcqIndexEspinBox->setValue(index_e);
                }
                //得到捕获门限
                if(acqline[0]=="c" && acqline[35]=="1")
                {
                    QString db1;
                    int n = acqline.length() - 37;
                    db1 = acqline.mid(37,n);
                    double c_db1 = db1.toDouble();
                    ui->AcqDb1doubleSpinBox->setValue(c_db1);
                }
                if(acqline[0]=="c" && acqline[35]=="2")
                {
                    QString db2;
                    int n = acqline.length() - 37;
                    db2 = acqline.mid(37,n);
                    double c_db2 = db2.toDouble();
                    ui->AcqDb2doubleSpinBox->setValue(c_db2);
                }
            }
            ui->AcqConfigtextEdit->setText(array);
        }
        file.close();//文件读取完毕后关闭文件。
    }

    //Enable Acqisition's button
    ui->AcqWriteCpushButton->setEnabled(true);
    ui->AcqStartpushButton->setEnabled(true);
    ui->AcqEndpushButton->setEnabled(true);
}

/*********************************************************************************************
* sun 20200802
* By sunguiyu96@gmail.com
* Acquisition Part
* 将打开的xx.config文件重新写入
* input：
* output：
* Process：
* 2020/08/02 sun 18:07:Complete the modification to make it run within the integral program；
* 2020/08/05 sun 11:19:Write ACQ.config only；
**********************************************************************************************/
void PositionSystem::on_AcqWriteCpushButton_clicked()
{
    //Write config
    QString currentpath = QApplication::applicationDirPath();       //读入.exe所在的路径
    QString configpath = currentpath + "/config/";
    //QString filename = QFileDialog::getOpenFileName(this, "打开文件", configpath, "config files(*.config);;Txt(*.txt)");
    QString filename = configpath + "ACQ.config";
    QString str;
    if(filename.isEmpty() == false)
    {
        QFile file(filename);
        bool isok = file.open(QIODevice::WriteOnly);
        if(isok == true)
        {
            //Reading information from the interface is overridden
            str = "20200802AcqV2.4\n\n";
            str += "#ACQ\n";
            QString DataName;
            DataName = ui->AcqDATA_namelineEdit->text();
            str = str + "DATA_name:\"" + DataName + "\"\n";
            QString AcqName;
            AcqName = ui->AcqOut_namelineEdit->text();
            str = str + "acqout_name:\"" + AcqName + "\"\n";
            int index;
            index = ui->AcqIndexBspinBox->value();
            str = str + "INDEX_B:" + QString::number(index) +"\n";
            index = ui->AcqIndexEspinBox->value();
            str = str + "INDEX_E:" + QString::number(index) +"\n";
            double db;
            db=ui->AcqDb1doubleSpinBox->value();
            str = str + "comparison_with_outmatchedfilter_db1:" + QString::number(db,10,1) +"\n";
            db=ui->AcqDb2doubleSpinBox->value();
            str = str + "comparison_with_outmatchedfilter_db2:" + QString::number(db,10,1) +"\n";
            file.write(str.toUtf8());
        }
        file.close();
        //ui->AcqConfigtextEdit->setText(str + "\n" + "Write " + filename + " OK!!");
    }

    //Read the config file written above (the default configuration file)
    if(filename.isEmpty() == false)
    {
        QFile file(filename);
        bool isok = file.open(QIODevice::ReadOnly);//以只读的方式打开文件
        if(isok == true)
        {
            QByteArray array;
            QByteArray configline;
            int index_b=0,index_e=0;
            while(file.atEnd() == false)
            {
                configline = file.readLine();      //Open the file as read-only
                array += configline;//将The reads in the file are stored in a byte array
                QString acqline;
                acqline.prepend(configline);
                //qDebug() << acqline;
                //Gets the data path and the data name
                if(acqline[0]=="D" && acqline[1]=="A")
                {
                    QString DataName;
                    int n_name = acqline.length() - 13;
                    DataName = acqline.mid(11,n_name);
                    ui->AcqDATA_namelineEdit->setText(DataName);
                }
                //Gets the path and name of the acquisition result file
                if(acqline[0]=="a" && acqline[7]=="n")
                {
                    QString AcqOutName;
                    int n_name = acqline.length() - 15;
                    AcqOutName = acqline.mid(13,n_name);
                    AcqOutPathandName = currentpath + "/ACQ/" +AcqOutName;
                    ui->AcqOut_namelineEdit->setText(AcqOutName);
                    //qDebug() <<  AcqOutPathandName;
                    //ui ->textEdit_2 ->setText(AcqOutPathandName);
                }
                //Get the total amount
                if(acqline[0]=="I" && acqline[6]=="B")
                {
                    QString i_b;
                    int n = acqline.length() - 8;
                    i_b = acqline.mid(8,n);
                    index_b = i_b.toInt();
                    BeginIndex = index_b;
                    ui->AcqIndexBspinBox->setValue(index_b);
                }
                if(acqline[0]=="I" && acqline[6]=="E")
                {
                    QString i_e;
                    int n = acqline.length() - 8;
                    i_e = acqline.mid(8,n);
                    index_e = i_e.toInt();
                    TotalIndex = index_e - index_b + 1;
                    QString total = QString::number(TotalIndex);
                    ui ->AcqStatetextEdit ->setText(AcqOutPathandName + "\n" + "Total:" + total);
                    ui->AcqIndexEspinBox->setValue(index_e);
                }
                //Get the threshold
                if(acqline[0]=="c" && acqline[35]=="1")
                {
                    QString db1;
                    int n = acqline.length() - 37;
                    db1 = acqline.mid(37,n);
                    double c_db1 = db1.toDouble();
                    ui->AcqDb1doubleSpinBox->setValue(c_db1);
                }
                if(acqline[0]=="c" && acqline[35]=="2")
                {
                    QString db2;
                    int n = acqline.length() - 37;
                    db2 = acqline.mid(37,n);
                    double c_db2 = db2.toDouble();
                    ui->AcqDb2doubleSpinBox->setValue(c_db2);
                }
            }
            ui->AcqConfigtextEdit->setText(array);
        }
        file.close();//Close the file after it has been read
    }

    //Write success signs
    QString currentText = ui->AcqStatetextEdit->toPlainText();
    ui->AcqStatetextEdit->setText(currentText + "\n\nWrite " + filename + " OK!!");
    //Keep at the bottom
    QTextCursor cursor = ui->AcqStatetextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->AcqStatetextEdit->setTextCursor(cursor);

}

/*********************************************************************************************
* sun 20200802
* By sunguiyu96@gmail.com
* Acquisition Part
* Start the Acq.exe
* input：
* output：
* Process：
* 2020/08/02 sun 18:12:Complete the modification to make it run within the integral program；
* 2020/08/12 sun 11:40:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::on_AcqStartpushButton_clicked()
{
    //Get acq mode
    onAcqModeClick();

    //Call IridiumAcq.exe in this file
    QString currentpath = QApplication::applicationDirPath();       //Read in the path of. Exe
    //qDebug() << "exepath:" << exepath << endl;
    QString workpath = currentpath;     //set the workpath of .Exe
    //QMessageBox::warning(0,"PATH",exepath,QMessageBox::Yes);           //View current path

    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_dt =current_date_time.toString("\nyyyy.MM.dd hh:mm:ss");
    QString currentText = ui->AcqStatetextEdit->toPlainText();

    qDebug() << AcqExemode << endl;
    switch(AcqExemode)
    {
    case 0:
        {
            //Three processes to achieve Acqsition
            QString exepath1 = currentpath + "/IridiumAcq1.exe";
            QString exepath2 = currentpath + "/IridiumAcq2.exe";
            QString exepath3 = currentpath + "/IridiumAcq3.exe";
            QProcess *AcqProcess1;
            QProcess *AcqProcess2;
            QProcess *AcqProcess3;
            if (QFileInfo(exepath1).exists() )//&& QFileInfo(exepath2).exists() && QFileInfo(exepath3).exists())
            {
                AcqProcess1 = new QProcess(this);
                AcqProcess2 = new QProcess(this);
                AcqProcess3 = new QProcess(this);
                int readOutput = TotalIndex % 3;
                switch(readOutput)
                {
                case 0:
                    connect(AcqProcess3, SIGNAL(readyRead()),this, SLOT(refreshacqout()));
                    break;
                case 1:
                    connect(AcqProcess1, SIGNAL(readyRead()),this, SLOT(refreshacqout()));
                    break;
                case 2:
                    connect(AcqProcess2, SIGNAL(readyRead()),this, SLOT(refreshacqout()));
                    break;
                }

                QStringList AcqList("ACQ for raw Tek Data is running...");
                AcqProcess1->setWorkingDirectory(workpath);
                AcqProcess2->setWorkingDirectory(workpath);
                AcqProcess3->setWorkingDirectory(workpath);
                AcqProcess1->start(exepath1,AcqList);
                AcqProcess2->start(exepath2,AcqList);
                AcqProcess3->start(exepath3,AcqList);
                //AcqProcess->startDetached(exepath,QStringList(),workpath);
                ui->AcqStatetextEdit->setText(currentText + "\n\n" + current_dt + ":IRIDIUMACQ.EXE FOR RAW TEK DATA HAS START!!  \n");
                //Keep it at the bottom
                QTextCursor cursor = ui->AcqStatetextEdit->textCursor();
                cursor.movePosition(QTextCursor::End);
                ui->AcqStatetextEdit->setTextCursor(cursor);
            }
        }
        break;
    case 1:
        {
            //Capture program for preprocessing data
            QString exepath = currentpath + "/IridiumAcq.exe";
            QProcess *AcqProcess;
            if (QFileInfo(exepath).exists())
            {
                AcqProcess = new QProcess(this);
                connect(AcqProcess, SIGNAL(readyRead()),this, SLOT(refreshacqout()));

                QStringList AcqList("ACQ for raw Tek Data is running...");
                AcqProcess->setWorkingDirectory(workpath);
                AcqProcess->start(exepath,AcqList);

                //AcqProcess->startDetached(exepath,QStringList(),workpath);
                QDateTime current_date_time =QDateTime::currentDateTime();
                QString current_dt =current_date_time.toString("\nyyyy.MM.dd hh:mm:ss");
                QString currentText = ui->AcqStatetextEdit->toPlainText();
                ui->AcqStatetextEdit->setText(currentText + "\n\n" + current_dt + ":IRIDIUMACQ.EXE FOR PRO TEK DATA HAS START!!  \n");
                //Keep it at the bottom
                QTextCursor cursor = ui->AcqStatetextEdit->textCursor();
                cursor.movePosition(QTextCursor::End);
                ui->AcqStatetextEdit->setTextCursor(cursor);
            }
        }
        break;
    case 2:
        {
            //Capture program for preprocessing data
            QString exepath = currentpath + "/IridiumAcqJ.exe";
            QProcess *AcqProcess;
            if (QFileInfo(exepath).exists())
            {
                AcqProcess = new QProcess(this);
                connect(AcqProcess, SIGNAL(readyRead()),this, SLOT(refreshacqout()));

                QStringList AcqList("ACQ for raw Tek Data is running...");
                AcqProcess->setWorkingDirectory(workpath);
                AcqProcess->start(exepath,AcqList);

                //AcqProcess->startDetached(exepath,QStringList(),workpath);
                ui->AcqStatetextEdit->setText(currentText + "\n\n" + current_dt + ":IRIDIUMACQ.EXE FOR SELF DATA HAS START!!  \n");
                //Keep it at the bottom
                QTextCursor cursor = ui->AcqStatetextEdit->textCursor();
                cursor.movePosition(QTextCursor::End);
                ui->AcqStatetextEdit->setTextCursor(cursor);
            }
        }
        break;
    }

}

/*********************************************************************************************
* sun 20200802
* By sunguiyu96@gmail.com
* Acquisition Part
* 关闭IridiumAcq.exeProcess
* input：
* output：
* Process：
* 2020/08/02 sun 18:14:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::on_AcqEndpushButton_clicked()
{
    //close IridiumAcq.exeProcess
    switch(AcqExemode)
    {
    case 0:
        {
            QString c = "taskkill /im IridiumAcq1.exe /f";
            int pInt = QProcess::execute(c);    //Close the background notepad.exeProcess, blocking operation, always occupy the cpu, success returns 0, failure returns 1
            if(pInt==0)
            {
                QMessageBox::warning(0,"PATH","SUCCESS KILL IRIDIUMACQ1.EXE!",QMessageBox::Yes);           //查看当前路径
            }
            c = "taskkill /im IridiumAcq2.exe /f";
            pInt = QProcess::execute(c);
            if(pInt==0)
            {
                QMessageBox::warning(0,"PATH","SUCCESS KILL IRIDIUMACQ2.EXE!",QMessageBox::Yes);           //查看当前路径
            }
            c = "taskkill /im IridiumAcq3.exe /f";
            pInt = QProcess::execute(c);
            if(pInt==0)
            {
                QMessageBox::warning(0,"PATH","SUCCESS KILL IRIDIUMACQ3.EXE!",QMessageBox::Yes);           //查看当前路径
            }
            //Call IridiumAcq.exe in this file
            QString currentpath = QApplication::applicationDirPath();       //Read in the path of. Exe
            //qDebug() << "exepath:" << exepath << endl;
            QString workpath = currentpath;     //set the workpath of .Exe
            //sort for acqout
            QString exepath = currentpath + "/IridiumAcqoutSort.exe";
            QProcess *AcqProcess;
            if (QFileInfo(exepath).exists())
            {
                AcqProcess = new QProcess(this);
                connect(AcqProcess, SIGNAL(readyRead()),this, SLOT(refreshacqout()));

                QStringList AcqList("ACQ for raw Tek Data is running...");
                AcqProcess->setWorkingDirectory(workpath);
                AcqProcess->start(exepath,AcqList);

                //AcqProcess->startDetached(exepath,QStringList(),workpath);
                QDateTime current_date_time =QDateTime::currentDateTime();
                QString current_dt =current_date_time.toString("\nyyyy.MM.dd hh:mm:ss");
                QString currentText = ui->AcqStatetextEdit->toPlainText();
                ui->AcqStatetextEdit->setText(currentText + "\n\n" + current_dt + ":IRIDIUMACQSORT.EXE HAS START!!  \n");
                //Keep it at the bottom
                QTextCursor cursor = ui->AcqStatetextEdit->textCursor();
                cursor.movePosition(QTextCursor::End);
                ui->AcqStatetextEdit->setTextCursor(cursor);
            }
        }
        break;
    case 1:
        {
            QString c = "taskkill /im IridiumAcq.exe /f";
            int pInt = QProcess::execute(c);    //Close the background notepad.exeProcess, blocking operation, always occupy the cpu, success returns 0, failure returns 1
            if(pInt==0)
            {
                QMessageBox::warning(0,"PATH","SUCCESS KILL IRIDIUMACQ.EXE!",QMessageBox::Yes);           //查看当前路径
            }
        }
        break;
    case 2:
        {
            QString c = "taskkill /im IridiumAcqf.exe /f";
            int pInt = QProcess::execute(c);    //Close the background notepad.exeProcess, blocking operation, always occupy the cpu, success returns 0, failure returns 1
            if(pInt==0)
            {
                QMessageBox::warning(0,"PATH","SUCCESS KILL IRIDIUMACQf.EXE!",QMessageBox::Yes);           //查看当前路径
            }
        }

    }

}

/*********************************************************************************************
* sun 20200802
* By sunguiyu96@gmail.com
* Acquisition Part
* Execute the refresh program (automatically)
* input：
* output：
* Process：
* 2020/08/02 sun 18:18:Complete the modification to make it run within the integral program；
**********************************************************************************************/
//void PositionSystem::on_AcqRefreshpushButton_clicked()
//{
//    if(ui->AcqFreshcheckBox->isChecked()==true)
//    {
//        QTimer *timerrefresh = new QTimer(this);
//        connect(timerrefresh,SIGNAL(timeout()),this,SLOT(refreshacqout()));
//        timerrefresh->start(1000 * 5);        //5s刷新一次
//    }
//    else
//    {
//        refreshacqout();
//    }
//}

/*********************************************************************************************
* sun 20200802
* By sunguiyu96@gmail.com
* Acquisition Part
* Read, draw, display progress slot function from exe's std out
* input：
* output：
* Process：
* 2020/08/02 sun 18:18:Complete the modification to make it run within the integral program；
* 2020/08/05 sun 12:31:Modify to read program Cout, identify the sequence number and refresh；
**********************************************************************************************/
void PositionSystem::refreshacqout(void)
{
    QProcess *AcqProcess = (QProcess *)sender();
    QString AcqCout1 = AcqProcess->readAll();
    AcqCout += AcqCout1;
    ui->AcqConfigtextEdit->setText(AcqCout);
    //Move the cursor to the end
    QTextCursor cursor = ui->AcqConfigtextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->AcqConfigtextEdit->setTextCursor(cursor);

    //qDebug() << AcqCout1;
    QChar qch = AcqCout1.at(0);
    char ch = qch.toLatin1();
    int ind = 0;
    for(int i = 2;i < 7; i++)
    {
        qch = AcqCout1.at(i);
        ch = qch.toLatin1();
        if(ch==' ')
        {
            continue;
        }
        if(ch >= 48 && ch < 58)
        {
            ind = ind * 10 + ch - 48;
        }
        //qDebug() << i <<  " qch:" << qch <<  " ch:" << ch;
    }


    //qDebug() <<  " Ind:" << ind << endl;
    if(ind != 0)
    {
        ReadData();     //读取捕获结果
        PlotData();     //画图

        RefreshBar(ind);   //显示进展
    }

    if(AcqCout1.startsWith("* All m"))
    {
        if(AcqExemode == 0)
        {
            Delay_MSec(20000);       //delay 20s->20000ms
            //Call IridiumAcq.exe in this file
            QString currentpath = QApplication::applicationDirPath();       //Read in the path of. Exe
            //qDebug() << "exepath:" << exepath << endl;
            QString workpath = currentpath;     //set the workpath of .Exe
            //sort for acqout
            QString exepath = currentpath + "/IridiumAcqoutSort.exe";
            QProcess *AcqProcess1;
            if (QFileInfo(exepath).exists())
            {
                AcqProcess1 = new QProcess(this);
                connect(AcqProcess1, SIGNAL(readyRead()),this, SLOT(refreshacqoutSort()));

                QStringList AcqList("ACQ for raw Tek Data is running...");
                AcqProcess1->setWorkingDirectory(workpath);
                AcqProcess1->start(exepath,AcqList);

                //AcqProcess->startDetached(exepath,QStringList(),workpath);
                QDateTime current_date_time =QDateTime::currentDateTime();
                QString current_dt =current_date_time.toString("\nyyyy.MM.dd hh:mm:ss");
                QString currentText = ui->AcqStatetextEdit->toPlainText();
                ui->AcqStatetextEdit->setText(currentText + "\n\n" + current_dt + ":IRIDIUMACQSORT.EXE HAS START!!  \n");
                //Keep it at the bottom
                cursor = ui->AcqStatetextEdit->textCursor();
                cursor.movePosition(QTextCursor::End);
                ui->AcqStatetextEdit->setTextCursor(cursor);
            }
        }
    }

}

/*********************************************************************************************
* sun 20200802
* By sunguiyu96@gmail.com
* Acquisition Part
* Read slot function from IridiumSort.exe's std out
* input：
* output：
* Process：
* 2020/08/12 sun 16:57:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::refreshacqoutSort(void)
{
    QProcess *AcqProcess = (QProcess *)sender();
    QString AcqCout1 = AcqProcess->readAll();
    AcqCout += AcqCout1;
    ui->AcqConfigtextEdit->setText(AcqCout);
    //Move the cursor to the end
    QTextCursor cursor = ui->AcqConfigtextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->AcqConfigtextEdit->setTextCursor(cursor);
}

/*********************************************************************************************
* sun 20200802
* By sunguiyu96@gmail.com
* Acquisition Part
* 读取acq结果文件
* input：
* output：
* Process：
* 2019/12/12 sun 16:13:达到理想效果；
* 2019/12/30 sun 17:26:捕获文件路径可通过readconfig按钮读取；
* 2020/08/02 sun 18:18:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::ReadData()
{
    QString acqpath = AcqOutPathandName;
    //qDebug() << "ACQPATH: " << acqpath;
    QFile file(acqpath);

    int NLine = 0;

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while (!file.atEnd())
        {
            QByteArray line = file.readLine();
            NLine++;
        }
        file.close();
    }

    //qDebug() << "NUM OF LINE: " << NLine ;
    int N = NLine + 10;
    double Fi = 28270833;
    Index.resize(N);
    Time.resize(N);
    QVector<double>Fre(N);
    Dop.resize(N);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        int i=0;
        while (!file.atEnd())
        {
            QByteArray line = file.readLine();
            QString str(line);
            QVector<QStringRef> lineRef;
            lineRef = str.splitRef(' ',QString::SkipEmptyParts);

            //qDebug() << str;

            Index[i] = lineRef[0].toInt();
            Time[i] = lineRef[1].toDouble();
            Fre[i] = lineRef[2].toDouble();
            Dop[i] = Fre[i] - Fi;
//            qDebug() << i << ":" << Time[i] << "," << Dop[i];
            CurruntIndex = Index[i] - BeginIndex + 1;
            i++;
        }

        file.close();
    }

}

/*********************************************************************************************
* sun 20200802
* By sunguiyu96@gmail.com
* Acquisition Part
* 将读取的结果展示在坐标系中
* input：
* output：
* Process：
* 2019/12/13 sun 0:13:开始；
* 2020/08/02 sun 18:24:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::PlotData()
{
    //清空原有图形
    int plottableCount = ui->AcqFigure->plottableCount();
    if (plottableCount != 0)
    {
        ui->AcqFigure->clearPlottables();
    }
    //添加图形
    ui->AcqFigure->addGraph();
    //设置画笔颜色
    ui->AcqFigure->graph(0)->setPen(QPen(Qt::blue));
    //设置线为无
    ui->AcqFigure->graph(0)->setLineStyle(QCPGraph::LineStyle::lsNone);
    //设置散点图
    ui->AcqFigure->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ScatterShape::ssPlus,5));
    //传入数据
    ui->AcqFigure->graph(0)->setData(Time,Dop);
    //设置X轴文字标注
    ui->AcqFigure->xAxis->setLabel("Time");
    //设置Y轴文字标注
    ui->AcqFigure->yAxis->setLabel("Doppler");
    //设置使最适合
    ui->AcqFigure->graph(0)->rescaleAxes();
//    ui->widget->xAxis->setRange(0,900);
    ui->AcqFigure->yAxis->setRange(-36000,36000);
    //在坐标轴右侧和上方画线，和X/Y轴一起形成一个矩形
    ui->AcqFigure->axisRect()->setupFullAxesBox();
    //允许使用鼠标移动和放大
    ui->AcqFigure->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);\
    //刷新图像
    ui->AcqFigure->replot();
}

/*********************************************************************************************
* sun 20200802
* By sunguiyu96@gmail.com
* Acquisition Part
* Refresh processBar to show the progress captured
* input：current index
* output：
* Process：
* 2019/12/13 sun 0:22:开始；
* 2020/08/02 sun 18:25:Complete the modification to make it run within the integral program；
* 2020/08/05 sun 11:34:Modify input；
**********************************************************************************************/
void PositionSystem::RefreshBar(int ind)
{
    //qDebug() << CurruntIndex;
    //qDebug() << TotalIndex;
    int x = round(double((ind - BeginIndex) * 100) / TotalIndex);
    //qDebug() << ind << x;
    ui->AcqprogressBar->setValue(x);
}

/*********************************************************************************************
* sun 20200812
* By sunguiyu96@gmail.com
* Acquisition Part
* Get Acq mode(which acq.exe will be execuated)
* input：
* output：
* Process：
* 2020/08/12 sun 11:08:Complete the modification to make it run within the integral program；
* 2020/08/05 sun 11:34:Modify input；
**********************************************************************************************/
void PositionSystem::onAcqModeClick()
{
    switch(AcqMode->checkedId())
    {
    case 0:
        AcqExemode = 0;
        break;
    case 1:
        AcqExemode = 1;
        break;
    case 2:
        AcqExemode = 2;
        break;
    }
}

/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* Update TLE Part
* 显示铱星Iridium星座TLE数据网页并更新铱星Iridium星座TLE
* input：
* output：/TLEDownload/Irdium.tle
* Process：
* 2020/06/13 sun 18:33:目前可以显示网页及保存TLE；
* 2020/06/13 sun 18:55:优化了信息output；
* 2020/08/01 sun 19:12:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::on_Iridium_clicked()
{
    //铱星TLE所在的网站地址
    QString path = "https://www.celestrak.com/NORAD/elements/table.php?tleFile=iridium&title=Iridium%20Satellites&orbits=40&pointsPerRev=90&frame=1";
    QString pathIridium = "https://www.celestrak.com/NORAD/elements/iridium.txt";

    //读取text的目前内容
    QString Currunt_textEdit = ui->UptextEdit->toPlainText();
    QString text = "Loading https://www.celestrak.com/NORAD/elements/table.php?tleFile=iridium ...";
    Currunt_textEdit += text;
    ui->UptextEdit->setText(Currunt_textEdit);

    QUrl url(path);
    QUrl urlIridium(pathIridium);

    ui->TLEVIew->load(url);
    ui->TLEVIew->show();

    //以下为保存网页源码
    QNetworkAccessManager manager;
    QEventLoop loop;
    QNetworkReply *reply;

    //qDebug() << "Reading code from " << pathIridium;

    reply = manager.get(QNetworkRequest(urlIridium));

    QObject::connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));      //请求结束并下载完成后，退出子事件循环

    loop.exec();         //开启子事件循环

    //写入文件
    //QString currentpath = "C:/Qt/TLETest/TLEDownload/";
    QString currentpath = QApplication::applicationDirPath();       //读入.exe所在的路径
    QString FILE_NAME = currentpath + "/TLEDownload/Iridium.tle";
    QFile file(FILE_NAME);

    if( !file.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        //qDebug() << "Cannot open the file: " << FILE_NAME;
    }
    QTextStream out(&file);
    QString codeContent = reply->readAll();

    //qDebug() << FILE_NAME << endl;

    out << codeContent;

    //更新显示
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_dt =current_date_time.toString("\nyyyy.MM.dd hh:mm:ss.zzz");
    text = current_dt + ": Iridium.tle has updated successfully!\n\n";
    Currunt_textEdit += text;
    ui->UptextEdit->setText(Currunt_textEdit);
    QTextCursor cursor = ui->UptextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->UptextEdit->setTextCursor(cursor);

    file.close();
}

/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* Update TLE Part
* 显示铱星Iridium Next星座TLE数据网页并更新铱星Iridium Next星座TLE
* input：
* output：/TLEDownload/IrdiumNext.tle
* Process：
* 2020/06/13 sun 18:33:目前可以显示网页及保存TLE；
* 2020/06/13 sun 18:55:优化了信息output；
* 2020/08/01 sun 19:23:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::on_IridiumNext_clicked()
{
    //铱星TLE所在的网站地址
    QString path = "https://www.celestrak.com/NORAD/elements/table.php?tleFile=iridium-NEXT&title=Iridium%20NEXT%20Satellites&orbits=0&pointsPerRev=90&frame=1";
    QString pathIridium = "https://www.celestrak.com/NORAD/elements/iridium-NEXT.txt";

    //读取text的目前内容
    QString Currunt_textEdit = ui->UptextEdit->toPlainText();
    QString text = "Loading https://www.celestrak.com/NORAD/elements/table.php?tleFile=iridium-NEXT ...";
    Currunt_textEdit += text;
    ui->UptextEdit->setText(Currunt_textEdit);

    QUrl url(path);
    QUrl urlIridium(pathIridium);

    ui->TLEVIew->load(url);
    ui->TLEVIew->show();

    //以下为保存网页源码
    QNetworkAccessManager manager;
    QEventLoop loop;
    QNetworkReply *reply;

    //qDebug() << "Reading code from " << pathIridium;

    reply = manager.get(QNetworkRequest(urlIridium));

    QObject::connect(reply,SIGNAL(finished()),&loop,SLOT(quit()));      //请求结束并下载完成后，退出子事件循环

    loop.exec();        //开启子事件循环

    //写入文件
    //QString currentpath = "C:/Qt/TLETest/TLEDownload/";
    QString currentpath = QApplication::applicationDirPath();       //读入.exe所在的路径
    QString FILE_NAME = currentpath + "/TLEDownload/IridiumNEXT.tle";
    QFile file(FILE_NAME);

    if( !file.open(QIODevice::WriteOnly | QIODevice::Text) )
    {
        //qDebug() << "Cannot open the file: " << FILE_NAME;
    }
    QTextStream out(&file);
    QString codeContent = reply->readAll();

    //qDebug() << FILE_NAME << endl;
    out << codeContent;

    //更新显示
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_dt =current_date_time.toString("\nyyyy.MM.dd hh:mm:ss");
    text = current_dt + ": IridiumNEXT.tle has updated successfully!\n\n";
    Currunt_textEdit += text;
    ui->UptextEdit->setText(Currunt_textEdit);
    QTextCursor cursor = ui->UptextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->UptextEdit->setTextCursor(cursor);

    file.close();
}


/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* Update TLE Part
* 将Download文件内的TLE更新至更新至xxxxxxxx.tle之内
* input：
* output：/TLEDownload/xxxxxxxxt.tle（日期）
* Process：
* 2020/06/13 sun 18:59:开始；
* 2020/06/13 sun 19:55:结束；
* 2020/06/13 sun 20:17:基本实现，流output，不明出现两个空行；
* 2020/06/13 sun 22:29:可直接删除两个换行符；
* 2020/06/13 sun 23:46:发现\r\n均被认为是换行符，所以需要删除；
* 2020/06/14 sun 01:34:基本达到理想效果；
* 2020/08/01 sun 19:26:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::on_UpdateTLE_clicked()
{
    //During the update process, disable the remaining buttons
    ui->Iridium->setEnabled(false);
    ui->IridiumNext->setEnabled(false);
    ui->UpdateTLE->setEnabled(false);

    //QString currentpath = "C:/Qt/TLETest/TLEDownload/";
    QString currentpath = QApplication::applicationDirPath();       //读入.exe所在的路径
    currentpath = currentpath + "/TLEDownload/";
    QString IriTLE = currentpath + "Iridium.tle";
    QString NextTLE = currentpath + "IridiumNEXT.tle";

    QFileInfo fileI(IriTLE);
    QFileInfo fileN(NextTLE);
    if((fileI.exists() == false) ||(fileN.exists() == false))
    {
        ui->UptextEdit_2->setText("Please check if Iridium/IridiumNEXT.tle exists in " + currentpath);
    }
    else
    {
        QFile fileIri(IriTLE);
        bool isok = fileIri.open(QIODevice::ReadOnly);//以只读的方式打开文件
        QString Current_textEdit = ui->UptextEdit->toPlainText();
        QString Current_textEdit_2 = ui->UptextEdit_2->toPlainText();
        QByteArray array;
        QByteArray line;
        QString TLE;
        while(fileIri.atEnd() == false)
        {
            line = fileIri.readLine();      //读的每行
            array += line;//将文件中的读取的内容保存在字节数组中 末尾为\r\r\n，换三行
            line.remove(line.length() - 3,3);       //删除末尾"\r\r\n"换行符
//            int length = line.length();
//            qDebug() << length;
//            if(length > 4)
//            {
//                qDebug("%d %d %d %d\n",  line[length - 1], line[length - 2] , line[length - 3] , line[length - 4]);
//            }
            QString locline;
            locline.prepend(line);
//            if(length > 4)
//            {
//                qDebug("%d %d %d %d\n",  locline[length - 1] == "\n", locline[length - 2] == "\r", locline[length - 3] == "\r", locline[length - 4]== "7");
//            }
            //按格式读取
            if((locline[0]=="I" && locline[1]=="R" && locline[2]=="I") || (locline[0]=="D" && locline[1]=="U" && locline[2]=="M"))
            {
                Current_textEdit_2 = Current_textEdit_2 + line;

            }
            else if((locline[0] == "1") || (locline[0] == "2"))
            {
                QString str(line);
                TLE = TLE + str + "\n";

                if(locline[0] == "1")
                {
                    QString SatNum = line.mid(2,5);
                    QString TLE_DT = CalculateTimeVSTLE(line);

                    //设置信息显示框
                    Current_textEdit_2 = Current_textEdit_2 + "   " + SatNum + "    " + TLE_DT + "   OK!\n";
                    ui->UptextEdit_2->setText(Current_textEdit_2);
                    QTextCursor cursor = ui->UptextEdit_2->textCursor();
                    cursor.movePosition(QTextCursor::End);
                    ui->UptextEdit_2->setTextCursor(cursor);
                }
            }
        }
        //Current_textEdit += array;
        fileIri.close();

        QFile fileNext(NextTLE);
        isok = fileNext.open(QIODevice::ReadOnly);//以只读的方式打开文件

        while(fileNext.atEnd() == false)
        {
            line = fileNext.readLine();      //读的每行
            array += line;//将文件中的读取的内容保存在字节数组中。
            line.remove(line.length() - 3,3);       //删除末尾"\r\r\n"换行符
            QString locline;
            locline.prepend(line);
            //按格式读取
            if(locline[0]=="I" && locline[1]=="R" && locline[2]=="I")
            {
                Current_textEdit_2 = Current_textEdit_2 + line;

            }
            else if((locline[0] == "1") || (locline[0] == "2"))
            {
                QString str(line);
                TLE = TLE + str + "\n";

                if(locline[0] == "1")
                {
                    QString SatNum = line.mid(2,5);
                    QString TLE_DT = CalculateTimeVSTLE(line);

                    //设置信息显示框
                    Current_textEdit_2 = Current_textEdit_2 + "   " + SatNum + "    " + TLE_DT + "   OK!\n";
                    ui->UptextEdit_2->setText(Current_textEdit_2);
                    QTextCursor cursor = ui->UptextEdit_2->textCursor();
                    cursor.movePosition(QTextCursor::End);
                    ui->UptextEdit_2->setTextCursor(cursor);
                }
            }
        }
        //ui->textEdit->setText(Current_textEdit + array);
        //移动光标到末尾
        QTextCursor cursor = ui->UptextEdit->textCursor();
//        cursor.movePosition(QTextCursor::End);
//        ui->textEdit->setTextCursor(cursor);

        fileNext.close();

        //写入到需要的xxxxxxxx.TLE中
        //更新显示
        QDateTime current_date_time =QDateTime::currentDateTime();
        QString current_date =current_date_time.toString("yyyyMMdd");
        QString outfileName = currentpath + current_date + ".tle";

        QFile file(outfileName);
        if( !file.open(QIODevice::WriteOnly | QIODevice::Text) )
        {
            //qDebug() << "Cannot open the file: " << outfileName;
        }
        QTextStream out(&file);

        out << TLE;

        Current_textEdit = ui->UptextEdit->toPlainText();
        QString current_dt =current_date_time.toString("\nyyyy.MM.dd hh:mm:ss");
        ui->UptextEdit->setText(Current_textEdit + current_dt + ": " +current_date + ".tle has updated successfully!\n\n");
        //移动光标到末尾
        cursor.movePosition(QTextCursor::End);
        ui->UptextEdit->setTextCursor(cursor);

        //currentTLEname = current_date + ".tle";
        ui->UpTLEDlineEdit->setText(current_date + ".tle");
        ui->UpTLElineEdit->setText(current_date + ".tle");
    }


    ui->Iridium->setEnabled(true);
    ui->IridiumNext->setEnabled(true);
    ui->UpdateTLE->setEnabled(true);
    ui->UpCopypushButton->setEnabled(true);
}

/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* TLEupdate Part
* Copy the updated TLE file to the TLE folder
* input:
* output:
* Process:
* 2020/08/03 sun 11:46:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::on_UpCopypushButton_clicked()
{
    QString TLED = ui->UpTLEDlineEdit->text();
    QString TLE = ui->UpTLElineEdit->text();

    //Path
    QString currentpath = QApplication::applicationDirPath();       //Read the path where the .exe is located
    TLED = currentpath + "/TLEDownload/" + TLED;
    TLE = currentpath + "/TLE/" + TLE;


    QString text;
    //Read TLED
    if(TLED.isEmpty() == false)
    {
        QFile file(TLED);
        bool isok = file.open(QIODevice::ReadOnly);
        if(isok == true)
        {
            QByteArray array;
            while(file.atEnd() == false)
            {
                array += file.readLine();
            }
            text = QString(array);
        }
        file.close();       //Close the file after reading the file.
    }

    //Write TLE
    if(TLE.isEmpty() == false)
    {
        QFile file(TLE);
        bool isok = file.open(QIODevice::WriteOnly);
        if(isok == true)
        {
            file.write(text.toUtf8());
        }
        file.close();       //Close the file after reading the file.
    }


    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_dt =current_date_time.toString("\nyyyy.MM.dd hh:mm:ss");
    QString Current_textEdit = ui->UptextEdit->toPlainText();
    TLE = ui->UpTLElineEdit->text();
    ui->UptextEdit->setText(Current_textEdit + "\n" + current_dt + ": " + TLE + " has copied to TLE folder successfully!\n\n");
    //Keep it at the bottom
    QTextCursor cursor = ui->UptextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->UptextEdit->setTextCursor(cursor);
}

/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* Update TLE Part
* 根据input的TLE计算采集TLE对应时间
* input：TLE行信息
* output：QString格式采集时间
* Process：
* 2020/06/14 sun 00:08:开始；
* 2020/06/14 sun 01:32:达到理想效果；
* 2020/08/01 sun 19:31:Complete the modification to make it run within the integral program；
**********************************************************************************************/
QString PositionSystem::CalculateTimeVSTLE(QString line)
{
    QString TLE_DT;

    QString year = line.mid(18,2);
    QString day = line.mid(20,12);
    int TLEyear = year.toInt();
    double TLEday = day.toDouble();
    int UTCyear = 0;
    double UTCday = 0.0;
    if(TLEyear < 57)
    {
        UTCyear = TLEyear + 2000;
        UTCday = TLEday;
    }
    else
    {
        UTCyear = TLEyear + 1900;
        UTCday = TLEday;
    }
    //把基于TLE天数的UTC转换为真正的UTC
    DateTime UTC = days2ymdhms(UTCyear,UTCday);
    DateTime BJT = UTC2BJT(UTC);

    //转换日期格式
    QString DT_s,year_s,month_s,day_s,hour_s,minute_s,second_s;      //为转换为时间格式做准备
    //年
    if(BJT.Y >= 1000 && BJT.Y <= 9999)
    {
        year_s = QString::number(BJT.Y);        //考虑年一定为4位
    }
    else
    {
        ui ->UptextEdit_2 ->setText("Year Error");  //Report an error
    }
    //月
    if(BJT.M < 10 && BJT.M > 0)
    {
        month_s = QString::number(BJT.M);
        month_s = "0" + month_s;//补0
    }
    else if(BJT.M < 13 && BJT.M > 9)
    {
        month_s = QString::number(BJT.M);
    }
    else
    {
        ui ->UptextEdit_2 ->setText("Month Error");  //Report an error
    }
    //日
    if(BJT.D < 10 && BJT.D > 0)
    {
        day_s = QString::number(BJT.D);
        day_s = "0" + day_s;//补0
    }
    else if(BJT.D < 32 && BJT.D > 9)
    {
        day_s = QString::number(BJT.D);
    }
    else
    {
        ui ->UptextEdit_2 ->setText("Day Error");  //Report an error
    }
     //时
    if(BJT.h < 10 && BJT.h >= 0)
    {
        hour_s = QString::number(BJT.h);
        hour_s = "0" + hour_s;//补0
    }
    else if(BJT.h < 25 && BJT.h > 9)
    {
        hour_s = QString::number(BJT.h);
    }
    else
    {
         ui ->UptextEdit_2 ->setText("Hour Error");  //Report an error
    }
    //分
    if(BJT.m < 10 && BJT.m >= 0)
    {
        minute_s = QString::number(BJT.m);
        minute_s = "0" + minute_s;//补0
    }
    else if(BJT.m < 61 && BJT.m > 9)
    {
        minute_s = QString::number(BJT.m);
    }
    else
    {
        ui ->UptextEdit_2 ->setText("Minute Error");  //Report an error
    }
    //秒
    int second = (int)BJT.s;
    if(second < 10 && second >= 0)
    {
        second_s = QString::number(second);
        second_s = "0" + second_s;//补0
    }
    else if(second <= 60 && second >= 10)
    {
        second_s = QString::number(second);
    }
    else
    {
        ui ->UptextEdit_2 ->setText("Second Error");  //Report an error
    }

    TLE_DT = year_s + "/" + month_s + "/" + day_s + " " + hour_s + ":" + minute_s + ":" + second_s;

    return TLE_DT;
}

/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* Update TLE Part
* 从年和天数推出时间
* input：int年数，double天数
* output：DateTime格式时间
* Process：
* 2020/06/14 sun 00:25:开始；
* 2020/06/14 sun 00:43:结束；
* 2020/08/01 sun 19:34:Complete the modification to make it run within the integral program；
**********************************************************************************************/
PositionSystem::DateTime PositionSystem::days2ymdhms(int y,double d)
{
    DateTime dt;
    dt.Y = y;
    //设置月份
    int l_M[13] = {0};
    for(int i = 1;i < 12;i++)
    {
        l_M[i] = 31;
        if(i == 2)
        {
            l_M[i] = 28;
        }
        else if(i == 4 || i == 6 || i == 9 || i == 11)
        {
            l_M[i] = 30;
        }
    }
    int day = floor(d);

    //查找月日
    if((y - 1900) % 4 == 0)
    {
        l_M[2] = 29;
    }

    int i = 1;
    int temp = 0;
    while((day > temp + l_M[i]) && (i < 12))
    {
        temp += l_M[i];
        i++;
    }

    dt.M = i;
    dt.D = day - temp;

    double time  = (d - day) * 24.0;
    dt.h = fix(time);
    time = (time - double(dt.h)) * 60.0;
    dt.m = fix(time);
    dt.s = (time - double(dt.m)) * 60.0;

    return dt;
}

/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* Update TLE Part
* 向0取整（类似Matlab）
* input：double数
* output：int数
* Process：从C复制而来
* 2019/08/20 sun 16:41：完成；
* 2020/08/01 sun 19:35:Complete the modification to make it run within the integral program；
**********************************************************************************************/
int PositionSystem::fix(double a)
{
    int b = 0;
    if (a > 0)
    {
        b = floor(a);
    }
    if (a == 0.0)
    {
        b = 0;
    }
    if (a < 0)
    {
        a = -a;
        b = floor(a);
        b = -b;
    }

    return b;
}

/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* Update TLE Part
* UTC时间转换为BJT时间
* input：UTC时间
* output：BJT时间
* Process：
* 2020/06/14 sun 00:27:开始；
* 2020/06/14 sun 01:03:完成；
* 2020/08/01 sun 19:37:Complete the modification to make it run within the integral program；
**********************************************************************************************/
PositionSystem::DateTime PositionSystem::UTC2BJT(DateTime U)
{
    DateTime B;
    B.Y = U.Y;B.M = U.M;B.D = U.D;B.h = U.h;B.m = U.m;B.s = U.s;

    int UTCHourMinute = U.h * 100 + U.m;

    int MIN = 60;
    int HOUR = 24;

    if((UTCHourMinute < 0) || UTCHourMinute > 2359)
    {
        return B;
    }

    int UTCMinute = U.h * MIN + U.m;

    int BJTMinute = UTCMinute + 8 * MIN;
    if(BJTMinute <= 1439)
    {
        B.h = fix(double(BJTMinute/MIN));
        B.m = BJTMinute - B.h * MIN;
    }
    else
    {
        BJTMinute -= HOUR * MIN;
        B.h = fix(double(BJTMinute/MIN));
        B.m = BJTMinute - B.h * MIN;
        B.D++;
    }

    return B;
}


/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* Location Part
* Load LOC.config, extract information
* input：
* output：
* Process：
* 2020/05/26 sun 16:54:Basically realize all the functions of config reading；
* 2020/08/02 sun 22:15:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::on_LocConfigRead_clicked()
{
    //Disable button
    ui->LocMapDisplay->setEnabled(false);
    ui->LocMapAll->setEnabled(false);
    ui->LocMapOne->setEnabled(false);



    int syear = 0,smonth = 0,sday = 0,shour = 0,sminute = 0;
    double ssecond = 0.0;
    double loc_x = 0.0,loc_y = 0.0,loc_z = 0.0;
    int AssistantHigh = 0,posIter = 0;
    ititude LocItitude;
    QDateTime LocDT;
    //Read config
    QString currentpath = QApplication::applicationDirPath();       //Read the path where the .exe is located
//    QString currentpath = "C:/Qt/BaiduMapTest/BaiduMap2";        //Currently a fixed folder
    QString configpath = currentpath + "/config/";
//    qDebug() << configpath << endl;
//    QString filename = QFileDialog::getOpenFileName(this, "打开文件", configpath, "config files(*.config);;Txt(*.txt)");
    QString filename = configpath + "/LOC.config";
    if(filename.isEmpty() == false)
    {
        QFile file(filename);
        bool isok = file.open(QIODevice::ReadOnly);     //Open the file as read-only
        if(isok == true)
        {
            QByteArray array;
            QByteArray configline;
            while(file.atEnd() == false)
            {
                configline = file.readLine();      //Every line read
                array += configline;        //Save the read content in a byte array.
                QString locline;
                locline.prepend(configline);
                //qDebug() << acqline;

                //Get positioning error/result file path and name
                if(locline[0]=="s" && locline[1]=="t")
                {
                    QString LocOutName;
                    int n_name = locline.length() - 18;
                    LocOutName = locline.mid(12,n_name);
                    LoCoutPathandName = currentpath + "/LOC/" + LocOutName + ".txt";     //Location error file name
                    LoCoutPathandName_L = currentpath + "/LOC/" + LocOutName + "L.txt";     //Location result file name
                    //qDebug() <<  LoCoutPathandName <<endl;
                    //qDebug() <<  LoCoutPathandName_L <<endl;
                    ui ->LoctextEdit_2 ->setText(LoCoutPathandName + "\n" + LoCoutPathandName_L);
                }
                //Data time
                if(locline[0]=="s" && locline[1]=="y" && locline[2]=="e")
                {
                    QString year;
                    int n = locline.length() - 6;
                    year = locline.mid(6,n);
                    syear = year.toInt();
                }       //year
                if(locline[0]=="s" && locline[1]=="m" && locline[2]=="o")
                {
                    QString month;
                    int n = locline.length() - 7;
                    month = locline.mid(7,n);
                    smonth = month.toInt();
                }       //month
                if(locline[0]=="s" && locline[1]=="d" && locline[2]=="a")
                {
                    QString day;
                    int n = locline.length() - 5;
                    day = locline.mid(5,n);
                    sday = day.toInt();
                }       //day
                if(locline[0]=="s" && locline[1]=="h" && locline[2]=="o")
                {
                    QString hour;
                    int n = locline.length() - 6;
                    hour = locline.mid(6,n);
                    shour = hour.toInt();
                }       //hour
                if(locline[0]=="s" && locline[1]=="m" && locline[2]=="i")
                {
                    QString minute;
                    int n = locline.length() - 8;
                    minute = locline.mid(8,n);
                    sminute = minute.toInt();
                }       //minute
                if(locline[0]=="s" && locline[1]=="s" && locline[2]=="e")
                {
                    QString second;
                    int n = locline.length() - 8;
                    second = locline.mid(8,n);
                    ssecond = second.toDouble();
                }       //second
                if(locline[0]=="l" && locline[1]=="o" && locline[4]=="x" && locline[5]==":")
                {
                    QString locx;
                    int n = locline.length() - 6;
                    locx = locline.mid(6,n);
                    loc_x = locx.toDouble();
                }       //X
                if(locline[0]=="l" && locline[1]=="o" && locline[4]=="y" && locline[5]==":")
                {
                    QString locy;
                    int n = locline.length() - 6;
                    locy = locline.mid(6,n);
                    loc_y = locy.toDouble();
                }       //Y
                if(locline[0]=="l" && locline[1]=="o" && locline[4]=="z" && locline[5]==":")
                {
                    QString locz;
                    int n = locline.length() - 6;
                    locz = locline.mid(6,n);
                    loc_z = locz.toDouble();
                }       //Z
                if(locline[0]=="A" && locline[1]=="s" && locline[4]=="s")
                {
                    QString Assistant_High;
                    int n = locline.length() - 15;
                    Assistant_High = locline.mid(15,n);
                    AssistantHigh = Assistant_High.toInt();
                }       //Elevation assist
                if(locline[0]=="p" && locline[1]=="o" && locline[4]=="i")
                {
                    QString iter;
                    int n = locline.length() - 9;
                    iter = locline.mid(9,n);
                    posIter = iter.toInt();
                    Iter = posIter;
                }       //Positioning times
            }
            ui->LoctextEdit->setText(array);
        }
        file.close();       //Close the file after reading the file.
//        qDebug() << loc_x << endl;
//        qDebug() << syear << "/" << smonth << "/" << sday << endl;
//        qDebug() << shour << ":" << sminute << ":" << ssecond << endl;

        LocItitude = togeod(6378137,298.257223563,loc_x,loc_y,loc_z);       //Convert to latitude, longitude and High
    }

    //Display the read data on the panel
    //Time
    LocDT = intToQDatetime(syear,smonth,sday,shour,sminute,ssecond);        //Convert the read date and time to the required format
    //qDebug() << LocDT.toString("yyyy-MM-dd hh:mm:ss")  << endl;
    ui->LocdateTimeEdit->setDisplayFormat("yyyy/MM/dd HH:mm:ss");   //Set display format
    ui->LocdateTimeEdit->setDateTime(LocDT);
    //latitude, longitude and High
    Loc_Ititude = LocItitude;
    if(LocItitude.longitude > 0)
    {
        ui->LocLongitude->setText("E " + QString::number(LocItitude.longitude));
    }
    else if(LocItitude.longitude < 0)
    {
        ui->LocLongitude->setText("W " + QString::number(-1 * LocItitude.longitude));
    }
    else
    {
        ui->LocLongitude->setText(QString::number(LocItitude.longitude));
    }
    if(LocItitude.latitude > 0)
    {
        ui->LocLatitude->setText("N " + QString::number(LocItitude.latitude));
    }
    else if(LocItitude.latitude < 0)
    {
        ui->LocLatitude->setText("S " + QString::number(-1 * LocItitude.latitude));
    }
    else
    {
        ui->LocLatitude->setText(QString::number(LocItitude.latitude));
    }
    ui->LocHighlight->setText(QString::number(LocItitude.h));
    //Elevation assist
    if(AssistantHigh == 3)
    {
        ui->LocHighAissradioButton->setChecked(true);
    }
    else
    {
        ui->LocHighAissradioButton->setChecked(false);
    }
    //Positioning times
    ui->LocPosIterL->setText(QString::number(posIter));

    //After .config has been read, enable the next button
    ui->LocMapDisplay->setEnabled(true);
    ui->LocConfigWrite->setEnabled(true);
    ui->LocStartLoc->setEnabled(true);
    ui->LocEndLoc->setEnabled(true);
}

/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* Location Part
* Write LOC.config from textEdit
* input:
* output:
* Process:
* 2020/08/02 sun 23:56:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::on_LocConfigWrite_clicked()
{
    //Set Location's button disabled
    ui->LocConfigWrite->setEnabled(false);
    ui->LocMapDisplay->setEnabled(false);
    ui->LocMapAll->setEnabled(false);
    ui->LocMapOne->setEnabled(false);
    ui->LocMapRefCircle->setEnabled(false);
    ui->LocMapResCircle->setEnabled(false);
    ui->LocStartLoc->setEnabled(false);
    ui->LocEndLoc->setEnabled(false);

    //Write config
    QString currentpath = QApplication::applicationDirPath();       //Read the path where the .exe is located
    QString configpath = currentpath + "/config/";
    //QString filename = QFileDialog::getOpenFileName(this, "打开文件", configpath, "config files(*.config);;Txt(*.txt)");
    QString filename = configpath + "LOC.config";
    QString str;
    if(filename.isEmpty() == false)
    {
        QFile file(filename);
        bool isok = file.open(QIODevice::WriteOnly);
        if(isok == true)
        {
            //Rewrite from interface
            str = ui->LoctextEdit->toPlainText();
            file.write(str.toUtf8());
        }
        file.close();
        //ui->AcqConfigtextEdit->setText(str + "\n" + "Write " + filename + " OK!!");
    }

    //Read the config file written above
    int syear = 0,smonth = 0,sday = 0,shour = 0,sminute = 0;
    double ssecond = 0.0;
    double loc_x = 0.0,loc_y = 0.0,loc_z = 0.0;
    int AssistantHigh = 0,posIter = 0;
    ititude LocItitude;
    QDateTime LocDT;
    if(filename.isEmpty() == false)
    {
        QFile file(filename);
        bool isok = file.open(QIODevice::ReadOnly);     //Open the file as read-only
        if(isok == true)
        {
            QByteArray array;
            QByteArray configline;
            while(file.atEnd() == false)
            {
                configline = file.readLine();      //Every line read
                array += configline;        //Save the read content in a byte array.
                QString locline;
                locline.prepend(configline);
                //qDebug() << acqline;

                //Get positioning error/result file path and name
                if(locline[0]=="s" && locline[1]=="t")
                {
                    QString LocOutName;
                    int n_name = locline.length() - 18;
                    LocOutName = locline.mid(12,n_name);
                    LoCoutPathandName = currentpath + "/LOC/" + LocOutName + ".txt";     //Location error file name
                    LoCoutPathandName_L = currentpath + "/LOC/" + LocOutName + "L.txt";     //Location result file name
                    //qDebug() <<  LoCoutPathandName <<endl;
                    //qDebug() <<  LoCoutPathandName_L <<endl;
                    ui ->LoctextEdit_2 ->setText(LoCoutPathandName + "\n" + LoCoutPathandName_L);
                }
                //Data time
                if(locline[0]=="s" && locline[1]=="y" && locline[2]=="e")
                {
                    QString year;
                    int n = locline.length() - 6;
                    year = locline.mid(6,n);
                    syear = year.toInt();
                }       //year
                if(locline[0]=="s" && locline[1]=="m" && locline[2]=="o")
                {
                    QString month;
                    int n = locline.length() - 7;
                    month = locline.mid(7,n);
                    smonth = month.toInt();
                }       //month
                if(locline[0]=="s" && locline[1]=="d" && locline[2]=="a")
                {
                    QString day;
                    int n = locline.length() - 5;
                    day = locline.mid(5,n);
                    sday = day.toInt();
                }       //day
                if(locline[0]=="s" && locline[1]=="h" && locline[2]=="o")
                {
                    QString hour;
                    int n = locline.length() - 6;
                    hour = locline.mid(6,n);
                    shour = hour.toInt();
                }       //hour
                if(locline[0]=="s" && locline[1]=="m" && locline[2]=="i")
                {
                    QString minute;
                    int n = locline.length() - 8;
                    minute = locline.mid(8,n);
                    sminute = minute.toInt();
                }       //minute
                if(locline[0]=="s" && locline[1]=="s" && locline[2]=="e")
                {
                    QString second;
                    int n = locline.length() - 8;
                    second = locline.mid(8,n);
                    ssecond = second.toDouble();
                }       //second
                if(locline[0]=="l" && locline[1]=="o" && locline[4]=="x" && locline[5]==":")
                {
                    QString locx;
                    int n = locline.length() - 6;
                    locx = locline.mid(6,n);
                    loc_x = locx.toDouble();
                }       //X
                if(locline[0]=="l" && locline[1]=="o" && locline[4]=="y" && locline[5]==":")
                {
                    QString locy;
                    int n = locline.length() - 6;
                    locy = locline.mid(6,n);
                    loc_y = locy.toDouble();
                }       //Y
                if(locline[0]=="l" && locline[1]=="o" && locline[4]=="z" && locline[5]==":")
                {
                    QString locz;
                    int n = locline.length() - 6;
                    locz = locline.mid(6,n);
                    loc_z = locz.toDouble();
                }       //Z
                if(locline[0]=="A" && locline[1]=="s" && locline[4]=="s")
                {
                    QString Assistant_High;
                    int n = locline.length() - 15;
                    Assistant_High = locline.mid(15,n);
                    AssistantHigh = Assistant_High.toInt();
                }       //Elevation assist
                if(locline[0]=="p" && locline[1]=="o" && locline[4]=="i")
                {
                    QString iter;
                    int n = locline.length() - 9;
                    iter = locline.mid(9,n);
                    posIter = iter.toInt();
                    Iter = posIter;
                }       //Positioning times
            }
            ui->LoctextEdit->setText(array);
        }
        file.close();       //Close the file after reading the file.

        LocItitude = togeod(6378137,298.257223563,loc_x,loc_y,loc_z);       //Convert to latitude, longitude and High
    }

    //Display the read data on the panel
    //Time
    LocDT = intToQDatetime(syear,smonth,sday,shour,sminute,ssecond);        //Convert the read date and time to the required format

    ui->LocdateTimeEdit->setDisplayFormat("yyyy/MM/dd HH:mm:ss");   //Set display format
    ui->LocdateTimeEdit->setDateTime(LocDT);

    //latitude, longitude and High
    Loc_Ititude = LocItitude;
    if(LocItitude.longitude > 0)
    {
        ui->LocLongitude->setText("E " + QString::number(LocItitude.longitude));
    }
    else if(LocItitude.longitude < 0)
    {
        ui->LocLongitude->setText("W " + QString::number(-1 * LocItitude.longitude));
    }
    else
    {
        ui->LocLongitude->setText(QString::number(LocItitude.longitude));
    }
    if(LocItitude.latitude > 0)
    {
        ui->LocLatitude->setText("N " + QString::number(LocItitude.latitude));
    }
    else if(LocItitude.latitude < 0)
    {
        ui->LocLatitude->setText("S " + QString::number(-1 * LocItitude.latitude));
    }
    else
    {
        ui->LocLatitude->setText(QString::number(LocItitude.latitude));
    }
    ui->LocHighlight->setText(QString::number(LocItitude.h));
    //Elevation assist
    if(AssistantHigh == 3)
    {
        ui->LocHighAissradioButton->setChecked(true);
    }
    else
    {
        ui->LocHighAissradioButton->setChecked(false);
    }
    //Positioning times
    ui->LocPosIterL->setText(QString::number(posIter));

    //Write success sign
    QString currentText = ui->LoctextEdit_2->toPlainText();
    ui->LoctextEdit_2->setText(currentText + "\n\nWrite " + filename + " OK!!");
    //Keep it at the bottom
    QTextCursor cursor = ui->LoctextEdit_2->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->LoctextEdit_2->setTextCursor(cursor);

    //After .config has been read, enable the next button
    ui->LocMapDisplay->setEnabled(true);
    ui->LocConfigWrite->setEnabled(true);
}

/***********************************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* togeod
* Function：Subroutine to calculate geodetic coordinates latitude, longitude,
*           height given Cartesian coordinates X,Y,Z, and reference ellipsoid
*           values semi-major axis (a) and the inverse of flattening (finv)；
* input:a           - semi-major axis of the reference ellipsoid
*       finv        - inverse of flattening of the reference ellipsoid
*       X,Y,Z       - Cartesian coordinates
* output:Contained in the structure CanseeHigh，latitude/longitude/height above reference ellipsoid
* other:
* Copy it directly from the original C file to convert from XYZ to latitude and longitude
%  Copyright (C) 1987 C. Goad, Columbus, Ohio
%  Reprinted with permission of author, 1996
%  Fortran code translated into MATLAB
%  Kai Borre 03-30-96
%
% CVS record:
% $Id: togeod.m,v 1.1.1.1.2.4 2006/08/22 13:45:59 dpl Exp $
**************************************************************************************************************/
PositionSystem::ititude PositionSystem::togeod(double semimajor, double Rec_flat, double X, double Y, double Z)
{
    ititude togeodOut;
    togeodOut.latitude = 0;
    togeodOut.longitude = 0;
    togeodOut.h = 0;
    double tolsq=1.0e-10;
    int maxit = 10;
    double esq = 0;
    double oneesq = 0;
    double sinphi = 0;
    double cosphi = 0;
    double N_phi = 0;


    //compute radians-to-degree factor
    double rtd = 180 / 3.1415926535898;

    //compute square of eccentricity
    if (Rec_flat < 1.0e-20)
    {
        esq = 0;
    }
    else
    {
        esq = (2 - 1 / Rec_flat) / Rec_flat;
    }
    oneesq = 1 - esq;

    //first guess
    //P is distanse from spin axis
    double P = 0;
    P = sqrt(X*X + Y*Y);
    //direct calculation of langitude

    if (P > 1.0e-20)
    {
        togeodOut.longitude = atan2(Y, X)*rtd;
    }
    else
    {
        togeodOut.longitude = 0;
    }

    if (togeodOut.longitude < 0)
    {
        togeodOut.longitude = togeodOut.longitude + 360;
    }

    //r is distance from origin(0.0.0)
    double r = 0;
    r = sqrt(P*P + Z*Z);
    if (r > 1.0e-20)
    {
        sinphi = Z / r;
    }
    else
    {
        sinphi = 0;
    }
    togeodOut.latitude = asin(sinphi);

    //initial value of hright = distance from origin minus
    //approximate distance from origin to surface of elliosoid
    if (r < 1.0e-20)
    {
        togeodOut.h = 0;
        return togeodOut;
    }
    togeodOut.h = r - semimajor*(1 - sinphi*sinphi / Rec_flat);

    //iterate
    for (int i = 0; i < maxit; i++)
    {
        sinphi = sin(togeodOut.latitude);
        cosphi = cos(togeodOut.latitude);

        //compute radius of curvature in prime vertical direction
        N_phi = semimajor / sqrt(1 - esq*sinphi*sinphi);

        //compute residuals in P and Z
        double dP = 0;
        double dZ = 0;
        dP = P - (N_phi + togeodOut.h)*cosphi;
        dZ = Z - (N_phi*oneesq + togeodOut.h)*sinphi;

        //update hright and latitude
        togeodOut.h = togeodOut.h + (sinphi*dZ + cosphi*dP);
        togeodOut.latitude = togeodOut.latitude + (cosphi*dZ - sinphi*dP) / (N_phi + togeodOut.h);

        //test for convergence
        if ((dP*dP + dZ*dZ) < tolsq)
        {
            break;
        }

        //Not Converged:Warn user
        if (i == maxit)
        {
            printf("Problem in TOGEOD, did not converge in %2d iterrations!",i);
        }
    }//end of maxit circle

    togeodOut.latitude = togeodOut.latitude * rtd;

    return togeodOut;
}

/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* Location Part
* Convert the year, month and day of int type to QDatetime type
* input: Year month day hour minute second
* output: QDatetime
* Process:
* 2020/05/26 sun 16:14:Start；
* 2020/05/26 sun 16:44:Unmistakable；
* 2020/08/02 sun 22:15:Complete the modification to make it run within the integral program；
**********************************************************************************************/
QDateTime PositionSystem::intToQDatetime(int year,int month,int day,int hour,int minute,double second_d)
{
    QDateTime DT;
    QString DT_s,year_s,month_s,day_s,hour_s,minute_s,second_s;      //Prepare to convert time format
    if(year >= 1000 && year <= 9999)
    {
        year_s = QString::number(year);        //Consider the length of year must be 4
    }
    else
    {
        ui ->LoctextEdit_2 ->setText("Year Error");  //Report an error
    }
    //月
    if(month < 10 && month > 0)
    {
        month_s = QString::number(month);
        month_s = "0" + month_s;//补0
    }
    else if(month < 13 && month > 9)
    {
        month_s = QString::number(month);
    }
    else
    {
        ui ->LoctextEdit_2 ->setText("Month Error");  //Report an error
    }
    //日
    if(day < 10 && day > 0)
    {
        day_s = QString::number(day);
        day_s = "0" + day_s;//补0
    }
    else if(day < 32 && day > 9)
    {
        day_s = QString::number(day);
    }
    else
    {
        ui ->LoctextEdit_2 ->setText("Day Error");  //Report an error
    }
    //时
    if(hour < 10 && hour > 0)
    {
        hour_s = QString::number(hour);
        hour_s = "0" + hour_s;//补0
    }
    else if(hour < 25 && hour >= 9)
    {
        hour_s = QString::number(hour);
    }
    else
    {
        ui ->LoctextEdit_2 ->setText("Hour Error");  //Report an error
    }
    //分
    if(minute < 10 && minute >= 0)
    {
        minute_s = QString::number(minute);
        minute_s = "0" + minute_s;//补0
    }
    else if(minute < 61 && minute > 9)
    {
        minute_s = QString::number(minute);
    }
    else
    {
        ui ->LoctextEdit_2 ->setText("Minute Error");  //Report an error
    }
    //秒
    int second = (int)second_d;
    if(second < 10 && second > 0)
    {
        second_s = QString::number(second);
        second_s = "0" + second_s;//补0
    }
    else if(second <= 60 && second >= 10)
    {
        second_s = QString::number(second);
    }
    else
    {
        ui ->LoctextEdit_2 ->setText("Second Error");  //Report an error
    }
    DT_s = year_s + "-" + month_s + "-" + day_s + " " + hour_s + ":" + minute_s + ":" + second_s;
//    qDebug() << "Str:" << DT_s << endl;
    DT = QDateTime::fromString(DT_s,"yyyy-MM-dd hh:mm:ss");
    //qDebug() << DT.toString("yyyy-MM-dd hh:mm:ss")  << endl;

    return DT;
}

/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* Location Part
* After the Map is loaded, enable the next button
* input:
* output:
* Process:
* 2020/06/03 sun 09:35:Start；
* 2020/06/03 sun 09:40:Unmistakable；
* 2020/08/01 sun 22:38:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::MapLoadFinished(void)
{
    ui->LocMapDisplay->setEnabled(true);
    ui->LocMapAll->setEnabled(true);
    ui->LocMapOne->setEnabled(true);
    ui->LocMapRefCircle->setEnabled(true);
    ui->LocMapResCircle->setEnabled(true);
}

/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* Location Part
* Load and display the map
* input:
* output:
* Process:
* 2020/05/21 sun 18:47:Access the Baidu map API to display the location,
*                      and the WGS84->BD conversion function will be called；
* 2020/08/02 sun 22:42:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::on_LocMapDisplay_clicked()
{
    //Set Location's button disabled
    ui->LocConfigWrite->setEnabled(false);
    ui->LocMapDisplay->setEnabled(false);
    ui->LocMapAll->setEnabled(false);
    ui->LocMapOne->setEnabled(false);
    ui->LocMapRefCircle->setEnabled(false);
    ui->LocMapResCircle->setEnabled(false);

    //Set the ordinal number to zero
    current_i = 0;

    QString currentpath = QApplication::applicationDirPath();       //Read the path where the .exe is located
    QString path = currentpath + "/LoctiononBaiduMap.html";
//    QString path = "C:/Qt/BaiduMapTest/BaiduMap2/BaiduMap2.html";        //Fixed path
    QUrl url(path);

    ui->LocMapView->load(url);
    ui->LocMapView->show();

    //Read positioning results from XXXXL.txt
    QString filename = LoCoutPathandName_L;

    LocData.resize(Iter + 5);
    index.resize(Iter + 5);
    if(filename.isEmpty() == false)
    {
        QFile file(filename);
        bool isok = file.open(QIODevice::ReadOnly);     //Open the file as read-only
        if(isok == true)
        {
            QString Currunt_textEdit = ui->LoctextEdit->toPlainText();
            QByteArray array;
            QByteArray line;
            bool DataFlag = false;
            int i = 0;
            while(file.atEnd() == false)
            {
                line = file.readLine();      //Every line read
                array += line;      //Save the read content in a byte array.
                QString locline;
                locline.prepend(line);

                //Read positioning results in format
                if(locline[0]=="i" && locline[1]=="i" && locline[2]=="i")
                {
                    DataFlag = true;
                }
                else if(DataFlag == true)
                {
                    i++;
                    QString str(line);
                    QVector<QStringRef> lineRef;
                    lineRef = str.splitRef(' ',QString::SkipEmptyParts);

                    index[i] = lineRef[0].toInt();
                    LocData[i].latitude = lineRef[4].toDouble();
                    LocData[i].longitude = lineRef[5].toDouble();
                    LocData[i].h = lineRef[6].toDouble();
//                    qDebug() << index[i] << " " <<  LocData[i].latitude << " " << LocData[i].longitude << endl;
                    qDebug("%d %f %f",index[i], LocData[i].latitude,LocData[i].longitude);
                }
            }
            ui->LoctextEdit->setText(Currunt_textEdit + array);
            //Move the cursor to the end
            QTextCursor cursor = ui->LoctextEdit->textCursor();
            cursor.movePosition(QTextCursor::End);
            ui->LoctextEdit->setTextCursor(cursor);
        }
        file.close();       //Close the file after reading the file.
    }

//    connect(ui->MapView, SIGNAL(loadFinished(bool)), this, SLOT(MapLoadFinished(void)));//加载地图完成后执行MapLoadFinished函数

    MapLoadFinished();      //Execute the MapLoadFinished function after loading the map
}

/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* Location Part
* Button to locate all results on the map
* input:
* output:
* Process:
* 2020/06/02 sun 17:52:Achieve reading positioning results；
* 2020/06/02 sun 18:52:Display all positioning through interaction with Baidu map API js;
* 2020/06/03 sun 16:24:Add reading reference point；
* 2020/06/03 sun 16:51:Combine read positioning results to display map；
* 2020/08/02 sun 22:58:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::on_LocMapAll_clicked()
{
    //Set Location's button disabled
    ui->LocMapDisplay->setEnabled(false);
    ui->LocMapAll->setEnabled(false);
    ui->LocMapOne->setEnabled(false);
    ui->LocMapRefCircle->setEnabled(false);
    ui->LocMapResCircle->setEnabled(false);

    //Place the reference point on the map
    QString command_ = QString("addreal(%1,%2)").arg(QString::number(Loc_Ititude.longitude)).arg(QString::number(Loc_Ititude.latitude));
    ui->LocMapView->page()->runJavaScript(command_);

    //Point all positioning results on the map
    for(int j = 1;j < Iter + 1;j++)
    {
        QString command = QString("addpoint(%1,%2)").arg(QString::number(LocData[j].longitude)).arg(QString::number(LocData[j].latitude));
        ui->LocMapView->page()->runJavaScript(command);
    }

    //Enable button
    ui->LocMapDisplay->setEnabled(true);
    ui->LocMapAll->setEnabled(true);
    ui->LocMapRefCircle->setEnabled(true);
    ui->LocMapResCircle->setEnabled(true);
}

/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* Location Part
* Button to locate One results on the map sequentially
* input:
* output:
* Process:
* 2020/06/03 sun 16:53:Start;
* 2020/06/03 sun 17:30:Complpleted;
* 2020/08/02 sun 23:03:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::on_LocMapOne_clicked()
{
    //Set Location's button disabled
    ui->LocMapDisplay->setEnabled(false);
    ui->LocMapAll->setEnabled(false);
    ui->LocMapOne->setEnabled(false);
    ui->LocMapRefCircle->setEnabled(false);
    ui->LocMapResCircle->setEnabled(false);

    //Read the current content of text2
    QString Currunt_textEdit = ui->LoctextEdit_2->toPlainText();
    QString text;

    //Press this button for the first time to display the reference point
    if(current_i == 0)
    {
        text = "\nReal: " + QString::number(Loc_Ititude.longitude) + "," + QString::number(Loc_Ititude.latitude) + "\n";
        QString command_ = QString("addreal(%1,%2)").arg(QString::number(Loc_Ititude.longitude)).arg(QString::number(Loc_Ititude.latitude));
        ui->LocMapView->page()->runJavaScript(command_);
        current_i++;
    }
    else
    {
        current_i++;
        //Display anchor points in turn
        if(current_i <= Iter)
        {
            text ="\n" + QString::number(index[current_i]) +  ": " + QString::number(LocData[current_i].longitude) + "," + QString::number(LocData[current_i].latitude) + "\n";
            QString command = QString("addpoint(%1,%2)").arg(QString::number(LocData[current_i].longitude)).arg(QString::number(LocData[current_i].latitude));
            ui->LocMapView->page()->runJavaScript(command);
        }
    }

    //Display information in textEdit_2
    ui->LoctextEdit_2->setText(Currunt_textEdit + text);
    //Move the cursor to the end
    QTextCursor cursor = ui->LoctextEdit_2->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->LoctextEdit_2->setTextCursor(cursor);

    //Enable button
    ui->LocMapDisplay->setEnabled(true);
    ui->LocMapAll->setEnabled(true);
    ui->LocMapRefCircle->setEnabled(true);
    ui->LocMapResCircle->setEnabled(true);
    if(current_i <= Iter)
    {
        ui->LocMapOne->setEnabled(true);
    }
}

/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* Location Part
* Display the distribution of positioning results relative to the reference point on the map
* input:
* output:
* Process:
* 2020/06/03 sun 17:31:Start；
* 2020/06/03 sun 18:37:End；
* 2020/06/03 sun 19:35:Success；
* 2020/08/02 sun 23:08:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::on_LocMapRefCircle_clicked()
{
    //Set Location's button disabled
    ui->LocMapDisplay->setEnabled(false);
    ui->LocMapAll->setEnabled(false);
    ui->LocMapOne->setEnabled(false);
    ui->LocMapRefCircle->setEnabled(false);
    ui->LocMapResCircle->setEnabled(false);

    //Read distance from XXXXX.txt
    QVector<double>dis(10);
    dis.resize(Iter);

    QString filename = LoCoutPathandName;
    if(filename.isEmpty() == false)
    {
        QFile file(filename);
        bool isok = file.open(QIODevice::ReadOnly);     //Open the file as read-only
        if(isok == true)
        {
            QString Currunt_textEdit = ui->LoctextEdit->toPlainText();
            QByteArray array;
            QByteArray line;
            bool DataFlag = false;
            int i = 0;
            while(file.atEnd() == false)
            {
                line = file.readLine();      //Every line read
                array += line;      //Save the read content in a byte array
                QString locline;
                locline.prepend(line);

                //Read positioning results in format
                if(locline[0]=="i" && locline[1]=="i" && locline[2]=="i")
                {
                    DataFlag = true;
                }
                else if(locline[0]=="m" && locline[1]=="e" && locline[2]=="a")
                {
                    DataFlag = false;
                }
                else if(DataFlag == true)
                {
                    QString str(line);
                    QVector<QStringRef> lineRef;
                    lineRef = str.splitRef(' ',QString::SkipEmptyParts);

                    dis[i] = lineRef[1].toDouble();
                    //qDebug("%d %f",i + 1, dis[i]);

                    i++;
                }
            }
            ui->LoctextEdit->setText(Currunt_textEdit + array);
           //Move the cursor to the end
            QTextCursor cursor = ui->LoctextEdit->textCursor();
            cursor.movePosition(QTextCursor::End);
            ui->LoctextEdit->setTextCursor(cursor);
        }
        file.close();       //Close the file after reading the file.
    }

    //Sort to find the maximum radius and median radius
    qSort(dis.begin(),dis.end());
    double radius_50 = dis[int(Iter/2)];
    double radius_100 = dis[Iter - 1];
    //qDebug("radius:50: %f,100: %f",radius_50,radius_100);

    //Cooperate with Js to draw a circle with center as the center and radius respectively
    QString commandCir = QString("addcirclereal(%1,%2,%3,%4)").arg(QString::number(Loc_Ititude.longitude)).arg(QString::number(Loc_Ititude.latitude)).arg(QString::number(radius_50)).arg(QString::number(radius_100));
    ui->LocMapView->page()->runJavaScript(commandCir);

    //把按钮使能
    MapLoadFinished();


}

/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* Location Part
* Display the distribution of positioning results relative to the reference point on the map
* input:
* output:
* Process:
* 2020/06/03 sun 19:36:Start；
* 2020/06/03 sun 19:57:Success；
* 2020/08/02 sun 23:14:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::on_LocMapResCircle_clicked()
{
    //Set Location's button disabled
    ui->LocMapDisplay->setEnabled(false);
    ui->LocMapAll->setEnabled(false);
    ui->LocMapOne->setEnabled(false);
    ui->LocMapRefCircle->setEnabled(false);
    ui->LocMapResCircle->setEnabled(false);

    //Read XYZ coordinates from XXXXXL.txt
    QVector<double>X(10);
    QVector<double>Y(10);
    QVector<double>Z(10);
    X.resize(Iter);
    Y.resize(Iter);
    Z.resize(Iter);

    QString filename = LoCoutPathandName_L;
    if(filename.isEmpty() == false)
    {
        QFile file(filename);
        bool isok = file.open(QIODevice::ReadOnly);     //Open the file as read-only
        if(isok == true)
        {
            QString Currunt_textEdit = ui->LoctextEdit->toPlainText();
            QByteArray array;
            QByteArray line;
            bool DataFlag = false;
            int i = 0;
            while(file.atEnd() == false)
            {
                line = file.readLine();      //Every line read
                array += line;      //Save the read content in a byte array
                QString locline;
                locline.prepend(line);
                //Read positioning results in format
                if(locline[0]=="i" && locline[1]=="i" && locline[2]=="i")
                {
                    DataFlag = true;
                }
                else if(DataFlag == true)
                {
                    QString str(line);
                    QVector<QStringRef> lineRef;
                    lineRef = str.splitRef(' ',QString::SkipEmptyParts);

                    X[i] = lineRef[1].toDouble();
                    Y[i] = lineRef[2].toDouble();
                    Z[i] = lineRef[3].toDouble();
                    //qDebug("%d (%f,%f,%f)",i + 1, X[i],Y[i],Z[i]);

                    i++;
                }
            }
            ui->LoctextEdit->setText(Currunt_textEdit + array);
            //Move the cursor to the end
            QTextCursor cursor = ui->LoctextEdit->textCursor();
            cursor.movePosition(QTextCursor::End);
            ui->LoctextEdit->setTextCursor(cursor);
        }
        file.close();       //Close the file after reading the file.
    }


    //Calculate the average point of all points
    ititude center;
    double sumX = 0.0,sumY = 0.0,sumZ = 0.0;
    for(int j = 0;j < Iter;j++)
    {
        sumX += X[j];
        sumY += Y[j];
        sumZ += Z[j];
    }
    double centerX = sumX / Iter;
    double centerY = sumY / Iter;
    double centerZ = sumZ / Iter;
    center = togeod(6378137,298.257223563,centerX,centerY,centerZ);

    //Sort to find the maximum radius and median radius
    QVector<double>dis(10);
    dis.resize(Iter);
    double radius_50 = 0,radius_100 = 0;
    for(int j = 0;j < Iter;j++)
    {
        dis[j] = sqrt(pow((X[j] - centerX),2) + pow((Y[j] - centerY),2) + pow((Z[j] - centerZ),2));
    }
    qSort(dis.begin(),dis.end());
    radius_50 = dis[int(Iter/2)];
    radius_100 = dis[Iter - 1];
    //qDebug("radius:50: %f,100: %f",radius_50,radius_100);


    //Cooperate with Js to draw a circle with center as the center and radius respectively
    QString commandCir = QString("addcircleloc(%1,%2,%3,%4)").arg(QString::number(center.longitude)).arg(QString::number(center.latitude)).arg(QString::number(radius_50)).arg(QString::number(radius_100));
    ui->LocMapView->page()->runJavaScript(commandCir);

    //把按钮使能
    MapLoadFinished();
}

/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* Location Part
* execute IridiumLoc.exe
* input:
* output:
* Process:
* 2020/08/02 sun 23:40:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::on_LocStartLoc_clicked()
{
    //Call IridiumLoc.exe in this folder
    QString currentpath = QApplication::applicationDirPath();       //Read the path where the .exe is located
    QString exepath = currentpath + "/IridiumLoc.exe";
    QString workpath = currentpath;
    //QMessageBox::warning(0,"PATH",exepath,QMessageBox::Yes);

    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_dt =current_date_time.toString("\nyyyy.MM.dd hh:mm:ss");
    QString currentText = ui->AcqStatetextEdit->toPlainText();
    ui->LoctextEdit_2->setText(currentText + "\n\n" + current_dt + ":IRIDIUMLOC.EXE HAS START!!  \n");
    //Keep it at the bottom
    QTextCursor cursor = ui->LoctextEdit_2->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->LoctextEdit_2->setTextCursor(cursor);

    QProcess *LocProcess;
    if (QFileInfo(exepath).exists())
    {
        LocProcess = new QProcess(this);
        connect(LocProcess, SIGNAL(readyRead()),this, SLOT(refreshlocout()));
        QStringList AcqList("ACQ is running...");
        LocProcess->setWorkingDirectory(workpath);
        LocProcess->start(exepath,AcqList);
       //AcqProcess->startDetached(exepath,QStringList(),workpath);
    }
}

/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* Location Part
* turn off IridiumLoc.exe
* input:
* output:
* Process:
* 2020/08/02 sun 23:43:Complete the modification to make it run within the integral program；
**********************************************************************************************/
void PositionSystem::on_LocEndLoc_clicked()
{
    QString c = "taskkill /im IridiumLoc.exe /f";
    int pInt = QProcess::execute(c);    //Close the background IridiumLoc.exe Process, blocking operation, always occupy the cpu, success returns 0, failure returns 1
    if(pInt == 0)
    {
        QMessageBox::warning(0,"PATH","SUCCESS KILL IRIDIUMLOC.EXE!",QMessageBox::Yes);
    }
}

/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* Location Part
* Check whether IridiumLoc.exe has finished running
* input:
* output:
* Process:
* 2020/08/03 sun 00:13:Complete the modification to make it run within the integral program；
* 2020/08/06 sun 00:45:The serial number can be read and the progress can be refreshed；
**********************************************************************************************/
void PositionSystem::refreshlocout(void)
{
    QProcess *LocProcess = (QProcess *)sender();
    QString LocCout1 = LocProcess->readAll();
    LocCout += LocCout1;
    ui->LoctextEdit_2->setText(LocCout);
    //Move the cursor to the end
    QTextCursor cursor = ui->LoctextEdit_2->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->LoctextEdit_2->setTextCursor(cursor);

    //qDebug() << LocCout1 << endl;

    if(LocCout1.contains("output successfuly!",Qt::CaseSensitive))
    {
        QDateTime current_date_time =QDateTime::currentDateTime();
        QString current_dt =current_date_time.toString("\nyyyy.MM.dd hh:mm:ss");
        QString Currunt_textEdit = ui->LoctextEdit_2->toPlainText();
        ui->LoctextEdit_2->setText(Currunt_textEdit + "\n\n" + current_dt + ":" + LoCoutPathandName_L + " output successfully!\nLocation has finished!!  ");
        //Move the cursor to the end
        cursor = ui->LoctextEdit_2->textCursor();
        cursor.movePosition(QTextCursor::End);
        ui->LoctextEdit_2->setTextCursor(cursor);
    }

    int ind = 0;
    if(LocCout1.contains("index",Qt::CaseSensitive))
    {
        QChar qch = LocCout1.at(0);
        char ch = qch.toLatin1();
        for(int i = 8;i < 14; i++)
        {
            qch = LocCout1.at(i);
            ch = qch.toLatin1();
            if(ch >= 48 && ch < 58)
            {
                ind = ind * 10 + ch - 48;
            }
            //qDebug() << i <<  " qch:" << qch <<  " ch:" << ch << "ind: " << ind;
        }
    }

    if(ind !=0)
    {
        int x = round(double(ind * 100) / Iter);
        //qDebug() << " x:" << x ;
        ui->LocprogressBar->setValue(x);
    }



//    QString filename = LoCoutPathandName_L;
//    //qDebug() << "refresh" << filename << endl;
//    if(filename.isEmpty() == false)
//    {
//        QDateTime current_date_time =QDateTime::currentDateTime();
//        QString current_dt =current_date_time.toString("\nyyyy.MM.dd hh:mm:ss");
//        QString Currunt_textEdit = ui->LoctextEdit_2->toPlainText();
//        ui->LoctextEdit_2->setText(Currunt_textEdit + "\n\n" + current_dt + ":" + filename + " output successfully!\nLocation has finished!!  ");
//        //Move the cursor to the end
//        cursor = ui->LoctextEdit_2->textCursor();
//        cursor.movePosition(QTextCursor::End);
//        ui->LoctextEdit_2->setTextCursor(cursor);
//    }
}

