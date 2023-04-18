//#include "psas.h"

#include "hsm_full.h"
#include "ui_psas.h"
#include <QPushButton>
#include <QTextEdit>
#include <iostream>
#include<dirent.h>

std::string GMname;
std::ifstream GMlocation;



std::vector<std::vector<double> > NODE;
std::vector<std::vector<int> > CON;
std::vector<std::vector<double> > el_prop;
std::vector<std::vector<double>> el_load;
std::vector<std::vector<double>> node_load;
std::vector<std::vector<int>> BC;
std::vector<int> Props;
std::vector<std::vector<double>> RelMat;

PyObject *ModelSetupName, *ModelSetupMethod, *ModelSetupFunc, *Model, *el;
PyObject *SetupArgs, *SetupOut;
PyObject *PlotModelName, *PlotModelMethod, *PlotModelFunc;
PyObject *PlotArgs, *PlotOut;
PyObject *GMName, *GMMethod, *GMFunc;
PyObject *GMArgs, *GMOut, *PyGM, *PyDyn;
int twodthreed=0;
int sw = 0;
std::vector<double> GM;
double GMdata;
std::vector<double> DynamicParams;



int count3 = 0;

PSAS::PSAS(QWidget *parent) :
    QMainWindow(parent),
    ui2(new Ui::PSAS)
{
    ui2->setupUi(this);
    ui2->textEdit->setText("Hello, world!");
    ui2->DimText->setText("2D");
    ui2->plainTextEdit->setPlainText("Type GM file Here");


    connect(ui2->add_node,&QPushButton::released,this,&PSAS::add_Node_to_Model);
    connect(ui2->remove_node,&QPushButton::released,this,&PSAS::remove_Node_from_Model);
    connect(ui2->add_element_button,&QPushButton::released,this,&PSAS::add_Element_to_Model);
    connect(ui2->remove_element_button,&QPushButton::released,this,&PSAS::remove_Element_from_Model);
    connect(ui2->El_prop_button,&QPushButton::released,this,&PSAS::add_el_props);
    connect(ui2->Boundary_Button,&QPushButton::released,this,&PSAS::add_BCs);
    connect(ui2->El_Load_Button,&QPushButton::released,this,&PSAS::add_el_load);
    connect(ui2->Nodal_Load_Button,&QPushButton::released,this,&PSAS::add_node_load);
    connect(ui2->SubmitModel,&QPushButton::released,this,&PSAS::setupModel);
    connect(ui2->SwitchDimButton,&QPushButton::released,this,&PSAS::switchDim);
    connect(ui2->plotModelButton,&QPushButton::released,this,&PSAS::plotModel);
    connect(ui2->HybridProps,&QPushButton::released,this,&PSAS::HybridEl_Window);
    connect(ui2->HybridCheck,&QCheckBox::stateChanged,this,&PSAS::enableHybrid);
    connect(ui2->submitEQ,&QPushButton::released,this,&PSAS::submitEQ);
    connect(ui2->submitDynOp,&QPushButton::released,this,&PSAS::submitDynOpt);
    connect(ui2->CustomEl,&QPushButton::released,this,&PSAS::CustomEl_Window);
    connect(ui2->CustomCheck,&QCheckBox::stateChanged,this,&PSAS::enableCustom);
}

void PSAS::add_Node_to_Model(){

    if (twodthreed == 1){
        std::vector<double> new_data = {ui2->x_pos_input->value(),ui2->y_pos_input->value(),ui2->z_pos_input->value(),ui2->Mass_Input->value()};
        NODE.push_back(new_data);
        node_load.push_back({0.0,0.0,0.0,0.0,0.0,0.0});
        BC.push_back({0,0,0,0,0,0});
        ui2->textEdit->clear();
        ui2->textEdit_4->clear();
        ui2->textEdit_6->clear();
        for(int i = 0 ; i<NODE.size(); i++){
            ui2->textEdit->append(QString("(%1,%2,%3);%4").arg(NODE[i][0]).arg(NODE[i][1]).arg(NODE[i][2]).arg(NODE[i][3]));
            ui2->textEdit_4->append(QString("%1,%2,%3,%4,%5,%6").arg(BC[i][0]).arg(BC[i][1]).arg(BC[i][2]).arg(BC[i][3]).arg(BC[i][4]).arg(BC[i][5]));
            ui2->textEdit_6->append(QString("%1,%2,%3,%4,%5,%6").arg(node_load[i][0]).arg(node_load[i][1]).arg(node_load[i][2]).arg(node_load[i][3]).arg(node_load[i][4]).arg(node_load[i][5]));
        }
    }else{
        std::vector<double> new_data = {ui2->x_pos_input->value(),ui2->y_pos_input->value(),ui2->Mass_Input->value()};
        NODE.push_back(new_data);
        node_load.push_back({0.0,0.0,0.0});
        BC.push_back({0,0,0});
        ui2->textEdit->clear();
        ui2->textEdit_4->clear();
        ui2->textEdit_6->clear();
        for(int i = 0 ; i<NODE.size(); i++){
            ui2->textEdit->append(QString("(%1,%2);%3").arg(NODE[i][0]).arg(NODE[i][1]).arg(NODE[i][2]));
            ui2->textEdit_4->append(QString("%1,%2,%3").arg(BC[i][0]).arg(BC[i][1]).arg(BC[i][2]));
            ui2->textEdit_6->append(QString("%1,%2,%3").arg(node_load[i][0]).arg(node_load[i][1]).arg(node_load[i][2]));
        }
    }
}

void PSAS::remove_Node_from_Model(){
    if (twodthreed == 1){
        std::vector<double> new_data = {ui2->x_pos_input->value(),ui2->y_pos_input->value(),ui2->z_pos_input->value(),ui2->Mass_Input->value()};
        for(int i = 0 ; i<NODE.size(); i++){
            if(NODE[i][0]==new_data[0] and NODE[i][1]==new_data[1] and NODE[i][2]==new_data[2]){
                NODE.erase(NODE.begin()+i);
                BC.erase(BC.begin()+i);
                node_load.erase(node_load.begin()+i);
                break;
            }
            //printf("%f\n",Positions[0][0]);
            //printf("%f\n",new_data[0]);
        }
        ui2->textEdit->clear();
        ui2->textEdit_4->clear();
        ui2->textEdit_6->clear();
        for(int i = 0 ; i<NODE.size(); i++){
            ui2->textEdit->append(QString("(%1,%2,%3);%4").arg(NODE[i][0]).arg(NODE[i][1]).arg(NODE[i][2]).arg(NODE[i][3]));
            ui2->textEdit_4->append(QString("%1,%2,%3,%4,%5,%6").arg(BC[i][0]).arg(BC[i][1]).arg(BC[i][2]).arg(BC[i][3]).arg(BC[i][4]).arg(BC[i][5]));
            ui2->textEdit_6->append(QString("%1,%2,%3,%4,%5,%6").arg(node_load[i][0]).arg(node_load[i][1]).arg(node_load[i][2]).arg(node_load[i][3]).arg(node_load[i][4]).arg(node_load[i][5]));
        }
    }else{
        std::vector<double> new_data = {ui2->x_pos_input->value(),ui2->y_pos_input->value(),ui2->Mass_Input->value()};
        for(int i = 0 ; i<NODE.size(); i++){
            if(NODE[i][0]==new_data[0] and NODE[i][1]==new_data[1]){
                NODE.erase(NODE.begin()+i);
                BC.erase(BC.begin()+i);
                node_load.erase(node_load.begin()+i);
                break;
            }
            //printf("%f\n",Positions[0][0]);
            //printf("%f\n",new_data[0]);
        }
        ui2->textEdit->clear();
        ui2->textEdit_4->clear();
        ui2->textEdit_6->clear();
        for(int i = 0 ; i<NODE.size(); i++){
            ui2->textEdit->append(QString("(%1,%2);%3").arg(NODE[i][0]).arg(NODE[i][1]).arg(NODE[i][2]));
            ui2->textEdit_4->append(QString("%1,%2,%3").arg(BC[i][0]).arg(BC[i][1]).arg(BC[i][2]));
            ui2->textEdit_6->append(QString("%1,%2,%3").arg(node_load[i][0]).arg(node_load[i][1]).arg(node_load[i][2]));
        }
    }
}

void PSAS::add_Element_to_Model(){
    if (twodthreed == 1){
        ui2->textEdit_2->clear();
        if(ui2->i_node_input->value() == 0 or ui2->j_node_input->value() == 0){
            ui2->textEdit_2->append(QString("Nodes are 1 indexed"));
        }else if(ui2->i_node_input->value()>NODE.size() or ui2->j_node_input->value()>NODE.size()){
            ui2->textEdit_2->append(QString("At least one node does not exist"));
        }else if(ui2->i_node_input->value() == ui2->j_node_input->value()){
            ui2->textEdit_2->append(QString("Not a valid Element"));
        }else{
            std::vector<int> new_props = {ui2->i_node_input->value(),ui2->j_node_input->value()};
            CON.push_back(new_props);
            el_prop.push_back({0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0});
            el_load.push_back({0.0,0.0,0.0,0.0,0.0,0.0});
            RelMat.push_back({-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0,-1.0});
            ui2->textEdit_3->clear();
            ui2->textEdit_5->clear();
            ui2->ElREL->clear();
            for(int i = 0 ; i<CON.size(); i++){
                ui2->textEdit_2->append(QString("%1,%2").arg(CON[i][0]).arg(CON[i][1]));
                if (el_prop[i][8] == 0){
                    ui2->textEdit_3->append(QString("%1,%2,%3,%4,%5,%6,%7,%8,%9").arg(el_prop[i][0]).arg(el_prop[i][1]).arg(el_prop[i][2]).arg(el_prop[i][3]).arg(el_prop[i][4]).arg(el_prop[i][5]).arg(el_prop[i][6]).arg(el_prop[i][7]).arg(el_prop[i][8]));
                }else{
                    ui2->textEdit_3->append(QString("Custom Element"));
                }
                ui2->textEdit_5->append(QString("%1,%2,%3,%4,%5,%6").arg(el_load[i][0]).arg(el_load[i][1]).arg(el_load[i][2]).arg(el_load[i][3]).arg(el_load[i][4]).arg(el_load[i][5]));
                ui2->ElREL->append(QString("%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12").arg(RelMat[i][0]).arg(RelMat[i][1]).arg(RelMat[i][2]).arg(RelMat[i][3]).arg(RelMat[i][4]).arg(RelMat[i][5]).arg(RelMat[i][6]).arg(RelMat[i][7]).arg(RelMat[i][8]).arg(RelMat[i][9]).arg(RelMat[i][10]).arg(RelMat[i][11]));
            }
        }
    }else{
        ui2->textEdit_2->clear();
        if(ui2->i_node_input->value() == 0 or ui2->j_node_input->value() == 0){
            ui2->textEdit_2->append(QString("Nodes are 1 indexed"));
        }else if(ui2->i_node_input->value()>NODE.size() or ui2->j_node_input->value()>NODE.size()){
            ui2->textEdit_2->append(QString("At least one node does not exist"));
        }else if(ui2->i_node_input->value() == ui2->j_node_input->value()){
            ui2->textEdit_2->append(QString("Not a valid Element"));
        }else{
            std::vector<int> new_props = {ui2->i_node_input->value(),ui2->j_node_input->value()};
            CON.push_back(new_props);
            el_prop.push_back({0.0,0.0,0.0,0.0,0.0,0.0});
            el_load.push_back({0.0,0.0,0.0});
            RelMat.push_back({-1.0,-1.0,-1.0,-1.0,-1.0,-1.0});
            ui2->textEdit_3->clear();
            ui2->textEdit_5->clear();
            ui2->ElREL->clear();
            for(int i = 0 ; i<CON.size(); i++){
                ui2->textEdit_2->append(QString("%1,%2").arg(CON[i][0]).arg(CON[i][1]));
                if (el_prop[i][5] == 0){
                    ui2->textEdit_3->append(QString("%1,%2,%3,%4,%5,%6").arg(el_prop[i][0]).arg(el_prop[i][1]).arg(el_prop[i][2]).arg(el_prop[i][3]).arg(el_prop[i][4]).arg(el_prop[i][5]));
                }else{
                    ui2->textEdit_3->append(QString("Custom Element"));
                }
                ui2->textEdit_5->append(QString("%1,%2,%3").arg(el_load[i][0]).arg(el_load[i][1]).arg(el_load[i][2]));
                ui2->ElREL->append(QString("%1,%2,%3,%4,%5,%6").arg(RelMat[i][0]).arg(RelMat[i][1]).arg(RelMat[i][2]).arg(RelMat[i][3]).arg(RelMat[i][4]).arg(RelMat[i][5]));
            }
        }
    }
}
void PSAS::remove_Element_from_Model(){
    if (twodthreed == 1){
        std::vector<int> new_el = {ui2->i_node_input->value(),ui2->j_node_input->value()};
        for(int i = 0 ; i<CON.size(); i++){
            if(CON[i][0]==new_el[0] and CON[i][1]==new_el[1]){
                CON.erase(CON.begin()+i);
                el_prop.erase(el_prop.begin()+i);
                el_load.erase(el_load.begin()+i);
                RelMat.erase(el_load.begin()+i);
                break;
            }


        }
        ui2->textEdit_2->clear();
        ui2->textEdit_3->clear();
        ui2->textEdit_5->clear();
        for(int i = 0 ; i<CON.size(); i++){
            ui2->textEdit_2->append(QString("%1,%2").arg(CON[i][0]).arg(CON[i][1]));
            if (el_prop[i][8] == 0){
                ui2->textEdit_3->append(QString("%1,%2,%3,%4,%5,%6,%7,%8,%9").arg(el_prop[i][0]).arg(el_prop[i][1]).arg(el_prop[i][2]).arg(el_prop[i][3]).arg(el_prop[i][4]).arg(el_prop[i][5]).arg(el_prop[i][6]).arg(el_prop[i][7]).arg(el_prop[i][8]));
            }else{
                ui2->textEdit_3->append(QString("Custom Element"));
            }
            ui2->textEdit_5->append(QString("%1,%2,%3,%4,%5,%6").arg(el_load[i][0]).arg(el_load[i][1]).arg(el_load[i][2]).arg(el_load[i][3]).arg(el_load[i][4]).arg(el_load[i][5]));
            ui2->ElREL->append(QString("%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12").arg(RelMat[i][0]).arg(RelMat[i][1]).arg(RelMat[i][2]).arg(RelMat[i][3]).arg(RelMat[i][4]).arg(RelMat[i][5]).arg(RelMat[i][6]).arg(RelMat[i][7]).arg(RelMat[i][8]).arg(RelMat[i][9]).arg(RelMat[i][10]).arg(RelMat[i][11]));
        }
    }else{
        std::vector<int> new_el = {ui2->i_node_input->value(),ui2->j_node_input->value()};
        for(int i = 0 ; i<CON.size(); i++){
            if(CON[i][0]==new_el[0] and CON[i][1]==new_el[1]){
                CON.erase(CON.begin()+i);
                el_prop.erase(el_prop.begin()+i);
                el_load.erase(el_load.begin()+i);
                RelMat.erase(el_load.begin()+i);
                break;
            }

        }
        ui2->textEdit_2->clear();
        ui2->textEdit_3->clear();
        ui2->textEdit_5->clear();
        for(int i = 0 ; i<CON.size(); i++){
            ui2->textEdit_2->append(QString("%1,%2").arg(CON[i][0]).arg(CON[i][1]));
            if (el_prop[i][5] == 0){
                ui2->textEdit_3->append(QString("%1,%2,%3,%4,%5,%6").arg(el_prop[i][0]).arg(el_prop[i][1]).arg(el_prop[i][2]).arg(el_prop[i][3]).arg(el_prop[i][4]).arg(el_prop[i][5]));
            }else{
                ui2->textEdit_3->append(QString("Custom Element"));
            }
            ui2->textEdit_5->append(QString("%1,%2,%3").arg(el_load[i][0]).arg(el_load[i][1]).arg(el_load[i][2]));
            ui2->ElREL->append(QString("%1,%2,%3,%4,%5,%6").arg(RelMat[i][0]).arg(RelMat[i][1]).arg(RelMat[i][2]).arg(RelMat[i][3]).arg(RelMat[i][4]).arg(RelMat[i][5]));
        }
    }
}

void PSAS::add_el_props(){
    if (twodthreed == 1){
        ui2->textEdit_3->clear();
        ui2->ElREL->clear();
        if(ui2->El_Prop_select->value()>el_prop.size()){
            ui2->textEdit_2->append(QString("Element Does Not Exist"));
        }else if(ui2->El_Prop_select->value()==0){
            ui2->textEdit_3->append(QString("Elements are 1 indexed"));
        }else{
            if(ui2->CustomCheck->isChecked()){
                el_prop[ui2->El_Prop_select->value()-1] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,1.0};
            }else{
                el_prop[ui2->El_Prop_select->value()-1] = {ui2->E_input->value(),ui2->A_input->value(),ui2->J_input->value(),ui2->v_input->value(),ui2->Iy_input->value(),ui2->Iz_input->value(),ui2->rho_input->value(),ui2->HybridCheck->isChecked(),0.0};
            }
            RelMat[ui2->El_Prop_select->value()-1] = {ui2->REL1->value(),ui2->REL2->value(),ui2->REL3->value(),ui2->REL4->value(),ui2->REL5->value(),ui2->REL6->value(),ui2->REL7->value(),ui2->REL8->value(),ui2->REL9->value(),ui2->REL10->value(),ui2->REL11->value(),ui2->REL12->value()};
            for(int i = 0 ; i<CON.size(); i++){
                if (el_prop[i][8] == 0){
                    ui2->textEdit_3->append(QString("%1,%2,%3,%4,%5,%6,%7,%8,%9").arg(el_prop[i][0]).arg(el_prop[i][1]).arg(el_prop[i][2]).arg(el_prop[i][3]).arg(el_prop[i][4]).arg(el_prop[i][5]).arg(el_prop[i][6]).arg(el_prop[i][7]).arg(el_prop[i][8]));
                }else{
                    ui2->textEdit_3->append(QString("Custom Element"));
                }
                ui2->ElREL->append(QString("%1,%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12").arg(RelMat[i][0]).arg(RelMat[i][1]).arg(RelMat[i][2]).arg(RelMat[i][3]).arg(RelMat[i][4]).arg(RelMat[i][5]).arg(RelMat[i][6]).arg(RelMat[i][7]).arg(RelMat[i][8]).arg(RelMat[i][9]).arg(RelMat[i][10]).arg(RelMat[i][11]));
            }
        }
    }else{
        ui2->textEdit_3->clear();
        ui2->ElREL->clear();
        if(ui2->El_Prop_select->value()>el_prop.size()){
            ui2->textEdit_2->append(QString("Element Does Not Exist"));
        }else if(ui2->El_Prop_select->value()==0){
            ui2->textEdit_3->append(QString("Elements are 1 indexed"));
        }else{
            if(ui2->CustomCheck->isChecked()){
                el_prop[ui2->El_Prop_select->value()-1] = {0.0,0.0,0.0,0.0,0.0,1.0};
            }else{

                el_prop[ui2->El_Prop_select->value()-1] = {ui2->E_input->value(),ui2->A_input->value(),ui2->Iz_input->value(),ui2->rho_input->value(),ui2->HybridCheck->isChecked(),0.0};
            }
            RelMat[ui2->El_Prop_select->value()-1] = {ui2->REL1->value(),ui2->REL2->value(),ui2->REL3->value(),ui2->REL4->value(),ui2->REL5->value(),ui2->REL6->value()};
            for(int i = 0 ; i<CON.size(); i++){
                if (el_prop[i][5] == 0){
                    ui2->textEdit_3->append(QString("%1,%2,%3,%4,%5,%6").arg(el_prop[i][0]).arg(el_prop[i][1]).arg(el_prop[i][2]).arg(el_prop[i][3]).arg(el_prop[i][4]).arg(el_prop[i][5]));
                }else{
                    ui2->textEdit_3->append(QString("Custom Element"));
                }
                ui2->ElREL->append(QString("%1,%2,%3,%4,%5,%6").arg(RelMat[i][0]).arg(RelMat[i][1]).arg(RelMat[i][2]).arg(RelMat[i][3]).arg(RelMat[i][4]).arg(RelMat[i][5]));
            }
        }
    }
}

void PSAS::add_BCs(){
    if (twodthreed == 1){
        ui2->textEdit_4->clear();
        if(ui2->BC_Node->value() > NODE.size()){
            ui2->textEdit_4->append(QString("Node Does Not Exist"));
        }else if(ui2->BC_Node->value()==0){
            ui2->textEdit_4->append(QString("Nodes are 1 indexed"));
        }else if(ui2->Bx_input->value()>1 or ui2->By_input->value()>1 or ui2->Bz_input->value()>1 or ui2->Brx_input->value()>1 or ui2->Bry_input->value()>1 or ui2->Brz_input->value()>1){
            ui2->textEdit_4->append(QString("Boundary Conditions are Binary"));
        }else{
            BC[ui2->BC_Node->value()-1] = {ui2->Bx_input->value(),ui2->By_input->value(),ui2->Bz_input->value(),ui2->Brx_input->value(),ui2->Bry_input->value(),ui2->Brz_input->value()};

            for(int i = 0 ; i<NODE.size(); i++){
                ui2->textEdit_4->append(QString("%1,%2,%3,%4,%5,%6").arg(BC[i][0]).arg(BC[i][1]).arg(BC[i][2]).arg(BC[i][3]).arg(BC[i][4]).arg(BC[i][5]));
            }
        }
    }else{
        ui2->textEdit_4->clear();
        if(ui2->BC_Node->value() > NODE.size()){
            ui2->textEdit_4->append(QString("Node Does Not Exist"));
        }else if(ui2->BC_Node->value()==0){
            ui2->textEdit_4->append(QString("Nodes are 1 indexed"));
        }else if(ui2->Bx_input->value()>1 or ui2->By_input->value()>1 or ui2->Brz_input->value()>1){
            ui2->textEdit_4->append(QString("Boundary Conditions are Binary"));
        }else{
            BC[ui2->BC_Node->value()-1] = {ui2->Bx_input->value(),ui2->By_input->value(),ui2->Brz_input->value()};

            for(int i = 0 ; i<NODE.size(); i++){
                ui2->textEdit_4->append(QString("%1,%2,%3").arg(BC[i][0]).arg(BC[i][1]).arg(BC[i][2]));
            }
        }
    }
}

void PSAS::add_el_load(){
    if (twodthreed == 1){
        ui2->textEdit_5->clear();
        if(ui2->Element_load_select->value()>el_load.size()){
            ui2->textEdit_5->append(QString("Element Does Not Exist"));
        }else if(ui2->Element_load_select->value()==0){
            ui2->textEdit_5->append(QString("Elements are 1 indexed"));
        }else{
            el_load[ui2->Element_load_select->value()-1] = {ui2->wx_input->value(),ui2->wy_input->value(),ui2->wz_input->value(),ui2->rx_input->value(),ui2->ry_input->value(),ui2->rz_input->value()};

            for(int i = 0 ; i<CON.size(); i++){
                ui2->textEdit_5->append(QString("%1,%2,%3,%4,%5,%6").arg(el_load[i][0]).arg(el_load[i][1]).arg(el_load[i][2]).arg(el_load[i][3]).arg(el_load[i][4]).arg(el_load[i][5]));
            }
        }
    }else{
        ui2->textEdit_5->clear();
        if(ui2->Element_load_select->value()>el_load.size()){
            ui2->textEdit_5->append(QString("Element Does Not Exist"));
        }else if(ui2->Element_load_select->value()==0){
            ui2->textEdit_5->append(QString("Elements are 1 indexed"));
        }else{
            el_load[ui2->Element_load_select->value()-1] = {ui2->wx_input->value(),ui2->wy_input->value(),ui2->rz_input->value()};

            for(int i = 0 ; i<CON.size(); i++){
                ui2->textEdit_5->append(QString("%1,%2,%3").arg(el_load[i][0]).arg(el_load[i][1]).arg(el_load[i][2]));
            }
        }
    }
}

void PSAS::add_node_load(){
    if (twodthreed == 1){
        ui2->textEdit_6->clear();
        if(ui2->Node_Load_Select->value() > NODE.size()){
            ui2->textEdit_6->append(QString("Node Does Not Exist"));
        }else if(ui2->Node_Load_Select->value() == 0){
            ui2->textEdit_6->append(QString("Nodes are 1 indexed"));
        }else{
            node_load[ui2->Node_Load_Select->value()-1] = {ui2->xLoad_input->value(),ui2->yLoad_input->value(),ui2->zLoad_input->value(),ui2->mxLoad_input->value(),ui2->myLoad_input->value(),ui2->mzLoad_input->value()};

            for(int i = 0 ; i<NODE.size(); i++){
                ui2->textEdit_6->append(QString("%1,%2,%3,%4,%5,%6").arg(node_load[i][0]).arg(node_load[i][1]).arg(node_load[i][2]).arg(node_load[i][3]).arg(node_load[i][4]).arg(node_load[i][5]));
            }
        }
    }else{
        ui2->textEdit_6->clear();
        if(ui2->Node_Load_Select->value() > NODE.size()){
            ui2->textEdit_6->append(QString("Node Does Not Exist"));
        }else if(ui2->Node_Load_Select->value() == 0){
            ui2->textEdit_6->append(QString("Nodes are 1 indexed"));
        }else{
            node_load[ui2->Node_Load_Select->value()-1] = {ui2->xLoad_input->value(),ui2->yLoad_input->value(),ui2->mzLoad_input->value()};

            for(int i = 0 ; i<NODE.size(); i++){
                ui2->textEdit_6->append(QString("%1,%2,%3").arg(node_load[i][0]).arg(node_load[i][1]).arg(node_load[i][2]));
            }
        }
    }
}

void PSAS::switchDim(){
    if (twodthreed == 0){
        twodthreed = 1;
        ui2->DimText->clear();
        ui2->DimText->setText("3D");
        ui2->z_pos_input->setDisabled(0);
        ui2->J_input->setDisabled(0);
        ui2->v_input->setDisabled(0);
        ui2->Iy_input->setDisabled(0);
        ui2->Bz_input->setDisabled(0);
        ui2->Brx_input->setDisabled(0);
        ui2->Bry_input->setDisabled(0);
        ui2->zLoad_input->setDisabled(0);
        ui2->mxLoad_input->setDisabled(0);
        ui2->myLoad_input->setDisabled(0);
        ui2->wz_input->setDisabled(0);
        ui2->rx_input->setDisabled(0);
        ui2->ry_input->setDisabled(0);
        ui2->REL7->setDisabled(0);
        ui2->REL8->setDisabled(0);
        ui2->REL9->setDisabled(0);
        ui2->REL10->setDisabled(0);
        ui2->REL11->setDisabled(0);
        ui2->REL12->setDisabled(0);
    }
    else if (twodthreed == 1){
        twodthreed = 0;
        ui2->DimText->clear();
        ui2->DimText->setText("2D");
        ui2->z_pos_input->setDisabled(1);
        ui2->J_input->setDisabled(1);
        ui2->v_input->setDisabled(1);
        ui2->Iy_input->setDisabled(1);
        ui2->Bz_input->setDisabled(1);
        ui2->Brx_input->setDisabled(1);
        ui2->Bry_input->setDisabled(1);
        ui2->zLoad_input->setDisabled(1);
        ui2->mxLoad_input->setDisabled(1);
        ui2->myLoad_input->setDisabled(1);
        ui2->wz_input->setDisabled(1);
        ui2->rx_input->setDisabled(1);
        ui2->ry_input->setDisabled(1);
        ui2->REL7->setDisabled(1);
        ui2->REL8->setDisabled(1);
        ui2->REL9->setDisabled(1);
        ui2->REL10->setDisabled(1);
        ui2->REL11->setDisabled(1);
        ui2->REL12->setDisabled(1);
    }
    NODE = {};
    CON = {};
    el_prop = {};
    el_load = {};
    node_load = {};
    BC = {};
}

int PSAS::setupModel(){
    Py_Initialize();
    import_array();
    PyObject *sysPath = PySys_GetObject((char*)"path");
    PyList_Append(sysPath,PyUnicode_FromString("/home/jim53/Desktop/HSM_Full"));  // path to the module to import
    ModelSetupName = PyUnicode_FromString("Model_Setup");
    sw = ui2->selfWeightCheck->isChecked();
    Props = {twodthreed,sw};
    int NODE_dim[2] = {(int)NODE.size(),(int)NODE[0].size()};
    int CON_dim[2] = {(int)CON.size(),(int)CON[0].size()};
    int el_prop_dim[2] = {(int)el_prop.size(),(int)el_prop[0].size()};
    int el_load_dim[2] = {(int)el_load.size(),(int)el_load[0].size()};
    int node_load_dim[2] = {(int)node_load.size(),(int)node_load[0].size()};
    int BC_dim[2] = {(int)BC.size(),(int)BC[0].size()};
    int Prop_dim[1] = {(int)Props.size()};
    int Rel_dim[2] = {(int)RelMat.size(),(int)RelMat[0].size()};
    int nd = 2;

    printf("check1\n");
    std::vector<double> NODE_flat;
    std::vector<int> CON_flat;
    std::vector<double> el_prop_flat;
    std::vector<double> el_load_flat;
    std::vector<double> node_load_flat;
    std::vector<double> HybridElMatrix_flat;
    std::vector<int> HybridElControl_flat;
    std::vector<int> BC_flat;
    std::vector<double> Rel_flat;
    std::vector<double> Custom_flat;

    printf("check2\n");
    for(int i=0; i<NODE.size(); i++){
        for(int j=0; j<NODE[i].size(); j++){
            NODE_flat.push_back(NODE[i][j]);
        }
    }
    for(int i=0; i<CON.size(); i++){
        for(int j=0; j<CON[i].size(); j++){
            CON_flat.push_back(CON[i][j]);
        }
    }
    for(int i=0; i<el_prop.size(); i++){
        for(int j=0; j<el_prop[i].size(); j++){
            el_prop_flat.push_back(el_prop[i][j]);
        }
    }
    for(int i=0; i<el_load.size(); i++){
        for(int j=0; j<el_load[i].size(); j++){
            el_load_flat.push_back(el_load[i][j]);
        }
    }
    for(int i=0; i<node_load.size(); i++){
        for(int j=0; j<node_load[i].size(); j++){
            node_load_flat.push_back(node_load[i][j]);
        }
    }
    for(int i=0; i<BC.size(); i++){
        for(int j=0; j<BC[i].size(); j++){
            BC_flat.push_back(BC[i][j]);
        }
    }

    for(int i=0; i<RelMat.size(); i++){
        for(int j=0; j<RelMat[i].size(); j++){
            Rel_flat.push_back(RelMat[i][j]);
        }
    }


    double *NODEmem = &NODE_flat[0];
    int *CONmem = &CON_flat[0];
    double *el_propmem = &el_prop_flat[0];
    double *el_loadmem = &el_load_flat[0];
    double *node_loadmem = &node_load_flat[0];
    int *BCmem = &BC_flat[0];
    int *propMem = &Props[0];
    double *Relmem = &Rel_flat[0];

    printf("check3\n");
    //build python matrices
    ModelSetupMethod = PyImport_Import(ModelSetupName);
    PyObject *python_NODE = PyArray_SimpleNewFromData(nd,NODE_dim,NPY_DOUBLE,(double*)NODEmem);
    PyObject *python_CON = PyArray_SimpleNewFromData(nd,CON_dim,NPY_INT,(double*)CONmem);
    PyObject *python_el_prop = PyArray_SimpleNewFromData(nd,el_prop_dim,NPY_DOUBLE,(double*)el_propmem);
    PyObject *python_el_load = PyArray_SimpleNewFromData(nd,el_load_dim,NPY_DOUBLE,(double*)el_loadmem);
    PyObject *python_node_load = PyArray_SimpleNewFromData(nd,node_load_dim,NPY_DOUBLE,(double*)node_loadmem);
    PyObject *python_BC = PyArray_SimpleNewFromData(nd,BC_dim,NPY_INT,(double*)BCmem);
    PyObject *modelProp = PyArray_SimpleNewFromData(1,Prop_dim,NPY_INT,(int*)propMem);
    PyObject *pythonRel = PyArray_SimpleNewFromData(nd,Rel_dim,NPY_DOUBLE,(double*)Relmem);

    printf("check4\n");
    SetupArgs = PyTuple_New (12);
    if (not HybridElMatrix.empty()){

        int HybridElMatrix_dim[3] = {(int)HybridElMatrix.size(),(int)HybridElMatrix[0].size(),(int)HybridElMatrix[0][0].size()};
        for(int i=0; i<HybridElMatrix.size(); i++){
            for(int j=0; j<HybridElMatrix[i].size(); j++){
                for(int k=0; k<HybridElMatrix[i][j].size(); k++){
                    HybridElMatrix_flat.push_back(HybridElMatrix[i][j][k]);
                }
            }
        }
        double *HybridElMatrixmem = &HybridElMatrix_flat[0];
        PyObject *python_HybridElMatrix = PyArray_SimpleNewFromData(3,HybridElMatrix_dim,NPY_DOUBLE,(double*)HybridElMatrixmem);
        PyTuple_SetItem(SetupArgs, 10, python_HybridElMatrix);
    }else{
        PyTuple_SetItem(SetupArgs, 10, PyLong_FromDouble(-1.0));
    }

    if (not HybridElControl.empty()){

        int HybridElControl_dim[2] = {(int)HybridElControl.size(),(int)HybridElControl[0].size()};
        for(int i=0; i<HybridElControl.size(); i++){
            for(int j=0; j<HybridElControl[i].size(); j++){
                HybridElControl_flat.push_back(HybridElControl[i][j]);
            }
        }
        int *HybridElControlmem = &HybridElControl_flat[0];
        PyObject *python_HybridElControl = PyArray_SimpleNewFromData(2,HybridElControl_dim,NPY_INT,(int*)HybridElControlmem);
        PyTuple_SetItem(SetupArgs, 11, python_HybridElControl);
    }else{
        PyTuple_SetItem(SetupArgs, 11, PyLong_FromDouble(-1.0));
    }

    if (not DynamicParams.empty()){
        int DynamicParams_dim[1] = {(int)DynamicParams.size()};
        double *DynamicParamsmem = &DynamicParams[0];
        PyObject *python_DynamicParams = PyArray_SimpleNewFromData(1,DynamicParams_dim,NPY_DOUBLE,(int*)DynamicParamsmem);
        PyTuple_SetItem(SetupArgs, 9, python_DynamicParams);
    }else{
        PyTuple_SetItem(SetupArgs, 9, PyLong_FromDouble(-1.0));
    }

    if (not CustomElMatrix.empty()){
        int Custom_dim[3] = {(int)CustomElMatrix.size(),(int)CustomElMatrix[0].size(),(int)CustomElMatrix[0][0].size()};
        for(int i=0; i<CustomElMatrix.size(); i++){
            for(int j=0; j<CustomElMatrix[i].size(); j++){
                for(int k=0; k<CustomElMatrix[i][j].size(); k++){
                    Custom_flat.push_back(CustomElMatrix[i][j][k]);
                }
            }
        }
        double *Custommem = &Custom_flat[0];
        PyObject *pythonCustom = PyArray_SimpleNewFromData(3,Custom_dim,NPY_DOUBLE,(double*)Custommem);
        PyTuple_SetItem(SetupArgs, 5, pythonCustom);
    }else{
        PyTuple_SetItem(SetupArgs, 5, PyLong_FromDouble(-1.0));
    }

    printf("check5\n");
    if (ModelSetupMethod != NULL) {
        PyTuple_SetItem(SetupArgs, 0, python_NODE);
        PyTuple_SetItem(SetupArgs, 1, python_CON);
        PyTuple_SetItem(SetupArgs, 2, python_BC);
        PyTuple_SetItem(SetupArgs, 3, python_el_prop);
        PyTuple_SetItem(SetupArgs, 4, pythonRel);
        PyTuple_SetItem(SetupArgs, 6, python_el_load);
        PyTuple_SetItem(SetupArgs, 7, python_node_load);
        PyTuple_SetItem(SetupArgs, 8, modelProp);
        printf("check6\n");
        ModelSetupFunc = PyObject_GetAttrString(ModelSetupMethod, "Model_Setup");
        if (ModelSetupFunc && PyCallable_Check(ModelSetupFunc)) {
            printf("check7\n");
            SetupOut = PyObject_CallObject(ModelSetupFunc, SetupArgs);
            Model = PyTuple_GetItem(SetupOut,0);
            el = PyTuple_GetItem(SetupOut,1);
            //PyObject* secResult = PyTuple_GetItem(pValue,1);
            //int dim = PyArray_NDIM(firstResult);
            //Py_DECREF(Model);
            if (SetupOut != NULL) {
                //void* test = PyArray_DATA(secResult);
                //int*ip = static_cast<int*>(test);
            //    npy_intp size = PyArray_SIZE(firstResult);
                printf("Value returned from the function\n");
            } else {
                printf("Error");
                PyErr_Print();
            }
        } else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function %s\n", "Test_Python");
        }
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load %s\n", "Test_Python");
        return 1;
    }
}

int PSAS::plotModel(){
    Py_Initialize();
    import_array();
    PyObject *sysPath = PySys_GetObject((char*)"path");
    PyList_Append(sysPath,PyUnicode_FromString("/home/jim53/Desktop/HSM_Full"));  // path to the module to import
    PlotModelName = PyUnicode_FromString("CreatePlot");
    PlotModelMethod = PyImport_Import(PlotModelName);

    if (PlotModelMethod != NULL) {

        PlotArgs = PyTuple_New(2);
        PyTuple_SetItem(PlotArgs, 0, Model);
        PyTuple_SetItem(PlotArgs, 1, el);

        PlotModelFunc = PyObject_GetAttrString(PlotModelMethod, "CreatePlot");
        if (PlotModelFunc && PyCallable_Check(PlotModelFunc)) {
            printf("attempt\n");
            PlotOut = PyObject_CallObject(PlotModelFunc, PlotArgs);
        } else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function %s\n", "Test_Python");
        }
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load %s\n", "Test_Python");
        return 1;
    }
}

void PSAS::HybridEl_Window(){
    HybridEl *StructSoft = new HybridEl();
    StructSoft->show();
}


void PSAS::submitEQ(){
    DIR *directory;
    struct dirent *x;
    GMname = ui2->plainTextEdit->toPlainText().toStdString();
    printf("%s\n",GMname.c_str());
    bool result = FALSE;
    if ((directory = opendir("/home/jim53/Desktop/HSM_Full")) != NULL){
        while((x=readdir(directory))!=NULL){
            if(GMname==x->d_name){
                    printf("attempt");
                    result=true;  //if file found then  assign  result to false.

                        break;     // break the loop if file found.
        }
    }
    closedir(directory);
    if(result)   // if file is present then....
      {
        ui2->plainTextEdit->setPlainText("file is present");
        std::string gmdir = "/home/jim53/Desktop/HSM_Full/";
        for(int i = 0; i<= (int)GMname.size(); i++)
            {
                gmdir.push_back(GMname.c_str()[i]);
            }

        printf("%s\n",gmdir.c_str());
        std::ifstream GMfile(gmdir.c_str());
        while(GMfile>>GMdata){
                GM.push_back(GMdata);
        }
        printf("%f",GM[0]);
      }
      else    //if file is not present....
      {
        ui2->plainTextEdit->setPlainText("file is was not found");
      }

}else{
        printf("Directory Not Found");
    }

}

int PSAS::submitDynOpt(){
    DynamicParams = {ui2->dir1->value(),ui2->dir2->value(),ui2->dir3->value(),ui2->scale->value(),ui2->dtold->value(),ui2->dt->value(),ui2->alpha->value(),ui2->zeta->value(),ui2->Mode1->value(),ui2->Mode2->value()};
    Py_Initialize();
    import_array();
    PyObject *sysPath = PySys_GetObject((char*)"path");
    PyList_Append(sysPath,PyUnicode_FromString("/home/jim53/Desktop/HSM_Full"));  // path to the module to import
    GMName = PyUnicode_FromString("GMread");
    GMMethod = PyImport_Import(GMName);
    int GM_dim[1] = {(int)GM.size()};
    int Dyn_dim[1] = {(int)DynamicParams.size()};
    double *GMmem = &GM[0];
    double *Dynmem = &DynamicParams[0];
    PyGM = PyArray_SimpleNewFromData(1,GM_dim,NPY_DOUBLE,(double*)GMmem);
    PyDyn = PyArray_SimpleNewFromData(1,Dyn_dim,NPY_DOUBLE,(double*)Dynmem);
    if (GMMethod != NULL) {

        GMArgs = PyTuple_New(2);
        PyTuple_SetItem(GMArgs, 0, PyGM);
        PyTuple_SetItem(GMArgs, 1, PyDyn);

        GMFunc = PyObject_GetAttrString(GMMethod, "GMread");
        if (GMFunc && PyCallable_Check(GMFunc)) {
            printf("1");
            GMOut = PyObject_CallObject(GMFunc, GMArgs);
            PyArrayObject *PyGMnew = (PyArrayObject*) GMOut;
            int dim = PyArray_NDIM(PyGMnew);

            if (GMOut != NULL) {
                ui2->plainTextEdit_2->setPlainText("Success!");
                printf("Value returned from the function\n");

                double* GMptr = (double*)PyArray_DATA(PyGMnew);
                npy_intp GMsize = PyArray_SIZE(PyGMnew);
                printf("%f\n",GMptr[0]);
                GM = {};
                for (int i = 0 ;i<GMsize;i++){
                    GM.push_back(GMptr[i]);
                }
                printf("%f\n",GM[0]);
            } else {
                printf("Error");
                PyErr_Print();
            }
        } else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function %s\n", "Test_Python");
        }
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load %s\n", "Test_Python");
        return 1;
    }
}

void PSAS::enableHybrid(){
    if (ui2->HybridCheck->checkState()){
        ui2->HybridProps->setEnabled(TRUE);
    }else{
        ui2->HybridProps->setEnabled(FALSE);
    }
}

void PSAS::enableCustom(){
    if (ui2->CustomCheck->checkState()){
        ui2->CustomEl->setEnabled(TRUE);
    }else{
        ui2->CustomEl->setEnabled(FALSE);
    }
}

void PSAS::CustomEl_Window(){
    CustomElement *StructSoft = new CustomElement();
    StructSoft->show();
}
PSAS::~PSAS()
{
    delete ui2;
}


