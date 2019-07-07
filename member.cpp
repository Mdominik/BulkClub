#include "member.h"

Member::Member()
{

}

Member::Member(QString name, int no, MembershipType type, QDate date, int total, int rebate):
    m_name{name}, m_number{no}, m_type{type}, m_date{date}, m_totalSpent{total}, m_rebateAmount{rebate}{}

