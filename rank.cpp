#include "rank.h"
#include "ui_rank.h"
#include "menu.h"
#include "userinfo.h"
#include "QMessageBox.h"

Rank::Rank(QWidget *parent,QString name):
    QDialog(parent),
    ui(new Ui::Rank)
{
    ui->setupUi(this);
    setWindowTitle("战绩排行");
    username = name;
    userInfo users;
    QVector<userInfo::user> top;
    users.top_three(top);
    if(top.size()==3)
    {
        ui->name_1->setText(top[0].name);
        ui->name_2->setText(top[1].name);
        ui->name_3->setText(top[2].name);
        ui->score_1->setText(QString::number(top[0].score,10));
        ui->score_2->setText(QString::number(top[1].score,10));
        ui->score_3->setText(QString::number(top[2].score,10));
        ui->time_1->setText(convert_time(top[0].time));
        ui->time_2->setText(convert_time(top[1].time));
        ui->time_3->setText(convert_time(top[2].time));
        ui->speed_1->setText(QString::number(users.get_speed(top[0].name),'f',2));
        ui->speed_2->setText(QString::number(users.get_speed(top[1].name),'f',2));
        ui->speed_3->setText(QString::number(users.get_speed(top[2].name),'f',2));
    }
    else if(top.size()==2)
    {
        ui->name_1->setText(top[0].name);
        ui->name_2->setText(top[1].name);
        ui->name_3->setText("-");
        ui->score_1->setText(QString::number(top[0].score,10));
        ui->score_2->setText(QString::number(top[1].score,10));
        ui->score_3->setText("-");
        ui->time_1->setText(convert_time(top[0].time));
        ui->time_2->setText(convert_time(top[1].time));
        ui->time_3->setText("-");
        ui->speed_1->setText(QString::number(users.get_speed(top[0].name),'f',2));
        ui->speed_2->setText(QString::number(users.get_speed(top[1].name),'f',2));
        ui->speed_3->setText("-");
    }
    else if(top.size()==1)
    {
        ui->name_1->setText(top[0].name);
        ui->name_2->setText("-");
        ui->name_3->setText("-");
        ui->score_1->setText(QString::number(top[0].score,10));
        ui->score_2->setText("-");
        ui->score_3->setText("-");
        ui->time_1->setText(convert_time(top[0].time));
        ui->time_2->setText("-");
        ui->time_3->setText("-");
        ui->speed_1->setText(QString::number(users.get_speed(top[0].name),'f',2));
        ui->speed_2->setText("-");
        ui->speed_3->setText("-");
    }
    else
    {
        ui->name_1->setText("-");
        ui->name_2->setText("-");
        ui->name_3->setText("-");
        ui->score_1->setText("-");
        ui->score_2->setText("-");
        ui->score_3->setText("-");
        ui->time_1->setText("-");
        ui->time_2->setText("-");
        ui->time_3->setText("-");
        ui->speed_1->setText("-");
        ui->speed_2->setText("-");
        ui->speed_3->setText("-");
    }


    connect(ui->insultButton,&QPushButton::clicked,this,insult);
    connect(ui->returnButton,&QPushButton::clicked,this,return_menu);
}

void Rank::return_menu()
{
    this->close();
    Menu menu(0,username);
    menu.show();
    menu.exec();
}

void Rank::insult()
{
    QString input_name = this->ui->nameInput->text().trimmed();
    userInfo users;
    int score = users.get_score(input_name);
    int time = users.get_time(input_name);
    int rank = users.get_rank(input_name);
    QString scoreStr = QString::number(score, 10);
    QString rankStr = QString::number(rank,10);
    if(score != -1000000)
    QMessageBox::information(this, tr("提示"), "总分: " + scoreStr + '\n' + "总时间: " + convert_time(time) + '\n' + "每分钟得分: " + QString::number(users.get_speed(input_name),'f',2) + '\n' + "排名: " + rankStr, QMessageBox::Yes);
    else
    QMessageBox::warning(this,tr("警告"),tr("查询失败!"),QMessageBox::Yes);
}

