#ifndef SETTING_DIALOG_H
#define SETTING_DIALOG_H

#include "controller.h"

#include <QDialog>

namespace Ui {
class SettingDialog;
}


class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent, Params& old, bool compete = false);
    ~SettingDialog();

    void getParams(Params& params);
    void accept();

private slots:
    void on_isRandom_clicked(bool checked);
    void on_blackIsHuman_clicked();
    void on_whiteIsHuman_clicked();
    void on_blackIsComputer_clicked();
    void on_whiteIsComputer_clicked();
    void on_blackStrategy_released();
    void on_whiteStrategy_released();
    void on_blackFirst_clicked();
    void on_whiteFirst_clicked();
    void on_boardSizeM_valueChanged(int arg1);
    void on_boardSizeN_valueChanged(int arg1);
    void on_speed_valueChanged(int arg1);

private:
    Ui::SettingDialog *ui;
    Params _params;
};

#endif // SETTING_DIALOG_H
