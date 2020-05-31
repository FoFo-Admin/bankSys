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

void Credit::setAmount(float money)
{
    this->creditAmount=money;
}

bool Credit::operator==(const Credit & obj)const&
{
    if (this->creditAmount == obj.creditAmount)
        return true;
    else
        return false;
}

bool Credit::operator!=(const Credit & obj)const&
{
    return !(*this == obj);
}

bool Credit::operator>(const Credit & obj)const&
{
    if (this->creditAmount > obj.creditAmount)
        return true;
    return false;
}

bool Credit::operator<(const Credit & obj)const&
{
    return !( *this > obj) && *this != obj;
}

bool Credit::operator>=(const Credit & obj)const&
{
    return *this > obj || *this == obj;
}

bool Credit::operator<=(const Credit & obj)const&
{
    return *this < obj || *this == obj;
}

