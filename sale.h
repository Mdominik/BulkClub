#ifndef SALE_H
#define SALE_H
#include "member.h"
#include "item.h"
#include <QFile>
#include <QDate>
class Sale
{
public:
    Sale();
    int getQuantity() const {return m_quantity;}
    int getPrice() const {return m_price;}
    QString getItem() const {return item;}
    int getMember() const {return m_number;}
    QDate getDate() const {return m_date;}
    void setItem(QString it) {item=it;}
    void setPrice(int price) {m_price=price;}
    void setMember(int number) {m_number=number;}
    void setQuantity(int q) {m_quantity=q;}
    void setDate(QDate date) {m_date=date;}



private:
    QDate m_date;
    int m_number;
    QString item;
    int m_price;
    int m_quantity;
};

#endif // SALE_H
