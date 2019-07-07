#include "managementsystem.h"

ManagementSystem::ManagementSystem()
{
    QFile file(MEMBERS_FILE);
    m_salesFiles[0] = new QFile (DAY1_FILE);
    m_salesFiles[1] = new QFile (DAY2_FILE);
    m_salesFiles[2] = new QFile (DAY3_FILE);
    m_salesFiles[3] = new QFile (DAY4_FILE);
    m_salesFiles[4] = new QFile (DAY5_FILE);
    m_salesFiles[5] = new QFile (DAY6_FILE);
    m_salesFiles[6] = new QFile (DAY7_FILE);
    initializeUsers();
    retrieveCredentials();
    populateMembersData(file);
    for(QFile* f : m_salesFiles) {

        populateDaySales(f);

    }
}
void ManagementSystem::initializeUsers() {
    manager = User(false, 0, "");
    admin = User(true, 0, "");
}

bool ManagementSystem::retrieveCredentials() {
    int counter=0;
    QFile credentials_file(CREDENTIALS_FILE);
    if(credentials_file.exists()){
        if (!credentials_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << manager.getLogin();
            return false;
        }
        while (!credentials_file.atEnd()) {
            bool encoding;
            QByteArray line = credentials_file.readLine();
            line = line.trimmed();
            if(counter==0) manager.setLogin(QString(line).toInt(&encoding, 10));
            if(counter==1) manager.setPsw(QString(line));
            if(counter==2) admin.setLogin(QString(line).toInt(&encoding, 10));
            if(counter==3) admin.setPsw(QString(line));
            counter++;
        }
        return true;
    }
    else {
        qDebug() << "File doesnt exists";
        return false;
    }
}



bool ManagementSystem::populateMembersData(QFile& file){
    Member* mem;
    MembershipType type;
    QString name_buf;
    int number_buf;
    MembershipType type_buf;
    QDate date_buf;

    int counter=0;
    if(file.exists()){
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qInfo() << "STH WENT WRONG";
            return false;
        }
        while (!file.atEnd()) {

            bool encoding;
            QByteArray line = file.readLine();
            line = line.trimmed();
            if(counter%4==0) {
                name_buf = QString(line);
            }
            else if((counter+3)%4==0) {
                number_buf = QString(line).toInt(&encoding, 10);

            }
            else if((counter+2)%4==0) {
                if(line.operator == ("Regular")) {
                    type_buf = MembershipType::Regular;
                }
                if(line.operator == ("Executive")) {
                    type_buf = MembershipType::Executive;
                }

            }
            else if((counter+1)%4==0) {
                QString date_str = QString(line);
                date_buf = QDate::fromString(date_str,"MM/dd/yyyy");

                mem = new Member;
                mem->setDate(date_buf);
                mem->setName(name_buf);
                mem->setNumber(number_buf);
                mem->setType(type_buf);
                m_members.push_back(*mem);
                delete mem;
            }
            counter++;
        }
    }
    else {
        qDebug() << "File doesnt exists";
        return false;
    }
}

bool ManagementSystem::populateDaySales(QFile* file) {
        QVector<Sale> day_vector;
        int lines_number=4;
        Sale* sale;
        int number_buf;
        QDate date_buf;
        QString item_buf;
        QString item_line_buf;
        float item_price_buf;
        int quantity_buf;
        int counter=0;
        if(file->exists()){
            if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug() << "Populate Day sales doesnt work";
                return false;
            }
            while (!file->atEnd()) {

                bool encoding;
                QByteArray line = file->readLine();
                line = line.trimmed();

                if(counter % lines_number==0) {
                    QString date_str = QString(line);
                    date_buf = QDate::fromString(date_str,"MM/dd/yyyy");
                }
                else if((counter+3) % lines_number==0) {
                    number_buf = QString(line).toInt(&encoding, 10);
                }
                else if((counter+2) % lines_number==0) {

                    item_buf = QString(line);

                }
                else if((counter+1) % lines_number==0) {

                    QStringList list;
                    list = QString(line).split('\t');
                    qDebug() << list.size();
                    item_price_buf = QString(list[0]).toFloat();
                    quantity_buf = QString(list[1]).toInt();
                    sale = new Sale;
                    sale->setDate(date_buf);
                    sale->setItem(item_buf);
                    sale->setMember(number_buf);
                    sale->setPrice(item_price_buf);
                    sale->setQuantity(quantity_buf);
                    day_vector.push_back(*sale);
                    delete sale;
                }
                m_allSales.push_back(day_vector);
                counter++;
            }
        }
        else {
            qDebug() << "File doesnt exists";
            return false;
        }
}
