#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <iostream>
#include <QDebug>
#include "user.h"

#define CREDENTIALS_FILE "login.txt"
#define DAY1_FILE "resources/day1.txt"
#define DAY2_FILE "resources/day2.txt"
#define DAY3_FILE "resources/day3.txt"
#define DAY4_FILE "resources/day4.txt"
#define DAY5_FILE "resources/day5.txt"
#define DAY6_FILE "resources/day6.txt"
#define DAY7_FILE "resources/day7.txt"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initializeUsers();
    bool retrieveCredentials();
private slots:
    void on_login_btn_released();

private:
    Ui::MainWindow *ui;
    User admin;
    User manager;
};

#endif // MAINWINDOW_H
