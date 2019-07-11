#ifndef SALE_H
#define SALE_H
#include "member.h"
#include "item.h"
#include <QFile>
#include <QDate>
const float REBATE_PERCENT = 0.03;

class Sale
{
public:
    Sale();
    int getQuantity() const {return m_quantity;}

    int getMembersID() const {return m_number;}
    QDate getDate() const {return m_date;}
    Item* getItem() {return m_item;}
    void setMembersID(int number) {m_number=number;}
    void setQuantity(int q) {m_quantity=q;}
    void setDate(QDate date) {m_date=date;}
    int getPriceBeforeTax() const {return m_item->getPrice()*(1-sales_tax);}
    void setItem(Item* it) {m_item=it;}

private:
    QDate m_date;
    int m_number;
    Item* m_item;
    int m_quantity;
    static int sales_tax;
};

#endif // SALE_H
