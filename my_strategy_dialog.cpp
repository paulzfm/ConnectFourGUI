#include "my_strategy_dialog.h"
#include "ui_my_strategy_dialog.h"

#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QIODevice>

MyStrategyDialog::MyStrategyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyStrategyDialog)
{
    ui->setupUi(this);

    QFile file("setting.txt");
    if (!file.open(QIODevice::ReadOnly)) {
        ui->info->setText("No files found. Please click \"change\" button to specify!");
    } else {
        QTextStream fin(&file);
        QString path;
        fin >> path;
        ui->info->setText("Current file: " + path);
    }
    file.close();
}

MyStrategyDialog::~MyStrategyDialog()
{
    delete ui;
}

void MyStrategyDialog::on_change_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,
        tr("Select dynamic library file"), "~", tr("Dynamic Library (*.dylib *.dll)"));
    if (path != "") {
        QFile file("setting.txt");
        if (!file.open(QIODevice::WriteOnly)) {
            fprintf(stderr, "***Error: cannot open file \"%s\".", path.toStdString().c_str());
        } else {
            QTextStream fout(&file);
            fout << path;
            ui->info->setText("Current file: " + path);
        }
        file.close();
    }
}
