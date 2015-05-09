#include "setting_dialog.h"
#include "ui_setting_dialog.h"
#include "controller.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

SettingDialog::SettingDialog(QWidget *parent, bool random, bool compete) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

    this->on_blackIsHuman_clicked();
    this->on_whiteIsHuman_clicked();
    ui->blackIsHuman->setChecked(true);
    ui->whiteIsHuman->setChecked(true);
    ui->boardSizeM->setValue(8);
    ui->boardSizeN->setValue(8);
    ui->blackFirst->setChecked(true);

    if (random) {
        ui->isRandom->setChecked(true);
        this->on_isRandom_clicked(true);
    } else {
        this->on_boardSizeM_valueChanged(8);
        this->on_boardSizeN_valueChanged(8);
        this->on_blackFirst_clicked();
    }

    ui->grpSpeed->setVisible(false);
    ui->speed->setRange(0, 5);
    ui->speed->setValue(1);
    this->on_speed_valueChanged(1);

    if (compete) {
        QFile file("setting.txt");
        if (!file.open(QIODevice::ReadOnly)) {
            // ignore this setting
        } else {
            QTextStream fin(&file);
            QString path;
            fin >> path;
            ui->blackIsComputer->setChecked(true);
            ui->blackStrategy->setText(QFileInfo(path).fileName());
            this->on_blackIsComputer_clicked();
            _params.blackPlayer = Controller::COMPUTER;
            _params.blackStrategy = path.toStdString();
        }
        file.close();
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
    ui->grpSpeed->setVisible(false);
}

void SettingDialog::on_whiteIsHuman_clicked()
{
    ui->whiteStrategy->setEnabled(false);
    _params.whitePlayer = Controller::HUMAN;
    ui->grpSpeed->setVisible(false);
}

void SettingDialog::on_blackIsComputer_clicked()
{
    ui->blackStrategy->setEnabled(true);
    _params.blackPlayer = Controller::COMPUTER;

    if (_params.whitePlayer == Controller::COMPUTER) {
        ui->grpSpeed->setVisible(true);
    }
}

void SettingDialog::on_whiteIsComputer_clicked()
{
    ui->whiteStrategy->setEnabled(true);
    _params.whitePlayer = Controller::COMPUTER;

    if (_params.blackPlayer == Controller::COMPUTER) {
        ui->grpSpeed->setVisible(true);
    }
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

void SettingDialog::on_speed_valueChanged(int arg1)
{
    _params.interval = arg1;
}
