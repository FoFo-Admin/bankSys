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
    void setBalance(float money);

    virtual QString type()=0;

    virtual float getAmount()=0;
    virtual int getPercent()=0;
    virtual void setAmount(float money)=0;
};

#endif // CARD_H
