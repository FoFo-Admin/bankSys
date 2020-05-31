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

void deposit::setAmount(float money)
{
    this->depositAmount = money;
}

bool deposit::operator==(const deposit & obj)const&
{
    if (this->depositAmount == obj.depositAmount)
        return true;
    else
        return false;
}

bool deposit::operator!=(const deposit & obj)const&
{
    return !(*this == obj);
}

bool deposit::operator>(const deposit & obj)const&
{
    if (this->depositAmount > obj.depositAmount)
        return true;
    return false;
}

bool deposit::operator<(const deposit & obj)const&
{
    return !( *this > obj) && *this != obj;
}

bool deposit::operator>=(const deposit & obj)const&
{
    return *this > obj || *this == obj;
}

bool deposit::operator<=(const deposit & obj)const&
{
    return *this < obj || *this == obj;
}

