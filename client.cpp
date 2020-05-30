#include "client.h"

Client::Client(QString FIO, Date Birthday, bool Lgota, QString tel, Card* card)
{
    this->FIO = FIO;
    this->Birthday = Birthday;
    this->Lgota = Lgota;
    this->tel = tel;
    if(card->type() == "debit")
    {
        this->card = new Debit(card->getNumber(), card->getBalance());
    }
    else if(card->type() == "credit")
    {
        this->card = new Credit(card->getNumber(), card->getBalance(), card->getAmount(), card->getPercent());
    }
    else if(card->type() == "deposit")
    {
        this->card = new deposit(card->getNumber(), card->getBalance(), card->getAmount(), card->getPercent());
    }
}

const QString Client::getFIO()
{
    return this->FIO;
}
void Client::setFIO(QString fio)
{
    this->FIO = fio;
}
Date Client::getBirthday()
{
    return this->Birthday;
}
void Client::setDate(Date d)
{
    this->Birthday = d;
}
bool Client::getLgota()
{
    return this->Lgota;
}
void Client::setLgota(bool lg)
{
    this->Lgota = lg;
}
const QString Client::gettel()
{
    return this->tel;
}
void Client::settel(QString tel)
{
    this->tel = tel;
}
Card* Client::getcard()
{
    return this->card;
}
