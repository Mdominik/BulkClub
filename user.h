#ifndef USER_H
#define USER_H
#include <QString>

class User
{
public:
    User();
    User(bool _admin, int _login, QString _psw);
    bool m_isAdmin; //if true -> admin, if false -> store manager
    int m_loginID;
    QString m_password;
    bool m_loggedNow;

};

#endif // USER_H
