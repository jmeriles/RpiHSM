#ifndef HYBRIDEL_H
#define HYBRIDEL_H

#include <QMainWindow>

namespace Ui {
class HybridEl;
}

class HybridEl : public QMainWindow
{
    Q_OBJECT

public:
    explicit HybridEl(QWidget *parent = nullptr);
    ~HybridEl();

private:
    Ui::HybridEl *ui;
};

#endif // HYBRIDEL_H
