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

 void findClient::getData(QVector<Client*> cl)
 {

 }

