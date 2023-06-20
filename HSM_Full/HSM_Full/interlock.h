#ifndef INTERLOCK_H
#define INTERLOCK_H

#include <QWidget>

namespace Ui {
class Interlock;
}

class Interlock : public QWidget
{
    Q_OBJECT

public:
    explicit Interlock(QWidget *parent = nullptr);
    ~Interlock();

private:
    Ui::Interlock *ui;
};

#endif // INTERLOCK_H
