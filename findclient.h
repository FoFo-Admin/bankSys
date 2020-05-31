#ifndef FINDCLIENT_H
#define FINDCLIENT_H

#include <QDialog>
#include "client.h"
#include <QVector>
#include "Date.h"
#include "card.h"
#include "deposit.h"
#include "credit.h"
#include "debit.h"

namespace Ui {
class findClient;
}

class findClient : public QDialog
{
    Q_OBJECT

public:
    explicit findClient(QWidget *parent = nullptr);
    ~findClient();
    public slots:
    void getData(QVector<Client*> cl);


private slots:
    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::findClient *ui;
    QVector<Client*> cFind;
};

#endif // FINDCLIENT_H
