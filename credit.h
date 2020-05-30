#ifndef CREDIT_H
#define CREDIT_H
#include "card.h"


class Credit:public Card
{
    float creditAmount;
    int creditPercent;
public:
    Credit(int number, float balance, float creditAmount, int creditPercent);

    float getAmount();
    int getPercent();

    void changeBalance();
    void changeCredit();
    QString type();
};

#endif // CREDIT_H
