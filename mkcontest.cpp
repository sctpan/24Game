#include "mkcontest.h"
#include "ui_mkcontest.h"
#include "QFile.h"
#include "QTextStream.h"
#include <ctime>
#include "mainwindow.h"
#include "QMessageBox.h"
#include "solologin.h"
#include "windows.h"
#include "userinfo.h"

MkContest::MkContest(QWidget *parent):
    QDialog(parent),
    ui(new Ui::MkContest)
{
    ui->setupUi(this);
    setWindowTitle("创建比赛");
    connect(ui->createButton,&QPushButton::clicked,this,make_contest);
}

void MkContest::getCards(int seed)
{
    srand(seed);
    int prob = rand()%20+1;
    if(prob <= 19)
    {
        do
        {
            for(int i=0;i<4;i++)
               cards[i] = rand()%13+1;
            while(cards[1] == cards[0])
                cards[1] = rand()%13+1;

            while(cards[2] == cards[0] || cards[2]==cards[1])
                cards[2] = rand()%13+1;

            while(cards[3] == cards[0] || cards[3] == cards[1] || cards[3] == cards[2])
                cards[3] = rand()%13+1;
        }while(!MainWindow::hasAnswer(cards[0],cards[1],cards[2],cards[3]));
    }
    else
    {
        do
        {
            for(int i=0;i<4;i++)
                cards[i] = rand()%13+1;
            while(cards[1] == cards[0])
                cards[1] = rand()%13+1;

            while(cards[2] == cards[0] || cards[2]==cards[1])
                cards[2] = rand()%13+1;

            while(cards[3] == cards[0] || cards[3] == cards[1] || cards[3] == cards[2])
                cards[3] = rand()%13+1;
        }while(MainWindow::hasAnswer(cards[0],cards[1],cards[2],cards[3]));
    }
}

void MkContest::make_contest()
{

    int player_num = ui->input_players->text().toInt();
    int pro_num = ui->input_pros->text().toInt();
    QFile f1("./contest.txt");
    if(!f1.open(QIODevice::WriteOnly))
        return;
    QTextStream txtOutput1(&f1);
    txtOutput1 << player_num << endl;
    txtOutput1 << 0 <<endl;
    txtOutput1 << pro_num << endl;
    for(int i=0; i<pro_num; i++)
    {
        if(i == 0)
        getCards(std::time(nullptr));
        else
        getCards(cards[rand()%4]);
        for(int j=0; j<3; j++)
            txtOutput1 << cards[j] << " ";
        txtOutput1 << cards[3] << endl;
    }
    f1.close();
    QFile f2("./grade.txt");
    if(!f2.open(QIODevice::WriteOnly))
        return;
    QTextStream txtOutput2(&f2);
    userInfo u;
    int cnt = u.cnt_users();
    for(int i=0; i<cnt; i++)
        txtOutput2 << 0 << " " << 0 << endl;
    f2.close();

    QFile f3("./result.txt");
    f3.open(QIODevice::WriteOnly);
    QTextStream txtOutput3(&f3);
    txtOutput3 << 0 << endl;
    f3.close();
    QMessageBox::information(this,tr("提示"),tr("比赛已创建!"),QMessageBox::Yes);
    this->hide();
    SoloLogin sl;
    sl.show();
    sl.exec();
}


