#include "instruction.h"
#include "ui_instruction.h"
#include "menu.h"

Instruction::Instruction(QWidget *parent,QString name) :
    QDialog(parent),
    ui(new Ui::Instruction)
{
    username = name;
    ui->setupUi(this);
    setWindowTitle("游戏说明");
    connect(ui->returnButton,&QPushButton::clicked,this,return_menu);
}

Instruction::~Instruction()
{
    delete ui;
}

void Instruction::return_menu()
{
    this->close();
    Menu menu(0,username);
    menu.show();
    menu.exec();
}
