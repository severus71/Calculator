#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QToolButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QDebug>
#include <QMessageBox>
#include <QChar>
#include "button.h"

class Calculator : public QWidget
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = 0);
    Button* InitButton(const QString &showStr, const char *method);
    ~Calculator();
    
private:
    enum {DIGTALNUM = 10};
    QLineEdit *showLineEdit;
    QGridLayout *mainLayout;
    Button *clearBtn, *backspaceBtn, *sumBtn, *subBtn, *multiplyBtn, *divideBtn, *equalbtn, *percentbtn, *pointBtn;
    Button *digtal[DIGTALNUM];

    bool cleanFlag, cleanAll, percentFlag;

    QChar op;
    double result;

private slots:
    void DigtalSlot();
    void PointSlot();
    void PercentSlot();
    void ClearSlot();
    void BackspaceSlot();
    void OperatorSlot();
    void EqualSlot();

private:
    double CalResult(double result, QChar op, double displayNum);
};

#endif // CALCULATOR_H
