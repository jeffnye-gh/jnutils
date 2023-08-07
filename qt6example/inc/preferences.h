#pragma once
#include "app.h"
#include <QCheckBox>
#include <QLabel>
#include <QList>
#include <QString>
#include <QDialog>
#include <QGridLayout>
#include <QTabWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QSpinBox>
#include <QDialogButtonBox>

#include <map>

class Preferences;
class Xmw;
// =======================================================================
// =======================================================================
class SettingsLE : public QLineEdit
{
  Q_OBJECT

public:
  SettingsLE(QString="",QWidget *parent=0);

public slots:
  void onCursorPositionChanged(int,int) { setStyleSheet(""); }
  void onTextChange(QString) { setStyleSheet(""); }

};

// =======================================================================
// =======================================================================
class SettingsL : public QLabel
{
  Q_OBJECT
public:
  SettingsL(QString,QWidget *parent=0);
};

// =======================================================================
// =======================================================================
class SettingsDialog : public QDialog
{
  Q_OBJECT

  enum class ControlSet{ DNN, SAIN, CUST };

public:
  SettingsDialog(Preferences *p,QWidget *parent=0);

  void constructWidgets();
  void applyLayout();
  void populateFields();
  void dimControls();
  void connectSignals();
  app::ControlSet cbToControlSet();
  bool checkTop();
  bool checkPaths();
  bool checkVariables();

  QString useEnv(QString,QString,QString);

public slots:
  void radioToggled(bool);
  void capturePrefs();
  void closeDialog();

  void loadFromEnv();
  void checkSettings();
  void preferencesAccept();
  void preferencesReject();
 
public:
  QTabWidget *tabs;
  Preferences *prefs;

  QAction *loadFromEnvAct,*checkPathsAct;

QLabel
*architectureL,
*baremetaltoolsL,
*benchmarksL,
*buildrootL,
*camL,
*condortopL,
*cpmdromajoL,
*crosscompileL,
*dromajoL,
*emptyL,
*kernelL,
*linuxtoolsL,
*mapL,
*olympiaL,
*opensbiL,
*patchesL,
*riscvprefixL,
*spartaL,
*spikeL,
*cpmtoolsL,
*uarchversionL,
*veerL,
*whisperL;

SettingsLE
*architectureLE,
*baremetaltoolsLE,
*benchmarksLE,
*buildrootLE,
*camLE,
*condortopLE,
*cpmdromajoLE,
*crosscompileLE,
*dromajoLE,
*kernelLE,
*linuxtoolsLE,
*mapLE,
*olympiaLE,
*opensbiLE,
*patchesLE,
*riscvprefixLE,
*spartaLE,
*spikeLE,
*cpmtoolsLE,
*uarchversionLE,
*veerLE,
*whisperLE;

  QGridLayout *grid;
  QCheckBox   *verboseCB;

  QPushButton *loadFromEnvPB,*checkPathsPB;

  QDialogButtonBox *buttonBox;
};
// =======================================================================
// =======================================================================
class Preferences
{
public:
  Preferences();

  void removeOpenFile(QString);
  void uniquifyFileLists();
  void editSettings();


  QColor   getColor(app::ItemTypes);
  QString  getStyle(app::ItemTypes);
  uint32_t getSize(app::ItemTypes);
  bool     getVisible(app::ItemTypes);

  // ---------------------------------------------------------------------
  // ---------------------------------------------------------------------
public:
  Xmw *gui;
  SettingsDialog *settingsDialog;

  QString architecture;
  QString uarchversion;
  QString baremetaltools;
  QString benchmarks;
  QString buildroot;
  QString cam;
  QString condortop;
  QString cpmdromajo;
  QString crosscompile;
  QString dromajo;
  QString kernel;
  QString linuxtools;
  QString map;
  QString sparta;
  QString olympia;
  QString opensbi;
  QString patches;
  QString riscvprefix;
  QString spike;
  QString cpmtools;
  QString veer;
  QString whisper;

  static const std::map<QString,QString> defaults;  

  QList<SettingsLE*> pathsToCheck;
  QList<SettingsLE*> variablesToCheck;

 private:
  bool prefsAcceptState{false};
};
