#include "card.h"

Card::Card(int number, float balance)
{
    this->number = number;
    this->balance = balance;
}

int Card::getNumber()
{
    return this->number;
}
float Card::getBalance()
{
    return this->balance;
}
void Card::setBalance(float money)
{
    this->balance = money;
}
