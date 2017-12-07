#include "register.h"
#include "menu.h"
#include "QMessageBox.h"
#include "ui_register.h"
#include "QFile.h"
#include "QTextStream.h"
#include "userinfo.h"
#include "solologin.h"

Register::Register(QWidget *parent):
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    setWindowTitle("注册");
    ui->pwdInput->setEchoMode(QLineEdit::Password);
    ui->pwdCfm->setEchoMode(QLineEdit::Password);
    connect(ui->regButton,&QPushButton::clicked,this,judge_info);
    connect(ui->returnButton,&QPushButton::clicked,this,return_menu);
}

void Register::return_menu()
{
    this->close();
    SoloLogin sl;
    sl.show();
    sl.exec();
}

void Register::judge_info()
{
    userInfo users;
    QString name = this->ui->nameInput->text().trimmed();
    QString pwd_input = this->ui->pwdInput->text().trimmed();
    QString pwd_confirm = this->ui->pwdCfm->text().trimmed();
    if(users.has_user(name)) //判断该用户名是否已注册过
    {
        QMessageBox::information(this, tr("提示"), tr("该用户名已被注册！"), QMessageBox::Yes);
        this->ui->nameInput->clear();
        this->ui->pwdInput->clear();
        this->ui->pwdCfm->clear();
        this->ui->nameInput->setFocus();
    }
    else
    {
      if(pwd_input == pwd_confirm)
      {
         if(save_info(name,pwd_confirm))
         {
             QMessageBox::information(this, tr("提示"), tr("注册成功！"), QMessageBox::Yes);
             return_menu();
         }
         else
           QMessageBox::warning(this,tr("警告"),tr("注册失败!"),QMessageBox::Yes);
      }
      else
      {
          QMessageBox::warning(this,tr("警告"),tr("输入密码不一致!"),QMessageBox::Yes);
          this->ui->pwdInput->clear();
          this->ui->pwdCfm->clear();
          this->ui->pwdInput->setFocus();
      }
    }
}

bool Register::save_info(QString str1, QString str2)
{
    QFile f1("./username.txt");
    QFile f2("./password.txt");
    QFile f3("./score.txt");
    QFile f4("./time.txt");
    QFile f5("./grade.txt");
    if(!f1.open(QIODevice::WriteOnly|QIODevice::Append))
        return false;

    if(!f2.open(QIODevice::WriteOnly|QIODevice::Append))
        return false;

    if(!f3.open(QIODevice::WriteOnly|QIODevice::Append))
        return false;

    if(!f4.open(QIODevice::WriteOnly|QIODevice::Append))
        return false;

    if(!f5.open(QIODevice::WriteOnly|QIODevice::Append))
        return false;
    QTextStream txtOutput1(&f1);
    QTextStream txtOutput2(&f2);
    QTextStream txtOutput3(&f3);
    QTextStream txtOutput4(&f4);
    QTextStream txtOutput5(&f5);
    txtOutput1 << str1 << endl;
    txtOutput2 << str2 << endl;
    txtOutput3 << 0 << endl;
    txtOutput4 << 0 << endl;
    txtOutput5 << 0 << " " << 0 << endl;
    f1.close();
    f2.close();
    f3.close();
    f4.close();
    f5.close();
    return true;
}
