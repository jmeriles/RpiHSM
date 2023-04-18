#ifndef READGM_H
#define READGM_H

#include <QWidget>

namespace Ui {
class ReadGM;
}

class ReadGM : public QWidget
{
    Q_OBJECT

public:
    explicit ReadGM(QWidget *parent = nullptr);
    ~ReadGM();

private:
    Ui::ReadGM *ui;
};

#endif // READGM_H
