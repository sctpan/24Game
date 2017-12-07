#include "userinfo.h"
#include "QFile.h"
#include "QTextStream.h"
#include "QMessageBox.h"
userInfo::userInfo()
{
    read_info();
}
bool userInfo::read_info()
{
    QFile f1("./username.txt");
    QFile f2("./score.txt");
    QFile f3("./time.txt");
    if(!f1.open(QIODevice::ReadOnly | QIODevice::Text))
       return false;
    if(!f2.open(QIODevice::ReadOnly | QIODevice::Text))
       return false;
    if(!f3.open(QIODevice::ReadOnly | QIODevice::Text))
       return false;
    QTextStream txtInput1(&f1);
    QTextStream txtInput2(&f2);
    QTextStream txtInput3(&f3);
    QString nameStr;
    QString scoreStr;
    QString timeStr;
    while(!txtInput1.atEnd())
    {
        nameStr = txtInput1.readLine();
        scoreStr = txtInput2.readLine();
        timeStr = txtInput3.readLine();
        user u;
        u.name = nameStr;
        u.score = scoreStr.toInt();
        u.time = timeStr.toInt();
        all_users.append(u);
    }
    f1.close();
    f2.close();
    f3.close();
    return true;
}

bool userInfo::has_user(QString n)
{
    for(int i=0; i<all_users.size(); i++)
    {
        if(all_users[i].name == n)
            return true;
    }
    return false;
}
int userInfo::get_score(QString n)
{
    for(int i=0; i<all_users.size(); i++)
    {
        if(all_users[i].name == n)
            return all_users[i].score;
    }
    return -1000000;
}

int userInfo::get_time(QString n)
{
    for(int i=0; i<all_users.size(); i++)
    {
        if(all_users[i].name == n)
            return all_users[i].time;
    }
    return -1000000;
}

double userInfo::get_speed(QString n)
{
    if(get_time(n) == 0)
        return 0;
    return double(get_score(n)) / double(get_time(n)) * 60;
}

void userInfo::set_score(QString n,int s)
{
    for(int i=0; i<all_users.size(); i++)
    {
        if(all_users[i].name == n)
        {
            all_users[i].score = s;
            break;
        }
    }
    save(n,s,1);
}

void userInfo::save_grade(QString n,int score,int time)
{

    QVector<user> players;
    QFile f1("./grade.txt");
    f1.open(QIODevice::ReadOnly);
    QFile f2("./username.txt");
    f2.open(QIODevice::ReadOnly);
    QTextStream txtInput1(&f1);
    QTextStream txtInput2(&f2);
    while(!txtInput1.atEnd() && !txtInput2.atEnd())
    {
        user u;
        txtInput2 >> u.name;
        txtInput1 >> u.score >> u.time;
        players.push_back(u);
    }
    f1.close();
    f2.close();
    for(int i=0; i<players.size(); i++)
    {
        if(players[i].name == n)
        {
            players[i].score = score;
            players[i].time = time;
            break;
        }
    }
    QFile::remove("./grade.txt");
    QFile f3("./grade.txt");
    f3.open(QIODevice::WriteOnly);
    QTextStream txtOutput(&f3);
    for(int i=0; i<players.size()-1; i++)
        txtOutput << players[i].score << " " << players[i].time << endl;
    txtOutput << players[players.size()-1].score << " " << players[players.size()-1].time;
    f1.close();
}

void userInfo::save(QString n,int num,int mode)
{
    QString num_str = QString::number(num, 10);
    QString path;
    if(mode == 1)
        path = "./score.txt";
    else
        path = "./time.txt";
    QFile f1(path);
    f1.open(QIODevice::ReadOnly);
    QFile f2("./username.txt");
    f2.open(QIODevice::ReadOnly);
    QTextStream txtInput1(&f1);
    QTextStream txtInput2(&f2);
    QString lineStr;
    QVector<QString> numStr;
    QVector<QString> nameStr;
    while(!txtInput1.atEnd())
    {
        lineStr = txtInput1.readLine();
        numStr.append(lineStr);
    }
    while(!txtInput2.atEnd())
    {
        lineStr = txtInput2.readLine();
        nameStr.append(lineStr);
    }
    for(int i=0; i<nameStr.size(); i++)
    {
        if(nameStr[i] == n)
        {
            numStr[i] = num_str;
            break;
        }
    }
    f1.close();
    f2.close();
    //QFile::remove(path);
    QFile f3(path);
    f3.open(QIODevice::WriteOnly);
    QTextStream txtOutput(&f3);
    for(int i=0; i<numStr.size(); i++)
        txtOutput << numStr[i] << endl;
    f3.close();
}
bool operator <(const userInfo::user a,const userInfo::user b)
{
    double a_score = double(a.score);
    double b_score = double(b.score);
    double a_time = double(a.time);
    double b_time = double(b.time);
    double a_speed = (a.time==0) ? 0 : a_score / a_time;
    double b_speed = (b.time==0) ? 0 : b_score / b_time;
    if(a_speed != b_speed)
    return a_speed > b_speed;
    else
    return a_score > b_score;
}

bool operator <(const userInfo::player a,const userInfo::player b)
{
    if(a.score != b.score)
        return a.score > b.score;
    else
       return a.time < b.time;
}

userInfo::player userInfo::get_winner()
{
    QVector<player> players;
    QFile f1("./grade.txt");
    f1.open(QIODevice::ReadOnly);
    QFile f2("./username.txt");
    f2.open(QIODevice::ReadOnly);
    QTextStream txtInput1(&f1);
    QTextStream txtInput2(&f2);
    while(!txtInput1.atEnd())
    {
        player p;
        txtInput2 >> p.name;
        txtInput1 >> p.score >> p.time;
        players.push_back(p);
    }
    f1.close();
    f2.close();
    qSort(players.begin(),players.end());
    for(int i=0; i<players.size(); i++)
        if(in_contest(players[i].name))
            return players[i];
}

void userInfo::cal_scores()
{
    bool flag = true;
    QVector<player> players;
    QFile f1("./grade.txt");
    f1.open(QIODevice::ReadOnly);
    QFile f2("./username.txt");
    f2.open(QIODevice::ReadOnly);
    QTextStream txtInput1(&f1);
    QTextStream txtInput2(&f2);
    while(!txtInput1.atEnd())
    {
        player p;
        txtInput2 >> p.name;
        txtInput1 >> p.score >> p.time;
        players.push_back(p);
    }
    f1.close();
    f2.close();
    qSort(players.begin(),players.end());
    for(int i=0; i<players.size(); i++)
    {
        if(in_contest(players[i].name))
        {
            if(flag)
            {
                flag = false;
                save(players[i].name,get_score(players[i].name) + cnt_completed()-1,1);
            }
            else
            {
                save(players[i].name,get_score(players[i].name) - 1,1);
            }
        }
    }

}







int userInfo::cnt_completed()
{
    QVector<player> players;
    QFile f1("./grade.txt");
    f1.open(QIODevice::ReadOnly);
    QFile f2("./username.txt");
    f2.open(QIODevice::ReadOnly);
    QFile f3("./incontest.txt");
    f3.open(QIODevice::ReadOnly);
    QTextStream txtInput1(&f1);
    QTextStream txtInput2(&f2);
    QTextStream txtInput3(&f3);
    QVector<QString> player_name;
    while(!txtInput1.atEnd() && !txtInput2.atEnd())
    {
        player p;
        txtInput2 >> p.name;
        txtInput1 >> p.score >> p.time;
        players.push_back(p);
    }
    f1.close();
    f2.close();
    while(!txtInput3.atEnd())
        player_name.push_back(txtInput3.readLine());
    f3.close();
    int count = 0;
    for(int i=0; i<player_name.size(); i++)
    {
        for(int j=0; j<players.size(); j++)
        {
            if(players[j].name == player_name[i])
            {
                if(players[j].time != 0)
                    count++;
            }
        }
    }
    return count;
}

bool userInfo::is_completed(QString name)
{
    QVector<player> players;
    QFile f1("./grade.txt");
    f1.open(QIODevice::ReadOnly);
    QFile f2("./username.txt");
    f2.open(QIODevice::ReadOnly);

    QTextStream txtInput1(&f1);
    QTextStream txtInput2(&f2);

    while(!txtInput1.atEnd())
    {
        player p;
        txtInput2 >> p.name;
        txtInput1 >> p.score >> p.time;
        players.push_back(p);
    }
    f1.close();
    f2.close();

    for(int i=0; i<players.size(); i++)
    {
            if(players[i].name == name)
            {
                if(players[i].time != 0)
                    return true;
            }
    }
    return false;
}



void userInfo::user_sort()
{
    qSort(all_users.begin(),all_users.end());
}

void userInfo::top_three(QVector<user> & u)
{
    user_sort();
    if(all_users.size() >= 3)
    {
        for(int i=0; i<3; i++)
             u.push_back(all_users[i]);
    }
    else
    {
        for(int i=0; i<all_users.size(); i++)
             u.push_back(all_users[i]);
    }
}

int userInfo::get_rank(QString n)
{
    user_sort();
    for(int i=0; i<all_users.size(); i++)
    {
        if(all_users[i].name == n)
            return i+1;
    }
}

QString convert_time(int t)
{
    int minute = t / 60;
    int second = t - 60 * minute;
    QString time = QString::number(minute,10) + 'm' + QString::number(second,10) + 's';
    return time;
}

bool userInfo::in_contest(QString n)
{
    QFile f("./incontest.txt");
    f.open(QIODevice::ReadOnly);
    QTextStream txtInput(&f);
    QVector<QString> lineStr;
    while(!txtInput.atEnd())
        lineStr.append(txtInput.readLine());
    for(int i=0; i<lineStr.size(); i++)
    {
        if(lineStr[i] == n)
            return true;
    }
    return false;
    f.close();
}

int userInfo::cnt_users()
{
    return all_users.size();
}
