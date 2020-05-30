#ifndef CARD_H
#define CARD_H
#include <QString>

class Card
{
protected:
    int number;
    float balance;
public:
    Card(int number, float balance);

    int getNumber();
    float getBalance();

    virtual void changeBalance()=0;
    virtual QString type()=0;

    virtual float getAmount()=0;
    virtual int getPercent()=0;
};

#endif // CARD_H
