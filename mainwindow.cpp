#include "mainwindow.h"
#include "ui_mainwindow.h"


//nomenclature:
// login window --> the window for login
// management system window --> the main window after login


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->id_input->setPlaceholderText("Your ID");
    ui->psw_input->setPlaceholderText("Your psw");
    manSystem = ManagementSystem();

    //hides management system window
    ui->mainMenu->hide();
    ui->logout->hide();
    ui->admin_man->hide();
    ui->id->hide();
    ui->line->hide();

}

MainWindow::~MainWindow()
{
    delete ui;

}

//button for logging in released. Checks credentials and logs in.
void MainWindow::on_login_btn_released()
{
    bool ok;

    //get data from input
    QString id_text = ui->id_input->text();
    QString psw_text = ui->psw_input->text();

    //check manager's credentials
    if(manSystem.getManager().getLogin() == id_text.toInt(&ok, 10) && !manSystem.getManager().getPsw().compare(psw_text)) {
        qInfo() << "Manager(" << manSystem.getManager().getLogin() << ") just logged in.";
        manSystem.getManager().setLoggedNow(true);
        disappearAfterLogged(false);

    }

    //check admin's credentials
    else if(manSystem.getAdmin().getLogin() == id_text.toInt(&ok, 10) && !manSystem.getAdmin().getPsw().compare(psw_text))  {
        qInfo() << "Admin(" << manSystem.getAdmin().getLogin()<< ") just logged in.";
        manSystem.getAdmin().setLoggedNow(true);
        disappearAfterLogged(true);

    }
}


// hides the elements of the login window and shows the elements of the management system window.
// It also updates the personal data info shown (admin/manager + ID)
void MainWindow::disappearAfterLogged(bool adminLogged) {
    ui->header_label->hide();
    ui->login_form->hide();
    ui->mainMenu->show();
    ui->logout->show();
    ui->admin_man->show();
    ui->id->show();
    ui->line->show();
    if (adminLogged) {
        ui->admin_man->setText("admin");
        qInfo() << manSystem.getAdmin().getLogin();
        ui->id->setText("ID: " + QString::number(manSystem.getAdmin().getLogin()));

        manSystem.setCurrentlyLogged(CurrentlyLogged::admin);
    } else {
        ui->admin_man->setText("manager");
        qInfo() << manSystem.getManager().getLogin();
        ui->id->setText("ID: " + QString::number(manSystem.getManager().getLogin()));

        manSystem.setCurrentlyLogged(CurrentlyLogged::manager);
    }
}

void MainWindow::on_logout_released()
{
    manSystem.setCurrentlyLogged(CurrentlyLogged::noOne);
    manSystem.getAdmin().setLoggedNow(false);
    manSystem.getManager().setLoggedNow(false);
    QApplication::quit();
}
