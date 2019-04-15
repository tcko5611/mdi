#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QTextStream>
#include <QApplication>
#include <QDir>
#include <QCloseEvent>

#include "MdiChild.h"

MdiChild::MdiChild(const QString &fileName, QWidget *parent)
  :QTextEdit(parent)
{
  setAttribute(Qt::WA_DeleteOnClose);
  loadFile(fileName);
}

bool MdiChild::loadFile(const QString &fileName)
{
  QFile file(fileName);
  QFileInfo fileInfo(file);
  if (!fileInfo.exists()) {
    setCurrentFile(fileName);
    
    connect(document(), &QTextDocument::contentsChanged,
	    this, &MdiChild::documentWasModified);
    
    return true;
  }
  if (!file.open(QFile::ReadOnly | QFile::Text)) {
    QMessageBox::warning(this, tr("MDI"),
			 tr("Cannot read file %1:\n%2.")
			 .arg(fileName)
			 .arg(file.errorString()));
    return false;
  }

  QTextStream in(&file);
  QApplication::setOverrideCursor(Qt::WaitCursor);
  setPlainText(in.readAll());
  QApplication::restoreOverrideCursor();
  
  setCurrentFile(fileName);
  
  connect(document(), &QTextDocument::contentsChanged,
	  this, &MdiChild::documentWasModified);
  
  return true;
}

bool MdiChild::save()
{
  QFile file(curFile);
  if (!file.open(QFile::WriteOnly | QFile::Text)) {
    QMessageBox::warning(this, tr("MDI"),
			 tr("Cannot write file %1:\n%2.")
			 .arg(QDir::toNativeSeparators(curFile), file.errorString()));
    return false;
  }

  QTextStream out(&file);
  QApplication::setOverrideCursor(Qt::WaitCursor);
  out << toPlainText();
  QApplication::restoreOverrideCursor();
  
  return true;
}

QString MdiChild::userFriendlyCurrentFile()
{
  return strippedName(curFile);
}

void MdiChild::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void MdiChild::documentWasModified()
{
  setWindowModified(document()->isModified());
}

bool MdiChild::maybeSave()
{
  if (!document()->isModified())
    return true;
  const QMessageBox::StandardButton ret
    = QMessageBox::warning(this, tr("MDI"),
			   tr("'%1' has been modified.\n"
			      "Do you want to save your changes?")
			   .arg(userFriendlyCurrentFile()),
			   QMessageBox::Save | QMessageBox::Discard
			   | QMessageBox::Cancel);
  switch (ret) {
  case QMessageBox::Save:
    return save();
  case QMessageBox::Cancel:
    return false;
  default:
    break;
  }
  return true;
}

void MdiChild::setCurrentFile(const QString &fileName)
{
  curFile = QFileInfo(fileName).canonicalFilePath();
  document()->setModified(false);
  setWindowModified(false);
  setWindowTitle(userFriendlyCurrentFile() + "[*]");
}

QString MdiChild::strippedName(const QString &fullFileName)
{
  return QFileInfo(fullFileName).fileName();
}

