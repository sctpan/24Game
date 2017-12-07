#include "regcontest.h"
#include "ui_regcontest.h"
#include "menu.h"
#include "QFile.h"
#include "QTextStream.h"
#include "QMessageBox.h"
RegContest::RegContest(QWidget *parent,QString name):
    QDialog(parent),
    ui(new Ui::RegContest)
{
    ui->setupUi(this);
    username = name;
    setWindowTitle("注册比赛");
    QFile f2("./contest.txt");
    f2.open(QIODevice::ReadOnly);
    QTextStream txtInput2(&f2);
    QString all_players = txtInput2.readLine();
    QString reg_players = txtInput2.readLine();
    QString pros = txtInput2.readLine();
    f2.close();
    ui->proLabel->setText(pros);
    ui->regLabel->setText(reg_players + '/' + all_players);
    connect(ui->regButton,&QPushButton::clicked,this,register_contest);
    connect(ui->returnButton,&QPushButton::clicked,this,return_menu);

}

RegContest::~RegContest()
{
    delete ui;
}

void RegContest::register_contest()
{
    QFile f1("./incontest.txt");
    if(!f1.open(QIODevice::WriteOnly | QIODevice::Append))
       return;
    QTextStream txtOutput1(&f1);
    txtOutput1 << username << endl;
    f1.close();


    QFile f2("./contest.txt");
    f2.open(QIODevice::ReadOnly);
    QTextStream txtInput2(&f2);
    QVector<QString> lineStr;
    while(!txtInput2.atEnd())
        lineStr.append(txtInput2.readLine());
    lineStr[1] = QString::number(lineStr[1].toInt() + 1,10);
    f2.close();

    f2.open(QIODevice::WriteOnly);
    QTextStream txtOutput2(&f2);
    for(int i=0; i<lineStr.size(); i++)
        txtOutput2 << lineStr[i] << endl;
    f2.close();

    QMessageBox::information(this,tr("提示"),tr("比赛已注册!"),QMessageBox::Yes);
    return_menu();
}

void RegContest::return_menu()
{
    this->hide();
    Menu mn("hastimer",0,username);
    mn.show();
    mn.exec();
}
