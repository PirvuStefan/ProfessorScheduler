#include <QApplication>

#include "../Headers/MainWindow.h"

// #016B61 #70B2B2 #9ECFD4 #E5E9C5
// color palette

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}
