#ifndef MANAGEMENTSYSTEM_H
#define MANAGEMENTSYSTEM_H

#include "user.h"
#include "member.h"
#include "item.h"
#include "sale.h"
#include <QFile>
#include <QDebug>
#include <QVector>
#define CREDENTIALS_FILE "/home/dominik/projects/study/BulkClub/BulkClub/login.txt"
#define DAY1_FILE "/home/dominik/projects/study/BulkClub/BulkClub/resources/day1.txt"
#define DAY2_FILE "/home/dominik/projects/study/BulkClub/BulkClub/resources/day2.txt"
#define DAY3_FILE "/home/dominik/projects/study/BulkClub/BulkClub/resources/day3.txt"
#define DAY4_FILE "/home/dominik/projects/study/BulkClub/BulkClub/resources/day4.txt"
#define DAY5_FILE "/home/dominik/projects/study/BulkClub/BulkClub/resources/day5.txt"
#define DAY6_FILE "/home/dominik/projects/study/BulkClub/BulkClub/resources/day6.txt"
#define DAY7_FILE "/home/dominik/projects/study/BulkClub/BulkClub/resources/day7.txt"
#define MEMBERS_FILE "/home/dominik/projects/study/BulkClub/BulkClub/resources/warehouse shoppers.txt"


enum CurrentlyLogged {
    noOne, admin, manager
};

class ManagementSystem
{
public:
    ManagementSystem();
    void initializeUsers();
    bool retrieveCredentials();
    User getAdmin() const {return admin;}
    User getManager() const {return manager;}
    QVector<QVector<Sale>> getSales() const {return m_allSales;}
    QVector<Member> getMembers() const {return m_members;}
    CurrentlyLogged getCurrentlyLogged() const { return logged;}
    void setCurrentlyLogged(CurrentlyLogged log) {logged=log;}
    void setMembers(QVector<Member>& mem) {m_members=mem;}
    bool populateMembersData(QFile& file);
    bool populateDaySales(QFile* file);

private:
    User admin;
    User manager;
    QVector<Member> m_members;
    CurrentlyLogged logged;
    QVector<QVector<Sale>> m_allSales;//0=no one, 1=admin, 2=manager
    QFile* m_salesFiles[7];
};



#endif // MANAGEMENTSYSTEM_H
