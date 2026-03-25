#include "calculator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Calculator");
    a.setApplicationVersion("1.0.0");
    a.setOrganizationName("ZouYunzhi");
    a.setOrganizationDomain("ZouYunzhi.com");
    Calculator w;
    w.show();
    return a.exec();
}
