#ifndef INPUTBOX_H
#define INPUTBOX_H

#include <QWidget>
#include <QLineEdit>
#include <QRegularExpressionValidator>

class InputBox : public QWidget
{
    Q_OBJECT
public:
    explicit InputBox(QWidget *parent = nullptr, const QRect& rect = QRect(0, 0, 0, 0), const QString& exstr = "");
    ~InputBox();
    QString text() const;
    void clear();
    void setText(const QString& text);
    void setCursorHideState(bool state);

private:
    QLineEdit* edit;
    QRegularExpression* re;
    QRegularExpressionValidator* validator;
};

#endif // INPUTBOX_H
