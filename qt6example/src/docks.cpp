#include "xmw.h"
#include "docks.h"
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <iostream>
using namespace std;
// =======================================================================
// =======================================================================
LoadMonitor::LoadMonitor(QString _t,QWidget *parent)
  : QWidget(parent),
    title(_t),
    grid(new QGridLayout())
{
}
// ----------------------------------------------------------------------
LoadMonitor::LoadMonitor(QList<Server> &_s,QString _t,QWidget *parent)
  : QWidget(parent),
    servers(_s),
    title(_t),
    grid(new QGridLayout())
{
  populateGrid();
}
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
void LoadMonitor::populateGrid()
{
  int r=0;

  QLabel *top = new QLabel("SERVERS");
  top->setStyleSheet("QLabel { color : #7f7fFF;}");
  grid->addWidget(top,   r,0,1,4);

  ++r;

  foreach(Server s,servers) {

    QLabel *name      = new QLabel(s.name+" ("+s.ip+")");
    name->setStyleSheet("QLabel { font-size : 12px; color : #7f7fFF;}");

    QLabel *loadL     = new QLabel("Load");
    loadL->setStyleSheet("QLabel { font-size : 12px;}");

    QLineEdit *loadLE = new QLineEdit(s.load);
    loadLE->setReadOnly(true);
    loadLE->setStyleSheet("QLineEdit { font-size : 12px;}");

    QLabel *memL      = new QLabel("Mem(Used/Avail)");
    memL->setStyleSheet("QLabel { font-size : 12px;}");

    QLineEdit *memLE  = new QLineEdit(s.memory);

    memLE->setReadOnly(true);
    memLE->setStyleSheet("QLineEdit { font-size : 12px;}");

    grid->addWidget(name,   r,0,1,2); ++r;
    grid->addWidget(loadL,  r,1,1,1);
    grid->addWidget(loadLE, r,2,1,2); ++r;
    grid->addWidget(memL,   r,1,1,1);
    grid->addWidget(memLE,  r,2,1,2); ++r;
  }

  this->setLayout(grid);
}
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
void LoadMonitor::update()
{
  //Read and update load for all servers
  for(int i=0;i<servers.size();++i) {

    bool localHost = false;
    if(servers[i].ip == "127.0.0.1") localHost = true;

    QString cmd,file;
    if(localHost) {
      file = ".tmp.top.localhost";
      cmd = "top -b -n1";
    } else {
      file = ".tmp.top."+servers[i].ip;
      cmd  = "ssh "+servers[i].ip + " top -b -n1";
    }

    //Typical command
    //cmd ssh 192.168.1.76 top -b -n1 >  .tmp.top.192.168.1.76

    string fullCmd = cmd.toStdString() + " > " + file.toStdString();
    int ret = system(fullCmd.c_str());
    if(!ret) {
      setServerLoadFromTop(servers[i],file,false);
    }
  }

  //Read and update memory usage for all servers
  for(int i=0;i<servers.size();++i) {

    bool localHost = false;
    if(servers[i].ip == "127.0.0.1") localHost = true;

    QString cmd,file;
    if(localHost) {
      file = ".tmp.free.localhost";
      cmd = "free -g";
    } else {
      file = ".tmp.free."+servers[i].ip;
      cmd  = "ssh "+servers[i].ip + " free -g";
    }

    //Typical command
    //cmd ssh 192.168.1.76 top -b -n1 >  .tmp.top.192.168.1.76

    string fullCmd = cmd.toStdString() + " > " + file.toStdString();
    int ret = system(fullCmd.c_str());
    if(!ret) {
      setServerMemoryFromFree(servers[i],file,false);
    }
  }

  populateGrid();
}
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
void LoadMonitor::setServerMemoryFromFree(Server &s,QString file,bool debug)
{
  s.memory = "error";
  ifstream in(file.toStdString().c_str());
  if(!in.is_open()) {
    if(debug) cout<<"HERE FREE no file"<<endl;
    return;
  }

  string line;
  getline(in,line); //header
  getline(in,line); //mem:
  in.close();

  QString qline = QString::fromStdString(line);

  if(qline.length() == 0) {
    if(debug) cout<<"HERE FREE no qline"<<endl;
    return;
  }

  QStringList list;
  list = qline.split(" ",Qt::SkipEmptyParts);

  //0 'Mem:'
  //1 total
  //2 used
  //3 free
  //4 shared
  //5 buff/cache
  //6 available
  if(list.size() != 7) {
    if(debug) cout<<"HERE FREE bad split"<<endl;
    return;
  }

  //expects free to have been called as 'free -g'
  s.memory = QString("%1G/%2G").arg(list[2]).arg(list[6]);

}
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
void LoadMonitor::setServerLoadFromTop(Server &s,QString file,bool debug)
{
  s.load = "error";
  ifstream in(file.toStdString().c_str());
  if(!in.is_open()) {
    if(debug) cout<<"HERE TOP no file"<<endl;
    return;
  }

  string line;
  getline(in,line);
  in.close();

  QString qline = QString::fromStdString(line);

  if(qline.length() == 0) {
    if(debug) cout<<"HERE TOP no qline"<<endl;
    return;
  }

  QString flt("[+-]?([0-9]*[.])?[0-9]+");
  QString pattern("load average: (%1), (%2), (%3)");
  QRegularExpression rx(QString(pattern.arg(flt).arg(flt).arg(flt)));
  QRegularExpressionMatch match = rx.match(qline);

  if(!match.hasMatch()) {
    if(debug) cout<<"HERE TOP no match"<<endl;
    return;
  } 

  //0 is load average: 0.29, 0.33, 0.35
  //1 is 0.29
  //2 is 0.
  //3 is 0.33
  //4 is 0
  //5 is 0.35
  //6 is 0.

  QStringList matches = match.capturedTexts();
  if(matches.size() != 7) {
    if(debug) cout<<"HERE TOP wrong size"<<endl;
    return; 
  }

  s.load = matches[1]+"/"+matches[3]+"/"+matches[5];

}
// =======================================================================
// =======================================================================
QueueMonitor::QueueMonitor(QString _t,QWidget *parent)
    : QWidget(parent),
      title(_t),
      grid(new QGridLayout())
{
}
// ----------------------------------------------------------------------
QueueMonitor::QueueMonitor(QList<LsfQueue> &_q,QString _t,QWidget *parent)
    : QWidget(parent),
      queues(_q),
      title(_t),
      grid(new QGridLayout())
{
  first = true;
  populateGrid();
}
// ----------------------------------------------------------------------
// ----------------------------------------------------------------------
void QueueMonitor::populateGrid()
{
  int r=0;

  QLabel *top = new QLabel("QUEUES (Pend/Run/Max)");

  top->setStyleSheet("QLabel { color : #7fFF7f;}");
  grid->addWidget(top,   r,0,1,3); ++r;

  foreach(LsfQueue q,queues) {

    QLabel *name      = new QLabel(q.name+" ("+q.server.name+")");
    name->setStyleSheet("QLabel { font-size : 12px; color : #7fFF7f; }");

    QString load = QString("%1/%2/%3")
                   .arg(q.pending).arg(q.running).arg(q.maxSlots);

    QLineEdit *slotsLE = new QLineEdit(load);
    slotsLE->setStyleSheet("QLabel { font-size : 12px;}");

    slotsLE->setReadOnly(true);

    grid->addWidget(name,   r,0,1,2);
    grid->addWidget(slotsLE,r,2,1,1); ++r;
  }

  this->setLayout(grid);
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void QueueMonitor::update()
{
  //FIXME: insert query once LSF is setup; for now call the proxy
  //The proxy script returns a text file containing typical bqueues
  //output. The format is the default one used by bqueues

  //QString cmd("bqueues  > .qstat.txt");
  QString proxy("./scripts/bqueues.py --out .qstat.txt");

  bool debug = true;

  int ret = system(proxy.toStdString().c_str());
  if(ret) {
    if(debug) { cout<<"HERE QM sys failed"<<endl; }
    return;
  }

  setQueueStateFromBqueues(".qstat.txt",true);
  populateGrid();
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void QueueMonitor::setQueueStateFromBqueues(QString file,bool debug)
{
  ifstream in(file.toStdString().c_str());
  if(!in.is_open()) {
    if(debug) cout<<"HERE BQ no file"<<endl;
    return;
  }

  string line;
  //QUEUE_NAME  HOST     PRIO STATUS    MAX JL/U JL/P JL/H NJOBS PEND RUN SUSP
  getline(in,line); //header

  QString qline = QString::fromStdString(line);
  if(qline.length() == 0) {
    if(debug) cout<<"HERE BQ no line"<<endl;
    return;
  }

  struct MinQ {
    QString njobs;
    QString pend;
    QString run;
  };

  QMap<QString,MinQ> capture;

  while(getline(in,line)) {
    QString qline = QString::fromStdString(line);
    QStringList slist; 
    slist = qline.split(" ",Qt::SkipEmptyParts);

    if(slist.size() < 12) {
      if(debug) cout<<"HERE BQ bad split"<<endl;
      return;
    }

    //0 queue name
    //1-7 host,pri,stat,max,jlu,jlp,jln,
    //8 njobs
    //9 pend
    //10 run
    //11 susp

    MinQ mq;
    mq.njobs = slist[8];
    mq.pend  = slist[9];
    mq.run   = slist[10];
   
    capture.insert(slist[0],mq); 
  }

  for(int i=0;i<queues.size();++i) {
    QString name = queues[i].name;
    if(capture.find(name) != capture.end()) {
      int maxSlots = capture[name].njobs.toInt();
      int pending  = capture[name].pend.toInt();
      int running  = capture[name].run.toInt();

      queues[i].maxSlots = maxSlots;
      queues[i].pending  = pending;
      queues[i].running  = running;
    }
  }
}
// =======================================================================
// =======================================================================
StatusMonitor::StatusMonitor(QString _t, QWidget *parent)
    : QDockWidget(_t,parent),
      loadMonitor (new LoadMonitor ("Server Load")),
      queueMonitor(new QueueMonitor("LSF QStat")),
      title(_t)
{
  this->setObjectName("StatusMonitor");
  QWidget *widget = new QWidget(this);

  QVBoxLayout *vert = new QVBoxLayout();
  vert->setObjectName("vert");
  vert->addWidget(loadMonitor);
  vert->addWidget(queueMonitor);
  widget->setLayout(vert); 

  scan = new QPushButton("Scan");
  scan->setCheckable(true);
  scan->setChecked(false);
  connect(scan,SIGNAL(pressed()),this,SLOT(scanPressed()));

  refresh = new QPushButton("Refresh");
  connect(refresh,SIGNAL(pressed()),this,SLOT(refreshPressed()));

  QHBoxLayout *horz = new QHBoxLayout();

  horz->addWidget(scan);
  horz->addWidget(refresh);
  vert->addLayout(horz);

  this->setWidget(widget);
  this->setMaximumWidth(325);
  this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void StatusMonitor::populatePanels(QList<Server>   &servers,
                                  QList<LsfQueue> &queues)
{
  loadMonitor->servers = servers;
  queueMonitor->queues = queues;

  loadMonitor->populateGrid();
  queueMonitor->populateGrid();
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void StatusMonitor::scanPressed()
{
  if(scan->isChecked()) {
    killTimer(timerId);
  } else {
    timerId = startTimer(2000);
  }
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void StatusMonitor::refreshPressed()
{
  loadMonitor ->update();
  queueMonitor->update();
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void StatusMonitor::timerEvent(QTimerEvent *)
{
  refreshPressed();
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void StatusMonitor::removeRow(QGridLayout *g,int row)
{
  remove(g, row, -1, true);
  g->setRowMinimumHeight(row, 0);
  g->setRowStretch(row, 0);
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void StatusMonitor::removeColumn(QGridLayout *g, int col)
{
  remove(g, -1, col, true);
  g->setColumnMinimumWidth(col, 0);
  g->setColumnStretch(col, 0);
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void StatusMonitor::remove(QGridLayout *g,int row,int col,bool deleteWidgets)
{
  for (int i = g->count() - 1; i >= 0; i--) {
    int r, c, rs, cs;
    g->getItemPosition(i, &r, &c, &rs, &cs);
    if (
        (row == -1 || (r <= row && r + rs > row)) &&
        (col == -1 || (c <= col && c + cs > col))) {

      QLayoutItem *item = g->takeAt(i);
      if (deleteWidgets) {
        deleteChildWidgets(item);
      }
      delete item;
    }
  }
}
// -----------------------------------------------------------------------
// -----------------------------------------------------------------------
void StatusMonitor::deleteChildWidgets(QLayoutItem *item)
{
  QLayout *layout = item->layout();
  if (layout) {
    // Process all child items recursively.
    int itemCount = layout->count();
    for (int i = 0; i < itemCount; i++) {
      deleteChildWidgets(layout->itemAt(i));
    }
  }
  delete item->widget();
}

