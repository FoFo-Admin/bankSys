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

    void setAmount(float money);
    QString type();

    //--------- Comparison operators ---------
    bool operator == (const Credit&  obj)const&;
    bool operator != (const Credit& obj)const&;
    bool operator > (const Credit& obj)const&;
    bool operator < (const Credit& obj)const&;
    bool operator >= (const Credit& obj)const&;
    bool operator <= (const Credit& obj)const&;
};

#endif // CREDIT_H
