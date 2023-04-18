#include "hsm_full.h"
#include "ui_customelement.h"
std::vector<std::vector<std::vector<double>>> CustomElMatrix;

CustomElement::CustomElement(QWidget *parent) :
    QMainWindow(parent),
    ui4(new Ui::CustomElement)
{
    ui4->setupUi(this);


    connect(ui4->SubmitEl,&QPushButton::released,this,&CustomElement::submitElement);
    connect(ui4->Undo,&QPushButton::released,this,&CustomElement::undoSubmit);
    if (twodthreed == 0){
        ui4->K17->setEnabled(FALSE);
        ui4->K18->setEnabled(FALSE);
        ui4->K19->setEnabled(FALSE);
        ui4->K110->setEnabled(FALSE);
        ui4->K111->setEnabled(FALSE);
        ui4->K112->setEnabled(FALSE);
        ui4->K27->setEnabled(FALSE);
        ui4->K28->setEnabled(FALSE);
        ui4->K29->setEnabled(FALSE);
        ui4->K210->setEnabled(FALSE);
        ui4->K211->setEnabled(FALSE);
        ui4->K212->setEnabled(FALSE);
        ui4->K37->setEnabled(FALSE);
        ui4->K38->setEnabled(FALSE);
        ui4->K39->setEnabled(FALSE);
        ui4->K310->setEnabled(FALSE);
        ui4->K311->setEnabled(FALSE);
        ui4->K312->setEnabled(FALSE);
        ui4->K47->setEnabled(FALSE);
        ui4->K48->setEnabled(FALSE);
        ui4->K49->setEnabled(FALSE);
        ui4->K410->setEnabled(FALSE);
        ui4->K411->setEnabled(FALSE);
        ui4->K412->setEnabled(FALSE);
        ui4->K57->setEnabled(FALSE);
        ui4->K58->setEnabled(FALSE);
        ui4->K59->setEnabled(FALSE);
        ui4->K510->setEnabled(FALSE);
        ui4->K511->setEnabled(FALSE);
        ui4->K512->setEnabled(FALSE);
        ui4->K67->setEnabled(FALSE);
        ui4->K68->setEnabled(FALSE);
        ui4->K69->setEnabled(FALSE);
        ui4->K610->setEnabled(FALSE);
        ui4->K611->setEnabled(FALSE);
        ui4->K612->setEnabled(FALSE);
        ui4->K71->setEnabled(FALSE);
        ui4->K72->setEnabled(FALSE);
        ui4->K73->setEnabled(FALSE);
        ui4->K74->setEnabled(FALSE);
        ui4->K75->setEnabled(FALSE);
        ui4->K76->setEnabled(FALSE);
        ui4->K77->setEnabled(FALSE);
        ui4->K78->setEnabled(FALSE);
        ui4->K79->setEnabled(FALSE);
        ui4->K710->setEnabled(FALSE);
        ui4->K711->setEnabled(FALSE);
        ui4->K712->setEnabled(FALSE);
        ui4->K81->setEnabled(FALSE);
        ui4->K82->setEnabled(FALSE);
        ui4->K83->setEnabled(FALSE);
        ui4->K84->setEnabled(FALSE);
        ui4->K85->setEnabled(FALSE);
        ui4->K86->setEnabled(FALSE);
        ui4->K87->setEnabled(FALSE);
        ui4->K88->setEnabled(FALSE);
        ui4->K89->setEnabled(FALSE);
        ui4->K810->setEnabled(FALSE);
        ui4->K811->setEnabled(FALSE);
        ui4->K812->setEnabled(FALSE);
        ui4->K91->setEnabled(FALSE);
        ui4->K92->setEnabled(FALSE);
        ui4->K93->setEnabled(FALSE);
        ui4->K94->setEnabled(FALSE);
        ui4->K95->setEnabled(FALSE);
        ui4->K96->setEnabled(FALSE);
        ui4->K97->setEnabled(FALSE);
        ui4->K98->setEnabled(FALSE);
        ui4->K99->setEnabled(FALSE);
        ui4->K910->setEnabled(FALSE);
        ui4->K911->setEnabled(FALSE);
        ui4->K912->setEnabled(FALSE);
        ui4->K10_1->setEnabled(FALSE);
        ui4->K10_2->setEnabled(FALSE);
        ui4->K10_3->setEnabled(FALSE);
        ui4->K10_4->setEnabled(FALSE);
        ui4->K10_5->setEnabled(FALSE);
        ui4->K10_6->setEnabled(FALSE);
        ui4->K10_7->setEnabled(FALSE);
        ui4->K10_8->setEnabled(FALSE);
        ui4->K10_9->setEnabled(FALSE);
        ui4->K10_10->setEnabled(FALSE);
        ui4->K10_11->setEnabled(FALSE);
        ui4->K10_12->setEnabled(FALSE);
        ui4->K11_1->setEnabled(FALSE);
        ui4->K11_2->setEnabled(FALSE);
        ui4->K11_3->setEnabled(FALSE);
        ui4->K11_4->setEnabled(FALSE);
        ui4->K11_5->setEnabled(FALSE);
        ui4->K11_6->setEnabled(FALSE);
        ui4->K11_7->setEnabled(FALSE);
        ui4->K11_8->setEnabled(FALSE);
        ui4->K11_9->setEnabled(FALSE);
        ui4->K11_10->setEnabled(FALSE);
        ui4->K11_11->setEnabled(FALSE);
        ui4->K11_12->setEnabled(FALSE);
        ui4->K12_1->setEnabled(FALSE);
        ui4->K12_2->setEnabled(FALSE);
        ui4->K12_3->setEnabled(FALSE);
        ui4->K12_4->setEnabled(FALSE);
        ui4->K12_5->setEnabled(FALSE);
        ui4->K12_6->setEnabled(FALSE);
        ui4->K12_7->setEnabled(FALSE);
        ui4->K12_8->setEnabled(FALSE);
        ui4->K12_9->setEnabled(FALSE);
        ui4->K12_10->setEnabled(FALSE);
        ui4->K12_11->setEnabled(FALSE);
        ui4->K12_12->setEnabled(FALSE);
    }
    }

    void CustomElement::submitElement(){
    if (twodthreed == 0){
    CustomElMatrix.push_back({{ui4->K11->value(),ui4->K12->value(),ui4->K13->value(),ui4->K14->value(),ui4->K15->value(),ui4->K16->value()},
                             {ui4->K21->value(),ui4->K22->value(),ui4->K23->value(),ui4->K24->value(),ui4->K25->value(),ui4->K26->value()},
                             {ui4->K31->value(),ui4->K32->value(),ui4->K33->value(),ui4->K34->value(),ui4->K35->value(),ui4->K36->value()},
                             {ui4->K41->value(),ui4->K42->value(),ui4->K43->value(),ui4->K44->value(),ui4->K45->value(),ui4->K46->value()},
                             {ui4->K51->value(),ui4->K52->value(),ui4->K53->value(),ui4->K54->value(),ui4->K55->value(),ui4->K56->value()},
                             {ui4->K61->value(),ui4->K62->value(),ui4->K63->value(),ui4->K64->value(),ui4->K65->value(),ui4->K66->value()}});

    ui4->textEdit->setText("Success: Close Window");
    ui4->SubmitEl->setEnabled(FALSE);
    }else{
        CustomElMatrix.push_back({{ui4->K11->value(),ui4->K12->value(),ui4->K13->value(),ui4->K14->value(),ui4->K15->value(),ui4->K16->value(),ui4->K17->value(),ui4->K18->value(),ui4->K19->value(),ui4->K110->value(),ui4->K111->value(),ui4->K112->value()},
                                 {ui4->K21->value(),ui4->K22->value(),ui4->K23->value(),ui4->K24->value(),ui4->K25->value(),ui4->K26->value(),ui4->K27->value(),ui4->K28->value(),ui4->K29->value(),ui4->K210->value(),ui4->K211->value(),ui4->K212->value()},
                                 {ui4->K31->value(),ui4->K32->value(),ui4->K33->value(),ui4->K34->value(),ui4->K35->value(),ui4->K36->value(),ui4->K37->value(),ui4->K38->value(),ui4->K39->value(),ui4->K310->value(),ui4->K311->value(),ui4->K312->value()},
                                 {ui4->K41->value(),ui4->K42->value(),ui4->K43->value(),ui4->K44->value(),ui4->K45->value(),ui4->K46->value(),ui4->K47->value(),ui4->K48->value(),ui4->K49->value(),ui4->K410->value(),ui4->K411->value(),ui4->K412->value()},
                                 {ui4->K51->value(),ui4->K52->value(),ui4->K53->value(),ui4->K54->value(),ui4->K55->value(),ui4->K56->value(),ui4->K57->value(),ui4->K58->value(),ui4->K59->value(),ui4->K510->value(),ui4->K511->value(),ui4->K512->value()},
                                 {ui4->K61->value(),ui4->K62->value(),ui4->K63->value(),ui4->K64->value(),ui4->K65->value(),ui4->K66->value(),ui4->K67->value(),ui4->K68->value(),ui4->K69->value(),ui4->K610->value(),ui4->K611->value(),ui4->K612->value()},
                                 {ui4->K71->value(),ui4->K72->value(),ui4->K73->value(),ui4->K74->value(),ui4->K75->value(),ui4->K76->value(),ui4->K77->value(),ui4->K78->value(),ui4->K79->value(),ui4->K710->value(),ui4->K711->value(),ui4->K712->value()},
                                 {ui4->K81->value(),ui4->K82->value(),ui4->K83->value(),ui4->K84->value(),ui4->K85->value(),ui4->K86->value(),ui4->K87->value(),ui4->K88->value(),ui4->K89->value(),ui4->K810->value(),ui4->K811->value(),ui4->K812->value()},
                                 {ui4->K91->value(),ui4->K92->value(),ui4->K93->value(),ui4->K94->value(),ui4->K95->value(),ui4->K96->value(),ui4->K97->value(),ui4->K98->value(),ui4->K99->value(),ui4->K910->value(),ui4->K911->value(),ui4->K912->value()},
                                 {ui4->K10_1->value(),ui4->K10_2->value(),ui4->K10_3->value(),ui4->K10_4->value(),ui4->K10_5->value(),ui4->K10_6->value(),ui4->K10_7->value(),ui4->K10_8->value(),ui4->K10_9->value(),ui4->K10_10->value(),ui4->K10_11->value(),ui4->K10_12->value()},
                                 {ui4->K11_1->value(),ui4->K11_2->value(),ui4->K11_3->value(),ui4->K11_4->value(),ui4->K11_5->value(),ui4->K11_6->value(),ui4->K11_7->value(),ui4->K11_8->value(),ui4->K11_9->value(),ui4->K11_10->value(),ui4->K11_11->value(),ui4->K11_12->value()},
                                 {ui4->K12_1->value(),ui4->K12_2->value(),ui4->K12_3->value(),ui4->K11_4->value(),ui4->K12_5->value(),ui4->K12_6->value(),ui4->K12_7->value(),ui4->K12_8->value(),ui4->K12_9->value(),ui4->K12_10->value(),ui4->K12_11->value(),ui4->K12_12->value()}});

    ui4->textEdit->setText("Success: Close Window");
    ui4->SubmitEl->setEnabled(FALSE);
    }
    ui4->Undo->setEnabled(TRUE);
    }

void CustomElement::undoSubmit(){
    CustomElMatrix.erase(CustomElMatrix.end());
    ui4->textEdit->setText("Submit Revoked");
    ui4->SubmitEl->setEnabled(TRUE);
    ui4->Undo->setEnabled(FALSE);
}
CustomElement::~CustomElement()
{
    delete ui4;
}
