#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include"QtCore"
#include"QtGui"
#include <QMainWindow>
#include"SerialPort/qextserialport.h"

namespace Ui {
class MainWindow;
}
class QtCore;

#define LIGHT_COLOR_RED   0
#define LIGHT_COLOR_GREEN 1
#define LIGHT_COLOR_GRAY 2

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    bool m_bStopShow;
    QTimer * m_pReadTimer;
    QTimer * m_pAutoSendTime;
    QextSerialPort *myCom;
    void InitComInfo();
    void GetPortNameFrmUI(QString & strPortName);
    void GetPortSettingsFrmUI(PortSettings & stuPortSettings);
    void SetLightState( QPushButton * pBtn,int nState);

    void SendData();
    unsigned short CRC16(unsigned char *pBuf,int nLength);
    int getRoung(int iValue, int iBase);
private slots:
    void RestoreSendLight();
    void RestoreRecvLight();
    void readMyCom();
    void autoSendData();
    void on_BtnSend_1_clicked();

    void on_BtnOpenCOM_clicked();

    void on_BtnClearRecv_clicked();

    void on_BtnStopShow_clicked();


    void on_checkBox_AutoSend_clicked(bool checked);

    void on_BtnClear_clicked();

    void on_BtnParity_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
