#include "hsm_full.h"
#include "ui_hybridel.h"
#include <QPushButton>
#include <QTextEdit>

std::vector<std::vector<std::vector<double>>> HybridElMatrix;
std::vector<std::vector<int>> HybridElControl;


HybridEl::HybridEl(QWidget *parent) :
    QMainWindow(parent),
    ui3(new Ui::HybridEl)
{
    ui3->setupUi(this);
    connect(ui3->SubmitEl,&QPushButton::released,this,&HybridEl::submitElement);
    connect(ui3->Undo,&QPushButton::released,this,&HybridEl::undoSubmit);
    if (twodthreed == 0){
        ui3->K17->setEnabled(FALSE);
        ui3->K18->setEnabled(FALSE);
        ui3->K19->setEnabled(FALSE);
        ui3->K110->setEnabled(FALSE);
        ui3->K111->setEnabled(FALSE);
        ui3->K112->setEnabled(FALSE);
        ui3->K27->setEnabled(FALSE);
        ui3->K28->setEnabled(FALSE);
        ui3->K29->setEnabled(FALSE);
        ui3->K210->setEnabled(FALSE);
        ui3->K211->setEnabled(FALSE);
        ui3->K212->setEnabled(FALSE);
        ui3->K37->setEnabled(FALSE);
        ui3->K38->setEnabled(FALSE);
        ui3->K39->setEnabled(FALSE);
        ui3->K310->setEnabled(FALSE);
        ui3->K311->setEnabled(FALSE);
        ui3->K312->setEnabled(FALSE);
        ui3->K47->setEnabled(FALSE);
        ui3->K48->setEnabled(FALSE);
        ui3->K49->setEnabled(FALSE);
        ui3->K410->setEnabled(FALSE);
        ui3->K411->setEnabled(FALSE);
        ui3->K412->setEnabled(FALSE);
        ui3->K57->setEnabled(FALSE);
        ui3->K58->setEnabled(FALSE);
        ui3->K59->setEnabled(FALSE);
        ui3->K510->setEnabled(FALSE);
        ui3->K511->setEnabled(FALSE);
        ui3->K512->setEnabled(FALSE);
        ui3->K67->setEnabled(FALSE);
        ui3->K68->setEnabled(FALSE);
        ui3->K69->setEnabled(FALSE);
        ui3->K610->setEnabled(FALSE);
        ui3->K611->setEnabled(FALSE);
        ui3->K612->setEnabled(FALSE);
        ui3->K71->setEnabled(FALSE);
        ui3->K72->setEnabled(FALSE);
        ui3->K73->setEnabled(FALSE);
        ui3->K74->setEnabled(FALSE);
        ui3->K75->setEnabled(FALSE);
        ui3->K76->setEnabled(FALSE);
        ui3->K77->setEnabled(FALSE);
        ui3->K78->setEnabled(FALSE);
        ui3->K79->setEnabled(FALSE);
        ui3->K710->setEnabled(FALSE);
        ui3->K711->setEnabled(FALSE);
        ui3->K712->setEnabled(FALSE);
        ui3->K81->setEnabled(FALSE);
        ui3->K82->setEnabled(FALSE);
        ui3->K83->setEnabled(FALSE);
        ui3->K84->setEnabled(FALSE);
        ui3->K85->setEnabled(FALSE);
        ui3->K86->setEnabled(FALSE);
        ui3->K87->setEnabled(FALSE);
        ui3->K88->setEnabled(FALSE);
        ui3->K89->setEnabled(FALSE);
        ui3->K810->setEnabled(FALSE);
        ui3->K811->setEnabled(FALSE);
        ui3->K812->setEnabled(FALSE);
        ui3->K91->setEnabled(FALSE);
        ui3->K92->setEnabled(FALSE);
        ui3->K93->setEnabled(FALSE);
        ui3->K94->setEnabled(FALSE);
        ui3->K95->setEnabled(FALSE);
        ui3->K96->setEnabled(FALSE);
        ui3->K97->setEnabled(FALSE);
        ui3->K98->setEnabled(FALSE);
        ui3->K99->setEnabled(FALSE);
        ui3->K910->setEnabled(FALSE);
        ui3->K911->setEnabled(FALSE);
        ui3->K912->setEnabled(FALSE);
        ui3->K10_1->setEnabled(FALSE);
        ui3->K10_2->setEnabled(FALSE);
        ui3->K10_3->setEnabled(FALSE);
        ui3->K10_4->setEnabled(FALSE);
        ui3->K10_5->setEnabled(FALSE);
        ui3->K10_6->setEnabled(FALSE);
        ui3->K10_7->setEnabled(FALSE);
        ui3->K10_8->setEnabled(FALSE);
        ui3->K10_9->setEnabled(FALSE);
        ui3->K10_10->setEnabled(FALSE);
        ui3->K10_11->setEnabled(FALSE);
        ui3->K10_12->setEnabled(FALSE);
        ui3->K11_1->setEnabled(FALSE);
        ui3->K11_2->setEnabled(FALSE);
        ui3->K11_3->setEnabled(FALSE);
        ui3->K11_4->setEnabled(FALSE);
        ui3->K11_5->setEnabled(FALSE);
        ui3->K11_6->setEnabled(FALSE);
        ui3->K11_7->setEnabled(FALSE);
        ui3->K11_8->setEnabled(FALSE);
        ui3->K11_9->setEnabled(FALSE);
        ui3->K11_10->setEnabled(FALSE);
        ui3->K11_11->setEnabled(FALSE);
        ui3->K11_12->setEnabled(FALSE);
        ui3->K12_1->setEnabled(FALSE);
        ui3->K12_2->setEnabled(FALSE);
        ui3->K12_3->setEnabled(FALSE);
        ui3->K12_4->setEnabled(FALSE);
        ui3->K12_5->setEnabled(FALSE);
        ui3->K12_6->setEnabled(FALSE);
        ui3->K12_7->setEnabled(FALSE);
        ui3->K12_8->setEnabled(FALSE);
        ui3->K12_9->setEnabled(FALSE);
        ui3->K12_10->setEnabled(FALSE);
        ui3->K12_11->setEnabled(FALSE);
        ui3->K12_12->setEnabled(FALSE);
        ui3->DOF7->setEnabled(FALSE);
        ui3->DOF8->setEnabled(FALSE);
        ui3->DOF9->setEnabled(FALSE);
        ui3->DOF10->setEnabled(FALSE);
        ui3->DOF11->setEnabled(FALSE);
        ui3->DOF12->setEnabled(FALSE);
}
}

void HybridEl::submitElement(){
    if (twodthreed == 0){
    HybridElMatrix.push_back({{ui3->K11->value(),ui3->K12->value(),ui3->K13->value(),ui3->K14->value(),ui3->K15->value(),ui3->K16->value()},
                             {ui3->K21->value(),ui3->K22->value(),ui3->K23->value(),ui3->K24->value(),ui3->K25->value(),ui3->K26->value()},
                             {ui3->K31->value(),ui3->K32->value(),ui3->K33->value(),ui3->K34->value(),ui3->K35->value(),ui3->K36->value()},
                             {ui3->K41->value(),ui3->K42->value(),ui3->K43->value(),ui3->K44->value(),ui3->K45->value(),ui3->K46->value()},
                             {ui3->K51->value(),ui3->K52->value(),ui3->K53->value(),ui3->K54->value(),ui3->K55->value(),ui3->K56->value()},
                             {ui3->K61->value(),ui3->K62->value(),ui3->K63->value(),ui3->K64->value(),ui3->K65->value(),ui3->K66->value()}});
    HybridElControl.push_back({ui3->DOF1->value(),ui3->DOF2->value(),ui3->DOF3->value(),ui3->DOF4->value(),ui3->DOF5->value(),ui3->DOF6->value()});
    ui3->textEdit->setText("Success: Close Window");
    ui3->SubmitEl->setEnabled(FALSE);
    }else{
        HybridElMatrix.push_back({{ui3->K11->value(),ui3->K12->value(),ui3->K13->value(),ui3->K14->value(),ui3->K15->value(),ui3->K16->value(),ui3->K17->value(),ui3->K18->value(),ui3->K19->value(),ui3->K110->value(),ui3->K111->value(),ui3->K112->value()},
                                 {ui3->K21->value(),ui3->K22->value(),ui3->K23->value(),ui3->K24->value(),ui3->K25->value(),ui3->K26->value(),ui3->K27->value(),ui3->K28->value(),ui3->K29->value(),ui3->K210->value(),ui3->K211->value(),ui3->K212->value()},
                                 {ui3->K31->value(),ui3->K32->value(),ui3->K33->value(),ui3->K34->value(),ui3->K35->value(),ui3->K36->value(),ui3->K37->value(),ui3->K38->value(),ui3->K39->value(),ui3->K310->value(),ui3->K311->value(),ui3->K312->value()},
                                 {ui3->K41->value(),ui3->K42->value(),ui3->K43->value(),ui3->K44->value(),ui3->K45->value(),ui3->K46->value(),ui3->K47->value(),ui3->K48->value(),ui3->K49->value(),ui3->K410->value(),ui3->K411->value(),ui3->K412->value()},
                                 {ui3->K51->value(),ui3->K52->value(),ui3->K53->value(),ui3->K54->value(),ui3->K55->value(),ui3->K56->value(),ui3->K57->value(),ui3->K58->value(),ui3->K59->value(),ui3->K510->value(),ui3->K511->value(),ui3->K512->value()},
                                 {ui3->K61->value(),ui3->K62->value(),ui3->K63->value(),ui3->K64->value(),ui3->K65->value(),ui3->K66->value(),ui3->K67->value(),ui3->K68->value(),ui3->K69->value(),ui3->K610->value(),ui3->K611->value(),ui3->K612->value()},
                                 {ui3->K71->value(),ui3->K72->value(),ui3->K73->value(),ui3->K74->value(),ui3->K75->value(),ui3->K76->value(),ui3->K77->value(),ui3->K78->value(),ui3->K79->value(),ui3->K710->value(),ui3->K711->value(),ui3->K712->value()},
                                 {ui3->K81->value(),ui3->K82->value(),ui3->K83->value(),ui3->K84->value(),ui3->K85->value(),ui3->K86->value(),ui3->K87->value(),ui3->K88->value(),ui3->K89->value(),ui3->K810->value(),ui3->K811->value(),ui3->K812->value()},
                                 {ui3->K91->value(),ui3->K92->value(),ui3->K93->value(),ui3->K94->value(),ui3->K95->value(),ui3->K96->value(),ui3->K97->value(),ui3->K98->value(),ui3->K99->value(),ui3->K910->value(),ui3->K911->value(),ui3->K912->value()},
                                 {ui3->K10_1->value(),ui3->K10_2->value(),ui3->K10_3->value(),ui3->K10_4->value(),ui3->K10_5->value(),ui3->K10_6->value(),ui3->K10_7->value(),ui3->K10_8->value(),ui3->K10_9->value(),ui3->K10_10->value(),ui3->K10_11->value(),ui3->K10_12->value()},
                                 {ui3->K11_1->value(),ui3->K11_2->value(),ui3->K11_3->value(),ui3->K11_4->value(),ui3->K11_5->value(),ui3->K11_6->value(),ui3->K11_7->value(),ui3->K11_8->value(),ui3->K11_9->value(),ui3->K11_10->value(),ui3->K11_11->value(),ui3->K11_12->value()},
                                 {ui3->K12_1->value(),ui3->K12_2->value(),ui3->K12_3->value(),ui3->K11_4->value(),ui3->K12_5->value(),ui3->K12_6->value(),ui3->K12_7->value(),ui3->K12_8->value(),ui3->K12_9->value(),ui3->K12_10->value(),ui3->K12_11->value(),ui3->K12_12->value()}});
    HybridElControl.push_back({ui3->DOF1->value(),ui3->DOF2->value(),ui3->DOF3->value(),ui3->DOF4->value(),ui3->DOF5->value(),ui3->DOF6->value(),ui3->DOF7->value(),ui3->DOF8->value(),ui3->DOF9->value(),ui3->DOF10->value(),ui3->DOF11->value(),ui3->DOF12->value()});
    ui3->textEdit->setText("Success: Close Window");
    ui3->SubmitEl->setEnabled(FALSE);
    }
    ui3->Undo->setEnabled(TRUE);
}

void HybridEl::undoSubmit(){
    HybridElMatrix.erase(HybridElMatrix.end());
    HybridElControl.erase(HybridElControl.end());
    ui3->textEdit->setText("Submit Revoked");
    ui3->SubmitEl->setEnabled(TRUE);
    ui3->Undo->setEnabled(FALSE);
}
HybridEl::~HybridEl()
{
    delete ui3;
}
