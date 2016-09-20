#ifndef BUTTON_H
#define BUTTON_H

#include <QToolButton>

class Button : public QToolButton
{
public:
    explicit Button(const QString &str, QWidget *parent = 0);

    QSize sizeHint() const Q_DECL_OVERRIDE;
};

#endif // BUTTON_H
