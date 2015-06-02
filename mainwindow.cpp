#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "setting_dialog.h"
#include "my_strategy_dialog.h"
#include "about_dialog.h"

#include <time.h>
#include <stdlib.h>

#include <QGridLayout>
#include <QUrl>
#include <QDesktopServices>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    srand(time(NULL));
    ui->setupUi(this);
    this->setWindowTitle("Connect Four GUI");
    this->setMinimumSize(100, 100);

    // central widget layout
    QGridLayout *layout = new QGridLayout(ui->centralWidget);
    layout->setMargin(0);

    // game info
    info = new QLabel(this);
    info->setAlignment(Qt::AlignCenter);
    layout->addWidget(info, 0, 0);

    // board
    board = new Board(this);
    layout->addWidget(board, 1, 0);

    // controller
    controller = new Controller(this);
    controller->setInfo(info);
    controller->setWindow(this);

    // status bar
    status = new QLabel(this);
    status->setMinimumSize(status->sizeHint());
    status->setAlignment(Qt::AlignHCenter);
    status->setText("Please launch a new game.");
    ui->statusBar->addWidget(status);
    controller->setStatus(status);

    // disable actions
    ui->actionReplay->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionReplay_triggered()
{
    controller->restartGame();
}

void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionStrategyFile_triggered()
{
    MyStrategyDialog *dlg = new MyStrategyDialog(this);
    dlg->exec();
}

void MainWindow::on_actionCompete_triggered()
{
    SettingDialog *dlg = new SettingDialog(this, controller->paramsBak, true);
    if (dlg->exec() == QDialog::Accepted) {
        Params params;
        dlg->getParams(params);
        controller->loadSettings(params, board);
    }
    ui->actionReplay->setEnabled(true);
}

void MainWindow::on_actionOthers_triggered()
{
    SettingDialog *dlg = new SettingDialog(this, controller->paramsBak);
    if (dlg->exec() == QDialog::Accepted) {
        Params params;
        dlg->getParams(params);
        controller->loadSettings(params, board);
    }
    ui->actionReplay->setEnabled(true);
}

void MainWindow::on_actionHelp_triggered()
{
    const QUrl url("https://github.com/paulzfm/ConnectFourGUI");
    QDesktopServices::openUrl(url);
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog *dlg = new AboutDialog(this);
    dlg->exec();
}

void MainWindow::on_actionCompeteTool_triggered()
{
    QMessageBox::information(NULL, "Information", "Please run this program from command line!",
                             QMessageBox::Ok);
}
