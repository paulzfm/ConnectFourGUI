#include "setting_dialog.h"
#include "ui_setting_dialog.h"
#include "controller.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QDebug>

SettingDialog::SettingDialog(QWidget *parent, bool random) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

    _params.boardM = 8;
    _params.boardN = 8;
    _params.firstPlayer = Game::BLACK_PLAYER;
    _params.isRandom = false;
    _params.blackPlayer = Controller::HUMAN;
    _params.whitePlayer = Controller::HUMAN;

    ui->blackFirst->setChecked(true);
    ui->boardSizeM->setValue(_params.boardM);
    ui->boardSizeN->setValue(_params.boardN);
    ui->blackIsHuman->setChecked(true);
    ui->blackStrategy->setEnabled(false);
    ui->whiteIsHuman->setChecked(true);
    ui->whiteStrategy->setEnabled(false);

    if (random) {
        _params.isRandom = true;
        ui->isRandom->setChecked(true);
    }
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::getParams(Params &params)
{
    params = _params;
}

void SettingDialog::accept()
{
    // check
    if (_params.blackPlayer == Controller::COMPUTER && _params.blackStrategy == "") {
        QMessageBox::warning(this, "Error", "Please select a dynamic library file for black",
                             QMessageBox::Ok);
        return;
    }
    if (_params.whitePlayer == Controller::COMPUTER && _params.whiteStrategy == "") {
        QMessageBox::warning(this, "Error", "Please select a dynamic library file for white",
                             QMessageBox::Ok);
        return;
    }

    QDialog::accept();
}

void SettingDialog::on_isRandom_clicked(bool checked)
{
    if (checked) {
        ui->boardSizeM->setEnabled(false);
        ui->boardSizeN->setEnabled(false);
        ui->blackFirst->setEnabled(false);
        ui->whiteFirst->setEnabled(false);
        _params.isRandom = true;
    } else {
        ui->boardSizeM->setEnabled(true);
        ui->boardSizeN->setEnabled(true);
        ui->blackFirst->setEnabled(true);
        ui->whiteFirst->setEnabled(true);
        _params.isRandom = false;
    }
}

void SettingDialog::on_blackIsHuman_clicked()
{
    ui->blackStrategy->setEnabled(false);
    _params.blackPlayer = Controller::HUMAN;
}

void SettingDialog::on_whiteIsHuman_clicked()
{
    ui->whiteStrategy->setEnabled(false);
    _params.whitePlayer = Controller::HUMAN;
}

void SettingDialog::on_blackIsComputer_clicked()
{
    ui->blackStrategy->setEnabled(true);
    _params.blackPlayer = Controller::COMPUTER;
}

void SettingDialog::on_whiteIsComputer_clicked()
{
    ui->whiteStrategy->setEnabled(true);
    _params.whitePlayer = Controller::COMPUTER;
}

void SettingDialog::on_blackStrategy_released()
{
    QString path = ".";
    if (_params.blackStrategy != "") {
        path = QString::fromStdString(_params.blackStrategy);
    } else if (_params.whiteStrategy != "") {
        path = QString::fromStdString(_params.whiteStrategy);
    }

    QString file = QFileDialog::getOpenFileName(this,
        tr("Select dynamic library file (for Black)"), path, tr("Dynamic Library (*.dylib *.dll)"));
    if (file != "") {
        _params.blackStrategy = file.toStdString();
        ui->blackStrategy->setText(QFileInfo(file).fileName());
    } else {
        ui->blackStrategy->setText("Strategy File");
    }

    qDebug() << file;
    std::cout << _params.blackStrategy << std::endl;
}

void SettingDialog::on_whiteStrategy_released()
{
    QString path = ".";
    if (_params.whiteStrategy != "") {
        path = QString::fromStdString(_params.whiteStrategy);
    } else if (_params.blackStrategy != "") {
        path = QString::fromStdString(_params.blackStrategy);
    }

    QString file = QFileDialog::getOpenFileName(this,
        tr("Select dynamic library file (for White)"), path, tr("Dynamic Library (*.dylib *.dll)"));
    if (file != "") {
        _params.whiteStrategy = file.toStdString();
        ui->whiteStrategy->setText(QFileInfo(file).fileName());
    } else {
        ui->whiteStrategy->setText("Strategy File");
    }
}

void SettingDialog::on_blackFirst_clicked()
{
    _params.firstPlayer = Game::BLACK_PLAYER;
}

void SettingDialog::on_whiteFirst_clicked()
{
    _params.firstPlayer = Game::WHITE_PLAYER;
}

void SettingDialog::on_boardSizeM_valueChanged(int arg1)
{
    _params.boardM = arg1;
}

void SettingDialog::on_boardSizeN_valueChanged(int arg1)
{
    _params.boardN = arg1;
}
