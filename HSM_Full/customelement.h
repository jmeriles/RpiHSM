#ifndef CUSTOMELEMENT_H
#define CUSTOMELEMENT_H

#include <QMainWindow>

namespace Ui {
class CustomElement;
}

class CustomElement : public QMainWindow
{
    Q_OBJECT

public:
    explicit CustomElement(QWidget *parent = nullptr);
    ~CustomElement();

private:
    Ui::CustomElement *ui;
};

#endif // CUSTOMELEMENT_H
