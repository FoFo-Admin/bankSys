#include "updateclient.h"
#include "ui_updateclient.h"

updateClient::updateClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::updateClient)
{
    ui->setupUi(this);

    ui->groupBox->hide();
}

updateClient::~updateClient()
{
    delete ui;
}

void updateClient::on_pushButton_2_clicked()
{
    QSqlQuery query;
    query.exec("select count(id) from Customer where tel = '"+ui->lineEdit->text()+"';");

    while(query.next())
    {
        if(query.value(0).toInt()!=0)
        {
            QSqlQuery query1;
            query1.exec("SELECT Name, Surname, MiddleName, YEAR(Birth), MONTH(Birth), DAY(Birth), Tel, Lgota  FROM Customer where tel = '"+ui->lineEdit->text()+"' ;");
            while(query1.next())
            {
             ui->groupBox->show();

             ui->name->setText(query1.value(0).toString());
             ui->surname->setText(query1.value(1).toString());
             ui->middlename->setText(query1.value(2).toString());
             QDate d(query1.value(3).toInt(), query1.value(4).toInt(), query1.value(5).toInt());
             ui->dateEdit->setDate(d);
             ui->tel->setText(query1.value(6).toString());
             if(query1.value(7).toInt() == 1)
                 ui->lg->setCheckState(Qt::Checked);
             else ui->lg->setCheckState(Qt::Unchecked);
            }
        }
    }
}

void updateClient::on_pushButton_clicked()
{
    int bit = 0;
    if(ui->lg->isChecked()) bit = 1;

    QString bitStr = QString::number(bit);
    QString year = QString::number(ui->dateEdit->date().year());
    QString month = QString::number(ui->dateEdit->date().month());
    QString day = QString::number(ui->dateEdit->date().day());
    QSqlQuery query;
    query.exec("update Customer set name = '"+ui->name->text()+"', surname = '"+ui->surname->text()+"', MiddleName = '"+ui->middlename->text()+"', Birth = '"+day+"-"+month+"-"+year+"', Tel = '"+ui->tel->text()+"', Lgota = "+bitStr+" where Tel = '"+ui->lineEdit->text()+"';");
    emit sendData();
    this->hide();
}
