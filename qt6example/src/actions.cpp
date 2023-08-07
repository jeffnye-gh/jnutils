#include "xmw.h"

void Xmw::createActions()
{
  createFileActions();
  createEditActions();
  createViewActions();
  createHelpActions();
}
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void Xmw::createFileActions()
{
  fileNewAct = new QAction("&New",this);
  fileNewAct->setShortcuts(QKeySequence::New);
  fileNewAct->setStatusTip("Create a new JSON Session");
  connect(fileNewAct, SIGNAL(triggered()), this, SLOT(fileNew()));

  fileOpenAct = new QAction("&Open...", this);
  fileOpenAct->setShortcuts(QKeySequence::Open);
  fileOpenAct->setStatusTip("Open an existing JSON Session");
  connect(fileOpenAct, SIGNAL(triggered()), this, SLOT(fileOpen()));

  fileSaveAct = new QAction("&Save", this);
  fileSaveAct->setShortcuts(QKeySequence::Save);
  fileSaveAct->setStatusTip("Save the session");
  connect(fileSaveAct, SIGNAL(triggered()), this, SLOT(fileSave()));

  fileSaveAsAct = new QAction("Save &As...", this);
  fileSaveAsAct->setShortcuts(QKeySequence::SaveAs);
  fileSaveAsAct->setStatusTip("Save the session under a new name");
  connect(fileSaveAsAct, SIGNAL(triggered()), this, SLOT(fileSaveAs()));

  fileExitAct = new QAction("E&xit", this);
  fileExitAct->setShortcuts(QKeySequence::Quit);
  fileExitAct->setStatusTip("Exit the application");
  connect(fileExitAct, SIGNAL(triggered()), this, SLOT(close()));

}
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void Xmw::createEditActions()
{

  editAddTestCaseAct = new QAction("Add testcase...",this);
  editDelTestCaseAct = new QAction("Delete testcase...",this);
  editPreferencesAct = new QAction("Preferences...", this);

  connect(editAddTestCaseAct, SIGNAL(triggered()), 
          this, SLOT(editAddTestCase()));

  connect(editDelTestCaseAct, SIGNAL(triggered()), 
          this, SLOT(editDelTestCase()));

  connect(editPreferencesAct, SIGNAL(triggered()), 
          this, SLOT(editPreferences()));
}
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void Xmw::createViewActions()
{
  viewShowStatusAct = new QAction("Qs");
  viewShowStatusAct->setToolTip("show job status");
  connect(viewShowStatusAct,SIGNAL(triggered()),
          this,SLOT(viewShowStatus()));
}
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void Xmw::createHelpActions()
{
  helpAboutAct = new QAction("&About", this);
  helpAboutAct->setStatusTip("Show the application's About box");
  connect(helpAboutAct, SIGNAL(triggered()), this, SLOT(helpAbout()));

  helpIssuesAct = new QAction("&Known issues", this);
  helpIssuesAct->setStatusTip("Print known issues");
  connect(helpIssuesAct, SIGNAL(triggered()), this, SLOT(helpIssues()));

}

