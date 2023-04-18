#include "hsm_full.h"
#include "ui_readgm.h"
#include <iostream>
#include<dirent.h>

std::string GMname;
std::ifstream GMlocation;



ReadGM::ReadGM(QWidget *parent) :
    QWidget(parent),
    ui4(new Ui::ReadGM)
{
    ui4->setupUi(this);
    connect(ui4->submitEQ,&QPushButton::released,this,&ReadGM::submitEQ);
}

void ReadGM::submitEQ(){
    DIR *directory;
    struct dirent *x;
    GMname = ui4->plainTextEdit->toPlainText().toStdString();
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
        ui4->plainTextEdit->setPlainText("file is present");
      }
      else    //if file is not present....
      {
        ui4->plainTextEdit->setPlainText("file is was not found");
      }
}else{
        printf("Directory Not Found");
    }
}
ReadGM::~ReadGM()
{
    delete ui4;
}
