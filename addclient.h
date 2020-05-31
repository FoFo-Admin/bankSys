#ifndef ADDCLIENT_H
#define ADDCLIENT_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "client.h"
#include <QVector>
#include "Date.h"
#include "card.h"
#include "deposit.h"
#include "credit.h"
#include "debit.h"

namespace Ui {
class AddClient;
}

class AddClient : public QDialog
{
    Q_OBJECT

public:
    explicit AddClient(QWidget *parent = nullptr);
    ~AddClient();

private slots:
    void on_pushButton_clicked();

signals:
    void sendData();

private:
    Ui::AddClient *ui;
};

#endif // ADDCLIENT_H
