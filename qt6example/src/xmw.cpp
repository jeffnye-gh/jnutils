#include <QtGui>

#include "xmw.h"
#include "docks.h"
#include <QApplication>
#include <QFileDialog>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QAction>
#include <QMenu>
#include <QPlainTextEdit>
#include <QMessageBox>
#include <QHBoxLayout>

// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
Xmw::Xmw(QWidget *parent)
  : QMainWindow(parent)
{
  createActions();
  createMenus();
  createToolBars();
  createStatusBar();

  statusDock  = new StatusMonitor("Status Monitor",this);

  QHBoxLayout *horz = new QHBoxLayout;

  controls = new Controls();
  horz->addWidget(controls);
  horz->addWidget(statusDock);

  QWidget *central = new QWidget;
  central->setLayout(horz);
  setCentralWidget(central);
  
  setCurrentFile("");
  setUnifiedTitleAndToolBarOnMac(true);

  loadJsonFile("tests/data.json");
//  loadJsonFile("empty.json");
//  editPreferencesAct->trigger();
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void Xmw::closeEvent(QCloseEvent *event)
{
  if (maybeSave()) {
    writeSettings();
    event->accept();
  } else {
    event->ignore();
  }
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void Xmw::setCurrentFile(const QString &fileName)
{
  curFile = fileName;
//  textEdit->document()->setModified(false);
  setWindowModified(false);

  QString shownName = curFile;
  if (curFile.isEmpty())
      shownName = "untitled.txt";
  setWindowFilePath(shownName);
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
//QString Xmw::strippedName(const QString &fullFileName)
//{
//  return QFileInfo(fullFileName).fileName();
//}
