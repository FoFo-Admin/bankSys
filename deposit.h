#ifndef DEPOSIT_H
#define DEPOSIT_H
#include "card.h"


class deposit:public Card
{
    float depositAmount;
    int depositPercent;
public:
    deposit(int number, float balance, float depositAmount, int depositPercent);

    float getAmount();
    int getPercent();

    void changeDeposit();
    void changeBalance();
    QString type();
};

#endif // DEPOSIT_H
