#include <QApplication>
#include "bfruby.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BFRuby w;
    w.show();
    
    return a.exec();
}
