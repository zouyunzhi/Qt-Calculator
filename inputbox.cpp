#include "inputbox.h"
#include <QApplication>

InputBox::InputBox(QWidget *parent, const QRect& rect, const QString& exstr)
    : QWidget(parent)
    , re(new QRegularExpression(exstr))
    , validator(new QRegularExpressionValidator(*re, this))
    , edit(new QLineEdit(parent))
{
    QFont font = qApp->font();
    font.setPointSize(24);
    edit->setValidator(validator);
    edit->setGeometry(rect);
    edit->setAlignment(Qt::AlignLeft);
    edit->setFont(font);
    edit->setStyleSheet("QLineEdit{border: 2px solid black; border-radius: 5px}");
}

InputBox::~InputBox(){
    delete edit;
    delete re;
    delete validator;
}

QString InputBox::text() const {
    return edit->text();
}

void InputBox::clear(){
    edit->clear();
}

void InputBox::setText(const QString& text){
    edit->setText(text);
}

void InputBox::setCursorHideState(bool state){
    edit->setReadOnly(state);
}
