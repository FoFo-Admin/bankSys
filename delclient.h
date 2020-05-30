#ifndef DELCLIENT_H
#define DELCLIENT_H

#include <QDialog>

namespace Ui {
class delclient;
}

class delclient : public QDialog
{
    Q_OBJECT

public:
    explicit delclient(QWidget *parent = nullptr);
    ~delclient();

signals:
    void sendData(QString tel, QString number);

private slots:
    void on_pushButton_clicked();

private:
    Ui::delclient *ui;
};

#endif // DELCLIENT_H
