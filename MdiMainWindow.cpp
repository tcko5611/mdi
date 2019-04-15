#include <QFileInfo>
#include <QDockWidget>

#include "MdiMainWindow.h"
#include "MdiChild.h"
#include "ui_MdiMainWindow.h"

MdiMainWindow::MdiMainWindow(const QString &weightFileName,
			     const QString &templateFileName,
			     QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MdiMainWindow)
{

  ui->setupUi(this);
  QFileInfo weightFileInfo(weightFileName);
  QFileInfo templateFileInfo(templateFileName);
  if (templateFileInfo.exists()) {
    ui->actionShowTemplateFile->setEnabled(true);
    templateDock = new QDockWidget(tr("Template"), this);
    templateDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    templateChild = new MdiChild(templateFileName, templateDock);
    templateDock->setWidget(templateChild);
    if (!weightFileInfo.exists()) {
      QFile::copy(templateFileName, weightFileName);
    }
  }
  else {
    ui->actionShowTemplateFile->setEnabled(false);
  }
  weightChild = new MdiChild(weightFileName);
  setCentralWidget(weightChild);
  if (templateDock)
    addDockWidget(Qt::RightDockWidgetArea, templateDock);

    // weightChild->show();
}

MdiMainWindow::~MdiMainWindow()
{
    delete ui;
}

void MdiMainWindow::on_actionSave_triggered()
{
   weightChild->save();
}

void MdiMainWindow::on_actionShowTemplateFile_triggered(bool checked)
{
  if (checked)
    templateDock->show();
  else
    templateDock->hide();
}
