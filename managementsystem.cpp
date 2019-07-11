#include "managementsystem.h"
static int ccc=0;
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
    for(auto& mem : m_members) {
        if(mem.getType()==1) m_regularMembers.push_back(mem.getNumber());
        else if(mem.getType()==0) m_executiveMembers.push_back(mem.getNumber());
    }
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
            if(counter%LINES_MEMBERS==0) {
                name_buf = QString(line);
                qInfo() << line;
            }
            else if((counter+3)%LINES_MEMBERS==0) {
                number_buf = QString(line).toInt(&encoding, 10);

            }
            else if((counter+2)%LINES_MEMBERS==0) {

                if(line.operator == ("Regular")) {
                    type_buf = MembershipType::Regular;
                }
                if(line.operator == ("Executive")) {
                    type_buf = MembershipType::Executive;
                }
            }
            else if((counter+1)%LINES_MEMBERS==0) {
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
        Item* item;
        int number_buf;
        QDate date_buf;
        QString item_buf;
        QString item_line_buf;
        int item_price_buf;
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

                if(counter % LINES_SALES==0) {
                    QString date_str = QString(line);
                    date_buf = QDate::fromString(date_str,"MM/dd/yyyy");
                }
                else if((counter+3) % LINES_SALES==0) {
                    number_buf = QString(line).toInt(&encoding, 10);

                }
                else if((counter+2) % LINES_SALES==0) {
                    item_buf = QString(line);
                }
                else if((counter+1) % LINES_SALES==0) {

                    QStringList list;
                    list = QString(line).split('\t');
                    item_price_buf = static_cast<int>(QString(list[0]).toFloat()*100);
                    quantity_buf = QString(list[1]).toInt();
                    sale = new Sale;
                    sale->setDate(date_buf);
                    sale->setQuantity(quantity_buf);
                    sale->setMembersID(number_buf);

                    int i = m_allItemsNames.indexOf(item_buf);

                    // create a new item object if it doesn't exist yet
                    if(i==-1) {
                        item = new Item;
                        m_allItemsNames.append(item_buf);
                        item->setName(item_buf);
                        item->setPrice(item_price_buf);

                        m_allItems.push_back(item);
                    }

                    // use an existing item object
                    else {
                        for (int j=0; j < m_allItems.size(); j++) {
                            if(!m_allItems[j]->getName().compare(item_buf)) {
                                item = m_allItems[j];
                            }
                        }
                    }
                    item->setCount(item->getCount()+quantity_buf); //increment amount of items sold
                    sale->setItem(item);
                    m_allSalesOneVec.push_back(*sale);
                    day_vector.push_back(*sale);
                    Member* mem = findMember(number_buf);

                    mem->setTotalSpent(mem->getTotalSpent()+quantity_buf*item_price_buf);

                    //if the current member is executive, add rebate
                    if(m_executiveMembers.contains(number_buf)) {
                        qInfo() << mem->getRebate();
                        mem->setRebate(mem->getRebate()+REBATE_PERCENT*quantity_buf*item_price_buf);
                    }

                }
                counter++;
            }
        }
        else {
            qDebug() << "File doesnt exists";
            return false;
        }
        m_allSales.push_back(day_vector);
}

Member* ManagementSystem::findMember(int id) {
    for(auto &mem : m_members){
        if(mem.getNumber() == id) {
            return &mem;
        }
    }
    qInfo() << "NOT FOUND";
    return nullptr;
}


void ManagementSystem::sortPurchasesByNumber() {
    std::sort(m_allSalesOneVec.begin(), m_allSalesOneVec.end(), [](Sale& a, Sale& b) {
        return a.getMembersID() < b.getMembersID();
    });
    return;
}

//sorting members (true - by id, false - by rebate)
void ManagementSystem::sortMembers(bool is_byID) {
    std::sort(m_members.begin(), m_members.end(), [&is_byID](Member& a, Member& b) {
        return is_byID ? a.getNumber() < b.getNumber() : a.getRebate() > b.getRebate();
    });
}

void ManagementSystem::addMemberToFile(Member& m) {
    QFile file(MEMBERS_FILE);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        QTextStream stream(&file);
        stream << m.getName() << endl;
        stream << m.getNumber() << endl;
        static_cast<bool>(m.getType()) ? stream << "Executive" << endl : stream << "Regular" <<endl;
        stream << m.getDate().toString("dd/MM/yyyy") << endl;
    }
}

void ManagementSystem::deleteMemberFromFile(QString& member_name) {
    QFile file(MEMBERS_FILE);
    QFile file_tmp(TMP_FILE);
    if(file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        file_tmp.resize(0);
        QTextStream stream(&file_tmp);
        while(!stream.atEnd()) {
            stream << file.readLine();
        }
    }

    if(file_tmp.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        int counter = 0;
        while(!stream.atEnd())
        {
            QString line = stream.readLine();
            qInfo() << line;
            if(line.contains(member_name) || counter > 0) {
                counter++;
                if(counter == 4) counter = 0;
                continue;
            } else {
                stream << line;
            }
        }
    }
}
