#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include "Date.h"
#include "card.h"
#include "deposit.h"
#include "credit.h"
#include "debit.h"
#include <QVector>

class Client
{
    QString FIO;
    Date Birthday;
    bool Lgota;
    QString tel;
    QVector <Card*> card;

    bool active;
public:
    Client( QString FIO, Date Birthday, bool Lgota, QString tel, QVector<Card*> card);
};

#endif // CLIENT_H
