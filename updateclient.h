#ifndef UPDATECLIENT_H
#define UPDATECLIENT_H

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
class updateClient;
}

class updateClient : public QDialog
{
    Q_OBJECT

signals:
    void sendData();

public:
    explicit updateClient(QWidget *parent = nullptr);
    ~updateClient();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::updateClient *ui;
};

#endif // UPDATECLIENT_H
