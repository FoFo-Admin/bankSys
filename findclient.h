#ifndef FINDCLIENT_H
#define FINDCLIENT_H

#include <QDialog>
#include "client.h"
#include "addclient.h"
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


private:
    Ui::findClient *ui;
};

#endif // FINDCLIENT_H
