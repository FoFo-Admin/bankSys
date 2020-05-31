#include "debit.h"

Debit::Debit(int number, float balance):Card(number, balance)
{

}

QString Debit::type()
{
    return "debit";
}

void Debit::setAmount(float money)
{

}

float Debit::getAmount()
{
   return 0.0;
}
int Debit::getPercent()
{
    return 0;
}

bool Debit::operator==(const Debit & obj)const&
{
    if (this->balance == obj.balance)
        return true;
    else
        return false;
}

bool Debit::operator!=(const Debit & obj)const&
{
    return !(*this == obj);
}

bool Debit::operator>(const Debit & obj)const&
{
    if (this->balance > obj.balance)
        return true;
    return false;
}

bool Debit::operator<(const Debit & obj)const&
{
    return !( *this > obj) && *this != obj;
}

bool Debit::operator>=(const Debit & obj)const&
{
    return *this > obj || *this == obj;
}

bool Debit::operator<=(const Debit & obj)const&
{
    return *this < obj || *this == obj;
}
