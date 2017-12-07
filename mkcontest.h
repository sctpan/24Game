#ifndef MKCONTEST_H
#define MKCONTEST_H
#include <QDialog>
#include <QTimer>
namespace Ui {
class MkContest;
}

class MkContest : public QDialog
{
    Q_OBJECT
public:
    explicit MkContest(QWidget *parent = nullptr);

private slots:
    void make_contest();
private:
    Ui::MkContest *ui;
    int cards[4];
    void getCards(int);
};

#endif // MKCONTEST_H
