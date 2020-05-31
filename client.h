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
    Client(Client* obj);
    //аксессоры
    const QString getFIO() const;
    void setFIO(QString fio);
    Date getBirthday() const;
    void setDate(Date d);
    bool getLgota() const;
    void setLgota(bool lg);
    const QString gettel() const;
    void settel(QString tel);
    Card* getcard() const;


    Client& operator = (const Client& obj);
};

#endif // CLIENT_H
