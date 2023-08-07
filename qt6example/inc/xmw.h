#pragma once

#include "msg/msg.h"
#include "docks.h"
#include "preferences.h"
#include "controls.h"

#include "json/json.h"

#include <QAction>
#include <QApplication>
#include <QFileDialog>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QStatusBar>
#include <QString>
#include <QToolBar>
#include <QVector>

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
class Xmw : public QMainWindow
{
  Q_OBJECT

public:
  explicit Xmw(QWidget *parent = Q_NULLPTR);

protected:
  void closeEvent(QCloseEvent *event);

private slots:
  void fileNew();
  void fileOpen();
  bool fileSave();
  bool fileSaveAs();
  void editAddTestCase();
  void editDelTestCase();
  void editPreferences() { prefs.editSettings(); }

  void viewShowStatus();

  void helpAbout();
  void helpIssues();

  void documentWasModified();

private:
  void createActions();
  void createFileActions();
  void createEditActions();
  void createViewActions();
  void createHelpActions();

  void createMenus();

  void createToolBars();
  void createStatusBar();
  void createDockWidgets();

  void createCentralWidget();

  void readSettings();
  void writeSettings();

  void populateStatusDock();

  //Slot helpers - this is no longer used but kept for reference
  bool maybeSave() {
  //  if (textEdit->document()->isModified()) {
  //    QMessageBox::StandardButton ret;
  //    ret = QMessageBox::warning(this, tr("Application"),
  //          "The document has been modified.\n"
  //          "Do you want to save your changes?",
  //          QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
  //
  //         if (ret == QMessageBox::Save)   return fileSave();
  //    else if (ret == QMessageBox::Cancel) return false;
  //  }
    return true;
  }

  bool loadFile(const QString &fileName);
  bool loadJsonFile(QString);
  bool saveFile(const QString &fileName);

  void setCurrentFile(const QString &fileName);

  Preferences prefs;
  Msg msg;

  StatusMonitor  *statusDock;
  Controls *controls;

  QString curFile;

  QMenu *fileMenu;
  QMenu *editMenu;
  QMenu *helpMenu;

  QToolBar *viewToolBar;

  QAction *fileNewAct;
  QAction *fileOpenAct;
  QAction *fileSaveAct;
  QAction *fileSaveAsAct;
  QAction *fileExitAct;

  QAction *editAddTestCaseAct;
  QAction *editDelTestCaseAct;
  QAction *editPreferencesAct;

  QAction *viewShowStatusAct;

  QAction *helpAboutAct;
  QAction *helpIssuesAct;

  QWidget *parent;

  Json::Value servers;
  Json::Value lsfqueues;
  Json::Value testcontrols;

  static const QVector<QString> issuesVec;
};
