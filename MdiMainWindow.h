#ifndef MDIMAINWINDOW_H /* -*-c++-*- */
#define MDIMAINWINDOW_H

#include <QMainWindow>

class MdiChild;
class QFileSystemWatcher;
namespace Ui {
class MdiMainWindow;
}

class MdiMainWindow : public QMainWindow
{
  Q_OBJECT
  
public:
  explicit MdiMainWindow(const QString &weightFileName,
			 const QString &templateFileName,
			 QWidget *parent = 0);
  ~MdiMainWindow();
  MdiChild* createMdiChild(const QString &fileName);
						   
private slots:
  
  void on_actionSave_triggered();
  
  void on_actionShowTemplateFile_triggered(bool checked);
  
  void on_actionVim_triggered();
  
  void on_actionEmacs_triggered();

  void editorStarted();

  void editorFinished();
private:
  Ui::MdiMainWindow *ui;
  MdiChild *weightChild;
  MdiChild *templateChild;
  QDockWidget *templateDock;
  QFileSystemWatcher *fileWatcher;
};

#endif // MDIMAINWINDOW_H
