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

    void setAmount(float money);
    QString type();

    //--------- Comparison operators ---------
    bool operator == (const deposit&  obj)const&;
    bool operator != (const deposit& obj)const&;
    bool operator > (const deposit& obj)const&;
    bool operator < (const deposit& obj)const&;
    bool operator >= (const deposit& obj)const&;
    bool operator <= (const deposit& obj)const&;
};

#endif // DEPOSIT_H
