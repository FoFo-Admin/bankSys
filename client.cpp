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
Client::Client(Client* obj)
{
    this->FIO = obj->getFIO();
    this->Birthday=obj->getBirthday();
    this->Lgota=obj->getLgota();
    this->tel=obj->gettel();
    this->card=obj->getcard();
}

const QString Client::getFIO() const
{
    return this->FIO;
}
void Client::setFIO(QString fio)
{
    this->FIO = fio;
}
Date Client::getBirthday() const
{
    return this->Birthday;
}
void Client::setDate(Date d)
{
    this->Birthday = d;
}
bool Client::getLgota() const
{
    return this->Lgota;
}
void Client::setLgota(bool lg)
{
    this->Lgota = lg;
}
const QString Client::gettel() const
{
    return this->tel;
}
void Client::settel(QString tel)
{
    this->tel = tel;
}
Card* Client::getcard() const
{
    return this->card;
}


Client & Client::operator=(const Client & obj)
{
    this->FIO = obj.getFIO();
    this->Birthday=obj.getBirthday();
    this->Lgota=obj.getLgota();
    this->tel=obj.gettel();
    this->card=obj.getcard();

    return *this;
}
