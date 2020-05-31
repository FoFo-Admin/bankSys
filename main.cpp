#include "mainwindow.h"
#include "exeption.h"
#include <QMessageBox>
#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>
#include <QFile>
#include <QApplication>
#include <QFileDialog>
#include <QUrl>
#include <QDebug>
#include "delclient.h"

int main(int argc, char *argv[])
{

        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();

}
