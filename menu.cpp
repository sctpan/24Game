#include "menu.h"
#include "ui_menu.h"
#include "solologin.h"
#include "register.h"
#include "rank.h"
#include "instruction.h"
#include "mainwindow.h"
#include "userinfo.h"
#include "QFile.h"
#include "QTextStream.h"
#include "QMessageBox.h"
#include "regcontest.h"
#include "contestwindow.h"

Menu::Menu(QWidget *parent,QString name) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    setWindowTitle("24点游戏");
    ui->outButton->setFlat(true);
    setStyleSheet(
                "#outButton:hover{color:blue;border:none}"
                "#outButton:pressed{color:blue;border:none}"
                );
    ui->nameLabel->setText(name);
    connect(ui->outButton,&QPushButton::clicked,this,return_login);
    connect(ui->soloButton,&QPushButton::clicked,this,enter_solo_mode);
    connect(ui->multiButton,&QPushButton::clicked,this,enter_multi_mode);
    connect(ui->rankButton,&QPushButton::clicked,this,enter_rank_mode);
    connect(ui->instuctButton,&QPushButton::clicked,this,enter_instruction_mode);
    connect(ui->exitButton,&QPushButton::clicked,this,exit);
    username = name;
}

Menu::Menu(QString mode,QWidget *parent,QString name) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    setWindowTitle("24点游戏");
    ui->outButton->setFlat(true);
    setStyleSheet(
                "#outButton:hover{color:blue;border:none}"
                "#outButton:pressed{color:blue;border:none}"
                );
    ui->nameLabel->setText(name);
    if(mode == "hastimer")
    {
        timer = new QTimer(this);
        timer->setInterval(500);
        timer->start();
    }
    connect(ui->outButton,&QPushButton::clicked,this,return_login);
    connect(ui->soloButton,&QPushButton::clicked,this,enter_solo_mode);
    connect(ui->multiButton,&QPushButton::clicked,this,enter_multi_mode);
    connect(ui->rankButton,&QPushButton::clicked,this,enter_rank_mode);
    connect(ui->instuctButton,&QPushButton::clicked,this,enter_instruction_mode);
    connect(ui->exitButton,&QPushButton::clicked,this,exit);
    connect(timer,SIGNAL(timeout()),this,SLOT(detect()));
    username = name;
    flag = false;
}

Menu::~Menu()
{
    delete ui;
}

void Menu::enter_solo_mode()
{
    this->close();
    MainWindow game(nullptr,username);
    game.show();
    game.exec();
}

void Menu::enter_multi_mode()
{
    QFile f1("./contest.txt");
    if(!f1.open(QIODevice::ReadOnly | QIODevice::Text))
       return;
    QTextStream txtInput1(&f1);
    int all_players = txtInput1.readLine().toInt();
    int reg_players = txtInput1.readLine().toInt();
    if(all_players == 0 && reg_players == 0)
        QMessageBox::information(this,tr("提示信息"),tr("当前没有比赛!"),QMessageBox::Yes);
    else if(all_players == reg_players && all_players!=0 && !userInfo::in_contest(username))
        QMessageBox::information(this,tr("提示信息"),tr("比赛人数已满!"),QMessageBox::Yes);
    else if((all_players != reg_players) && userInfo::in_contest(username))
    {
        QMessageBox::information(this,tr("提示信息"),tr("你已注册比赛，比赛还未开始!"),QMessageBox::Yes);
    }
    else if(!userInfo::in_contest(username))
    {
        this->hide();
        RegContest reg(0,username);
        reg.show();
        reg.exec();
    }
    else if(userInfo::is_completed(username))
    {
        QMessageBox::information(this,tr("提示信息"),tr("你已完成比赛，请等待比赛结果!"),QMessageBox::Yes);
    }
    else
    {
        this->hide();
        ContestWindow cw(0,username);
        cw.show();
        cw.exec();
    }
}

void Menu::exit()
{
    this->close();
     std::exit(0);
}

void Menu::enter_rank_mode()
{
    this->hide();
    Rank r(0,username);
    r.show();
    r.exec();
}

void Menu::enter_instruction_mode()
{
    this->hide();
    Instruction ins(0,username);
    ins.show();
    ins.exec();
}

void Menu::return_login()
{
    this->close();
    SoloLogin sl;
    sl.show();
    sl.exec();
}

void Menu::detect()
{
    if(flag)
    {
        timer->stop();
        return;
    }
    flag = true;
    QFile f("./result.txt");
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        timer->stop();
        return;
    }
    QTextStream txtInput(&f);
    int isover = txtInput.readLine().toInt();
    if(!isover)
    {
        QFile f1("./contest.txt");
        if(!f1.open(QIODevice::ReadOnly | QIODevice::Text))
           return;
        QTextStream txtInput1(&f1);
        int all_players = txtInput1.readLine().toInt();
        int reg_players = txtInput1.readLine().toInt();
        if(all_players == reg_players && userInfo::in_contest(username) && !userInfo::is_completed(username))
        {
            QMessageBox::information(this,tr("提示信息"),tr("你注册的比赛已就绪，准备好后按<多人对战>直接进入比赛!"),QMessageBox::Yes);
            timer->stop();
            delete timer;
        }
    }
    else
    {
        QString name,scoreStr,timeStr;
        txtInput >> name >> scoreStr >> timeStr;
        timeStr = convert_time(timeStr.toInt());
        QString str = tr("他的得分: ") + scoreStr + tr("   他的用时: ") + timeStr;
        QMessageBox::information(this,tr("比赛结果公告"),tr("上次比赛获胜者为: ") + name + '\n' + str,QMessageBox::Yes);
        timer->stop();
        delete timer;
    }
}

