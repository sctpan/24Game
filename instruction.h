#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QDialog>

namespace Ui {
class Instruction;
}

class Instruction : public QDialog
{
    Q_OBJECT

public:
    explicit Instruction(QWidget *parent = 0,QString name = "null");
    ~Instruction();
    void return_menu();
private:
    Ui::Instruction *ui;
    QString username;
};

#endif // INSTRUCTION_H
