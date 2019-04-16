#ifndef MDICHILD_H /* -*-c++-*- */
#define MDICHILD_H
#include <QTextEdit>

class MdiChild : public QTextEdit
{
    Q_OBJECT

public:
  MdiChild(const QString& fileName, QWidget *parent = 0);


  bool save();
  QString userFriendlyCurrentFile();
  QString currentFile() { return curFile; }

public slots:
  bool loadFile();  
protected:
  void closeEvent(QCloseEvent *event) override;
					      
private:
  bool maybeSave();
  void setCurrentFile(const QString &fileName);
  
  QString curFile;
};

#endif // MDICHILD_H
