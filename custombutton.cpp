#include "custombutton.h"
#include <QApplication>

CustomButton::CustomButton(
    QWidget *parent,
    const QString& _text,
    int r,
    int c,
    function<void()> clickFunc
    )
    : QWidget(parent)
    , button(new QPushButton(_text, parent))
{
    QFont font = qApp->font();
    font.setPointSize(15);
    button->setGeometry(QRect(c * 100, r * 100 + 240, 100, 100));
    button->setFont(font);
    if(r == 4 && c == 3){
        button->setStyleSheet("background-color: skyblue;");
    }
    connect(button, &QPushButton::clicked, this, [clickFunc](){
        if(clickFunc){
            clickFunc();
        }
    });
}

CustomButton::~CustomButton(){
    delete button;
}

void CustomButton::click(){
    button->click();
}
