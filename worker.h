#ifndef WORKER_H
#define WORKER_H
#include <QString>
#include "Date.h"
#include "card.h"
#include "deposit.h"
#include "credit.h"


class worker
{
    QString FIO;
    Date Birthday;
    bool Lgota;
    QString tel;
    QString Job;
    float Salary;
    Card * card;

    bool active;
public:
    worker();
};

#endif // WORKER_H
