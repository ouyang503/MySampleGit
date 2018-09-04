#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cprocess_lua.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_BtnExceLua_clicked();

    void on_BtnExceLua_2_clicked();

private:
    Ui::MainWindow *ui;
    CProcess_LUA m_lua;
};

#endif // MAINWINDOW_H
