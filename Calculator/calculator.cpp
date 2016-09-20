#include <QMessageBox>
#include <cmath>
#include "calculator.h"

Calculator::Calculator(QWidget *parent)
    : QWidget(parent)
{
    cleanFlag = false;
    op = '@';
    result = 0;

    mainLayout = new QGridLayout;
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    showLineEdit = new QLineEdit;
    showLineEdit->setReadOnly(true);
    showLineEdit->setAlignment(Qt::AlignRight);
    showLineEdit->setMaxLength(12);

    QFont font = showLineEdit->font();
    font.setPointSize(font.pointSize() + 8);
    showLineEdit->setFont(font);
    showLineEdit->setText(tr("0"));

    mainLayout->addWidget(showLineEdit, 0, 0, 1, 4);

    for(int i = 1; i < DIGTALNUM; ++i)
    {
        digtal[i] = InitButton(QString::number(i), SLOT(DigtalSlot()));
        mainLayout->addWidget(digtal[i], 4 - ((i - 1) / 3), (i - 1) % 3);
    }

    clearBtn = InitButton(tr("C"), SLOT(ClearSlot()));
    mainLayout->addWidget(clearBtn, 1, 0);

    backspaceBtn = InitButton(tr("←"), SLOT(BackspaceSlot()));
    mainLayout->addWidget(backspaceBtn, 1, 1);

    divideBtn = InitButton(tr("/"), SLOT(OperatorSlot()));
    mainLayout->addWidget(divideBtn, 1, 2);

    multiplyBtn = InitButton(tr("X"), SLOT(OperatorSlot()));
    mainLayout->addWidget(multiplyBtn, 1, 3);

    subBtn = InitButton(tr("-"), SLOT(OperatorSlot()));
    mainLayout->addWidget(subBtn, 2, 3);

    sumBtn = InitButton(tr("+"), SLOT(OperatorSlot()));
    mainLayout->addWidget(sumBtn, 3, 3);

    equalbtn = InitButton(tr("="), SLOT(EqualSlot()));
    mainLayout->addWidget(equalbtn, 4, 3, 2, 1);

    percentbtn = InitButton(tr("%"), SLOT(PercentSlot()));
    mainLayout->addWidget(percentbtn, 5, 0);

    digtal[0] = InitButton(tr("0"), SLOT(DigtalSlot()));
    mainLayout->addWidget(digtal[0], 5, 1);

    pointBtn = InitButton(tr("."), SLOT(PointSlot()));
    mainLayout->addWidget(pointBtn, 5, 2);

    setLayout(mainLayout);
}


Button* Calculator::InitButton(const QString &showStr, const char * method)
{
    Button *btn = new Button(showStr);
    QObject::connect(btn, SIGNAL(clicked(bool)), this, method);
    return btn;
}

Calculator::~Calculator()
{

}

// 如果cleanFlag为true则清除所有，再setText, cleanFlag = false
// 如果cleanFlag为false,
    // 判断当前的值为０，直接setText(length == 1 && displayNum == 0) cleanFlag = false, 否则追加
void Calculator::DigtalSlot()
{
    Button *btn = ((Button *)this->sender());
    double displayNum = showLineEdit->text().toDouble();
    if(cleanFlag)
    {
        showLineEdit->setText(btn->text());
        cleanFlag = false;
    }
    else
    {
        if(showLineEdit->text().length() == 1 && displayNum == 0)
        {
            showLineEdit->setText(btn->text());
            cleanFlag = false;
        }
        else
        {
            showLineEdit->insert(btn->text());
        }
    }
}

// 小数点，如果字符串中包含'.'直接返回，否则追加'.'
void Calculator::PointSlot()
{
    Button *btn = ((Button *)this->sender());
    if(showLineEdit->text().contains('.'))
    {
        return;
    }
    else
    {
        showLineEdit->insert(btn->text());
    }
}

// 百分号，直接除１００, cleanFlag = true;
void Calculator::PercentSlot()
{
    double displayNum = showLineEdit->text().toDouble();
    showLineEdit->setText(QString::number(displayNum / 100));
    cleanFlag = true;
}

//　清楚全部数据, cleanFlag = false; op = '@'
void Calculator::ClearSlot()
{
    result = 0;
    op == '@';
    cleanFlag = false;
    showLineEdit->setText("0");
}

// 退格，如果删除全部则 setText 0并且cleanFlag = false;
void Calculator::BackspaceSlot()
{
    showLineEdit->backspace();
    if(showLineEdit->text().isEmpty())
    {
        showLineEdit->setText("0");
        cleanFlag = false;
    }
}

// 如果cleanFlag为false,且op != '@'，则计算结果并显示,再保存运算符
// 否则保存运算符（最后一个为准）和当前的值，cleanFlag = true;
void Calculator::OperatorSlot()
{
    Button *btn = ((Button *)this->sender());
    if(!cleanFlag && op != '@')
    {
        //　计算结果，并显示
        double tmp = CalResult(result, op, showLineEdit->text().toDouble());
        showLineEdit->setText(QString::number(tmp));
    }

    result = showLineEdit->text().toDouble();
    op = btn->text().at(0);
    qDebug() << op;

    cleanFlag = true;
}

// 如果　op == '@' 不做任何处理
//  计算结果，并显示，且cleanFlag = true, result = 0, op = '@'
void Calculator::EqualSlot()
{
    if(op == '@')
    {
        return;
    }
    double tmp = CalResult(result, op, showLineEdit->text().toDouble());
    showLineEdit->setText(QString::number(tmp));
    cleanFlag = true;
    result = 0;
    op = '@';
}

// 计算结果
double Calculator::CalResult(double result, QChar op, double displayNum)
{
    switch(op.toLatin1())
    {
    case '+':
        result += displayNum;
        break;
    case '-':
        result -= displayNum;
        break;
    case '*':
        result *= displayNum;
        break;
    case '/':
        if(displayNum == 0)
        {
            QMessageBox::information(this, QString::fromUtf8("提示"), QString::fromUtf8("除数不能为０"));
            return result;
        }
        else
        {
            result /= displayNum;
        }
        break;
    default:
        break;
    }
    this->op = '@';
    return result;
}
