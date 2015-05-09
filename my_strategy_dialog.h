#ifndef MY_STRATEGY_DIALOG_H
#define MY_STRATEGY_DIALOG_H

#include <QDialog>

namespace Ui {
class MyStrategyDialog;
}

class MyStrategyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyStrategyDialog(QWidget *parent = 0);
    ~MyStrategyDialog();

private slots:
    void on_change_clicked();

private:
    Ui::MyStrategyDialog *ui;
};

#endif // MY_STRATEGY_DIALOG_H
