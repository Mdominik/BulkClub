#ifndef MANAGEMENTSYSTEM_H
#define MANAGEMENTSYSTEM_H

#include "user.h"
#include <QFile>
#include <QDebug>
#define CREDENTIALS_FILE "login.txt"
#define DAY1_FILE "resources/day1.txt"
#define DAY2_FILE "resources/day2.txt"
#define DAY3_FILE "resources/day3.txt"
#define DAY4_FILE "resources/day4.txt"
#define DAY5_FILE "resources/day5.txt"
#define DAY6_FILE "resources/day6.txt"
#define DAY7_FILE "resources/day7.txt"

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
    CurrentlyLogged getCurrentlyLogged() const { return logged;}
    void setCurrentlyLogged(CurrentlyLogged log) {logged=log;}
private:
    User admin;
    User manager;

    CurrentlyLogged logged; //0=no one, 1=admin, 2=manager
};

#endif // MANAGEMENTSYSTEM_H
