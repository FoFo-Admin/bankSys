#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "client.h"
#include "addclient.h"
#include <QVector>
#include "Date.h"
#include "card.h"
#include "deposit.h"
#include "credit.h"
#include "debit.h"
#include "findclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_4_triggered();
    void on_action_triggered();

signals:
    void sendData(QVector<Client*> cl);

private:
    Ui::MainWindow *ui;
    QSqlDatabase database;

    QVector<Client*> clients;
    AddClient* addC;

    findClient * fc;
    bool Connect();
    void downloadAll();
};
#endif // MAINWINDOW_H
