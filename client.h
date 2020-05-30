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
    Card* card;

    bool active;
public:
    Client( QString FIO, Date Birthday, bool Lgota, QString tel, Card* card);

    //аксессоры
    const QString getFIO();
    void setFIO(QString fio);
    Date getBirthday();
    void setDate(Date d);
    bool getLgota();
    void setLgota(bool lg);
    const QString gettel();
    void settel(QString tel);
    Card* getcard();
};

#endif // CLIENT_H
