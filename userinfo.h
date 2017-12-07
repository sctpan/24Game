#ifndef USERINFO_H
#define USERINFO_H
#include <QString>
#include <QVector>
QString convert_time(int);
class userInfo
{
public:  
    userInfo();
    typedef struct{
        QString name;
        int score;
        int time;
    }user;
    typedef struct{
        QString name;
        int score;
        int time;
    }player;
    bool has_user(QString n);
    int get_score(QString n);
    int get_rank(QString n);
    int get_time(QString n);
    double get_speed(QString n);
    void set_score(QString n,int);
    void set_time(QString n,int);
    void top_three(QVector<user> & u);
    static player get_winner();
    static int cnt_completed();
    static bool is_completed(QString);
    void save(QString, int ,int );
    void save_grade(QString, int ,int );
    static bool in_contest(QString);
    int cnt_users();
    void cal_scores();
private:
    QVector<user> all_users;
    bool read_info();
    void user_sort();
    friend bool operator <(const userInfo::user a,const userInfo::user b);
    friend bool operator <(const userInfo::player a,const userInfo::player b);
};

#endif // USERINFO_H
