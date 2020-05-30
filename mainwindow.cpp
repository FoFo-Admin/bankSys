#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    addC = new AddClient();
    fc = new findClient();
    del = new delclient();
    Connect();
    downloadAll();
    connect(this,SIGNAL(sendData(QVector<Client*>)),fc, SLOT(getData(<Client*>)));
    connect(del,SIGNAL(sendData(QString, QString)),this, SLOT(delData(QString, QString)));
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
