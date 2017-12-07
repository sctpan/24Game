#ifndef CONTESTWINDOW_H
#define CONTESTWINDOW_H
#include <QDialog>
#include <QVector>
#include<QString>
#include <QTimer>
#include "userinfo.h"
#include "mainwindow.h"

namespace Ui {
class ContestWindow;
}

class ContestWindow : public QDialog
{
    Q_OBJECT
public:
    explicit ContestWindow(QWidget *parent = nullptr,QString name = NULL);
    ~ContestWindow();
    static bool hasAnswer(double a, double b, double c, double d);
private slots:
    void clear();//清空所有数据，重置界面显示
    void clear_equation();//清空所有内部数据，不改变界面显示
    void backspace(); //退格
    void equal();
    void input_plus(); //添加加号
    void input_minus(); //添加减号
    void input_times(); //添加乘号
    void input_divide(); //添加除号
    void input_power(); //添加幂运算符号
    void input_left(); //添加左括号
    void input_right(); //添加右括号
    void input_no(); //输入无答案
    void on_card1_clicked(); //添加第一张牌
    void on_card2_clicked(); //添加第二张牌
    void on_card3_clicked(); //添加第三张牌
    void on_card4_clicked(); //添加第四张牌
    void showErrorDialog(QString); //显示错误提示信息
    void show_time();  //显示倒计时
    void exit_contest();

private:
    Ui::ContestWindow *ui;
    userInfo users;
    QVector<Card> cards;//四张牌
    QString equation,equation_for_show;
    int score;//得分
    int time;
    int interval;
    QTimer *timer;
    int showtime;
    bool input_no_flag;
    void getCards();
    int **all_cards;
    void putCards(int);//随机产生四张牌放在四个位置中
    double calculate(QString & equation);//主运算函数
    void check_erase_signal();//检测是否需要覆盖运算符
    void check_input_no();
    void append(QString c);//在文本框内追加文字，改变数据
    const int PRECISION = 12;//转换精度
    QVector<Card *> sequence;//输入顺序
    int seq;
    int round;
    int present;
    int players_num;
    QString username;
};



#endif // CONTESTWINDOW_H
