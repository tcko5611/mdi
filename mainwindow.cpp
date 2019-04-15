#include "mainwindow.h"
#include "MdiMainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
  QString weightFile = ui->lineEditWeight->text();
  QString templateFile = ui->lineEditTemplate->text();
  mdiMainWindow = new MdiMainWindow(weightFile, templateFile, this);
  mdiMainWindow->setWindowModality(Qt::WindowModal);
  mdiMainWindow->show();
}
