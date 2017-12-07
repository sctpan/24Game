#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>
namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT
public:
    explicit Register(QWidget *parent = nullptr);
    void return_menu();
    void judge_info();
    bool save_info(QString,QString);
private:
    Ui::Register *ui;
};

#endif // REGISTER_H
