#ifndef DEBIT_H
#define DEBIT_H
#include "card.h"

class Debit:public Card
{
public:
    Debit(int number, float balance);

    QString type();
    float getAmount();
    int getPercent();
    void setAmount(float money);
};

#endif // DEBIT_H
