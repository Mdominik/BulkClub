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
        ui->id->setText("ID: " + QString::number(manSystem.getAdmin().getLogin()));
        manSystem.setCurrentlyLogged(CurrentlyLogged::admin);
    } else {
        ui->admin_man->setText("manager");
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

void MainWindow::on_display_btn_released()
{
    ui->display->clear();
    float priceSum=0;

    int sum_exec = 0;
    int sum_regular = 0;
    for(auto& sale: manSystem.getSales()[ui->weekdayBox->currentIndex()]) {
        if(ui->showExec->checkState()) {
            int i = manSystem.getExecutiveMembers().indexOf(sale.getMember());
            if(i!=-1) {
                ui->display->append(sale.getDate().toString());
                ui->display->append(QString::number(sale.getMember()));
                ui->display->append(sale.getItem());
                ui->display->append(QString::number(sale.getPrice()));
                ui->display->append(QString::number(sale.getQuantity()));
                ui->display->append("\n");
                priceSum = priceSum + sale.getPrice()*sale.getQuantity();
                sum_exec++;
            }
        }
        if(ui->showRegular->checkState()) {
            int i = manSystem.getRegularMembers().indexOf(sale.getMember());
            if(i!=-1) {
                ui->display->append(sale.getDate().toString());
                ui->display->append(QString::number(sale.getMember()));
                ui->display->append(sale.getItem());
                ui->display->append(QString::number(sale.getPrice()));
                ui->display->append(QString::number(sale.getQuantity()));
                ui->display->append("\n");
                priceSum = priceSum + sale.getPrice()*sale.getQuantity();
                sum_regular++;
            }
        }
    }
    ui->revenue->setText("$"+QString::number(priceSum));
    ui->numberExec->setText(QString::number(sum_exec));
    ui->numberRegular->setText(QString::number(sum_regular));
}

void MainWindow::on_display_btn_2_released()
{
    manSystem.sortPurchasesByNumber();
    ui->display_2->clear();
    float sum=0;
    for(auto& sale: manSystem.getAllSalesOneVec()) {
        ui->display_2->append(sale.getDate().toString());
        ui->display_2->append(QString::number(sale.getMember()));
        ui->display_2->append(sale.getItem());
        ui->display_2->append(QString::number(sale.getPrice()));
        ui->display_2->append(QString::number(sale.getQuantity()));
        ui->display_2->append("\n");
        sum += sale.getPrice()*sale.getQuantity();
    }
    ui->grandTotal->setText("$" + QString::number(sum));
}


