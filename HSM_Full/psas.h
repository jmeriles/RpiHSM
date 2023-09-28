#ifndef PSAS_H
#define PSAS_H

#include <QMainWindow>

namespace Ui {
class PSAS;
}

class PSAS : public QMainWindow
{
    Q_OBJECT

public:
    explicit PSAS(QWidget *parent = nullptr);
    ~PSAS();

public slots:
    void add_Node_to_Model();
    void remove_Node_from_Model();
    void add_Element_to_Model();
    void remove_Element_from_Model();
    void add_el_props();
    void add_BCs();
    void add_el_load();
    void add_node_load();

private:
    Ui::PSAS *ui2;
};



#endif // PSAS_H
