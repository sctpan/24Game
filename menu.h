#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0,QString name = "null");
    explicit Menu(QString mode,QWidget *parent = 0,QString name = "null");
    ~Menu();
    void enter_solo_mode();
    void enter_rank_mode();
    void enter_multi_mode();
    void enter_instruction_mode();
    void return_login();
    void exit();
private slots:
    void detect();
private:
    Ui::Menu *ui;
    QString username;
    QTimer *timer;
    bool flag;
};

#endif // MENU_H
