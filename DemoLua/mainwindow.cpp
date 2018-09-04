#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_BtnExceLua_clicked()
{

   ui->lineEdit->setText(m_lua.getLog());
}

void MainWindow::on_BtnExceLua_2_clicked()
{
   m_lua.setLog(ui->lineEdit_2->text());
}
