#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QUrl>
#include <QDebug>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_manager = new QNetworkAccessManager(this);
    addC = new AddClient();
    fc = new findClient();
    del = new delclient();
    update = new updateClient();
    Connect();
    downloadAll();
    connect(this,SIGNAL(sendData(QVector<Client*>)),fc, SLOT(getData(QVector<Client*>)));
    connect(del,SIGNAL(sendData(QString, QString)),this, SLOT(delData(QString, QString)));
    connect(update,SIGNAL(sendData()),this, SLOT(updateData()));
    connect(addC,SIGNAL(sendData(Client*)),this, SLOT(updateData()));

    ui->label_4->hide();
    ui->lineEdit_3->hide();
}

void MainWindow::delData(QString tel, QString number)
{
    QMutableVectorIterator<Client*> i(clients);

    while(i.hasNext()) {
        Client* current=i.next();

        if(current->gettel() == tel
        && current->getcard()->getNumber() == number)
        i.remove();
    }
}

void MainWindow::updateData()
{
    clients.clear();

    QSqlQuery query;
    query.exec("SELECT Name+' '+Surname+' '+MiddleName, YEAR(Birth), MONTH(Birth), DAY(Birth), Tel, Lgota, Card_id  FROM Customer;");

    while(query.next())
    {
        QSqlQuery tmpquery;
        tmpquery.exec("SELECT Type.Name, money, Credit, Deposit FROM Card, Type WHERE Card.id = "+query.value(6).toString()+" AND Card.Type_id = Type.id;");
        while(tmpquery.next())
        {
            Date date(query.value(1).toInt(), query.value(2).toInt(), query.value(3).toInt());
            float lg = false;
            if(query.value(5).toInt()==1)
                lg = true;
         QString type = tmpquery.value(0).toString();
         if(tmpquery.value(0).toString()=="Debit")
            {
              Card* card = new Debit(query.value(6).toInt(), tmpquery.value(1).toFloat());
              clients.push_back(new Client(query.value(0).toString(), date, lg, query.value(4).toString(), card));
         }
         else if(tmpquery.value(0).toString()=="Credit")
         {
                Card* card = new Credit(query.value(6).toInt(), tmpquery.value(1).toFloat(), tmpquery.value(2).toFloat(), 25);
                clients.push_back(new Client(query.value(0).toString(), date, lg, query.value(4).toString(), card));

         }
         else if(tmpquery.value(0).toString()=="Deposit")
         {
             Card* card = new deposit(query.value(6).toInt(), tmpquery.value(1).toFloat(), tmpquery.value(3).toFloat(), 14);
             clients.push_back(new Client(query.value(0).toString(), date, lg, query.value(4).toString(), card));

         }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;

    database.close();
}

bool MainWindow::Connect()
{
    database = QSqlDatabase::addDatabase("QODBC");

    QString connectingString = "Driver={SQL Server};";
    connectingString += "Server=FOFO_PC;";
    connectingString += "Database=bank;";

    database.setDatabaseName(connectingString);
    bool res = database.open();

    if(res) ui->label->setText("База данных подключенна");
    else ui->label->setText("Потерянно подключение к банковской базе");


    return res;
}

void MainWindow::downloadAll()
{
    QSqlQuery query;
    query.exec("SELECT Name+' '+Surname+' '+MiddleName, YEAR(Birth), MONTH(Birth), DAY(Birth), Tel, Lgota, Card_id  FROM Customer;");

    while(query.next())
    {
        QSqlQuery tmpquery;
        tmpquery.exec("SELECT Type.Name, money, Credit, Deposit FROM Card, Type WHERE Card.id = "+query.value(6).toString()+" AND Card.Type_id = Type.id;");
        while(tmpquery.next())
        {
            Date date(query.value(1).toInt(), query.value(2).toInt(), query.value(3).toInt());
            float lg = false;
            if(query.value(5).toInt()==1)
                lg = true;
         QString type = tmpquery.value(0).toString();
         if(tmpquery.value(0).toString()=="Debit")
            {
              Card* card = new Debit(query.value(6).toInt(), tmpquery.value(1).toFloat());
              clients.push_back(new Client(query.value(0).toString(), date, lg, query.value(4).toString(), card));
         }
         else if(tmpquery.value(0).toString()=="Credit")
         {
                Card* card = new Credit(query.value(6).toInt(), tmpquery.value(1).toFloat(), tmpquery.value(2).toFloat(), 25);
                clients.push_back(new Client(query.value(0).toString(), date, lg, query.value(4).toString(), card));

         }
         else if(tmpquery.value(0).toString()=="Deposit")
         {
             Card* card = new deposit(query.value(6).toInt(), tmpquery.value(1).toFloat(), tmpquery.value(3).toFloat(), 14);
             clients.push_back(new Client(query.value(0).toString(), date, lg, query.value(4).toString(), card));

         }
        }
    }
}


void MainWindow::on_action_4_triggered()
{
    addC->show();
}

void MainWindow::on_action_triggered()
{
    emit sendData(clients);
    fc->show();
}


void MainWindow::on_action_8_triggered()
{
    del->show();
}

void MainWindow::on_action_2_triggered()
{
    update->show();
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->radioButton->isChecked())
    {
        if(ui->lineEdit_2->text().toInt() > 0)
        {
            for (int i = 0;i < clients.size();i++) {
                if(clients[i]->getcard()->getNumber() == ui->lineEdit->text().toInt())
                {
                    if(clients[i]->getcard()->getBalance()-ui->lineEdit_2->text().toInt()>=0)
                    {
                    clients[i]->getcard()->setBalance(clients[i]->getcard()->getBalance()-ui->lineEdit_2->text().toInt());

                    QSqlQuery query;
                    query.exec("update Card set Money = "+QString::number(clients[i]->getcard()->getBalance())+" where id = "+ui->lineEdit->text()+";");

                    Date a;
                    QTime t;

                    ofstream oppa(ui->lineEdit->text().toUtf8()+QString::number(a.getYear()).toUtf8()+QString::number(a.getMonth()).toUtf8()+QString::number(a.getDay()).toUtf8()+QString::number(t.currentTime().hour()).toUtf8()+QString::number(t.currentTime().minute()).toUtf8()+QString::number(t.currentTime().second()).toUtf8()+".html");
                    oppa << "<h1>КВИТАНЦИЯ ШПАКОБАНК №"<<ui->lineEdit->text().toInt()<<a.getYear()<<a.getMonth()<<a.getDay()<<t.currentTime().hour()<<t.currentTime().minute()<<t.currentTime().second()<<"</h1><br><h2><b>Операция:</b></h2><p>Снятие средств</p><br><h2><b>Размер снятия:</b></h2><p>"<<ui->lineEdit_2->text().toInt()<<"</p><br><h2><b>Номер карты:</b></h2><p>"<<ui->lineEdit->text().toInt()<<"</p><br>";
                    oppa.close();

                    QMessageBox msgBox;
                    msgBox.setText("Квитанция созданна под номером " + ui->lineEdit->text().toUtf8()+QString::number(a.getYear()).toUtf8()+QString::number(a.getMonth()).toUtf8()+QString::number(a.getDay()).toUtf8()+QString::number(t.currentTime().hour()).toUtf8()+QString::number(t.currentTime().minute()).toUtf8()+QString::number(t.currentTime().second()).toUtf8()+".html");
                    msgBox.exec();
                    }
                }
            }
        }
    }
    if(ui->radioButton_2->isChecked())
    {
        if(ui->lineEdit_2->text().toInt() > 0)
        {
            for (int i = 0;i < clients.size();i++) {
                if(clients[i]->getcard()->getNumber() == ui->lineEdit->text().toInt())
                {
                    clients[i]->getcard()->setBalance(clients[i]->getcard()->getBalance()+ui->lineEdit_2->text().toInt());

                    QSqlQuery query;
                    query.exec("update Card set Money = "+QString::number(clients[i]->getcard()->getBalance())+" where id = "+ui->lineEdit->text()+";");

                    Date a;
                    QTime t;

                    ofstream oppa(ui->lineEdit->text().toUtf8()+QString::number(a.getYear()).toUtf8()+QString::number(a.getMonth()).toUtf8()+QString::number(a.getDay()).toUtf8()+QString::number(t.currentTime().hour()).toUtf8()+QString::number(t.currentTime().minute()).toUtf8()+QString::number(t.currentTime().second()).toUtf8()+".html");
                    oppa << "<h1>КВИТАНЦИЯ ШПАКОБАНК №"<<ui->lineEdit->text().toInt()<<a.getYear()<<a.getMonth()<<a.getDay()<<t.currentTime().hour()<<t.currentTime().minute()<<t.currentTime().second()<<"</h1><br><h2><b>Операция:</b></h2><p>Пополнение</p><br><h2><b>Размер пополнения:</b></h2><p>"<<ui->lineEdit_2->text().toInt()<<"</p><br><h2><b>Номер карты:</b></h2><p>"<<ui->lineEdit->text().toInt()<<"</p><br>";
                    oppa.close();

                    QMessageBox msgBox;
                    msgBox.setText("Квитанция созданна под номером " + ui->lineEdit->text().toUtf8()+QString::number(a.getYear()).toUtf8()+QString::number(a.getMonth()).toUtf8()+QString::number(a.getDay()).toUtf8()+QString::number(t.currentTime().hour()).toUtf8()+QString::number(t.currentTime().minute()).toUtf8()+QString::number(t.currentTime().second()).toUtf8()+".html");
                    msgBox.exec();
                }
            }
        }
    }
    if(ui->radioButton_3->isChecked())
    {
        if(ui->lineEdit_2->text().toInt() > 0)
        {
            for (int i = 0;i < clients.size();i++) {
                if(clients[i]->getcard()->getNumber() == ui->lineEdit->text().toInt())
                {
                    if(clients[i]->getcard()->type()=="deposit")
                    {
                        if(clients[i]->getcard()->getBalance() - ui->lineEdit_2->text().toInt() >= 0)
                       {
                            clients[i]->getcard()->setBalance(clients[i]->getcard()->getBalance()-ui->lineEdit_2->text().toInt());
                            clients[i]->getcard()->setAmount(clients[i]->getcard()->getAmount()+ui->lineEdit_2->text().toInt());

                            QSqlQuery query;
                            query.exec("update Card set Money = "+QString::number(clients[i]->getcard()->getBalance())+", Deposit = "+QString::number(clients[i]->getcard()->getAmount())+" where id = "+ui->lineEdit->text()+";");

                            Date a;
                            QTime t;

                            ofstream oppa(ui->lineEdit->text().toUtf8()+QString::number(a.getYear()).toUtf8()+QString::number(a.getMonth()).toUtf8()+QString::number(a.getDay()).toUtf8()+QString::number(t.currentTime().hour()).toUtf8()+QString::number(t.currentTime().minute()).toUtf8()+QString::number(t.currentTime().second()).toUtf8()+".html");
                            oppa << "<h1>КВИТАНЦИЯ ШПАКОБАНК №"<<ui->lineEdit->text().toInt()<<a.getYear()<<a.getMonth()<<a.getDay()<<t.currentTime().hour()<<t.currentTime().minute()<<t.currentTime().second()<<"</h1><br><h2><b>Операция:</b></h2><p>Пополнение депозита</p><br><h2><b>Размер пополнения:</b></h2><p>"<<ui->lineEdit_2->text().toInt()<<"</p><br><h2><b>Номер карты:</b></h2><p>"<<ui->lineEdit->text().toInt()<<"</p><br>";
                            oppa.close();

                            QMessageBox msgBox;
                            msgBox.setText("Квитанция созданна под номером " + ui->lineEdit->text().toUtf8()+QString::number(a.getYear()).toUtf8()+QString::number(a.getMonth()).toUtf8()+QString::number(a.getDay()).toUtf8()+QString::number(t.currentTime().hour()).toUtf8()+QString::number(t.currentTime().minute()).toUtf8()+QString::number(t.currentTime().second()).toUtf8()+".html");
                            msgBox.exec();
                        }
                    }
                }
            }
        }
    }
    if(ui->radioButton_4->isChecked())
    {
        if(ui->lineEdit_2->text().toInt() > 0)
        {
            for (int i = 0;i < clients.size();i++) {
                if(clients[i]->getcard()->getNumber() == ui->lineEdit->text().toInt())
                {
                    if(clients[i]->getcard()->type()=="credit")
                    {
                        if(clients[i]->getcard()->getBalance() - ui->lineEdit_2->text().toInt() >= 0)
                       {
                            if(clients[i]->getcard()->getAmount() - ui->lineEdit_2->text().toInt() >= 0)
                            {
                                clients[i]->getcard()->setBalance(clients[i]->getcard()->getBalance()-ui->lineEdit_2->text().toInt());
                                clients[i]->getcard()->setAmount(clients[i]->getcard()->getAmount()-ui->lineEdit_2->text().toInt());

                                QSqlQuery query;
                                query.exec("update Card set Money = "+QString::number(clients[i]->getcard()->getBalance())+", Credit = "+QString::number(clients[i]->getcard()->getAmount())+" where id = "+ui->lineEdit->text()+";");

                                Date a;
                                QTime t;

                                ofstream oppa(ui->lineEdit->text().toUtf8()+QString::number(a.getYear()).toUtf8()+QString::number(a.getMonth()).toUtf8()+QString::number(a.getDay()).toUtf8()+QString::number(t.currentTime().hour()).toUtf8()+QString::number(t.currentTime().minute()).toUtf8()+QString::number(t.currentTime().second()).toUtf8()+".html");
                                oppa << "<h1>КВИТАНЦИЯ ШПАКОБАНК №"<<ui->lineEdit->text().toInt()<<a.getYear()<<a.getMonth()<<a.getDay()<<t.currentTime().hour()<<t.currentTime().minute()<<t.currentTime().second()<<"</h1><br><h2><b>Операция:</b></h2><p>Погашение задолжности</p><br><h2><b>Размер пополнения:</b></h2><p>"<<ui->lineEdit_2->text().toInt()<<"</p><br><h2><b>Номер карты:</b></h2><p>"<<ui->lineEdit->text().toInt()<<"</p><br>";
                                oppa.close();

                                QMessageBox msgBox;
                                msgBox.setText("Квитанция созданна под номером " + ui->lineEdit->text().toUtf8()+QString::number(a.getYear()).toUtf8()+QString::number(a.getMonth()).toUtf8()+QString::number(a.getDay()).toUtf8()+QString::number(t.currentTime().hour()).toUtf8()+QString::number(t.currentTime().minute()).toUtf8()+QString::number(t.currentTime().second()).toUtf8()+".html");
                                msgBox.exec();
                            }
                        }
                    }
                }
            }
        }
    }
    if(ui->radioButton_5->isChecked())
    {
        if(ui->lineEdit_2->text().toInt() > 0)
        {
            for (int i = 0;i < clients.size();i++) {
                if(clients[i]->getcard()->getNumber() == ui->lineEdit->text().toInt())
                {
                    for (int j = 0;j < clients.size();j++)
                    {
                        if(clients[j]->getcard()->getNumber() == ui->lineEdit_3->text().toInt())
                        {
                            if(clients[i]->getcard()->getBalance() - ui->lineEdit_2->text().toInt() >= 0)
                            {

                                    clients[i]->getcard()->setBalance(clients[i]->getcard()->getBalance()-ui->lineEdit_2->text().toInt());
                                    clients[j]->getcard()->setBalance(clients[j]->getcard()->getBalance()+ui->lineEdit_2->text().toInt());

                                    QSqlQuery query;
                                    query.exec("update Card set Money = "+QString::number(clients[i]->getcard()->getBalance())+" where id = "+ui->lineEdit->text()+";");

                                    QSqlQuery query2;
                                    query2.exec("update Card set Money = "+QString::number(clients[j]->getcard()->getBalance())+" where id = "+ui->lineEdit_3->text()+";");

                                    Date a;
                                    QTime t;

                                    ofstream oppa(ui->lineEdit->text().toUtf8()+QString::number(a.getYear()).toUtf8()+QString::number(a.getMonth()).toUtf8()+QString::number(a.getDay()).toUtf8()+QString::number(t.currentTime().hour()).toUtf8()+QString::number(t.currentTime().minute()).toUtf8()+QString::number(t.currentTime().second()).toUtf8()+".html");
                                    oppa << "<h1>КВИТАНЦИЯ ШПАКОБАНК №"<<ui->lineEdit->text().toInt()<<a.getYear()<<a.getMonth()<<a.getDay()<<t.currentTime().hour()<<t.currentTime().minute()<<t.currentTime().second()<<"</h1><br><h2><b>Операция:</b></h2><p>Перевод средств</p><br><h2><b>Размер перевода:</b></h2><p>"<<ui->lineEdit_2->text().toInt()<<"</p><br><h2><b>Номер карты отправителя:</b></h2><p>"<<ui->lineEdit->text().toInt()<<"</p><br>"<<"<h2><b>Номер карты получателя:</b></h2><p>"<<ui->lineEdit_3->text().toInt()<<"</p><br>";
                                    oppa.close();

                                    QMessageBox msgBox;
                                    msgBox.setText("Квитанция созданна под номером " + ui->lineEdit->text().toUtf8()+QString::number(a.getYear()).toUtf8()+QString::number(a.getMonth()).toUtf8()+QString::number(a.getDay()).toUtf8()+QString::number(t.currentTime().hour()).toUtf8()+QString::number(t.currentTime().minute()).toUtf8()+QString::number(t.currentTime().second()).toUtf8()+".html");
                                    msgBox.exec();
                             }

                        }
                    }
                }
            }
        }
    }
    if(ui->radioButton_6->isChecked())
    {
        if(ui->lineEdit_2->text().toInt() > 0)
        {
            for (int i = 0;i < clients.size();i++) {
                if(clients[i]->getcard()->getNumber() == ui->lineEdit->text().toInt())
                {
                    if(clients[i]->getcard()->type()=="deposit")
                    {
                            if(clients[i]->getcard()->getAmount() - ui->lineEdit_2->text().toInt() >= 0)
                            {
                                clients[i]->getcard()->setBalance(clients[i]->getcard()->getBalance()+ui->lineEdit_2->text().toInt());
                                clients[i]->getcard()->setAmount(clients[i]->getcard()->getAmount()-ui->lineEdit_2->text().toInt());

                                QSqlQuery query;
                                query.exec("update Card set Money = "+QString::number(clients[i]->getcard()->getBalance())+", Deposit = "+QString::number(clients[i]->getcard()->getAmount())+" where id = "+ui->lineEdit->text()+";");

                                Date a;
                                QTime t;

                                ofstream oppa(ui->lineEdit->text().toUtf8()+QString::number(a.getYear()).toUtf8()+QString::number(a.getMonth()).toUtf8()+QString::number(a.getDay()).toUtf8()+QString::number(t.currentTime().hour()).toUtf8()+QString::number(t.currentTime().minute()).toUtf8()+QString::number(t.currentTime().second()).toUtf8()+".html");
                                oppa << "<h1>КВИТАНЦИЯ ШПАКОБАНК №"<<ui->lineEdit->text().toInt()<<a.getYear()<<a.getMonth()<<a.getDay()<<t.currentTime().hour()<<t.currentTime().minute()<<t.currentTime().second()<<"</h1><br><h2><b>Операция:</b></h2><p>Снятие депозитных средств</p><br><h2><b>Размер пополнения:</b></h2><p>"<<ui->lineEdit_2->text().toInt()<<"</p><br><h2><b>Номер карты:</b></h2><p>"<<ui->lineEdit->text().toInt()<<"</p><br>";
                                oppa.close();

                                QMessageBox msgBox;
                                msgBox.setText("Квитанция созданна под номером " + ui->lineEdit->text().toUtf8()+QString::number(a.getYear()).toUtf8()+QString::number(a.getMonth()).toUtf8()+QString::number(a.getDay()).toUtf8()+QString::number(t.currentTime().hour()).toUtf8()+QString::number(t.currentTime().minute()).toUtf8()+QString::number(t.currentTime().second()).toUtf8()+".html");
                                msgBox.exec();
                            }
                        }

                }
            }
        }
    }
    if(ui->radioButton_7->isChecked())
    {
        if(ui->lineEdit_2->text().toInt() > 0)
        {
            for (int i = 0;i < clients.size();i++) {
                if(clients[i]->getcard()->getNumber() == ui->lineEdit->text().toInt())
                {
                    if(clients[i]->getcard()->type()=="credit")
                    {
                                clients[i]->getcard()->setBalance(clients[i]->getcard()->getBalance()+ui->lineEdit_2->text().toInt());
                                clients[i]->getcard()->setAmount(clients[i]->getcard()->getAmount()+ui->lineEdit_2->text().toInt());

                                QSqlQuery query;
                                query.exec("update Card set Money = "+QString::number(clients[i]->getcard()->getBalance())+", Credit = "+QString::number(clients[i]->getcard()->getAmount())+" where id = "+ui->lineEdit->text()+";");

                                Date a;
                                QTime t;

                                ofstream oppa(ui->lineEdit->text().toUtf8()+QString::number(a.getYear()).toUtf8()+QString::number(a.getMonth()).toUtf8()+QString::number(a.getDay()).toUtf8()+QString::number(t.currentTime().hour()).toUtf8()+QString::number(t.currentTime().minute()).toUtf8()+QString::number(t.currentTime().second()).toUtf8()+".html");
                                oppa << "<h1>КВИТАНЦИЯ ШПАКОБАНК №"<<ui->lineEdit->text().toInt()<<a.getYear()<<a.getMonth()<<a.getDay()<<t.currentTime().hour()<<t.currentTime().minute()<<t.currentTime().second()<<"</h1><br><h2><b>Операция:</b></h2><p>Оформление кредита</p><br><h2><b>Размер пополнения:</b></h2><p>"<<ui->lineEdit_2->text().toInt()<<"</p><br><h2><b>Номер карты:</b></h2><p>"<<ui->lineEdit->text().toInt()<<"</p><br>";
                                oppa.close();

                                QMessageBox msgBox;
                                msgBox.setText("Квитанция созданна под номером " + ui->lineEdit->text().toUtf8()+QString::number(a.getYear()).toUtf8()+QString::number(a.getMonth()).toUtf8()+QString::number(a.getDay()).toUtf8()+QString::number(t.currentTime().hour()).toUtf8()+QString::number(t.currentTime().minute()).toUtf8()+QString::number(t.currentTime().second()).toUtf8()+".html");
                                msgBox.exec();
                            }


                }
            }
        }
    }
}

void MainWindow::on_radioButton_clicked()
{
    ui->label_4->hide();
    ui->lineEdit_3->hide();
}

void MainWindow::on_radioButton_2_clicked()
{
    ui->label_4->hide();
    ui->lineEdit_3->hide();
}

void MainWindow::on_radioButton_7_clicked()
{
    ui->label_4->hide();
    ui->lineEdit_3->hide();
}

void MainWindow::on_radioButton_6_clicked()
{
    ui->label_4->hide();
    ui->lineEdit_3->hide();
}

void MainWindow::on_radioButton_4_clicked()
{
    ui->label_4->hide();
    ui->lineEdit_3->hide();
}

void MainWindow::on_radioButton_5_clicked()
{
    ui->label_4->show();
    ui->lineEdit_3->show();
}

void MainWindow::on_radioButton_3_clicked()
{
    ui->label_4->hide();
    ui->lineEdit_3->hide();
}

void MainWindow::on_action_3_triggered()
{
    for(int i = 0; i < clients.size(); i++)
    {
        if(clients[i]->getcard()->type()=="credit")
        {
            if(clients[i]->getLgota())
            {
                clients[i]->getcard()->setAmount(clients[i]->getcard()->getAmount()+(((clients[i]->getcard()->getAmount() / 100)*(clients[i]->getcard()->getPercent()-5))/12));
            }
            else
            clients[i]->getcard()->setAmount(clients[i]->getcard()->getAmount()+(((clients[i]->getcard()->getAmount() / 100)*clients[i]->getcard()->getPercent())/12));

            QSqlQuery query;
            query.exec("update Card set Credit = "+QString::number(clients[i]->getcard()->getAmount())+" where id = "+QString::number(clients[i]->getcard()->getNumber())+";");
        }
        else if(clients[i]->getcard()->type()=="deposit")
        {
            if(clients[i]->getLgota())
            {
                clients[i]->getcard()->setAmount(clients[i]->getcard()->getAmount()+(((clients[i]->getcard()->getAmount() / 100)*(clients[i]->getcard()->getPercent()+5))/12));
            }
            else
            clients[i]->getcard()->setAmount(clients[i]->getcard()->getAmount()+(((clients[i]->getcard()->getAmount() / 100)*clients[i]->getcard()->getPercent())/12));

            QSqlQuery query;
            query.exec("update Card set Deposit = "+QString::number(clients[i]->getcard()->getAmount())+" where id = "+QString::number(clients[i]->getcard()->getNumber())+";");
        }
    }
}
