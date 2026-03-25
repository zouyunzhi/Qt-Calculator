#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QLineEdit>
#include <QRegularExpressionValidator>
#include <QTranslator>
#include <QSettings>
#include <custombutton.h>
#include <inputbox.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class Calculator;
}
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();
    static constexpr int row = 5;
    static constexpr int col = 4;

private:
    Ui::Calculator *ui;
    QList<QList<QString>> textlist;
    QMenu* language;
    QMenu* about;
    QAction* aboutCalc;
    QAction* aboutQt;
    CustomButton* buttons[row][col];
    InputBox* formula;
    InputBox* result;
    QTranslator* translator;
    QSettings settings;
    QList<QPair<QString, QString>> languages = {
        {"English", "en_US"},
        {"Español", "es_ES"},
        {"Français", "fr_FR"},
        {"Deutsch", "de_DE"},
        {"Italiano", "it_IT"},
        {"Português", "pt_PT"},
        {"Русский", "ru_RU"},
        {"日本語", "ja_JP"},
        {"한국어", "ko_KR"},
        {"العربية", "ar_SA"},
                  {"हिन्दी", "hi_IN"},
        {"ภาษาไทย", "th_TH"},
        {"Tiếng Việt", "vi_VN"},
        {"Nederlands", "nl_NL"},
        {"Svenska", "sv_SE"},
        {"简体中文", "zh_CN"},
        {"繁體中文", "zh_TW"}
    };
    void setupUi();
    void retranslateUi();
    void initMenuBar();
    bool calculate(const QString& formula_str);
    function<void()> createButtonFunc(const QString& str);
    void changeLanguage(const QString& code);
    void keyPressEvent(QKeyEvent* event) override;
};
#endif // CALCULATOR_H
