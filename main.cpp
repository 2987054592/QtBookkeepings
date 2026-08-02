#include <QApplication>
#include "mainwindow.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    qDebug() << "OpenSSL support:" << QSslSocket::supportsSsl();
    qDebug() << "OpenSSL version used:" << QSslSocket::sslLibraryBuildVersionString();
    MainWindow w;
    w.show();
    return QApplication::exec();
}
