#include "procwatcher.h"
#include <QApplication>

int main (int argc, char* argv[]) {
    QApplication a (argc, argv);
    ProcWatcher w;
    w.initTree ();
    w.show ();

    return a.exec ();
}
