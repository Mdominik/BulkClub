#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
#include <iostream>
#include <QDebug>
#include <ctime>
#include "managementsystem.h"
#include "inside.h"
#include "sale.h"
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
    void on_display_btn_released();

    void on_display_btn_2_released();

    void on_display_btn_3_released();

    void on_btn_searchByItemsName_released();

    void on_display_btn_4_released();

    void on_filter_btn_released();

    void on_addDelete_btn_pressed();

    void on_addDelete_btn_released();

    void on_addDelete_combo_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    ManagementSystem manSystem;
    Inside* inside;
    QWidget personalData;
};

#endif // MAINWINDOW_H
