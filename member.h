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
    Member(QString name, int no, MembershipType type, QDateTime date, int total, int rebate):
        m_name{name}, m_number{no}, m_type{type}, m_date{date}, m_totalSpent{total}, m_rebateAmount{rebate}{}

    QString getName() const {return m_name;}
    int getNumber() const {return m_number;}
    MembershipType getType() const {return m_type;}
    QDateTime getDate() const {return m_date;}
    int getTotalSpent() const {return m_totalSpent;}
    int getRebate() const {return m_rebateAmount;}

    void setName(QString name) {m_name = name;}
    void setNumber(int number) {m_number = number;}
    void setType(MembershipType type) {m_type = type;}
    void setDate(QDateTime date) {m_date = date;}
    void setTotalSpent(int spent) {m_totalSpent = spent;}
    void setRebate(int rebate) {m_rebateAmount = rebate;}

    bool populateMembersData();

private:
    QString m_name;
    int m_number;
    MembershipType m_type;
    QDateTime m_date;
    int m_totalSpent; //in cents
    int m_rebateAmount; //in percent
};

#endif // MEMBER_H
