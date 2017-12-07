#include "contestwindow.h"
#include "ui_contestwindow.h"
#include<ctime>
#include "QMessageBox.h"
#include<cmath>
#include "qmath.h"
#include "menu.h"
#include "QFile.h"
#include "QTextStream.h"

static bool isSignal(QChar c);

static QString getAnswer(double a, double b, double c, double d);
ContestWindow::ContestWindow(QWidget *parent, QString name) :
     QDialog(parent),
    ui(new Ui::ContestWindow)
{
    ui->setupUi(this);
    ui->username->setText(tr("加油，") + name);
    input_no_flag = false;
    present = 0;
    timer = new QTimer(this);
    interval = 45;
    showtime = interval;
    score = 0;
    username = name;
    time = 0;
    timer->setInterval(1000);
    ui->score->setText(QString::number(score,10));
    ui->time->setText(QString::number(time,10));
    ui->username->setText(name);
    for(int i=0;i<4;i++)
        cards.push_back(Card());
    sequence.fill(nullptr,4);
    seq=-1;
    setStyleSheet(
                "#output{padding: 0 20px;border-radius : 10px; background-color:rgba(255,255,255,0.8);color:black;}"
                "#card1,#card2,#card3,#card4{background-color:rgba(255,255,255,0.8);border:hidden;border-radius: 2px;}"
                "#card1:pressed,#card2:pressed,#card3:pressed,#card4:pressed{outline:2px inset blue;}"
                );
    setWindowTitle("24点游戏");
    connect(ui->backspaceButton,&QPushButton::clicked,this,backspace);
    connect(ui->plusButton,&QPushButton::clicked,this,input_plus);
    connect(ui->minusButton,&QPushButton::clicked,this,input_minus);
    connect(ui->timesButton,&QPushButton::clicked,this,input_times);
    connect(ui->divideButton,&QPushButton::clicked,this,input_divide);
    connect(ui->powerButton,&QPushButton::clicked,this,input_power);
    connect(ui->leftButton,&QPushButton::clicked,this,input_left);
    connect(ui->rightButton,&QPushButton::clicked,this,input_right);
    connect(ui->noButton,&QPushButton::clicked,this,input_no);
    connect(ui->submitButton,&QPushButton::clicked,this,equal);
    connect(timer,SIGNAL(timeout()),this,SLOT(show_time()));
    getCards();
    putCards(present);
}

ContestWindow::~ContestWindow()
{
    delete ui;
}
void ContestWindow::clear()
{
    clear_equation();
    ui->output->setText(equation_for_show);
}

void ContestWindow::getCards()
{
    QFile f("./contest.txt");
    f.open(QIODevice::ReadOnly);
    QTextStream txtInput(&f);
    players_num = txtInput.readLine().toInt();
    txtInput.readLine();
    int pros = txtInput.readLine().toInt();
    round = pros;
    all_cards = new int *[pros];
    for(int i=0; i<pros; i++)
        all_cards[i] = new int[4];
    for(int i=0; i<pros; i++)
    {
        for(int j=0; j<4; j++)
            txtInput >> all_cards[i][j];
    }
    f.close();
}

void ContestWindow::putCards(int num)
{
    if(present == round)
    {
        showErrorDialog("你已完成比赛，请等待其他用户完成比赛，届时将通知你比赛结果!");
        exit_contest();
    }
    ui->roundLabel->setText(tr("第") + QString::number(present+1,10) + tr("/") + QString::number(round,10) + tr("题"));
    clear();
    input_no_flag = false;
    for(int i=0;i<4;i++)
        cards[i]=Card::getValuedCard(all_cards[num][i]);
    ui->card1->setStyleSheet(cards[0].getBackground());
    ui->card2->setStyleSheet(cards[1].getBackground());
    ui->card3->setStyleSheet(cards[2].getBackground());
    ui->card4->setStyleSheet(cards[3].getBackground());
    time = time + interval - showtime;
    ui->time->setText(convert_time(time));
    showtime = interval;
    ui->timeLabel->setText(QString::number(showtime,10));
    timer->start();
    present++;
}


void ContestWindow::clear_equation()
{
    equation.clear();
    equation_for_show.clear();
    for(int i=0;i<4;i++)
        cards[i].checked = false;
    sequence.fill(nullptr,4);
    seq=-1;
}
void ContestWindow::showErrorDialog(QString info)
{
    QMessageBox::information(this,tr("提示信息"),info,QMessageBox::Yes);
}

void ContestWindow::input_plus()
{
    check_input_no();
    check_erase_signal();
    if(!equation.isEmpty())
        append("+");
}

void ContestWindow::input_minus()
{
    check_input_no();
    check_erase_signal();
    if(!equation.isEmpty())
        append("-");
}

void ContestWindow::input_times()
{
    check_input_no();
    check_erase_signal();
    if(!equation.isEmpty())
        append("*");
}

void ContestWindow::input_divide()
{
    check_input_no();
    check_erase_signal();
    if(!equation.isEmpty())
        append("/");
}

 void ContestWindow::input_power()
 {
    check_input_no();
    check_erase_signal();
    if(!equation.isEmpty())
        append("^");
 }

void ContestWindow::input_left()
{
    check_input_no();
    append("(");
}

void ContestWindow::input_right()
{
    check_input_no();
    if(equation_for_show[equation.size()-1] == '(')
    {
        equation_for_show += "0";
        equation += "0";
    }
    append(")");
}

void ContestWindow::input_no()
{
    clear();
    equation_for_show = "No solution";
    input_no_flag = true;
    ui->output->setText(equation_for_show);
}

void ContestWindow::check_erase_signal()
{
    if(equation.size()>0&&isSignal(equation[equation.size()-1]))
    {
        equation_for_show.resize(equation.size()-1);
        equation.resize(equation.size()-1);
    }
}

void ContestWindow::check_input_no()
{
    if(input_no_flag)
    {
        clear();
        input_no_flag = true;
    }
}

void ContestWindow::append(QString c)
{
    equation_for_show += c;
    equation += c;
    ui->output->setText(equation_for_show);
}

static bool isSignal(QChar c)
{
    return (c=='+'||c=='-'||c=='*'||c=='/'||c=='^');
}

void ContestWindow::on_card1_clicked()
{
    check_input_no();
    for(int i=equation.size()-1;i>=0;i--)
    {
        if(equation[i] == '(')
            continue;
        if(isSignal(equation[i]))
            break;
        if(equation[i]>='0' && equation[i]<='9')
        {
            showErrorDialog("两张牌之间必须有运算符。");
            return;
        }
        else
        {
            showErrorDialog("算式有误。");
            return;
        }
    }

    if(cards[0].checked == false)
    {
        append(QString::number(cards[0].getValue()));
        cards[0].checked = true;
        sequence[++seq] = &cards[0];
    }
    else
        showErrorDialog("同一张牌不能使用两次。");
}

void ContestWindow::on_card2_clicked()
{
    check_input_no();
    for(int i=equation.size()-1;i>=0;i--)
    {
        if(equation[i] == '(')
            continue;
        if(isSignal(equation[i]))
            break;
        if(equation[i]>='0' && equation[i]<='9')
        {
            showErrorDialog("两张牌之间必须有运算符。");
            return;
        }
        else
        {
            showErrorDialog("算式有误。");
            return;
        }
    }
    if(cards[1].checked == false)
    {
        append(QString::number(cards[1].getValue()));
        cards[1].checked = true;
        sequence[++seq] = &cards[1];
    }
    else
        showErrorDialog("同一张牌不能使用两次。");
}

void ContestWindow::on_card3_clicked()
{
    check_input_no();
    for(int i=equation.size()-1;i>=0;i--)
    {
        if(equation[i] == '(')
            continue;
        if(isSignal(equation[i]))
            break;
        if(equation[i]>='0' && equation[i]<='9')
        {
            showErrorDialog("两张牌之间必须有运算符。");
            return;
        }
        else
        {
            showErrorDialog("算式有误。");
            return;
        }
    }
    if(cards[2].checked == false)
    {
        append(QString::number(cards[2].getValue()));
        cards[2].checked = true;
        sequence[++seq] = &cards[2];
    }
    else
        showErrorDialog("同一张牌不能使用两次。");
}

void ContestWindow::on_card4_clicked()
{
    check_input_no();
    for(int i=equation.size()-1;i>=0;i--)
    {
        if(equation[i] == '(')
            continue;
        if(isSignal(equation[i]))
            break;
        if(equation[i]>='0' && equation[i]<='9')
        {
            showErrorDialog("两张牌之间必须有运算符。");
            return;
        }
        else
        {
            showErrorDialog("算式有误。");
            return;
        }
    }
    if(cards[3].checked == false)
    {
        append(QString::number(cards[3].getValue()));
        cards[3].checked = true;
        sequence[++seq] = &cards[3];
    }
    else
        showErrorDialog("同一张牌不能使用两次。");
}

void ContestWindow::backspace()
{
    check_input_no();
    if(equation.size()>0)
    {
        if(!isSignal(equation[equation.size()-1]) && equation[equation.size()-1] != '(' && equation[equation.size()-1] !=')')
        {
            int i,j;
            for(i=equation.size()-1;i>=0;i--)
                if(isSignal(equation[i]))
                    break;

            QString last_num;       //看删掉的是哪一张牌，同步更改sequence
            for(j=i+1;j<equation.size();j++)
                last_num+=equation[j];

            equation_for_show.resize(equation.size()-(j - i - 1));
            equation.resize(equation.size()-(j - i - 1));
            ui->output->setText(equation_for_show);

            for(int i=seq;i>=0;i--)
                if(sequence[i]->value == last_num.toDouble())
                {
                    sequence[i]->checked = false;
                    sequence[seq]=nullptr;
                    seq--;
                    break;
                }
        }
        else     //如果最后一个字符是操作符就直接删
        {
            equation_for_show.resize(equation.size()-1);
            equation.resize(equation.size()-1);
            ui->output->setText(equation_for_show);
        }
    }
}

void ContestWindow::equal()
{
    if(input_no_flag)
    {
        if(hasAnswer(cards[0].getValue(),cards[1].getValue(),cards[2].getValue(),cards[3].getValue()))
        {
            timer->stop();
            QString solution = getAnswer(cards[0].getValue(),cards[1].getValue(),cards[2].getValue(),cards[3].getValue());
            showErrorDialog(tr("答错了，下题加油!") + "\n" + "参考答案: " + solution);
            time = time + 30;
            clear();
            putCards(present);
        }
        else
        {
            timer->stop();
            ui->score->setText(QString::number(++score));
            showErrorDialog("恭喜你答对了！");
            clear();
            putCards(present);
        }
    }
    else
    {
        try
        {
            for(auto card : cards)
                if(card.checked == false)
                {
                    throw "每张牌必须使用一次";
                }
            if(fabs(calculate(equation) - 24.0) < 1E-6)
            {
                timer->stop();
                ui->score->setText(QString::number(++score));
                showErrorDialog("恭喜你答对了！");
                clear();
                putCards(present);
            }
            else
            {
                timer->stop();
                QString solution = getAnswer(cards[0].getValue(),cards[1].getValue(),cards[2].getValue(),cards[3].getValue());
                showErrorDialog(tr("答错了，下题加油!") + "\n" + "参考答案: " + solution);
                time = time + 30;
                clear();
                putCards(present);
            }
            clear_equation();
        }
        catch(const char * c)
        {
            showErrorDialog(QString(c));
            clear();
        }
    }
}

double ContestWindow::calculate(QString & equation)
{
    const QChar TIMES = '*';
    const QChar DIVIDE ='/';
    const QChar PLUS = '+';
    const QChar MINUS = '-';
    const QChar POWER = '^';

    /*缺失最后一个操作数则抛出错误*/
    if(isSignal(equation[equation.size()-1]))
        throw "缺少运算数";

    /*根据算式中是否还有括号判断不同的路径*/
    auto first_left = equation.indexOf('(');
    auto last_right = equation.lastIndexOf(')');
    if (first_left == last_right)//如果算式当中已经没有括号
    {
        double result;
        double num1, num2, temp_result;
        QVector<QChar> sigs;
        QVector<double> nums;
        QString current_num;
        for (auto i : equation)
            if (i == POWER || i == TIMES || i == DIVIDE || i == PLUS || i == MINUS)
            {
                if (current_num.size() == 0)
                {
                    if (i == PLUS || i == MINUS)
                        current_num.push_back(i);
                    else
                        throw "运算符错误";
                }
                else
                {
                    sigs.push_back(i); //存储运算符
                    nums.push_back(current_num.toDouble()); //将牌值转换为运算数存储
                    current_num.clear();
                }
            }
            else if (i >= '0'&&i <= '9')
            {
                current_num += i;
            }
        nums.push_back(current_num.toDouble());//最后一个数

        for (int i = 0; i < sigs.size(); i++)
        {
            if(sigs[i] == POWER)
            {
                num1 = nums[i];
                num2 = nums[i + 1];
                temp_result = qPow(num1,num2);
                nums.remove(i, 2);
                sigs.remove(i);
                nums.insert(nums.begin() + i, temp_result);
                i--;
            }
            else if (sigs[i] == TIMES)
            {
                num1 = nums[i];
                num2 = nums[i + 1];
                temp_result = num1*num2;
                nums.remove(i, 2);
                sigs.remove(i);
                nums.insert(nums.begin() + i, temp_result);
                i--;
            }
            else if (sigs[i] == DIVIDE)
            {
                num1 = nums[i];
                num2 = nums[i + 1];
                temp_result = num1 / num2;
                nums.remove(i, 2);
                sigs.remove(i);
                nums.insert(nums.begin() + i, temp_result);
                i--;
            }
        }
        result = nums[0];
        for (int i = 0; i < nums.size() - 1; i++)
            if (sigs[i] == PLUS)
                result += nums[i + 1];
            else if (sigs[i] == MINUS)
                result -= nums[i + 1];
        return result;
    }
    else if (first_left == -1)//括号不配对情况
    {
        //equation.remove(equation.lastIndexOf(')'), 1);
        throw "括号不成对";
    }
    else if (last_right == -1)
    {
        //equation.remove(equation.indexOf('('), 1);
        throw "括号不成对";
    }
    else//抹掉括号
    {
        int left, right, left_2, right_2;
        left = equation.indexOf('(');
        right = equation.lastIndexOf(')');
        left_2 = equation.lastIndexOf('(');
        right_2 = equation.indexOf(')');
        if (left_2 >= left && right_2 <= right && left_2 < right_2)//只有嵌套括号，一层一层去掉括号
        {
            QString sub_str = equation.mid(first_left + 1, last_right - first_left - 1);
            double sub_result = calculate(sub_str);
            equation.replace(first_left, last_right - first_left + 1, QString::number(sub_result,'g',PRECISION));
            return calculate(equation);
        }
        else//有分离括号,分开计算
        {
            left = equation.lastIndexOf('(');//找到最右边的左括号
            right = equation.mid(left, equation.size()).indexOf(')') + left;//与之配对的右括号
            //此时left和right之间有单位算式
            QString sub_str = equation.mid(left + 1, right - left - 1);
            double sub_result = calculate(sub_str);
            equation.replace(left, right - left + 1, QString::number(sub_result,'g',PRECISION));
            return calculate(equation);
        }
    }
}

void ContestWindow::show_time()
{
    showtime--;
    ui->timeLabel->setText(QString::number(showtime,10));
    if(showtime == 0)
    {
        timer->stop();
        QString solution = getAnswer(cards[0].getValue(),cards[1].getValue(),cards[2].getValue(),cards[3].getValue());
        showErrorDialog(tr("你已超时,下题加油!") + "\n" + "参考答案: " + solution);
        ui->timeLabel->setText(QString::number(showtime,10));
        putCards(present);
    }
}

void ContestWindow::exit_contest()
{
    users.save_grade(username,score,time);
    if(players_num == userInfo::cnt_completed())
    {
        userInfo::player py = userInfo::get_winner();
        userInfo users;
        users.cal_scores();
        QFile f("./result.txt");
        f.open(QIODevice::WriteOnly);
        QTextStream txtOutput(&f);
        txtOutput << 1 << endl;
        txtOutput << py.name << " " << py.score << " " << py.time;
        f.close();
        QFile::remove("./contest.txt");
        QFile::remove("./incontest.txt");
        QFile::remove("./grade.txt");
        QFile f1("./contest.txt");
        if(!f1.open(QIODevice::WriteOnly))
            return;
        QTextStream txtOutput1(&f1);
        txtOutput1 << 0 << endl;
        txtOutput1 << 0 <<endl;
        f1.close();
    }
    delete timer;
    this->close();
    Menu menu("hastimer",0,username);
    menu.show();
    menu.exec();
}

static double plus(double a, double b)
{
    return a+b;
}
static double minus(double a, double b)
{
    return a-b;
}
static double times(double a, double b)
{
    return a*b;
}
static double divide(double a, double b)
{
    if(b == 0)
    {
        if(a>=0)
            return INFINITY;
        else if(a<0)
            return -INFINITY;
    }
    return a/b;
}

static double power(double a, double b)
{
    return qPow(a,b);
}
static double (*operators[5])(double,double) = {&plus, &minus, &times, &divide, &power};//函数指针
bool ContestWindow::hasAnswer(double a, double b, double c, double d)//穷举所有情况看是否有解
{
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            for(int k=0; k<5; k++)
            {
                //((a#b)#c)#d
                double answer = operators[k](operators[j](operators[i](a, b), c) , d);
                if(fabs(answer -24.0)<1E-6)
                    return true;
                //(a#(b#c))#d
                answer = operators[k](operators[j](a, operators[i](b, c)) , d);
                if(fabs(answer -24.0)<1E-6)
                    return true;
                //a#((b#c)#d)
                answer = operators[k](a, operators[j](operators[i](b, c) , d));
                if(fabs(answer -24.0)<1E-6)
                    return true;
                //(a#b)#(c#d)
                answer = operators[k](operators[i](a, b), operators[j](c, d));
                if(fabs(answer -24.0)<1E-6)
                    return true;
                //a#(b#(c#d))
                answer = operators[k](a, operators[j](b, operators[i](c, d)));
                if(fabs(answer -24.0)<1E-6)
                    return true;
            }
        }
    }
    return false;
}

static QString getAnswer(double a, double b, double c, double d)//穷举所有情况得到解
{
    QString a_s = QString::number(a,'g');
    QString b_s = QString::number(b,'g');
    QString c_s = QString::number(c,'g');
    QString d_s = QString::number(d,'g');
    const QString signal[5] = {"+","-","*","/","^"};
    QString solution;

    for(int i=0; i<5; i++)
    {
        for(int j=0; j<5; j++)
        {
            for(int k=0; k<5; k++)
            {
                //((a#b)#c)#d
                double answer = operators[k](operators[j](operators[i](a, b), c) , d);
                if(fabs(answer -24.0)<1E-6)
                {
                    solution = "(("+a_s+signal[i]+b_s+")"+signal[j]+c_s+")"+signal[k]+d_s;
                    return solution;
                }
                //(a#(b#c))#d
                answer = operators[k](operators[j](a, operators[i](b, c)) , d);
                if(fabs(answer -24.0)<1E-6)
                {
                    solution = "("+a_s+signal[j]+"("+b_s+signal[i]+c_s+"))"+signal[k]+d_s;
                    return solution;
                }
                //a#((b#c)#d)
                answer = operators[k](a, operators[j](operators[i](b, c) , d));
                if(fabs(answer -24.0)<1E-6)
                {
                    solution = a_s+signal[k]+"(("+b_s+signal[i]+c_s+")"+signal[j]+d_s+")";
                    return solution;
                }
                //(a#b)#(c#d)
                answer = operators[k](operators[i](a, b), operators[j](c, d));
                if(fabs(answer -24.0)<1E-6)
                {
                    solution = "("+a_s+signal[i]+b_s+")"+signal[k]+"("+c_s+signal[j]+d_s+")";
                    return solution;
                }
                //a#(b#(c#d))
                answer = operators[k](a, operators[j](b, operators[i](c, d)));
                if(fabs(answer -24.0)<1E-6)
                {
                    solution = a_s+signal[k]+"("+b_s+signal[j]+"("+c_s+signal[i]+d_s+"))";
                    return solution;
                }
            }
        }
    }
    return "No solution!";
}
