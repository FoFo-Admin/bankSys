#include "credit.h"

Credit::Credit(int number, float balance, float creditAmount, int creditPercent):Card(number, balance)
{
    this->creditAmount = creditAmount;
    this->creditPercent = creditPercent;
}

QString Credit::type()
{
    return "credit";
}

float Credit::getAmount()
{
    return this->creditAmount;
}
int Credit::getPercent()
{
    return this->creditPercent;
}

void Credit::changeBalance()
{

}
