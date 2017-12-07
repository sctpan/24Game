#ifndef SOLOLOGIN_H
#define SOLOLOGIN_H
#include <QDialog>

namespace Ui {
class SoloLogin;
}

class SoloLogin : public QDialog
{
    Q_OBJECT

public:
    explicit SoloLogin(QWidget *parent = 0);
    ~SoloLogin();
    void return_menu();
    void login();
    void enter_register_mode();
    bool read_info(QVector<QString> &,QVector<QString> &);


private:
    Ui::SoloLogin *ui;
};

#endif // SOLOLOGIN_H
