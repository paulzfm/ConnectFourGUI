#ifndef SETTING_DIALOG_H
#define SETTING_DIALOG_H

#include <QDialog>

namespace Ui {
class SettingDialog;
}

struct Params
{
    int boardM;
    int boardN;
    int firstPlayer;
    bool isRandom;
    int blackPlayer;
    int whitePlayer;
    const char* blackStrategy;
    const char* whiteStrategy;
};

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();

    Params param();
    void accept();

private slots:
    void on_isRandom_clicked(bool checked);
    void on_blackIsHuman_clicked();

    void on_whiteIsHuman_clicked();

    void on_blackIsComputer_clicked();

    void on_whiteIsComputer_clicked();

    void on_blackStrategy_released();

private:
    Ui::SettingDialog *ui;
    Params _params;
};

#endif // SETTING_DIALOG_H
