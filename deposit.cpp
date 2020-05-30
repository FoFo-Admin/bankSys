#include "deposit.h"

deposit::deposit(int number, float balance, float depositAmount, int depositPercent):Card(number, balance)
{
    this->depositAmount = depositAmount;
    this->depositPercent = depositPercent;
}

QString deposit::type()
{
    return "deposit";
}

float deposit::getAmount()
{
    return this->depositAmount;
}
int deposit::getPercent()
{
    return this->depositPercent;
}

void deposit::changeBalance()
{

}
