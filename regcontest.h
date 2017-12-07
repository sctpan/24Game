#ifndef REGCONTEST_H
#define REGCONTEST_H

#include <QDialog>
namespace Ui {
class RegContest;
}

class RegContest : public QDialog
{
    Q_OBJECT
public:
    explicit RegContest(QWidget *parent = nullptr,QString name = NULL);
    ~RegContest();
    void register_contest();
    void return_menu();

private:
    Ui::RegContest *ui;
    QString username;
};

#endif // REGCONTEST_H
