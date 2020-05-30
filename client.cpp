#include "client.h"

Client::Client(QString FIO, Date Birthday, bool Lgota, QString tel, QVector<Card*> card)
{
    this->FIO = FIO;
    this->Birthday = Birthday;
    this->Lgota = Lgota;
    this->tel = tel;
    if(card[0]->type() == "debit")
    {
        this->card.push_back(new Debit(card[0]->getNumber(), card[0]->getBalance()));
    }
    else if(card[0]->type() == "credit")
    {
        this->card.push_back(new Credit(card[0]->getNumber(), card[0]->getBalance(), card[0]->getAmount(), card[0]->getPercent()));
    }
    else if(card[0]->type() == "deposit")
    {
        this->card.push_back(new deposit(card[0]->getNumber(), card[0]->getBalance(), card[0]->getAmount(), card[0]->getPercent()));
    }
}
