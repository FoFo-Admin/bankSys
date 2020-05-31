#include "addclient.h"
#include "ui_addclient.h"
#include "exeption.h"

AddClient::AddClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddClient)
{
    ui->setupUi(this);
}

AddClient::~AddClient()
{
    delete ui;
}

void AddClient::on_pushButton_clicked()
{
    try {

    QSqlQuery query1;
    query1.exec("SELECT COUNT(id) from Customer where Tel = '"+ui->tel->text()+"'");
    while(query1.next())
    {
        if(query1.value(0).toInt() >= 5)
            throw new MaxCards(ui->tel->text());
    }

    int lgota = 0;
    QString tel = ui->tel->text();
    QString name = ui->name->text();
    QString surname = ui->surname->text();
    Date date(ui->birthday->date().year(), ui->birthday->date().month(),ui->birthday->date().day());
    QString middlename = ui->middlename->text();
    int type = 3;
    if(ui->checkBox->isChecked()) lgota = 1;

    QString sLgota = QString::number(lgota);
    QString sDay = QString::number(date.getDay());
    QString sYear = QString::number(date.getYear());
    QString sMonth = QString::number(date.getMonth());

    if(ui->deb->isChecked()) type = 3;
    else if(ui->cre->isChecked()) type = 1;
    else if(ui->dep->isChecked()) type = 2;
    QString typeS = QString::number(type);

    QSqlQuery query;
    query.prepare("INSERT Card VALUES (:typeS,0,0,0);");
    query.bindValue(":typeS", typeS);
    query.exec();

    query.exec("INSERT Customer VALUES('"+name+"', '"+surname+"','"+middlename+"', '"+sDay+"-"+sMonth+"-"+sYear+"', '"+tel+"', "+sLgota+", (SELECT TOP(1) id FROM Card ORDER BY id DESC));");
    emit sendData();
    this->hide();

    } catch (Exeption * ex) {
        QMessageBox messageBox;
        messageBox.critical(0,"Error",ex->SendError());
        messageBox.setFixedSize(500,200);
    }
}
