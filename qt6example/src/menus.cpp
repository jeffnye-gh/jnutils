#include "xmw.h"

void Xmw::createMenus()
{
  fileMenu = menuBar()->addMenu(tr("&File"));
  fileMenu->addAction(fileNewAct);
  fileMenu->addAction(fileOpenAct);
  fileMenu->addAction(fileSaveAct);
  fileMenu->addAction(fileSaveAsAct);
  fileMenu->addSeparator();
  fileMenu->addAction(fileExitAct);

  editMenu = menuBar()->addMenu(tr("&Edit"));
  editMenu->addAction(editAddTestCaseAct);
  editMenu->addAction(editDelTestCaseAct);
  editMenu->addSeparator();
  editMenu->addAction(editPreferencesAct);

  menuBar()->addSeparator();

  helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(helpAboutAct);
  helpMenu->addAction(helpIssuesAct);
}

