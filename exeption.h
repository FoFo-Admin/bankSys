#ifndef EXEPTION_H
#define EXEPTION_H
#include <QFileDialog>
#include <QUrl>
#include <QDebug>
#include <QMessageBox>


class Exeption
{
public:
    Exeption(){}
    ~Exeption(){}

    virtual QString SendError()=0;
};

class AccountHaveMoney : public Exeption
{
    int card;
    public:
    AccountHaveMoney(int card){
        this->card= card;
    }
    ~AccountHaveMoney(){}

     virtual QString SendError()
     {
         QString error =  QString::number(card) + " карта не пустая";

         return error;
     }
};

class NotExist : public Exeption
{
    public:
    NotExist(){
    }
    ~NotExist(){}

     virtual QString SendError()
     {
         QString error = "База прислала пустой ответ на ваш запрос";

         return error;
     }
};

class MaxCards : public Exeption
{
    QString tel;
    public:
    MaxCards(QString tel){
        this->tel = tel;
    }
    ~MaxCards(){}

     virtual QString SendError()
     {
         QString error = "Созданно максимальное колличество карт (5) для абонента с номером: " + this->tel;

         return error;
     }
};

class WrongMoney : public Exeption{
public:
WrongMoney(){
}
~WrongMoney(){}

 virtual QString SendError()
 {
     QString error = "Минимальное допустимое значение денежной еденицы - 1";

     return error;
 }
};

class NotMuch : public Exeption
{
    int card;
    public:
    NotMuch(int card){
        this->card= card;
    }
    ~NotMuch(){}

     virtual QString SendError()
     {
         QString error =  QString::number(card) + " на этой карте не хватает средств";

         return error;
     }
};

class NotDeposit : public Exeption
{
    int card;
    public:
    NotDeposit(int card){
        this->card= card;
    }
    ~NotDeposit(){}

     virtual QString SendError()
     {
         QString error =  QString::number(card) + " эта карта не депозитовая";

         return error;
     }
};

class NotCredit : public Exeption
{
    int card;
    public:
    NotCredit(int card){
        this->card= card;
    }
    ~NotCredit(){}

     virtual QString SendError()
     {
         QString error =  QString::number(card) + " эта карта не кредитная";

         return error;
     }
};

class tooDeposit : public Exeption
{
    int card;
    public:
    tooDeposit(int card){
        this->card= card;
    }
    ~tooDeposit(){}

     virtual QString SendError()
     {
         QString error =  QString::number(card) + " у вас не хватает средств на депозите";

         return error;
     }
};

class tooCredit : public Exeption
{
    int card;
    public:
    tooCredit(int card){
        this->card= card;
    }
    ~tooCredit(){}

     virtual QString SendError()
     {
         QString error =  QString::number(card) + " чтобы оплатить кредит вам необходимо меньше средств";

         return error;
     }
};


#endif // EXEPTION_H
