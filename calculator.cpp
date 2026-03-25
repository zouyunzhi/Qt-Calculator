#include "calculator.h"
#include "ui_calculator.h"
#include <QMessageBox>
#include <QKeyEvent>
#include <QMenu>
#include <exprtk.hpp>
using namespace exprtk;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
    , textlist(row, QList<QString>(col))
    , formula(new InputBox(this, QRect(10, 40, 380, 80), "[0-9+\\-\\*\\/\\.\\(\\)]+"))
    , result(new InputBox(this, QRect(10, 150, 380, 80), "[0-9]+"))
    , translator(new QTranslator(this))
    , settings("ZouYunzhi", "Calculator")
{
    setupUi();
}

Calculator::~Calculator(){
    settings.sync();
    delete ui;
}

void Calculator::setupUi(){
    ui->setupUi(this);
    initMenuBar();
    resize(400, 740);
    setWindowTitle("计算器 1.0.0");
    setWindowIcon(QIcon(":/logo.jpeg"));
    textlist = {
        {"(", ")", "C", "+"},
        {"7", "8", "9", "-"},
        {"4", "5", "6", "*"},
        {"1", "2", "3", "/"},
        {"←", "0", ".", "="}
    };
    result->setCursorHideState(true);
    for(int i = 0; i < row; i++){
        for(int j = 0; j < col; j++){
            QString button_str = textlist[i][j];
            buttons[i][j] = new CustomButton(this, button_str, i, j, createButtonFunc(button_str));
        }
    }
    if(!settings.allKeys().isEmpty()){
        changeLanguage(settings.value("Language").toString());
    }else{
        changeLanguage("en_US");
    }
    retranslateUi();
}

void Calculator::retranslateUi(){
    setWindowTitle(tr("计算器 1.0.0"));
    language->setTitle(tr("语言"));
    about->setTitle(tr("关于"));
    aboutCalc->setText(tr("关于计算器"));
    aboutQt->setText(tr("关于qt"));
}

void Calculator::initMenuBar(){
    menuBar()->setFixedSize(750, 20);
    menuBar()->setStyleSheet("QMenuBar { background-color: skyblue; color: black; } "
                             "QMenuBar::item:selected { background-color: #1e3a5f; }");
    language = menuBar()->addMenu(tr("语言"));
    about = menuBar()->addMenu(tr("关于"));
    for(const auto& [name, code] : languages){
        QAction* action = new QAction(name, this);
        action->setData(code);
        connect(action, &QAction::triggered, this, [this, code](){
            changeLanguage(code);
        });
        language->addAction(action);
    }
    aboutCalc = new QAction(tr("关于计算器"), this);
    aboutQt = new QAction(tr("关于qt"), this);
    connect(aboutCalc, &QAction::triggered, this, [this](){
        QMessageBox::about(
            this,
            tr("关于计算器"),
            tr(
               "计算器 1.0.0\n"
               "作者：邹允之\n"
               "这是一个简单优雅的计算器应用，有加减乘除计算这些基本功能"
            )
        );
    });
    connect(aboutQt, &QAction::triggered, this, [this](){
        QMessageBox::aboutQt(this);
    });
    about->addAction(aboutCalc);
    about->addAction(aboutQt);
}

void Calculator::changeLanguage(const QString& code){
    if(!translator->isEmpty()){
        qApp->removeTranslator(translator);
    }
    QString filename(QString(":/translations/%1.qm").arg(code));
    if(!translator->load(filename)){
        QMessageBox::critical(this, tr("错误"), tr("无法加载翻译文件!"));
        return;
    }
    qApp->installTranslator(translator);
    settings.setValue("Language", code);
    retranslateUi();
}

function<void()> Calculator::createButtonFunc(const QString& str){
    if(str == "C"){
        return [this](){
            formula->clear();
            result->clear();
            result->setCursorHideState(true);
        };
    }else if(str == "←"){
        return [this](){
            if(!formula->text().isEmpty()){
                formula->setText(formula->text().chopped(1));
            }
        };
    }else if(str == "="){
        return [this](){
            if(calculate(formula->text())){
                result->setCursorHideState(false);
            }
        };
    }else{
        return [this, str](){
            formula->setText(formula->text() + str);
        };
    }
}

bool Calculator::calculate(const QString& formula_str){
    if(formula_str.isEmpty()){
        QMessageBox::warning(this, tr("提示"), tr("表达式为空，请先输入表达式!"));
        return false;
    }
    try{
        expression<double> expr;
        parser<double> par;
        string std_formula = formula_str.toStdString();
        if(par.compile(std_formula, expr)){
            double res = expr.value();
            result->setText(QString::number(res, 'g', 16).remove(QRegularExpression("\\.?S0+$")));
            QMessageBox::information(this, tr("计算完成"), tr("计算完成啦————快去查看结果吧!"));
        }else{
            QMessageBox::critical(this, tr("计算错误"), tr("表达式语法错误!请重新输入表达式"));
        }
    }catch(const exception& e){
        QString error_str = QString("计算失败!错误原因:%1").arg(e.what());
        QMessageBox::critical(this, tr("运行错误"), tr(error_str.toStdString().c_str()));
        return false;
    }
    return true;
}

void Calculator::keyPressEvent(QKeyEvent* event){
    int key = event->key();
    if(key == Qt::Key_Enter || key == Qt::Key_Return){
        buttons[4][3]->click();
    }else if(key == Qt::Key_Escape){
        buttons[0][2]->click();
    }
    QWidget::keyPressEvent(event);
}
