#include "imclientdialog.h"
#include <QApplication>
#include "ckernel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    IMClientDialog w;
//    w.show();
    CKernel kernel;
    return a.exec();
}
