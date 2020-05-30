#ifndef ADDCLIENT_H
#define ADDCLIENT_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "Date.h"

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

private:
    Ui::AddClient *ui;
};

#endif // ADDCLIENT_H
