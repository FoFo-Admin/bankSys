#include "findclient.h"
#include "ui_findclient.h"
#include "QtAlgorithms"

findClient::findClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::findClient)
{
    ui->setupUi(this);
    ui->groupBox_3->hide();

    ui->comboBox->addItem("Без сортировки", QVariant("None"));
    ui->comboBox->addItem("Наибольшая задолжность сберегательные аккаунты", QVariant("cre"));
    ui->comboBox->addItem("Наибольший вклад", QVariant("dep"));
    ui->comboBox->addItem("Наименьшие сберегательные аккаунты", QVariant("acc"));
    ui->comboBox->addItem("По дате рождения", QVariant("date"));

    ui->comboBox_2->addItem("Все", QVariant("all"));
    ui->comboBox_2->addItem("Дебетовые", QVariant("debit"));
    ui->comboBox_2->addItem("Кредитные", QVariant("credit"));
    ui->comboBox_2->addItem("Депозитные", QVariant("deposit"));

    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList()<<
                 "ФИО" << "Дата рождения"<<"Номер карты"<<"Тип карты"<<"Номер телефона"<<"Льготы");

}

findClient::~findClient()
{
    delete ui;
}

 void findClient::getData(QVector<Client*> cl)
 {
     cFind.clear();
    for(int i = 0; i < cl.size(); i++)
    {
        cFind.push_back(cl[i]);
    }
 }


void findClient::on_radioButton_clicked()
{
    ui->groupBox_2->show();
    ui->groupBox_3->hide();
}

void findClient::on_radioButton_2_clicked()
{
    ui->groupBox_2->hide();
    ui->groupBox_3->show();
}

void findClient::on_pushButton_clicked()
{
    if(ui->radioButton_2->isChecked())
    {
        for(int i = 0; i < cFind.size(); i++)
        {
            if(cFind[i]->getcard()->getNumber() == ui->lineEdit_3->text().toInt())
            {
                QString l = "false";
                if(cFind[i]->getLgota()) l = "true";
                QString HTMLText = "<h3><b>Владелец:</b></h3>"+cFind[i]->getFIO() +
                                "\n <h3><b>Дата рождения:</b></h3>"+QString::number(cFind[i]->getBirthday().getDay())+"-"+QString::number(cFind[i]->getBirthday().getMonth())+"-"+QString::number(cFind[i]->getBirthday().getYear())+
                                "\n <h3><b>Номер телефона:</b></h3>"+cFind[i]->gettel() +
                                "\n <h3><b>Льготы:</b></h3>"+ l +
                                "\n <h3><b>Номер карты:</b></h3>"+QString::number(cFind[i]->getcard()->getNumber()) +
                                "\n <h3><b>Тип карты:</b></h3>"+cFind[i]->getcard()->type() +
                                "\n <h3><b>Баланс:</b></h3>"+QString::number(cFind[i]->getcard()->getBalance());
                if(cFind[i]->getcard()->type() == "credit")
                {
                    QString am = QString::number(cFind[i]->getcard()->getAmount());
                    HTMLText+="\n<h3><b>Текущая задолжность:</b></h3>" + am +
                             "<h3><b>Процент:</b></h3>"+cFind[i]->getcard()->getPercent();
                }
                if(cFind[i]->getcard()->type() == "deposit")
                {
                    QString am = QString::number(cFind[i]->getcard()->getAmount());
                    HTMLText+="\n<h3><b>Текущий баланс:</b></h3>" + am +
                             "<h3><b>Процент:</b></h3>"+QString::number(cFind[i]->getcard()->getPercent());
                }
                ui->textEdit->setHtml(HTMLText);
            }
        }
    }
    else if(ui->radioButton->isChecked())
    {
        ui->tableWidget->setRowCount(0);
        if(ui->comboBox->itemData(ui->comboBox->currentIndex()).toString()=="None"){
            if(ui->comboBox_2->itemData(ui->comboBox_2->currentIndex()).toString()=="all")
            {
                for(int i = 0; i < cFind.size(); i++)
                {
                    QString l = "false";
                    if(cFind[i]->getLgota()) l = "true";

                    int  j = ui->tableWidget->rowCount();
                    ui->tableWidget->setRowCount(j+1);

                    QTableWidgetItem* item = new QTableWidgetItem();
                    item->setText(cFind[i]->getFIO());
                    ui->tableWidget->setItem(j, 0, item);
                    item = new QTableWidgetItem();
                    item->setText(QString::number(cFind[i]->getBirthday().getDay())+"-"+QString::number(cFind[i]->getBirthday().getMonth())+"-"+QString::number(cFind[i]->getBirthday().getYear()));
                    ui->tableWidget->setItem(j, 1, item);
                    item = new QTableWidgetItem();
                    item->setText(QString::number(cFind[i]->getcard()->getNumber()));
                    ui->tableWidget->setItem(j, 2, item);
                    item = new QTableWidgetItem();
                    item->setText(cFind[i]->getcard()->type());
                    ui->tableWidget->setItem(j, 3, item);
                    item = new QTableWidgetItem();
                    item->setText(cFind[i]->gettel());
                    ui->tableWidget->setItem(j, 4, item);
                    item = new QTableWidgetItem();
                    item->setText(l);
                    ui->tableWidget->setItem(j, 5, item);
                }
            }
        }
        else if(ui->comboBox->itemData(ui->comboBox->currentIndex()).toString()=="cre")
        {
            QVector<Client*>c;
            for(int i = 0; i < cFind.size(); i++)
            {
                if(cFind[i]->getcard()->type()=="credit")
                    c.push_back(cFind[i]);
            }
            Client* temp;
            for(int i = 0; i < c.size()-1; i++)
            {
                for (int j = 0; j < c.size() - i - 1; j++) {
                           if (c[j]->getcard() < c[j + 1]->getcard()) {
                               temp = new Client(c[j]);
                               c[j] = c[j + 1];
                               c[j + 1] = temp;
                           }
                       }

            }


            for(int i = 0; i < c.size(); i++)
            {
                QString l = "false";
                if(c[i]->getLgota()) l = "true";

                int  j = ui->tableWidget->rowCount();
                ui->tableWidget->setRowCount(j+1);

                QTableWidgetItem* item = new QTableWidgetItem();
                item->setText(c[i]->getFIO());
                ui->tableWidget->setItem(j, 0, item);
                item = new QTableWidgetItem();
                item->setText(QString::number(c[i]->getBirthday().getDay())+"-"+QString::number(c[i]->getBirthday().getMonth())+"-"+QString::number(c[i]->getBirthday().getYear()));
                ui->tableWidget->setItem(j, 1, item);
                item = new QTableWidgetItem();
                item->setText(QString::number(c[i]->getcard()->getNumber()));
                ui->tableWidget->setItem(j, 2, item);
                item = new QTableWidgetItem();
                item->setText(c[i]->getcard()->type());
                ui->tableWidget->setItem(j, 3, item);
                item = new QTableWidgetItem();
                item->setText(c[i]->gettel());
                ui->tableWidget->setItem(j, 4, item);
                item = new QTableWidgetItem();
                item->setText(l);
                ui->tableWidget->setItem(j, 5, item);
            }

        }
        if(ui->fio->isChecked())
        {

        }
    }
}
