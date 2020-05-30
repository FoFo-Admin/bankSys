#ifndef DEBIT_H
#define DEBIT_H
#include "card.h"

class Debit:public Card
{
public:
    Debit(int number, float balance);

    void changeBalance();
    QString type();
    float getAmount();
    int getPercent();
};

#endif // DEBIT_H
