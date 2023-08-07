#pragma once
#include "json/json.h"

#include <QTabWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QDialog>
#include <QCheckBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QWidget>
#include <QVector>

#include <vector>
#include <iostream>
using namespace std;

class Xmw;
// =========================================================================
// =========================================================================
struct TestCase
{
  TestCase()
    : name(""),
      simulatorLog(""),
      compileLog(""),
      lsfQueue("")
  {}

  TestCase(QString _n,QString _sl, QString _cl, QString _lsf,
           QVector<QString> _ccmds,QVector<QString> _scmds)
    : name(_n),
      simulatorLog(_sl),
      compileLog(_cl),
      lsfQueue(_lsf),
      compileCmds(_ccmds),
      simulatorCmds(_scmds)
  {}

  QString name;
  QString simulatorLog;
  QString compileLog;
  QString lsfQueue;

  QList<QString> compileCmds;
  QList<QString> simulatorCmds;
};
// =========================================================================
// =========================================================================
class TestCheckBox : public QCheckBox
{
  Q_OBJECT
public:
  TestCheckBox(QWidget *parent=0) 
    : QCheckBox(parent)
  {
  }

public slots:

  void setSelected() {
    setCheckState(Qt::Checked);
  }

  void setUnselected() {
    setCheckState(Qt::Unchecked);
  }
};

// =========================================================================
// =========================================================================
class TestPushButton : public QPushButton
{
  Q_OBJECT
public:
  TestPushButton(TestCase &_tc,QString _t,QWidget *parent=0) 
    : QPushButton(_t,parent),
      name(_t), tc(_tc)
  {
  }

public slots:
  void openEditPanel();

public:
  QString name;
  TestCase tc;
};

// =========================================================================
// =========================================================================
class TestCaseEditDialog : public QDialog
{
  Q_OBJECT

public:
  TestCaseEditDialog(TestPushButton *_pb,QString _n,QWidget *parent=0);

public slots:
  void testCaseAccept();
  void testCaseReject() { close(); }

//signals:
//  void newTestCaseAccepted;
//  void newTestCaseRejected;

public:
  bool fromPushButton;
  TestPushButton *pb;
  QString name;
  QDialogButtonBox *bbox;
  
  QLineEdit *nameLE;
  QTextEdit *compTE;
  QTextEdit *simTE;
};

// =========================================================================
// =========================================================================
class Controls : public QWidget
{
  Q_OBJECT

public:
  Controls(QWidget *parent=0);

  void buildControlDialog(Json::Value&);
  void addUbench(int,QWidget *);
  void buildPanelWidget(int,QWidget *,Json::Value&,QTabWidget*);

public slots:
  void runSelected();

public:
  QTabWidget *tabs;
  Json::Value testcontrols;
};
