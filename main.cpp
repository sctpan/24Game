#include "solologin.h"
#include <QApplication>
#include <QLabel>
#include "QFile.h"
#include "QTextStream.h"

void inti()
{
    QFile f1("./username.txt");
    QFile f2("./password.txt");
    QFile f3("./score.txt");
    QFile f4("./time.txt");
    QFile f5("./contest.txt");
    f1.open(QIODevice::WriteOnly|QIODevice::Append);
    f2.open(QIODevice::WriteOnly|QIODevice::Append);
    f3.open(QIODevice::WriteOnly|QIODevice::Append);
    f4.open(QIODevice::WriteOnly|QIODevice::Append);
    f5.open(QIODevice::WriteOnly|QIODevice::Append);
    f1.close();
    f2.close();
    f3.close();
    f4.close();
    f5.close();
}
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    inti();
    SoloLogin sl;
    sl.exec();
    return app.exec();
}
