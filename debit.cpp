#include "debit.h"

Debit::Debit(int number, float balance):Card(number, balance)
{

}

QString Debit::type()
{
    return "debit";
}

void Debit::changeBalance()
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
