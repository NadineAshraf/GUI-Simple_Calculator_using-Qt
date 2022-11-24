#include "calculator.h"
#include "qpushbutton.h"
#include "ui_calculator.h"
double calcVal = 0.0;
bool divTrigger = false;
bool mulTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i=0; i<10; ++i){
        QString butName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this,
                SLOT(NumPressed()));
    }
    connect(ui->Add, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Equals, SIGNAL(released()), this,
             SLOT(EqualButtonPressed()));
    connect(ui->ChangeSign, SIGNAL(released()), this,
            SLOT(ChangeNumberSign()));
    connect(ui->Clear, SIGNAL(released()), this,
            SLOT(ClearPressed()));
}

Calculator::~Calculator()
{
    delete ui;
}
void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    QString displayVal = ui->Display->text();
    if((displayVal.toDouble() == 0) || (displayVal.toDouble()== 0.0))
    {
        ui ->Display->setText(butVal);
    }
    else
    {
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui -> Display->setText(QString::number(dblNewVal,'g',16));
    }
}
void Calculator::MathButtonPressed(){
    divTrigger = false;
    mulTrigger = false;
    addTrigger = false;
    subTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal,"/", Qt::CaseInsensitive) == 0)
    {
        divTrigger = true;
    }
    else if(QString::compare(butVal,"*", Qt::CaseInsensitive) == 0)
    {
        mulTrigger = true;
    }
    else if(QString::compare(butVal,"+", Qt::CaseInsensitive) == 0)
    {
        addTrigger = true;
    }
    else
    {
        subTrigger = true;
    }
    ui->Display->setText("");
}
void Calculator::EqualButtonPressed()
{
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if(addTrigger || subTrigger || mulTrigger || divTrigger)
    {
        if(addTrigger)
        {
            solution = calcVal + dblDisplayVal;
        }
        else if(subTrigger)
        {
            solution = calcVal - dblDisplayVal;
        }
        else if(mulTrigger)
        {
            solution = calcVal * dblDisplayVal;
        }
        else
        {
            solution = calcVal / dblDisplayVal;
        }
    }
    ui ->Display->setText(QString::number(solution));
}
 void Calculator::ChangeNumberSign()
 {
      QPushButton * button = (QPushButton*)sender();
     QString displayVal = ui->Display->text();


     if(button->text() == "+/-")
     {
         double dblDisplayVal = displayVal.toDouble();
         double dbDisplayValSign = -1 * dblDisplayVal;
         ui ->Display->setText((QString::number(dbDisplayValSign)));
     }

 }
 void Calculator::ClearPressed()
 {
     QPushButton * button = (QPushButton*)sender();
    QString displayVal = ui->Display->text();
    if(button->text() == "AC")
    {
     ui->Display->setText("");
    }
 }

