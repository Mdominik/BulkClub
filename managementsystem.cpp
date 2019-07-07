#include "managementsystem.h"

ManagementSystem::ManagementSystem()
{
    initializeUsers();
    retrieveCredentials();
}
void ManagementSystem::initializeUsers() {
    manager = User(false, 0, "");
    admin = User(true, 0, "");
}

bool ManagementSystem::retrieveCredentials() {
    int counter=0;
    QFile credentials_file("/home/dominik/projects/study/BulkClub/BulkClub/login.txt");
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
