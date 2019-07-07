#include "user.h"
User::User(){}

User::User(bool _admin, int _login, QString _psw) : m_isAdmin{_admin}, m_loginID{_login}, m_password{_psw}
{
    m_loggedNow = false;
}

