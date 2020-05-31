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
#include "delclient.h"
#include "updateclient.h"
#include <fstream>
#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>
#include <QFile>

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

    void on_action_8_triggered();

    void on_action_2_triggered();

    void on_pushButton_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_7_clicked();

    void on_radioButton_6_clicked();

    void on_radioButton_4_clicked();

    void on_radioButton_5_clicked();

    void on_radioButton_3_clicked();

    void on_action_3_triggered();

signals:
    void sendData(QVector<Client*> cl);

private:
    Ui::MainWindow *ui;
    QSqlDatabase database;
    QNetworkAccessManager *m_manager;

    void delData(QString tel, QString number);

    QVector<Client*> clients;
    AddClient* addC;
    delclient* del;
    updateClient* update;

    findClient * fc;
    QFile *m_file;

    void updateData();
    bool Connect();
    void downloadAll();
};
#endif // MAINWINDOW_H
