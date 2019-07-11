#ifndef MEMBER_H
#define MEMBER_H
#include <QDateTime>
enum MembershipType {
    Executive, Regular
};

class Member
{
public:
    Member();
    Member(QString name, int no, MembershipType type, QDate date, int total, int rebate);

    QString getName() const {return m_name;}
    int getNumber() const {return m_number;}
    MembershipType getType() const {return m_type;}
    QDate getDate() const {return m_date;}
    int getTotalSpent() const {return m_totalSpent;}
    int getRebate() const {return m_rebateAmount;}

    void setName(QString name) {m_name = name;}
    void setNumber(int number) {m_number = number;}
    void setType(MembershipType type) {m_type = type;}
    void setDate(QDate date) {m_date = date;}
    void setTotalSpent(int spent) {m_totalSpent = spent;}
    void setRebate(int rebate) {m_rebateAmount = rebate;}



private:
    QString m_name;
    int m_number;
    MembershipType m_type;
    QDate m_date;
    int m_totalSpent=0; //in cents
    int m_rebateAmount=0;

};



#endif // MEMBER_H
