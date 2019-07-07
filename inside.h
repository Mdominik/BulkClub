#ifndef INSIDE_H
#define INSIDE_H

#include <QDialog>

namespace Ui {
class Inside;
}

class Inside : public QDialog
{
    Q_OBJECT

public:
    explicit Inside(QWidget *parent = 0);
    ~Inside();

private:
    Ui::Inside *ui;
};

#endif // INSIDE_H
