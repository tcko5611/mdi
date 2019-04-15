#ifndef MDICHILD_H /* -*-c++-*- */
#define MDICHILD_H
#include <QTextEdit>

class MdiChild : public QTextEdit
{
    Q_OBJECT

public:
  MdiChild(const QString& fileName, QWidget *parent = 0);

  bool loadFile(const QString &fileName);
  bool save();
  QString userFriendlyCurrentFile();
  QString currentFile() { return curFile; }
  
protected:
  void closeEvent(QCloseEvent *event) override;
					      
private slots:
  void documentWasModified();
  
private:
  bool maybeSave();
  void setCurrentFile(const QString &fileName);
  QString strippedName(const QString &fullFileName);
  
  QString curFile;
};

#endif // MDICHILD_H
