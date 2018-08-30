#include "mainwindow.h"
#include <QApplication>
#include<QTextCodec>
#include<QtCore>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    //下面几行代码对于支持中文必不可少
      QTextCodec *codec = QTextCodec::codecForName("UTF-8");
      QTextCodec::setCodecForLocale(codec);
      QTextCodec::setCodecForCStrings(codec);
      QTextCodec::setCodecForTr(codec);

    MainWindow w;
    w.show();

    return a.exec();
}
