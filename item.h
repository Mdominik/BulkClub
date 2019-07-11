#ifndef ITEM_H
#define ITEM_H
#include <QString>


class Item
{
public:
    Item();
    int getPrice() const {return m_price;}
    QString getName() const {
        return m_name;
    }
    void setName(QString it) {m_name=it;}
    void setPrice(int price) {m_price=price;}
    int getCount() const {return count;}
    void setCount(int c) {count = c;}
private:
    QString m_name;
    int m_price;
    int count=0;
};

#endif // ITEM_H
