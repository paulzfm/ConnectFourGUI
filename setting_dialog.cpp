#include "setting_dialog.h"
#include "ui_setting_dialog.h"
#include "controller.h"

#include <QFileDialog>
#include <QFileInfo>

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

    _params.boardM = 10;
    _params.boardN = 10;
    _params.firstPlayer == Game::BLACK_PLAYER;
    _params.isRandom = false;
    _params.blackPlayer = Controller::HUMAN;
    _params.whitePlayer = Controller::HUMAN;
    _params.blackStrategy = NULL;
    _params.whiteStrategy = NULL;

    ui->blackFirst->setChecked(true);
    ui->boardSizeM->setValue(_params.boardM);
    ui->boardSizeN->setValue(_params.boardN);
    ui->blackIsHuman->setChecked(true);
    ui->blackStrategy->setEnabled(false);
    ui->whiteIsHuman->setChecked(true);
    ui->whiteStrategy->setEnabled(false);
}

SettingDialog::~SettingDialog()
{
    delete ui;
}

Params SettingDialog::param()
{
    return _params;
}

void SettingDialog::accept()
{
    // check
    if (_params.blackPlayer == Controller::COMPUTER && _params.blackStrategy == NULL) {

    }
    if (_params.whitePlayer == Controller::COMPUTER && _params.whiteStrategy == NULL) {

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
    if (_params.blackStrategy != NULL) {
        path = QString::fromStdString(_params.blackStrategy);
    } else if (_params.whiteStrategy != NULL) {
        path = QString::fromStdString(_params.whiteStrategy);
    }

    QString file = QFileDialog::getOpenFileName(this,
        tr("Select dynamic library file (for Black)"), path, tr("Dynamic Library (*.dylib *.dll)"));
    if (file != "") {
        _params.blackStrategy = file.toStdString().c_str();
        ui->blackStrategy->setText(QFileInfo(file).fileName());
    } else {
        ui->blackStrategy->setText("Strategy File");
    }
}

void SettingDialog::on_whiteStrategy_released()
{
    QString path = ".";
    if (_params.whiteStrategy != NULL) {
        path = QString::fromStdString(_params.whiteStrategy);
    } else if (_params.blackStrategy != NULL) {
        path = QString::fromStdString(_params.blackStrategy);
    }

    QString file = QFileDialog::getOpenFileName(this,
        tr("Select dynamic library file (for White)"), path, tr("Dynamic Library (*.dylib *.dll)"));
    if (file != "") {
        _params.whiteStrategy = file.toStdString().c_str();
        ui->whiteStrategy->setText(QFileInfo(file).fileName());
    } else {
        ui->whiteStrategy->setText("Strategy File");
    }
}
