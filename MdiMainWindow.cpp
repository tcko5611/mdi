#include <QFileInfo>
#include <QDockWidget>
#include <QProcess>
#include <QDebug>
#include <QFileSystemWatcher>

#include "MdiMainWindow.h"
#include "MdiChild.h"
#include "ui_MdiMainWindow.h"

MdiMainWindow::MdiMainWindow(const QString &weightFileName,
			     const QString &templateFileName,
			     QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MdiMainWindow)
{
  setAttribute(Qt::WA_DeleteOnClose);
  ui->setupUi(this);
  QFileInfo templateFileInfo(templateFileName);
  weightChild = new MdiChild(weightFileName);
  setCentralWidget(weightChild);

  if (templateFileInfo.exists()) {
    ui->actionShowTemplateFile->setEnabled(true);
    templateDock = new QDockWidget(tr("Template"), this);
    templateDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    templateChild = new MdiChild(templateFileName, templateDock);
    templateChild->setReadOnly(true);
    templateDock->setWidget(templateChild);
    addDockWidget(Qt::RightDockWidgetArea, templateDock);
    ui->actionShowTemplateFile->setChecked(true);
    connect(templateDock, SIGNAL(visibilityChanged(bool)),
	    ui->actionShowTemplateFile, SLOT(setChecked(bool)));
  }
  else {
    ui->actionShowTemplateFile->setEnabled(false);
  }
  /*
  fileWatcher = new QFileSystemWatcher(this);
  connect(fileWatcher, SIGNAL(fileChanged(const QString&)),
	  weightChild, SLOT(loadFile()));
  */
}

MdiMainWindow::~MdiMainWindow()
{
  qDebug() << "destructor for MdiMainWindow";
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

void MdiMainWindow::editorStarted()
{
  // fileWatcher->addPath(weightChild->currentFile());
  ui->actionVim->setEnabled(false);
  ui->actionEmacs->setEnabled(false);
  
  weightChild->setReadOnly(true);
  weightChild->hide();
}

void  MdiMainWindow::editorFinished()
{
  // fileWatcher->removePath(weightChild->currentFile());
  ui->actionVim->setEnabled(true);
  ui->actionEmacs->setEnabled(true);
  weightChild->setReadOnly(false);
  weightChild->show();
}

void MdiMainWindow::on_actionVim_triggered()
{
  QString command = "xterm -e vim " + weightChild->currentFile();
  QProcess *p = new QProcess(this);
  connect(p, SIGNAL(finished(int, QProcess::ExitStatus)), p, SLOT(deleteLater()));
  connect(p, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(editorFinished()));
  p->start(command);
  editorStarted();
}

void MdiMainWindow::on_actionEmacs_triggered()
{
  QString command = "emacs --no-splash " + weightChild->currentFile();
  QProcess *p = new QProcess(this);
  connect(p, SIGNAL(finished(int, QProcess::ExitStatus)), p, SLOT(deleteLater()));
  connect(p, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(editorFinished()));
  p->start(command);
  editorStarted();

}
