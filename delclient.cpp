#include "delclient.h"
#include "ui_delclient.h"

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "Date.h"

delclient::delclient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::delclient)
{
    ui->setupUi(this);
}

delclient::~delclient()
{
    delete ui;
}

void delclient::on_pushButton_clicked()
{
    QSqlQuery query;
    query.exec("select count(id) from Customer where tel = "+ui->lineEdit->text()+" and Card_id = "+ui->lineEdit_2->text()+";");

    while(query.next())
    {
        if(query.value(0).toInt()!=0)
        {
            QSqlQuery query1;
            query1.exec("delete from Customer where tel = "+ui->lineEdit->text()+" and Card_id = "+ui->lineEdit_2->text()+";");
            QSqlQuery query2;
            query2.exec("delete from Card where id = "+ui->lineEdit_2->text()+";");
        }
    }
    emit sendData(ui->lineEdit->text(), ui->lineEdit_2->text());
    this->hide();

}
