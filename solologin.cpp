#include "solologin.h"
#include "menu.h"
#include "ui_solologin.h"
#include "QMessageBox.h"
#include "mainwindow.h"
#include "QFile.h"
#include "QTextStream.h"
#include "register.h"
#include "mkcontest.h"

SoloLogin::SoloLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SoloLogin)
{
    ui->setupUi(this);
    setWindowTitle("登录");
    ui->regButton->setFlat(true);
    ui->pwdInput->setEchoMode(QLineEdit::Password);
    setStyleSheet(
                "#regButton:hover{color:blue;border:none}"
                "#regButton:pressed{color:blue;border:none}"
                );
    connect(ui->loginButton,&QPushButton::clicked,this,login);
    connect(ui->regButton,&QPushButton::clicked,this,enter_register_mode);
    connect(ui->returnButton,&QPushButton::clicked,this,return_menu);
}

SoloLogin::~SoloLogin()
{
    delete ui;
}

void SoloLogin::return_menu()
{
    this->close();
    std::exit(0);
}

void SoloLogin::enter_register_mode()
{
    Register reg;
    this->hide();
    reg.show();
    reg.exec();
}

void SoloLogin::login()
{
    bool flag = true;
    int index = -1;
    QVector<QString> name;
    QVector<QString> pwd;
    if(!read_info(name,pwd))
    {
        QMessageBox::warning(this,tr("警告"),tr("读取信息错误!"),QMessageBox::Yes);
        return_menu();
        return;
    }
    QString input_name = this->ui->nameInput->text().trimmed();
    QString input_pwd = this->ui->pwdInput->text().trimmed();
    if(input_name == "admin" && input_pwd == "admin") //判断是不是管理员账号
    {
        this->hide();
        MkContest mc;
        mc.show();
        mc.exec();
    }
    else
    {
        for(int i=0; i<name.size(); i++)
        {
            if(name[i] == input_name)
            {
                index = i;
                break;
            }
        }
        if(index == -1) //如果没有找到该用户名，则登录失败
        flag = false;
        else
        {
            if(pwd[index] != input_pwd) //用户名和密码不匹配,则登录失败
                flag = false;
        }
        if(flag)
          {
            Menu mn("hastimer",0,input_name);
            this->hide();
            mn.show();
            mn.exec();
          }
          else
          {
              QMessageBox::warning(this,tr("警告"),tr("用户名或密码错误!"),QMessageBox::Yes);
              this->ui->nameInput->clear();
              this->ui->pwdInput->clear();
              this->ui->nameInput->setFocus();
          }
    }
}

bool SoloLogin::read_info(QVector<QString> &name, QVector<QString> &pwd)
{
    QFile f1("./username.txt");
    QFile f2("./password.txt");
    if(!f1.open(QIODevice::ReadOnly | QIODevice::Text))
       return false;
    if(!f2.open(QIODevice::ReadOnly | QIODevice::Text))
       return false;
    QTextStream txtInput1(&f1);
    QTextStream txtInput2(&f2);
    QString lineStr;
    while(!txtInput1.atEnd())
    {
        lineStr = txtInput1.readLine();
        name.append(lineStr);
    }
    while(!txtInput2.atEnd())
    {
        lineStr = txtInput2.readLine();
        pwd.append(lineStr);
    }

    f1.close();
    f2.close();
    return true;
}


