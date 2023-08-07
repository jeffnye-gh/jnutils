#include "controls.h"
#include "xmw.h"
#include <QGridLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>

#include <QTabBar>
#include <QTabWidget>
#include <iostream>
using namespace std;

#define qfs(s) QString::fromStdString(s)
// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
Controls::Controls(QWidget *parent)
  : QWidget(parent)
{
}
// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
void Controls::buildControlDialog(Json::Value &_tc)
{
  testcontrols = _tc;

  tabs = new QTabWidget;

  for (Json::Value::ArrayIndex i = 0; i != testcontrols.size(); i++) {
    QString tabName = qfs(testcontrols[i]["tabname"].asString());
    QWidget *panelWidget = new QWidget;
    Json::Value tabContents = testcontrols[i];
    int tabId = tabs->addTab(panelWidget,tabName);
    buildPanelWidget(tabId,panelWidget,tabContents,tabs);
  }

  //For limit testing
  //  QString tabNName("TestTab%1");
  //  for(size_t i=0;i<16;++i) {
  //    QWidget *panelWidget = new QWidget;
  //    int tabId = tabs->addTab(panelWidget,tabNName.arg(i));
  //  }

  QVBoxLayout *vert     = new QVBoxLayout;
  vert->addWidget(tabs);
  this->setLayout(vert);
}
// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
void Controls::buildPanelWidget(int tabId, QWidget *panel,
                                Json::Value &tabContents, QTabWidget *tabs)
{
  (void) tabId;
  (void) tabs;

  Json::Value::iterator itr1;
  QMap<QString,TestCase> tcMap;

  for(itr1  = tabContents["testcases"].begin();
      itr1 != tabContents["testcases"].end(); ++itr1)
  {
    TestCase tc;

    tc.name = qfs(itr1.key().asString());

    Json::Value compArry = (*itr1)["compile"];

    for(Json::Value::ArrayIndex i=0;i!=compArry.size();++i) {
      tc.compileCmds << qfs(compArry[i].asString());
    }

    Json::Value simArry = (*itr1)["simulate"];

    for(Json::Value::ArrayIndex i=0;i!=simArry.size();++i) {
      tc.simulatorCmds << qfs(simArry[i].asString());
    }

    tcMap.insert(tc.name,tc);
  }

  QGridLayout *grid = new QGridLayout;

  QPushButton *run  = new QPushButton("Run");
  QPushButton *sa   = new QPushButton("Select All");
  QPushButton *usa  = new QPushButton("Deselect All");

  connect(run,SIGNAL(pressed()),this,SLOT(runSelected()));

  size_t row=0;

  grid->addWidget(run, row,1,1,1);
  grid->addWidget(sa,  row,3,1,1);
  grid->addWidget(usa, row,5,1,1);

  ++row;

  size_t col = 0;

  TestCase empty;
  QString emptyName("empty%1");

  //For limit testing
  //size_t MAXCOL = 25;
  //size_t TRIG   = 325;

  size_t MAXCOL = 6;
  size_t TRIG = 9;
  for(size_t k=tcMap.size();k<TRIG;++k) {
    tcMap.insert(emptyName.arg(k),empty);
  }

  for(auto tcName : tcMap.keys()) {

    if(col>=MAXCOL) { ++row; col = 0; }

    QString thisName = "";
    if(!tcName.contains("empty")) thisName = tcName;
    //thisName = tcName; limit testing
    TestCheckBox   *cb  = new TestCheckBox();
    TestPushButton *pb  = new TestPushButton(tcMap[tcName],thisName);

    cb->setObjectName("cb"+tcName);
    pb->setObjectName("pb"+tcName);

    connect(pb, SIGNAL(pressed()),pb,SLOT(openEditPanel()));
    connect(sa, SIGNAL(pressed()),cb,SLOT(setSelected()));
    connect(usa,SIGNAL(pressed()),cb,SLOT(setUnselected()));

    grid->addWidget(cb,row,col,  1,1);
    grid->addWidget(pb,row,col+1,1,1);
    col += 2;

  }

  panel->setLayout(grid);
}
// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
void Controls::runSelected()
{
}
// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
void TestPushButton::openEditPanel()
{
  TestCaseEditDialog *edit = new TestCaseEditDialog(this,name);
  edit->exec();
}
// --------------------------------------------------------------------------
TestCaseEditDialog::TestCaseEditDialog(TestPushButton *_pb,QString _n,
                                       QWidget *parent)
  : QDialog(parent),
    pb(_pb),
    name(_n)
{
  QGridLayout *grid = new QGridLayout;

  QLabel    *nameL  = new QLabel("Test case");
  nameL->setStyleSheet("QLabel { color : #7f7fFF;}");

  if(name.length() > 0) {
    nameLE = new QLineEdit(name);
  } else {
    nameLE = new QLineEdit("");
    nameLE->setStyleSheet("QLineEdit { color : #000000; "
                          "background-color : #FFFFFF;}");
  }

  QLabel *compL = new QLabel("Compile Commands");
  compL->setStyleSheet("QLabel { color : #7fFF7f;}");

  QLabel *simL  = new QLabel("Simulator Commands");
  simL->setStyleSheet("QLabel { color : #7fFF7f;}");

  QString textEditStyle;
  textEditStyle = "QTextEdit { color : #000000; background-color : #FFFFFF; }";

  compTE = new QTextEdit(this);
  compTE->setStyleSheet(textEditStyle);

  simTE  = new QTextEdit(this);
  simTE->setStyleSheet(textEditStyle);

  if(fromPushButton) {
    foreach(QString s,pb->tc.compileCmds)   compTE->append(s);
    foreach(QString s,pb->tc.simulatorCmds) simTE->append(s);
  }

  bbox = new QDialogButtonBox(this);
  bbox->setOrientation(Qt::Horizontal);
  bbox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

  connect(bbox,SIGNAL(accepted()),this,SLOT(testCaseAccept()));
  connect(bbox,SIGNAL(rejected()),this,SLOT(testCaseReject()));

  int r=0;

  grid->addWidget(nameL,   r,0,1,1);
  grid->addWidget(nameLE,  r,1,1,4); ++r;

  grid->addWidget(compL,   r,0,1,1); ++r;
  grid->addWidget(compTE,  r,0,1,4); ++r; //r+=4+1;

  grid->addWidget(simL,    r,0,1,1); ++r;
  grid->addWidget(simTE,   r,0,1,4); ++r; //r+=4+1;

  grid->addWidget(bbox,    r,2,1,1);

  this->setLayout(grid);
}
// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
void TestCaseEditDialog::testCaseAccept()
{
  close();
}
