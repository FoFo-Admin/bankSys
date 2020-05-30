#include "findclient.h"
#include "ui_findclient.h"

findClient::findClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::findClient)
{
    ui->setupUi(this);
}

findClient::~findClient()
{
    delete ui;
}

 void getData(QVector<Client*> cl)
 {

 }
