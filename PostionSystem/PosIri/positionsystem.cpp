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
* 2020/08/02 sun 20:13:Position part's interface redeployment completed;
**********************************************************************************************/

#include "positionsystem.h"
#include "ui_positionsystem.h"

#include <QWebEngineView>

PositionSystem::PositionSystem(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PositionSystem)
{
    ui->setupUi(this);

    //In order to show current time
    QTimer *timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpdate()));
    timer->start(1000);

    //Set the range of the serial number Index in Acqsition part
    ui->AcqIndexBspinBox->setRange(0,100000);
    ui->AcqIndexEspinBox->setRange(0,100000);

    //Set Location's button disabled
    ui->LocMapDisplay->setEnabled(false);
    ui->LocMapAll->setEnabled(false);
    ui->LocMapOne->setEnabled(false);
    ui->LocMapRefCircle->setEnabled(false);
    ui->LocMapResCircle->setEnabled(false);
}


PositionSystem::~PositionSystem()
{
    delete ui;
}

//GPS Loc and Log's Global Variable
QByteArray currentDATA;     //串口读取数据
QSerialPort *serial_c = new QSerialPort;        //打开并读取数据的串口
PositionSystem::GPSInfo GPSOut;     //储存所需的GPS信息
int nn = 0;         //从上一次清空text接收到的信息次数

//Acquisition's Global Variable
static int CurruntIndex = 0;
static int TotalIndex = 0;     //总的块数
static int BeginIndex = 0;  //起始块数
QVector<int>Index(10);
QVector<double>Time(10);
QVector<double>Dop(10);

QString AcqOutPathandName;

//Location's Global Variable
QString LoCoutPathandName;
QString LoCoutPathandName_L;
QVector<PositionSystem::ititude>LocData(10);
QVector<int>index(10);
static PositionSystem::ititude Loc_Ititude;
static int Iter = 0;
static int current_i = 0;

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
* 2020/08/01 sun 20:22:修改在总程序框架之内运行；
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
}

/*********************************************************************************************
* sun 20200801
* By sunguiyu96@gmail.com
* GPS Loc and Log Part
* 接收串口的数据并分包（为接收Novatel数据）
* input：
* output：存储在GPS文件夹
* Process：
* 2020/01/02 sun 18:52:开始；
* 2020/01/08 sun 11:15:达到预想效果；
* 2020/01/08 sun 21:10:ASCII有效数据分离，写文件完成；
* 2020/01/09 sun 00:20:根据数据头尾分包程序完成，实测数据通过；
* 2020/08/01 sun 20:31:修改在总程序框架之内运行；
**********************************************************************************************/

void PositionSystem::ReadPort()
{
    GPSOut.time = QDateTime::currentDateTime();
    QByteArray buf;
    buf = serial_c->readAll();

//    QString buf_string = buf;
//    qDebug() << "YYY:" <<buf_string;

    //根据数据头尾分包，解决数据不完整的问题
    QByteArray ReadyDATA = NULL;
    //无头且变量为空
    if((!buf.contains("#")) & (currentDATA.isNull()))
    {
        return;
    }
    //有头无尾，清空原有内容再附加
    if((buf.contains("#")) & (!buf.contains("\n")))
    {
        currentDATA.clear();
        currentDATA.append(buf);
    }
    //无头无尾且变量已有内容，数据中端，直接附加
    if((!buf.contains("#")) & (!buf.contains("\n")) & (!currentDATA.isNull()))
    {
        currentDATA.append(buf);
    }
    //无头有尾且变量已有内容，已完整读取，附加后output再清空
    if((!buf.contains("#")) & (buf.contains("\n")) & (!currentDATA.isNull()))
    {
        currentDATA.append(buf);
        ReadyDATA = currentDATA;
        currentDATA.clear();
    }
    //有头有尾，先清空原内容，再附加，然后output再清空
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
        //接收ASCII的GPS信息
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

        //output到界面
        ui->GPSLatilineEdit->setText(datalist[2]);
        ui->GPSLonglineEdit->setText(datalist[3]);
        ui->GPSHighlineEdit->setText(datalist[4]);
        ui->GPSStatelineEdit->setText(GPSOut.sol_state);
        ui->GPSSatNumlineEdit->setText(datalist[15]);

        QString str = ui->GPStextEdit->toPlainText();       //将字符串与文本联系起来
        int n =0 ;
        str += QString("\n%1: ").arg(nn + 1);
        str += QDateTime::currentDateTime().toString("hh:mm:ss");
        str += "\n";

        //如果记录标志为是则output文件
        if(ui->GPSLogcheckBox->isChecked()==true) //记录数据
        {
            //写入文件
            QString currentpath = QApplication::applicationDirPath();       //读入.exe所在的路径
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
    if(nn > 200)            //读入的太多会阻塞
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
* 2020/08/01 sun 20:37:修改在总程序框架之内运行；
**********************************************************************************************/
void PositionSystem::on_GPSOpenPort_clicked()
{
    //打开串口->读取数据 步骤

    //1 设置串口名（选取串口）
    serial_c->setPortName(ui->GPSPortcomboBox->currentText());

    //2 打开串口
    serial_c->open(QIODevice::ReadWrite);

    //3 设置波特率
    qDebug() << ui->GPSRatecomboBox->currentText();
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
* 2020/08/01 sun 20:37:修改在总程序框架之内运行；
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
* 2020/08/01 sun 20:44:修改在总程序框架之内运行；
**********************************************************************************************/
void PositionSystem::on_GPSSentCommand_clicked()
{
    QString command = "log bestposa ontime 1";
    serial_c->write(command.toUtf8());
    QString str = ui->GPStextEdit->toPlainText();
    ui->GPStextEdit->setText(str + "\n" + "Command has been sent!");
}

/*********************************************************************************************
* sun 20200802
* By sunguiyu96@gmail.com
* Acquisition Part
* 读取Acq.config文件(默认配置文件)函数
* input：
* output：
* Process：
* 2020/08/02 sun 17:42:修改在总程序框架之内运行；
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
}

/*********************************************************************************************
* sun 20200802
* By sunguiyu96@gmail.com
* Acquisition Part
* 读取xx.config文件函数
* input：
* output：
* Process：
* 2020/08/02 sun 17:48:修改在总程序框架之内运行；
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
}

/*********************************************************************************************
* sun 20200802
* By sunguiyu96@gmail.com
* Acquisition Part
* 将打开的xx.config文件重新写入
* input：
* output：
* Process：
* 2020/08/02 sun 18:07:修改在总程序框架之内运行；
**********************************************************************************************/
void PositionSystem::on_AcqWriteCpushButton_clicked()
{
    //写config
    QString currentpath = QApplication::applicationDirPath();       //读入.exe所在的路径
    QString configpath = currentpath + "/config/";
    QString filename = QFileDialog::getOpenFileName(this, "打开文件", configpath, "config files(*.config);;Txt(*.txt)");
    QString str;
    if(filename.isEmpty() == false)
    {
        QFile file(filename);
        bool isok = file.open(QIODevice::WriteOnly);
        if(isok == true)
        {
            //从界面重写
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

    //读上面写的config文件（默认的配置文件）
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

    //写成功标志
    QString currentText = ui->AcqStatetextEdit->toPlainText();
    ui->AcqStatetextEdit->setText(currentText + "\n\nWrite " + filename + " OK!!");
    //使保持在最下面
    QTextCursor cursor = ui->AcqStatetextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->AcqStatetextEdit->setTextCursor(cursor);

}

/*********************************************************************************************
* sun 20200802
* By sunguiyu96@gmail.com
* Acquisition Part
* 开始执行Acq程序
* input：
* output：
* Process：
* 2020/08/02 sun 18:12:修改在总程序框架之内运行；
**********************************************************************************************/
void PositionSystem::on_AcqStartpushButton_clicked()
{
    //调用本文件中的IridiumAcq.exe
    QString currentpath = QApplication::applicationDirPath();       //读入.exe所在的路径
    QString exepath = currentpath + "/IridiumAcq.exe";
    QString workpath = currentpath;
    //QMessageBox::warning(0,"PATH",exepath,QMessageBox::Yes);           //查看当前路径
    QString currentText = ui->AcqStatetextEdit->toPlainText();
    ui->AcqStatetextEdit->setText(currentText + "\n\nIRIDIUMACQ.EXE HAS START!!  \n");
    //使保持在最下面
    QTextCursor cursor = ui->AcqStatetextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->AcqStatetextEdit->setTextCursor(cursor);

    QProcess *pro;
    if (QFileInfo(exepath).exists())
    {
        pro = new QProcess(this);
        connect(pro, SIGNAL(readyReadStandardOutput()),this, SLOT(readFromStdOut()));
        pro->startDetached(exepath,QStringList(),workpath);
//        pro->start(exepath,QStringList(),workpath);
        //ui->textEdit_2->setText("END2   \n");

        QByteArray res = pro->readAllStandardOutput();
        ui->AcqStatetextEdit->append(QString::fromLocal8Bit(res));
        //ui->textEdit_2->setText(pro->readAllStandardOutput());
        //ui->textEdit_2->append("\n END");
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
* 2020/08/02 sun 18:14:修改在总程序框架之内运行；
**********************************************************************************************/
void PositionSystem::on_AcqEndpushButton_clicked()
{
    //关闭IridiumAcq.exeProcess
    QString c = "taskkill /im IridiumAcq.exe /f";
       int pInt = QProcess::execute(c);    //关闭后台notepad.exeProcess，阻塞式运行,一直占用cpu,成功返回0，失败返回1
       if(pInt==0)
       {
           QMessageBox::warning(0,"PATH","SUCCESS KILL IRIDIUMACQ.EXE!",QMessageBox::Yes);           //查看当前路径
       }

}

/*********************************************************************************************
* sun 20200802
* By sunguiyu96@gmail.com
* Acquisition Part
* （自动）执行刷新程序
* input：
* output：
* Process：
* 2020/08/02 sun 18:18:修改在总程序框架之内运行；
**********************************************************************************************/
void PositionSystem::on_AcqRefreshpushButton_clicked()
{
    if(ui->AcqFreshcheckBox->isChecked()==true)
    {
        QTimer *timerrefresh = new QTimer(this);
        connect(timerrefresh,SIGNAL(timeout()),this,SLOT(refreshacqout()));
        timerrefresh->start(1000 * 5);        //5s刷新一次
    }
    else
    {
        refreshacqout();
    }
}

/*********************************************************************************************
* sun 20200802
* By sunguiyu96@gmail.com
* Acquisition Part
* 读取、画图、显示进展总函数
* input：
* output：
* Process：
* 2020/08/02 sun 18:18:修改在总程序框架之内运行；
**********************************************************************************************/
void PositionSystem::refreshacqout(void)
{
    ReadData();     //读取捕获结果
    PlotData();     //画图
    RefreshBar();   //显示进展
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
* 2020/08/02 sun 18:18:修改在总程序框架之内运行；
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

    qDebug() << "NUM OF LINE: " << NLine ;
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

            qDebug() << str;

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
* 2020/08/02 sun 18:24:修改在总程序框架之内运行；
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
* 刷新processBar,展示捕获的进展
* input：
* output：
* Process：
* 2019/12/13 sun 0:22:开始；
* 2020/08/02 sun 18:25:修改在总程序框架之内运行；
**********************************************************************************************/
void PositionSystem::RefreshBar()
{
    qDebug() << CurruntIndex;
    int x = round((CurruntIndex * 100)/TotalIndex);
    ui->AcqprogressBar->setValue(x);
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
* 2020/08/01 sun 19:12:修改在总程序框架之内运行；
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

    qDebug() << "Reading code from " << pathIridium;

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
        qDebug() << "Cannot open the file: " << FILE_NAME;
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
* 2020/08/01 sun 19:23:修改在总程序框架之内运行；
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

    qDebug() << "Reading code from " << pathIridium;

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
        qDebug() << "Cannot open the file: " << FILE_NAME;
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
* 2020/08/01 sun 19:26:修改在总程序框架之内运行；
**********************************************************************************************/
void PositionSystem::on_UpdateTLE_clicked()
{
    //更新过程中，几个按钮无效
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
            qDebug() << "Cannot open the file: " << outfileName;
        }
        QTextStream out(&file);

        out << TLE;

        Current_textEdit = ui->UptextEdit->toPlainText();
        QString current_dt =current_date_time.toString("\nyyyy.MM.dd hh:mm:ss");
        ui->UptextEdit->setText(Current_textEdit + current_dt + ": " +current_date + ".tle has updated successfully!\n\n");
        //移动光标到末尾
        cursor.movePosition(QTextCursor::End);
        ui->UptextEdit->setTextCursor(cursor);
    }

    ui->Iridium->setEnabled(true);
    ui->IridiumNext->setEnabled(true);
    ui->UpdateTLE->setEnabled(true);
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
* 2020/08/01 sun 19:31:修改在总程序框架之内运行；
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
        ui ->UptextEdit_2 ->setText("Year Error");  //报错
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
        ui ->UptextEdit_2 ->setText("Month Error");  //报错
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
        ui ->UptextEdit_2 ->setText("Day Error");  //报错
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
         ui ->UptextEdit_2 ->setText("Hour Error");  //报错
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
        ui ->UptextEdit_2 ->setText("Minute Error");  //报错
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
        ui ->UptextEdit_2 ->setText("Second Error");  //报错
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
* 2020/08/01 sun 19:34:修改在总程序框架之内运行；
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
* 2020/08/01 sun 19:35:修改在总程序框架之内运行；
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
* 2020/08/01 sun 19:37:修改在总程序框架之内运行；
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
* Multiple Part
* 时间更新槽函数
* input：
* output：
* Process：
* 2020/06/14 sun 01:08:完成；
* 2020/08/01 sun 19:38:修改在总程序框架之内运行；
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

