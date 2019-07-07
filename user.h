#ifndef USER_H
#define USER_H
#include <QString>

class User
{
public:
    User();
    User(bool _admin, int _login, QString _psw);
    void setIsAdmin(bool is) {m_isAdmin = is;}
    void setLogin(int login) {m_loginID = login;}
    void setPsw(QString psw) {m_password = psw;}
    void setLoggedNow(bool logged) {m_loggedNow = logged;}

    bool getIsAdmin() const {return m_isAdmin;}
    int getLogin() const {return m_loginID;}
    QString getPsw() const {return m_password;}
    bool getLoggedNow() const {return m_loggedNow;}
private:
    bool m_isAdmin; //if true -> admin, if false -> store manager
    int m_loginID;
    QString m_password;
    bool m_loggedNow;

};

#endif // USER_H
