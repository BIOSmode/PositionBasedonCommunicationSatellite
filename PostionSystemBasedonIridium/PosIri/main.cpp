#include "positionsystem.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PositionSystem w;
    w.show();
    return a.exec();
}
