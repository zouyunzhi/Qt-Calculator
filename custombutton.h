#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QWidget>
#include <QPushButton>

using namespace std;

class CustomButton : public QWidget
{
    Q_OBJECT
public:
    explicit CustomButton(
        QWidget *parent = nullptr,
        const QString& _text = "",
        int r = 0,
        int c = 0,
        function<void()> clickFunc = nullptr
        );
    ~CustomButton();
    void click();

private:
    QPushButton* button;
};

#endif // CUSTOMBUTTON_H
