#include "app.h"
#include "xmw.h"
#include "preferences.h"

#include <QCheckBox>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QProcessEnvironment>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>

#include <iostream>
#include <map>

using namespace std;
// =======================================================================
// =======================================================================
SettingsL::SettingsL(QString text,QWidget *parent)
  : QLabel(text,parent)
{
  this->setAlignment(Qt::AlignRight);
  this->setStyleSheet("color : grey;");
}
// =======================================================================
// =======================================================================
SettingsLE::SettingsLE(QString text,QWidget *parent)
  : QLineEdit(parent)
{
//  (void)text;
  setText("");
//  setPlaceholderText("..................................................");
  setObjectName(text);
//  connect(this, SIGNAL(textChanged(QString)),
//          this, SLOT(onTextChange(QString)));
//  connect(this, SIGNAL(cursorPositionChanged(int,int)),
//          this, SLOT(onCursorPositionChanged(int,int)));
}
// =======================================================================
// =======================================================================
SettingsDialog::SettingsDialog(Preferences *_p,QWidget *parent)
  : QDialog(parent),
    prefs(_p)
{
  constructWidgets();
  connectSignals();
  populateFields();
  applyLayout();
  this->resize(1024,512);
}
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
const map<QString,QString> Preferences::defaults =
{
  { "architecture","Cuzco" },
  { "baremetaltools","$TOP/riscv64-unknown-elf" },
  { "benchmarks","$TOP/benchmarks" },
  { "buildRoot","$TOP/buildroot-2020.05.1" },
  { "cam","" },
  { "condorTop","/home/jeff/Development/condor.3" },
  { "cpmDromajo","$TOP/cpm.dromajo" },
  { "crosscompile","riscv64-unknown-linux-gnu-" },
  { "dromajo","$TOP/dromajo" },
  { "kernel","$TOP/linux-5.8-rc4" },
  { "linuxtools","riscv64-unknown-linux-gnu" },
  { "map","$TOP/map" },
  { "sparta","$TOP/map/sparta" },
  { "olympia","$TOP/riscv-perf-model" },
  { "opensbi","$TOP/opensbi" },
  { "patches","$TOP/how-to/patches" },
  { "riscvprefix","riscv64-unknown-elf-" },
  { "spike","$TOP/spike" },
  { "tools","$TOP/tool" },
  { "uarchversion","v1.0" },
  { "veer","$TOP/veer" },
  { "whisper","$TOP/whisper" }
};
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void SettingsDialog::applyLayout()
{
  grid = new QGridLayout;
  uint32_t r = 0;

  grid->addWidget(architectureL,   r,0,1,1);
  grid->addWidget(architectureLE,  r,1,1,1);
  grid->addWidget(uarchversionL,   r,2,1,1);
  grid->addWidget(uarchversionLE,  r,3,1,1); ++r;

  grid->addWidget(condortopL,      r,0,1,1);
  grid->addWidget(condortopLE,     r,1,1,1);
  grid->addWidget(cpmtoolsL,       r,2,1,1);
  grid->addWidget(cpmtoolsLE,      r,3,1,1); ++r;

  grid->addWidget(baremetaltoolsL, r,0,1,1);
  grid->addWidget(baremetaltoolsLE,r,1,1,1);
  grid->addWidget(linuxtoolsL,     r,2,1,1);
  grid->addWidget(linuxtoolsLE,    r,3,1,1); ++r;

  grid->addWidget(buildrootL,      r,0,1,1);
  grid->addWidget(buildrootLE,     r,1,1,1);
  grid->addWidget(kernelL,         r,2,1,1);
  grid->addWidget(kernelLE,        r,3,1,1); ++r;

  grid->addWidget(opensbiL,        r,0,1,1);
  grid->addWidget(opensbiLE,       r,1,1,1);
  grid->addWidget(benchmarksL,     r,2,1,1);
  grid->addWidget(benchmarksLE,    r,3,1,1); ++r;

  grid->addWidget(mapL,            r,0,1,1);
  grid->addWidget(mapLE,           r,1,1,1);
  grid->addWidget(spartaL,         r,2,1,1);
  grid->addWidget(spartaLE,        r,3,1,1); ++r;

  grid->addWidget(cpmdromajoL,     r,0,1,1);
  grid->addWidget(cpmdromajoLE,    r,1,1,1);
  grid->addWidget(dromajoL,        r,2,1,1);
  grid->addWidget(dromajoLE,       r,3,1,1); ++r;

  grid->addWidget(camL,            r,0,1,1);
  grid->addWidget(camLE,           r,1,1,1);
  grid->addWidget(olympiaL,        r,2,1,1);
  grid->addWidget(olympiaLE,       r,3,1,1); ++r;

  grid->addWidget(patchesL,        r,0,1,1);
  grid->addWidget(patchesLE,       r,1,1,1);
  grid->addWidget(spikeL,          r,2,1,1);
  grid->addWidget(spikeLE,         r,3,1,1); ++r;

  grid->addWidget(veerL,           r,0,1,1);
  grid->addWidget(veerLE,          r,1,1,1);
  grid->addWidget(whisperL,        r,2,1,1);
  grid->addWidget(whisperLE,       r,3,1,1); ++r;

  grid->addWidget(crosscompileL,   r,0,1,1);
  grid->addWidget(crosscompileLE,  r,1,1,1);
  grid->addWidget(riscvprefixL,    r,2,1,1);
  grid->addWidget(riscvprefixLE,   r,3,1,1); ++r;

  QGridLayout *grid2 = new QGridLayout;

  QWidget *allbuttons = new QWidget(this);

  grid2->addWidget(loadFromEnvPB,   0,0,1,1);
  grid2->addWidget(checkPathsPB,    0,1,1,1);
  grid2->addWidget(buttonBox,       0,2,1,2);

  allbuttons->setLayout(grid2);

  grid->addWidget(allbuttons, r,2,1,2);

//  QWidget *topLevel = new QWidget(this);
//  topLevel->setGeometry(QRect(10, 10, 1024, 1024));
  this->setLayout(grid);
}
// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void SettingsDialog::constructWidgets()
{
  //verboseL  = new QLabel("Verbose level");
  emptyL  = new QLabel("");

  architectureL    = new SettingsL("Architecture");
  uarchversionL    = new SettingsL("uArch Version");
  condortopL       = new SettingsL("$TOP");
  cpmtoolsL        = new SettingsL("CPM Tools");

  baremetaltoolsLE = new SettingsLE("baremetaltoolsLE");
  baremetaltoolsL  = new SettingsL("Bare Metal tools");

  linuxtoolsL      = new SettingsL("Linux tools");

  benchmarksL      = new SettingsL("Benchmarks");
  buildrootL       = new SettingsL("buildRoot");
  camL             = new SettingsL("CAM");
  cpmdromajoL      = new SettingsL("cpm.Dromajo");
  crosscompileL    = new SettingsL("CROSS_COMPILE");
  dromajoL         = new SettingsL("Dromajo");
  kernelL          = new SettingsL("Kernel");
  mapL             = new SettingsL("$TOP/map");
  olympiaL         = new SettingsL("Olympia");
  opensbiL         = new SettingsL("OpenSBI");
  patchesL         = new SettingsL("Patches");
  riscvprefixL     = new SettingsL("RISCV Prefix");
  spartaL          = new SettingsL("Map/Sparta");
  spikeL           = new SettingsL("spikeL");
  veerL            = new SettingsL("veerL");
  whisperL         = new SettingsL("whisperL");

  architectureLE   = new SettingsLE("architectureLE");
  uarchversionLE   = new SettingsLE("uarchversionLE");
  condortopLE      = new SettingsLE("condortopLE");
  linuxtoolsLE     = new SettingsLE("linuxtoolsLE");
  benchmarksLE     = new SettingsLE("benchmarksLE");
  buildrootLE      = new SettingsLE("buildrootLE");
  camLE            = new SettingsLE("camLE");
  cpmdromajoLE     = new SettingsLE("cpmdromajoLE");
  crosscompileLE   = new SettingsLE("crosscompileLE");
  dromajoLE        = new SettingsLE("dromajoLE");
  kernelLE         = new SettingsLE("kernelLE");
  olympiaLE        = new SettingsLE("olympiaLE");
  opensbiLE        = new SettingsLE("opensbiLE");
  mapLE            = new SettingsLE("mapLE");
  patchesLE        = new SettingsLE("patchesLE");
  riscvprefixLE    = new SettingsLE("riscvprefixLE");
  spartaLE         = new SettingsLE("spartaLE");
  spikeLE          = new SettingsLE("spikeLE");
  cpmtoolsLE       = new SettingsLE("cpmtoolsLE");
  veerLE           = new SettingsLE("veerLE");
  whisperLE        = new SettingsLE("whisperLE");

  prefs->pathsToCheck.clear();

  prefs->pathsToCheck << baremetaltoolsLE <<linuxtoolsLE 
               << benchmarksLE << buildrootLE
               << camLE << cpmdromajoLE << dromajoLE
               << kernelLE << olympiaLE << opensbiLE << mapLE
               << patchesLE << spartaLE << spikeLE
               << cpmtoolsLE << veerLE << whisperLE;

  prefs->variablesToCheck << crosscompileLE << riscvprefixLE
                          << architectureLE << uarchversionLE;

  loadFromEnvPB  = new QPushButton("Load from ENV");
  loadFromEnvPB->setToolTip("load settings from linux environment");
  loadFromEnvAct = new QAction("Load from ENV");
  connect(loadFromEnvPB,SIGNAL(pressed()),this,SLOT(loadFromEnv()));

  checkPathsPB  = new QPushButton("Check Settings");
  checkPathsPB->setToolTip("check for settings values and paths");
  checkPathsAct = new QAction("Check Settings");
  connect(checkPathsPB,SIGNAL(pressed()),this,SLOT(checkSettings()));

  buttonBox = new QDialogButtonBox(this);
  buttonBox->setOrientation(Qt::Horizontal);
  buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
  connect(buttonBox,SIGNAL(accepted()),this,SLOT(preferencesAccept()));
  connect(buttonBox,SIGNAL(rejected()),this,SLOT(preferencesReject()));
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void SettingsDialog::preferencesAccept()
{/* cout<<"HERE preferencesAccept"<<endl;*/}
// -----------------------------------------------------------------------
void SettingsDialog::preferencesReject()
{/* cout<<"HERE preferencesReject"<<endl;*/}
// -----------------------------------------------------------------------
#define ENV(s) QProcessEnvironment::systemEnvironment().value(s)
// -----------------------------------------------------------------------
QString SettingsDialog::useEnv(QString in,QString t2r,QString top)
{
  QString out = in;
  in.replace(in.indexOf(t2r),t2r.size(),top);
  return in;
}
// -----------------------------------------------------------------------
void SettingsDialog::loadFromEnv()
{
  condortopLE ->setText(ENV("CONDOR_TOP"));

  QString t2r = condortopLE->displayText();
  QString top = "$TOP";

  cpmtoolsLE  ->setText(useEnv(ENV("CPM_TOOLS"),t2r,top));

  baremetaltoolsLE->setText(useEnv(ENV("RV_BAREMETAL_TOOLS"),t2r,top));
  linuxtoolsLE    ->setText(useEnv(ENV("RV_LINUX_TOOLS"),t2r,top));
  benchmarksLE    ->setText(useEnv(ENV("BENCHMARKS"),t2r,top));
  buildrootLE     ->setText(useEnv(ENV("BUILDROOT"),t2r,top));
  camLE           ->setText(useEnv(ENV("CAM"),t2r,top));
  cpmdromajoLE    ->setText(useEnv(ENV("CPM_DROMAJO"),t2r,top));

  dromajoLE       ->setText(useEnv(ENV("DROMAJO"),t2r,top));
  kernelLE        ->setText(useEnv(ENV("KERNEL"),t2r,top));
  olympiaLE       ->setText(useEnv(ENV("OLYMPIA"),t2r,top));
  opensbiLE       ->setText(useEnv(ENV("OPENSBI"),t2r,top));
  mapLE           ->setText(useEnv(ENV("MAP"),t2r,top));
  patchesLE       ->setText(useEnv(ENV("PATCHES"),t2r,top));
  spartaLE        ->setText(useEnv(ENV("SPARTA"),t2r,top));
  spikeLE         ->setText(useEnv(ENV("SPIKE"),t2r,top));
  veerLE          ->setText(useEnv(ENV("VEER"),t2r,top));
  whisperLE       ->setText(useEnv(ENV("WHISPER"),t2r,top));

  crosscompileLE  ->setText(useEnv(ENV("CROSS_COMPILE"),t2r,top));
  riscvprefixLE   ->setText(useEnv(ENV("RISCV_PREFIX"),t2r,top));

}
// -----------------------------------------------------------------------
void SettingsDialog::checkSettings()
{
  if(!checkTop()) return;

  bool pathsOk = checkPaths();
  bool varsOk  = checkVariables();

  if(pathsOk && varsOk) {
    QMessageBox::information(this,"CamDash",
      QString("Settings checks complete"));
  } else if(!pathsOk) {
    QMessageBox::critical(this,"CamDash",
      QString("\nErrors found in paths settings.\n"));
  } else if(!varsOk) {
    QMessageBox::critical(this,"CamDash",
      QString("\nErrors found in variable settings.\n"));
  }
}
// -----------------------------------------------------------------------
// FIXME
// -----------------------------------------------------------------------
bool SettingsDialog::checkVariables()
{
  bool allFound = true;

// Text returned for these LE's is empty
//  foreach(SettingsLE *i,prefs->variablesToCheck) {
//    i->setStyleSheet(""); //clear any previous error
//
//    QString text = i->displayText();
//
//    if(text.length() == 0 || text == "<empty variable>") {
//      allFound = false;
//      i->setStyleSheet("QLineEdit { color : red; }");
//      i->setText("<empty variable>");
//      cout<<"-E: bad variable in "<<i->objectName().toStdString()<<endl;
//    }
//  }

  return allFound;
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
bool SettingsDialog::checkTop()
{
  QString top = condortopLE->displayText();
  condortopLE->setStyleSheet(""); //clear any previous error

  bool ok = true;
  if(top.length() == 0) {

    ok = false;
    condortopLE->setStyleSheet("QLineEdit { color : red; }");
    condortopLE->setText("<empty path>");

    QMessageBox::critical(this, "CamDash",
       QString("$TOP does not exist\nPlease correct and re-check"));

  } else if(!QDir(top).exists()) {

    ok = false;
    condortopLE->setStyleSheet("QLineEdit { color : red; }");
    QMessageBox::critical(this, "CamDash",
       QString("$TOP does not exist\nPlease correct and re-check"));

  }

  return ok;
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
bool SettingsDialog::checkPaths()
{
  QString top = condortopLE->displayText();
  QString subStr("$TOP");
  bool allFound = true;

  foreach(SettingsLE *i,prefs->pathsToCheck) {
    i->setStyleSheet(""); //clear any previous error

    QString path = i->displayText();

    if(path.length() == 0 || path == "<empty path>") {
      i->setStyleSheet("QLineEdit { color : red; }");
      i->setText("<empty path>");
      cout<<"-E: bad path in "<<i->objectName().toStdString()<<endl;
    }

    path.replace(path.indexOf(subStr),subStr.size(),top);

    if(!QDir(path).exists()) {
      i->setStyleSheet("QLineEdit { color : red; }");
      allFound = false;
    }
  }

  return allFound;
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void SettingsDialog::connectSignals()
{
  connect(buttonBox,SIGNAL(accepted()),this,SLOT(capturePrefs()));
  connect(buttonBox,SIGNAL(rejected()),this,SLOT(closeDialog()));
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void SettingsDialog::closeDialog()
{
  close();
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void SettingsDialog::populateFields()
{
  architectureLE   ->setText(prefs->architecture);
  uarchversionLE   ->setText(prefs->uarchversion);

  baremetaltoolsLE ->setText(prefs->baremetaltools);
  benchmarksLE     ->setText(prefs->benchmarks);
  buildrootLE      ->setText(prefs->buildroot);
  camLE            ->setText(prefs->cam);
  condortopLE      ->setText(prefs->condortop);
  cpmdromajoLE     ->setText(prefs->cpmdromajo);
  cpmtoolsLE       ->setText(prefs->cpmtools);
  crosscompileLE   ->setText(prefs->crosscompile);
  dromajoLE        ->setText(prefs->dromajo);
  kernelLE         ->setText(prefs->kernel);
  linuxtoolsLE     ->setText(prefs->linuxtools);
  mapLE            ->setText(prefs->map);
  olympiaLE        ->setText(prefs->olympia);
  opensbiLE        ->setText(prefs->opensbi);
  patchesLE        ->setText(prefs->patches);
  riscvprefixLE    ->setText(prefs->riscvprefix);
  spartaLE         ->setText(prefs->sparta);
  spikeLE          ->setText(prefs->spike);
  veerLE           ->setText(prefs->veer);
  whisperLE        ->setText(prefs->whisper);

  dimControls();
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void SettingsDialog::capturePrefs()
{
  prefs->uarchversion = uarchversionLE->displayText();
  prefs->architecture = architectureLE->displayText();
  prefs->condortop    = condortopLE->displayText();

  prefs->baremetaltools = baremetaltoolsLE->displayText();
  prefs->benchmarks   = benchmarksLE->displayText();
  prefs->buildroot    = buildrootLE->displayText();
  prefs->cam          = camLE->displayText();
  prefs->cpmdromajo   = cpmdromajoLE->displayText();
  prefs->crosscompile = crosscompileLE->displayText();
  prefs->dromajo      = dromajoLE->displayText();
  prefs->kernel       = kernelLE->displayText();
  prefs->linuxtools   = linuxtoolsLE->displayText();
  prefs->map          = mapLE->displayText();
  prefs->sparta       = spartaLE->displayText();
  prefs->olympia      = olympiaLE->displayText();
  prefs->opensbi      = opensbiLE->displayText();
  prefs->patches      = patchesLE->displayText();
  prefs->riscvprefix  = riscvprefixLE->displayText();
  prefs->spike        = spikeLE->displayText();
  prefs->cpmtools     = cpmtoolsLE->displayText();
  prefs->veer         = veerLE->displayText();
  prefs->whisper      = whisperLE->displayText();

  close();
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void SettingsDialog::radioToggled(bool)
{
  dimControls();
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
app::ControlSet SettingsDialog::cbToControlSet()
{
  return app::ControlSet::CUST;
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void SettingsDialog::dimControls()
{
}
// ===========================================================================
// ===========================================================================
Preferences::Preferences()
{
  settingsDialog = new SettingsDialog(this);
  settingsDialog->hide();
}
// -------------------------------------------------------------------
// -------------------------------------------------------------------
void Preferences::editSettings()
{
  prefsAcceptState = false;
  settingsDialog = new SettingsDialog(this);
  if(settingsDialog->exec() == QDialog::Accepted) {
    prefsAcceptState = true;
  }
}
// -------------------------------------------------------------------
// -------------------------------------------------------------------
uint32_t Preferences::getSize(app::ItemTypes i)
{
  (void)i;
  return 100;
}
// -------------------------------------------------------------------
// -------------------------------------------------------------------
QColor Preferences::getColor(app::ItemTypes i)
{
  (void)i;
  return Qt::black;
}
// -------------------------------------------------------------------
// -------------------------------------------------------------------
QString Preferences::getStyle(app::ItemTypes i)
{
  (void)i;
  return "";
}
// -------------------------------------------------------------------
// -------------------------------------------------------------------
bool Preferences::getVisible(app::ItemTypes i)
{
  (void)i;
  return true;
}
// -------------------------------------------------------------------
// -------------------------------------------------------------------
void Preferences::uniquifyFileLists()
{
}
// -------------------------------------------------------------------
// -------------------------------------------------------------------
void Preferences::removeOpenFile(QString fn)
{
  (void)fn;
}
