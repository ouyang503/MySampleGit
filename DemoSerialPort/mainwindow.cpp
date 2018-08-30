#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->InitComInfo();
    m_bStopShow = false;
    myCom = NULL;
    m_pReadTimer = NULL;
    m_pAutoSendTime = NULL;

    ui->lineEdit_Cycle->setText("1000");
    QRegExp regx("[0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, ui->lineEdit_Cycle );
    ui->lineEdit_Cycle->setValidator( validator );

    m_pAutoSendTime = new QTimer(this);
    connect(m_pAutoSendTime,SIGNAL(timeout()),this,SLOT(autoSendData()));

    this->setWindowTitle(tr("串口调试"));
}
MainWindow::~MainWindow()
{
    if(m_pAutoSendTime)
    {
        m_pAutoSendTime->stop();
        delete m_pAutoSendTime;
        m_pAutoSendTime = NULL;
    }

    if(m_pReadTimer)
    {
        m_pReadTimer->stop();
        delete m_pReadTimer;
        m_pReadTimer = NULL;
    }
    if(myCom)
    {
        myCom->close();
        delete myCom;
        myCom = NULL;
    }

    delete ui;
}
void MainWindow::InitComInfo()
{
    QString str;
    QStringList strList;
    //串口名称
#ifdef _TTY_WIN_
    for(int i=1;i<33;i++)
    {
        str=QString("COM%1").arg(i);
        strList.append(str);
    }
#elif defined(_TTY_IRIX_)
    for(int i=1;i<10;i++)
    {
        str=QString("/dev/ttyf%1").arg(i);
        strList.append(str);
    }
#elif defined(_TTY_HPUX_)
    for(int i=0;i<10;i++)
    {
        str=QString("/dev/tty1p%1").arg(i);
        strList.append(str);
    }
#elif defined(_TTY_SUN_)
    setPortName("/dev/ttya");

#elif defined(_TTY_DIGITAL_)
    for(int i=0;i<10;i++)
    {
        str=QString("/dev/tty0%1").arg(i);
        strList.append(str);
    }
#elif defined(_TTY_FREEBSD_)
    for(int i=0;i<10;i++)
    {
        str=QString("/dev/ttyd%1").arg(i);
        strList.append(str);
    }
#else
    for(int i=0;i<10;i++)
    {
        str=QString("/dev/ttyS%1").arg(i);
        strList.append(str);
    }
#endif
    ui->comboBox_Name->addItems(strList);
    ui->comboBox_Name->setCurrentIndex(0);
    //波特率
    strList.clear();
    strList.append( tr("110"));
    strList.append( tr("300"));
    strList.append( tr("600"));
    strList.append( tr("1200"));
    strList.append( tr("2400"));
    strList.append( tr("4800"));
    strList.append( tr("9600"));
    strList.append( tr("14400"));
    strList.append( tr("19200"));
    strList.append( tr("38400"));
    strList.append( tr("56000"));
    strList.append( tr("57600"));
    strList.append( tr("115200"));
    ui->comboBox_BaudRate->addItems(strList);
    ui->comboBox_BaudRate->setCurrentIndex(6);
    //数据位
    strList.clear();
    strList.append( tr("6"));
    strList.append( tr("7"));
    strList.append( tr("8"));
    ui->comboBox_DataBits->addItems(strList);
    ui->comboBox_DataBits->setCurrentIndex(2);
    //校验位
    strList.clear();
    strList.append( tr("无"));
    strList.append( tr("奇校验"));
    strList.append( tr("偶校验"));
    strList.append( tr("Mark"));
    strList.append( tr("空格校验"));
    ui->comboBox_Parity->addItems(strList);
    ui->comboBox_Parity->setCurrentIndex(0);
    //停止位
    strList.clear();
    strList.append( tr("1"));
    strList.append( tr("1.5"));
    strList.append( tr("2"));
    ui->comboBox_StopBits->addItems(strList);
    ui->comboBox_StopBits->setCurrentIndex(0);

}
void MainWindow::GetPortNameFrmUI(QString & strPortName)
{
    strPortName =ui->comboBox_Name->currentText();
}
void MainWindow::GetPortSettingsFrmUI(PortSettings & stuPortSettings)
{
    QString   str;
    //波特率
    str=  ui->comboBox_BaudRate->currentText();
    BaudRateType baudRate;
    switch (str.toInt())
    {
    case 110:
        baudRate = BAUD110;
        break;
    case 300:
        baudRate = BAUD300;
        break;
    case 600:
        baudRate = BAUD600;
        break;
    case 1200:
        baudRate = BAUD1200;
        break;
    case 2400:
        baudRate = BAUD2400;
        break;
    case 4800:
        baudRate = BAUD4800;
        break;
    case 9600:
        baudRate = BAUD9600;
        break;
    case 14400:
        baudRate = BAUD14400;
        break;
    case 19200:
        baudRate = BAUD19200;
        break;
    case 38400:
        baudRate = BAUD38400;
        break;
    case 56000:
        baudRate = BAUD56000;
        break;
    case 57600:
        baudRate = BAUD57600;
        break;
    case 115200:
        baudRate = BAUD115200;
        break;
    default:
        baudRate =BAUD9600;
    }
    stuPortSettings.BaudRate =  baudRate;
    //数据位
    str=  ui->comboBox_DataBits->currentText();
    switch(str.toInt())
    {
    case 6:
        stuPortSettings.DataBits = DATA_6 ;
        break;
    case 7:
        stuPortSettings.DataBits = DATA_7 ;
        break;
    case 8:
        stuPortSettings.DataBits = DATA_8 ;
        break;
    default:
        stuPortSettings.DataBits = DATA_8 ;
    }
    //校验位
    int index=  ui->comboBox_Parity->currentIndex();
    switch(index)
    {
    case 0:
        stuPortSettings.Parity = PAR_NONE;
        break;
    case 1:
        stuPortSettings.Parity = PAR_ODD;
        break;
    case 2:
        stuPortSettings.Parity = PAR_EVEN;
        break;
    case 3:
        stuPortSettings.Parity = PAR_MARK;
        break;
    case 4:
        stuPortSettings.Parity = PAR_SPACE;
        break;
    default:
        stuPortSettings.Parity = PAR_NONE;
    }
    //停止位
    index=  ui->comboBox_StopBits->currentIndex();
    switch(index)
    {
    case 0:
        stuPortSettings.StopBits =  STOP_1;
        break;
    case 1:
        stuPortSettings.StopBits =  STOP_1_5;
        break;
    case 2:
        stuPortSettings.StopBits =  STOP_2;
        break;
    default:
        stuPortSettings.StopBits =  STOP_1;
    }
    //数据流控制设置，我们设置为无数据流控制*/
    stuPortSettings.FlowControl =FLOW_OFF;
    stuPortSettings.Timeout_Millisec = 10;
}
void MainWindow::readMyCom() //读取串口数据并显示出来
{
    static int i =0;
    QByteArray temp = myCom->readAll(); //读取串口缓冲区的所有数据给临时变量temp
    if(!temp.isEmpty())
    {
        i =0;
        if(m_bStopShow)
        {
            return;
        }
        if(ui->checkBox_RecvBy16->isChecked())
        {
            QByteArray  org =temp.toHex();
            int size= org.size();
            int space= getRoung(size*1.0/2+0.5,1)-1;
            if(space<=0)
                return;
            for(int i=0,pos=2;i<space;++i,pos+=(2+1))
            {
                org.insert(pos,QChar(' '));
            }

            ui->textEdit_Recv->insertPlainText(org);


        }
        else
        {
            ui->textEdit_Recv->insertPlainText(temp);
        }

        if(ui->checkBox_AutoClear->isChecked())
        {
            if(ui->textEdit_Recv->toPlainText().length()>1000)
            {
                ui->textEdit_Recv->clear();
            }
        }
        if(ui->checkBox_ChangeLine->isChecked())
        {
            ui->textEdit_Recv->insertPlainText("\r\n");
        }

        ui->textEdit_Recv->moveCursor(QTextCursor::End);
        SetLightState(ui->BtnLightRecv,LIGHT_COLOR_GREEN);
    }
    else
    {
        i =i+1;
        if(i>10)
        {
            QTimer::singleShot( 100, this, SLOT(RestoreRecvLight()) );
            i =0;
        }
    }
}
void MainWindow::autoSendData()
{
    if(myCom)
    {
        SendData();
    }
    else
    {
        //  this->statusBar()->showMessage(tr("串口未打开"));
    }
}
void MainWindow::on_BtnSend_1_clicked()
{
    if(myCom)
    {
        SendData();
    }
    else
    {
        this->statusBar()->showMessage(tr("串口未打开"));
    }
}
void MainWindow::on_BtnOpenCOM_clicked()
{
    QString strName;
    PortSettings stuPortSettings;
    this->GetPortNameFrmUI(strName);
    this->GetPortSettingsFrmUI(stuPortSettings);

    if(myCom)
    {
        if(m_pReadTimer)
        {
            m_pReadTimer->stop();
            delete m_pReadTimer;
            m_pReadTimer = NULL;
        }
        myCom->close();
        delete myCom;
        myCom = NULL;
        ui->BtnOpenCOM->setText(tr("打开串口"));
        this->SetLightState( ui->BtnLightStatue,LIGHT_COLOR_GRAY);
        this->SetLightState( ui->BtnLightSend,LIGHT_COLOR_GRAY);
        this->SetLightState( ui->BtnLightRecv,LIGHT_COLOR_GRAY);
    }
    else
    {

        strName = QString("\\\\.\\%1").arg(strName);
        myCom = new QextSerialPort(strName,stuPortSettings,QextSerialBase::Polling);

        if(myCom ->open(QIODevice::ReadWrite))//以读写方式打开串口
        {
            myCom->setBaudRate(stuPortSettings.BaudRate);
            myCom->setDataBits(stuPortSettings.DataBits);
            myCom->setStopBits(stuPortSettings.StopBits);
            myCom->setParity(stuPortSettings.Parity);
            myCom->setFlowControl(stuPortSettings.FlowControl);
            myCom->setTimeout(500);

            //connect(myCom,SIGNAL(readyRead()),this,SLOT(readMyCom()));
            m_pReadTimer = new QTimer(this);
            m_pReadTimer->start(100);
            connect(m_pReadTimer,SIGNAL(timeout()),this,SLOT(readMyCom()));
            ui->BtnOpenCOM->setText(tr("关闭串口"));
            this->statusBar()->showMessage(tr("打开成功"));
            this->SetLightState( ui->BtnLightStatue,LIGHT_COLOR_GREEN);
            this->SetLightState( ui->BtnLightSend,LIGHT_COLOR_GRAY);
            this->SetLightState( ui->BtnLightRecv,LIGHT_COLOR_GRAY);
        }
        else
        {
            myCom->close();
            delete myCom;
            myCom = NULL;
            this->SetLightState( ui->BtnLightStatue,LIGHT_COLOR_RED);
            this->statusBar()->showMessage(tr("打开失败"));
        }
  }
}
void MainWindow:: SetLightState( QPushButton * pBtn,int nState)
{
    QString strSheet;
    switch(nState)
    {
    case LIGHT_COLOR_RED:
        strSheet ="QPushButton{border-image:url(:/lightRedUp.png);}\
                QPushButton:hover{border-image:url(:/lightRedUp.png);}\
                QPushButton:pressed{border-image:url(:/lightRedUp.png)}";
                break;
    case LIGHT_COLOR_GREEN:
        strSheet ="QPushButton{border-image:url(:/lightGreenUp.png);}\
                QPushButton:hover{border-image:url(:/lightGreenUp.png);}\
                QPushButton:pressed{border-image:url(:/lightGreenUp.png)}";
                break;

    case LIGHT_COLOR_GRAY:
        strSheet ="QPushButton{border-image:url(:/lightGrayDown.png);}\
                QPushButton:hover{border-image:url(:/lightGrayDown.png);}\
                QPushButton:pressed{border-image:url(:/lightGrayDown.png)}";
                break;
    }
    pBtn->setStyleSheet(strSheet);
}
void MainWindow::SendData()
{
    SetLightState( ui->BtnLightSend,LIGHT_COLOR_GREEN);
    if(ui->checkBox_SendBy16->isChecked())
    {
        QStringList strList;
        strList = ui->textEdit_Send->toPlainText().split(QChar(' '));

        QByteArray arrData;
        bool bOk;
        for(int i = 0;i<strList.length();i++)
        {
            arrData.append(strList.at(i).toInt(&bOk,16));
        }
        myCom->write(arrData);
    }
    else
    {
        myCom->write(ui->textEdit_Send->toPlainText().toAscii()); //以ASCII码形式将数据写入串口
    }
    QTimer::singleShot( 200, this, SLOT(RestoreSendLight()) );
}

void MainWindow::RestoreSendLight()
{
    SetLightState( ui->BtnLightSend,LIGHT_COLOR_GRAY);
}
void MainWindow::RestoreRecvLight()
{
    SetLightState( ui->BtnLightRecv,LIGHT_COLOR_GRAY);
}

void MainWindow::on_BtnClearRecv_clicked()
{
    ui->textEdit_Recv->clear();
}

void MainWindow::on_BtnStopShow_clicked()
{
    if(m_bStopShow)
    {
        ui->BtnStopShow->setText(tr("停止显示"));
        m_bStopShow =  false;
    }
    else
    {
        ui->BtnStopShow->setText(tr("继续显示"));
        m_bStopShow =  true;
    }
}


void MainWindow::on_checkBox_AutoSend_clicked(bool checked)
{
    if(checked)
    {
        int nInterval = ui->lineEdit_Cycle->text().toInt();
        m_pAutoSendTime->start(nInterval);
    }
    else
    {
        m_pAutoSendTime->stop();
    }
}

void MainWindow::on_BtnClear_clicked()
{
    ui->textEdit_Send->clear();
}
unsigned short MainWindow::CRC16( unsigned char *pBuf,int  nLength)
{
    unsigned short wReturn = 0xFFFF;
    for(int nDataLen=0;nDataLen<nLength;nDataLen++)
    {
        wReturn^=(unsigned short)((unsigned char)(pBuf[nDataLen]));
        for(int nIndex=0;nIndex<8;nIndex++)
        {
            if(wReturn&0x0001)
            {
                wReturn>>=1;
                wReturn^=0xA001;
            }
            else
            {
                wReturn>>=1;
            }
        }
    }
    return wReturn;
}

void MainWindow::on_BtnParity_clicked()
{
    QStringList strList;
    QString strScrData;
    strScrData = ui->textEdit_Send->toPlainText();
    strList = strScrData.split(QChar(' '));

    QByteArray arrData;
    QString strHigh;
    QString strLow;
    bool bOk;
    for(int i = 0;i<strList.length();i++)
    {
        arrData.append(strList.at(i).toInt(&bOk,16));
    }
    unsigned short crc=CRC16((unsigned char *)arrData.data(),arrData.length());

    QString str;
    str.sprintf("%04X",crc);
    strHigh.sprintf("%02X",crc& 0xff);
    strLow.sprintf("%02X",crc>>8);
    strScrData = strScrData+QChar(' ')+strHigh+QChar(' ')+strLow;
    ui->textEdit_Send->setText(strScrData);
}

int MainWindow::getRoung(int iValue, int iBase)
{
    int iFactor, iMod;
    iFactor = iValue / iBase;
    iMod = iValue % iBase;
    iFactor=(iMod*2>iBase)?(iFactor+1):iFactor;
    int iRtn=iFactor*iBase;
    return iRtn;
}
