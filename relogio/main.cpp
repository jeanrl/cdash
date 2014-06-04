#include "wrelogio.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    wrelogio w;
    w.show();

    return a.exec();
}
