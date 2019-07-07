#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->id_input->setPlaceholderText("Your ID");
    ui->psw_input->setPlaceholderText("Your psw");
    initializeUsers();
    retrieveCredentials();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::initializeUsers() {
    manager = User(false, 0, "");
    admin = User(true, 0, "");
}

bool MainWindow::retrieveCredentials() {
    int counter=0;
    QFile credentials_file("/home/dominik/projects/study/BulkClub/BulkClub/login.txt");
    if(credentials_file.exists()){
        if (!credentials_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << manager.m_loginID;
            return false;
        }
        while (!credentials_file.atEnd()) {
            bool encoding;
            QByteArray line = credentials_file.readLine();
            line = line.trimmed();
            if(counter==0) manager.m_loginID = QString(line).toInt(&encoding, 10);
            if(counter==1) manager.m_password = QString(line);
            if(counter==2) admin.m_loginID = QString(line).toInt(&encoding, 10);
            if(counter==3) admin.m_password = QString(line);
            counter++;
        }
        return true;
    }
    else {
        qDebug() << "File doesnt exists";
        return false;
    }
}

void MainWindow::on_login_btn_released()
{
    bool ok;
    QString id_text = ui->id_input->text();
    QString psw_text = ui->psw_input->text();

    //check manager's credentials
    if(manager.m_loginID == id_text.toInt(&ok, 10) && !manager.m_password.compare(psw_text)) {
        qInfo() << "Manager(" << manager.m_loginID << ") just logged in.";
        manager.m_loggedNow = true;
    }

    //check admin's credentials
    else if(admin.m_loginID == id_text.toInt(&ok, 10) && !admin.m_password.compare(psw_text)) {
        qInfo() << "Admin(" << admin.m_loginID << ") just logged in.";
        admin.m_loggedNow = true;
    }
}
