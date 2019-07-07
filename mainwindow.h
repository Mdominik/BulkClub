#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <iostream>
#include <QDebug>
#include "managementsystem.h"
#include "inside.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setFrontEnd();
    void disappearAfterLogged(bool adminLogged);
private slots:
    void on_login_btn_released();

    void on_logout_released();

private:
    Ui::MainWindow *ui;
    ManagementSystem manSystem;
    Inside* inside;
    QWidget personalData;
};

#endif // MAINWINDOW_H
