#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<ctime>
#include "QMessageBox.h"
#include<cmath>
#include "qmath.h"
#include "menu.h"


static bool isSignal(QChar c);

static QString getAnswer(double a, double b, double c, double d);
MainWindow::MainWindow(QWidget *parent, QString name) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->username->setText(tr("加油，") + name);
    input_no_flag = false;
    timer = new QTimer(this);
    interval = 45;
    showtime = interval;
    score = users.get_score(name);
    username = name;
    time = users.get_time(name);
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
    connect(ui->answerButton,&QPushButton::clicked,this,get_hint);
    connect(ui->exitButton,&QPushButton::clicked,this,exit_game);
    connect(timer,SIGNAL(timeout()),this,SLOT(show_time()));
    putCards();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::clear()
{
    clear_equation();
    ui->output->setText(equation_for_show);
}
void MainWindow::putCards()
{
    clear();
    input_no_flag = false;
    srand(std::time(nullptr));
    int prob = rand()%20+1; //控制无解题的数量，概率为1/20
    if(prob <= 19)
    {
        do
        {
            for(int i=0;i<4;i++)
                cards[i]=Card::getRandomCard();
            while(cards[1] == cards[0])
                cards[1] = Card::getRandomCard();

            while(cards[2] == cards[0] || cards[2]==cards[1])
                cards[2] = Card::getRandomCard();

            while(cards[3] == cards[0] || cards[3] == cards[1] || cards[3] == cards[2])
                cards[3] = Card::getRandomCard();
        }while(!hasAnswer(cards[0].getValue(),cards[1].getValue(),cards[2].getValue(),cards[3].getValue()));
    }
    else
    {
        do
        {
            for(int i=0;i<4;i++)
                cards[i]=Card::getRandomCard();
            while(cards[1] == cards[0])
                cards[1] = Card::getRandomCard();

            while(cards[2] == cards[0] || cards[2]==cards[1])
                cards[2] = Card::getRandomCard();

            while(cards[3] == cards[0] || cards[3] == cards[1] || cards[3] == cards[2])
                cards[3] = Card::getRandomCard();
        }while(hasAnswer(cards[0].getValue(),cards[1].getValue(),cards[2].getValue(),cards[3].getValue()));
    }
    ui->card1->setStyleSheet(cards[0].getBackground());
    ui->card2->setStyleSheet(cards[1].getBackground());
    ui->card3->setStyleSheet(cards[2].getBackground());
    ui->card4->setStyleSheet(cards[3].getBackground());
    time = time + interval - showtime;
    ui->time->setText(convert_time(time));
    showtime = interval;
    ui->timeLabel->setText(QString::number(showtime,10));
    timer->start();
}

Card Card::getRandomCard()
{
    Card new_card;
    new_card.value = rand()%13+1;
    new_card.background = "border-image:url(':/images/"+new_card.types[rand()%4]+QString::number(new_card.getValue())+".png')";
    return new_card;
}

Card Card::getValuedCard(int num)
{
    Card new_card;
    new_card.value = num;
    new_card.background = "border-image:url(':/images/"+new_card.types[rand()%4]+QString::number(new_card.getValue())+".png')";
    return new_card;
}

Card &Card::operator=(const Card & c)
{
    value = c.getValue();
    background = c.background;
    return *this;
}

bool Card::operator ==(const Card & c) const
{
    if(value == c.value && background == c.background)
        return true;
    else
        return false;
}
void MainWindow::clear_equation()
{
    equation.clear();
    equation_for_show.clear();
    for(int i=0;i<4;i++)
        cards[i].checked = false;
    sequence.fill(nullptr,4);
    seq=-1;
}
void MainWindow::showErrorDialog(QString info)
{
    QMessageBox::information(this,tr("提示信息"),info,QMessageBox::Yes);
}

void MainWindow::input_plus()
{
    check_input_no();
    check_erase_signal();
    if(!equation.isEmpty())
        append("+");
}

void MainWindow::input_minus()
{
    check_input_no();
    check_erase_signal();
    if(!equation.isEmpty())
        append("-");
}

void MainWindow::input_times()
{
    check_input_no();
    check_erase_signal();
    if(!equation.isEmpty())
        append("*");
}

void MainWindow::input_divide()
{
    check_input_no();
    check_erase_signal();
    if(!equation.isEmpty())
        append("/");
}

 void MainWindow::input_power()
 {
    check_input_no();
    check_erase_signal();
    if(!equation.isEmpty())
        append("^");
 }

void MainWindow::input_left()
{
    check_input_no();
    append("(");
}

void MainWindow::input_right()
{
    check_input_no();
    if(equation_for_show[equation.size()-1] == '(')
    {
        equation_for_show += "0";
        equation += "0";
    }
    append(")");
}

void MainWindow::input_no()
{
    clear();
    equation_for_show = "No solution";
    input_no_flag = true;
    ui->output->setText(equation_for_show);
}

void MainWindow::check_erase_signal()
{
    if(equation.size()>0&&isSignal(equation[equation.size()-1]))
    {
        equation_for_show.resize(equation.size()-1);
        equation.resize(equation.size()-1);
    }
}

void MainWindow::check_input_no()
{
    if(input_no_flag)
    {
        clear();
        input_no_flag = true;
    }
}

void MainWindow::append(QString c)
{
    equation_for_show += c;
    equation += c;
    ui->output->setText(equation_for_show);
}

static bool isSignal(QChar c)
{
    return (c=='+'||c=='-'||c=='*'||c=='/'||c=='^');
}

void MainWindow::on_card1_clicked()
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

void MainWindow::on_card2_clicked()
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

void MainWindow::on_card3_clicked()
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

void MainWindow::on_card4_clicked()
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

void MainWindow::backspace()
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

void MainWindow::equal()
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
            putCards();
        }
        else
        {
            timer->stop();
            ui->score->setText(QString::number(++score));
            showErrorDialog("恭喜你答对了！");
            clear();
            putCards();
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
                putCards();
            }
            else
            {
                timer->stop();
                QString solution = getAnswer(cards[0].getValue(),cards[1].getValue(),cards[2].getValue(),cards[3].getValue());
                showErrorDialog(tr("答错了，下题加油!") + "\n" + "参考答案: " + solution);
                time = time + 30;
                clear();
                putCards();
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

double MainWindow::calculate(QString & equation)
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

void MainWindow::show_time()
{
    showtime--;
    ui->timeLabel->setText(QString::number(showtime,10));
    if(showtime == 0)
    {
        timer->stop();
        QString solution = getAnswer(cards[0].getValue(),cards[1].getValue(),cards[2].getValue(),cards[3].getValue());
        showErrorDialog(tr("你已超时,下题加油!") + "\n" + "参考答案: " + solution);
        ui->timeLabel->setText(QString::number(showtime,10));
        putCards();
    }
}

void MainWindow::exit_game()
{
    QString name = ui->username->text();
    users.save(name,score,1);
    users.save(name,time,2);
    delete timer;
    this->close();
    Menu menu(0,name);
    menu.show();
    menu.exec();
}

void MainWindow::get_hint()
{
    timer->stop();
    QString solution = getAnswer(cards[0].getValue(),cards[1].getValue(),cards[2].getValue(),cards[3].getValue());
    showErrorDialog("参考答案: " + solution + "\n" + "下题加油!");
    time = time + 10;
    clear();
    putCards();
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
bool MainWindow::hasAnswer(double a, double b, double c, double d)//穷举所有情况看是否有解
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
