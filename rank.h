#ifndef RANK_H
#define RANK_H
#include <QDialog>

namespace Ui {
class Rank;
}

class Rank : public QDialog
{
    Q_OBJECT
public:
    explicit Rank(QWidget *parent = nullptr,QString name = "null");
    void return_menu();
    void insult();
private:
    Ui::Rank *ui;
    QString username;
};

#endif // RANK_H
